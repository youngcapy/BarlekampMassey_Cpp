#ifndef GALOISMATHSEASY_H
#define GALOISMATHSEASY_H

#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <algorithm>


class GaloisMathsEasy {
	friend class BarlekampMasseyClass;

	public:

		GaloisMathsEasy();
        
    private:

		void extendPoly(std::vector<unsigned>& poly, unsigned numToExtend); // Extending poly adding zeros to the begin

		void decreasePoly(std::vector<unsigned>& poly, unsigned numToDecrease); // Decreasing poly deleting elements

		void multiplyPolyOnConst(std::vector<unsigned>& poly, unsigned& base ,unsigned& constNum); // Multiplying elements to constant num 

		void multiplyPolyOnPoly(std::vector<unsigned>& polyToMultiply, std::vector<unsigned>& multiplierPoly, unsigned& base); // Meaned polies to be equialent at length.

		void polyToDegree(std::vector<unsigned>& poly, unsigned degree); // Meaned poly to be like 2x^3+ 1x^2 + x + 1 == {2, 1, 1, 1};
		
		void numToField(int& num, unsigned& base); // Function to bring elements to field by link
  
        unsigned reversedToField(unsigned& num, unsigned& base); // Finding reversed to the field with Euclidus extended algorithm

        //HELP FUNCTIONS EUCLIDUS//
        void extendedEuclid(unsigned a, unsigned b, std::pair<unsigned, unsigned>& coeffsPair);

};

#endif // GALOISMATHSEASY_H
