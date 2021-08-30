//
//

#include "generator.h"

#include <array>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdio.h>


void print_heightmap(const bluesky::heightmap& hm)
{
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "  Global offset = " << hm.offset << std::endl;
    for (size_t rr=0; rr<5; ++rr)
    {
        std::cout << "  ";
        for (size_t cc=0; cc<5; ++cc)
        {
            std::cout << hm.data[rr][cc] << "   ";
        }
        std::cout << std::endl;
    }
}


int
main()
{
    using namespace bluesky;

    // make a random heightfield
    heightmap hm;
    hm.offset = 16.0f;
    for (size_t rr=0; rr<33; ++rr)
        for (size_t cc=0; cc<33; ++cc)
        {
            float value = 45 - 2*sqrt( (rr-16)*(rr-16) + (cc-16)*(cc-16));
            hm.data[rr][cc] = hm.offset + (char) value;
        }

    std::cout << "Input: [0-4, 0-4]" << std::endl;
    print_heightmap(hm);
    std::cout << std::endl;

    // heightmap -> VGHT
    VGHT vght = VGHTfromHeightmap(hm);

    // VGHT -> heightmap
    heightmap hm2 = heightmapFromVGHT(vght);

    std::cout << "Output: [0-4, 0-4]" << std::endl;
    print_heightmap(hm2);
    std::cout << std::endl;

    // Compare
    float sum = 0.0f;
    for (size_t rr=0; rr<33; ++rr)
        for (size_t cc=0; cc<33; ++cc)
            sum+= fabs(hm.data[rr][cc] - hm2.data[rr][cc]);
    std::cout << sum << " total error. Avg. of " << sum/(33*33) << std::endl;

}
