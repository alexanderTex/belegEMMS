#include "../include/core/Vector3.h"

const char Vector3::delimiter = '*';

Vector3::Vector3()
{
    //ctor
    this->X = 0;
    this->Y = 0;
    this->Z = 0;
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


std::string Vector3::Serialize(Vector3 &vec)
{
    std::stringstream s;

    s << vec.X << delimiter << vec.Y << delimiter << vec.Z;

    return s.str();
}

Vector3 Vector3::Deserialize(std::string s) throw(DeserializationException)
{
    Vector3 vec;

    std::vector<std::string> elems;

    for(int i = 0; i < 3; i++)
    {
       split(s, delimiter, elems);
    }

    try
    {
        vec.X = std::stoi( elems[0] );
        vec.Y = std::stoi( elems[1] );
        vec.Z =std::stoi( elems[2] );
    }
    catch(std::string invalid_argument)
    {
        Logger::GetLoggerIntance()->LogInfo("Vector3 Deserializierung failed  ", __FILE__, __LINE__);
        throw DESERIALIZATION_FAILED;
    }

    return vec;
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
