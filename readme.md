# Echo64 - 64x64 Virtual Screen Simulation

## Overview

Echo64 is a simple SDL2-based virtual screen simulation that displays a 64x64 pixel grid. Users can add white pixels to the grid by clicking on the window, allowing for a basic drawing interface.

## Features

- **64x64 Pixel Grid**: Visualize a virtual screen where each pixel can be individually activated.
- **Dynamic Pixel Addition**: Click on the screen to add white pixels.
- **Grid Visualization**: A grid is drawn for reference, making it easy to see individual pixels.

## Requirements

- C++11 or later
- [SDL2](https://www.libsdl.org/download-2.0.php)

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/EchoedRGB/Echo64.git
   cd Echo64
   ```

2. **Install SDL2**: Follow the instructions on the [SDL2 website](https://www.libsdl.org/download-2.0.php) for your platform.

3. **Compile the code**:
   ```bash
   g++ -o screen screen.cpp -lSDL2
   ```

## Usage

Run the compiled program:
```bash
./screen
```

Click on the window to add white pixels to the virtual screen.

## Contributing

Feel free to submit issues or pull requests. Contributions are welcome!

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Thanks to the SDL2 community for their incredible work and support.
