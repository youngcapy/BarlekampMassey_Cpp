#pragma once

#include "GaloisMathsEasy.h"
#include "GaloisMathsExtended.h"
#include <fstream>
#include <thread>



class BarlekampMasseyClass {

	friend class GaloisMathsEasy;
	friend class GaloisMathsExtended;
	public:

		BarlekampMasseyClass(std::string fileWay, unsigned base, unsigned degree = 1);
		

	private:
		void easyFieldBM();
		void extendedFieldBM();
		void bmGettingReady(bool mode);
		void extendedFieldHelper(std::vector<unsigned>&, std::vector<unsigned>&, unsigned&, unsigned&, unsigned&);
		GaloisMathsEasy* EasyOperational{};
		GaloisMathsExtended* HardOperational{};
		std::thread operationalThread;
		std::thread readingThread;
		std::vector<unsigned> buffer;
		unsigned base{};
		unsigned degree{};
		std::string fileWay;
		std::vector<unsigned> sequence{};
	
};