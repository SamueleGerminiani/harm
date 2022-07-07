
#include "z3TestCaseGenerator.hh"
#include <exp.hh>
#include <z3++.h>

namespace z3 {

z3::expr negateTestCases(const std::vector<TestCase> &tcs, context &c);

std::vector<TestCase>
Z3TestCaseGenerator::generateTestCase(expression::Proposition &p, size_t n,
                                      const std::vector<TestCase> &alreadyGen) {
  const size_t manyTC = 100;
  if (n >= manyTC) {
    messageInfo("Generating many testcases(" + std::to_string(n) +
                ")... this could take a while");
  }
  expr z3Expr = propToz3Expr(p);
  z3::context &c = z3Expr.ctx();

  // DEBUG
  // std::cout << "z3Expr: " << z3Expr << "\n";
  // bool doubleTC = false;

  z3::solver s(c);

  z3::params params(c);
  // max 2 seconds before aborting the solver
  params.set(":timeout", 2000U);
  s.set(params);

  s.add(z3Expr);

  std::vector<TestCase> res;
  res.clear();

  // add counterexamples
  if (!alreadyGen.empty()) {
    s.add(negateTestCases(alreadyGen, c));
  }


  for (size_t i = 0; i < n; i++) {
    // DEBUG
    // std::cout << "-----------------TestCase[" << i <<
    // "]---------------\n"; std::cout << "Solver:" << s << "\n"; std::cout << s << "\n";
    if (s.check() == sat) {
      // this variables is a chain of &&s of all models found
      z3::expr thisInstanceTestCase = c.bool_val(true);

      z3::model model = s.get_model();
      /* enable model completion, otherwise the solver might produce a
       partial model */
      model.eval(z3Expr, true);

      // DEBUG
      // std::cout<<"-------->"<<_converter.getNumberVariables()<<" vs
      // "<<model.size()<<"\n";
      // std::cout << "Model.size():" << model.size() << "\n";
      // std::cout << model << "\n";
      assert(model.size() == _converter.getNumberVariables());

      TestCase tc;
      for (size_t j = 0; j < model.size(); j++) {
        Assignment ass;
        TypeValue tv;
        VarValue vv;

        // proceed accordingly for each variable type

        // NUMERIC
        if (model.get_const_interp(model[j]).is_fpa()) {
          std::string varName = model[j].name().str();
          // DEBUG
          // doubleTC = true;

          // 32 bit float
          if (Z3_fpa_get_sbits(model.get_const_interp(model[j]).ctx(),
                               model.get_const_interp(model[j]).get_sort()) ==
              24) {
            uint64_t v_significand;
            Z3_fpa_get_numeral_significand_uint64(
                model.get_const_interp(model[j]).ctx(),
                model.get_const_interp(model[j]), &v_significand);
            int64_t v_exp;
            Z3_fpa_get_numeral_exponent_int64(
                model.get_const_interp(model[j]).ctx(),
                model.get_const_interp(model[j]), &v_exp, true);
            int v_sign_int;
            Z3_fpa_get_numeral_sign(model.get_const_interp(model[j]).ctx(),
                                    model.get_const_interp(model[j]),
                                    &v_sign_int);

            /* convert to un unsigned type to perform memory
             operations*/
            uint64_t v_sign = v_sign_int;

            // compose the 3 parts of the float
            uint32_t composed = ((v_sign << 63ULL) | (v_exp << 55ULL) |
                                 (v_significand << 32ULL)) >>
                                32ULL;

            /* convert the integer representation of a float to a C
             float*/
            intToFloat convertedComposed;
            convertedComposed.i = composed;

            vv.dVal = convertedComposed.f;
            tv = std::make_pair(expression::VarType::Numeric, vv);
            ass = std::make_pair(varName, tv);

            expr var = c.fpa_const(varName.c_str(), 8, 24);
            thisInstanceTestCase = thisInstanceTestCase &&
                                   (var == model.get_const_interp(model[j]));

            // 64 bit float
          } else if (Z3_fpa_get_sbits(
                         model.get_const_interp(model[j]).ctx(),
                         model.get_const_interp(model[j]).get_sort()) == 53) {

            vv.dVal =
                Z3_get_numeral_double(model.get_const_interp(model[j]).ctx(),
                                      model.get_const_interp(model[j]));
            tv = std::make_pair(expression::VarType::Numeric, vv);
            ass = std::make_pair(varName, tv);

            expr var = c.fpa_const(varName.c_str(), 11, 53);
            thisInstanceTestCase = thisInstanceTestCase &&
                                   (var == model.get_const_interp(model[j]));



          } else {
            messageError("Uknown float sort!");
          }

          // BOOL
        } else if (model.get_const_interp(model[j]).is_bool()) {
          std::string varName = model[j].name().str();
          bool v =
              Z3_get_bool_value(model.get_const_interp(model[j]).ctx(),
                                model.get_const_interp(model[j])) == Z3_L_TRUE
                  ? true
                  : false;

          vv.bVal = v;
          tv = std::make_pair(expression::VarType::Bool, vv);
          ass = std::make_pair(varName, tv);

          expr var = c.bool_const(varName.c_str());
          thisInstanceTestCase = thisInstanceTestCase && (v ? var : !var);

          /* LOGIC (char,short,int,long long and their unsigned
           version)*/
        } else if (model.get_const_interp(model[j]).is_bv()) {
          std::string varName = model[j].name().str();
          uint64_t v = model.get_const_interp(model[j]).get_numeral_uint64();

          assert(_converter._varToTypeSize.count(varName));
          std::pair<expression::VarType, size_t> &varTypeSize =
              _converter._varToTypeSize.at(varName);
          // SLOGIC(signed integers)
          if (varTypeSize.first == expression::VarType::SLogic) {
            /*check if the most significand bit is 1 (negative
            integer) or 0 (positive integer) and proceed
            accordinly*/

            if (v & (1ULL << (varTypeSize.second - 1))) {
              // negative value needs conversion to 2s complement
              uint64_t mask = ULLONG_MAX;
              mask = mask << (varTypeSize.second - 1);
              vv.sVal = (int64_t)(v | mask);
            } else {
              // positive value
              vv.sVal = (int64_t)(v);
            }
            tv = std::make_pair(expression::VarType::SLogic, vv);
          } else if (varTypeSize.first == expression::VarType::ULogic) {
            // ULOGIC(unsigned integers)
            vv.uVal = v;
            tv = std::make_pair(expression::VarType::ULogic, vv);
          } else {
            messageError("Variable is of type z3 integer but an non-integer "
                         "expression type is found!");
          }

          ass = std::make_pair(varName, tv);

          expr var = c.bv_const(varName.c_str(), varTypeSize.second);
          thisInstanceTestCase =
              thisInstanceTestCase && (var == model.get_const_interp(model[j]));
        } else {
          messageError("Uknown variable type!");
        } // if type

        tc.push_back(ass);

      } // for model

      res.push_back(tc);

      /* add the model negated to generate a different model in the next
       * cycle*/
      s.add(!thisInstanceTestCase);
    } else {
      //      if (res.empty()) {
      //        messageError("Z3 couldn't find any testcases for proposition: "
      //        +
      //                     prop2String(p));
      //      } else {
      //        messageWarning(
      //            "Z3 couldn't find all the requested testcases for
      //            proposition: " + prop2String(p));
      //      }
     //  std::cout << "Unsat! Can't generate more testcases...\n";
      
      
      break;
    } // if check

  } // for n testcases

  // sort assignments by name
  for (TestCase &tc : res) {
    std::sort(std::begin(tc), std::end(tc), [](Assignment &e1, Assignment &e2) {
      return e1.first < e2.first;
    });
  }

  // DEBUG - check if all testcases are different(for float/double)
  // if (doubleTC) {
  //    for (size_t i = 0; i < res.size(); i++) {
  //        for (size_t j = i + 1; j < res.size(); j++) {
  //            for (size_t k = 0; k < res[0].size(); k++) {
  //                if (res[i][k].second.second.dVal !=
  //                    res[j][k].second.second.dVal) {
  //                    goto nextComparison;
  //                }
  //            }
  //            messageError("Found two equal testcases!");
  //        nextComparison:;
  //        }
  //    }
  //}
  return res;

} // end fun
z3::expr Z3TestCaseGenerator::negateTestCases(const std::vector<TestCase> &tcs,
                                              context &c) {

  z3::expr res = c.bool_val(true);
  for (const auto &tc : tcs) {
    z3::expr chain = c.bool_val(true);
    for (const auto &ass : tc) {
      z3::expr var(c);
      z3::expr val(c);
      auto ts = _converter._varToTypeSize.at(ass.first);
      switch (ass.second.first) {
      case expression::VarType::Bool:
        var = c.bool_const(ass.first.c_str());
        val = c.bool_val(ass.second.second.bVal);
        break;
      case expression::VarType::ULogic:
        var = c.bv_const(ass.first.c_str(),ts.second);
        val = c.bv_val( ass.second.second.uVal,ts.second);
        break;
      case expression::VarType::SLogic:
        var = c.bv_const(ass.first.c_str(),ts.second);
        val = c.bv_val( ass.second.second.sVal,ts.second);
        break;
      case expression::VarType::Numeric:
        if (ts.second == 32) {
          var = c.fpa_const(ass.first.c_str(),8,24);
          val = c.fpa_val((float)ass.second.second.dVal);
        } else {
          var = c.fpa_const(ass.first.c_str(),11,53);
          val = c.fpa_val((double)ass.second.second.dVal);
        }
        break;
      default:
        messageError("This should not happen!");
        break;
      }
      chain = chain && var == val;
    }
    chain = !(chain);
    res = res && chain;
  }
  return res;
}

expr Z3TestCaseGenerator::propToz3Expr(expression::Proposition &p) {
  _converter.clear();
  p.acceptVisitor(_converter);
  return _converter.get();
}
std::vector<expr>
Z3TestCaseGenerator::propToz3Expr(std::vector<expression::Proposition *> &ps) {
  _converter.clear();
  std::vector<expr> res;
  for (auto &p : ps) {
    p->acceptVisitor(_converter);
    res.push_back(_converter.get());
    _converter.clear();
  }
  return res;
}
std::vector<expr> Z3TestCaseGenerator::propToz3Expr(
    std::vector<std::shared_ptr<expression::Proposition>> &ps) {
  _converter.clear();
  std::vector<expr> res;
  for (auto &p : ps) {
    p->acceptVisitor(_converter);
    res.push_back(_converter.get());
    _converter.clear();
  }
  return res;
}

std::ostream &operator<<(std::ostream &o, const TestCase &tc) {
  o << "--------------------\n";
  for (const auto &ass : tc) {
    const z3::VarName &vn = ass.first;
    const z3::TypeValue &tv = ass.second;
    std::cout << (int)tv.first << " ";
    switch (tv.first) {
    case expression::VarType::Bool:
      std::cout << vn << ":" << tv.second.bVal << "\n";
      break;
    case expression::VarType::ULogic:
      std::cout << vn << ":" << tv.second.uVal << "\n";
      break;
    case expression::VarType::SLogic:
      std::cout << vn << ":" << tv.second.sVal << "\n";
      break;
    case expression::VarType::Numeric:
      std::cout << vn << ":" << tv.second.dVal << "\n";
      break;
    default:
      break;
    }
  }

  return o;
}

} // namespace z3
