#ifndef CUBE_H
#define CUBE_H
#include "../Types.h"

class Cube {
public:
    static void Draw(const BlockData& data, Vector3 position, unsigned char faces = FACE_ALL);
};
#endif