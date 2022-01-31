#ifndef PATH_HPP
#define PATH_HPP

#include <SDL.h>
#include <vector>

class Path {
private:
    SDL_Point center;
    int radius;
    int width;
    int points;
    int gap_size;
    float degree_as_radial;
    std::vector<int> gaps;
    std::vector<int> walls;

    void drawOutline(SDL_Renderer * renderer, int rotation);
    void drawWall(SDL_Renderer * renderer, int rotation, int wall);
public:
    Path(SDL_Point center, int radius, int width, int gap_size, std::vector<int> gaps, std::vector<int> walls);
    ~Path();

    void draw(SDL_Renderer * renderer, int rotation);
};

#endif // PATH_HPP