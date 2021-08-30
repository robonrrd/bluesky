//
#include <array>
#include <vector>

namespace bluesky
{

/// Data structures
///
struct heightmap
{
    float offset; // baked into data, but needed for conversion to VGHT
    std::array< std::array<float, 33>, 33> data;
};

// TES data structures
struct VGHT
{
    float offset;
    std::vector<char> data; // points to 1089 signed bytes
};


struct VNML // normals
{
    std::array<char, 3267> data; // (33x33 x 3 bytes)
};


/// Functions
///
VGHT VGHTfromHeightmap(const heightmap& hm);
VNML VNMLfromHeightmap(const heightmap& hm);

heightmap heightmapFromVGHT(const VGHT& vght);


} // namespace bluesky
