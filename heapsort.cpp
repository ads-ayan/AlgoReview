// HeapSort_PriorityQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>

#define PQ_SIZE 10

typedef struct priority_queue {
	int q[PQ_SIZE + 1];
	int n;
} priority_queue;

int pq_parent(int n) {
	if (n == 1) return (-1);
	else return ((int)n / 2);
}

int pq_young_child(int n) {
	return(2 * n);
}

void pq_swap(priority_queue *q, int child, int parent) {
	int temp = q->q[child];
	q->q[child] = q->q[parent];
	q->q[parent] = temp;
}

void bubble_up(priority_queue *q, int p) {
	if (pq_parent(p) == -1) return;

	if (q->q[pq_parent(p)] > q->q[p]) {
		pq_swap(q, p, pq_parent(p));
		bubble_up(q, pq_parent(p));
	}
}

void pq_insert(priority_queue *q, int i) {
	if (q->n >= PQ_SIZE) {
		printf("queue overflow\n");
	}
	else {
		q->n = (q->n) + 1;
		q->q[q->n] = i;
		bubble_up(q, q->n);
	}
}

void bubble_down(priority_queue *q, int p) {
	int c;
	int i;
	int min_index;

	c = pq_young_child(p);
	min_index = p;

	for (i = 0; i <= 1; i++) {
		if ((c + i) <= q->n) {
			if (q->q[min_index] > q->q[c + i]) min_index = c + i;
		}
	}

	if (min_index != p) {
		pq_swap(q, p, min_index);
		bubble_down(q, min_index);
	}
}

int extract_min(priority_queue *q) {
	int min = -1;

	if (q->n <= 0) {
		printf("Empty\n");
	}
	else {
		min = q->q[1];

		q->q[1] = q->q[q->n];
		q->n = q->n - 1;
		bubble_down(q, 1);
	}

	return min;
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

