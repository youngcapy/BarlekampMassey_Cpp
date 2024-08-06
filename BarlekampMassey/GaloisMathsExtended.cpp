#include "GaloisMathsExtended.h"

GaloisMathsExtended::GaloisMathsExtended(unsigned fieldBase, unsigned fieldDegree)
{

	base = fieldBase;
	grade = fieldDegree;
	primPoly.resize(grade + 1);
	getPoly();

	std::reverse(primPoly.begin(), primPoly.end());

	for (unsigned num : primPoly)
	   std::cout << num << std::endl;


}

bool GaloisMathsExtended::getPolyHelp(std::string strPoly){

	bool xFound = false;
	bool xDegree = false;
	bool xMul = false;
	bool readingNum = false;

	unsigned currentMul{};
	unsigned currentDegree{};

	for (unsigned i{}; i < strPoly.size(); i++) {


		if (std::isdigit(strPoly[i])) {
			
			if (readingNum) {

				if (xMul)
					currentMul = currentMul * 10 + (strPoly[i] - '0');
				else
					currentDegree = currentDegree * 10 + (strPoly[i] - '0');

			}

			if ((xMul == false) && (xDegree == false) && xFound == false) {
				xMul = true;
				currentMul = strPoly[i] - '0';
			}
			else if (xDegree == false && xMul == false) {

				xDegree = true;
				currentDegree = strPoly[i] - '0';


			}

			readingNum = true;

		}

		if (strPoly[i] == 'x') {
			xFound = true;
			readingNum = false;
			xMul = false;
		}

		if (strPoly[i] == ' ' && xFound) {

			if (currentMul == 0)
				currentMul = 1;
			if (currentDegree == 0)
				currentDegree = 1;
			primPoly[currentDegree] = currentMul;

			xMul = false;
			xDegree = false;
			xFound = false;
			readingNum = false;

			currentMul = 0;
			currentDegree = 0;


		}

		if (i == strPoly.size() - 1)
			primPoly[currentDegree] = currentMul;
		

	}
	return true;
}

bool GaloisMathsExtended::fieldBuilder() // Vectors are like x^n + x^(n-1) + ... + x^0
{
	std::vector<unsigned> tempVector(grade);
	tempVector[grade - 1] = 1;
    field[0] = tempVector;
	for(unsigned i{}; i < (unsigned)pow(base, grade) - 2; i++){

		field[i + 1] = elemCreator(field[i]);

	}
	tempVector = std::vector<unsigned>(grade);
	field[(unsigned)pow(base, grade) - 1] = tempVector;

	return true;
}

std::vector<unsigned> GaloisMathsExtended::elemCreator(std::vector<unsigned>& currentVector)
{
    std::vector<unsigned> result{currentVector};

	if(result[0] != 0){

		result[0] = 0;
		

	}

	else
		for(unsigned i{1}; i < result.size(); i++)
			result[i - 1] = result[i];
	
	return result;
}

bool GaloisMathsExtended::fieldSum()
{
    return false;
}

bool GaloisMathsExtended::fieldMul()
{
    return false;
}

bool GaloisMathsExtended::getPoly()
{

    std::string request {};
	request = "./script.sage ";
	request.append(std::to_string(base));
	request.append(" ");
	request.append(std::to_string(grade));

	system(request.c_str());
	
	std::ifstream file("conway_poly.txt");
	std::string polynomial;
	if (file.is_open()) {
		getline(file, polynomial);
		file.close();
	}
	std::cout << polynomial << std::endl;
	if(getPolyHelp(polynomial))
		return true;

	return false;
}

void GaloisMathsExtended::polyToDegree(std::vector<unsigned>& poly, int degree) {



}

void GaloisMathsExtended::numToField(int& num, unsigned& base) {

	num = abs(num) % base;

}

unsigned GaloisMathsExtended::reversedToField(int& num, unsigned& base) {

	return 0;

}
