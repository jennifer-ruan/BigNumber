//---------------------------------------------------------------------------------
// CC2.cpp
//---------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

#include "BigNumber.h"

using namespace std;

int main()
{
    ifstream input;
    ofstream output;
    input.open("input1.txt");
    output.open("output1.txt");

    if (!input.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    if (input.is_open()) {
        string line, firstNum, secondNum, operation;

        while (getline(input, line)) {
            if (line == "========") {

                getline(input, firstNum);
                getline(input, secondNum);
                getline(input, operation);

                BigNumber firstNumBig(firstNum);
                BigNumber secondNumBig(secondNum);
                BigNumber result;

                if (operation == "PLUS") {
                    result = Add(firstNumBig, secondNumBig);
                }
                else if (operation == "MINUS") {
                    result = Subtract(firstNumBig, secondNumBig);
                }
                else {
                    result = Multiply(firstNumBig, secondNumBig);
                }
                
                output << "========================" << endl;
                output << firstNum << endl;
                output << secondNum << endl;
                output << operation << endl;
                output << result.ConvertToString() << endl;
            }
        }
        input.close();
        output.close();
    }
    return 0;
}