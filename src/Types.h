#pragma once

#include "raylib.h"
#include <string>
#include <variant>

struct BlockTextureSides {
    Texture2D up;
    Texture2D down;
    Texture2D side;
};

struct BlockTextureFaces {
    Texture2D up;
    Texture2D down;
    Texture2D north;
    Texture2D south;
    Texture2D east;
    Texture2D west;
};

struct BlockData {
    std::string id;
    float breakTime = 0.0f;

    std::variant<
        Texture2D,
        BlockTextureSides,
        BlockTextureFaces
    > textures;

    Sound breakSound{};
    Sound placeSound{};
};