#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <stdio.h>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include "../include/core/Vector3.h"


using namespace std;


/**
* @brief Defines the Properties of a Playingfield
* Which is a 3 dimensional Grid
* Containing Slots
* Slots can be occupied by players
*/
class PlayingField
{
    public:
        /**
        * Is thrown when in an Error in Playingfield
        * Occupied when already occupied by other player
        * PositionNotAvailable when position is under current fieldstate not valid for occupation
        */
        enum FieldExeptions
        {
            OCCUPIED,
            POSITION_NOT_AVAILABLE,
            NO_SPACE_ANYMORE,
        };

        /**
        * Defines the States a slot can be in
        */
        enum OccupationState
        {
            NONE,
            RED,
            BLUE,
        };

        /**
        * Defines a Gridspace in a Sogo Playingfield
        * It contains the occupationstate of this position in the grid
        *
        */
        struct Slot
        {
            /**
            * The current occupation state
            */
            PlayingField::OccupationState Occupation;

            /**
            * Default constructor for a Slot
            * Occupation will be set to None
            */
            Slot();
            /**
            * constructor
            *
            */
            Slot(PlayingField::OccupationState occupation);
        };


        /**
        * constructor
        * generates a Playingfield with (fieldsize x fieldsize x fieldsize)
        * @param fieldSize (default value = 4)
        */
        PlayingField(int fieldSize = 4);

        /**
        * Copy constructor
        */
        PlayingField(const PlayingField &field);

        /**
        * Destructor clears the field
        */
        ~PlayingField();


        /**
        * Returns the slot at pos.x (horizontally)
        *                       pos.y (Vertically)
        *                       pos.z ("forwardly")
        * @throw out_of_range if value is higher than fieldsize
        */
        Slot* GetSlot(int x, int y, int z) const throw (out_of_range);

        /**
        * Getter for fieldSize
        * @return returns the fieldsize
        */
        inline int GetFieldSize() const
        {
            return m_fieldSize;
        }

        /**
        * Sets the occupationState of the Slot at pos(x,y,z) to id
        * @param x horizontal value
        * @param y depth value
        * @param z vertical value
        * @param id occupationstate for assignment
        * @throw out_of_range if value is higher than fieldsize
        * @throw FieldException if Slot is already occupied by other player
        */
        void OccupySlot(int x, int y, int z, OccupationState id) throw (out_of_range, FieldExeptions);

        /**
        * Sets the occupationState of the Slot at pos(x,y,z) to id
        * @param pos
        * @param id occupationstate for assignment
        * @throw out_of_range if value is higher than fieldsize
        * @throw FieldException if Slot is already occupied by other player
        */
        void OccupySlot(Vector3 pos, PlayingField::OccupationState id) throw(out_of_range, FieldExeptions);

        bool IsPositionAvailable(int x, int y, int z) const;
    protected:
    private:
        /**
         * @brief m_fieldSize
         */
        int m_fieldSize;

        //
        /**
         * @brief m_slots
         *  x ( horizontal ; layer 0 )
         *  y ( depth ; layer 1 )
         *  z ( vertical ; layer 2 )
         */
        vector<vector<vector<Slot*> *> *> *m_slots;

};



/**
* Returns all positions that are available by
* the game rules
* @param[in] field current state of the field
* @throw out_of_range
* @return return a vector of positions(Vector3)
*/
std::vector<Vector3> *GetAvailablePositions(const PlayingField *field) throw(out_of_range);

int GetAvailablePosition(int x, int y, const PlayingField *field) throw(out_of_range, PlayingField::FieldExeptions);

/**
* Returns all none occupied slots
* @param[in] field current state of the field
* @throw out_of_range
* @return return a vector of positions(Vector3)
*/
std::vector<Vector3> GetAllFreePositions(const PlayingField *field) throw(out_of_range);


/**
* Converts the PlayingField into a console friendly fashion
* @param[in] field  PlayingField to display
* @return drawn PlayingField
*/
std::string DrawPlayingField(const PlayingField *field);


/**
* NOT YET FINISHED!!!
* Searches for a win condition in the Field
* with a given last move
* to optimize (Not implemented yet)
* @param[in] field to check
* @param player player to check winCondition
* @param x last changed position in grid
* @param y last changed position in grid
* @param z last changed position in grid
* @throw out_of_range
* @return true if player won
*/
bool CheckForWin(const PlayingField *field, PlayingField::OccupationState player, int x, int y, int z) throw(out_of_range);

void GetAllWinPositions(const PlayingField *field, std::vector<Vector3> *positions) throw(out_of_range);


/**
* Searches for a win condition in the Field
* with a given last move to to optimize
* @param[in] field to check
* @param player player to check winCondition
* @throw out_of_range
* @return true if player won
*/
bool CheckForWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);


/**
* Checks all Plain lines for win conditions
* @param[in] field to check
* @param player player to check winCondition
* @throw out_of_range
* @return true if player won
*/
bool CheckPlainLineWins(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
* Searches for a win condition in Horizontal lines
* @param[in] field to check
* @param player player to check winCondition
* @throw out_of_range
* @return true if player won
*/
bool CheckHorizLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
* Searches for a win condition in Vertical lines
* @param[in] field to check
* @param player player to check winCondition
* @throw out_of_range
* @return true if player won
*/
bool CheckVertLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
* Searches for a win condition in Depth lines
* @param[in] field to check
* @param player player to check winCondition
* @throw out_of_range
* @return true if player won
*/
bool CheckDepthLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);




/**
* Checks all Cross line win conditions
* @param[in] field to check
* @param player player to check winCondition
* @throw out_of_range
* @return true if player won
*/
bool CheckCrossedLineWins(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
* Searches for a win condition in Plain Diag lines
* @param[in] field to check
* @param player player to check winCondition
* @throw out_of_range
* @return true if player won
*/
bool CheckCrossPlainLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
* Searches for a win condition in HorizontalDiagonal lines from Bottom left to top right
* (x, y)
* @param[in] field to check
* @param player player to check winCondition
* @throw out_of_range
* @return true if player won
*/
bool CheckCrossHoriDiagLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
* Searches for a win condition in DepthDiagonal lines
* (y, z)
* @param[in] field to check
* @param player player to check winCondition
* @throw out_of_range
* @return true if player won
*/
bool CheckCrossDepthDiagLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
* Searches for a win condition in CrossedDiagonal lines
* (x, y, z)
* @param[in] field to check
* @param player player to check winCondition
* @throw out_of_range
* @return true if player won
*/
bool CheckCrossDiagLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);


#endif // PLAYINGFIELD_H
