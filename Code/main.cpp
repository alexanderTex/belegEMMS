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
void PlayingFieldTestThree()
{
    PlayingField pF(3);

    cout << DrawPlayingField(&pF);
}

/**
* Test to see if a playingField can be "rendered"
* Drawn will be the first , the second and the third layer
*
* result : | - | - | - | - |  ,  | - | - | - | - |  ,  | - | - | - | - |
*          | - | - | - | - |  ,  | - | - | - | - |  ,  | - | - | - | - |
*          | - | - | - | - |  ,  | - | - | - | - |  ,  | - | - | - | - |
*          | - | - | - | - |  ,  | - | - | - | - |  ,  | - | - | - | - |
* should look like this ( actually looks different, cause the console window
* is not wide enough
*/
void PlayingFieldTestFour()
{
    PlayingField pF(4);

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

/**
* Test to check the evaluation of Input
*   no check yet for win or lose state
*
*
*/
void PlayingFieldInteractionTest()
{
    PlayingField pF(4);
    cout << DrawPlayingField(&pF) << endl;

    PlayingField::OccupationState playerState = PlayingField::Blue;

    int x,y,z;

    while(true)
    {
        switch(playerState)
        {
           case PlayingField::Blue:

            cout << "Player Blue : " << endl << endl;

            cout << "Please enter x :" << endl;
            cin >> x;
            cout << "Please enter y :" << endl;
            cin >> y;
            cout << "Please enter z :" << endl;
            cin >> z;

            try
            {
                pF.OccupySlot(x,y,z, PlayingField::Blue);
            }
            catch(PlayingField::FieldExeptions)
            {
                cout << " ERROR : Field already assigned" << endl << endl;
            }
            catch(out_of_range)
            {
                cout << " ERROR : Out of Range Error Player Blue" << endl << endl;
            }

            playerState = PlayingField::Red;

            cout << endl;

            break;

           case PlayingField::Red:

            cout << "Player Red : " << endl << endl;

            cout << "Please enter x :" << endl;
            cin >> x;
            cout << "Please enter y :" << endl;
            cin >> y;
            cout << "Please enter z :" << endl;
            cin >> z;


            try
            {
                pF.OccupySlot(x,y,z, PlayingField::Red);
            }
            catch(PlayingField::FieldExeptions)
            {
                cout << " ERROR : Field already assigned" << endl << endl;
            }
            catch(out_of_range)
            {
                cout << " ERROR : Out of Range Error Player Red" << endl << endl;
            }

            playerState = PlayingField::Blue;

            cout << endl;

            break;
        }

        cout << DrawPlayingField(&pF) << endl;
    }
}

int main()
{

    PlayingFieldInteractionTest();

    return 0;
}


