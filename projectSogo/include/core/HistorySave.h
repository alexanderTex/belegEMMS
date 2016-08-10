#ifndef HISTORYSAVE_H
#define HISTORYSAVE_H

#include <vector>
#include "Vector3.h"
#include "Player.h"
#include "../Subject.h"

/**
 * @brief The HistorySave class.
 *
 * @author Nils Brandt
 * @author Alexander Luedke
 *
 * @date 08. August 2016
 *
 * @version 1.0
 * Add Documentation
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

        inline static string Serialize(const Move& save)
        {
            stringstream s;

            s << Vector3::Serialize(*save.position) << delimiter << Player::Serialize(*save.player);

            return s.str();
        }

        inline static bool Deserialize(string str, Move *m)
        {
            std::vector<string> elems;

            split(str, delimiter, elems);

            bool worked = true;

            Logger::GetLoggerIntance()->LogInfo(str, __FILE__, __LINE__);

            Vector3 *vec;
            if(!Vector3::Deserialize(elems.at(0), vec))
            {
                worked = false;
            }


            Player *player;
            if(!Player::Deserialize(elems.at(1), player))
            {
                Logger::GetLoggerIntance()->LogInfo("Move deserialize Player Failed", __FILE__, __LINE__);
                worked = false;
            }

            if(worked)
                m = new Move(vec, player);

            return worked;
        }

        /**
         * @brief position
         */
        Vector3 *position;
        /**
         * @brief player
         */
        Player *player;

    private :
        const static char delimiter = ',';

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
     * @brief AddMove
     * @param move
     */
    void AddMove(Move *move);

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


    static string Serialize(const HistorySave& save);

    static bool Deserialize(string str, HistorySave *save);



private:
    const static char delimiter = '#';

    /**
     * @brief m_pastMoves
     */
    std::vector< Move * > *m_pastMoves;
};

#endif // HISTORYSAVE_H
