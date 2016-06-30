#include "../../include/core/Vector2.h"

Vector2::Vector2()
{
    //ctor
}

Vector2::Vector2(int x, int y)
{
    //ctor

    this->X = x;
    this->Y = y;
}

Vector2::Vector2(const Vector2 &src)
{
    //ctor

    this->X = src.X;
    this->Y = src.Y;
}


bool Vector2::operator==(const Vector2 &v)
{
    return this->X == v.X && this->Y == v.Y;
}
