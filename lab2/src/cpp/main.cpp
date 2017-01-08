// std
#include <memory>

// local
#include "WindowWrapper.h"

int main() {

    auto window_wrapper = WindowWrapper(1024, 768, "Bunny Reflection");

    window_wrapper.loop();

    return 0;
}