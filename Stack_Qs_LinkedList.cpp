// Coding_Exer_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>
#define MAX 20

typedef struct Queue {
	int capacity;
	int size;
	int front;
	int rear;
	int *elements;
} Queue;

Queue *createQueue(int max) {
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->capacity = max;
	q->front = 0;
	q->rear = -1;
	q->size = 0;
	q->elements = (int *)malloc(sizeof(int) * max);
	return q;
}

int isFull(Queue *q) {
	if (q->size == q->capacity) {
		return 1;
	}
	else {
		return 0;
	}
}

int isEmpty(Queue *q) {
	if (q->size == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void Enqueue(Queue *q, int x) {
	if (isFull(q)) {
		//full
	}
	else {
		q->rear++;
		q->size++;
		if (q->rear == q->capacity) {
			q->rear = 0;
		}
		q->elements[q->rear] = x;
	}
}

int Dequeue(Queue *q) {
	if (isEmpty(q)) {
		//empty
		return -1;
	}
	else {
		int val = q->elements[q->front];
		q->front++;
		q->size--;
		if (q->front == q->capacity) {
			q->front = 0;
		}
		return val;
	}
}

typedef struct Stack {
	int capacity;
	int size;
	int top;
	int *elements;
} Stack;

Stack *createStack(int capacity) {
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->capacity = capacity;
	s->size = 0;
	s->top = -1;
	s->elements = (int *)malloc(capacity * sizeof(int));
	return s;
}

int isStackFull(Stack *s) {
	if (s->size == s->capacity) {
		return 1;
	}
	else {
		return 0;
	}
}

int isStackEmpty(Stack *s) {
	if (s->size == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void Push(Stack *s, int e) {
	if (isStackFull(s)) {
		//full
	}
	else {
		s->top++;
		s->size++;
		s->elements[s->top] = e;
	}
}

int Pop(Stack *s) {
	if (isStackEmpty(s)) {
		return -1;
	}
	else {
		int ret = s->elements[s->top];
		s->top--;
		s->size--;
		return ret;
	}
}

typedef struct doublyNode {
	int val;
	doublyNode *next;
	doublyNode *prev;
} doublyNode;

void insert_front(doublyNode *node, int val) {
	if (node == NULL) return;
	doublyNode *p = (doublyNode *)malloc(sizeof(doublyNode));
	p->val = val;
	doublyNode *next = node->next;
	node->next = p;
	p->prev = node;
	p->next = next;
	if (next != NULL)
		next->prev = p;
}

void remove_front(doublyNode *node) {
	doublyNode *next = node->next;
	if (next != NULL) {
		node->next = next->next;
		next->next->prev = node;
		next = NULL;
		free(next);
	}
}

void insert_back(doublyNode *node, int val) {
	if (node == NULL) return;
	doublyNode *p = (doublyNode *)malloc(sizeof(doublyNode));
	p->val = val;
	doublyNode *prev = node->prev;
	if (prev != NULL)
		prev->next = p;
	node->prev = p;
	p->next = node;
	p->prev = prev;
}

void remove_back(doublyNode *node) {
	doublyNode *prev = node->prev;
	if (prev != NULL) {
		node->prev = prev->prev;
		prev->prev->next = node;
		prev = NULL;
		free(prev);
	}
}

void move_to_front(doublyNode *src, doublyNode *dst) {
	if (src->prev != NULL) {
		remove_front(src->prev);
	}
	else if (src->next != NULL) {
		remove_back(src->next);
	}
	if (dst != NULL) 
		insert_front(dst,src->val);
	/*if (src->prev != NULL)
		src->prev->next = src->next;
	if (src->next != NULL)
		src->next->prev = src->prev;
	if (dst->next != NULL)
		dst->next->prev = src;
	src->next = dst->next;
	src->prev = dst;
	dst->next = src;*/
}

int _tmain(int argc, _TCHAR* argv[])
{
	Queue *sampleQ = createQueue(200);
	doublyNode *HEAD = (doublyNode *)malloc(sizeof(doublyNode));
	HEAD->prev = NULL;
	doublyNode *TAIL = (doublyNode *)malloc(sizeof(doublyNode));
	TAIL->next = NULL;
	doublyNode *one = (doublyNode *)malloc(sizeof(doublyNode));
	one->val = 1;
	doublyNode *two = (doublyNode *)malloc(sizeof(doublyNode));
	two->val = 2;
	one->prev = HEAD;
	one->next = two;
	two->prev = one;
	two->next = TAIL;
	HEAD->next = one;
	TAIL->prev = two;
	insert_front(two, 3);
	move_to_front(one,two);
	return 0;
}

