#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <SDL.h>
#include <vector>

#include "Input.hpp"
#include "Path.hpp"

class Puzzle {
private:
    int path_width = 32;

    SDL_Point center;
    int rotation;
    SDL_Point ball;

    std::vector<Path> paths;
    
public:
    Puzzle(SDL_Point center, int path_width, int paths);
    ~Puzzle();

    void update();
    void handleInputs(std::vector<Input> inputs);
    void draw(SDL_Renderer * renderer);
};

#endif // PUZZLE_HPP