#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL2/SDL.h>
#include <vector>

enum class Input {
    CONFIRM,
    CANCEL,
    LEFT,
    RIGHT,
    MENU,
    NONE
};

class InputManager {

private:
    bool returned_to_horizontal_center;
    bool returned_to_vertical_center;

    Input getInputFromKeyboard(SDL_Keycode key);
    Input getInputFromControllerButton(Uint32 button);
    Input getInputFromControllerAxis(Uint32 axis, Sint16 value);

    void openGameController(Sint32);
    void closeDisconnectedGameControllers();
    void closeAllGameControllers();

    std::vector<SDL_GameController*> gameControllers;

public:
    ~InputManager();

    std::vector<Input> getInputs();

};

#endif // INPUT_HPP
