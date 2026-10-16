#include "Cube.h"
#include "../Types.h"
#include "rlgl.h"
#include <variant>

void Cube::Draw(BlockData data, Vector3 position)
{
    float x = position.x;
    float y = position.y;
    float z = position.z;

    float w = 0.5f;
    float h = 0.5f;
    float l = 0.5f;

    // Obtener las texturas de cada cara.
    Texture2D frontTexture{};
    Texture2D backTexture{};
    Texture2D upTexture{};
    Texture2D downTexture{};
    Texture2D rightTexture{};
    Texture2D leftTexture{};

    if (auto* single = std::get_if<Texture2D>(&data.textures))
    {
        frontTexture = backTexture = upTexture =
        downTexture = rightTexture = leftTexture = *single;
    }
    else if (auto* sides = std::get_if<BlockTextureSides>(&data.textures))
    {
        upTexture = sides->up;
        downTexture = sides->down;

        frontTexture = backTexture =
        rightTexture = leftTexture = sides->side;
    }
    else if (auto* faces = std::get_if<BlockTextureFaces>(&data.textures))
    {
        upTexture = faces->up;
        downTexture = faces->down;
        frontTexture = faces->south;
        backTexture = faces->north;
        rightTexture = faces->east;
        leftTexture = faces->west;
    }

    rlCheckRenderBatchLimit(36);

    rlBegin(RL_QUADS);
    rlColor4ub(255, 255, 255, 255);

    // Cara frontal (+Z)
    rlSetTexture(frontTexture.id);
    rlTexCoord2f(0, 0); rlVertex3f(x - w, y - h, z + l);
    rlTexCoord2f(1, 0); rlVertex3f(x + w, y - h, z + l);
    rlTexCoord2f(1, 1); rlVertex3f(x + w, y + h, z + l);
    rlTexCoord2f(0, 1); rlVertex3f(x - w, y + h, z + l);

    // Cara trasera (-Z)
    rlSetTexture(backTexture.id);
    rlTexCoord2f(1, 0); rlVertex3f(x - w, y - h, z - l);
    rlTexCoord2f(1, 1); rlVertex3f(x - w, y + h, z - l);
    rlTexCoord2f(0, 1); rlVertex3f(x + w, y + h, z - l);
    rlTexCoord2f(0, 0); rlVertex3f(x + w, y - h, z - l);

    // Cara superior (+Y)
    rlSetTexture(upTexture.id);
    rlTexCoord2f(0, 1); rlVertex3f(x - w, y + h, z - l);
    rlTexCoord2f(0, 0); rlVertex3f(x - w, y + h, z + l);
    rlTexCoord2f(1, 0); rlVertex3f(x + w, y + h, z + l);
    rlTexCoord2f(1, 1); rlVertex3f(x + w, y + h, z - l);

    // Cara inferior (-Y)
    rlSetTexture(downTexture.id);
    rlTexCoord2f(1, 1); rlVertex3f(x - w, y - h, z - l);
    rlTexCoord2f(0, 1); rlVertex3f(x + w, y - h, z - l);
    rlTexCoord2f(0, 0); rlVertex3f(x + w, y - h, z + l);
    rlTexCoord2f(1, 0); rlVertex3f(x - w, y - h, z + l);

    // Cara derecha (+X)
    rlSetTexture(rightTexture.id);
    rlTexCoord2f(1, 0); rlVertex3f(x + w, y - h, z - l);
    rlTexCoord2f(1, 1); rlVertex3f(x + w, y + h, z - l);
    rlTexCoord2f(0, 1); rlVertex3f(x + w, y + h, z + l);
    rlTexCoord2f(0, 0); rlVertex3f(x + w, y - h, z + l);

    // Cara izquierda (-X)
    rlSetTexture(leftTexture.id);
    rlTexCoord2f(0, 0); rlVertex3f(x - w, y - h, z - l);
    rlTexCoord2f(1, 0); rlVertex3f(x - w, y - h, z + l);
    rlTexCoord2f(1, 1); rlVertex3f(x - w, y + h, z + l);
    rlTexCoord2f(0, 1); rlVertex3f(x - w, y + h, z - l);

    rlEnd();
    rlSetTexture(0);
}