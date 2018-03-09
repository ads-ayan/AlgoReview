// BFS_Lists.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>
#define MAX 10

int Queue[MAX];
int front = -1;
int rear = -1;

void enQueue(int val) {
	if ((front == 0 && rear == MAX - 1) || rear == front - 1) {
		printf("Queue full\n");
	}
	else if (rear == -1 && front == -1) {
		rear = front = 0;
		Queue[rear] = val;
	}
	else if (rear == MAX - 1 && front != 0) {
		rear = 0;
		Queue[rear] = val;
	}
	else {
		rear++;
		Queue[rear] = val;
	}
}

int deQueue() {
	if (front == -1) {
		printf("Queue empty\n");
		return -1;
	}

	int ret = Queue[front];
	if (front == rear) {
		front = -1;
		rear = -1;
	}
	else if (front == MAX - 1) {
		front = 0;
	}
	else {
		front++;
	}

	return ret;
}

int empty_queue() {
	if (front == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

int processed[MAX + 1];
int discovered[MAX + 1];
int parent[MAX + 1];

typedef struct edgenode {
	int y;
	int weight;
	edgenode *next;
} edgenode;

typedef struct graph {
	edgenode *edges[MAX + 1];
	int degree[MAX + 1];
	int nvertices;
	int nedges;
	int directed;
} graph;

void init_graph(graph *g, int directed){
	int i;
	g->nedges = 0;
	g->nvertices = 0;
	g->directed = directed;

	for (i = 1; i <= MAX; i++) g->degree[i] = 0;
	for (i = 1; i <= MAX; i++) g->edges[i] = NULL;
}

void insert_edge(graph *g, int x, int y, int directed) {
	edgenode *p;
	p = (edgenode *)malloc(sizeof(edgenode));
	p->y = y;
	p->weight = 1;
	p->next = g->edges[x];

	g->edges[x] = p;
	g->degree[x]++;
	if (directed == 0) {
		insert_edge(g, y, x, 1);
	}
	else {
		g->nedges++;
	}
}

void print_graph(graph *g) {
	int i;
	edgenode *p;

	for (i = 1; i <= g->nvertices; i++) {
		printf("%d: ", i);
		p = g->edges[i];
		while (p != NULL) {
			printf(" %d", p->y);
			p = p->next;
		}
		printf("\n");
	}
}

void init_bfs(graph *g) {
	for (int i = 1; i <= g->nvertices; i++) {
		processed[i] = discovered[i] = 0;
		parent[i] = -1;
	}
}

void bfs(graph *g, int start) {
	int v;
	int y;
	edgenode *p;

	enQueue(start);
	discovered[start] = 1;
	while (empty_queue() == 0) {
		v = deQueue();
		p = g->edges[v];
		//process vertex early
		while (p != NULL) {
			y = p->y;
			if ((processed[y] == 0) || g->directed) {
				//process edge
			}
			if (discovered[y] == 0) { // or not equal to test case number
				enQueue(y);
				discovered[y] = 1;
				parent[y] = v;
			}
			p = p->next;
		}
		//process vertex late
	}
}

int finished;

void dfs(graph *g, int v) {
	edgenode *p;
	int y;

	if (finished == 1) return;

	discovered[v] = 1;
	//time
	//process vertex early
	p = g->edges[v];
	while (p != NULL) {
		y = p->y;
		if (discovered[y] == 0) { // or not equal to test case number
			parent[y] = v;
			//process edge
			dfs(g, y);
		}
		else if ((processed[y] == 0) || (g->directed == 1)) {
			//process ege
		}

		if (finished == 1) return;
		p = p->next;
	}

	//process vertex late
	processed[v] = 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

