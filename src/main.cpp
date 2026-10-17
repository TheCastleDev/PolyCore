#include "raylib.h"
#include "objects/Player.h"
#include "utils/WorldGenUtils.h"
#include "utils/DrawingUtils.h"
#include "Types.h"
#include "Blocks.h"

int main()
{
    InitWindow(1280, 720, "PolyCore - Free Camera");
    SetTargetFPS(144);

    Player player;
    Image heightMap = WorldGenUtils::GenNoise(16, 16, GetRandomValue(1, 5000));
    Texture2D hmTex = LoadTextureFromImage(heightMap);
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F))
        {
            UnloadTexture(hmTex);
            UnloadImage(heightMap);
            heightMap = WorldGenUtils::GenNoise(16, 16, GetRandomValue(1, 5000));
            hmTex = LoadTextureFromImage(heightMap);
        }
        float deltaTime = GetFrameTime();

        player.Update(deltaTime);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        player.Begin3D();

        DrawPlane(
            {0.0f, 0.0f, 0.0f},
            {100.0f, 100.0f},
            LIGHTGRAY);

        DrawGrid(100, 1.0f);

        WorldGenUtils::GenerateTerrainFromHeightmap(heightMap, DIRT, Vector3{0, 0.5f, 0});

        DrawCube(Vector3{0, 90 / 2, 0}, 1, 900, 1, BLUE);

        EndMode3D();

        DrawText("WASD: Move | Mouse: Look", 10, 10, 20, DARKGRAY);
        DrawText("SPACE/CTRL: Up/Down | SHIFT: Fast", 10, 35, 20, DARKGRAY);
        DrawTexture(hmTex, 10, 60, WHITE);
        EndDrawing();
    }

    Blocks::UnloadAll();
    UnloadImage(heightMap);
    UnloadTexture(hmTex);
    EnableCursor();
    CloseWindow();

    return 0;
}