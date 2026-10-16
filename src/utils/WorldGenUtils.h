#ifndef WORLDGENUTILS_H
#define WORLDGENUTILS_H
#include "raylib.h"
#include "../Types.h"

struct WorldGenUtils
{
    static Image GenNoise(int width, int height, int seed);
    static void GenerateTerrainFromHeightmap(Image heightmap, BlockData blockData, Vector3 startPos);
};

#endif