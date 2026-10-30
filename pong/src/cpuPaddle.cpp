#include "cpuPaddle.h"

void CpuPaddle::Update(int ballY) {
    if (y + height / 2 > ballY) {
        y = y - speed;
    }
    if (y + height / 2 <= ballY) {
        y = y + speed;
    }
    LimitMovement();
}
