#pragma once
#include "Types.h"

namespace Blocks {
    // Ruta de textura según la variante del bloque (1, 3 o 6 texturas)
    const std::string& TexturePath(const BlockData& block, Face face);
    Texture2D GetTexture(const std::string& path);
    void UnloadAll();
}

// ---------------------------------------------------------------- declaración
// Variante de 1 textura
inline BlockData DIRT = {
    .id = "dirt_block",
    .textures = { "assets/textures/blocks/dirt.png" },
    .breakTime = 1.0f
};

// Variante de 3 texturas: { arriba, abajo, lados }
inline BlockData GRASS_BLOCK = {
    .id = "grass_block",
    .textures = {
        "assets/textures/blocks/grass_block_top.png",  // arriba
        "assets/textures/blocks/dirt.png",             // abajo
        "assets/textures/blocks/grass_block_side.png"  // lados
    },
    .breakTime = 1.0f
};
