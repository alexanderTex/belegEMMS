#ifndef SLOTVECTOR_H
#define SLOTVECTOR_H

#include <sstream>
#include <ostream>
#include <vector>
#include <string>
#include "stringutlities.h"
#include "Logger.h"

/**
 * @brief Defines a structures that encapsulates a position in 3D space.
 * X is the horizontal value
 * Y is the depth value
 * Z is the vertical value
 *
 * @author Nils Brandt
 * @author Alexander Luedke
 *
 * @date 08. August 2016
 *
 * @version 1.0
 * Add Documentation
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

    /**
     * @brief Vector3
     * @param src
     */
    Vector3(const Vector3 &src);


    static std::string Serialize(Vector3 &vec);

    static Vector3 Deserialize(std::string s) throw(DeserializationException);



    /**
     * @brief X
     */
    int X;
    /**
     * @brief Y
     */
    int Y;
    /**
     * @brief Z
     */
    int Z;

    bool operator==(const Vector3 &v2);

private:
    const static char delimiter;

};



std::ostream &operator<< (std::ostream &out, const Vector3 &vec);

#endif // SLOTVECTOR_H
