//
//
//
#pragma once


#include "common.h"

#include <string>
#include <vector>

namespace bluesky
{

class ESPWriter
{
public:
    ESPWriter();

    template<class T> void write(T in);
    void writeField(const std::string& in);
    void writeString(const std::string& in);

    void saveToFile(const std::string& filename);

private:
    std::vector<BYTE> m_data;
};

}
