#include <stdio.h>
#include <stdlib.h>
#include "stm8s.h"
#include "delay.h"
#include "conway.h"
#define SIZE 8

int count_neighbors(int grid[SIZE][SIZE], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Skip the cell itself
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                count += grid[nx][ny];
            }
        }
    }
    return count;
}

void update_grid(int grid[SIZE][SIZE]) {
    int new_grid[SIZE][SIZE];

    for (uint8_t i = 0; i < SIZE; i++) {
        for (uint8_t j = 0; j < SIZE; j++) {
            new_grid[i][j] = 0;
        }
    }

    for (uint8_t i = 0; i < SIZE; i++) {
        for (uint8_t j = 0; j < SIZE; j++) {
            int neighbors = count_neighbors(grid, i, j);
            if (grid[i][j]) {
                new_grid[i][j] = (neighbors == 2 || neighbors == 3);
            } else {
                new_grid[i][j] = (neighbors == 3);
            }
        }
    }

    for (uint8_t i = 0; i < SIZE; i++) {
        for (uint8_t j = 0; j < SIZE; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }
}

void grid_to_1d_array(int grid[SIZE][SIZE], uint32_t array[SIZE * SIZE], uint32_t color, uint32_t color_bg) {
    for (int i = 0; i < SIZE; i++) {
        for (uint8_t j = 0; j < SIZE; j++) {
            array[i * SIZE + j] = grid[i][j] ? color : color_bg;
        }
    }
}


