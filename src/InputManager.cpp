#include "Input.hpp"

#define AXIS_MAX 32767
#define AXIS_MIN -32767

InputManager::~InputManager() {
    closeAllGameControllers();
}

std::vector<Input> InputManager::getInputs() {
    std::vector<Input> inputs;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        Input input = Input::NONE;

        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                input = getInputFromKeyboard(event.key.keysym.sym);
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                input = getInputFromControllerButton(event.cbutton.button);
                break;
            case SDL_CONTROLLERAXISMOTION:
                input = getInputFromControllerAxis(event.caxis.axis, event.caxis.value);
                break;
            case SDL_CONTROLLERDEVICEADDED:
                openGameController(event.cdevice.which);
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                closeDisconnectedGameControllers();
                break;
        }
        if (input != Input::NONE) {
            inputs.push_back(input);
        }
    }
    return inputs;
}

Input InputManager::getInputFromKeyboard(SDL_Keycode key) {
    Input event;

    switch (key) {
        case SDLK_a:
        case SDLK_LEFT:
            event = Input::LEFT;
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            event = Input::RIGHT;
            break;
        case SDLK_e:
        case SDLK_RETURN:
        case SDLK_SPACE:
            event = Input::CONFIRM;
            break;
        case SDLK_q:
        case SDLK_BACKSPACE:
            event = Input::CANCEL;
            break;
        case SDLK_ESCAPE:
            event = Input::MENU;
            break;
        default:
            event = Input::NONE;
            break;
    }

    return event;
}


Input InputManager::getInputFromControllerButton(Uint32 button) {
    Input event;

    switch (button) {
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            event = Input::LEFT;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            event = Input::RIGHT;
            break;
        case SDL_CONTROLLER_BUTTON_A:
            event = Input::CONFIRM;
            break;
        case SDL_CONTROLLER_BUTTON_B:
            event = Input::CANCEL;
            break;
        case SDL_CONTROLLER_BUTTON_START:
            event = Input::MENU;
            break;
        default:
            event = Input::NONE;
            break;
    }

    return event;
}

Input InputManager::getInputFromControllerAxis(Uint32 axis, Sint16 value) {
    Input event = Input::NONE;

    switch (axis) {
        case SDL_CONTROLLER_AXIS_LEFTX:
            if (value > (AXIS_MAX*0.5)) {
                if (this->returned_to_horizontal_center) {
                    event = Input::RIGHT;
                    this->returned_to_horizontal_center = false;
                }
            } else if (value < (AXIS_MIN*0.5)) {
                if(this->returned_to_horizontal_center) {
                    event = Input::LEFT;
                    this->returned_to_horizontal_center = false;
                }
            } else {
                this->returned_to_horizontal_center = true;
            }
            break;
        default:
            break;
    }

    return event;
}

void InputManager::openGameController(Sint32 index) {
     if (SDL_IsGameController(index)) {
        SDL_GameController * controller = SDL_GameControllerOpen(index);
        SDL_Log("Adding controller: %s", SDL_GameControllerName(controller));
        gameControllers.push_back(controller);
    }
}

void InputManager::closeDisconnectedGameControllers() {
    std::vector<SDL_GameController*> currentControllers;
    for(SDL_GameController * controller : gameControllers) {
        if (!SDL_GameControllerGetAttached(controller)) {
            SDL_Log("Removing controller: %s", SDL_GameControllerName(controller));
            SDL_GameControllerClose(controller);
            controller = NULL;
        } else {
            currentControllers.push_back(controller);
        }
    }

    gameControllers = currentControllers;
}

void InputManager::closeAllGameControllers() {
    for (int i = 0; i < int(gameControllers.size()); i++) {
        SDL_Log("Removing controller: %s", SDL_GameControllerName(gameControllers[i]));
        SDL_GameControllerClose(gameControllers[i]);
        gameControllers[i] = NULL;
    }
}
