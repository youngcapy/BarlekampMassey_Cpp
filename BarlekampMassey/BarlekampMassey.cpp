#include "BarlekampClass.h"
#include "GaloisMathsEasy.h"
#include "GaloisMathsExtended.h"
#include "BarlekampMasseyInfo.h"

#include "sys/resource.h"

int main(int argc, char* argv[])
{
	

	BarlekampMasseyClass execution{"seq.txt", 2, 14};
	//struct rlimit rl;
	//getrlimit(RLIMIT_STACK, &rl);
    //std::cout << rl.rlim_cur << std::endl;

	return 0;

}

