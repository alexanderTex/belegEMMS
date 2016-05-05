#ifndef AI_H
#define AI_H

#include "../include/core/PlayingField.h"
#include "../include/core/Vector3.h"
#include <stdexcept>


/**
* Defines an AI-Player
* Future content
* strenght etc.
*
*/
class AI
{
    public:
        AI();
        virtual ~AI();
    protected:
    private:
};


/**
* Calculates the best next move
* @param[in] field current state of the field
* @param max_Player the player for who the algorithm searches a good move
* @param current_Player the player who is currently making a move
* @param[out] choice the best move for max player
* @throw out_of_range
* @return returns the score of the move selected ( 1 : best case, 0 : draw, -1 : worst case )
*/
int MiniMax(const PlayingField *field, PlayingField::OccupationState max_Player, PlayingField::OccupationState current_player, Vector3 *choice) throw(out_of_range);

/**
* Calculates the best next move
* @param[in] field current state of the field
* @param max_Player the player for who the algorithm searches a good move
* @param current_Player the player who is currently making a move
* @param[out] choice the best move for max player
* @throw out_of_range
* @return returns the score of the move selected ( 1 : best case, 0 : draw, -1 : worst case )
*/
int MiniMax(const PlayingField *field, PlayingField::OccupationState max_Player, PlayingField::OccupationState current_player, int depth, Vector3 *choice) throw(out_of_range);

/**
* Returns all none occupied slots
* @param[in] field current state of the field
* @throw out_of_range
* @return return a vector of positions(Vector3)
*/
inline std::vector<Vector3> GetAllPossiblePosi(const PlayingField *field) throw(out_of_range)
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

#endif // AI_H
