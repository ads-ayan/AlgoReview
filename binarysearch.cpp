// BinarySearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int numbers[10001];
int T;
int binarySearch(int arr[], int l, int r, int x)
{
	while (l <= r) {
		int m = l + (r - l) / 2;

		// Check if x is present at mid 
		if (arr[m] == x)
			return m;

		// If x greater, ignore left half 
		if (arr[m] < x)
			l = m + 1;

		// If x is smaller, ignore right half 
		else
			r = m - 1;
	}

	// if we reach here, then element was 
	// not present 
	return -1;
}

int lowerbound(int v) {
	int l, r;
	l = 0;
	r = T;
	while (l != r) {
		int m = l + (r - l) / 2;

		// If x greater, ignore left half 
		if (numbers[m] < v)
			l = m + 1;

		// If x is smaller, ignore right half 
		else
			r = m;
	}
	return l;
}

int upperbound(int v) {
	int l, r;
	l = 0;
	r = T;
	while (l != r) {
		int m = l + (r - l) / 2;

		// If x greater, ignore left half 
		if (numbers[m] <= v)
			l = m + 1;

		// If x is smaller, ignore right half 
		else
			r = m;
	}
	return l;
}

int rangecount(int a, int b) {
	int one = lowerbound(a);
	int two = upperbound(b);
	return two - one;
}

int _tmain(int argc, _TCHAR* argv[])
{
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		int C;
		scanf("%d", &C);
		numbers[i] = C;
	}
	while (1) {
		int c;
		int num;
		scanf("%d", &c);
		if (c == 3) {
			break;
		}

		if (c == 0) {
			scanf("%d", &num);
			printf("%d\n", lowerbound(num));
		}
		else if (c == 1) {
			scanf("%d", &num);
			printf("%d\n", upperbound(num));
		}
		else if (c == 2) {
			int num2;
			scanf("%d %d", &num, &num2);
			printf("%d\n", rangecount(num, num2));
		}

	}
	return 0;
}
