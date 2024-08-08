#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>

class Parser{
    friend class GaloisMathsExtended;

    private:
        std::vector<unsigned> polyFinder(const unsigned& base, const unsigned& grade);    


};




#endif