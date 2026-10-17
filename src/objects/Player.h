#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player
{
public:
    Player();

    void Update(float deltaTime);
    void Begin3D() const;
    Vector3 GetPosition();

    Camera3D GetCamera() const;

private:
    Camera3D camera;

    float moveSpeed;
    float fastSpeed;
    float mouseSensitivity;
};

#endif