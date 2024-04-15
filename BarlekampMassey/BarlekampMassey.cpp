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
	unsigned grade = 2;
	GaloisMathsEasy galLib;
	unsigned base = 13;
	unsigned numToMultiply = 4;
	galLib.multiplyPolyOnConst(sampleVec, base, numToMultiply);
	for (auto n : sampleVec)
		std::cout << n << std::endl;

}

