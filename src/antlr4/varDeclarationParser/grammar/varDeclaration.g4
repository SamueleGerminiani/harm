grammar varDeclaration;

file : varDec EOF;

varDec : vartype ('[' NUMERIC ':' NUMERIC ']')? name;

name : NAME;

vartype : VARTYPE;

VARTYPE:
  'bool' 
| 'unsigned char' 
| 'unsigned short' 
| 'unsigned int' 
| 'unsigned long int' 
| 'char' 
| 'short' 
| 'int' 
| 'long int' 
| 'float' 
| 'double' 
|    'byte'
|    'shortint'
|    'longint'
|    'byte unsigned'
|    'shortint unsigned'
|    'longint unsigned'
|    'time'
|    'shortreal'
|    'real'
|    'reg'
|    'wire'
|    'logic'
    'bit'
; 

NAME
   : VALID_ID_START VALID_ID_CHAR*
   ;

fragment VALID_ID_START
    : ('a' .. 'z')
    | ('A' .. 'Z')
    | ('_')
    ;

fragment VALID_ID_CHAR
    : VALID_ID_START
    | ('0' .. '9')
    | ('.')
    ;

    NUMERIC
    : ('0' .. '9') + 
    ;

// Ignore: \r, \n, \t
WS : [ \t\r\n] -> skip;
