#pragma once
#define MAX 1000000007

void Swap(int* nums, int i, int j) {
	int temp = nums[i];
	nums[i] = nums[j];
	nums[j] = temp;
}

int Partion(int* nums, int left, int right) {
	int pivot = left, index = pivot + 1;
	for (int i = index; i <= right; i++) {
		if (nums[i] > nums[pivot]) {
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

int Min(int a, int b) {
	return a > b ? b : a;
}

unsigned long long calcSum(int max, int len) {
	unsigned long long ret = ((unsigned long long)max * 2 - (unsigned long long)len + 1) * (unsigned long long)len / 2;
	return ret % MAX;
}

int maxProfit(int* inventory, int inventorySize, int orders) {
	QuickSort(inventory, inventorySize);
	if (inventorySize == 1) {
		return calcSum(inventory[0], orders);
	}
	long long ret = 0;
	int times = 1;
	while (orders > 0) {
		if (orders <= times) {
			ret = (ret + (unsigned long long)orders * inventory[0]) % MAX;
			break;
		}
		int num = Min(inventory[0] - (times >= inventorySize ? 0 : inventory[times]), orders / times);
		ret = (ret + calcSum(inventory[0], num) * times) % MAX;
		inventory[0] = inventory[0] - num;
		orders -= num * times;
		times++;
	}
	return ret;
}