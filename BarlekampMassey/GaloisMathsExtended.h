#ifndef GALOISMATHSEXTENDED_H
#define GALOISMATHSEXTENDED_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <cmath>

class GaloisMathsExtended {

friend class BarlekampClass;
friend class Field;

public:

	GaloisMathsExtended(unsigned fieldBase, unsigned fieldDegree);

private:
	unsigned base;
	unsigned grade;
	std::vector<unsigned> primPoly;
    std::vector<std::vector<unsigned>> field;

    bool fieldBuilder();
    bool fieldSum();
    bool fieldMul();
	std::vector<unsigned> elemCreator(std::vector<unsigned>&);
	bool getPoly();
	bool getPolyHelp(std::string);
	void polyToDegree(std::vector<unsigned>& poly, int degree);
	void numToField(int& num, unsigned& base);
	unsigned reversedToField(int& num, unsigned& base);


};

#endif