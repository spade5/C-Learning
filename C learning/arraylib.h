#pragma once
#include <stdlib.h>

int** create2DArray(int row, int col) {
	int** p = (int**)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++) {
		p[i] = (int*)malloc(sizeof(int) * col);
		for (int j = 0; j < col; j++) {
			p[i][j] = 0;
		}
	}
	return p;
}