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
     */
    GameManager();

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
     * @brief SetGameData
     */
    inline void SetGameData(GameData * data)
    {
        this->m_data = data;
        m_endGame = false;
    }

    inline void StartGame()
    {
        m_paused = false;
        m_endGame = false;
    }


    inline void PauseGame()
    {
        m_paused = true;
    }

    inline void SuspendProcessingLoop()
    {
        m_endGame = true;
    }

    /**
     * @brief Stop
     * sets the boolean to end the Main processing thread when the user quits the game
     */
    inline void StopGameManagerThread()
    {
        m_endGame = true;
        m_stopThreadExecution = true;
    }

    /**
     * @brief InputConfirmationDetected
     * @param pos
     */
    inline void InputConfirmationDetected(Vector2 pos)
    {
        playerPosChoice = pos;

        std::stringstream s;
        s << pos.X << " : " << pos.Y;
        Logger::GetLoggerIntance()->LogInfo(s.str(), __FILE__, __LINE__);

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
    void PlayInputErrorSound();

    void PlayInputAcceptSound();

    /**
     * @brief TurnFinished
     * emitted when players turn finishes
     */
    void TurnFinished();
    /**
     * @brief PlayerWon
     * emitted when a player won
     */
    void PlayerWon();

private:
    /**
     * @brief GameLoop
     * processes the game loop with ai and player actions
     */
    void GameLoop();

    void InputRoutine(bool &currentPlayerMoveReady, Vector3 *pos) throw(out_of_range, PlayingField::FieldExeptions);

    bool PlayerInputProcess(Vector3 *pos) throw(out_of_range, PlayingField::FieldExeptions);

    /**
     * @brief AIProcess
     * @param ai to process
     */
    bool AIProcess(Player *player, Vector3 *move);


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
    bool m_paused;

    bool m_endGame;

    /**
     * @brief m_stop
     */
    bool m_stopThreadExecution;
    /**
     * @brief m_playerInputConfirmed
     */
    bool m_playerInputConfirmed;

};




#endif // GAMEMANAGERTHREAD_H
