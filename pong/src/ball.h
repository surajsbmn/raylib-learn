#pragma once

class Ball {
  public:
    float x, y;
    int speedX, speedY;
    int radius;

    void Draw();
    void Update();
    void Reset();
};
