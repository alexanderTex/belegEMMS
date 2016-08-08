#ifndef HISTORYSAVE_H
#define HISTORYSAVE_H

#include <vector>
#include "Vector3.h"
#include "Player.h"
#include "../Subject.h"

/**
 * @brief The HistorySave class
 */
class HistorySave
{

    /**
     * @brief The Move struct
     */
    struct Move
    {
        /**
         * @brief Move
         * @param pos
         * @param player
         */
        Move(Vector3 *pos, Player *player)
        {
            this->position = pos;
            this->player = player;
        }

        /**
         * @brief Move
         * @param src
         */
        Move(const Move* src);


        virtual ~Move();

        /**
         * @brief position
         */
        Vector3 *position;
        /**
         * @brief player
         */
        Player *player;
    };

public:
    /**
     * @brief HistorySave
     */
    HistorySave();
    /**
     * @brief HistorySave
     * @param src
     */
    HistorySave(const HistorySave &src);

    ~HistorySave();

    /**
     * @brief AddMove
     * @param pos
     * @param player
     */
    void AddMove(Vector3 pos, Player player);
    /**
     * @brief RevertLast
     */
    void RevertLast();

    /**
     * @brief GetMoveCount
     * @return
     */
    int GetMoveCount() const;

    /**
     * @brief GetMove
     * @param number
     * @return
     */
    const Move *GetMove(int number) const throw(out_of_range);

    /**
     * @brief GetLastMove
     * @return
     */
    const Move *GetLastMove() const throw(out_of_range);

private:
    /**
     * @brief m_pastMoves
     */
    std::vector< Move * > *m_pastMoves;
};

#endif // HISTORYSAVE_H
