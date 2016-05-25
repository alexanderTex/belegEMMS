#include "../../include/core/PlayingField.h"

#include <iostream>

PlayingField::Slot::Slot()
{
    //ctor
    this->Occupation = None;
}

PlayingField::Slot::Slot(PlayingField::OccupationState occupation)
{
    //ctor
    this->Occupation = occupation;
}


PlayingField:: PlayingField(int fieldSize)
{
    //ctor

    this->m_FieldSize = fieldSize;

    this->m_slots = new vector<vector< vector<Slot*> *> *>();

    // fills the Field
    //fills the field's horizontal lines
    for(int i = 0; i < this->m_FieldSize; i++)
    {
        this->m_slots->push_back(new vector< vector<Slot*> *>());

        //fills the field's depth lines
        for(int j = 0; j < this->m_FieldSize; j++)
        {
            this->m_slots->at(i)->push_back(new vector<Slot*>());

            //fills the field's Vertical lines
            for(int k = 0; k < this->m_FieldSize; k++)
            {
                this->m_slots->at(i)->at(j)->push_back(new Slot());
            }
        }
    }

}

PlayingField::PlayingField(const PlayingField *field):
    PlayingField(field->GetFieldSize())
{
    // copies the states of the field
    //copies the field's horizontal lines
    for(int i = 0; i < this->m_FieldSize; i++)
    {
        //copies the field's depth lines
        for(int j = 0; j < this->m_FieldSize; j++)
        {
            //copies the field's Vertical lines
            for(int k = 0; k < this->m_FieldSize; k++)
            {
                this->m_slots->at(i)->at(j)->at(k) = new Slot(field->GetSlot(i,j,k)->Occupation);
            }
        }
    }
}

PlayingField::~PlayingField()
{
    //copies the field's horizontal lines
    for(int i = 0; i < this->m_FieldSize; i++)
    {
        //copies the field's depth lines
        for(int j = 0; j < this->m_FieldSize; j++)
        {
            //copies the field's Vertical lines
            for(int k = 0; k < this->m_FieldSize; k++)
            {
                delete(this->m_slots->at(i)->at(j)->at(k));
            }
            delete(this->m_slots->at(i)->at(j));
        }
        delete(this->m_slots->at(i));
    }

    delete(this->m_slots);
}

PlayingField::Slot* PlayingField::GetSlot( int x, int y, int z) const throw(out_of_range)
{
    return this->m_slots->at(x)->at(y)->at(z);
}

 void PlayingField::OccupySlot(int x, int y, int z, PlayingField::OccupationState id) throw(out_of_range, FieldExeptions)
 {
     if(this->IsPositionAvailable(x,y,z))
     {
         Slot *s = this->GetSlot(x,y,z);

         if(s->Occupation == None)
         {
            s->Occupation = id;
         }
         else
         {
            throw Occupied;
         }

     }
     else
     {
        throw PositionNotAvailable;
     }
 }

void PlayingField::OccupySlot(Vector3 pos, PlayingField::OccupationState id) throw(out_of_range, FieldExeptions)
{
    OccupySlot(pos.X, pos.Y, pos.Z, id);
}

 bool PlayingField::IsPositionAvailable(int x, int y, int z) const
 {
    Vector3 v(x, y, z);

     bool b = false;

     std::vector<Vector3> posPositions = GetAvailablePositions(this);
     for(int i = 0; i < posPositions.size(); i++)
     {
        if(posPositions.at(i) == v)
        {
            b = true;
            break;
        }
     }

     return b;
 }

 std::vector<Vector3> GetAvailablePositions(const PlayingField *field) throw(out_of_range)
 {
    std::vector<Vector3> ret;

    Vector3 *vec = new Vector3();

    for(int i = 0; i < field->GetFieldSize(); i++)
    {
        for(int j = 0; j < field->GetFieldSize(); j++)
        {
            for(int k = 0; k < field->GetFieldSize(); k++)
            {
                if(field->GetSlot(i,j,k)->Occupation == PlayingField::None)
                {
                    vec->X = i;
                    vec->Y = j;
                    vec->Z = k;
                    ret.push_back(*vec);
                    break;
                }
            }
        }
    }

    delete(vec);

    return ret;
 }

 int GetAvailablePosition(int x, int y, const PlayingField *field) throw(out_of_range)
 {
     std::vector<Vector3> avPositions = GetAvailablePositions(field);

     for(int i = 0; i < avPositions.size(); i++)
     {
         if(avPositions.at(i).X == x && avPositions.at(i).Y == y)
         {
             return avPositions.at(i).Z;
         }
     }
     return -1;
 }

