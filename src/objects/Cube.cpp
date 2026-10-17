#include "Cube.h"
#include "../Types.h"
#include "../Blocks.h"
#include "rlgl.h"

namespace {
    void EmitFace(Face face, float x, float y, float z)
    {
        const float w = 0.5f;
        const float h = 0.5f;
        const float l = 0.5f;

        switch (face)
        {
            case FACE_FRONT: // +Z
                rlTexCoord2f(0, 0); rlVertex3f(x - w, y - h, z + l);
                rlTexCoord2f(1, 0); rlVertex3f(x + w, y - h, z + l);
                rlTexCoord2f(1, 1); rlVertex3f(x + w, y + h, z + l);
                rlTexCoord2f(0, 1); rlVertex3f(x - w, y + h, z + l);
                break;

            case FACE_BACK: // -Z
                rlTexCoord2f(1, 0); rlVertex3f(x - w, y - h, z - l);
                rlTexCoord2f(1, 1); rlVertex3f(x - w, y + h, z - l);
                rlTexCoord2f(0, 1); rlVertex3f(x + w, y + h, z - l);
                rlTexCoord2f(0, 0); rlVertex3f(x + w, y - h, z - l);
                break;

            case FACE_TOP: // +Y
                rlTexCoord2f(0, 1); rlVertex3f(x - w, y + h, z - l);
                rlTexCoord2f(0, 0); rlVertex3f(x - w, y + h, z + l);
                rlTexCoord2f(1, 0); rlVertex3f(x + w, y + h, z + l);
                rlTexCoord2f(1, 1); rlVertex3f(x + w, y + h, z - l);
                break;

            case FACE_BOTTOM: // -Y
                rlTexCoord2f(1, 1); rlVertex3f(x - w, y - h, z - l);
                rlTexCoord2f(0, 1); rlVertex3f(x + w, y - h, z - l);
                rlTexCoord2f(0, 0); rlVertex3f(x + w, y - h, z + l);
                rlTexCoord2f(1, 0); rlVertex3f(x - w, y - h, z + l);
                break;

            case FACE_RIGHT: // +X
                rlTexCoord2f(1, 0); rlVertex3f(x + w, y - h, z - l);
                rlTexCoord2f(1, 1); rlVertex3f(x + w, y + h, z - l);
                rlTexCoord2f(0, 1); rlVertex3f(x + w, y + h, z + l);
                rlTexCoord2f(0, 0); rlVertex3f(x + w, y - h, z + l);
                break;

            case FACE_LEFT: // -X
                rlTexCoord2f(0, 0); rlVertex3f(x - w, y - h, z - l);
                rlTexCoord2f(1, 0); rlVertex3f(x - w, y - h, z + l);
                rlTexCoord2f(1, 1); rlVertex3f(x - w, y + h, z + l);
                rlTexCoord2f(0, 1); rlVertex3f(x - w, y + h, z - l);
                break;

            default:
                break;
        }
    }
}

void Cube::Draw(const BlockData& data, Vector3 position, unsigned char faces)
{
    if (faces == 0) return;

    const float x = position.x;
    const float y = position.y;
    const float z = position.z;

    rlCheckRenderBatchLimit(36);

    const Face order[6] = {
        FACE_TOP, FACE_BOTTOM, FACE_FRONT, FACE_BACK, FACE_RIGHT, FACE_LEFT
    };

    unsigned char drawn = 0;

    // Agrupa las caras que comparten textura para minimizar draw calls
    for (Face face : order)
    {
        if (!(faces & face) || (drawn & face)) continue;

        const std::string& path = Blocks::TexturePath(data, face);

        rlBegin(RL_QUADS);
        rlColor4ub(255, 255, 255, 255);
        rlSetTexture(Blocks::GetTexture(path).id);

        for (Face other : order)
        {
            if (!(faces & other) || (drawn & other)) continue;
            if (path != Blocks::TexturePath(data, other)) continue;

            EmitFace(other, x, y, z);
            drawn |= other;
        }

        rlEnd();
    }

    rlSetTexture(0);
}
