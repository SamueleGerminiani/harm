// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   VCDParserlex



#include "VCDParser.hpp"


// Unqualified %code blocks.
#line 38 "flex_bison_src/VCDParser.ypp"


#include "VCDFileParser.hpp"

//! Current time while parsing the VCD file.
VCDTime current_time = 0;


#line 57 "..//VCDParser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace VCDParser {
#line 149 "..//VCDParser.cpp"

  /// Build a parser object.
  parser::parser (VCDFileParser & driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_TOK_VALUE: // TOK_VALUE
        value.YY_MOVE_OR_COPY< VCDBit > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_KW_BEGIN: // TOK_KW_BEGIN
      case symbol_kind::S_TOK_KW_FORK: // TOK_KW_FORK
      case symbol_kind::S_TOK_KW_FUNCTION: // TOK_KW_FUNCTION
      case symbol_kind::S_TOK_KW_MODULE: // TOK_KW_MODULE
      case symbol_kind::S_TOK_KW_INTERFACE: // TOK_KW_INTERFACE
      case symbol_kind::S_TOK_KW_STRUCT: // TOK_KW_STRUCT
      case symbol_kind::S_TOK_KW_TASK: // TOK_KW_TASK
      case symbol_kind::S_scope_type: // scope_type
        value.YY_MOVE_OR_COPY< VCDScopeType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_reference: // reference
        value.YY_MOVE_OR_COPY< VCDSignal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_TIME_NUMBER: // TOK_TIME_NUMBER
        value.YY_MOVE_OR_COPY< VCDTimeRes > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_TIME_UNIT: // TOK_TIME_UNIT
        value.YY_MOVE_OR_COPY< VCDTimeUnit > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_VAR_TYPE: // TOK_VAR_TYPE
        value.YY_MOVE_OR_COPY< VCDVarType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_DECIMAL_NUM: // TOK_DECIMAL_NUM
        value.YY_MOVE_OR_COPY< size_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_COMMENT_TEXT: // TOK_COMMENT_TEXT
      case symbol_kind::S_TOK_DATE_TEXT: // TOK_DATE_TEXT
      case symbol_kind::S_TOK_VERSION_TEXT: // TOK_VERSION_TEXT
      case symbol_kind::S_TOK_BIN_NUM: // TOK_BIN_NUM
      case symbol_kind::S_TOK_REAL_NUM: // TOK_REAL_NUM
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_comment_text: // comment_text
      case symbol_kind::S_version_text: // version_text
      case symbol_kind::S_date_text: // date_text
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_TOK_VALUE: // TOK_VALUE
        value.move< VCDBit > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_KW_BEGIN: // TOK_KW_BEGIN
      case symbol_kind::S_TOK_KW_FORK: // TOK_KW_FORK
      case symbol_kind::S_TOK_KW_FUNCTION: // TOK_KW_FUNCTION
      case symbol_kind::S_TOK_KW_MODULE: // TOK_KW_MODULE
      case symbol_kind::S_TOK_KW_INTERFACE: // TOK_KW_INTERFACE
      case symbol_kind::S_TOK_KW_STRUCT: // TOK_KW_STRUCT
      case symbol_kind::S_TOK_KW_TASK: // TOK_KW_TASK
      case symbol_kind::S_scope_type: // scope_type
        value.move< VCDScopeType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_reference: // reference
        value.move< VCDSignal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_TIME_NUMBER: // TOK_TIME_NUMBER
        value.move< VCDTimeRes > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_TIME_UNIT: // TOK_TIME_UNIT
        value.move< VCDTimeUnit > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_VAR_TYPE: // TOK_VAR_TYPE
        value.move< VCDVarType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_DECIMAL_NUM: // TOK_DECIMAL_NUM
        value.move< size_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_COMMENT_TEXT: // TOK_COMMENT_TEXT
      case symbol_kind::S_TOK_DATE_TEXT: // TOK_DATE_TEXT
      case symbol_kind::S_TOK_VERSION_TEXT: // TOK_VERSION_TEXT
      case symbol_kind::S_TOK_BIN_NUM: // TOK_BIN_NUM
      case symbol_kind::S_TOK_REAL_NUM: // TOK_REAL_NUM
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_comment_text: // comment_text
      case symbol_kind::S_version_text: // version_text
      case symbol_kind::S_date_text: // date_text
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_TOK_VALUE: // TOK_VALUE
        value.copy< VCDBit > (that.value);
        break;

      case symbol_kind::S_TOK_KW_BEGIN: // TOK_KW_BEGIN
      case symbol_kind::S_TOK_KW_FORK: // TOK_KW_FORK
      case symbol_kind::S_TOK_KW_FUNCTION: // TOK_KW_FUNCTION
      case symbol_kind::S_TOK_KW_MODULE: // TOK_KW_MODULE
      case symbol_kind::S_TOK_KW_INTERFACE: // TOK_KW_INTERFACE
      case symbol_kind::S_TOK_KW_STRUCT: // TOK_KW_STRUCT
      case symbol_kind::S_TOK_KW_TASK: // TOK_KW_TASK
      case symbol_kind::S_scope_type: // scope_type
        value.copy< VCDScopeType > (that.value);
        break;

      case symbol_kind::S_reference: // reference
        value.copy< VCDSignal* > (that.value);
        break;

      case symbol_kind::S_TOK_TIME_NUMBER: // TOK_TIME_NUMBER
        value.copy< VCDTimeRes > (that.value);
        break;

      case symbol_kind::S_TOK_TIME_UNIT: // TOK_TIME_UNIT
        value.copy< VCDTimeUnit > (that.value);
        break;

      case symbol_kind::S_TOK_VAR_TYPE: // TOK_VAR_TYPE
        value.copy< VCDVarType > (that.value);
        break;

      case symbol_kind::S_TOK_DECIMAL_NUM: // TOK_DECIMAL_NUM
        value.copy< size_t > (that.value);
        break;

      case symbol_kind::S_TOK_COMMENT_TEXT: // TOK_COMMENT_TEXT
      case symbol_kind::S_TOK_DATE_TEXT: // TOK_DATE_TEXT
      case symbol_kind::S_TOK_VERSION_TEXT: // TOK_VERSION_TEXT
      case symbol_kind::S_TOK_BIN_NUM: // TOK_BIN_NUM
      case symbol_kind::S_TOK_REAL_NUM: // TOK_REAL_NUM
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_comment_text: // comment_text
      case symbol_kind::S_version_text: // version_text
      case symbol_kind::S_date_text: // date_text
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_TOK_VALUE: // TOK_VALUE
        value.move< VCDBit > (that.value);
        break;

      case symbol_kind::S_TOK_KW_BEGIN: // TOK_KW_BEGIN
      case symbol_kind::S_TOK_KW_FORK: // TOK_KW_FORK
      case symbol_kind::S_TOK_KW_FUNCTION: // TOK_KW_FUNCTION
      case symbol_kind::S_TOK_KW_MODULE: // TOK_KW_MODULE
      case symbol_kind::S_TOK_KW_INTERFACE: // TOK_KW_INTERFACE
      case symbol_kind::S_TOK_KW_STRUCT: // TOK_KW_STRUCT
      case symbol_kind::S_TOK_KW_TASK: // TOK_KW_TASK
      case symbol_kind::S_scope_type: // scope_type
        value.move< VCDScopeType > (that.value);
        break;

      case symbol_kind::S_reference: // reference
        value.move< VCDSignal* > (that.value);
        break;

      case symbol_kind::S_TOK_TIME_NUMBER: // TOK_TIME_NUMBER
        value.move< VCDTimeRes > (that.value);
        break;

      case symbol_kind::S_TOK_TIME_UNIT: // TOK_TIME_UNIT
        value.move< VCDTimeUnit > (that.value);
        break;

      case symbol_kind::S_TOK_VAR_TYPE: // TOK_VAR_TYPE
        value.move< VCDVarType > (that.value);
        break;

      case symbol_kind::S_TOK_DECIMAL_NUM: // TOK_DECIMAL_NUM
        value.move< size_t > (that.value);
        break;

      case symbol_kind::S_TOK_COMMENT_TEXT: // TOK_COMMENT_TEXT
      case symbol_kind::S_TOK_DATE_TEXT: // TOK_DATE_TEXT
      case symbol_kind::S_TOK_VERSION_TEXT: // TOK_VERSION_TEXT
      case symbol_kind::S_TOK_BIN_NUM: // TOK_BIN_NUM
      case symbol_kind::S_TOK_REAL_NUM: // TOK_REAL_NUM
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_comment_text: // comment_text
      case symbol_kind::S_version_text: // version_text
      case symbol_kind::S_date_text: // date_text
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 31 "flex_bison_src/VCDParser.ypp"
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.filepath;
}

