#include "BarlekampClass.h"


BarlekampMasseyClass::BarlekampMasseyClass(std::string fileWay, unsigned base, unsigned degree)
{

	this->base = base;
	this->degree = degree;
	this->fileWay = fileWay;

	if(degree == 1){
		EasyOperational = new GaloisMathsEasy{};
		bmGettingReady(0);
		//easyFieldBM();
	}

	else{
		HardOperational = new GaloisMathsExtended{this->base, this->degree};
		bmGettingReady(1);
		//extendedFieldBM();
	}

	/*
	if (cypheredSeq.size() > sequence.size())
		EasyOperational->extendPoly(sequence, cypheredSeq.size());
	for (unsigned i{}; i < cypheredSeq.size(); i++) {

		int temp = cypheredSeq[i];
		EasyOperational->numToField(temp, base);
		sequence[i] = static_cast<unsigned>(temp);

	}
	*/


}


std::vector<unsigned> BarlekampMasseyClass::easyFieldBM() {

	std::vector<unsigned> returnalPoly{ 1 };
	std::vector<unsigned> previousState{ 1 };
	std::vector<unsigned> tempForReturnal{ 1 };
	std::stack<std::vector<unsigned>> tempForStates{};
	unsigned length = 0; // ReturnalPoly size
	unsigned b = 1;
	unsigned x = 1;
	unsigned n = 0; // Steps quantity
	int d = 0; // Error
	int prevErr = 0; // Temporary for comparing errors
	// ANOTHER TEMPS
	int multiplierNegative{}; 
	unsigned multiplierPositive{}; 
	int sizeDifference{};
	int tempForBring{};

	while (n < sequence.size()) {

		prevErr = 0;
		for (unsigned i{ 1 }; i < length + 1; i++) {
		
			int tempNum = returnalPoly[returnalPoly.size() - i - 1] * sequence[n - i];
			prevErr += tempNum;
		
		}
		d = sequence[n] + (prevErr); // Checking an error
		EasyOperational->numToField(d, base);
		if (d == 0) {
			x++;
			n++;
			continue;
		}
		
		else if (d != 0) {

			// CALCULATING NEW RETURNAL 

			tempForStates.push(std::vector<unsigned>{previousState.begin(), previousState.end()});

			multiplierNegative = 0 - d;
			EasyOperational->polyToDegree(previousState, x); // Bringing poly to field
			multiplierNegative *= EasyOperational->reversedToField(b, base); // Finding reversed and inserting it
			EasyOperational->numToField(multiplierNegative, base);
			multiplierPositive = static_cast<unsigned>(multiplierNegative); 
			//Calculating needed operations for all situations

			if ((2 * length) <= n) {

				EasyOperational->extendPoly(tempForReturnal, returnalPoly.size() - tempForReturnal.size()); // Extending if needed
				std::copy(returnalPoly.begin(), returnalPoly.end(), tempForReturnal.begin()); // Copying to temp array

			}
			

			EasyOperational->multiplyPolyOnConst(previousState, base, multiplierPositive); // Renewing a returnals
			sizeDifference = previousState.size() - returnalPoly.size();
			if (sizeDifference > 0)
				EasyOperational->extendPoly(returnalPoly, sizeDifference);
			else
				EasyOperational->extendPoly(previousState, abs(sizeDifference));

			for (unsigned j{}; j < previousState.size(); j++) {
				
				tempForBring = previousState[j] + returnalPoly[j];
				EasyOperational->numToField(tempForBring, base);
				returnalPoly[j] = static_cast<unsigned>(tempForBring); // Rewriting returnalPolynom

			}
			previousState = tempForStates.top();
			//tempForStates.pop();

			if ((2 * length) <= n) {

				sizeDifference = previousState.size() - tempForReturnal.size();
				if (sizeDifference >= 0)
					EasyOperational->decreasePoly(previousState, previousState.size() - tempForReturnal.size());
				else
					EasyOperational->extendPoly(previousState, abs(sizeDifference));
				std::copy(tempForReturnal.begin(), tempForReturnal.end(), previousState.begin());
				length = n + 1 - length;
				b = d;
				x = 1;

			}
			else
				x++; // Increasing a gradecounter

			n++; // Increasing steps, coming to next iteration

		}
	

	}

	//returnalPoly.pop_back(); // Deleting unused num
	std::reverse(returnalPoly.begin(), returnalPoly.end()); // Reversing to display in LFSR (x^0 + x^1 + x^2....+ x^n)
	for (auto n : returnalPoly)
		std::cout << n << "\t";
	std::cout << std::endl;
	std::cout << length << std::endl;

	return returnalPoly;

}

