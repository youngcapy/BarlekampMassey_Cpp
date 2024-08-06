#pragma once

#include "GaloisMathsEasy.h"
#include "GaloisMathsExtended.h"




class BarlekampMasseyClass {

	friend class GaloisMathsEasy;
	friend class GaloisMathsExtended;
	public:

		BarlekampMasseyClass(std::vector<int> cypheredSeq, unsigned base, unsigned degree = 1)
		{

			this->base = base;
			this->degree = degree;

			HardOperational = new GaloisMathsExtended{this->base, this->degree};
			EasyOperational = new GaloisMathsEasy{};

			if (cypheredSeq.size() > sequence.size())
				EasyOperational->extendPoly(sequence, cypheredSeq.size());
			for (unsigned i{}; i < cypheredSeq.size(); i++) {

				int temp = cypheredSeq[i];
				EasyOperational->numToField(temp, base);
				sequence[i] = static_cast<unsigned>(temp);

			}

		}
		void easyFieldBM();

	private:
		GaloisMathsEasy* EasyOperational{};
		GaloisMathsExtended* HardOperational{};
		unsigned base{};
		unsigned degree{};
		std::vector<unsigned> sequence{};
	
};