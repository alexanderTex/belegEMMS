#ifndef STRINGUTLITIES_H
#define STRINGUTLITIES_H

#include <string>
#include <sstream>
#include <vector>

// gefunden auf stackoverflow
inline void split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


#endif // STRINGUTLITIES_H
