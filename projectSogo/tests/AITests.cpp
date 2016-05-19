#include "PlayingFieldTest.cpp"

void RulesAndInfoDisplay();

/**
* Test for playing with ai on a 2x2x2 field
*/
void PlayingFieldAITest2x2x2()
{
    RulesAndInfoDisplay();

    PlayingField pF(2);
    cout << DrawPlayingField(&pF) << endl;

    PlayingField::OccupationState playerState = PlayingField::Blue;

    int x,y,z;

    bool win = false;

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
                    x = 0;
                    y = 0;
                    z = 0;
                }

                if(CheckForWin(&pF, playerState))
                {
                    win = true;
                    break;
                }

                playerState = PlayingField::Red;

                cout << endl;

            break;

           case PlayingField::Red:

                Vector3 choice;

                MiniMax(&pF, PlayingField::Red, PlayingField::Red, &choice);


                try
                {
                    pF.OccupySlot(choice.X,choice.Y,choice.Z, PlayingField::Red);
                }
                catch(PlayingField::FieldExeptions)
                {
                    cout << " ERROR : Field already assigned" << endl << endl;
                }
                catch(out_of_range)
                {
                    cout << " ERROR : Out of Range Error Player Red" << endl << endl;
                }

                if(CheckForWin(&pF, playerState))
                {
                    win = true;
                    break;
                }

                playerState = PlayingField::Blue;

                cout << endl;

            break;
        }

        cout << DrawPlayingField(&pF) << endl;

        if(win)
        {
            stringstream s;
            switch(playerState)
            {
            case PlayingField::Blue:
                    s << "Blue";
                break;
            case PlayingField::Red:
                    s << "Red";
                break;
            }

            s << "-Player won!" << std::endl;;

            cout << s.str();
            break;
        }
    }
}

/**
* AI playtest on a 3x3x3 field with no search depth
* Expected result : long search or crash
* result : crash
*/
void PlayingFieldAITest3x3x3NoDepth()
{
    RulesAndInfoDisplay();

    PlayingField pF(3);
    cout << DrawPlayingField(&pF) << endl;

    PlayingField::OccupationState playerState = PlayingField::Blue;

    int x,y,z;

    bool win = false;

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
                catch(PlayingField::FieldExeptions e)
                {
                    if(e == PlayingField::Occupied)
                    {
                        cout << " ERROR : Field already assigned" << endl << endl;
                    }
                    else
                    {
                        cout << " ERROR : Wrong Move!" << endl << endl;
                    }
                }
                catch(out_of_range)
                {
                    cout << " ERROR : Out of Range Error Player Blue" << endl << endl;
                    x = 0;
                    y = 0;
                    z = 0;
                }

                if(CheckForWin(&pF, playerState))
                {
                    win = true;
                    break;
                }

                playerState = PlayingField::Red;

                cout << endl;

            break;

           case PlayingField::Red:

                Vector3 choice;

                MiniMax(&pF, PlayingField::Red, PlayingField::Red, &choice);


                try
                {
                    pF.OccupySlot(choice.X,choice.Y,choice.Z, PlayingField::Red);
                }
                catch(PlayingField::FieldExeptions e)
                {
                    if(e == PlayingField::Occupied)
                    {
                        cout << " ERROR : Field already assigned" << endl << endl;
                    }
                    else
                    {
                        cout << " ERROR : Wrong Move!" << endl << endl;
                    }
                }
                catch(out_of_range)
                {
                    cout << " ERROR : Out of Range Error Player Red" << endl << endl;
                }

                if(CheckForWin(&pF, playerState))
                {
                    win = true;
                    break;
                }

                playerState = PlayingField::Blue;

                cout << endl;

            break;
        }

        cout << DrawPlayingField(&pF) << endl;

        if(win)
        {
            stringstream s;
            switch(playerState)
            {
            case PlayingField::Blue:
                    s << "Blue";
                break;
            case PlayingField::Red:
                    s << "Red";
                break;
            }

            s << "-Player won!" << std::endl;;

            cout << s.str();
            break;
        }
    }
}

