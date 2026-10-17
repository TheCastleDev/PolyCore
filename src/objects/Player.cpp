
#include "Player.h"
#include <cmath>

Player::Player()
{
    camera.position = {0.0f, 2.0f, 5.0f};
    camera.target = {0.0f, 2.0f, 4.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    moveSpeed = 8.0f;
    fastSpeed = 20.0f;
    mouseSensitivity = 0.003f;

    DisableCursor();
}

void Player::Update(float deltaTime)
{
    //Movimiento de camara
    Vector2 mouseDelta = GetMouseDelta();

    Vector3 forward = {
        camera.target.x - camera.position.x,
        camera.target.y - camera.position.y,
        camera.target.z - camera.position.z
    };

    float yaw = atan2f(forward.x, forward.z);

    float pitch = atan2f(
        forward.y,
        sqrtf(forward.x * forward.x + forward.z * forward.z)
    );

    yaw -= mouseDelta.x * mouseSensitivity;
    pitch -= mouseDelta.y * mouseSensitivity;

    const float limit = 1.55334f;

    if (pitch > limit) pitch = limit;
    if (pitch < -limit) pitch = -limit;

    forward = {
        sinf(yaw) * cosf(pitch),
        sinf(pitch),
        cosf(yaw) * cosf(pitch)
    };

    Vector3 right = {
        -cosf(yaw),
        0.0f,
        sinf(yaw)
    };

    //Movimiento
    Vector3 movement = {0.0f, 0.0f, 0.0f};

    if (IsKeyDown(KEY_W))
    {
        movement.x += forward.x;
        movement.y += forward.y;
        movement.z += forward.z;
    }

    if (IsKeyDown(KEY_S))
    {
        movement.x -= forward.x;
        movement.y -= forward.y;
        movement.z -= forward.z;
    }

    if (IsKeyDown(KEY_D))
    {
        movement.x += right.x;
        movement.z += right.z;
    }

    if (IsKeyDown(KEY_A))
    {
        movement.x -= right.x;
        movement.z -= right.z;
    }

    if (IsKeyDown(KEY_SPACE))
        movement.y += 1.0f;

    if (IsKeyDown(KEY_LEFT_CONTROL) ||
        IsKeyDown(KEY_RIGHT_CONTROL))
    {
        movement.y -= 1.0f;
    }

    //Velocidad
    float length = sqrtf(
        movement.x * movement.x +
        movement.y * movement.y +
        movement.z * movement.z
    );

    if (length > 0.0f)
    {
        movement.x /= length;
        movement.y /= length;
        movement.z /= length;
    }

    float speed = IsKeyDown(KEY_LEFT_SHIFT)
                    ? fastSpeed
                    : moveSpeed;

    camera.position.x += movement.x * speed * deltaTime;
    camera.position.y += movement.y * speed * deltaTime;
    camera.position.z += movement.z * speed * deltaTime;

    camera.target = {
        camera.position.x + forward.x,
        camera.position.y + forward.y,
        camera.position.z + forward.z
    };
}

void Player::Begin3D() const
{
    BeginMode3D(camera);
}

Vector3 Player::GetPosition(){
    return camera.position;
}