#line 602 "..//VCDParser.cpp"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_TOK_VALUE: // TOK_VALUE
        yylhs.value.emplace< VCDBit > ();
        break;

      case symbol_kind::S_TOK_KW_BEGIN: // TOK_KW_BEGIN
      case symbol_kind::S_TOK_KW_FORK: // TOK_KW_FORK
      case symbol_kind::S_TOK_KW_FUNCTION: // TOK_KW_FUNCTION
      case symbol_kind::S_TOK_KW_MODULE: // TOK_KW_MODULE
      case symbol_kind::S_TOK_KW_INTERFACE: // TOK_KW_INTERFACE
      case symbol_kind::S_TOK_KW_STRUCT: // TOK_KW_STRUCT
      case symbol_kind::S_TOK_KW_TASK: // TOK_KW_TASK
      case symbol_kind::S_scope_type: // scope_type
        yylhs.value.emplace< VCDScopeType > ();
        break;

      case symbol_kind::S_reference: // reference
        yylhs.value.emplace< VCDSignal* > ();
        break;

      case symbol_kind::S_TOK_TIME_NUMBER: // TOK_TIME_NUMBER
        yylhs.value.emplace< VCDTimeRes > ();
        break;

      case symbol_kind::S_TOK_TIME_UNIT: // TOK_TIME_UNIT
        yylhs.value.emplace< VCDTimeUnit > ();
        break;

      case symbol_kind::S_TOK_VAR_TYPE: // TOK_VAR_TYPE
        yylhs.value.emplace< VCDVarType > ();
        break;

      case symbol_kind::S_TOK_DECIMAL_NUM: // TOK_DECIMAL_NUM
        yylhs.value.emplace< size_t > ();
        break;

      case symbol_kind::S_TOK_COMMENT_TEXT: // TOK_COMMENT_TEXT
      case symbol_kind::S_TOK_DATE_TEXT: // TOK_DATE_TEXT
      case symbol_kind::S_TOK_VERSION_TEXT: // TOK_VERSION_TEXT
      case symbol_kind::S_TOK_BIN_NUM: // TOK_BIN_NUM
      case symbol_kind::S_TOK_REAL_NUM: // TOK_REAL_NUM
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_comment_text: // comment_text
      case symbol_kind::S_version_text: // version_text
      case symbol_kind::S_date_text: // date_text
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 10: // declaration_command: TOK_KW_COMMENT comment_text TOK_KW_END
#line 115 "flex_bison_src/VCDParser.ypp"
                                                {
    driver.fh -> comment = yystack_[1].value.as < std::string > ();
}
#line 789 "..//VCDParser.cpp"
    break;

  case 11: // declaration_command: TOK_KW_DATE date_text TOK_KW_END
