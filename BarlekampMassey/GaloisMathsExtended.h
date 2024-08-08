#ifndef GALOISMATHSEXTENDED_H
#define GALOISMATHSEXTENDED_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <cmath>
#include <set>
#include "Parser.h"

class GaloisMathsExtended {
friend class Parser;
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
    bool fieldSum(std::vector<unsigned>&, std::vector<unsigned>&);
    bool fieldMul();
	std::vector<unsigned> elemCreator(std::vector<unsigned>&);
	void polyToDegree(std::vector<unsigned>& poly, int degree);
	void numToField(int& num);
	unsigned reversedToField(int& num);


};

#endif