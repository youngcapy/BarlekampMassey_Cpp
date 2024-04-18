#include <iostream>;
#include <vector>;
#include "GaloisMathsEasy.cpp";
#include "GaloisMathsHard.cpp";
#include "BarlekampClass.cpp";

class BarlekampMasseyInfo {

    public:
		BarlekampMasseyInfo()
		{

		}
	private:
		int degree;
		std::vector<int> polynom{};
};


int main()
{

	std::vector<unsigned> sampleVec{ 4, 3, 2, 1, 0 }; // 4x^4 + 3x^3 + 2x^2 + x;
	GaloisMathsEasy galLib;
	unsigned base = 5;
	std::vector<unsigned> multiplier{ 3, 1, 3, 4, 1 }; // 3x^4 + 1x^3 + 3x^2 + 4x + 1;
	galLib.multiplyPolyOnPoly(sampleVec, multiplier, base); // Expecting  2x^8 + 4x^7 + 2x^6 + x^5 + 4x^4 + 4x^7 + 3x^6 + 4x^5 + 2x^4 + 3x^3 + x^6 + 2x^5 + x^4 + 3x^3 + 2x^2 + 3x^5 + x^4 + 3x^3 + 4x^2 + x = 
	// = 2x^8 + 3x^7 + x^6 + 3x^4 + 4x^3 + x^2 + x {2, 3, 1, 0, 3, 4, 1, 1, 0}
	for (auto num : sampleVec)
		std::cout << num << std::endl;

}

