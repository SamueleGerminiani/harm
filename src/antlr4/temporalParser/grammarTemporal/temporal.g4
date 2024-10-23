grammar temporal;

@parser::header {
#include <string>
// Forward declaration
bool isUnary(const std::string& token);
bool isSharedOperator(const std::string& token);
bool canUseSharedOperator(const std::string& unaryOp, const std::string& sharedOp);
bool canTakeThisNot(const std::string& unaryOp, const std::string& ph);
}

@parser::members {
// Definition
bool isUnary(const std::string& token){
return token=="X" || token=="nexttime" || token=="F" || token=="eventually" || token=="!" || token=="not";
}
bool isSharedOperator(const std::string& token){
return token=="and" || token=="&&" || token=="or" || token=="||" || token=="|";
}
bool canUseSharedOperator(const std::string& unaryOp, const std::string& sharedOp){
return !(isSharedOperator(sharedOp) && isUnary(unaryOp));
}

bool canTakeThisNot(const std::string& unaryOp, const std::string& ph){
return !(unaryOp=="!" && ph[0]=='P');
}

}

import proposition;

formula : <assoc=right> ALWAYS LROUND implication RROUND EOF 
        | <assoc=right> ALWAYS implication EOF
        | sva_assert EOF
        ;

sva_assert : 'assert property' LROUND sva_assert RROUND
            | LROUND sva_assert RROUND
            | LROUND '@posedge' boolean RROUND sva_assert
            | <assoc=right> LROUND implication RROUND
            | <assoc=right> implication
            ;
            


implication : <assoc=right> tformula IMPL tformula
    	    | <assoc=right> tformula IMPLO tformula
    	    | <assoc=right> LCURLY? sere RCURLY? SEREIMPL tformula
    	    | <assoc=right> LCURLY? sere RCURLY? SEREIMPLO tformula
        	;


sere : FIRST_MATCH LROUND sere RROUND
     | LROUND sere RROUND
	 | LCURLY sere RCURLY
	 | <assoc=right> sere LSQUARED TIMES UINTEGER? (DOTS | COL)? (UINTEGER | DOLLAR)? RSQUARED
	 | <assoc=right> sere LSQUARED PLUS RSQUARED
	 | <assoc=right> booleanLayer LSQUARED ASS UINTEGER? (DOTS | COL)? (UINTEGER | DOLLAR)? RSQUARED
	 | <assoc=right> booleanLayer LSQUARED IMPLO UINTEGER? (DOTS | COL)? (UINTEGER | DOLLAR)? RSQUARED
     | dt_ncreps 
	 | sere BAND sere
	 | sere (TAND|INTERSECT|AND) sere
     | DT_AND
	 | sere (TOR|OR|BOR) sere
	 | sere DELAY LSQUARED? UINTEGER? (DOTS | COL)? (UINTEGER | DOLLAR)? RSQUARED? sere
	 | DELAY LSQUARED? UINTEGER? (DOTS | COL)? (UINTEGER | DOLLAR)? RSQUARED? sere
     | dt_next 
     | dt_next_and 
	 | sere COL sere
	 | sere SCOL sere
     | booleanLayer
	 ;

booleanLayer: LROUND booleanLayer RROUND
            | boolean 
            | NOT? PLACEHOLDER 
            ;


tformula: LROUND tformula RROUND 
        | {canUseSharedOperator(_input->LT(-1)->getText(),_input->LT(2)->getText())}? LCURLY? sere RCURLY?  
        | <assoc=right> {canTakeThisNot(_input->LT(1)->getText(),_input->LT(2)->getText())}? (TNOT|NOT) tformula 
    	| <assoc=right> NEXT LSQUARED? UINTEGER? RSQUARED? tformula
    	| <assoc=right> EVENTUALLY tformula 
    	| <assoc=right> tformula (UNTIL|RELEASE) tformula
     	| tformula (TAND|AND) tformula 
    	| tformula (TOR|OR|BOR) tformula 
        | DT_AND
        | booleanLayer
    	;

PLACEHOLDER: 'P' UINTEGER;


DT_AND
    : '..&&..'
    ;

dt_next
    : '..##' UINTEGER '..'
    ;

dt_next_and
    : '..#' UINTEGER '&' '..'
    ;

dt_ncreps
    : '..[' (IMPLO | ASS) UINTEGER ']@' (COL | SCOL) '..';

EVENTUALLY
    : 'F' | 'eventually'
    ;

ALWAYS
    : 'G' | 'always'
    ;

NEXT
    : 'X' | 'nexttime' | 'next'
    ;

UNTIL
    : 'W' | 'until'
    ;

RELEASE
    : 'R'
    ;

DOTS
    : '..'
    ;

IMPL
    : '=>'
    ;

IMPLO
    : '->'
    ;

IFF
    : '<->'
    ;

SEREIMPL
    : '|=>'
    | '[]=>'
    ;

SEREIMPLO
    : '|->'
    | '[]->'
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

FIRST_MATCH
    : 'first_match'
    ;

TNOT: 'not';

TAND: 'and';

INTERSECT : 'intersect';

TOR : 'or';

