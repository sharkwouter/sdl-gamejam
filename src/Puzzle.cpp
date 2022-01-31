#include "Puzzle.hpp"
#include <time.h>

Puzzle::Puzzle(SDL_Point center, int path_width, int paths) {
    this->center = center;

    // Create paths
    this->paths.reserve(paths);
    for (size_t i = 1; i <= paths; i++) {
        std::vector<int> gaps;
        std::vector<int> walls;
        if (i == 1) {
            gaps = {0, 180};
            walls = {};
        } else {
            if (i == paths) {
                gaps = {rand() % 360};
            } else {
                gaps = {rand() % 360, rand() % 360};
            }
            walls = {rand() % 360, rand() % 360, rand() % 360, rand() % 360};
        }
        this->paths.push_back(Path(center, i*path_width, path_width, path_width/2, gaps, walls));
    }
    
    this-> rotation = 0;
}

Puzzle::~Puzzle() {

}

void Puzzle::handleInputs(std::vector<Input> inputs) {
    for (Input i : inputs) {
        switch (i) {
            case Input::LEFT:
                rotation -= 1;
                break;
            case Input::RIGHT:
                rotation += 1;
                break;
            default:
                break;
        }
    }
}

void Puzzle::update() {
    if(this->rotation < 0) {
        this->rotation += 360;
    }
    if(this->rotation > 359) {
        this->rotation -= 360;
    }
}

void Puzzle::draw(SDL_Renderer * renderer) {
    for (Path path : this->paths) {
        path.draw(renderer, this->rotation);
    }
}