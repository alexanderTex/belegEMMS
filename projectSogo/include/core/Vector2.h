#ifndef VECTOR2_H
#define VECTOR2_H

#include <ostream>
#include <sstream>

/**
 * @brief Defines a structures that encapsulates a position in 2D space.
 * X is the horizontal value
 * Y is the depth value
 *
 *  @author Nils Brandt
 * @author Alexander Luedke
 *
 * @date 08. August 2016
 *
 * @version 1.0
 * Add Documentation
*/
struct Vector2
{
    /**
    * Default constructor
    * Initializes X,Y to zero
    */
    Vector2();

    Vector2(const Vector2 &src);

    /**
    * constructor
    * @param x will be assigned to X
    * @param y will be assigned to Y
    */
    Vector2(int x, int y);

    inline std::string Serialize()
    {
        std::stringstream s;

        //s <<
    }

    inline void Deserialize()
    {
        std::stringstream s;

        //s <<
    }


    /**
     * @brief X x value
     */
    int X;
    /**
     * @brief Y y value
     */
    int Y;

    bool operator==(const Vector2 &v);

};

std::ostream &operator<< (std::ostream &out, const Vector2 &vec);

#endif // VECTOR2_H
