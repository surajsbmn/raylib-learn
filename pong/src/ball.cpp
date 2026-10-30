#include "ball.h"
#include "globals.h"
#include "raylib.h"

void Ball::Draw() { DrawCircle(x, y, radius, Yellow); }

void Ball::Update() {
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

void Ball::Reset() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    int speeds[2] = {1, -1};
    speedX *= speeds[GetRandomValue(0, 1)];
    speedY *= speeds[GetRandomValue(0, 1)];
}
