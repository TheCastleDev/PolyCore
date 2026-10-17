#include "WorldGenUtils.h"
#include "raylib.h"
#include "../Types.h"
#include "../Blocks.h"
#include "../objects/Cube.h"
#include <cmath>

Image WorldGenUtils::GenNoise(int width, int height, int seed)
{
    Image noiseImage = GenImageColor(width, height, BLACK);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float nx = x + seed * 10.0f;
            float ny = y + seed * 10.0f;

            float val = sin(nx * 0.05f) * cos(ny * 0.05f) +
                        sin(nx * 0.02f + ny * 0.02f) * 0.5f;
            float noiseVal = (val + 1.5f) / 3.0f;
            unsigned char c = (unsigned char)(noiseVal * 255.0f);
            Color pixelColor = {c, c, c, 255};
            ImageDrawPixel(&noiseImage, x, y, pixelColor);
        }
    }

    return noiseImage;
}

void WorldGenUtils::GenerateTerrainFromHeightmap(Image heightmap, const BlockData& fillBlock, Vector3 startPos)
{
    if (heightmap.data == nullptr) return;

    auto cellHeight = [&](int x, int z) -> int
    {
        if (x < 0 || z < 0 || x >= heightmap.width || z >= heightmap.height) return -1;
        return GetImageColor(heightmap, x, z).r;
    };

    for (int z = 0; z < heightmap.height; z++)
    {
        for (int x = 0; x < heightmap.width; x++)
        {
            int height = cellHeight(x, z);

            for (int iy = height; iy >= 0; iy--)
            {
                unsigned char faces = 0;

                if (cellHeight(x, z + 1) < iy) faces |= FACE_FRONT;
                if (cellHeight(x, z - 1) < iy) faces |= FACE_BACK;
                if (cellHeight(x + 1, z) < iy) faces |= FACE_RIGHT;
                if (cellHeight(x - 1, z) < iy) faces |= FACE_LEFT;
                if (iy == height) faces |= FACE_TOP;
                if (iy == 0) faces |= FACE_BOTTOM;

                Vector3 cubePos = {
                    startPos.x + (float)x,
                    startPos.y + (float)iy,
                    startPos.z + (float)z
                };

                const BlockData& block = (iy == height) ? GRASS_BLOCK : fillBlock;
                Cube::Draw(block, cubePos, faces);
            }
        }
    }
}