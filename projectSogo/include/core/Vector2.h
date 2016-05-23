#ifndef VECTOR2_H
#define VECTOR2_H

#include <ostream>

/**
* Defines a structures that encapsulates a position in 2D space
* X
* Y
*/
struct Vector2
{
    /**
    * Default constructor
    * Initializes X,Y to zero
    */
    Vector2();
    /**
    * constructor
    * @param x will be assigned to X
    * @param y will be assigned to Y
    */
    Vector2(int x, int y);

    int X;
    int Y;

    bool operator==(const Vector2 &v);

};

inline std::ostream &operator<< (std::ostream &out, const Vector2 &vec)
{
    out << "x = " << vec.X << ", y = " << vec.Y;
    return out;
}

#endif // VECTOR2_H
