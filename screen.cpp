#include <SDL2/SDL.h>
#include <vector>

using namespace std;

const int REAL_SCREEN_SIZE = 960;
const int VIRTUAL_SCREEN_SIZE = 64;
const int PIXEL_SIZE = REAL_SCREEN_SIZE / VIRTUAL_SCREEN_SIZE;

struct Coordinate {
    int x, y;
};

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
vector<Coordinate> white_pixels; // Acts like a list to store coordinates

void initScreen() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("64x64 Virtual Screen Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, REAL_SCREEN_SIZE, REAL_SCREEN_SIZE, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void addCoordinate(int x, int y) {
    // In bottom-left origin, (0,0) is at the bottom-left
    white_pixels.push_back({ x / PIXEL_SIZE, y / PIXEL_SIZE }); // Add the new coordinate
}

void drawVirtualScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (const auto& pixel : white_pixels) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = { pixel.x * PIXEL_SIZE, (VIRTUAL_SCREEN_SIZE - pixel.y - 1) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE };
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

int main() {
    initScreen();

    // Adding white pixels using addCoordinate function
    // addCoordinate(int x, int y);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }
        drawVirtualScreen();
    }

    cleanUp();
    return 0;
}
