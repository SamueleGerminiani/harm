// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file ../../../../include/traceReader/vcdTraceReader//VCDParser.hpp
 ** Define the VCDParser::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_VCDPARSER_INCLUDE_TRACEREADER_VCDTRACEREADER_VCDPARSER_HPP_INCLUDED
# define YY_VCDPARSER_INCLUDE_TRACEREADER_VCDTRACEREADER_VCDPARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 18 "flex_bison_src/VCDParser.ypp"

    #include <string>
    #include <map>

    #include "VCDTypes.hpp"
    #include "VCDFile.hpp"

    class VCDFileParser;

#line 59 "../../../../include/traceReader/vcdTraceReader//VCDParser.hpp"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

namespace VCDParser {
#line 199 "../../../../include/traceReader/vcdTraceReader//VCDParser.hpp"




  /// A Bison parser.
  class parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // TOK_VALUE
      char dummy1[sizeof (VCDBit)];

      // TOK_KW_BEGIN
      // TOK_KW_FORK
      // TOK_KW_FUNCTION
      // TOK_KW_MODULE
      // TOK_KW_INTERFACE
      // TOK_KW_STRUCT
      // TOK_KW_TASK
      // scope_type
      char dummy2[sizeof (VCDScopeType)];

      // reference
      char dummy3[sizeof (VCDSignal*)];

      // TOK_TIME_NUMBER
      char dummy4[sizeof (VCDTimeRes)];

      // TOK_TIME_UNIT
      char dummy5[sizeof (VCDTimeUnit)];

      // TOK_VAR_TYPE
      char dummy6[sizeof (VCDVarType)];

      // TOK_DECIMAL_NUM
      char dummy7[sizeof (size_t)];

