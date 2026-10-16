#pragma once
#include "Types.h"
#include <string>

BlockData DIRT_BLOCK = {
    .id = "dirt_block",
    .breakTime = 1.0f,
    .textures = LoadTexture("assets/textures/dirt.png")
};