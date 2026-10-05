grammar proposition;

startBoolean : (boolean | booleanTernary) EOF;
startInt : (numeric | numericTernary) EOF;
startLogic : (numeric | numericTernary) EOF;
startFloat : (numeric | numericTernary) EOF;
startString : string EOF;

// ------------------------------------------ TERNARY (SystemVerilog precedence: lowest)
// A ternary is allowed at the top of an expression, as a branch of a ternary, or in parentheses
// (as an operand of any other operator it must be parenthesized, as in SystemVerilog)
booleanTernary
    : boolean QUESTION (boolean | booleanTernary) COL (boolean | booleanTernary)
    ;
numericTernary
    : boolean QUESTION (numeric | numericTernary) COL (numeric | numericTernary)
    ;

// ------------------------------------------ BOOLEAN
boolean
    : NOT boolean
    | nonTemporalFunction
    | numeric INSIDE LCURLY ((sm_constant | sm_range) ',')* (sm_constant | sm_range) RCURLY
    | numeric relop numeric
    | numeric EQ numeric
    | numeric NEQ numeric
    | numeric CASE_EQ numeric
    | numeric CASE_NEQ numeric
    | string relop string
    | string EQ string
    | string NEQ string
    | boolean EQ boolean
    | boolean NEQ boolean
    | boolean booleanop=AND boolean
    | boolean booleanop=OR boolean
    | booleanAtom
    | numeric
    | LROUND boolean RROUND
    | LROUND booleanTernary RROUND
    ;


booleanAtom
    : BOOLEAN_CONSTANT
    | BOOLEAN_VARIABLE
    ;

BOOLEAN_CONSTANT
    : '@true' 
    | '@false'
    ;


BOOLEAN_VARIABLE
    : START_VAR VARIABLE ',bool' END_VAR 
    ;

// ------------------------------------------ NUMERIC
numeric
    : NEG numeric 
    | nonTemporalFunction
    | numeric range 
    | numeric artop=(TIMES|DIV) numeric
    | numeric artop=(PLUS|MINUS) numeric
    | numeric logop=LSHIFT numeric
    | numeric logop=RSHIFT numeric
    | numeric logop=BAND numeric
    | numeric logop=BXOR numeric
    | numeric logop=BOR numeric
    | intAtom
    | logicAtom
    | floatAtom
    | concatenation
    | LROUND numeric RROUND
    | LROUND numericTernary RROUND
    ;

// at least two items (or a replication), so that '{a}' stays a SERE in temporal formulas
concatenation
    : LCURLY concatItem (',' concatItem)+ RCURLY
    | LCURLY UINTEGER LCURLY concatItem (',' concatItem)* RCURLY RCURLY
    ;
concatItem
    : numeric
    | booleanAtom
    ;

range: LSQUARED (SINTEGER | UINTEGER) (COL (SINTEGER | UINTEGER))? RSQUARED;

sm_range: LSQUARED (numeric | min_dollar) COL (numeric | max_dollar) RSQUARED;
min_dollar: DOLLAR;
max_dollar: DOLLAR;

sm_constant: numeric; 

intAtom
    : int_constant
    | INT_VARIABLE
    ;

int_constant
    : GCC_BINARY
    | SINTEGER CONST_SUFFIX?
    | UINTEGER CONST_SUFFIX?
    | HEX
    ;

INT_VARIABLE
    : START_VAR VARIABLE ',int' END_VAR
    ;

CONST_SUFFIX
    : 'll'
    | 'ull'
    ;

logicAtom
    : logic_constant
    | int_constant
    | LOGIC_VARIABLE
    ;


logic_constant
    : UINTEGER? VERILOG_BASED
    | FILL_LITERAL
    ;


LOGIC_VARIABLE
    : START_VAR VARIABLE ',logic' END_VAR
    ;

floatAtom
    : FLOAT_CONSTANT
    | FLOAT_VARIABLE
    ;

FLOAT_CONSTANT
    :  FLOAT
    ;

FLOAT_VARIABLE
    : START_VAR VARIABLE ',float' END_VAR 
    ;


string :
      string PLUS string
    | string SUBSTR LROUND (UINTEGER ',' UINTEGER | UINTEGER)? RROUND
    | stringAtom
    | LROUND string RROUND
    ;


