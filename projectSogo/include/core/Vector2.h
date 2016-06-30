#ifndef VECTOR2_H
#define VECTOR2_H

#include <ostream>

/**
* @brief Defines a structures that encapsulates a position in 2D space
* X is the horizontal value
* Y is the depth value
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

inline std::ostream &operator<< (std::ostream &out, const Vector2 &vec)
{
    out << "x = " << vec.X << ", y = " << vec.Y;
    return out;
}

#endif // VECTOR2_H