      // TOK_COMMENT_TEXT
      // TOK_DATE_TEXT
      // TOK_VERSION_TEXT
      // TOK_BIN_NUM
      // TOK_REAL_NUM
      // TOK_IDENTIFIER
      // comment_text
      // version_text
      // date_text
      char dummy8[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    END = 0,                       // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    TOK_BRACKET_O = 258,           // TOK_BRACKET_O
    TOK_BRACKET_C = 259,           // TOK_BRACKET_C
    TOK_COLON = 260,               // TOK_COLON
    TOK_DOLLAR = 261,              // TOK_DOLLAR
    TOK_KW_END = 262,              // TOK_KW_END
    TOK_KW_COMMENT = 263,          // TOK_KW_COMMENT
    TOK_COMMENT_TEXT = 264,        // TOK_COMMENT_TEXT
    TOK_KW_DATE = 265,             // TOK_KW_DATE
    TOK_DATE_TEXT = 266,           // TOK_DATE_TEXT
    TOK_KW_ENDDEFINITIONS = 267,   // TOK_KW_ENDDEFINITIONS
    TOK_KW_SCOPE = 268,            // TOK_KW_SCOPE
    TOK_KW_TIMESCALE = 269,        // TOK_KW_TIMESCALE
    TOK_KW_UPSCOPE = 270,          // TOK_KW_UPSCOPE
    TOK_KW_VAR = 271,              // TOK_KW_VAR
    TOK_KW_VERSION = 272,          // TOK_KW_VERSION
    TOK_VERSION_TEXT = 273,        // TOK_VERSION_TEXT
    TOK_KW_DUMPALL = 274,          // TOK_KW_DUMPALL
    TOK_KW_DUMPOFF = 275,          // TOK_KW_DUMPOFF
    TOK_KW_DUMPON = 276,           // TOK_KW_DUMPON
    TOK_KW_DUMPVARS = 277,         // TOK_KW_DUMPVARS
    TOK_KW_BEGIN = 278,            // TOK_KW_BEGIN
    TOK_KW_FORK = 279,             // TOK_KW_FORK
    TOK_KW_FUNCTION = 280,         // TOK_KW_FUNCTION
    TOK_KW_MODULE = 281,           // TOK_KW_MODULE
    TOK_KW_INTERFACE = 282,        // TOK_KW_INTERFACE
    TOK_KW_STRUCT = 283,           // TOK_KW_STRUCT
    TOK_KW_TASK = 284,             // TOK_KW_TASK
    TOK_TIME_NUMBER = 285,         // TOK_TIME_NUMBER
    TOK_TIME_UNIT = 286,           // TOK_TIME_UNIT
    TOK_VAR_TYPE = 287,            // TOK_VAR_TYPE
    TOK_HASH = 288,                // TOK_HASH
    TOK_VALUE = 289,               // TOK_VALUE
    TOK_BIN_NUM = 290,             // TOK_BIN_NUM
    TOK_BINARY_NUMBER = 291,       // TOK_BINARY_NUMBER
    TOK_REAL_NUM = 292,            // TOK_REAL_NUM
    TOK_REAL_NUMBER = 293,         // TOK_REAL_NUMBER
    TOK_IDENTIFIER = 294,          // TOK_IDENTIFIER
    TOK_DECIMAL_NUM = 295          // TOK_DECIMAL_NUM
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 41, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_TOK_BRACKET_O = 3,                     // TOK_BRACKET_O
        S_TOK_BRACKET_C = 4,                     // TOK_BRACKET_C
        S_TOK_COLON = 5,                         // TOK_COLON
        S_TOK_DOLLAR = 6,                        // TOK_DOLLAR
        S_TOK_KW_END = 7,                        // TOK_KW_END
        S_TOK_KW_COMMENT = 8,                    // TOK_KW_COMMENT
        S_TOK_COMMENT_TEXT = 9,                  // TOK_COMMENT_TEXT
        S_TOK_KW_DATE = 10,                      // TOK_KW_DATE
        S_TOK_DATE_TEXT = 11,                    // TOK_DATE_TEXT
        S_TOK_KW_ENDDEFINITIONS = 12,            // TOK_KW_ENDDEFINITIONS
        S_TOK_KW_SCOPE = 13,                     // TOK_KW_SCOPE
        S_TOK_KW_TIMESCALE = 14,                 // TOK_KW_TIMESCALE
        S_TOK_KW_UPSCOPE = 15,                   // TOK_KW_UPSCOPE
        S_TOK_KW_VAR = 16,                       // TOK_KW_VAR
        S_TOK_KW_VERSION = 17,                   // TOK_KW_VERSION
        S_TOK_VERSION_TEXT = 18,                 // TOK_VERSION_TEXT
        S_TOK_KW_DUMPALL = 19,                   // TOK_KW_DUMPALL
        S_TOK_KW_DUMPOFF = 20,                   // TOK_KW_DUMPOFF
        S_TOK_KW_DUMPON = 21,                    // TOK_KW_DUMPON
        S_TOK_KW_DUMPVARS = 22,                  // TOK_KW_DUMPVARS
        S_TOK_KW_BEGIN = 23,                     // TOK_KW_BEGIN
        S_TOK_KW_FORK = 24,                      // TOK_KW_FORK
        S_TOK_KW_FUNCTION = 25,                  // TOK_KW_FUNCTION
        S_TOK_KW_MODULE = 26,                    // TOK_KW_MODULE
        S_TOK_KW_INTERFACE = 27,                 // TOK_KW_INTERFACE
        S_TOK_KW_STRUCT = 28,                    // TOK_KW_STRUCT
        S_TOK_KW_TASK = 29,                      // TOK_KW_TASK
        S_TOK_TIME_NUMBER = 30,                  // TOK_TIME_NUMBER
        S_TOK_TIME_UNIT = 31,                    // TOK_TIME_UNIT
        S_TOK_VAR_TYPE = 32,                     // TOK_VAR_TYPE
        S_TOK_HASH = 33,                         // TOK_HASH
        S_TOK_VALUE = 34,                        // TOK_VALUE
        S_TOK_BIN_NUM = 35,                      // TOK_BIN_NUM
        S_TOK_BINARY_NUMBER = 36,                // TOK_BINARY_NUMBER
        S_TOK_REAL_NUM = 37,                     // TOK_REAL_NUM
        S_TOK_REAL_NUMBER = 38,                  // TOK_REAL_NUMBER
        S_TOK_IDENTIFIER = 39,                   // TOK_IDENTIFIER
        S_TOK_DECIMAL_NUM = 40,                  // TOK_DECIMAL_NUM
        S_YYACCEPT = 41,                         // $accept
        S_input = 42,                            // input
        S_declaration_commands = 43,             // declaration_commands
        S_simulation_commands = 44,              // simulation_commands
        S_declaration_command = 45,              // declaration_command
        S_simulation_command = 46,               // simulation_command
        S_scope_type = 47,                       // scope_type
        S_simulation_time = 48,                  // simulation_time
        S_value_changes = 49,                    // value_changes
        S_value_change = 50,                     // value_change
        S_scalar_value_change = 51,              // scalar_value_change
        S_vector_value_change = 52,              // vector_value_change
        S_reference = 53,                        // reference
        S_comment_text = 54,                     // comment_text
        S_version_text = 55,                     // version_text
        S_date_text = 56                         // date_text
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_TOK_VALUE: // TOK_VALUE
        value.move< VCDBit > (std::move (that.value));
        break;

      case symbol_kind::S_TOK_KW_BEGIN: // TOK_KW_BEGIN
      case symbol_kind::S_TOK_KW_FORK: // TOK_KW_FORK
      case symbol_kind::S_TOK_KW_FUNCTION: // TOK_KW_FUNCTION
      case symbol_kind::S_TOK_KW_MODULE: // TOK_KW_MODULE
      case symbol_kind::S_TOK_KW_INTERFACE: // TOK_KW_INTERFACE
      case symbol_kind::S_TOK_KW_STRUCT: // TOK_KW_STRUCT
      case symbol_kind::S_TOK_KW_TASK: // TOK_KW_TASK
      case symbol_kind::S_scope_type: // scope_type
        value.move< VCDScopeType > (std::move (that.value));
        break;

      case symbol_kind::S_reference: // reference
        value.move< VCDSignal* > (std::move (that.value));
        break;

      case symbol_kind::S_TOK_TIME_NUMBER: // TOK_TIME_NUMBER
        value.move< VCDTimeRes > (std::move (that.value));
        break;

      case symbol_kind::S_TOK_TIME_UNIT: // TOK_TIME_UNIT
        value.move< VCDTimeUnit > (std::move (that.value));
        break;

      case symbol_kind::S_TOK_VAR_TYPE: // TOK_VAR_TYPE
        value.move< VCDVarType > (std::move (that.value));
        break;

      case symbol_kind::S_TOK_DECIMAL_NUM: // TOK_DECIMAL_NUM
        value.move< size_t > (std::move (that.value));
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
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VCDBit&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VCDBit& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VCDScopeType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VCDScopeType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VCDSignal*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VCDSignal*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VCDTimeRes&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VCDTimeRes& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VCDTimeUnit&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VCDTimeUnit& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VCDVarType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VCDVarType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, size_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const size_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_TOK_VALUE: // TOK_VALUE
        value.template destroy< VCDBit > ();
        break;

      case symbol_kind::S_TOK_KW_BEGIN: // TOK_KW_BEGIN
      case symbol_kind::S_TOK_KW_FORK: // TOK_KW_FORK
      case symbol_kind::S_TOK_KW_FUNCTION: // TOK_KW_FUNCTION
      case symbol_kind::S_TOK_KW_MODULE: // TOK_KW_MODULE
      case symbol_kind::S_TOK_KW_INTERFACE: // TOK_KW_INTERFACE
      case symbol_kind::S_TOK_KW_STRUCT: // TOK_KW_STRUCT
      case symbol_kind::S_TOK_KW_TASK: // TOK_KW_TASK
      case symbol_kind::S_scope_type: // scope_type
        value.template destroy< VCDScopeType > ();
        break;

      case symbol_kind::S_reference: // reference
        value.template destroy< VCDSignal* > ();
        break;

      case symbol_kind::S_TOK_TIME_NUMBER: // TOK_TIME_NUMBER
        value.template destroy< VCDTimeRes > ();
        break;

      case symbol_kind::S_TOK_TIME_UNIT: // TOK_TIME_UNIT
        value.template destroy< VCDTimeUnit > ();
        break;

      case symbol_kind::S_TOK_VAR_TYPE: // TOK_VAR_TYPE
        value.template destroy< VCDVarType > ();
        break;

      case symbol_kind::S_TOK_DECIMAL_NUM: // TOK_DECIMAL_NUM
        value.template destroy< size_t > ();
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
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::END
                   || (token::YYerror <= tok && tok <= token::TOK_KW_COMMENT)
                   || tok == token::TOK_KW_DATE
                   || (token::TOK_KW_ENDDEFINITIONS <= tok && tok <= token::TOK_KW_VERSION)
                   || (token::TOK_KW_DUMPALL <= tok && tok <= token::TOK_KW_DUMPVARS)
                   || tok == token::TOK_HASH
                   || tok == token::TOK_BINARY_NUMBER
                   || tok == token::TOK_REAL_NUMBER);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, VCDBit v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const VCDBit& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOK_VALUE);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, VCDScopeType v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const VCDScopeType& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT ((token::TOK_KW_BEGIN <= tok && tok <= token::TOK_KW_TASK));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, VCDTimeRes v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const VCDTimeRes& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOK_TIME_NUMBER);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, VCDTimeUnit v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const VCDTimeUnit& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOK_TIME_UNIT);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, VCDVarType v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const VCDVarType& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOK_VAR_TYPE);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, size_t v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const size_t& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOK_DECIMAL_NUM);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOK_COMMENT_TEXT
                   || tok == token::TOK_DATE_TEXT
                   || tok == token::TOK_VERSION_TEXT
                   || tok == token::TOK_BIN_NUM
                   || tok == token::TOK_REAL_NUM
                   || tok == token::TOK_IDENTIFIER);
