#include "Parser.h"

std::vector<unsigned> Parser::polyFinder(const unsigned &base, const unsigned &grade)
{

    std::vector<unsigned> resultingVec;
    try{

        std::ifstream conwayReader("CPimport.txt");
        std::string fileStr{};
        std::string strLikePoly{};
        unsigned baseDistance = std::ceil(std::log10(base + 1));
        unsigned gradeDistance = std::ceil(std::log10(grade + 1));

        if(conwayReader.is_open()){

            while(std::getline(conwayReader, fileStr)){

                unsigned basePos = fileStr.find(std::to_string(base));
                unsigned gradePos = fileStr.find(std::to_string(grade));
                if(basePos  == 1 && gradePos == baseDistance + 2){
                    strLikePoly = fileStr.substr(4 + baseDistance + gradeDistance, grade * 2 + 2);
                    std::stringstream strParser(strLikePoly);
                    std::string number{};
                    while(std::getline(strParser, number, ','))
                        resultingVec.push_back(static_cast<unsigned>(std::stoi(number)));
                    break;
                }
            }

        } 
        conwayReader.close();

    }
    catch(std::exception e){

        std::cout << e.what() << std::endl;

    }
    std::reverse(resultingVec.begin(), resultingVec.end());
    return resultingVec;
}
