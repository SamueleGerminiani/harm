grammar metric;

file : numeric EOF;


// ------------------------------------------ LOGIC
logic
    : NEG logic 
    | logic logop=LSHIFT logic
    | logic logop=RSHIFT logic
    | logic logop=BAND logic
    | logic logop=BXOR logic
    | logic logop=BOR logic
    | logicAtom
    | LPAREN logic RPAREN
    ;

logicAtom
    : logicConstant
    | logicVariable
    ;

logicConstant
    : VERILOG_BINARY
    | GCC_BINARY
    | NUMERIC
    | HEX
    ;

logicVariable
    : '<' variable ',logic(' SIGN ',' NUMERIC ')>' 
    ;

SIGN
    :
    'u'
    | 's';


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
   : VALID_ID_START VALID_ID_CHAR* INDEX?
   ;

INDEX:
'[' NUMERIC ':' NUMERIC ']'
| '[' NUMERIC ']';

fragment VALID_ID_START
    : ('a' .. 'z')| ('A' .. 'Z') | ('_')
    ;

fragment VALID_ID_CHAR
    : VALID_ID_START
    | ('0' .. '9')
    | ('.')
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
