#include "../../include/core/PlayingField.h"

PlayingField::Slot::Slot()
{
    //ctor
    this->Occupation = None;
}


PlayingField:: PlayingField(int fieldSize)
{
    //ctor

    this->m_FieldSize = fieldSize;


    // fills the Field
    //fills the field's horizontal lines
    for(int i = 0; i < this->m_FieldSize; i++)
    {
        this->m_slots.push_back(*(new vector< vector<Slot*> >()));

        //fills the field's depth lines
        for(int j = 0; j < this->m_FieldSize; j++)
        {
            this->m_slots.at(i).push_back(*(new vector<Slot*>()));

            //fills the field's Vertical lines
            for(int k = 0; k < this->m_FieldSize; k++)
            {
                this->m_slots.at(i).at(j).push_back(new Slot());
            }
        }
    }

}

PlayingField::Slot* PlayingField::GetSlot(int x, int y, int z) const throw(out_of_range)
{
    return this->m_slots.at(x).at(y).at(z);
}

 void PlayingField::OccupySlot(int x, int y, int z, PlayingField::OccupationState id) throw(out_of_range, FieldExeptions)
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


std::string DrawPlayingField(const PlayingField *field)
{
    std::stringstream sStream;

    // iterates through the Vertcal lines
    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        // iterates through the depth Stacks
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
