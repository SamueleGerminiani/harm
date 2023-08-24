grammar varDeclaration;
import proposition;

file : varDec EOF;

varDec : VARTYPE ('[' LOGIC_CONSTANT ':' LOGIC_CONSTANT ']')? Name ;

Name : START_VAR VARIABLE END_VAR;


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


// Ignore: \r, \n, \t
WS : [ \t\r\n] -> skip;
