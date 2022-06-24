grammar limits;

file : parameter EOF;

parameter
: atom ',' parameter
| atom
;

atom
: dep
| width
| all
| offset
| effort
| strategy
| negated
;

dep: NUMERIC 'D';
width: NUMERIC 'W';
all: NUMERIC 'A';
offset: NOT? 'O' ;
negated: NOT? 'N' ;
effort: NUMERIC 'E';
strategy: SEQ | RAN;
SEQ:'S';
RAN:'R';

NOT: '!';

//==== Token constant ==========================================================
NUMERIC
: '-'? ('0' .. '9') + ('.' ('0' .. '9') +)?
;




// Ignore: \r, \n, \t
WS : [ \t\r\n] -> skip;
