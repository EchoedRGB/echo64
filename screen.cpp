#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

using namespace std;

const int REAL_SCREEN_SIZE = 960;
const int VIRTUAL_SCREEN_SIZE = 64;
const int PIXEL_SIZE = REAL_SCREEN_SIZE / VIRTUAL_SCREEN_SIZE;

struct Coordinate {
    int x, y;
};

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
vector<Coordinate> white_pixels;

void initScreen() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("64x64 Virtual Screen Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, REAL_SCREEN_SIZE, REAL_SCREEN_SIZE, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void addCoordinate(int x, int y) {
    // Ensure coordinates are within bounds for virtual coordinates
    if (x >= 0 && x < VIRTUAL_SCREEN_SIZE && y >= 0 && y < VIRTUAL_SCREEN_SIZE) {
        // Add the coordinate directly (no scaling needed)
        white_pixels.push_back({ x, y });
    } else {
        std::cout << "Coordinate out of bounds: (" << x << ", " << y << ")" << std::endl;
    }
}

void drawVirtualScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (const auto& pixel : white_pixels) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = { pixel.x * PIXEL_SIZE, (VIRTUAL_SCREEN_SIZE - 1 - pixel.y) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE };
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    for (int i = 0; i <= VIRTUAL_SCREEN_SIZE; ++i) {
        SDL_RenderDrawLine(renderer, i * PIXEL_SIZE, 0, i * PIXEL_SIZE, REAL_SCREEN_SIZE);
        SDL_RenderDrawLine(renderer, 0, i * PIXEL_SIZE, REAL_SCREEN_SIZE, i * PIXEL_SIZE);
    }

    SDL_RenderPresent(renderer);
}

void cleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void startScreen() {
    initScreen();
}

void run() {
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }
        drawVirtualScreen();
    }

    cleanUp();
}
