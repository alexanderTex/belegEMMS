#ifndef GAMEMANAGERTHREAD_H
#define GAMEMANAGERTHREAD_H

#include <QThread>
#include "GameData.h"
#include "AI.h"
#include "Player.h"

/**
 * @brief The GameManager class
 * Handles the game loop logic in a thread
 */
class GameManager : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief The AI struct
     * Contains a reference to a player which is of type ai
     * and if the ai player has calculated its next move
     */
    struct AIPlayer
    {
        /**
         * @brief AI
         * @param player
         * @param hasMove
         */
        AIPlayer(const Player *player, bool hasMove = false)
        {
            this->player = player;
            this->hasMove = hasMove;
        }
        /**
         * @brief player
         */
        const Player *player;
        /**
         * @brief hasMove
         */
        bool hasMove;
    };

    /**
     * @brief GameManager
     * @param data
     */
    GameManager(GameData *data);

    /**
     * @brief ~GameManager
     */
    virtual ~GameManager();

    /**
     * @brief run
     * override of the QThread run
     */
    virtual void run();

    /**
     * @brief GetGameData
     * @return
     */
    inline const GameData* GetGameData() const
    {
        return this->m_data;
    }

    /**
     * @brief Stop
     * sets the boolean to end the game logic loop
     */
    inline void Stop()
    {
        m_stop = true;
    }

    /**
     * @brief InputConfirmationDetected
     * @param pos
     */
    inline void InputConfirmationDetected(Vector2 pos)
    {
        playerPosChoice = pos;
        m_playerInputConfirmed = true;
    }

    /**
     * @brief Tries to Occupy the given position , adds the move to the history, checks if the player won ( return true if won),
     * switches currentplayer, and sends out event that a move is done
     * @param pos
     * @return true if the player just won the game
     */
    bool MakeMove(Vector3 pos) throw(PlayingField::FieldExeptions, std::out_of_range);   

signals:
    /**
     * @brief InputMade
     */
    void TurnFinished();
    /**
     * @brief PlayerWon
     */
    void PlayerWon();

private:
    /**
     * @brief GameLoop
     */
    void GameLoop();

    void AIProcess(AIPlayer *ai);


    /**
     * @brief playerPosChoice
     */
    Vector2 playerPosChoice;
    /**
     * @brief m_data
     */
    GameData *m_data;
    /**
     * @brief m_stop
     */
    bool m_stop;
    /**
     * @brief m_playerInputConfirmed
     */
    bool m_playerInputConfirmed;

};




#endif // GAMEMANAGERTHREAD_H
