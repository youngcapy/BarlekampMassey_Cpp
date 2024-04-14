#include <iostream>;
#include <vector>;
#include <cmath>;

static class GaloisMathsEasy {

	public:

		void polyToDegree(std::vector<unsigned>& poly, int& degree){
		
			

		}
		void numToField(int& num, unsigned& base) {

			num = abs(num) % base;
			
		}       

        unsigned reversedToField(unsigned& num, unsigned& base) {

			std::pair<int, int> bezoutCoeffs{ extendedEuclid(num, base) };
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
        std::pair<unsigned, unsigned>extendedEuclid(unsigned a, unsigned b) {
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

			numToField(x, b);
			numToField(y, b);

			return std::pair<unsigned, unsigned> {x, y};

        }

};