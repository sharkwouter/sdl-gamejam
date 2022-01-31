#include "Path.hpp"

#include "constants.hpp"

Path::Path(SDL_Point center, int radius, int width, int gap_size, std::vector<int> gaps, std::vector<int> walls) {
    this->center = center;
    this->radius = radius;
    this->width = width;
    this->gap_size = gap_size;
    this->gaps = gaps;
    this->walls = walls;

    this->points = 2*radius*PI;
    this->degree_as_radial = PI/180;
}

Path::~Path() {

}

void Path::draw(SDL_Renderer * renderer, int rotation) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    drawOutline(renderer, rotation);
    for (int wall : this->walls) {
        drawWall(renderer, rotation, wall);
    }
}

void Path::drawOutline(SDL_Renderer * renderer, int rotation) {  
    int x, y, i, gap_rotation, gap_point, gap_edge_l, gap_edge_r;
    float radial;
    bool should_draw;

    for (i = 0; i < points; i++) {
        should_draw = true;
        for(int gap: gaps) {
            gap_rotation = (gap+rotation);
            if(gap_rotation > 359) {
                gap_rotation -= 360;
            }

            gap_point = gap_rotation*this->points/360;
            gap_edge_l = gap_point-this->gap_size/2;
            gap_edge_r = gap_point+this->gap_size/2;
            if ((i >= gap_edge_l && i <= gap_edge_r)||
                (gap_edge_l < 0 && i >= (gap_edge_l+points)) ||
                (gap_edge_r > points && i <= (gap_edge_r-points))
            ) {
                should_draw = false;
                break;
            }
        }

        if (should_draw) {
            radial = 2 * PI * i / points;
            x = radius * cos(radial);
            y = radius * sin(radial);

            SDL_RenderDrawPoint(renderer, center.x + x, center.y + y);
        }
    }
}

void Path::drawWall(SDL_Renderer * renderer, int rotation, int wall) {
        float point = this->degree_as_radial*(wall+rotation);

        float len_x = cos(point);
        float len_y = sin(point);

        int x1 = len_x * (radius-this->width);
        int y1 = len_y * (radius-this->width);
        int x2 = len_x * radius;
        int y2 = len_y * radius;
        SDL_RenderDrawLine(renderer, center.x + x1, center.y + y1, center.x + x2, center.y + y2);
}