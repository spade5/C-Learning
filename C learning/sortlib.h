#pragma once

void BubbleSort(int* nums, int numsSize) {
	int temp, i, j;
	for (i = 0; i < numsSize - 1; i++) {
		for (j = 0; j < numsSize - i - 1; j++) {
			if (nums[j] > nums[j + 1]) {
				temp = nums[j + 1];
				nums[j + 1] = nums[j];
				nums[j] = temp;
			}
		}
	}
}

void InsertSort(int* nums, int numsSize) {
	int temp, i, j;
	for (i = 1; i < numsSize; i++) {
		temp = nums[i];
		for (j = i - 1; j >= 0; j--) {
			if (temp < nums[j]) {
				nums[j + 1] = nums[j];
			}
			else {
				break;
			}
		}
		nums[j + 1] = temp;
	}
}

void Swap(int* nums, int i, int j) {
	int temp = nums[i];
	nums[i] = nums[j];
	nums[j] = temp;
}

int Partion(int* nums, int left, int right) {
	int pivot = left, index = pivot + 1;
	for (int i = index; i <= right; i++) {
		if (nums[i] < nums[pivot]) {
			Swap(nums, i, index);
			index++;
		}
	}
	Swap(nums, pivot, index - 1);
	return index - 1;
}

void QuickSort2(int* nums, int left, int right) {
	if (left >= right) return;
	int partionIndex = Partion(nums, left, right);
	if (partionIndex > left) {
		QuickSort2(nums, left, partionIndex);
	}
	if (partionIndex + 1 < right) {
		QuickSort2(nums, partionIndex + 1, right);
	}
}

void QuickSort(int* nums, int numsSize) {
	QuickSort2(nums, 0, numsSize - 1);
}

/*int nums[N];
for (int i = 0; i < N; i++) {
	nums[i] = rand() % N;
	printf("%d,", nums[i]);
}
printf("\n");

QuickSort(nums, N);
for (int i = 0; i < N; i++) {
	printf("%d,", nums[i]);
}*/