stringAtom
    : STRING_CONSTANT
    | STRING_VARIABLE
    ;

SUBSTR: '.substr';

//match any character inside double quotes
STRING_CONSTANT
    :  '"' ~('"')* '"'
    ;

STRING_VARIABLE
    : START_VAR VARIABLE ',string' END_VAR 
    ;


LCURLY
    : '{'
    ;

RCURLY
    : '}'
    ;
LSQUARED
    : '['
    ;

RSQUARED
    : ']'
    ;

LROUND
    : '('
    ;

RROUND
    : ')'
    ;

INSIDE
    : 'inside'
    ;


FUNCTION
: '$stable'
| '$past'
| '$rose'
| '$fell'
;

nonTemporalFunction: FUNCTION LROUND pfunc_arg (',' pfunc_arg)* RROUND;
pfunc_arg: numeric |  boolean;

//==== Token VARIABLE ==========================================================
fragment VARIABLE
   : VALID_ID_START VALID_ID_CHAR* 
   ;

fragment VALID_ID_START
    : (('a' .. 'z')| ('A' .. 'Z') | ('_'));

fragment VALID_ID_CHAR
    : ('a' .. 'z') 
    | ('A' .. 'Z')
    | ('0' .. '9')
    | ('.')
    | ('_')
    | (':')
    | (']')
    | ('[')
    | ('(')
    | (')')
    | ('{')
    | ('}')
    ;


//==== Token constant ==========================================================
    SINTEGER
    : '-' ('0' .. '9')+
    ;

    UINTEGER
    : ('0' .. '9')+
    ;

    FLOAT
    : '-'? ('0' .. '9')+ '.' ('0' .. '9')+
    | '-'? ('0' .. '9')+ '.f'
    ;

    

    GCC_BINARY
    : '0b' ('0' .. '1')+
    ;
    
    HEX
    : '0x' (('0' .. '9') | ('a' .. 'f'))+ 
    | '0x' (('0' .. '9') | ('A' .. 'F'))+ 
    ;


   // [size]'[s]<base><digits>: the size is a separate UINTEGER token (see logic_constant)
   VERILOG_BASED
   : SINGLE_QUOTE [sS]? ( [bB] [01xXzZ?_]+
                        | [oO] [0-7xXzZ?_]+
                        | [dD] ( [0-9_]+ | [xXzZ?] '_'* )
                        | [hH] [0-9a-fA-FxXzZ?_]+ )
   ;

   // '0 '1 'x 'z: every bit set to the digit, width taken from the context
   FILL_LITERAL: SINGLE_QUOTE [01xXzZ];

   SINGLE_QUOTE: '\'';
//------------------------------------------------------------------------------

fragment START_VAR: '«';
fragment END_VAR: '»';


//==== Arithmetic Operators ====================================================
PLUS
    : '+'
    ;

MINUS
    : '-'
    ;

TIMES
    : '*'
    ;

DIV
    : '/'
    ;
//------------------------------------------------------------------------------

//==== Relational Operators ====================================================
relop
    : GT
    | GE
    | LT
    | LE
    ;

GT
    : '>'
    ;

GE
    : '>='
    ;

LT
    : '<'
    ;

LE
    : '<='
    ;

EQ
    : '=='
    ;

NEQ
    : '!='
    ;

CASE_EQ
    : '==='
    ;

CASE_NEQ
    : '!=='
    ;

QUESTION
    : '?'
    ;
//------------------------------------------------------------------------------


//==== Integer Operators =========================================================

BAND
    : '&'
    ;

BOR
    : '|'
    ;

BXOR
    : '^'
    ;

NEG
    : '~'
    ;

LSHIFT: '<<';

RSHIFT: '>>';

//------------------------------------------------------------------------------


//==== Boolean Operators ========================================================

AND
    : '&&'
    ;

OR
    : '||'
    ;

NOT
    : '!'
    ;
//------------------------------------------------------------------------------

COL
    : ':'
    ;

DCOL
    : '::'
    ;

DOLLAR
    : '$'
    ;

RANGE: '><';

cls_op :  RANGE
    | GT
    | GE
    | LT
    | LE
    | EQ
    ;

CLS_TYPE: 'S' | 'K' ;

// Ignore: \r, \n, \t
WS : [ \t\r\n] -> skip;