#line 118 "flex_bison_src/VCDParser.ypp"
                                                {
    driver.fh -> date = yystack_[1].value.as < std::string > ();
}
#line 797 "..//VCDParser.cpp"
    break;

  case 13: // declaration_command: TOK_KW_SCOPE scope_type TOK_IDENTIFIER TOK_KW_END
#line 122 "flex_bison_src/VCDParser.ypp"
                                                         {
    // PUSH the current scope stack.
    
    VCDScope * new_scope = new VCDScope();
    new_scope -> name = yystack_[1].value.as < std::string > ();
    new_scope -> type = yystack_[2].value.as < VCDScopeType > ();
    new_scope -> parent = driver.scopes.top();
    
    driver.fh -> add_scope(
        new_scope
    );
    
    driver.scopes.top() -> children.push_back(new_scope);
    driver.scopes.push(new_scope);

}
#line 818 "..//VCDParser.cpp"
    break;

  case 14: // declaration_command: TOK_KW_TIMESCALE TOK_TIME_NUMBER TOK_TIME_UNIT TOK_KW_END
#line 138 "flex_bison_src/VCDParser.ypp"
                                                              {
    driver.fh -> time_resolution = yystack_[2].value.as < VCDTimeRes > ();
    driver.fh -> time_units      = yystack_[1].value.as < VCDTimeUnit > ();
}
#line 827 "..//VCDParser.cpp"
    break;

  case 15: // declaration_command: TOK_KW_UPSCOPE TOK_KW_END