std::vector<Vector3> GetAllFreePositions(const PlayingField *field) throw(out_of_range)
{
    std::vector<Vector3> ret;

    Vector3 *vec = new Vector3();

    for(int i = 0; i < field->GetFieldSize(); i++)
    {
        for(int j = 0; j < field->GetFieldSize(); j++)
        {
            for(int k = 0; k < field->GetFieldSize(); k++)
            {
                if(field->GetSlot(i,j,k)->Occupation == PlayingField::None)
                {
                    vec->X = i;
                    vec->Y = j;
                    vec->Z = k;
                    ret.push_back(*vec);
                }
            }
        }
    }

    delete(vec);

    return ret;
}

std::string DrawPlayingField(const PlayingField *field)
{
    std::stringstream sStream;

    // iterates through the depth lines
    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        // iterates through the vertical Stacks
        for(int j = 0; j < field->GetFieldSize(); j++)
        {
            // sets the first line
            sStream << "|";

            // iterates through the horizontal lines
            for(int k = 0; k < field->GetFieldSize(); k++)
            {
                switch(field->GetSlot(k, i, j)->Occupation)
                {
                    case PlayingField::None:
                        sStream << " - |";
                        break;
                    case PlayingField::Blue:
                        sStream << " x |";
                        break;
                    case PlayingField::Red:
                        sStream << " o |";
                        break;
                }
            }
            // sets the seperator between the stages
            if(j < field->GetFieldSize() - 1)
            {
                sStream << "     ,     ";
            }
        }

        sStream << endl;
    }

    return sStream.str();

}


bool CheckForWin(const PlayingField *field, PlayingField::OccupationState player, int x, int y, int z) throw(out_of_range)
{
    // will become an enum
    int direction = 0;

    for(direction = 0; direction < 6; direction++)
    {

        bool iterResult = false;

        switch(direction)
        {

        case 0:
                // vertical (z) direction

                for(int i = 0; i < field->GetFieldSize() ;i++)
                {
                    iterResult = field->GetSlot(x,y, i)->Occupation == player;

                    if(!iterResult)
                    {
                        break;
                    }
                }
            break;
        case 1:
                // horizontal (x) direction

                for(int i = 0; i < field->GetFieldSize() ;i++)
                {
                    iterResult = field->GetSlot(i, y, z)->Occupation == player;

                    if(!iterResult)
                    {
                        break;
                    }
                }
            break;
        case 2:
                // depth (y) direction

                for(int i = 0; i < field->GetFieldSize() ;i++)
                {
                    iterResult = field->GetSlot(x, i, z)->Occupation == player;

                    if(!iterResult)
                    {
                        break;
                    }
                }
            break;
        case 3:
                // (x, z) diagonal direction

                for(int i = 0; i < field->GetFieldSize() ;i++)
                {
                    iterResult = field->GetSlot(field->GetFieldSize() - (i + 1),y, i)->Occupation == player;

                    if(!iterResult)
                    {
                        break;
                    }
                }

                if(iterResult)
                {
                    break;
                }

                for(int i = 0; i < field->GetFieldSize() ;i++)
                {
                    iterResult = field->GetSlot(i,y, i)->Occupation == player;

                    if(!iterResult)
                    {
                        break;
                    }
                }
            break;
        case 4:
                // (y, z) diagonal direction

                for(int i = 0; i < field->GetFieldSize() ;i++)
                {
                    iterResult = field->GetSlot(x,field->GetFieldSize() - (i + 1), i)->Occupation == player;

                    if(!iterResult)
                    {
                        break;
                    }
                }

                if(iterResult)
                {
                    break;
                }

                for(int i = 0; i < field->GetFieldSize() ;i++)
                {
                    iterResult = field->GetSlot(x,i, i)->Occupation == player;

                    if(!iterResult)
                    {
                        break;
                    }
                }
            break;
        case 5:
                //  (x, y, z) diagonal direction

                for(int i = 0; i < field->GetFieldSize() ;i++)
                {
                    iterResult = field->GetSlot(field->GetFieldSize() - (i + 1),field->GetFieldSize() - (i + 1), i)->Occupation == player;

                    if(!iterResult)
                    {
                        break;
                    }
                }

                if(iterResult)
                {
                    break;
                }

                for(int i = 0; i < field->GetFieldSize() ;i++)
                {
                    iterResult = field->GetSlot(i,i, i)->Occupation == player;

                    if(!iterResult)
                    {
                        break;
                    }
                }
            break;
        }


        if(iterResult)
        {
            return true;
            break;
        }


    }


return false;

}



