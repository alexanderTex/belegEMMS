#include <iostream>

#include "PlayingField.h"
#include "Vector3.h"
#include "AI.h"
#include "../tests/AITests.cpp"
#include "../tests/PlayingFieldTest.cpp"

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
    PlayingFieldAITestUltimateBattle();
    return 0;
}


