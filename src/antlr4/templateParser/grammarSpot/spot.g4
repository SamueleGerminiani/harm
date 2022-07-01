grammar spot;
import proposition;

file : ALWAYS formula EOF
| ALWAYS LPAREN formula RPAREN EOF;



formula : tformula IMPL tformula
	    | tformula IMPL2 tformula
	    | LGPAREN sere RGPAREN LCPAREN  RCPAREN IMPL tformula
	    | LGPAREN sere RGPAREN LCPAREN  RCPAREN IMPL2 tformula
	    | LGPAREN sere RGPAREN BIND1 tformula
	    | LGPAREN sere RGPAREN BIND2 tformula
	    | LGPAREN sere RGPAREN SEREIMPL1 tformula
	    | LGPAREN sere RGPAREN SEREIMPL2 tformula
	;

sere : boolean | (NOT)? placeholder | DT_AND 
	 | LPAREN sere RPAREN
	 | LGPAREN sere RGPAREN
	 | sere BOR sere
	 | sere BAND sere
	 | sere AND sere
	 | sere SCOL sere
	 | sere COL sere
	 | sere LCPAREN TIMES NUMERIC? DOTS? NUMERIC? RCPAREN
	 | sere LCPAREN PLUS RCPAREN
	 | sere LCPAREN ASS NUMERIC DOTS? NUMERIC? RCPAREN
	 | sere LCPAREN IMPL NUMERIC DOTS? NUMERIC? RCPAREN
	 | DELAY LCPAREN? NUMERIC DOTS? NUMERIC? RCPAREN? sere
	 | sere DELAY LCPAREN? NUMERIC? DOTS? NUMERIC? RCPAREN? sere
     | dt_next | dt_next_and | dt_NCReps
	 ;

tformula: boolean | placeholder | DT_AND
	| LPAREN tformula RPAREN 
	| NOT tformula 
	| tformula AND tformula 
	| tformula OR tformula 
	| tformula XOR tformula 
	| tformula UNTIL tformula 
	| tformula RELEASE tformula
	| NEXT LCPAREN NUMERIC RCPAREN tformula 
	| NEXT tformula 
	| LGPAREN sere RGPAREN
	;

placeholder: 'P' NUMERIC ;

DT_AND
    : '..&&..'
    ;

dt_next
    : '..##' NUMERIC '..'
    ;

dt_next_and
    : '..#' NUMERIC '&' '..'
    ;
dt_NCReps
    : '..[->' NUMERIC ']' SEP '..';

SEP:'@:' | '@;';

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

IMPL2
    : '=>'
    ;

IFF
    : '<->'
    ;

XOR
    : 'xor'
    ;
	
BIND1
    : '[]->'
    ;

BIND2
    : '[]=>'
    ;
SEREIMPL1
    : '|->'
    ;

SEREIMPL2
    : '|=>'
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

FIRST_MATCH
	:
'first_match'
	;
	
