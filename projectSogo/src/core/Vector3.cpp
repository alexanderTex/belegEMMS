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

Vector3::Vector3(const Vector3 &src)
{
    this->X = src.X;
    this->Y = src.Y;
    this->Z = src.Z;
}

bool Vector3::operator==(const Vector3 &v2)
{
    return this->X == v2.X && this->Y == v2.Y && this->Z == v2.Z;
}

std::ostream &operator<< (std::ostream &out, const Vector3 &vec)
{
    out << "x = " << vec.X << ", y = " << vec.Y << ", z = " << vec.Z;
    return out;
}
