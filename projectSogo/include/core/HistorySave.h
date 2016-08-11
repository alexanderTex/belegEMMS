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
        Move()
        {
            this->position = new Vector3();
            this->player = new Player();
        }


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

        inline static Move *Deserialize(string str) throw(DeserializationException)
        {
            std::vector<string> elems;

            split(str, delimiter, elems);

            Vector3 vec = Vector3::Deserialize(elems.at(0));


            Player *player = Player::Deserialize(elems.at(1));

            Move *m = new Move(new Vector3(vec), player);

            return m;
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

    static HistorySave *Deserialize(string str) throw(DeserializationException);



private:
    const static char delimiter = '#';

    /**
     * @brief m_pastMoves
     */
    std::vector< Move * > *m_pastMoves;
};

#endif // HISTORYSAVE_H
