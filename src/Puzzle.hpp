#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <SDL.h>
#include <vector>

#include "Input.hpp"
#include "Path.hpp"
#include "Ball.hpp"

class Puzzle {
private:
    int path_width;

    SDL_Point center;
    int rotation;
    Ball ball;

    std::vector<Path> paths;

    bool done;

    void drawBall(SDL_Renderer * renderer);
public:
    Puzzle(SDL_Point center, int path_width, int paths);
    ~Puzzle();

    void update();
    void handleInputs(std::vector<Input> inputs);
    void draw(SDL_Renderer * renderer);

    bool isDone() {return this->done;};
};

#endif // PUZZLE_HPP