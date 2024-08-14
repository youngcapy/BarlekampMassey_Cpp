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
#include "limits.h"
#include "Parser.h"


class GaloisMathsExtended {
friend class Parser;
friend class BarlekampMasseyClass;
friend class BarlekampClass;
friend class Field;

public:

	GaloisMathsExtended(unsigned fieldBase, unsigned fieldDegree);

private:
	unsigned base; // contains field base
	unsigned grade; // contains field grade
	unsigned elemQuantity; // contains pow(base, grade)
	unsigned constantNegIndex; // contains convertion constant
	std::vector<unsigned> primPoly; // contains primitive polynomial
    std::vector<std::vector<unsigned>> field; // contains field of polynomials with indexes
	std::vector<std::vector<unsigned>*> numPolyConv; // contains decimal nums with links to their polynomials
	
	bool constantNegFinder(); // finds convertion constant
	bool convertionBuilder(); // builds numPolyConv
    bool fieldBuilder(); // builds field	
    bool fieldSum(std::vector<unsigned>&, std::vector<unsigned>&); // provides sum to field
    unsigned fieldMul(unsigned&, unsigned&); // provides mul to field

	unsigned polyToNumConv(std::vector<unsigned>*); // converts polynomial to decimal(again?)
	//unsigned polyToDecConv(const std::vector<unsigned>&); // converts polynomial to decimal

	std::vector<unsigned> numToPolyConv(unsigned&); // converts decimal to polynomial
	std::vector<unsigned> elemCreator(std::vector<unsigned>&); // creates polynomials for field
	void polyToDegree(std::vector<unsigned>& poly, int degree); // provides exponentiation
	void numToField(int& num); // moves num to field
	unsigned reversedToField(const unsigned&); // returns reversed num to field


};

#endif