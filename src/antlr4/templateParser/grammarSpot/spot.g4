grammar spot;
import proposition;

file : ALWAYS LROUND formula RROUND EOF 
| ALWAYS formula EOF
;



formula : tformula IMPL tformula
	    | tformula IMPLO tformula
	    | LCURLY sere RCURLY SEREIMPL tformula
	    | LCURLY sere RCURLY SEREIMPLO tformula
	;

sere : boolean | (NOT)? PLACEHOLDER | (NOT)? FUNCTION LROUND nonTemporalExp RROUND
     | DT_AND 
	 | LROUND sere RROUND
	 | LCURLY sere RCURLY
	 | sere BOR sere
	 | sere BAND sere
	 | sere AND sere
	 | sere SCOL sere
	 | sere COL sere
	 | sere LSQUARED TIMES UINTEGER? DOTS? UINTEGER? RSQUARED
	 | sere LSQUARED PLUS RSQUARED
	 | sere LSQUARED ASS UINTEGER DOTS? UINTEGER? RSQUARED
	 | sere LSQUARED IMPL UINTEGER DOTS? UINTEGER? RSQUARED
	 | sere DELAY LSQUARED? UINTEGER? DOTS? UINTEGER? RSQUARED? sere
     | DT_NEXT | DT_NEXT_AND | DT_NCREPS
	 ;

tformula: boolean | PLACEHOLDER | DT_AND
	| LROUND tformula RROUND 
	| NOT tformula 
	| tformula AND tformula 
	| tformula OR tformula 
	| tformula XOR tformula 
	| tformula UNTIL tformula 
	| tformula RELEASE tformula
	| NEXT LSQUARED UINTEGER RSQUARED tformula 
	| NEXT tformula 
	| LCURLY sere RCURLY
	;

nonTemporalExp:
PLACEHOLDER | boolean;

PLACEHOLDER: 'P' UINTEGER ;

DT_AND
    : '..&&..'
    ;

DT_NEXT
    : '..##' UINTEGER '..'
    ;

DT_NEXT_AND
    : '..#' UINTEGER '&' '..'
    ;

DT_NCREPS
    : '..[->' UINTEGER ']' SEP '..';

SEP:'@:' | '@;';

FUNCTION
: '$stable';


EVENTUALLY
    : 'F'
    ;
ALWAYS
    : 'G'
    ;
NEXT
    : 'X'
    ;
UNTIL
    : 'U'
    ;

RELEASE
    : 'R'
    ;


DOTS
    : '..'
    ;
IMPL
    : '->'
    ;

IMPLO
    : '=>'
    ;

IFF
    : '<->'
    ;

XOR
    : 'xor'
    ;
	
SEREIMPL
    : '|->'
    | '[]->'
    ;

SEREIMPLO
    : '|=>'
    | '[]=>'
    ;

ASS
    : '='
    ;

DELAY
    : '##'
    ;

SCOL
    : ';'
    ;

COL
    : ':'
    ;

