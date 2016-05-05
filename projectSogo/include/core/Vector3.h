#ifndef SLOTVECTOR_H
#define SLOTVECTOR_H

/**
* Defines a structures that encapsulates a position in 3D space
* X is the horizontal value
* Y is the depth value
* Z is the vertical value
*/
struct Vector3
{
    /**
    * Default constructor
    * Initializes X,Y,Z to zero
    */
    Vector3();
    /**
    * constructor
    * @param x will be assigned to X
    * @param y will be assigned to Y
    * @param z will be assigned to Z
    */
    Vector3(int x, int y ,int z);

    int X;
    int Y;
    int Z;
};

#endif // SLOTVECTOR_H
