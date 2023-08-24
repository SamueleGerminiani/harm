grammar proposition;

file : boolean EOF;

// ------------------------------------------ BOOLEAN
boolean
    : NOT boolean
    | logic relop logic
    | numeric relop numeric
    | logic EQ logic
    | numeric EQ numeric
    | boolean EQ boolean
    | logic NEQ logic
    | numeric NEQ numeric
    | boolean NEQ boolean
    | boolean booleanop=AND boolean
    | boolean booleanop=OR boolean
    | booleanAtom
    | logic
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

// ------------------------------------------ LOGIC
logic
    : NEG logic 
    | logic bitSelect 
    | logic artop=(TIMES|DIV) logic
    | logic artop=(PLUS|MINUS) logic
    | logic logop=LSHIFT logic
    | logic logop=RSHIFT logic
    | logic logop=BAND logic
    | logic logop=BXOR logic
    | logic logop=BOR logic
    | logicAtom
    | LROUND logic RROUND
    ;

bitSelect: '[' UINTEGER (':' UINTEGER)? ']';

logicAtom
    : logic_constant
    | LOGIC_VARIABLE
    ;

logic_constant
    : VERILOG_BINARY
    | GCC_BINARY
    | SINTEGER CONST_SUFFIX?
    | UINTEGER CONST_SUFFIX?
    | HEX
    ;

LOGIC_VARIABLE
    : START_VAR VARIABLE ',logic' END_VAR
    ;

CONST_SUFFIX
    : 'll'
    | 'ull'
    ;


// ------------------------------------------ NUMERIC
numeric
    : numeric artop=(TIMES|DIV) numeric
    | numeric artop=(PLUS|MINUS) numeric
    | numericAtom
    | logic
    | LROUND numeric RROUND
    ;

numericAtom
    : NUMERIC_CONSTANT
    | NUMERIC_VARIABLE
    ;

NUMERIC_CONSTANT
    :  FLOAT
    ;

NUMERIC_VARIABLE
    : START_VAR VARIABLE ',numeric' END_VAR 
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

    
    VERILOG_BINARY
    : ('\'')('b')('0' .. '1')+
    ;

    GCC_BINARY
    : '0b' ('0' .. '1')+
    ;
    
    HEX
    : '0x' (('0' .. '9') | ('a' .. 'f'))+ 
    | '0x' (('0' .. '9') | ('A' .. 'F'))+ 
    ;


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


//==== Logic Operators =========================================================

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

// Ignore: \r, \n, \t
WS : [ \t\r\n] -> skip;
