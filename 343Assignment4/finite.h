#ifndef FINITE_H
#define FINITE_H

class Finite
{
public:
    //constructor
    Finite();
    //destructor
    ~Finite();
    //inputs a new value into system
    void input(string input);
    //prints out formatted version
    void print();
    
private:
    //{current state, number, number, expression, output}
    string currentArray[5];
    //could be deleted and just assigned to arr positions
    string currentNums;
    string currentState;
    string currentEx;
    string finalPrintOut;
    //different inputs
    bool numInput(string num);
    void stateInput(string state);
    bool expressionInput(string express);
    bool doubleNumInput(string arr[]);
    //checks on if the state needs to be progressed or not
    void statusCheck();
    //clears all the values being held
    void reset(string err);
    //helper function for print
    void printHelper();
};
#endif //FINITE_H
#include "finite.cpp"