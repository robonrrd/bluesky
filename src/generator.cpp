//
#include "generator.h"

#include <array>
#include <math.h>
#include <stdio.h>


namespace bluesky
{

VGHT VGHTfromHeightmap(const heightmap& hm)
{
    VGHT vght;
    vght.data.resize(33*33);

    float offset = 0.0f;
    for (size_t rr=0; rr<33; ++rr)
    {
        float row_offset = 0;
        for (size_t cc=0; cc<33; ++cc)
        {
            float value = hm.data[rr][cc] - hm.offset;
            vght.data[rr*33+cc] = value - offset - row_offset;

            if (cc == 0)
            {
                offset += vght.data[rr*33+cc];
            }
            else
            {
                row_offset += vght.data[rr*33+cc];
            }
        }
    }

    vght.offset = hm.offset / 8.0f;
    return vght;
}

heightmap heightmapFromVGHT(const VGHT& vght)
{
    heightmap height_map;

    float offset = vght.offset * 8.0f;
    height_map.offset = offset;
    float row_offset = 0;
    for (int i = 0; i < 1089; i++)
    {
        float value = vght.data[i]; // signed byte, each unit equals 8 game units

        int r = i / 33;
        int c = i % 33;

        if (c == 0) // first column value controls height for all remaining points in cell
        {
            row_offset = 0;
            offset += value;
        }

        else // other col values control height of all points in the same row
        {
            row_offset += value;
        }

        height_map.data[c][r] = offset + row_offset;
    }

    return height_map;
}


VNML VNMLfromHeightmap(const heightmap& hm)
{
    VNML vnml;

    float R, L, T, B;
    size_t count = 0;
    for (size_t rr=0; rr<33; ++rr)
    {
        for (size_t cc=0; cc<33; ++cc)
        {
            if (rr == 0)
                B = hm.data[rr][cc];
            else
                B = hm.data[rr-1][cc];

            if (rr == 32)
                T = hm.data[rr][cc];
            else
                T = hm.data[rr+1][cc];

            if (cc == 0)
                L = hm.data[rr][cc];
            else
                L = hm.data[rr][cc-1];

            if (cc == 32)
                R = hm.data[rr][cc];
            else
                R = hm.data[rr][cc+1];

            float x = (R-L)/2.0;
            float y = (B-T)/2.0;
            float z = 1.0f;
            float dd = sqrt(x*x + y*y + z*z);

            vnml.data[3*count]   = (char) (255*x/dd);
            vnml.data[3*count+1] = (char) (255*y/dd);
            vnml.data[3*count+2] = (char) (255*z/dd);

            count++;
        }
    }

    return vnml;
}

} // namespace bluesky
