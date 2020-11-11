#pragma once

#include "arraylib.h"

int superEggDrop(int K, int N) {
	int** dp = create2DArray(K + 1, N + 1);
	int m = 0;
	
	while (dp[K][m] < N) {
		m++;
		for (int i = 1; i <= K; i++) {
			dp[i][m] = dp[i][m - 1] + dp[i - 1][m - 1] + 1;
			printf("k:%d, m:%d, dp[k][m]:%d\n", i, m, dp[i][m]);
		}
	}

	return m;
}

void superEggDropTest() {
	printf("%d\n", superEggDrop(3, 14));
}