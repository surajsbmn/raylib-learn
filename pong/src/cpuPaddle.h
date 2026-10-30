#pragma once
#include "paddle.h"

class CpuPaddle : public Paddle {
  public:
    void Update(int ballY);
};
