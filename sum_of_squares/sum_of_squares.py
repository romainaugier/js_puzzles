#!/usr/bin/env python3

# https://www.janestreet.com/puzzles/sum-of-squares-index/

import typing

GRID_SIZE = 5

def is_even(num: int) -> bool:
    return num % 2 == 0

def is_odd(num: int) -> bool:
    return num % 2 != 0

def row_to_num(grid: typing.List[int], row: int) -> int:
    return int(''.join(str(n) for n in grid[row * GRID_SIZE : (row + 1) * GRID_SIZE]))

def num_to_row(grid: typing.List[int], row: int, num: int) -> None:
    num_str = str(num).zfill(GRID_SIZE)

    for i in range(GRID_SIZE):
        grid[row * GRID_SIZE + i] = int(num_str[i])

def row_divisible_by(grid: typing.List[int], row: int, number: int) -> bool:
    return row_to_num(grid, row) % number == 0

def col_to_num(grid: typing.List[int], col: int) -> int:
    num_str = ''

    for i in range(GRID_SIZE):
        num_str += str(grid[i * GRID_SIZE + col])
    
    return int(num_str)

def num_to_col(grid: typing.List[int], col: int, num: int) -> None:
    num_str = str(num).zfill(GRID_SIZE)

    for i in range(GRID_SIZE):
        grid[i * GRID_SIZE + col] = int(num_str[i])

def col_divisible_by(grid: typing.List[int], col: int, number: int) -> bool:
    return col_to_num(grid, col) % number == 0

def sum_grid(grid: typing.List[int]) -> int:
    return sum(grid)

row_divisors = (1, 2, 3, 4, 5)
col_divisors = (6, 7, 8, 9, 10)

def valid_grid(grid: typing.List[int]) -> bool:
    for i, row_div in enumerate(row_divisors):
        if i == GRID_SIZE:
            break

        if not row_divisible_by(grid, i, row_div):
            return False

    for i, col_div in enumerate(col_divisors):
        if i == GRID_SIZE:
            break

        if not col_divisible_by(grid, i, col_div):
            return False

    return True

result = None
max_sum = 0
search = 0

def solve_grid(grid: typing.List[int], index: int) -> None:
    global result
    global max_sum
    global search
    search += 1

    if index == (GRID_SIZE * GRID_SIZE):
        if not valid_grid(grid):
            return
        
        s = sum_grid(grid)

        if s > max_sum:
            result = grid.copy()
            max_sum = s

        return

    col = index % GRID_SIZE
    row = index // GRID_SIZE

    for digit in range(9, -1, -1):
        old = grid[index]
        grid[index] = digit

        # prune early searches
        if col == (GRID_SIZE - 1):
            divisor = row_divisors[row]

            if not row_divisible_by(grid, row, divisor):
                continue

        if row == (GRID_SIZE - 1):
            divisor = col_divisors[col]

            if not col_divisible_by(grid, col, divisor):
                continue

        solve_grid(grid, index + 1)

        grid[index] = old

def sum_of_squares() -> None:
    global search

    grid = list(0 for _ in range(GRID_SIZE * GRID_SIZE))

    solve_grid(grid, 0) 

    print(f"RESULT ({search} searches)")
    print(result, max_sum)

if __name__ == "__main__":
    sum_of_squares()