#line 142 "flex_bison_src/VCDParser.ypp"
                               {
    // POP the current scope stack.

    driver.scopes.pop();

}
#line 838 "..//VCDParser.cpp"
    break;

  case 16: // declaration_command: TOK_KW_VAR TOK_VAR_TYPE TOK_DECIMAL_NUM TOK_IDENTIFIER reference TOK_KW_END
#line 149 "flex_bison_src/VCDParser.ypp"
               {
    // Add this variable to the current scope.

          VCDSignal *new_signal = yystack_[1].value.as < VCDSignal* > ();
          new_signal->type = yystack_[4].value.as < VCDVarType > ();
          new_signal->size = yystack_[3].value.as < size_t > ();
          new_signal->hash = yystack_[2].value.as < std::string > ();

          if (new_signal->type != VCDVarType::VCD_VAR_REAL &&
              new_signal->type != VCDVarType::VCD_VAR_REALTIME) {
            if (new_signal->size == 1 && new_signal->lindex <= 0) {
              new_signal->rindex = -1;
              new_signal->lindex = 0;
            } else if (new_signal->size > 0 && new_signal->rindex == -1 &&
                       new_signal->lindex == -1) {
              new_signal->rindex = 0;
              new_signal->lindex = new_signal->size - 1;
            } else if (new_signal->size > 0 && new_signal->rindex == 0 &&
                       new_signal->lindex == 0) {
              new_signal->rindex = 0;
              new_signal->lindex = new_signal->size - 1;
            }
          }

          if (new_signal->lindex != -1 || new_signal->rindex != -1) {
            if (new_signal->size == 1) {
              if (!((new_signal->lindex == -1) || (new_signal->rindex == -1))) {
                std::cout << "!((new_signal->lindex == -1) || "
                             "(new_signal->rindex == -1))"
                          << "\n";
                std::cout << "Hash:" << new_signal->hash << "\n";
                std::cout << "MSB:" << new_signal->lindex << "\n";
                std::cout << "LSB:" << new_signal->rindex << "\n";
                std::cout << "Size:" << new_signal->size << "\n";
                assert(0);
                exit(1);
              }
            } else if (new_signal->size != 0) {

              if (new_signal->lindex < 0) {
                std::cout << " the size is != 1 but MSB is < 0"
                          << "\n";
                std::cout << "Hash:" << new_signal->hash << "\n";
                std::cout << "MSB:" << new_signal->lindex << "\n";
                std::cout << "LSB:" << new_signal->rindex << "\n";
                std::cout << "Size:" << new_signal->size << "\n";
                assert(0);
                exit(1);
              }
              if (new_signal->lindex < new_signal->rindex) {
                std::cout
                    << "Reverse bit direction not supported, vectors must "
                       "be defined like this: [MSB:LSB] with MSB > LSB"
                    << "\n";
                std::cout << "Hash:" << new_signal->hash << "\n";
                std::cout << "MSB:" << new_signal->lindex << "\n";
                std::cout << "LSB:" << new_signal->rindex << "\n";
                std::cout << "Size:" << new_signal->size << "\n";
                assert(0);
                exit(1);
              }
              if ((new_signal->lindex - new_signal->rindex) + 1 !=
                  new_signal->size) {
                std::cout << "Size does not match vector declaration"
                          << "\n";
                std::cout << "Hash:" << new_signal->hash << "\n";
                std::cout << "MSB:" << new_signal->lindex << "\n";
                std::cout << "LSB:" << new_signal->rindex << "\n";
                std::cout << "Size:" << new_signal->size << "\n";
                exit(1);
              }
            }
          }

          VCDScope *scope = driver.scopes.top();

          new_signal->scope = driver.scopes.top();
          scope->signals.push_back(new_signal);

          driver.fh->add_signal(new_signal);


}
#line 926 "..//VCDParser.cpp"
    break;

  case 17: // declaration_command: TOK_KW_VERSION version_text TOK_KW_END
