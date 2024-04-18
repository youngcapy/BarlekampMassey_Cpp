#include <iostream>;
#include <vector>;
#include <cmath>;
#pragma once

class GaloisMathsEasy {

	public:

		GaloisMathsEasy()
		{

		}

		void extendPoly(std::vector<unsigned>& poly, unsigned numToExtend) { // Extending poly adding zeros to the begin

			if (numToExtend <= 0)
				return;
			for(unsigned i{}; i < numToExtend; i++)
				poly.insert(poly.begin(), 0);

		}

		void decreasePoly(std::vector<unsigned>& poly, unsigned numToDecrease) { // Decreasing poly deleting elements

			for (unsigned i{}; i < numToDecrease; i++)
				poly.pop_back();

		}

		void multiplyPolyOnConst(std::vector<unsigned>& poly, unsigned& base ,unsigned& constNum) { // Multiplying elements to constant num 

			for (unsigned i{}; i < poly.size(); i++) {
				poly[i] *= constNum;
				int temp = (unsigned)poly[i];
				numToField(temp, base);
				poly[i] = static_cast<unsigned>(temp);
			}
		}

		void multiplyPolyOnPoly(std::vector<unsigned>& polyToMultiply, std::vector<unsigned>& multiplierPoly, unsigned& base) { // Meaned polies to be equialent at length.

			unsigned firstSizeOfPoly = polyToMultiply.size();
			bool extended = false;
			unsigned sizeOfVectorMuled{0};
			for (unsigned i{}; i < polyToMultiply.size(); i++) {
				if (polyToMultiply[i] == 0) // If element is zero, skip
					continue;
				for (unsigned j{}; j < multiplierPoly.size(); j++) {

					if (multiplierPoly[j] == 0) // If element is zero, skip
						continue;
					if ((2 * firstSizeOfPoly - 1 - i - j) > polyToMultiply.size() && !extended) { // The vector can be extended just once
						sizeOfVectorMuled = 2 * firstSizeOfPoly - 1 - i - j;
						i += sizeOfVectorMuled - polyToMultiply.size();
						extendPoly(polyToMultiply, i);
						extended = true;
						
					}
					unsigned indexToInsert = polyToMultiply.size() - (polyToMultiply.size() - 1 - i + multiplierPoly.size() - j);
					if(indexToInsert != i)
						polyToMultiply[indexToInsert] += (polyToMultiply[i] * multiplierPoly[j]); // Multiplying elements
					else
						polyToMultiply[indexToInsert] = polyToMultiply[i] * multiplierPoly[j];
				}
			}

			for (unsigned i{}; i < polyToMultiply.size(); i++) {
				int temp = static_cast<int>(polyToMultiply[i]);
				numToField(temp, base); // Bringing elements to field
				polyToMultiply[i] = static_cast<unsigned>(temp);
			
			}
		}

		void polyToDegree(std::vector<unsigned>& poly, unsigned degree){ // Meaned poly to be like 2x^3+ 1x^2 + x + 1 == {2, 1, 1, 1};
		
			for (unsigned i{}; i < degree; i++)
				poly.push_back(0);

		}
		void numToField(int& num, unsigned& base) { // Function to bring elements to field

			bool negFlag = num < 0;
			num = abs(num) % base;
			
			if (negFlag)
				num = base - num;
			
		}       

        unsigned reversedToField(unsigned& num, unsigned& base) { // Finding reversed to the field with Euclidus extended algorithm

			if (num == 1 || num == 0)
				return num;

			std::pair<unsigned, unsigned> bezoutCoeffs{0, 0};

			extendedEuclid(num, base, bezoutCoeffs);

			int x_coeff{ static_cast<int>(bezoutCoeffs.first * num ) };
			int y_coeff{ static_cast<int>(bezoutCoeffs.second * num) };
			numToField(x_coeff, base);
			if (x_coeff == 1)
				return bezoutCoeffs.first;
			else {

				numToField(y_coeff, base);
				return bezoutCoeffs.second;

			}
        }



        //HELP FUNCTIONS EUCLIDUS//
        void extendedEuclid(unsigned a, unsigned b, std::pair<unsigned, unsigned>& coeffsPair) {
			int r1{}; int r2{};
			int r = 0;
			
			if (a > b) {
				r1 = a;
				r2 = b;
			}
			else {
				r1 = b;
				r2 = a;
			}
				
			int x1 = 0; int y1 = 1;
			int x2 = 1; int y2 = 0;

			int x{}; int y{}; // Bezout`s coeffs
			unsigned q{};

			while (r != 1) {

				q = r1 / r2;
				r = r1 - q * r2;
				r1 = r2;
				r2 = r;
				x = x1 - q * x2;
				y = y1 - q * y2;

				// Updating values

				x1 = x2; y1 = y2;
				x2 = x; y2 = y;
				
			}
			//std::cout;
			numToField(x, b);
			numToField(y, b);
			coeffsPair.first = x;
			coeffsPair.second = y;

        }

};