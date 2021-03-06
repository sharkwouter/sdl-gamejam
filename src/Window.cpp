#include "Window.hpp"

Window::Window(const std::string &title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER | SDL_INIT_TIMER) != 0) {
        SDL_Log("couldn't init SDL: %s", SDL_GetError());
        exit(1);
    }

    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (this->window == nullptr) {
        SDL_Log("couldn't create window: %s", SDL_GetError());
        exit(1);
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == nullptr) {
        SDL_Log("couldn't create renderer: %s", SDL_GetError());
        exit(1);
    }

    // Make the use of transparancy possible
    SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);

    this->start_frame = SDL_GetTicks();
    this->frame_delay = 1000 / 60; // Target 60 fps
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->renderer);
}

void Window::present() {
    int delta = SDL_GetTicks() - this->start_frame;
    if (delta < this->frame_delay) {
        SDL_Delay(this->frame_delay - delta);
    }
    SDL_RenderPresent(this->renderer);
    this->start_frame = SDL_GetTicks();
}

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
