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
	GaloisMathsEasy sample;
	unsigned base = 293;
	unsigned reversed = 129;
	std::cout << sample.reversedToField(reversed, base) << std::endl;

}

