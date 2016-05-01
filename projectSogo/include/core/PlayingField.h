#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <stdio.h>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>


using namespace std;


/**
*    Defines the Properties of a Playingfield
*
*/
class PlayingField
{
    public:
        enum FieldExeptions
        {
            Occupied,
        };

        /**
        *   Defines the States a slot can be in
        */
        enum OccupationState
        {
            None,
            Red,
            Blue,
        };

        struct Slot
        {
            PlayingField::OccupationState Occupation;

            Slot();
            Slot(PlayingField::OccupationState occupation);
        };


        /**
        *
        */
        PlayingField(int fieldSize = 4);

        /**
        *
        */
        PlayingField(const PlayingField *field);


        /**
        *   Returns the slot at pos.x (horizontally)
        *                       pos.y (Vertically)
        *                       pos.z ("forwardly")
        *   @throw out_of_range if value is higher than fieldsize
        */
        Slot* GetSlot(int x, int y, int z) const throw (out_of_range);

        inline int GetFieldSize() const
        {
            return m_FieldSize;
        }

        /**
        *   Sets the occupationState of the Slot at pos to id
        *   @throw out_of_range if value is higher than fieldsize
        */
        void OccupySlot(int x, int y, int z, OccupationState id) throw (out_of_range, FieldExeptions);
    protected:
    private:

        int m_FieldSize;

        // x ( horizontal ; layer 0 )
        // y ( depth ; layer 1 )
        // z ( vertical ; layer 2 )
        vector<vector<vector<Slot*> > > m_slots;

};

/**
* Draws the PlayingField in a console friendly fashion
*
*/
std::string DrawPlayingField(const PlayingField *field);


/**
*   Searches for a win condition in the Field
*   with a given last move to to optimize
*   Currently not in use!!!
*/
bool CheckForWin(const PlayingField *field, PlayingField::OccupationState player, int x, int y, int z) throw(out_of_range);

/**
*   Searches for a win condition in the Field
*   no optimization
*/
bool CheckForWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
* Checks all Plain line win conditions
*/
bool CheckPlainLineWins(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
* Checks all Cross line win conditions
*/
bool CheckCrossedLineWins(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
*   Searches for a win condition in Horizontal lines
*/
bool CheckHorizLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
*   Searches for a win condition in Vertical lines
*/
bool CheckVertLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
*   Searches for a win condition in Depth lines
*/
bool CheckDepthLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
*   Searches for a win condition in Plain Diag lines
*/
bool CheckPlainDiagLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
*   Searches for a win condition in HorizontalDiagonal lines
*/
bool CheckCrossHoriDiagLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
*   Searches for a win condition in DepthDiagonal lines
*/
bool CheckCrossDepthDiagLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);

/**
*   Searches for a win condition in CrossedDiagonal lines
*/
bool CheckCrossDiagLineWin(const PlayingField *field, PlayingField::OccupationState player) throw(out_of_range);


#endif // PLAYINGFIELD_H
