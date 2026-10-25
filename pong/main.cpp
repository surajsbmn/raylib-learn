#include "raylib.h"
#include <iostream>

using namespace std;

Color Green = Color{38, 185, 154, 255};
Color DarkGreen = Color{20, 160, 133, 255};
Color LightGreen = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

int playerScore = 0;
int cpuScore = 0;

class Ball {
  public:
    float x, y;
    int speedX, speedY;
    int radius;

    void Draw() { DrawCircle(x, y, radius, Yellow); }

    void Update() {
        x += speedX;
        y += speedY;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speedY *= -1;
        }

        if (x + radius >= GetScreenWidth()) {
            cpuScore++;
            Reset();
        }

        if (x - radius <= 0) {
            playerScore++;
            Reset();
        }
    }

    void Reset() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speeds[2] = {1, -1};
        speedX *= speeds[GetRandomValue(0, 1)];
        speedY *= speeds[GetRandomValue(0, 1)];
    }
};

class Paddle {
  public:
    float x, y;
    float width, height;
    int speed;

    void Draw() { DrawRectangle(x, y, width, height, WHITE); }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y = y + speed;
        }
        LimitMovement();
    }

  protected:
    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }

        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }
};

class CpuPaddle : public Paddle {
  public:
    void Update(int ballY) {
        if (y + height / 2 > ballY) {
            y = y - speed;
        }
        if (y + height / 2 <= ballY) {
            y = y + speed;
        }
        LimitMovement();
    }
};

void runGame();

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

    runGame();

    CloseWindow();
    return 0;
}

void runGame() {

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