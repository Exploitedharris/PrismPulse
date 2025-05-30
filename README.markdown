# PrismPulse: A 2D Reflex-Puzzle Game

## Overview
PrismPulse is an innovative 2D reflex-puzzle game built in C++ using the SFML library. Players align prismatic lenses on a grid to redirect light beams and activate crystal receptors, while dodging disruptive shadow pulses that scramble lens alignments. The game combines quick reflexes with strategic puzzle-solving, offering a unique experience distinct from traditional puzzle or reflex games.

This open-source project is designed for developers, gamers, and educators interested in C++ game development, light-based mechanics, and dynamic reflex challenges. By sponsoring PrismPulse via GitHub Sponsors, you support new features, level designs, and educational resources for the community.

## Features
- **Prismatic Lens Mechanics**: Rotate lenses to redirect light beams to receptors.
- **Shadow Pulse Challenges**: Dodge or counter pulses that disrupt lens alignments.
- **Minimalist Visuals**: Clean 2D graphics with glowing light and shadow effects.
- **Cross-Platform**: Runs on Windows, macOS, and Linux via SFML.
- **Modular Codebase**: Well-structured C++ code for easy extension and learning.

## Getting Started

### Prerequisites
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support.
- **SFML Library**: Version 2.5.1 or later (install via [SFML's official site](https://www.sfml-dev.org/) or package manager).
- **CMake**: Version 3.10 or later for building.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/prismpulse.git
   cd prismpulse
   ```
2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
3. Configure with CMake:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   cmake --build .
   ```
5. Run the game:
   ```bash
   ./PrismPulse
   ```

## Gameplay
- **Objective**: Activate all crystal receptors by redirecting light beams with lenses, while avoiding shadow pulse disruptions.
- **Controls**:
  - **Arrow Keys**: Move the cursor on the grid.
  - **Space**: Rotate the lens at the cursor (90-degree increments).
  - **Enter**: Counter a shadow pulse.
  - **R**: Reset the level.
  - **Esc**: Pause or exit.
- **Mechanics**: Lenses redirect light beams based on their orientation. Shadow pulses randomly rotate lenses, increasing disruption. Counter pulses strategically to maintain beam alignment.

## Project Structure
- `src/main.cpp`: Game entry point and main loop.
- `src/Entity.hpp`: Base class for game entities (lenses, beams, receptors, pulses).
- `src/Game.hpp`: Core game logic, light redirection, and rendering.
- `assets/`: Placeholder for textures/fonts (add your own or use SFML defaults).

## Contributing
Contributions are welcome! Fork the repo, create a feature branch, and submit a pull request. For major changes, open an issue to discuss your ideas.

## Sponsorship
Support PrismPulse’s development through [GitHub Sponsors](https://github.com/sponsors/yourusername)! Your contributions fund:
- New lens types and receptor patterns.
- Enhanced shadow pulse mechanics and visual effects.
- Tutorials for C++ and light-based game mechanics.
- Optimizations for broader platform support.

## License
Licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments
- Built with [SFML](https://www.sfml-dev.org/) for graphics and input.
- Inspired by light-based puzzles and reflex-driven challenges.
- Thanks to the open-source community for feedback and inspiration.

---

**Sponsor PrismPulse to illuminate the future of reflex-puzzle gaming!**