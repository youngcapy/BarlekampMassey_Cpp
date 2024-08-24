#include "GaloisMathsExtended.h"

GaloisMathsExtended::GaloisMathsExtended(unsigned fieldBase, unsigned fieldDegree)
{

	base = fieldBase;
	grade = fieldDegree;
	elemQuantity = pow(base, grade);
	primPoly.resize(grade + 1);

	Parser polyGetter{};
	primPoly = polyGetter.polyFinder(base, grade);
	
	for(auto num: primPoly)
		std::cout << num << "\t";
	std::cout << std::endl;
	

	fieldBuilder();
	for(std::vector<unsigned> vec: field){

		for(unsigned num: vec)
			std::cout << num << "\t";
		std::cout << std::endl;
	}

	if(!convertionBuilder())
		std::cout << "Error" << std::endl;

	constantNegFinder();
}

bool GaloisMathsExtended::constantNegFinder()
{
    
	for(unsigned i{}; i < field.size(); i++)
		if(&field[i] == numPolyConv[base - 1])
			constantNegIndex = i;
	return true;
}

bool GaloisMathsExtended::convertionBuilder() // building field for convertion poly-decimal
{
	
	numPolyConv.resize(pow(base, grade));

	for(unsigned j{}; j < field.size(); j++){

		unsigned polyGrade{grade - 1};
		unsigned index{};
		for(unsigned i{}; i < grade; i++){

			if(polyGrade == i){

				index += field[j][i];
				break;

			}
			index += pow(field[j][i] * base, polyGrade - i);

		}

		numPolyConv[index] = &field[j];

	}

	return true;

}

bool GaloisMathsExtended::fieldBuilder() // Vectors are like x^n + x^(n-1) + ... + x^0
{
	field.resize(pow(base, grade));
	std::vector<unsigned> tempVector(grade);
	tempVector[grade - 1] = 1;
    field[0] = tempVector;
	for(unsigned i{}; i < (unsigned)pow(base, grade) - 2; i++){

		field[i + 1] = elemCreator(field[i]);

	}
	tempVector = std::vector<unsigned>(grade); // last elem is zero
	field[(unsigned)pow(base, grade) - 1] = tempVector;
	return true;
}


unsigned GaloisMathsExtended::polyToNumConv(std::vector<unsigned>& poly)
{
    for(unsigned i{}; i < numPolyConv.size(); i++)
		if(*numPolyConv[i] == poly)
			return i;
	return elemQuantity - 1; // returning zero elem
}

unsigned GaloisMathsExtended::polyToIndexConv(std::vector<unsigned> & poly)
{
	for(unsigned i{}; i < field.size(); i++)
		if(poly == field[i])
			return i;
    return elemQuantity - 1; // returning zero elem
}

std::vector<unsigned> GaloisMathsExtended::elemCreator(std::vector<unsigned>& currentVector)
{
    std::vector<unsigned> result{currentVector};
	bool highDegree{};
	unsigned highDegreeNum{};

	if(result[0] != 0){
		
		highDegreeNum = result[0];
		highDegree = true;

	}

	result.erase(result.begin());
	result.push_back(0);
	


	if(highDegree){

		for(unsigned i{1}; i < primPoly.size(); i++){
			int temp = result[i - 1] - (primPoly[i] * highDegreeNum);
			numToField(temp);
			result[i - 1] = static_cast<unsigned>(temp);
		
		}
	}
	
	return result;
}

bool GaloisMathsExtended::fieldSum(std::vector<unsigned>& firstOper, std::vector<unsigned>& secOper)
{
	if(firstOper.size() < secOper.size())
		firstOper.resize(secOper.size());
	unsigned lessSize{};
	firstOper.size() > secOper.size() ? lessSize = secOper.size() : lessSize = firstOper.size();
	
	std::reverse(firstOper.begin(), firstOper.end());
	std::reverse(secOper.begin(), secOper.end());

    for(unsigned i{0}; i < lessSize; i++){

		firstOper[i] = (firstOper[i] + secOper[i]) % base;
		
	}

	std::reverse(firstOper.begin(), firstOper.end());
	std::reverse(secOper.begin(), secOper.end());

	return true;
}

bool GaloisMathsExtended::polyIndexSum(std::vector<unsigned>& firstPoly, std::vector<unsigned>& secPoly)
{

	while(firstPoly.size() < secPoly.size())
		firstPoly.insert(firstPoly.begin(), elemQuantity - 1);

	while(secPoly.size() < firstPoly.size())
		secPoly.insert(secPoly.begin(), elemQuantity - 1);

    
	for(unsigned i{}; i < firstPoly.size(); i++){

 		std::vector<unsigned> tempFirstPoly{field[firstPoly[i]]};
		std::vector<unsigned> tempSecondPoly{field[secPoly[i]]};


		fieldSum(tempFirstPoly, tempSecondPoly);
		firstPoly[i] = polyToIndexConv(tempFirstPoly);

	}


	return true;
}

unsigned GaloisMathsExtended::fieldMul(unsigned& num1, unsigned& num2)
{
	if(num1 == elemQuantity - 1 || num2 == elemQuantity - 1)
		return elemQuantity - 1;
    unsigned fieldIndex = (num1 + num2);
	if(fieldIndex >= elemQuantity - 1)
		fieldIndex -= elemQuantity - 1;
	return fieldIndex;
}



std::vector<unsigned> GaloisMathsExtended::numToPolyConv(unsigned& index)
{
	if(index == 0)
		return std::vector<unsigned>(grade);
    return std::vector<unsigned>{*numPolyConv[index]};
}

void GaloisMathsExtended::polyToDegree(std::vector<unsigned>& poly, int degree) {

	for(unsigned i{}; i < degree; i++){

		poly.push_back(0);
		if(poly[0] != 0){

			continue;

		}
		poly.erase(poly.begin());

	}

}

void GaloisMathsExtended::indexPolyToDeg(std::vector<unsigned> &poly, int degree)
{

	for(unsigned i{}; i < degree; i++){

		poly.push_back(elemQuantity - 1);
		if(poly[0] != elemQuantity - 1){

			continue;

		}
		poly.erase(poly.begin());

	}

}

void GaloisMathsExtended::indexPolySum(std::vector<unsigned> &poly1, std::vector<unsigned> &poly2)
{
}

void GaloisMathsExtended::numToField(int& num) {

	num >= 0? num %= base : num = (base - (abs(num) % base)) % base;

}

unsigned GaloisMathsExtended::reversedToField(const unsigned& index) {

	if(index == 0)
		return 0;
	return (elemQuantity - 1) - index;

}