#line 232 "flex_bison_src/VCDParser.ypp"
                                            {
    driver.fh -> version = yystack_[1].value.as < std::string > ();
}
#line 934 "..//VCDParser.cpp"
    break;

  case 25: // scope_type: TOK_KW_BEGIN
#line 248 "flex_bison_src/VCDParser.ypp"
    { yylhs.value.as < VCDScopeType > () = yystack_[0].value.as < VCDScopeType > (); }
#line 940 "..//VCDParser.cpp"
    break;

  case 26: // scope_type: TOK_KW_FORK
#line 249 "flex_bison_src/VCDParser.ypp"
    { yylhs.value.as < VCDScopeType > () = yystack_[0].value.as < VCDScopeType > (); }
#line 946 "..//VCDParser.cpp"
    break;

  case 27: // scope_type: TOK_KW_FUNCTION
#line 250 "flex_bison_src/VCDParser.ypp"
    { yylhs.value.as < VCDScopeType > () = yystack_[0].value.as < VCDScopeType > (); }
#line 952 "..//VCDParser.cpp"
    break;

  case 28: // scope_type: TOK_KW_MODULE
#line 251 "flex_bison_src/VCDParser.ypp"
    { yylhs.value.as < VCDScopeType > () = yystack_[0].value.as < VCDScopeType > (); }
#line 958 "..//VCDParser.cpp"
    break;

  case 29: // scope_type: TOK_KW_STRUCT
#line 252 "flex_bison_src/VCDParser.ypp"
    { yylhs.value.as < VCDScopeType > () = yystack_[0].value.as < VCDScopeType > (); }
#line 964 "..//VCDParser.cpp"
    break;

  case 30: // scope_type: TOK_KW_INTERFACE
#line 253 "flex_bison_src/VCDParser.ypp"
    { yylhs.value.as < VCDScopeType > () = yystack_[0].value.as < VCDScopeType > (); }
#line 970 "..//VCDParser.cpp"
    break;

  case 31: // scope_type: TOK_KW_TASK
#line 254 "flex_bison_src/VCDParser.ypp"
    { yylhs.value.as < VCDScopeType > () = yystack_[0].value.as < VCDScopeType > (); }
#line 976 "..//VCDParser.cpp"
    break;

  case 32: // simulation_time: TOK_HASH TOK_DECIMAL_NUM
#line 257 "flex_bison_src/VCDParser.ypp"
                                           {
    current_time =  yystack_[0].value.as < size_t > ();
    if (current_time > driver.end_time)
        YYACCEPT;
    if (current_time > driver.start_time)
        driver.fh    -> add_timestamp(yystack_[0].value.as < size_t > ());
}
#line 988 "..//VCDParser.cpp"
    break;

  case 37: // scalar_value_change: TOK_VALUE TOK_IDENTIFIER
#line 273 "flex_bison_src/VCDParser.ypp"
                                               {

    VCDSignalHash   hash  = yystack_[0].value.as < std::string > ();
    if (current_time > driver.start_time) {
        VCDTimedValue * toadd = new VCDTimedValue();

        toadd -> time   = current_time;
        toadd -> value  = new VCDValue(yystack_[1].value.as < VCDBit > ());

        driver.fh -> add_signal_value(toadd, hash);
    }

}
#line 1006 "..//VCDParser.cpp"
    break;

  case 38: // vector_value_change: TOK_BIN_NUM TOK_IDENTIFIER
