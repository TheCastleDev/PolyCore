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
    Image heighMap = WorldGenUtils::GenNoise(16,16,0000);
    while (!WindowShouldClose())
    {
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
            
            WorldGenUtils::GenerateTerrainFromHeightmap(heighMap, DIRT_BLOCK,Vector3{0});

        EndMode3D();

        DrawText("WASD: Move | Mouse: Look", 10, 10, 20, DARKGRAY);
        DrawText("SPACE/CTRL: Up/Down | SHIFT: Fast", 10, 35, 20, DARKGRAY);

        EndDrawing();
    }

    EnableCursor();
    CloseWindow();

    return 0;
}