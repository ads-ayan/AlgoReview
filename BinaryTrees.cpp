// BinaryTrees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>

typedef struct tree {
	int item;
	int height;
	tree *left;
	tree *right;
} tree;

int height(tree *p) {
	return p ? p->height : 0;
}

int max(int a, int b) {
	return a > b ? a : b;
}

void recalc(tree *p) {
	p->height = 1 + max(height(p->left), height(p->right));
}

tree *rotate_right(tree *p) {
	tree *q = p->left;
	p->left = q->right;
	q->right = p;

	recalc(p);
	recalc(q);

	return q;
}

tree *rotate_left(tree *p) {
	tree *q = p->right;
	p->right = q->left;
	q->left = p;

	recalc(p);
	recalc(q);

	return q;
}

tree *balance(tree *p) {
	recalc(p);

	if (height(p->left) - height(p->right) == 2) {
		if (height(p->left->right) > height(p->left->left)) {
			p->left = rotate_left(p->left);
		}

		return rotate_right(p);
	}
	else if (height(p->right) - height(p->left) == 2) {
		if (height(p->right->left) > height(p->right->right)) {
			p->right = rotate_right(p->right);
		}

		return rotate_left(p);
	}

	return p;
}

tree *search_item(tree *p, int x) {
	if (p == NULL) return NULL;
	if (p->item == x) return p;
	if (x < p->item) {
		return search_item(p->left, x);
	}
	else if (x > p->item) {
		return search_item(p->right, x);
	}
}

tree *find_min(tree *p) {
	tree *min;

	if (p == NULL) return NULL;

	min = p;
	while (min->left != NULL) {
		min = min->left;
	}

	return min;
}

tree *insert_tree(tree *p, int x) {
	tree *t;

	if (p == NULL) {
		t = (tree*)malloc(sizeof(tree));
		t->item = x;
		t->left = t->right = NULL;
		t->height = 1;
		p = t;
		return p;
	}

	if (x < p->item) {
		p->left = insert_tree(p->left, x);
	}
	else if (x > p->item) {
		p->right = insert_tree(p->right, x);
	}

	return balance(p);
}

tree *remove_item(tree *p, int x) {
	if (p == NULL) return NULL;

	if (p->item > x) {
		p->left = remove_item(p->left, x);
	}
	else if (p->item < x) {
		p->right = remove_item(p->right, x);
	}
	else {
		if (p->left == NULL) {
			tree *temp = p->right;
			free(p);
			return temp;
		}
		else if (p->right == NULL) {
			tree *temp = p->left;
			free(p);
			return temp;
		}

		tree *temp = find_min(p->right);
		p->item = temp->item;
		p->right = remove_item(p->right, p->item);
	}

	return balance(p);
}


int _tmain(int argc, _TCHAR* argv[])
{
	tree *t = NULL;
	t = insert_tree(t, 1);
	t = insert_tree(t, 2);
	t = insert_tree(t, 3);
	t = insert_tree(t, 4);
	t = insert_tree(t, 5);
	t = insert_tree(t, 6);
	t = insert_tree(t, 7);
	t = insert_tree(t, 8);

	t = remove_item(t, 2);
	return 0;
}

