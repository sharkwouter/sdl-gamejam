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

    int screen_width = 1080;
    int screen_height = 1080;

    int paths = 10;

    Window window(PROJECT_NAME, screen_width, screen_height);

    srand(SDL_GetTicks());

    Puzzle * puzzle = new Puzzle({screen_width/2, screen_height/2}, screen_height/paths/2, paths);

    while (true) {
        std::vector<Input> inputs = input_manager.getInputs();
        for (Input i : inputs) {
            switch (i) {
                case Input::RESET:
                    delete puzzle;
                    puzzle = new Puzzle({screen_width/2, screen_height/2}, screen_height/paths/2, paths);
                    break;
                case Input::MINUS:
                    paths--;
                    if(paths < 3) {
                        paths = 3;
                    }
                    delete puzzle;
                    puzzle = new Puzzle({screen_width/2, screen_height/2}, screen_height/paths/2, paths);
                    break;
                case Input::PLUS:
                    paths++;
                    if(paths > 18) {
                        paths = 18;
                    }
                    delete puzzle;
                    puzzle = new Puzzle({screen_width/2, screen_height/2}, screen_height/paths/2, paths);
                    break;
            }
        }
        

        puzzle->handleInputs(inputs);
        puzzle->update();

        window.clear();
        puzzle->draw(window.renderer);
        window.present();
    }

    delete puzzle;

    return 0;
}
