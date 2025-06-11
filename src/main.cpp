#include <iostream>
#include "FrameHandler.h"

int main() {
    while (true) {
        FrameHandler camera;

        auto frame = camera.getFrame();
    }

    return 0;
}