#include "Puzzle.hpp"
#include <time.h>

Puzzle::Puzzle(SDL_Point center, int path_width, int paths) {
    this->center = center;
    this->path_width = path_width;

    // Create paths
    this->paths.reserve(paths);
    for (size_t i = 1; i <= paths; i++) {
        std::vector<int> gaps;
        std::vector<int> walls;
        if (i == 1) {
            gaps = {90};
            walls = {};
        } else if (i == 2) {
            gaps = {180};
            walls = {};
        } else {
            if (i == paths) {
                gaps = {rand() % 360};
            } else {
                gaps = {0, rand() % 360, rand() % 360};
            }
            walls = {rand() % 360, rand() % 360, rand() % 360, rand() % 360};
        }
        this->paths.push_back(Path(center, i*path_width, this->path_width, this->path_width/2, gaps, walls));
    }
    
    this->rotation = 0;

    this->ball = Ball{center.x, center.y, this->path_width/4-2};
}

Puzzle::~Puzzle() {

}

void Puzzle::handleInputs(std::vector<Input> inputs) {
    for (Input i : inputs) {
        switch (i) {
            case Input::LEFT:
                rotation -= 1;
                update();
                break;
            case Input::RIGHT:
                rotation += 1;
                update();
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
    // SDL_Log("%d", this->rotation);

    int ball_path = (ball.y+ball.radius-center.y)/this->path_width+1;
    int path_floor = center.y+ball_path*this->path_width-1;

    if (path_floor != ball.y+ball.radius) {
        ball.y++;
    } else {
        int test = 360-this->rotation+90;
        if (test < 0) {
            test+=360;
        }
        if (test > 359) {
            test-=360;
        }
        if(this->paths[ball_path-1].hasGap(0, 0, test)) {
            SDL_Log("gap found at %d", test);
            ball.y++;
        }
    }
}

void Puzzle::draw(SDL_Renderer * renderer) {
    for (Path path : this->paths) {
        path.draw(renderer, this->rotation);
    }
    drawBall(renderer);
}

// This function implements the Bresenham’s circle drawing algorithm
void Puzzle::drawBall(SDL_Renderer * renderer) {
    int x = -1;
    int y = this->ball.radius;
    int d = 3 - 2 * this->ball.radius;

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    while (y >= x) {
        x++;

        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        };

        SDL_RenderDrawPoint(renderer, this->ball.x + x, this->ball.y + y);
        SDL_RenderDrawPoint(renderer, this->ball.x + y, this->ball.y + x);
        SDL_RenderDrawPoint(renderer, this->ball.x - y, this->ball.y + x);
        SDL_RenderDrawPoint(renderer, this->ball.x - x, this->ball.y + y);
        SDL_RenderDrawPoint(renderer, this->ball.x - x, this->ball.y - y);
        SDL_RenderDrawPoint(renderer, this->ball.x - y, this->ball.y - x);
        SDL_RenderDrawPoint(renderer, this->ball.x + y, this->ball.y - x);
        SDL_RenderDrawPoint(renderer, this->ball.x + x, this->ball.y - y);
    }
}