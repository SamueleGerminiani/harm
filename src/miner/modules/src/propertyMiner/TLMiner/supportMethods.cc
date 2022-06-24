#include "supportMethods.hh"

#include <cmath>
#include<iostream>

namespace harm{


double getEntropy(size_t occurrences, size_t traceLength) {
    double goalTrue  = DIV(occurrences, traceLength);
    double goalFalse = 1 - goalTrue;
    //std::cout << "Goal True: " << occurrences << " " << traceLength<< std::endl;
    return (-1) * goalTrue * log2(goalTrue) +
           (-1) * goalFalse * log2(goalFalse);
}
double getConditionalEntropy(size_t occProposition,size_t occGoal, size_t traceLength) {
      double probXx = static_cast<double>(occProposition) /
                      static_cast<double>(traceLength);
      // P(Y|X=x)
      double propYTrueGivenXx = static_cast<double>(occGoal) /
                                static_cast<double>(occProposition);

      // // P(!Y|X=x)
      double propYFalseGivenXx = 1 - propYTrueGivenXx;

      // H(Y|X=x)
      double entropyYgivenXx =
          ((-1) * propYTrueGivenXx * log2(propYTrueGivenXx) +
           (-1) * propYFalseGivenXx * log2(propYFalseGivenXx));

      return probXx * entropyYgivenXx;
}

} 