bool CheckForWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range)
{
    return CheckPlainLineWins(field, player) || CheckCrossedLineWins(field, player);
}

bool CheckPlainLineWins(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range)
{
    return CheckHorizLineWin(field, player) || CheckVertLineWin(field, player) || CheckDepthLineWin(field, player);
}

bool CheckHorizLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range)
{
    bool iterResult = false;

    // horizontal (x) direction

    // iterates through vertical
    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        // iterates through depth
        for(int j = 0; j < field->GetFieldSize() ;j++)
        {
            // iterates through horizontal
            for(int k = 0; k < field->GetFieldSize() ;k++)
            {
                iterResult = field->GetSlot(k,j,i)->Occupation == player;

                // when a slot is not occupied by player
                if(!iterResult)
                {
                    // fallback
                    break;
                }
            }
            // returns true when all slots in a line return true
            if(iterResult)
            {
                return true;
            }
        }
    }

    return false;
}

bool CheckVertLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range)
{
    bool iterResult = false;

    // iterates through horizontal
    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        // iterates through depth
        for(int j = 0; j < field->GetFieldSize() ;j++)
        {
            // iterates through levels
            for(int k = 0; k < field->GetFieldSize() ;k++)
            {
                iterResult = field->GetSlot(i,j, k)->Occupation == player;

                // when a slot is not occupied by player
                if(!iterResult)
                {
                    break;
                }
            }
            // returns true when all slots in a line return true
            if(iterResult)
            {
                return true;
            }
        }
    }
    return false;
}

bool CheckDepthLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range)
{
    bool iterResult = false;

    // depth (y) direction

    // iterates through levels
    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        // iterates through horizontal
        for(int j = 0; j < field->GetFieldSize() ;j++)
        {
            // iterates through depth
            for(int k = 0; k < field->GetFieldSize() ;k++)
            {
                iterResult = field->GetSlot(j,k,i)->Occupation == player;

                // when a slot is not occupied by player
                if(!iterResult)
                {
                    break;
                }
            }
            // returns true when all slots in a line return true
            if(iterResult)
            {
                return true;
            }
        }
    }

    return false;
}


bool CheckCrossedLineWins(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range)
{
    return CheckCrossPlainLineWin(field, player) || CheckCrossHoriDiagLineWin(field, player) || CheckCrossDepthDiagLineWin(field, player) || CheckCrossDiagLineWin(field, player);
}


