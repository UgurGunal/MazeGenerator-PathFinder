# Maze Generator and Path Finder

This C++ project implements a maze generator and path finder. The maze generator utilizes the recursive backtracking algorithm to create mazes of specific dimensions. The path finder then helps find a unique path between chosen start and end points within the generated maze.

## Maze Properties

- Each cell in the maze is reachable from any other cell.
- There is a single unique path for each start and end point pair.

## Setup

1. Download the zip file and extract the `mazeDrawer` application.
2. Place the `mazeDrawer` application in the project directory.

## Running the Program

1. Run the program.
2. Enter the number of mazes to generate.
3. Specify the number of rows and columns for each maze.
4. Choose the entry point and end point for the path finder algorithm.
   - Note: Ensure that the coordinates of the start and end points are within the dimensions of the maze.
5. After entering the correct inputs, mazes are generated in the project directory as text files (e.g., `maze_1.txt`).

## Viewing the Generated Mazes

To convert the generated text files into visual mazes, follow these steps:

1. Run the `mazeDrawer` application.
2. Enter the name of the text file you want to visualize (e.g., `maze_1.txt`).
3. After the program terminates, open the `mazeDrawn.txt` file to view the generated maze.
- Note: `mazeDrawer` application only works for generating maze files. It is not possible to visualize path files.

Ensure that you carefully specify the coordinates for the start and end points to guarantee a unique path within the maze boundaries. Explore the generated mazes and enjoy experimenting with different configurations!
