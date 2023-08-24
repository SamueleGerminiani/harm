grammar spot;
import proposition;

file : ALWAYS LPAREN formula RPAREN EOF 
| ALWAYS formula EOF
;



formula : tformula IMPL tformula
	    | tformula IMPL2 tformula
	    | LGPAREN sere RGPAREN LCPAREN  RCPAREN IMPL tformula
	    | LGPAREN sere RGPAREN LCPAREN  RCPAREN IMPL2 tformula
	    | LGPAREN sere RGPAREN BIND1 tformula
	    | LGPAREN sere RGPAREN BIND2 tformula
	    | LGPAREN sere RGPAREN SEREIMPL1 tformula
	    | LGPAREN sere RGPAREN SEREIMPL2 tformula
	;

sere : boolean | (NOT)? PLACEHOLDER | (NOT)? FUNCTION LPAREN nonTemporalExp RPAREN
     | DT_AND 
	 | LPAREN sere RPAREN
	 | LGPAREN sere RGPAREN
	 | sere BOR sere
	 | sere BAND sere
	 | sere AND sere
	 | sere SCOL sere
	 | sere COL sere
	 | sere LCPAREN TIMES LOGIC_CONSTANT? DOTS? LOGIC_CONSTANT? RCPAREN
	 | sere LCPAREN PLUS RCPAREN
	 | sere LCPAREN ASS LOGIC_CONSTANT DOTS? LOGIC_CONSTANT? RCPAREN
	 | sere LCPAREN IMPL LOGIC_CONSTANT DOTS? LOGIC_CONSTANT? RCPAREN
	 | sere DELAY LCPAREN? LOGIC_CONSTANT? DOTS? LOGIC_CONSTANT? RCPAREN? sere
     | DT_NEXT | DT_NEXT_AND | DT_NCREPS
	 ;

tformula: boolean | PLACEHOLDER | DT_AND
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

nonTemporalExp:
PLACEHOLDER | boolean;

PLACEHOLDER: 'P' NUMERIC ;

DT_AND
    : '..&&..'
    ;

DT_NEXT
    : '..##' NUMERIC '..'
    ;

DT_NEXT_AND
    : '..#' NUMERIC '&' '..'
    ;

DT_NCREPS
    : '..[->' NUMERIC ']' SEP '..';

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
	