#line 289 "flex_bison_src/VCDParser.ypp"
                                   {

    VCDSignalHash   hash  = yystack_[0].value.as < std::string > ();
    VCDTimedValue * toadd = new VCDTimedValue();
    
    toadd -> time   = current_time;

    VCDBitVector * vec = new VCDBitVector();
    VCDValue * val = new VCDValue(vec);

    for(int i =1; i < yystack_[1].value.as < std::string > ().size(); i ++) {
        switch(yystack_[1].value.as < std::string > ()[i]) {
            case '0':
                vec -> push_back(VCD_0);
                break;
            case '1':
                vec -> push_back(VCD_1);
                break;
            case 'x':
            case 'X':
                vec -> push_back(VCD_X);
                break;
            case 'z':
            case 'Z':
                vec -> push_back(VCD_Z);
                break;
            default:
                vec -> push_back(VCD_X);
                break;
        }
    }

    toadd -> value = val;

    driver.fh -> add_signal_value(toadd, hash);

}
#line 1048 "..//VCDParser.cpp"
    break;

  case 39: // vector_value_change: TOK_REAL_NUM TOK_IDENTIFIER
#line 326 "flex_bison_src/VCDParser.ypp"
                                   {

    VCDSignalHash   hash  = yystack_[0].value.as < std::string > ();
    VCDTimedValue * toadd = new VCDTimedValue();
    
    toadd -> time   = current_time;
    toadd -> value  = 0;

    VCDValue * val;
    VCDReal real_value;
    
    // Legal way of parsing dumped floats according to the spec.
    // Sec 21.7.2.1, paragraph 4.
    const char * buffer = yystack_[1].value.as < std::string > ().c_str() + 1;
    float tmp;
    std::sscanf(buffer, "%g", &tmp);
    real_value = tmp;
    
    toadd -> value = new VCDValue(real_value);
    driver.fh -> add_signal_value(toadd, hash);
}
#line 1074 "..//VCDParser.cpp"
    break;

  case 40: // reference: TOK_IDENTIFIER
#line 349 "flex_bison_src/VCDParser.ypp"
                   {
    yylhs.value.as < VCDSignal* > ()  = new VCDSignal();
    yylhs.value.as < VCDSignal* > () -> reference = yystack_[0].value.as < std::string > ();
    yylhs.value.as < VCDSignal* > () -> lindex = -1;
    yylhs.value.as < VCDSignal* > () -> rindex = -1;
}
#line 1085 "..//VCDParser.cpp"
    break;

  case 41: // reference: TOK_IDENTIFIER TOK_BRACKET_O TOK_DECIMAL_NUM TOK_BRACKET_C
#line 355 "flex_bison_src/VCDParser.ypp"
                                                              {
    yylhs.value.as < VCDSignal* > ()  = new VCDSignal();
    yylhs.value.as < VCDSignal* > () -> reference = yystack_[3].value.as < std::string > ();
    yylhs.value.as < VCDSignal* > () -> lindex = yystack_[1].value.as < size_t > ();
    yylhs.value.as < VCDSignal* > () -> rindex = -1;
}
#line 1096 "..//VCDParser.cpp"
    break;

  case 42: // reference: TOK_IDENTIFIER TOK_BRACKET_O TOK_DECIMAL_NUM TOK_COLON TOK_DECIMAL_NUM TOK_BRACKET_C
#line 362 "flex_bison_src/VCDParser.ypp"
                 {
    yylhs.value.as < VCDSignal* > ()  = new VCDSignal();
    yylhs.value.as < VCDSignal* > () -> reference = yystack_[5].value.as < std::string > ();
    if (yystack_[3].value.as < size_t > () == 0 && yystack_[3].value.as < size_t > () == yystack_[1].value.as < size_t > ()) {
        yylhs.value.as < VCDSignal* > () -> lindex = -1;
        yylhs.value.as < VCDSignal* > () -> rindex = -1;
    } else {
        yylhs.value.as < VCDSignal* > () -> lindex = yystack_[3].value.as < size_t > ();
        yylhs.value.as < VCDSignal* > () -> rindex = yystack_[1].value.as < size_t > ();
    }
}
#line 1112 "..//VCDParser.cpp"
    break;

  case 43: // comment_text: %empty
#line 375 "flex_bison_src/VCDParser.ypp"
            {
    yylhs.value.as < std::string > () = std::string();
}
#line 1120 "..//VCDParser.cpp"
    break;

  case 44: // comment_text: TOK_COMMENT_TEXT
