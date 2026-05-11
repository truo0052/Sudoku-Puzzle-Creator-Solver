#Sudoku Puzzle Creator/Solver

An interactive command-line Sudoku puzzle application written in C that supports dynamic grid sizes.

## Features

- **Dynamic Grid Sizing**: Create Sudoku grids of any size that's a multiple of 3 (3×3, 6×6, 9×9, 12×12, etc.)
- **Input Validation**: Real-time validation of user inputs to ensure Sudoku rules are followed
- **Interactive Menu**: User-friendly menu system for easy navigation
- **Memory Management**: Proper dynamic memory allocation and deallocation

## Menu Options

1. **Generate a New Sudoku Puzzle** - Create a new grid with custom dimensions
2. **Input Grid Values** - Fill in the Sudoku grid with validation
3. **Display the Current Grid** - View the current state of the puzzle
4. **Clear & Restart** - Reset and create a new puzzle
5. **Exit** - Close the program

## Validation Rules

- Numbers must be between 0 (empty cell) and the grid size
- No duplicate numbers in the same row
- No duplicate numbers in the same column

## Compilation

```bash
gcc main.c -o sudoku