/**
* AI Playtest with a 3x3x3 with a AI-MiniMax search depth of 4
*
*/
void PlayingFieldAITest3x3x3()
{
    RulesAndInfoDisplay();

    PlayingField pF(3);
    cout << DrawPlayingField(&pF) << endl;

    PlayingField::OccupationState playerState = PlayingField::Blue;

    int x,y,z;

    bool win = false;

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

                try
                {
                    std::vector<Vector3> posPositions = GetAvailablePositions(&pF);

                    /**
                     * @brief b
                     * Encapsulate in Function ( Find first available Slot )
                     * Define Vector2 => easier access
                     * Logger schreiben ????
                     */

                    bool b = false;

                    int i;

                    for(i = 0; i < posPositions.size(); i++)
                    {
                       if(posPositions.at(i).X == x && posPositions.at(i).Y == y)
                       {
                           b = true;
                           break;
                       }
                    }

                    pF.OccupySlot(x,y,posPositions.at(i).Z, PlayingField::Blue);
                }
                catch(PlayingField::FieldExeptions e)
                {
                    if(e == PlayingField::Occupied)
                    {
                        cout << " ERROR : Field already assigned" << endl << endl;
                    }
                    else
                    {
                        cout << " ERROR : Wrong Move!" << endl << endl;
                    }

                }
                catch(out_of_range)
                {
                    cout << " ERROR : Out of Range Error Player Blue" << endl << endl;
                    x = 0;
                    y = 0;
                }

                if(CheckForWin(&pF, playerState))
                {
                    win = true;
                    break;
                }

                playerState = PlayingField::Red;

                cout << endl;

            break;

           case PlayingField::Red:

                cout << "Player Red : " << endl << endl;

                Vector3 choice;

                MiniMax(&pF, PlayingField::Red, PlayingField::Red, 4, &choice);


                try
                {
                    pF.OccupySlot(choice.X,choice.Y,choice.Z, PlayingField::Red);
                }
                catch(PlayingField::FieldExeptions e)
                {
                    if(e == PlayingField::Occupied)
                    {
                        cout << " ERROR : Field already assigned" << endl << endl;
                    }
                    else
                    {
                        cout << " ERROR : Wrong Move!" << endl << endl;
                    }
                }
                catch(out_of_range)
                {
                    cout << " ERROR : Out of Range Error Player Red" << endl << endl;
                }

                if(CheckForWin(&pF, playerState))
                {
                    win = true;
                    break;
                }

                playerState = PlayingField::Blue;

                cout << endl;

            break;
        }

        cout << DrawPlayingField(&pF) << endl;

        if(win)
        {
            stringstream s;
            switch(playerState)
            {
            case PlayingField::Blue:
                    s << "Blue";
                break;
            case PlayingField::Red:
                    s << "Red";
                break;
            }

            s << "-Player won!" << std::endl;

            cout << s.str();
            break;
        }
    }
}

/**
* AI Playtest with a 3x3x3 with a AI-MiniMax search depth of 4
* AI vs AI
*
*/
void PlayingFieldAITestUltimateBattle()
{
    RulesAndInfoDisplay();

    PlayingField pF(3);
    cout << DrawPlayingField(&pF) << endl;

    PlayingField::OccupationState playerState = PlayingField::Blue;

    bool win = false;

    while(true)
    {
        Vector3 choice;
        switch(playerState)
        {
           case PlayingField::Blue:

                cout << "Player Blue : " << endl << endl;

                MiniMax(&pF, PlayingField::Red, PlayingField::Blue, 4, &choice);

                try
                {
                    pF.OccupySlot(choice.X,choice.Y,choice.Z, PlayingField::Blue);
                }
                catch(PlayingField::FieldExeptions e)
                {
                    if(e == PlayingField::Occupied)
                    {
                        cout << " ERROR : Field already assigned" << endl << endl;
                    }
                    else
                    {
                        cout << " ERROR : Wrong Move!" << endl << endl;
                    }
                }
                catch(out_of_range)
                {
                    cout << " ERROR : Out of Range Error Player Red" << endl << endl;
                }

                if(CheckForWin(&pF, playerState))
                {
                    win = true;
                    break;
                }


                if(CheckForWin(&pF, playerState))
                {
                    win = true;
                    break;
                }

                playerState = PlayingField::Red;

                cout << endl;

            break;

           case PlayingField::Red:

                MiniMax(&pF, PlayingField::Red, PlayingField::Red, 4, &choice);


                try
                {
                    pF.OccupySlot(choice.X,choice.Y,choice.Z, PlayingField::Red);
                }
                catch(PlayingField::FieldExeptions e)
                {
                    if(e == PlayingField::Occupied)
                    {
                        cout << " ERROR : Field already assigned" << endl << endl;
                    }
                    else
                    {
                        cout << " ERROR : Wrong Move!" << endl << endl;
                    }
                }
                catch(out_of_range)
                {
                    cout << " ERROR : Out of Range Error Player Red" << endl << endl;
                }

                if(CheckForWin(&pF, playerState))
                {
                    win = true;
                    break;
                }

                playerState = PlayingField::Blue;

                cout << endl;

            break;
        }

        cout << DrawPlayingField(&pF) << endl;

        if(win)
        {
            stringstream s;
            switch(playerState)
            {
            case PlayingField::Blue:
                    s << "Blue";
                break;
            case PlayingField::Red:
                    s << "Red";
                break;
            }

            s << "-Player won!" << std::endl;;

            cout << s.str();
            break;
        }
    }

    /**
    * To do
    */
    void RiggedBoardTest();
}
