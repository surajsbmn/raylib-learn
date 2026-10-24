#include "raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define SPEED 10

int main() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Basics raylib");
  SetTargetFPS(60);

  Vector2 ballPos = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
  Vector2 ballSpeed = {SPEED, SPEED};
  const int radius = 20;

  while (WindowShouldClose() == false) {
    // Update
    {
      ballPos.x += ballSpeed.x;
      ballPos.y += ballSpeed.y;

      if (ballPos.x + radius >= GetScreenWidth() || ballPos.x - radius <= 0) {
        ballSpeed.x *= -1;
      }

      if (ballPos.y + radius >= GetScreenHeight() || ballPos.y - radius <= 0) {
        ballSpeed.y *= -1;
      }
    }

    BeginDrawing();
    {
      DrawCircle(ballPos.x, ballPos.y, radius, WHITE);

      ClearBackground(DARKPURPLE);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}