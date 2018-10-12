// BinaryTrees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>

typedef struct tree {
	int item;
	int height;
	//add'tl info for node count
	int lCount;
	int rCount;

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

int getCount(tree *p) {
	return p ? (p->lCount + p->rCount + 1) : 0;
}

tree *rotate_right(tree *p) {
	tree *q = p->left;
	p->left = q->right;
	p->lCount = getCount(p->left);
	q->right = p;
	q->rCount = getCount(q->right);
	recalc(p);
	recalc(q);

	return q;
}

tree *rotate_left(tree *p) {
	tree *q = p->right;
	p->right = q->left;
	p->rCount = getCount(p->right);
	q->left = p;
	q->lCount = getCount(q->left);
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

tree *search_kth_item(tree *p, int k) {
	if (p == NULL) return NULL;
	if (p->lCount + 1 == k) return p;
	if (k > p->lCount) {
		return search_kth_item(p->right, k - (p->lCount + 1));
	}
	else {
		return search_kth_item(p->left, k);
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

tree *find_max(tree *p) {
	tree *max;

	if (p == NULL) return NULL;

	max = p;
	while (max->right != NULL) {
		max = max->right;
	}

	return max;
}

tree *insert_tree(tree *p, int x) {
	tree *t;

	if (p == NULL) {
		t = (tree*)malloc(sizeof(tree));
		t->item = x;
		t->left = t->right = NULL;
		t->height = 1;
		t->lCount = 0;
		t->rCount = 0;
		p = t;
		return p;
	}

	if (x < p->item) {
		p->lCount++;
		p->left = insert_tree(p->left, x);
	}
	else if (x > p->item) {
		p->rCount++;
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

	//t = remove_item(t, 2);
	tree *m = find_min(t);
	tree *mx = find_max(t);
	tree *f = search_kth_item(t, 3);
	tree *s = search_kth_item(t, 6);


	return 0;
}

