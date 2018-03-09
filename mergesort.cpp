// MergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>

typedef struct Queue {
	int capacity;
	int size;
	int front;
	int rear;
	int *elements;
} Queue;

Queue *initQ(int max) {
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q->capacity = max;
	q->front = -1;
	q->rear = -1;
	q->elements = (int*)malloc(max*sizeof(int));
	return q;
}

int enqueue(Queue *q, int x) {
	if ((q->front == 0 && q->rear == q->capacity-1) || q->rear == q->front - 1) {
		return -1;
	}
	else if (q->front == -1 && q->rear == -1) {
		q->front = q->rear = 0;
		q->elements[q->rear] = x;
	}
	else if (q->rear == q->capacity - 1 && q->front != 0) {
		q->rear = 0;
		q->elements[q->rear] = x;
	}
	else {
		q->rear = q->rear + 1;
		q->elements[q->rear];
	}
	return 0;
}

int dequeue(Queue *q) {
	if (q->front == -1) {
		return -1;
	}

	int ret = q->elements[q->front];
	if (q->front == q->rear) {
		q->front = q->rear = -1;
	}
	else if (q->front == q->capacity - 1) {
		q->front = 0;
	}
	else {
		q->front++;
	}

	return ret;
}

int empty_queue(Queue *q) {
	if (q->front == -1) return 1;
	return 0;
}

void merge(int s[], int low, int middle, int high) {
	int i;
	Queue *buffer1, *buffer2;

	buffer1 = initQ(100);
	buffer2 = initQ(100);
	
	for (i = low; i < middle; i++){
		enqueue(buffer1, s[i]);
	}
	for (i = middle + 1; i < high; i++){
		enqueue(buffer2, s[i]);
	}

	i = low;
	while (!(empty_queue(buffer1) || empty_queue(buffer2))) {
		if (buffer1->elements[buffer1->front] <= buffer2->elements[buffer2->front]) {
			s[i++] = dequeue(buffer1);
		}
		else {
			s[i++] = dequeue(buffer2);
		}
	}

	while (!empty_queue(buffer1)) s[i++] = dequeue(buffer1);
	while (!empty_queue(buffer2)) s[i++] = dequeue(buffer2);
}

void mergesort(int s[], int low, int high) {
	int middle;

	if (low < high) {
		middle = (low + high) / 2;
		mergesort(s, low,middle);
		mergesort(s, middle + 1, high);
		merge(s, low, middle, high);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

