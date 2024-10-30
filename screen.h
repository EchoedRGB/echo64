#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <iostream>

// Constants for screen sizes and pixel size
const int REAL_SCREEN_SIZE = 960;  // Size of the actual window
const int VIRTUAL_SCREEN_SIZE = 64; // Size of the virtual grid
const int PIXEL_SIZE = REAL_SCREEN_SIZE / VIRTUAL_SCREEN_SIZE; // Size of each pixel on the screen

class VirtualScreen {
public:
    VirtualScreen(); // Constructor to initialize the virtual screen
    ~VirtualScreen(); // Destructor to clean up resources
    bool initScreen(); // Initializes the SDL window and renderer
    void addPixel(int x, int y); // Adds a pixel at the specified coordinates
    void render(); // Renders the current state of the screen
    void clearScreen(); // Clears the screen and resets pixel states

private:
    SDL_Window* window; // Pointer to the SDL window
    SDL_Renderer* renderer; // Pointer to the SDL renderer
    bool pixels[VIRTUAL_SCREEN_SIZE][VIRTUAL_SCREEN_SIZE]; // Pixel states

    void clear(); // Resets all pixels to false
};

#endif // SCREEN_H
