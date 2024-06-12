#include <iostream>;
#include <vector>;
#include "GaloisMathsEasy.cpp";
#include "GaloisMathsExtended.cpp";
#include "BarlekampClass.cpp";
#pragma once

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

	std::vector<int> mySeq{ 1, 3, 2, 0, 5, 3, 2, 6, 3, 4, 0, 6};
	unsigned base = 7;
	BarlekampMasseyClass massey(mySeq, base);
	massey.easyFieldBM();


}

