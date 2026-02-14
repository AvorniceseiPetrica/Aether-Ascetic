## Introduction / Motivation

This repository hosts a game I made using C++ and the SDL3 library. It is a 2D platformer with melee fighting elements. While many names went through my head while settling for a title, I went with "Aether Ascetic". The overall vibe of the game reflects a lone monk trying to defeat the forces of evil while traversing platforms up in the sky. <br> 
The motivation behind this project was mainly strengthening my coding skills and knowledge about common gaming concepts and mechanisms. Although it's not perfect, I feel happy with the final product and I wish fun upon anyone who decides to check my work as well.

## How to Build and Run

To play the game, you need a Linux environment (since the pre-compiled SDL3 libraries included are for Linux x86_64).

1.  **Clone the repository.**
2.  **Prerequisites:** Ensure you have `make` and a C++ compiler compatible with C++20 (e.g., `g++` version 10 or higher).
3.  **Build:** Run the `make` command inside the main folder.
    ```bash
    make
    ```
4.  **Run:** execute the generated binary:
    ```bash
    ./aa
    ```

*Note: All relevant SDL3 libraries are included locally in the `SDL/` directory, so no global installation of SDL3 is required.*
