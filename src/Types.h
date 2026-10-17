#pragma once

#include "raylib.h"
#include <string>
#include <vector>

enum Face {
    FACE_RIGHT  = 1 << 0, // +X
    FACE_LEFT   = 1 << 1, // -X
    FACE_TOP    = 1 << 2, // +Y
    FACE_BOTTOM = 1 << 3, // -Y
    FACE_FRONT  = 1 << 4, // +Z
    FACE_BACK   = 1 << 5, // -Z
    FACE_SIDES  = FACE_RIGHT | FACE_LEFT | FACE_FRONT | FACE_BACK,
    FACE_ALL    = 0x3F
};

struct BlockData {
    std::string id;

    // 1 textura  -> todas las caras usan la misma
    // 3 texturas -> { arriba, abajo, lados }
    // 6 texturas -> una por cara { +X, -X, +Y, -Y, +Z, -Z }
    std::vector<std::string> textures;

    float breakTime = 0.0f;

    Sound breakSound{};
    Sound placeSound{};
};
