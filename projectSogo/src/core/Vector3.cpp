#include "../include/core/Vector3.h"

Vector3::Vector3()
{
    //ctor
}

Vector3::Vector3(int x, int y, int z)
{
    //ctor

    this->X = x;
    this->Y = y;
    this->Z = z;
}

bool Vector3::operator==(const Vector3 &v2)
{
    return this->X == v2.X && this->Y == v2.Y && this->Z == v2.Z;
}
