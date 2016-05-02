#ifndef AI_H
#define AI_H

#include "../include/core/PlayingField.h"
#include "../include/core/SlotVector.h"
#include <stdexcept>

class AI
{
    public:
        AI();
        virtual ~AI();
    protected:
    private:
};

int MiniMax(const PlayingField *field, PlayingField::OccupationState max_Player, PlayingField::OccupationState current_player, SlotVector *choice) throw(out_of_range);

int MiniMax(const PlayingField *field, PlayingField::OccupationState max_Player, PlayingField::OccupationState current_player, int depth, SlotVector *choice) throw(out_of_range);

inline std::vector<SlotVector> GetAllPossiblePosi(const PlayingField *field) throw(out_of_range)
{
    std::vector<SlotVector> ret;

    SlotVector *vec = new SlotVector();

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

#endif // AI_H
