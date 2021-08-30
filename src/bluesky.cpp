//
//

#include "common.h"
#include "writer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#if 0
typedef unsigned char BYTE;
std::vector<BYTE> readFile(const char* filename)
{
    // open the file:
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);
    if (!file.good())
    {
        std::cout << std::string(filename) << " cannot be opened" << std::endl;
        return {};
    }

    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<BYTE> fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);
    return fileData;
}

int
main()
{
    std::string filename("/home/jeffreys/src/github/mine/bluesky/data/test_island.esp");

    // open file
    std::vector<BYTE> filedata = readFile(filename.c_str());
    std::cout << "File is " << filedata.size() << " bytes long" << std::endl;

    // read name 'TES4'
}
#endif

int
main()
{
    using bluesky::ESPWriter;


    // testing data
    std::string author("Bluesky");
    std::string description("Procedurally generated island");
    std::vector<std::string> master_files = {"Skyrim.esm", "Update.esm"};
    int32_t num_records_and_groups = 1;
    //

    ESPWriter writer;

    // Write TES4 header record
    writer.writeField( "TES4" );

    // write header
    writer.writeField( "HEDR" );
    writer.write<float>( 1.7 ); // version
    writer.write<int32_t>( num_records_and_groups );
    writer.write<uint64_t>( 0 ); // next available object ID

    if (author.length() > 0)
    {
        writer.writeField( "CNAM" );
        writer.writeString( author );
    }
    if (description.length() > 0)
    {
        writer.writeField( "SNAM" );
        writer.writeString( description );
    }
    for (const auto& ss : master_files)
    {
        writer.writeField( "MAST" );
        writer.writeString( ss );
        writer.writeField( "DATA" );
        writer.write<uint64_t>( 0 );
    }

    writer.writeField("INTV");
    writer.write<uint32_t>(0);

    /// Write top groups

    // WRLD
    writer.writeField("GRUP");
    size_t sg_sz = 33;  // TEMP!
    const uint32_t sz =
        4 + // GRUP
        4 + // uint32 size
        4 + // label (4xchar)
        4 + // int32 group type
        2 + // uint16 timestamp
        2 + // uint16 verson control
        4 + // unknown - zero in the case of top level groups
        sg_sz; // records and subgroup sizes


    // LAND record

    uint32_t land_sz = 0; // size of data field
    uint32_t land_flags =
        0x200 & // ESL
        0x8000 // visible when distant (maybe not needed?)
        ;

    writer.writeField( "LAND" );
    writer.write<uint32_t>(land_sz);
    writer.write<uint32_t>(land_flags); // flags
    writer.write<uint32_t>(0); // record (form) identifier
    writer.write<uint16_t>(0); // timestamp
    writer.write<uint16_t>(0); // version control
    writer.write<uint16_t>(0); // internal version of record
    writer.write<uint16_t>(0); // unknown

    // land data in fields

#if 0
    writer.writeField("GRUP");
    const uint32_t sz =
        4 + // GRUP
        4 + // uint32 size
        4 + // label (4xchar)
        4 + // int32 group type
        2 + // uint16 timestamp
        2 + // uint16 verson control
        4 + // unknown - zero in the case of top level groups

    writer.write<uint32_t>(sz); // size of entire group
    writer.writeField("LAND"); //   ..LAND
    writer.write<int32_t>(0); // label - top record, of type above
#endif

    writer.saveToFile( "test.bin" );
}


