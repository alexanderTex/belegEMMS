#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <stdexcept>

#include "PlayingField.h"
#include "Vector2.h"
#include "Logger.h"
#include "../include/Subject.h"
#include "Player.h"
#include "AI.h"
#include "HistorySave.h"

/**
 * @brief The GameData class
 * Holds a reference to the PlayingField
 * to both players and which one is the currentplayer
 *
 * @author Nils Brandt
 * @author Alexander Luedke
 *
 * @date 08. August 2016
 *
 * @version 1.0
 * Add Documentation
 */
class GameData
{
public:
    /**
     * @brief The GameDataException enum
     * thrown PlayerNotInTheGame when the player is not a player of the game
     */
    enum GameDataException
    {
        PlayerNotInTheGame,
    };

    /**
     * @brief GameData Default Constructor
    */
    GameData();

    /**
     * @brief GameData Initializes a Gamedata object with a given PlayingField
     * both players and the designated starting player
     * @param field given PlayingField
     * @param p1 player1
     * @param p2 player2
     * @param startingPlayer the beginning player
     */
    GameData(PlayingField *field, Player *p1, Player *p2, Player *startingPlayer);    


    // constructor with historysave*
    /**
     * @brief GameData Copy Constructor
     * @param src Gamedata to copy from
     */
    GameData(const GameData &src);

    /**
     * @brief ~GameData
     */
    virtual ~GameData();

    /**
     * @brief GetField
     * @return
     */
    const PlayingField *GetField() const;

    /**
     * @brief GetPlayers
     * @return
     */
    std::vector<const Player*> *GetPlayers() const;

    /**
     * @brief GetPlayer1
     * @return
     */
    Player *GetPlayer1() const;

    /**
     * @brief GetPlayer2
     * @return
     */
    Player *GetPlayer2() const;

    /**
     * @brief GetCurrentPlayer
     * @return
     */
    Player *GetCurrentPlayer() const;

    /**
     * @brief GetLastMove
     * @return
     */
    Vector3 GetLastMove() const;

    /**
     * @brief GetOpponent
     * @param p
     * @return
     * throws GamedataException if the given player p is not part of the game
     */
    const Player *GetOpponent(const Player *p) const throw(GameDataException);

    /**
     * @brief GetHistory
     * @return
     */
    const HistorySave *GetHistory() const;

    /**
     * @brief OccupySlot
     * occupies slotint playingfield and adds the move to the move history
     * @param x horizontal coordinate
     * @param y vertical coordinate
     * @param z depth coordinate
     * @param playerColor
     * throws out_of_range if the x,y or z is out of the range of the playingfield
     * throws FieldException if occupying the slot in Playingfield failed
     */
    void OccupySlot(int x, int y, int z, PlayingField::OccupationState playerColor) throw(out_of_range, PlayingField::FieldExeptions);

    /**
     * @brief SwitchPlayer
     * switch currentplayer to other player
     */
    void SwitchPlayer();

    static string Serialize(const GameData& data);


    static GameData *Deserialize(std::string str) throw(DeserializationException);


private:
     const static char delimiter;

     /**
      * @brief GameData Initializes a Gamedata object with a given PlayingField
      * both players and the designated starting player
      * @param field given PlayingField
      * @param p1 player1
      * @param p2 player2
      * @param startingPlayer the beginning player
      * @param historySave past history of the game
      */
     GameData(PlayingField *field, Player *p1, Player *p2, Player *startingPlayer, HistorySave *historySave);

    /**
     * @brief m_field
     */
    PlayingField *m_field;
    /**
     * @brief m_player1
     */
    Player *m_player1;
    /**
     * @brief m_player2
     */
    Player *m_player2;
    /**
     * @brief m_currentPlayer
     */
    Player *m_currentPlayer;
    /**
     * @brief m_history
     */
    HistorySave *m_history;
};

#endif // GAMEDATA_H
