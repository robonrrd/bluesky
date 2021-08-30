//
//
//

#include "writer.h"

#include <fstream>

namespace bluesky
{

ESPWriter::ESPWriter()
{
    // empty
}

template<class T>
void ESPWriter::write(T in)
{
    BYTE const * p = reinterpret_cast<BYTE const *>(&in);
    for (size_t ii = 0; ii != sizeof(T); ++ii)
    {
        m_data.push_back(p[ii]);
    }
}
template void ESPWriter::write<uint16_t>(uint16_t);
template void ESPWriter::write<int32_t>(int32_t);
template void ESPWriter::write<uint32_t>(uint32_t);
template void ESPWriter::write<uint64_t>(uint64_t);
template void ESPWriter::write<float>(float);
template void ESPWriter::write<double>(double);
template void ESPWriter::write<char>(char);

void ESPWriter::writeString(const std::string& in)
{
    for (size_t ii=0; ii<in.length(); ++ii)
    {
        write<char>(in.at(ii));
    }
    write<char>(0);
}

void ESPWriter::writeField(const std::string& in)
{
    for (size_t ii=0; ii<in.length(); ++ii)
    {
        write<char>(in.at(ii));
    }
    write<uint16_t>(0);
}



void ESPWriter::saveToFile(const std::string& filename)
{
    std::fstream fs;
    fs.open(filename, std::fstream::out | std::fstream::binary);
    fs.write(reinterpret_cast<const char*>(&m_data[0]), m_data.size()*sizeof(BYTE));
    fs.close();
}

}
