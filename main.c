#include <SDL2/SDL.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

#define PI 3.14

int closed = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int setupSdl() {
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_TIMER);

    window = SDL_CreateWindow(
        PROJECT_NAME,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initiation window. Error %s", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize renderer. Error: %s", SDL_GetError());
        return 1;
    }

    return 0;
}

void handleEvents(){
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                closed = 1;
                break;
        }
    }
}

void drawCircle(SDL_Renderer * renderer, int center_x, int center_y, int radius) {
	int x, y;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    int points = 2*radius*PI;

    for (int i = 0; i < points; i++) {
        if (i > 10  && i < 30) {
            continue;
        }

        if (i > 200  && i < 250) {
            continue;
        }
        x = radius * cos(2 * PI * i / points);
        y = radius * sin(2 * PI * i / points);
        SDL_RenderDrawPoint(renderer, center_x + x, center_y + y);
    }
}

void drawLine(SDL_Renderer * renderer, int center_x, int center_y, int radius, int degrees) {
        int points = 2*radius*PI;
        int point = points/360 * degrees;

        int x1 = radius * cos(2 * PI * point);
        int y1 = radius * sin(2 * PI * point);
        int x2 = (radius + 32) * cos(2 * PI * point);
        int y2 = (radius + 32) * sin(2 * PI * point);
        SDL_RenderDrawLine(renderer, center_x + x1, center_y + y1, center_x + x2, center_y + y2);
}

int main(int argc, char *argv[]) {
    if (setupSdl() != 0) {
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for(int i = 32; i < HEIGHT/2;i+=32) {
        drawCircle(renderer, WIDTH/2, HEIGHT/2, i);
        drawLine(renderer, WIDTH/2, HEIGHT/2, i, i % 360);
    }

    SDL_RenderPresent(renderer);

    while (!closed) {
        handleEvents();
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
