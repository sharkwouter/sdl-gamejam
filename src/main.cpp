#include "Window.hpp"
#include "Input.hpp"

InputManager input_manager;

int main(int argv, char** args) {
    (void) argv;
    (void) args;

    Window window(PROJECT_NAME, 800, 600);


    while (true) {
        std::vector<Input> events = input_manager.getInputs();

        // state_manager.handleEvents(events);
        // state_manager.update();

        window.clear();
        // state_manager.draw(window.renderer);
        window.present();
    }

    return 0;
}
