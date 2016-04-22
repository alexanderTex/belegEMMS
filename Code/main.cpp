#include <iostream>

#include <PlayingField.h>

using namespace std;


/**
* Test to see if a playingField can be "rendered"
* Drawn will be the first , the second and the third layer
*
* result : | - | - | - |  ,  | - | - | - |  ,  | - | - | - |
*          | - | - | - |  ,  | - | - | - |  ,  | - | - | - |
*          | - | - | - |  ,  | - | - | - |  ,  | - | - | - |
*/
void PlayingFieldTest()
{
    PlayingField pF(3);

    cout << DrawPlayingField(&pF);
}

/**
* Test to see if a SlotOccupation can be changed/altered
* result : | - | - | - |  ,  | - | - | - |  ,  | - | - | - |
*          | - | - | - |  ,  | - | - | - |  ,  | - | - | - |
*          | - | - | - |  ,  | - | - | - |  ,  | - | - | - |
*
*          | - | - | - |  ,  | - | - | - |  ,  | - | - | - |
*          | - | x | - |  ,  | - | - | - |  ,  | - | - | - |
*          | - | - | - |  ,  | - | - | - |  ,  | - | - | - |
*/
void PlayingFieldSlotOccupation()
{
    PlayingField pF(3);

    cout << DrawPlayingField(&pF) << endl;


    pF.OccupySlot(1,2,0, PlayingField::Blue);


    cout << endl << endl;

    cout << DrawPlayingField(&pF) << endl;

}

int main()
{
    cout << "Hello world!" << endl;

    PlayingFieldSlotOccupation();

    return 0;
}


