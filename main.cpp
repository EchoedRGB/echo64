#include "screen.h"
#include <chrono>
#include <thread>

// Function to create a delay in milliseconds
void delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int main() {
    VirtualScreen screen; // Create an instance of VirtualScreen

    // Initialize the virtual screen; exit if it fails
    if (!screen.initScreen()) {
        return -1;
    }

    // Add pixels at the corners of the virtual screen
    screen.addPixel(0, 0);     // Top-left corner
    screen.addPixel(63, 63);   // Bottom-right corner

    screen.render(); // Render the current state of the screen
    delay(1000);     // Wait for 1 second to view the pixels
    screen.clearScreen(); // Clear the screen

    return 0; // Exit the program successfully
}
