#include "WorldGenUtils.h"
#include "raylib.h"
#include "../Types.h"
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

void WorldGenUtils::GenerateTerrainFromHeightmap(Image heightmap, BlockData blockData, Vector3 startPos)
{
    if (heightmap.data == nullptr) return;

    for (int z = 0; z < heightmap.height; z++)
    {
        for (int x = 0; x < heightmap.width; x++)
        {
            Color pixelColor = GetImageColor(heightmap, x, z);

            int height = pixelColor.r;

            Vector3 cubePos = {
                startPos.x + (float)x,
                startPos.y + (float)height,
                startPos.z + (float)z
            };

            Cube::Draw(blockData, cubePos);
        }
    }
}