#endif
      }
    };

    /// Build a parser object.
    parser (VCDFileParser & driver_yyarg);
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_BRACKET_O (location_type l)
      {
        return symbol_type (token::TOK_BRACKET_O, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_BRACKET_O (const location_type& l)
      {
        return symbol_type (token::TOK_BRACKET_O, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_BRACKET_C (location_type l)
      {
        return symbol_type (token::TOK_BRACKET_C, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_BRACKET_C (const location_type& l)
      {
        return symbol_type (token::TOK_BRACKET_C, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_COLON (location_type l)
      {
        return symbol_type (token::TOK_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_COLON (const location_type& l)
      {
        return symbol_type (token::TOK_COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_DOLLAR (location_type l)
      {
        return symbol_type (token::TOK_DOLLAR, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_DOLLAR (const location_type& l)
      {
        return symbol_type (token::TOK_DOLLAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_END (location_type l)
      {
        return symbol_type (token::TOK_KW_END, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_END (const location_type& l)
      {
        return symbol_type (token::TOK_KW_END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_COMMENT (location_type l)
      {
        return symbol_type (token::TOK_KW_COMMENT, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_COMMENT (const location_type& l)
      {
        return symbol_type (token::TOK_KW_COMMENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_COMMENT_TEXT (std::string v, location_type l)
      {
        return symbol_type (token::TOK_COMMENT_TEXT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_COMMENT_TEXT (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_COMMENT_TEXT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_DATE (location_type l)
      {
        return symbol_type (token::TOK_KW_DATE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_DATE (const location_type& l)
      {
        return symbol_type (token::TOK_KW_DATE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_DATE_TEXT (std::string v, location_type l)
      {
        return symbol_type (token::TOK_DATE_TEXT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_DATE_TEXT (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_DATE_TEXT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_ENDDEFINITIONS (location_type l)
      {
        return symbol_type (token::TOK_KW_ENDDEFINITIONS, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_ENDDEFINITIONS (const location_type& l)
      {
        return symbol_type (token::TOK_KW_ENDDEFINITIONS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_SCOPE (location_type l)
      {
        return symbol_type (token::TOK_KW_SCOPE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_SCOPE (const location_type& l)
      {
        return symbol_type (token::TOK_KW_SCOPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_TIMESCALE (location_type l)
      {
        return symbol_type (token::TOK_KW_TIMESCALE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_TIMESCALE (const location_type& l)
      {
        return symbol_type (token::TOK_KW_TIMESCALE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_UPSCOPE (location_type l)
      {
        return symbol_type (token::TOK_KW_UPSCOPE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_UPSCOPE (const location_type& l)
      {
        return symbol_type (token::TOK_KW_UPSCOPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_VAR (location_type l)
      {
        return symbol_type (token::TOK_KW_VAR, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_VAR (const location_type& l)
      {
        return symbol_type (token::TOK_KW_VAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_VERSION (location_type l)
      {
        return symbol_type (token::TOK_KW_VERSION, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_VERSION (const location_type& l)
      {
        return symbol_type (token::TOK_KW_VERSION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_VERSION_TEXT (std::string v, location_type l)
      {
        return symbol_type (token::TOK_VERSION_TEXT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_VERSION_TEXT (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_VERSION_TEXT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_DUMPALL (location_type l)
      {
        return symbol_type (token::TOK_KW_DUMPALL, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_DUMPALL (const location_type& l)
      {
        return symbol_type (token::TOK_KW_DUMPALL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_DUMPOFF (location_type l)
      {
        return symbol_type (token::TOK_KW_DUMPOFF, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_DUMPOFF (const location_type& l)
      {
        return symbol_type (token::TOK_KW_DUMPOFF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_DUMPON (location_type l)
      {
        return symbol_type (token::TOK_KW_DUMPON, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_DUMPON (const location_type& l)
      {
        return symbol_type (token::TOK_KW_DUMPON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_DUMPVARS (location_type l)
      {
        return symbol_type (token::TOK_KW_DUMPVARS, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_DUMPVARS (const location_type& l)
      {
        return symbol_type (token::TOK_KW_DUMPVARS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_BEGIN (VCDScopeType v, location_type l)
      {
        return symbol_type (token::TOK_KW_BEGIN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_BEGIN (const VCDScopeType& v, const location_type& l)
      {
        return symbol_type (token::TOK_KW_BEGIN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_FORK (VCDScopeType v, location_type l)
      {
        return symbol_type (token::TOK_KW_FORK, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_FORK (const VCDScopeType& v, const location_type& l)
      {
        return symbol_type (token::TOK_KW_FORK, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_FUNCTION (VCDScopeType v, location_type l)
      {
        return symbol_type (token::TOK_KW_FUNCTION, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_FUNCTION (const VCDScopeType& v, const location_type& l)
      {
        return symbol_type (token::TOK_KW_FUNCTION, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_MODULE (VCDScopeType v, location_type l)
      {
        return symbol_type (token::TOK_KW_MODULE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_MODULE (const VCDScopeType& v, const location_type& l)
      {
        return symbol_type (token::TOK_KW_MODULE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_INTERFACE (VCDScopeType v, location_type l)
      {
        return symbol_type (token::TOK_KW_INTERFACE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_INTERFACE (const VCDScopeType& v, const location_type& l)
      {
        return symbol_type (token::TOK_KW_INTERFACE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_STRUCT (VCDScopeType v, location_type l)
      {
        return symbol_type (token::TOK_KW_STRUCT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_STRUCT (const VCDScopeType& v, const location_type& l)
      {
        return symbol_type (token::TOK_KW_STRUCT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_KW_TASK (VCDScopeType v, location_type l)
      {
        return symbol_type (token::TOK_KW_TASK, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_KW_TASK (const VCDScopeType& v, const location_type& l)
      {
        return symbol_type (token::TOK_KW_TASK, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_TIME_NUMBER (VCDTimeRes v, location_type l)
      {
        return symbol_type (token::TOK_TIME_NUMBER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_TIME_NUMBER (const VCDTimeRes& v, const location_type& l)
      {
        return symbol_type (token::TOK_TIME_NUMBER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_TIME_UNIT (VCDTimeUnit v, location_type l)
      {
        return symbol_type (token::TOK_TIME_UNIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_TIME_UNIT (const VCDTimeUnit& v, const location_type& l)
      {
        return symbol_type (token::TOK_TIME_UNIT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_VAR_TYPE (VCDVarType v, location_type l)
      {
        return symbol_type (token::TOK_VAR_TYPE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_VAR_TYPE (const VCDVarType& v, const location_type& l)
      {
        return symbol_type (token::TOK_VAR_TYPE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_HASH (location_type l)
      {
        return symbol_type (token::TOK_HASH, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_HASH (const location_type& l)
      {
        return symbol_type (token::TOK_HASH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_VALUE (VCDBit v, location_type l)
      {
        return symbol_type (token::TOK_VALUE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_VALUE (const VCDBit& v, const location_type& l)
      {
        return symbol_type (token::TOK_VALUE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_BIN_NUM (std::string v, location_type l)
      {
        return symbol_type (token::TOK_BIN_NUM, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_BIN_NUM (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_BIN_NUM, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_BINARY_NUMBER (location_type l)
      {
        return symbol_type (token::TOK_BINARY_NUMBER, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_BINARY_NUMBER (const location_type& l)
      {
        return symbol_type (token::TOK_BINARY_NUMBER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_REAL_NUM (std::string v, location_type l)
      {
        return symbol_type (token::TOK_REAL_NUM, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_REAL_NUM (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_REAL_NUM, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_REAL_NUMBER (location_type l)
      {
        return symbol_type (token::TOK_REAL_NUMBER, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_REAL_NUMBER (const location_type& l)
      {
        return symbol_type (token::TOK_REAL_NUMBER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_IDENTIFIER (std::string v, location_type l)
      {
        return symbol_type (token::TOK_IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_IDENTIFIER (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_DECIMAL_NUM (size_t v, location_type l)
      {
        return symbol_type (token::TOK_DECIMAL_NUM, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_DECIMAL_NUM (const size_t& v, const location_type& l)
      {
        return symbol_type (token::TOK_DECIMAL_NUM, v, l);
      }
#endif


    class context
    {
    public:
      context (const parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef signed char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const signed char yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const signed char yytable_[];

    static const signed char yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 103,     ///< Last index in yytable_.
      yynnts_ = 16,  ///< Number of nonterminal symbols.
      yyfinal_ = 54 ///< Termination state number.
    };


    // User arguments.
    VCDFileParser & driver;

  };

  inline
  parser::symbol_kind_type
  parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
    };
    // Last valid token kind.
    const int code_max = 295;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_TOK_VALUE: // TOK_VALUE
        value.copy< VCDBit > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_KW_BEGIN: // TOK_KW_BEGIN
      case symbol_kind::S_TOK_KW_FORK: // TOK_KW_FORK
      case symbol_kind::S_TOK_KW_FUNCTION: // TOK_KW_FUNCTION
      case symbol_kind::S_TOK_KW_MODULE: // TOK_KW_MODULE
      case symbol_kind::S_TOK_KW_INTERFACE: // TOK_KW_INTERFACE
      case symbol_kind::S_TOK_KW_STRUCT: // TOK_KW_STRUCT
      case symbol_kind::S_TOK_KW_TASK: // TOK_KW_TASK
      case symbol_kind::S_scope_type: // scope_type
        value.copy< VCDScopeType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_reference: // reference
        value.copy< VCDSignal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_TIME_NUMBER: // TOK_TIME_NUMBER
        value.copy< VCDTimeRes > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_TIME_UNIT: // TOK_TIME_UNIT
        value.copy< VCDTimeUnit > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_VAR_TYPE: // TOK_VAR_TYPE
        value.copy< VCDVarType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_DECIMAL_NUM: // TOK_DECIMAL_NUM
        value.copy< size_t > (YY_MOVE (that.value));
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
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_TOK_VALUE: // TOK_VALUE
        value.move< VCDBit > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOK_KW_BEGIN: // TOK_KW_BEGIN
      case symbol_kind::S_TOK_KW_FORK: // TOK_KW_FORK
      case symbol_kind::S_TOK_KW_FUNCTION: // TOK_KW_FUNCTION
      case symbol_kind::S_TOK_KW_MODULE: // TOK_KW_MODULE
      case symbol_kind::S_TOK_KW_INTERFACE: // TOK_KW_INTERFACE
      case symbol_kind::S_TOK_KW_STRUCT: // TOK_KW_STRUCT
      case symbol_kind::S_TOK_KW_TASK: // TOK_KW_TASK
      case symbol_kind::S_scope_type: // scope_type
        value.move< VCDScopeType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_reference: // reference
        value.move< VCDSignal* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOK_TIME_NUMBER: // TOK_TIME_NUMBER
        value.move< VCDTimeRes > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOK_TIME_UNIT: // TOK_TIME_UNIT
        value.move< VCDTimeUnit > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOK_VAR_TYPE: // TOK_VAR_TYPE
        value.move< VCDVarType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOK_DECIMAL_NUM: // TOK_DECIMAL_NUM
        value.move< size_t > (YY_MOVE (s.value));
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
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


} // VCDParser
#line 2362 "../../../../include/traceReader/vcdTraceReader//VCDParser.hpp"




#endif // !YY_VCDPARSER_INCLUDE_TRACEREADER_VCDTRACEREADER_VCDPARSER_HPP_INCLUDED
