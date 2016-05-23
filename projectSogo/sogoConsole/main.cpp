#include <iostream>

#include "./include/core/PlayingField.h"
#include "./include/core/Vector3.h"
#include "./include/core/AI.h"
#include "tests/AITests.cpp"
#include "tests/PlayingFieldTest.cpp"

using namespace std;

/**
* Diplays Rules and Other things in console
*
*/
void RulesAndInfoDisplay()
{
    cout << "You are x the opponent is o!" << endl;
    cout << "Goal : Four in a line ( horizontal, vertical or diagonal)" << endl << endl;

}

int main()
{
    PlayingFieldAITest3x3x3();
    return 0;
}


