grammar temporalSVA;
import proposition;

file : ALWAYS formula EOF
| ALWAYS LPAREN formula RPAREN EOF;



formula : tformula IMPL tformula
	    | tformula IMPL2 tformula
	    | LGPAREN sere RGPAREN LCPAREN  RCPAREN IMPL tformula
	    | LGPAREN sere RGPAREN LCPAREN  RCPAREN IMPL2 tformula
	    | LGPAREN sere RGPAREN BIND1 tformula
	    | LGPAREN sere RGPAREN BIND2 tformula
	;

sere : boolean | (NOT)? placeholder | BDT_AND 
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
     | bdt_next | bdt_next_and | bdt_NCReps
	 ;

tformula: boolean | placeholder | BDT_AND
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

BDT_AND
    : '..&&..'
    ;

bdt_next
    : '..##' NUMERIC '..'
    ;

bdt_next_and
    : '..#' NUMERIC '&' '..'
    ;
bdt_NCReps
    : '..[->' NUMERIC ']' SEP '..';

SEP:'@:' | '@;';

EVENTUALLY
    : 'eventually'
    ;
ALWAYS
    : 'always'
    ;
NEXT
    : 'nexttime'
    ;
UNTIL
    : 'until'
    ;

RELEASE
    : 'release'
    ;


DOTS
    : '..'
    ;
IMPL
    : '|->'
    ;

IMPL2
    : '|=>'
    ;

IFF
    : 'iff'
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
	
