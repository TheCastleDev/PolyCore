#include "Blocks.h"
#include <unordered_map>

namespace {
    std::unordered_map<std::string, Texture2D> g_textures;

    // Índice dentro de la variante de 6 texturas: { +X, -X, +Y, -Y, +Z, -Z }
    int FaceIndex(Face face)
    {
        switch (face)
        {
            case FACE_RIGHT:  return 0;
            case FACE_LEFT:   return 1;
            case FACE_TOP:    return 2;
            case FACE_BOTTOM: return 3;
            case FACE_FRONT:  return 4;
            case FACE_BACK:   return 5;
            default:          return 0;
        }
    }
}

namespace Blocks {

    const std::string& TexturePath(const BlockData& block, Face face)
    {
        static const std::string empty;

        if (block.textures.empty()) return empty;

        switch (block.textures.size())
        {
            case 6:
                return block.textures[FaceIndex(face)];
            case 3:
                if (face == FACE_TOP) return block.textures[0];
                if (face == FACE_BOTTOM) return block.textures[1];
                return block.textures[2];
            default:
                return block.textures[0];
        }
    }

    Texture2D GetTexture(const std::string& path)
    {
        auto it = g_textures.find(path);
        if (it != g_textures.end())
            return it->second;

        Texture2D texture = LoadTexture(path.c_str());
        g_textures[path] = texture;
        return texture;
    }

    void UnloadAll()
    {
        for (auto& [path, texture] : g_textures)
            UnloadTexture(texture);

        g_textures.clear();
    }
}
