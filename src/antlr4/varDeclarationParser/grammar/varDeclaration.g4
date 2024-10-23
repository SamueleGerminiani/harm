grammar varDeclaration;
import proposition;

file : varDec EOF;

varDec : VARTYPE range? Name ;

Name : START_VAR VARIABLE END_VAR;


VARTYPE:
//C types
  'bool' 
| 'char' 
| 'short' 
| 'int' 
| 'long int' 
| 'unsigned char' 
| 'unsigned short' 
| 'unsigned int' 
| 'unsigned long int' 
| 'size_t' 
| 'int64_t' 
| 'int32_t' 
| 'uint64_t' 
| 'uint32_t' 
| 'float' 
| 'double' 


//SV Type
//2-value
| 'shortint'
| 'longint'
| 'byte'
| 'bit'

| 'shortint unsigned'
| 'int unsigned'
| 'longint unsigned'
| 'byte unsigned'
| 'bit signed'

//4-value
| 'reg'
| 'logic'
| 'integer'
| 'wire'
| 'time'

| 'reg signed'
| 'logic signed'
| 'integer unsigned'
| 'wire signed'
| 'time signed'


//double
| 'shortreal'
| 'real'
| 'realtime'

; 


// Ignore: \r, \n, \t
WS : [ \t\r\n] -> skip;
