#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ROWS 8
#define COLS 8

// Maze structure definition
typedef struct {
    char grid[ROWS][COLS];
} Maze;

// Function prototypes
bool inBounds(int row, int col);
bool isOpen(Maze* maze, int row, int col);
void mark(Maze* maze, int row, int col);
void taint(Maze* maze, int row, int col);
bool escapeMaze(Maze* maze, int row, int col);
void printMaze(Maze* maze);
void initializeMaze(Maze* maze);

// Check if position is within maze bounds
bool inBounds(int row, int col) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

// Check if position is open (not wall)
bool isOpen(Maze* maze, int row, int col) {
    return maze->grid[row][col] == ' ' || maze->grid[row][col] == 'E';
}

// Mark position as visited
void mark(Maze* maze, int row, int col) {
    if (maze->grid[row][col] != 'E') {
        maze->grid[row][col] = '*';
    }
}

// Mark position as dead end
void taint(Maze* maze, int row, int col) {
    if (maze->grid[row][col] != 'E') {
        maze->grid[row][col] = 'x';
    }
}

// Main recursive function to solve the maze
bool escapeMaze(Maze* maze, int row, int col) {
    if (!inBounds(row, col)) {
        return false;        // base case 1: out of bounds
    } else if (maze->grid[row][col] == 'E') {
        return true;        // base case 2: found exit
    } else if (!isOpen(maze, row, col)) {
        return false;       // base case 3: blocked
    } else {
        // recursive case: try to escape in 4 directions
        mark(maze, row, col);
        if (escapeMaze(maze, row - 1, col)    // up
            || escapeMaze(maze, row + 1, col)  // down
            || escapeMaze(maze, row, col - 1)  // left
            || escapeMaze(maze, row, col + 1)) // right
        {
            return true;    // one of the paths worked!
        } else {
            taint(maze, row, col);
            return false;   // all 4 paths failed
        }
    }
}

// Print the current state of maze
void printMaze(Maze* maze) {
    printf("\nMaze:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", maze->grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Initialize maze with walls and paths
void initializeMaze(Maze* maze) {
    // Initialize with a sample maze layout
    char sampleMaze[ROWS][COLS] = {
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', '#', '#'},
        {'#', ' ', '#', '#', '#', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', '#', ' ', '#'},
        {'#', '#', '#', ' ', ' ', ' ', ' ', '#'},
        {'#', 'E', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'}
    };
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            maze->grid[i][j] = sampleMaze[i][j];
        }
    }
}

int main() {
    Maze maze;
    initializeMaze(&maze);
    
    printf("Initial maze state:");
    printMaze(&maze);
    
    // Start from position (1,1)
    if (escapeMaze(&maze, 1, 1)) {
        printf("Path found! Final maze state (path marked with *):");
        printMaze(&maze);
        printf("Legend:\n");
        printf("# - Wall\n");
        printf("  - Open path\n");
        printf("* - Path taken\n");
        printf("E - Exit\n");
    } else {
        printf("No escape path found!\n");
    }
    
    return 0;
}