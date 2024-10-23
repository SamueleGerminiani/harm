grammar proposition;

startBoolean : boolean EOF;
startInt : numeric EOF;
startFloat : numeric EOF;

// ------------------------------------------ BOOLEAN
boolean
    : NOT boolean
    | numeric relop numeric
    | numeric EQ numeric
    | numeric NEQ numeric
    | boolean EQ boolean
    | boolean NEQ boolean
    | boolean booleanop=AND boolean
    | boolean booleanop=OR boolean
    | booleanAtom
    | numeric
    | LROUND boolean RROUND
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
    | numeric range 
    | numeric artop=(TIMES|DIV) numeric
    | numeric artop=(PLUS|MINUS) numeric
    | numeric logop=LSHIFT numeric
    | numeric logop=RSHIFT numeric
    | numeric logop=BAND numeric
    | numeric logop=BXOR numeric
    | numeric logop=BOR numeric
    | intAtom
    | floatAtom
    | LROUND numeric RROUND
    ;

range: LSQUARED (SINTEGER | UINTEGER) (COL (SINTEGER | UINTEGER))? RSQUARED;

intAtom
    : int_constant
    | INT_VARIABLE
    ;

int_constant
    : GCC_BINARY
    | SINTEGER CONST_SUFFIX?
    | UINTEGER CONST_SUFFIX?
    | UINTEGER? VERILOG_BINARY
    | HEX
    ;

INT_VARIABLE
    : START_VAR VARIABLE ',int' END_VAR
    ;

CONST_SUFFIX
    : 'll'
    | 'ull'
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


   VERILOG_BINARY: SINGLE_QUOTE FVL
   ;

   FVL:('b'|'B') ('0'|'1'|'z'|'x')+;

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
