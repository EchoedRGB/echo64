#include "screen.h"

// Constructor initializes pointers to nullptr
VirtualScreen::VirtualScreen() : window(nullptr), renderer(nullptr) {
    // Initialize pixel array to false
    std::fill(&pixels[0][0], &pixels[0][0] + VIRTUAL_SCREEN_SIZE * VIRTUAL_SCREEN_SIZE, false);
}

// Destructor to clean up SDL resources
VirtualScreen::~VirtualScreen() {
    if (renderer) {
        SDL_DestroyRenderer(renderer); // Destroy the renderer
    }
    if (window) {
        SDL_DestroyWindow(window); // Destroy the window
    }
    SDL_Quit(); // Quit SDL subsystems
}

// Initializes the SDL window and renderer
bool VirtualScreen::initScreen() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false; // Initialization failed
    }
    
    // Create a window
    window = SDL_CreateWindow("64x64 Virtual Screen Simulation", 
                               SDL_WINDOWPOS_UNDEFINED, 
                               SDL_WINDOWPOS_UNDEFINED, 
                               REAL_SCREEN_SIZE, 
                               REAL_SCREEN_SIZE, 
                               SDL_WINDOW_SHOWN);
    
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false; // Window creation failed
    }
    
    // Create a renderer for the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false; // Renderer creation failed
    }
    return true; // Successful initialization
}

// Adds a pixel at the specified (x, y) coordinates
void VirtualScreen::addPixel(int x, int y) {
    if (x >= 0 && x < VIRTUAL_SCREEN_SIZE && y >= 0 && y < VIRTUAL_SCREEN_SIZE) {
        pixels[x][y] = true; // Set pixel to true if within bounds
    } else {
        std::cerr << "Coordinate out of bounds: (" << x << ", " << y << ")" << std::endl;
    }
}

// Renders the virtual screen
void VirtualScreen::render() {
    // Clear the screen with a black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Set the draw color to white for the pixels
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    // Draw each pixel
    for (int x = 0; x < VIRTUAL_SCREEN_SIZE; ++x) {
        for (int y = 0; y < VIRTUAL_SCREEN_SIZE; ++y) {
            if (pixels[x][y]) {
                // Create a rectangle for the pixel
                SDL_Rect rect = { x * PIXEL_SIZE, 
                                  (VIRTUAL_SCREEN_SIZE - 1 - y) * PIXEL_SIZE, 
                                  PIXEL_SIZE, 
                                  PIXEL_SIZE };
                SDL_RenderFillRect(renderer, &rect); // Fill the rectangle
            }
        }
    }

    // Draw grid lines
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    for (int i = 0; i <= VIRTUAL_SCREEN_SIZE; ++i) {
        SDL_RenderDrawLine(renderer, i * PIXEL_SIZE, 0, i * PIXEL_SIZE, REAL_SCREEN_SIZE); // Vertical lines
        SDL_RenderDrawLine(renderer, 0, i * PIXEL_SIZE, REAL_SCREEN_SIZE, i * PIXEL_SIZE); // Horizontal lines
    }

    // Present the rendered frame
    SDL_RenderPresent(renderer);
}

// Clears the pixel array by resetting all elements to false
void VirtualScreen::clear() {
    std::fill(&pixels[0][0], &pixels[0][0] + VIRTUAL_SCREEN_SIZE * VIRTUAL_SCREEN_SIZE, false);
}

// Clears the screen and immediately renders the cleared state
void VirtualScreen::clearScreen() {
    clear(); // Reset pixel states
    render(); // Render the cleared screen
}
