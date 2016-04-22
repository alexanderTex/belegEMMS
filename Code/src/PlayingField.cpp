#include "PlayingField.h"

PlayingField::Slot::Slot()
{
    //ctor
    this->Occupation = None;
}


PlayingField:: PlayingField(int fieldSize)
{
    //ctor

    this->m_FieldSize = fieldSize;

    for(int i = 0; i < this->m_FieldSize; i++)
    {

        this->m_slots.push_back(*(new vector< vector<Slot*> >()));

        for(int j = 0; j < this->m_FieldSize; j++)
        {
            this->m_slots.at(i).push_back(*(new vector<Slot*>()));

            for(int k = 0; k < this->m_FieldSize; k++)
            {
                this->m_slots.at(i).at(j).push_back(new Slot());
            }
        }
    }

}

PlayingField::Slot* PlayingField::GetSlot(int x, int y, int z) const throw(out_of_range)
{
    return this->m_slots.at(x).at(z).at(y);
}

 void PlayingField::OccupySlot(int x, int y, int z, PlayingField::OccupationState id) throw(out_of_range)
 {
    this->GetSlot(x,y,z)->Occupation = id;
 }


std::string DrawPlayingField(const PlayingField *field)
{
    std::stringstream sStream;


    for(int i = 0; i < field->GetFieldSize() ;i++)
    {
        for(int j = 0; j < field->GetFieldSize(); j++)
        {
            sStream << "|";
            for(int k = 0; k < field->GetFieldSize(); k++)
            {
                switch(field->GetSlot(k, j, i)->Occupation)
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

            if(!((j +1) >= field->GetFieldSize()))
            {
                sStream << "     ,     ";
            }
}

        sStream << endl;
    }

    return sStream.str();

}
