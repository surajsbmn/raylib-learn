#pragma once

class Paddle {
  public:
    float x, y;
    float width, height;
    int speed;

    void Draw();
    void Update();

  protected:
    void LimitMovement();
};
