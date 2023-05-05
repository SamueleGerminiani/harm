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
    | LPAREN boolean RPAREN
    ;

booleanAtom
    : booleanConstant
    | booleanVariable
    ;

booleanConstant
    : BOOLEAN
    ;

booleanVariable
    : '<' variable ',bool>' 
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
    | LPAREN logic RPAREN
    ;

bitSelect: '[' NUMERIC (':' NUMERIC)? ']';

logicAtom
    : logicConstant
    | logicVariable
    ;

logicConstant
    : VERILOG_BINARY
    | GCC_BINARY
    | NUMERIC CONST_SUFFIX?
    | HEX
    ;

logicVariable
    : '<' variable ',logic(' SIGN ',' NUMERIC ')>' 
    ;

SIGN
    :
    'u'
    | 's';

CONST_SUFFIX
    :
    'll'
    | 'ull';


// ------------------------------------------ NUMERIC
numeric
    : numeric artop=(TIMES|DIV) numeric
    | numeric artop=(PLUS|MINUS) numeric
    | numericAtom
    | logic
    | LPAREN numeric RPAREN
    ;

numericAtom
    : numericConstant
    | numericVariable
    ;

numericConstant
    :  NUMERIC
    ;

numericVariable
    : '<' variable ',numeric(' NUMERIC ')>' 
    ;




variable
    : VARIABLE
    ;

LGPAREN
    : '{'
    ;

RGPAREN
    : '}'
    ;
LCPAREN
    : '['
    ;

RCPAREN
    : ']'
    ;

LPAREN
    : '('
    ;

RPAREN
    : ')'
    ;


//==== Token VARIABLE ==========================================================
VARIABLE
   : ('::')? VALID_ID_START VALID_ID_CHAR* 
   ;



fragment VALID_ID_START
    : 'P' (('a' .. 'z')| ('A' .. 'Z') | ('_'))
	| (('a' .. 'z')| ('A' .. 'O')| ('Q' .. 'W')| ('Y' .. 'Z') | ('_')) ;

fragment VALID_ID_CHAR
    : ('a' .. 'z') 
    | ('A' .. 'Z')
    | ('0' .. '9')
    | ('.')
    | ('_')
    | ('::')
    ;
//------------------------------------------------------------------------------


//==== Token constant ==========================================================
    NUMERIC
    : '-'? ('0' .. '9') + ('.' ('0' .. '9') +)?
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

    BOOLEAN
    : '@true' 
    | '@false'
    ;


//------------------------------------------------------------------------------


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
