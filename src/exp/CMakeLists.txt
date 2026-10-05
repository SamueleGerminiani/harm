project(exp)

SET(EXP_SRCS
    #propositional
    src/formula/atom/NumericExpression.cc
    src/formula/atom/Constant.cc
    src/formula/atom/Variable.cc 
    src/formula/expression/GenericExpression.cc
    src/formula/expression/BitSelector.cc
    src/formula/expression/Ternary.cc
    src/formula/expression/Substring.cc
    src/formula/expression/SetMembership.cc
    src/formula/expression/TypeCast.cc
    src/formula/function/Function.cc
    #temporal
    src/formula/temporal/BooleanLayer.cc
    src/formula/temporal/Property.cc
    src/formula/temporal/Sere.cc
    #visitors
    src/visitors/PrinterVisitor.cc
    src/visitors/ExpVisitor.cc
    src/visitors/CopyVisitor.cc
    src/visitors/VarExtractVisitor.cc
    src/visitors/TraceChangerVisitor.cc
    #utils
    src/expUtils/expUtils.cc
    src/expUtils/smtEquivalence.cc
    )


add_library(exp ${EXP_SRCS})

target_include_directories(exp PUBLIC include ../miner/utils/include/)
if(HARM_WITH_Z3)
    target_sources(exp PRIVATE src/visitors/ExpToZ3Visitor.cc)
    target_link_libraries(exp PUBLIC z3::libz3)
endif()
