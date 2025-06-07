/*
    https://www.janestreet.com/puzzles/sum-of-squares-index/
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define GRID_SIZE 5
#define TOTAL_SIZE (GRID_SIZE * GRID_SIZE)

int result[TOTAL_SIZE];
int max_sum = 0;
long search_count = 0;
int row_divisors[] = {1, 2, 3, 4, 5};
int col_divisors[] = {6, 7, 8, 9, 10};
int pow_of_10[] = { 1, 10, 100, 1000, 10000 };

typedef struct {
    int row;
    int col;
} CellPos;

CellPos cell_order[] = {
    {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4},
    {4, 0}, {4, 1}, {4, 2}, {4, 3},
    {0, 0}, {0, 1}, {0, 2}, {0, 3},
    {1, 0}, {1, 1}, {1, 2}, {1, 3},
    {2, 0}, {2, 1}, {2, 2}, {2, 3},
    {3, 0}, {3, 1}, {3, 2}, {3, 3}
};

int cell_order_size = sizeof(cell_order) / sizeof(cell_order[0]);

inline bool is_even(int num) {
    return num % 2 == 0;
}

inline int row_to_num(int grid[], int row) {
    int num = 0;

    for (int i = 0; i < GRID_SIZE; i++) {
        num += grid[row * GRID_SIZE + i] * pow_of_10[4 - i];
    }

    return num;
}

inline bool row_divisible_by(int grid[], int row, int number) {
    return row_to_num(grid, row) % number == 0;
}

inline int col_to_num(int grid[], int col) {
    int num = 0;

    for (int i = 0; i < GRID_SIZE; i++) {
        num += grid[i * GRID_SIZE + col] * pow_of_10[4 - i];
    }

    return num;
}

inline bool col_divisible_by(int grid[], int col, int number) {
    return col_to_num(grid, col) % number == 0;
}

int sum_grid(int grid[]) {
    int sum = 0;

    for (int i = 0; i < TOTAL_SIZE; i++) {
        sum += grid[i];
    }

    return sum;
}

void print_grid(int grid[]) {
    printf("[");

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            printf("%d", grid[i * GRID_SIZE + j]);

            if (j < GRID_SIZE - 1) {
                printf(", ");
            }
        }

        if (i < GRID_SIZE - 1) {
            printf("\n");
        }
    }

    printf("]\n");
}

void solve_grid(int grid[], int index) {
    int total = sum_grid(grid);

    if ((total + (TOTAL_SIZE - index) * 9) <= max_sum)
    {
        return;
    }
    
    if (index == TOTAL_SIZE) {
        bool valid = true;

        for (int r = 0; r < GRID_SIZE && valid; r++) {
            if (!row_divisible_by(grid, r, row_divisors[r])) {
                valid = false;
            }
        }
        
        for (int c = 0; c < GRID_SIZE && valid; c++) {
            if (!col_divisible_by(grid, c, col_divisors[c])) {
                valid = false;
            }
        }
        
        if (valid) {
            if (total > max_sum) {
                max_sum = total;
                memcpy(result, grid, sizeof(int) * TOTAL_SIZE);
            }
        }

        return;
    }

    search_count++;
    
    int row = cell_order[index].row;
    int col = cell_order[index].col;
    int pos = row * GRID_SIZE + col;
    
    for (int digit = 9; digit >= 0; digit--) {
        grid[pos] = digit;
        
        if (col == GRID_SIZE - 1) {
            if (!row_divisible_by(grid, row, row_divisors[row])) {
                continue;
            }
        }
        
        if (row == GRID_SIZE - 1) {
            if (!col_divisible_by(grid, col, col_divisors[col])) {
                continue;
            }
        }
        
        solve_grid(grid, index + 1);
    }
    
    grid[pos] = 0;
}

void sum_of_squares() {
    int grid[TOTAL_SIZE];
    
    memset(grid, 0, TOTAL_SIZE * sizeof(int));
    memset(result, 0, TOTAL_SIZE * sizeof(int));
    
    solve_grid(grid, 0);
    
    printf("RESULT (%ld searches)\n", search_count);

    print_grid(result);
    
    printf("Max sum: %d\n", max_sum);
}

int main() {
    sum_of_squares();
    return 0;
}