std::vector<unsigned> BarlekampMasseyClass::extendedFieldBM()
{

	std::vector<unsigned> currentNum{};
	unsigned bmGrade{1}; // x
	unsigned stepsNum{0}; // N
	unsigned lfsrLength{0}; // L
	unsigned currentCheck{}; // d
	unsigned previousCheck{0}; // b

	unsigned numPolyConvConst{(HardOperational->elemQuantity) - HardOperational->grade};

	std::vector<unsigned> temp{}; // T(D)
	std::vector<unsigned> currentLFSR{0}; // C(D)
	std::vector<unsigned> helperB{0}; // B(D)
	
	for(unsigned j{}; j < buffer.size(); j++){

		if(buffer[j] == UINT_MAX)
			break;

		currentNum = *(HardOperational->numPolyConv[buffer[j]]);
		std::vector<unsigned> checkVec(HardOperational->elemQuantity);
		//currentCheck = currentNum;
		std::reverse(currentLFSR.begin(), currentLFSR.end());
		for(unsigned i{1}; i <= lfsrLength; i++){
			
			std::vector<unsigned> tempVector = HardOperational->numToPolyConv(buffer[stepsNum - i]);
			unsigned prevNums = HardOperational->polyToIndexConv(tempVector);
			unsigned mulTemp = HardOperational->fieldMul(currentLFSR[i], prevNums);			
			std::vector<unsigned> mulVec = HardOperational->field[mulTemp];
			HardOperational->fieldSum(checkVec, mulVec);

		}
		std::reverse(currentLFSR.begin(), currentLFSR.end());
		HardOperational->fieldSum(checkVec, currentNum);
		checkVec.erase(checkVec.begin(), checkVec.begin() + numPolyConvConst);
		currentCheck = HardOperational->polyToIndexConv(checkVec);

		if(currentCheck == HardOperational->elemQuantity - 1){


			bmGrade++;
		
		}

		else{

			if(2 * lfsrLength > stepsNum){

				extendedFieldHelper(currentLFSR, helperB, currentCheck, previousCheck, bmGrade);
				bmGrade++;

			}
			
			else{
	
				if(lfsrLength == 516)
					std::cout << "I`m here" << std::endl;
				temp = currentLFSR;
				extendedFieldHelper(currentLFSR, helperB, currentCheck, previousCheck, bmGrade);
				lfsrLength = stepsNum + 1 - lfsrLength;
				helperB = temp;
				previousCheck = currentCheck;
				bmGrade = 1;
			}


		}

		stepsNum++;

	}
	for(unsigned i{}; i < currentLFSR.size(); i++)
		currentLFSR[i] = HardOperational->polyToNumConv(HardOperational->field[currentLFSR[i]]);
	return currentLFSR;

}

void BarlekampMasseyClass::bmGettingReady(bool mode)
{

	/*
	if(mode)
		operationalThread = std::thread([this](){
			easyFieldBM();
		});
	*/

		readingThread = std::thread([this](){
		std::ifstream reader(fileWay);
		char symbol;
		unsigned currentNum{0};
		bool readingNum = false;
		while(reader.get(symbol)){

			if(isdigit(symbol)){
				
				if(!readingNum)
					readingNum = true;
				currentNum = currentNum * 10 + (symbol - '0'); 

			}
			else{

				if(readingNum)
					buffer.push_back(currentNum);
				readingNum = false;
				currentNum = 0;

			}

		}
		buffer.push_back(UINT_MAX);
		
	});
	readingThread.detach();

	if(!mode){
		std::future<std::vector<unsigned>> easyResult = std::async(&BarlekampMasseyClass::easyFieldBM, this);
	}
	else{
		std::cout << "Started extended thread" << std::endl;
		std::future<void> extendedFoo = std::async(std::launch::async, [this](){
			std::vector<unsigned> lfsrState = extendedFieldBM();
			std::ofstream writing("result.txt");
			
			for(unsigned num: lfsrState)
				writing << num << "\t";
			writing.close();
		});
	}
		/*
		operationalThread = std::thread([this](){
			std::vector<unsigned> lfsrState = extendedFieldBM();
			std::ofstream writing("result.txt");
			
			for(unsigned num: lfsrState)
				writing << num << "\t";
			writing.close();
		});
		
	operationalThread.detach();
		*/

}

void BarlekampMasseyClass::extendedFieldHelper(std::vector<unsigned>& currentLFSR, std::vector<unsigned> helperB, unsigned& currentCheck, unsigned& previousCheck, unsigned& gradeX)
{

	unsigned reversedPrev = HardOperational->reversedToField(previousCheck);
	unsigned checksMul = HardOperational->fieldMul(currentCheck, reversedPrev);
	checksMul = HardOperational->fieldMul(checksMul, HardOperational->constantNegIndex);
	HardOperational->indexPolyToDeg(helperB, gradeX);
	for(unsigned i{0}; i < helperB.size(); i++)
		helperB[i] = HardOperational->fieldMul(helperB[i], checksMul);
  	HardOperational->polyIndexSum(currentLFSR, helperB);	

}