bool CheckCrossPlainLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range)
{
    bool iterResult = false;

    // vertical (z) direction
    // iterates through levels
    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        // iterates through horizontal and depth
        for(int j = 0; j < field->GetFieldSize() ;j++)
        {
            iterResult = field->GetSlot(j,j, i)->Occupation == player;
            // when a slot is not occupied by player
            if(!iterResult)
            {
                break;
            }
        }
        // returns true when all slots in a line return true
        if(iterResult)
        {
            return true;
        }
    }

    // vertical (z) direction
    // iterates through levels
    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        // iterates through horizontal and depth
        for(int j = 0; j < field->GetFieldSize() ;j++)
        {
            iterResult = field->GetSlot(field->GetFieldSize() - (j + 1), j, i)->Occupation == player;
            // when a slot is not occupied by player
            if(!iterResult)
            {
                break;
            }
        }
        // returns true when all slots in a line return true
        if(iterResult)
        {
            return true;
        }
    }
    return false;
}

bool CheckCrossHoriDiagLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range)
{
    // (x, y) diagonal direction

    bool iterResult = false;


    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        for(int j = 0; j < field->GetFieldSize(); j++)
        {
            iterResult = field->GetSlot(j, i, j)->Occupation == player;

            // when a slot is not occupied by player
            if(!iterResult)
            {
                break;
            }
        }
        // returns true when all slots in a line return true
        if(iterResult)
        {
            return true;
        }
    }

    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        for(int j = 0; j < field->GetFieldSize(); j++)
        {
            iterResult = field->GetSlot(field->GetFieldSize() - (j + 1), i, j)->Occupation == player;

            // when a slot is not occupied by player
            if(!iterResult)
            {
                break;
            }
        }
        // returns true when all slots in a line return true
        if(iterResult)
        {
            return true;
        }
    }

    return false;
}

bool CheckCrossDepthDiagLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range)
{
    // (y, z) diagonal direction

    bool iterResult = false;

    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        for(int j = 0; j < field->GetFieldSize(); j++)
        {
            iterResult = field->GetSlot(i, j, j)->Occupation == player;

            // when a slot is not occupied by player
            if(!iterResult)
            {
                break;
            }
        }
        // returns true when all slots in a line return true
        if(iterResult)
        {
            return true;
        }
    }

    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        for(int j = 0; j < field->GetFieldSize(); j++)
        {
            iterResult = field->GetSlot(i, field->GetFieldSize() - (j + 1), j)->Occupation == player;

            // when a slot is not occupied by player
            if(!iterResult)
            {
                break;
            }
        }
        // returns true when all slots in a line return true
        if(iterResult)
        {
            return true;
        }
    }

    return false;
}

bool CheckCrossDiagLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range)
{
    //  (x, y, z) diagonal direction

    bool iterResult = false;

    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        iterResult = field->GetSlot(field->GetFieldSize() - (i + 1), i, field->GetFieldSize() - (i + 1))->Occupation == player;

        // when a slot is not occupied by player
        if(!iterResult)
        {
            break;
        }
    }
    // returns true when all slots in a line return true
    if(iterResult)
    {
        return true;
    }

    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        iterResult = field->GetSlot(i, i, field->GetFieldSize() - (i + 1))->Occupation == player;

        // when a slot is not occupied by player
        if(!iterResult)
        {
            break;
        }
    }
    // returns true when all slots in a line return true
    if(iterResult)
    {
        return true;
    }

    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        iterResult = field->GetSlot(field->GetFieldSize() - (i + 1), i, i)->Occupation == player;

        // when a slot is not occupied by player
        if(!iterResult)
        {
            break;
        }
    }
    // returns true when all slots in a line return true
    if(iterResult)
    {
        return true;
    }

    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        iterResult = field->GetSlot(i,i, i)->Occupation == player;

        // when a slot is not occupied by player
        if(!iterResult)
        {
            break;
        }
    }
    // returns true when all slots in a line return true
    if(iterResult)
    {
        return true;
    }

    return false;
}
