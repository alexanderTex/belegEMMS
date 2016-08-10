#ifndef AI_H
#define AI_H

#include "../include/core/PlayingField.h"
#include "../include/core/Vector3.h"
#include <stdexcept>

/**
 * @brief The AI class. Defines an AI-Player Future content strenght etc.
 *
 * @author Nils Brandt
 * @author Alexander Luedke
 *
 * @date 08. August 2016
 *
 * @version 1.0
 * Add Documentation
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
* Calculates the best move for the next turn
* @param[in] field current state of the field
* @param max_Player the player for who the algorithm searches a good move
* @param current_Player the player who is currently making a move
* @param[out] choice the best move for max player
* @throw out_of_range
* @return returns the score of the move selected ( 1 : best case, 0 : draw, -1 : worst case )
*/
int MiniMax(const PlayingField *field, PlayingField::OccupationState max_Player, PlayingField::OccupationState current_player, Vector3 *choice) throw(out_of_range);

/**
* Calculates the best next for the next turn
* @param[in] field current state of the field
* @param max_Player the player for who the algorithm searches a good move
* @param current_Player the player who is currently making a move
* @param depth how many moves in advance will be checked
* @param[out] choice the best move for max player
* @throw out_of_range
* @return returns the score of the move selected ( 1 : best case, 0 : draw, -1 : worst case )
*/
int MiniMax(const PlayingField *field, PlayingField::OccupationState max_Player, PlayingField::OccupationState current_player, int depth, Vector3 *choice) throw(out_of_range);



#endif // AI_H