#line 378 "flex_bison_src/VCDParser.ypp"
                     {
    yylhs.value.as < std::string > () = std::string(yystack_[0].value.as < std::string > ());
}
#line 1128 "..//VCDParser.cpp"
    break;

  case 45: // version_text: %empty
#line 383 "flex_bison_src/VCDParser.ypp"
          {
    yylhs.value.as < std::string > () = std::string();
}
#line 1136 "..//VCDParser.cpp"
    break;

  case 46: // version_text: TOK_VERSION_TEXT
#line 386 "flex_bison_src/VCDParser.ypp"
                     {
    yylhs.value.as < std::string > () = std::string(yystack_[0].value.as < std::string > ());
}
#line 1144 "..//VCDParser.cpp"
    break;

  case 47: // date_text: %empty
#line 392 "flex_bison_src/VCDParser.ypp"
          {
    yylhs.value.as < std::string > () = std::string();
}
#line 1152 "..//VCDParser.cpp"
    break;

  case 48: // date_text: TOK_DATE_TEXT
#line 395 "flex_bison_src/VCDParser.ypp"
                  {
    yylhs.value.as < std::string > () = std::string(yystack_[0].value.as < std::string > ());
}
#line 1160 "..//VCDParser.cpp"
    break;


#line 1164 "..//VCDParser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -26;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      44,    35,    -8,    -3,    69,   -25,     5,   -15,     2,   -21,
     -21,   -21,   -21,   -16,   -14,   -13,   -11,    31,    44,    54,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,    -5,   -26,    28,
     -26,    33,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
      29,    36,   -26,    40,   -26,    64,    -1,     4,     8,    16,
     -26,   -26,   -26,   -26,   -26,    54,   -26,   -21,   -26,   -26,
     -26,   -26,   -26,    75,    76,    45,   -26,   -26,   -26,   -26,
     -26,   -26,   -26,    46,    83,    92,    50,   -26,    17,   -26,
      60,    97,   -26
  };

  const signed char
  parser::yydefact_[] =
  {
       2,    43,    47,     0,     0,     0,     0,     0,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     4,
       6,     8,    23,    24,    35,    36,    44,     0,    33,     0,
      48,     0,    12,    25,    26,    27,    28,    30,    29,    31,
       0,     0,    15,     0,    46,     0,     0,     0,     0,     0,
      32,    37,    38,    39,     1,     3,     7,     0,     9,    22,
      34,    10,    11,     0,     0,     0,    17,    18,    19,    20,
      21,    13,    14,     0,    40,     0,     0,    16,     0,    41,
       0,     0,    42
  };

  const signed char
  parser::yypgoto_[] =
  {
     -26,   -26,   -26,    84,    85,   -18,   -26,   -26,    -2,     0,
     -26,   -26,   -26,   -26,   -26,   -26
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,    17,    18,    19,    20,    21,    40,    22,    27,    28,
      24,    25,    75,    29,    45,    31
  };

  const signed char
  parser::yytable_[] =
  {
      23,    58,    59,    30,    32,    41,    67,    46,    47,    48,
      49,    68,    42,    14,    15,    69,    16,    43,    23,    23,
      44,    79,    80,    70,    50,    51,    52,    60,    53,    14,
      15,    54,    16,    14,    15,    61,    16,    58,    14,    15,
      62,    16,    14,    15,    26,    16,    60,    60,    60,    60,
      14,    15,     1,    16,     2,    23,     3,     4,     5,     6,
       7,     8,    57,     9,    10,    11,    12,    64,    63,    14,
      15,    66,    16,     9,    10,    11,    12,    13,    14,    15,
      65,    16,    71,    72,    73,    74,    76,    13,    14,    15,
      78,    16,    33,    34,    35,    36,    37,    38,    39,    77,
      81,    82,    55,    56
  };

  const signed char
  parser::yycheck_[] =
  {
       0,    19,     7,    11,     7,    30,     7,     9,    10,    11,
      12,     7,     7,    34,    35,     7,    37,    32,    18,    19,
      18,     4,     5,     7,    40,    39,    39,    27,    39,    34,
      35,     0,    37,    34,    35,     7,    37,    55,    34,    35,
       7,    37,    34,    35,     9,    37,    46,    47,    48,    49,
      34,    35,     8,    37,    10,    55,    12,    13,    14,    15,
      16,    17,     8,    19,    20,    21,    22,    31,    39,    34,
      35,     7,    37,    19,    20,    21,    22,    33,    34,    35,
      40,    37,     7,     7,    39,    39,     3,    33,    34,    35,
      40,    37,    23,    24,    25,    26,    27,    28,    29,     7,
      40,     4,    18,    18
  };

  const signed char
  parser::yystos_[] =
  {
       0,     8,    10,    12,    13,    14,    15,    16,    17,    19,
      20,    21,    22,    33,    34,    35,    37,    42,    43,    44,
      45,    46,    48,    50,    51,    52,     9,    49,    50,    54,
      11,    56,     7,    23,    24,    25,    26,    27,    28,    29,
      47,    30,     7,    32,    18,    55,    49,    49,    49,    49,
      40,    39,    39,    39,     0,    44,    45,     8,    46,     7,
      50,     7,     7,    39,    31,    40,     7,     7,     7,     7,
       7,     7,     7,    39,    39,    53,     3,     7,    40,     4,
       5,    40,     4
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    41,    42,    42,    42,    42,    43,    43,    44,    44,
      45,    45,    45,    45,    45,    45,    45,    45,    46,    46,
      46,    46,    46,    46,    46,    47,    47,    47,    47,    47,
      47,    47,    48,    49,    49,    50,    50,    51,    52,    52,
      53,    53,    53,    54,    54,    55,    55,    56,    56
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     0,     2,     1,     1,     1,     2,     1,     2,
       3,     3,     2,     4,     4,     2,     6,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     1,     2,     2,     2,
       1,     4,     6,     0,     1,     0,     1,     0,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TOK_BRACKET_O",
  "TOK_BRACKET_C", "TOK_COLON", "TOK_DOLLAR", "TOK_KW_END",
  "TOK_KW_COMMENT", "TOK_COMMENT_TEXT", "TOK_KW_DATE", "TOK_DATE_TEXT",
  "TOK_KW_ENDDEFINITIONS", "TOK_KW_SCOPE", "TOK_KW_TIMESCALE",
  "TOK_KW_UPSCOPE", "TOK_KW_VAR", "TOK_KW_VERSION", "TOK_VERSION_TEXT",
  "TOK_KW_DUMPALL", "TOK_KW_DUMPOFF", "TOK_KW_DUMPON", "TOK_KW_DUMPVARS",
  "TOK_KW_BEGIN", "TOK_KW_FORK", "TOK_KW_FUNCTION", "TOK_KW_MODULE",
  "TOK_KW_INTERFACE", "TOK_KW_STRUCT", "TOK_KW_TASK", "TOK_TIME_NUMBER",
  "TOK_TIME_UNIT", "TOK_VAR_TYPE", "TOK_HASH", "TOK_VALUE", "TOK_BIN_NUM",
  "TOK_BINARY_NUMBER", "TOK_REAL_NUM", "TOK_REAL_NUMBER", "TOK_IDENTIFIER",
  "TOK_DECIMAL_NUM", "$accept", "input", "declaration_commands",
  "simulation_commands", "declaration_command", "simulation_command",
  "scope_type", "simulation_time", "value_changes", "value_change",
  "scalar_value_change", "vector_value_change", "reference",
  "comment_text", "version_text", "date_text", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    98,    98,    99,   100,   101,   105,   106,   110,   111,
     115,   118,   121,   122,   138,   142,   148,   232,   238,   239,
     240,   241,   242,   243,   244,   248,   249,   250,   251,   252,
     253,   254,   257,   266,   267,   270,   271,   273,   289,   326,
     349,   355,   361,   375,   378,   383,   386,   392,   395
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // VCDParser
#line 1694 "..//VCDParser.cpp"

#line 399 "flex_bison_src/VCDParser.ypp"



void VCDParser::parser::error (
    const location_type& l,
    const std::string& m) {
    driver.error(l,m);
}
