#define B buffer[1024]

/**
 *    ░██     ░██                       ░██           ░██                 ░██████                     ░██            ░██
 *    ░██    ░██                                      ░██                ░██   ░██                    ░██            ░██
 *    ░██   ░██    ░███████  ░██    ░██ ░██░████████  ░██  ░███████     ░██          ░███████   ░████████  ░███████  ░██    ░██░██    ░██
 *    ░███████    ░██    ░██ ░██    ░██ ░██░██    ░██     ░██            ░████████  ░██    ░██ ░██    ░██ ░██    ░██ ░██   ░██ ░██    ░██
 *    ░██   ░██   ░█████████  ░██  ░██  ░██░██    ░██      ░███████             ░██ ░██    ░██ ░██    ░██ ░██    ░██ ░███████  ░██    ░██
 *    ░██    ░██  ░██          ░██░██   ░██░██    ░██            ░██     ░██   ░██  ░██    ░██ ░██   ░███ ░██    ░██ ░██   ░██ ░██   ░███
 *    ░██     ░██  ░███████     ░███    ░██░██    ░██      ░███████       ░██████    ░███████   ░█████░██  ░███████  ░██    ░██ ░█████░██
 *
 *
 *
 */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void display_Menu(void);
int getSudokuSize(const char* prompt);
void getInputSudokuGrid(int** grid, int s);
int** createSudokuGrid(int s);
void printSudokuGrid(int** grid, int s);
int isValid(int** grid, int s, int row, int col, int num);


void display_Menu(void) {
    printf("\nKevin's Sudoku\n1. Generate a New Sudoku Puzzle\n2. Input Grid Values\n3. Display the Current Grid\n4. Clear & Restart\nX. Exit the Program\nEnter your choice (1/2/3/4/X): ");
}

// Function to get grid SIZE from user
int getSudokuSize(const char* prompt) {
    int valid_input;
    int result;

    do {
        printf("%s", prompt);
        result = scanf("%d", &valid_input);

        if (result != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (valid_input % 3 == 0 && valid_input > 0) {
            printf("Creating %dx%d Sudoku...\n", valid_input, valid_input);
            break;
        } else {
            printf("Wrong input. Please enter a multiple of 3 (3, 6, 9, 12, etc.).\n");
            while (getchar() != '\n');
        }

    } while (1);

    return valid_input;
}

void getInputSudokuGrid(int** grid, int s) {
    printf("\nEnter the Sudoku puzzle row by row (use 0 for empty cells):\n");
    printf("Enter numbers separated by spaces.\n\n");

    for (int i = 0; i < s; i++) {
        printf("Row %d: ", i + 1);

        for (int j = 0; j < s; j++) {
            int input;
            int result;

            do {
                result = scanf("%d", &input);

                if (result != 1) {
                    printf("Invalid input! Enter a number: ");
                    while (getchar() != '\n');
                    continue;
                }

                if (input < 0 || input > s) {
                    printf("Number must be between 0 and %d: ", s);
                    continue;  // No need to clear buffer here
                }

                // If not 0, check if valid placement
                if (input != 0 && !isValid(grid, s, i, j, input)) {
                    const int *pI = &i;
                    const int *pJ =&j;
                    printf("\nIssue on Row[%d] Col[%d]:\n", *pI+1, *pJ+1);
                    printSudokuGrid(grid, s);
                    printf("Try again: ");
                    while (getchar() != '\n') {}
                    continue;  // CHANGED from break to continue
                }

                grid[i][j] = input;
                break;  // Only break when input is valid

            } while (1);

        }
    }
    printf("\nGrid input complete!\n");
}



int** createSudokuGrid(int s) {
    int **grid = malloc(s * sizeof(int*));
    for (int i = 0; i < s; i++) {
        grid[i] = malloc(s * sizeof(int));
        for (int j = 0; j < s; j++) {
            grid[i][j] = 0;
        }
    }
    return grid;
}

void printSudokuGrid(int** grid, int s) {
    printf("\n");
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

int isValid(int** grid, int s, int row, int col, int num) {
    // Check if num already exists in the row
    for (int j = 0; j < s; j++) {
        if (grid[row][j] == num) {
            return 0;
        }
    }

    // Check if num already exists in the column
    for (int i = 0; i < s; i++) {
        if (grid[i][col] == num) {
            return 0;
        }
    }


    return 1;
}

int main(void) {
    int **grid = NULL;
    int s = 0;
    char ch;

    do {
        display_Menu();
        scanf(" %c", &ch);

        switch (toupper(ch)) {
            case '1':
                if (s > 0) {  // Changed from s > 1
                    printf("You have already generated a grid. Use option 4 to clear first.\n");
                    break;
                }

                s = getSudokuSize("Enter the size of Sudoku grid (e.g., 9 for 9x9): ");
                grid = createSudokuGrid(s);
                printf("Grid has been created.\n");
                break;

            case '2': // Input grid value should be move below

                printf("The current grid:");
                printSudokuGrid(grid, s);
                if (grid == NULL || s == 0) {
                    printf("The grid is empty. Go back and select option 1\n");
                    break;  // REMOVED extra break
                }
                getInputSudokuGrid(grid, s);
                break;

            case '3':
                if (grid == NULL || s == 0) {
                    printf("The grid is empty. Go back and select option 1\n");
                    break;
                }
                printf("\nCurrent Sudoku Grid:");
                printSudokuGrid(grid, s);
                break;

            case '4':
                if (grid != NULL) {
                    for (int i = 0; i < s; i++) {
                        free(grid[i]);
                    }
                    free(grid);
                    grid = NULL;
                    s = 0;
                    printf("Grid cleared! You can now create a new one.\n");
                }
                break;

            case 'X':
                // Free memory before exiting
                if (grid != NULL) {
                    for (int i = 0; i < s; i++) {
                        free(grid[i]);
                    }
                    free(grid);
                }
                printf("<--- Exiting... --->\n");
                break;

            default:
                printf("<--- Error: Invalid Option --->\n");
                break;
        }

    } while (toupper(ch) != 'X');

    return 0;
}
