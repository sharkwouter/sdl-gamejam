#include "Window.hpp"
#include "Input.hpp"
#include "Puzzle.hpp"

#ifndef PROJECT_NAME
    #define PROJECT_NAME "undefined"
#endif

InputManager input_manager;

int main(int argv, char** args) {
    (void) argv;
    (void) args;

    int screen_height = 800;
    int screen_width = 600;

    int paths = 4;
    int path_width = 64;

    Window window(PROJECT_NAME, screen_height, screen_width);
    Puzzle * puzzle = new Puzzle({screen_height/2, screen_width/2}, path_width, paths);

    while (true) {
        std::vector<Input> inputs = input_manager.getInputs();
        for (Input i : inputs) {
            switch (i)
            {
            case Input::RESET:
                delete puzzle;
                puzzle = new Puzzle({screen_height/2, screen_width/2}, path_width, paths);
                break;
            }
        }
        

        puzzle->handleInputs(inputs);
        puzzle->update();

        window.clear();
        puzzle->draw(window.renderer);
        window.present();
    }

    return 0;
}
