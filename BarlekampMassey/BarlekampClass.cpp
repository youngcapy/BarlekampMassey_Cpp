#include <iostream>;
#include <vector>;

class BarlekampMassey {

	public:
		BarlekampMassey(unsigned base, unsigned degree, std::vector<unsigned> sequence) : base(base), degree(degree), cypheredSequence(sequence)
		{
		
		}

	private:
		//Characteristics of field
		unsigned base;
		unsigned degree;
		//Characteristics of sequence
		std::vector<unsigned> cypheredSequence;
	
};