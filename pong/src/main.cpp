#include "ball.h"
#include "cpuPaddle.h"
#include "globals.h"
#include "paddle.h"
#include "raylib.h"
#include <iostream>

using namespace std;

Color Green = Color{38, 185, 154, 255};
Color DarkGreen = Color{20, 160, 133, 255};
Color LightGreen = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

int playerScore = 0;
int cpuScore = 0;

void runGameLoop();

Ball ball;
Paddle player;
CpuPaddle cpu;

int main() {
    cout << "Starting Pong...\n";

    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = GetScreenWidth() / 2;
    ball.y = GetScreenHeight() / 2;
    ball.speedX = 8;
    ball.speedY = 8;

    player.width = 25;
    player.height = 120;
    player.x = GetScreenWidth() - player.width - 10;
    player.y = GetScreenHeight() / 2 - player.height / 2;
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = GetScreenHeight() / 2 - cpu.height / 2;
    cpu.speed = 6;

    runGameLoop();

    CloseWindow();
    return 0;
}

void runGameLoop() {

    while (WindowShouldClose() == false) {
        // Update

        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // Check collision
        if (CheckCollisionCircleRec(
                Vector2{ball.x, ball.y}, ball.radius,
                Rectangle{player.x, player.y, player.width, player.height})) {
            ball.speedX *= -1;
        }
        if (CheckCollisionCircleRec(
                Vector2{ball.x, ball.y}, ball.radius,
                Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.speedX *= -1;
        }

        BeginDrawing();
        ClearBackground(DarkGreen);
        DrawRectangle(GetScreenWidth() / 2, 0, GetScreenWidth() / 2,
                      GetScreenHeight(), Green);
        DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2 , 150, LightGreen);
        DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2,
                 GetScreenHeight(), WHITE);
        ball.Draw();
        player.Draw();
        cpu.Draw();
        DrawText(TextFormat("%i", cpuScore), GetScreenWidth() / 4 - 20, 20, 80,
                 WHITE);
        DrawText(TextFormat("%i", playerScore), 3 * GetScreenWidth() / 4 - 20,
                 20, 80, WHITE);
        EndDrawing();
    }
}