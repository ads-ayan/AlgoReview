#include <malloc.h>

#include <stdio.h>


int getStrLen2(char* str){
	int len = 0;

	while (str[len]){
		len++;
	}

	return len;
}


typedef struct tree {
	char item[100];
	int height;

	//add'tl info for ropes
	int weight;
	int length;
	//add'tl info for node count
	int lCount;
	int rCount;

	tree *left;
	tree *right;
} tree;

int height(tree *p) {
	return p ? p->height : 0;
}

int length(tree *p) {
	return p ? p->length : 0;
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

int isLeaf(tree *p) {
	if (p->left == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

tree *create(char *str) {
	int len = getStrLen2(str);
	tree *p = (tree *)malloc(sizeof(tree));
	for (int i = 0; i < len; i++) {
		p->item[i] = str[i];
	}

	p->weight = len;
	p->length = len;

	p->left = NULL;
	p->right = NULL;
	return p;
}

char index(tree *root, int idx) {
	if (idx < 1 || idx > root->length) {
		return '\0';
	}

	if (isLeaf(root)) {
		return root->item[idx - 1];
	}
	else if (idx > root->weight) {
		return index(root->right, idx - root->weight);
	}
	else {
		return index(root->left, idx);
	}
}

tree *concat(tree *q, tree *r) {
	if (q == NULL) {
		return r;
	}

	if (r == NULL) {
		return q;
	}

	tree *s = (tree *)malloc(sizeof(tree));
	s->weight = q->length;
	s->length = q->length + r->length;
	s->left = q;
	s->right = r;

	return s;
}

void split(tree *root, int idx, tree **p1, tree **p2) {
	if (idx == root->weight) {
		tree *r;
		if (isLeaf(root)) {
			r = root;
		}
		else {
			r = root->left;
		}
		*p1 = r;
		*p2 = root->right;
		return;
	}
	else if (idx > root->weight) {
		split(root->right, idx - root->weight, p1, p2);
		*p1 = concat(root->left, *p1);
		return;
	}
	else {
		if (isLeaf(root)) {
			*p2 = (tree *)malloc(sizeof(tree));
			if (idx > 0) {
				*p1 = (tree *)malloc(sizeof(tree));
				(*p1)->length = idx;
				(*p1)->weight = idx;
				for (int i = 0; i < idx; i++) {
					(*p1)->item[i] = root->item[i];
				}
				(*p1)->left = NULL;
				(*p1)->right = NULL;
			}

			(*p2)->weight = root->length - idx;
			(*p2)->length = root->length - idx;
			int j = 0;
			for (int i = idx; i < (root->length); i++) {
				(*p2)->item[j] = root->item[i];
				j++;
			}
			(*p2)->left = NULL;
			(*p2)->right = NULL;
			return;
		}
		else {
			split(root->left, idx, p1, p2);
			*p2 = concat(*p2, root->right);
			return;
		}
	}

}

tree *insert(tree *root, int idx, char *str) {
	if (root == NULL) {
		return create(str);
	}

	tree *p1 = NULL;
	tree *p2 = NULL;
	split(root, idx, &p1, &p2);
	tree *temp = concat(p1, create(str));
	return concat(temp, p2);
}

tree *deleteTree(tree *root, int idx, int len) {
	tree *p1 = NULL;
	tree *p2 = NULL;
	tree *p3 = NULL;
	tree *p4 = NULL;
	split(root, idx-1, &p1, &p2);
	split(p2, len, &p3, &p4);
	return concat(p1, p4);
}
int start = 0;
void print(tree *root, int idx, int length, char *str) {
	if (root->weight >= (idx + length - 1)) {
		if (isLeaf(root)) {
			for (int i = idx-1; i < idx+length-1; i++) {
				str[start] = root->item[i];
				start++;
			}
		}
		else {
			print(root->left, idx, length, str);
		}
	}
	else {
		print(root->left, idx, root->weight - idx + 1, str);
		print(root->right, 1, length - root->weight + idx - 1, str);
	}
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

typedef struct move {
	char current;
	char prev;
	int cursor;
} move;

typedef struct Stack {
	int capacity;
	int size;
	int top;
	move elements[MAX_STR_SIZE + 1];
} Stack;

Stack *createStack(int capacity) {
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->capacity = capacity;
	s->size = 0;
	s->top = -1;
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

void Push(Stack *s, move e) {
	if (isStackFull(s)) {
		//full
	}
	else {
		s->top++;
		s->size++;
		s->elements[s->top] = e;
	}
}

move Pop(Stack *s) {
	if (isStackEmpty(s)) {
		return{ '\0', '\0', -1 };
	}
	else {
		move ret = s->elements[s->top];
		s->top--;
		s->size--;
		return ret;
	}
}

int shownum = 0;
Stack *undoStack = createStack(MAX_STR_SIZE + 1);
Stack *redoStack = createStack(MAX_STR_SIZE + 1);
tree *editor;

char str[MAX_STR_SIZE + 1];
int curPos;
int fromUndo;

void init(char* str){
	start = 0;
	fromUndo = 0;
	undoStack->top = -1;
	undoStack->size = 0;
	redoStack->top = -1;
	redoStack->size = 0;
	curPos = 0;
	editor = NULL;
	editor = insert(editor, curPos, str);
	curPos = getStrLen2(str);
}

void write(char ch){
	move x;
	if (ch != '\b') {
		editor = insert(editor, curPos, &ch);
		curPos++;
		x.cursor = curPos;
		x.current = index(editor, curPos);
		x.prev = '\0';
		if (fromUndo != 1) {
			Push(undoStack, x);
			redoStack->top = -1;
			redoStack->size = 0;
		}
		else
			fromUndo = 0;
	}
	else if(ch == '\b' && curPos > 0) {
		x.prev = index(editor, curPos);
		editor = deleteTree(editor, curPos, 1);
		x.current = '\b';
		curPos--;
		x.cursor = curPos;
		if (fromUndo != 1) {
			Push(undoStack, x);
			redoStack->top = -1;
			redoStack->size = 0;
		}
		else
			fromUndo = 0;
	}
	if (shownum == 2 && editor->length >= 280)
		printf("Length WRITE: %d\n", editor->length);
}

void moveCursor(int pos){
	curPos = pos;
}

void undo(){
	move x = Pop(undoStack);
	if (x.cursor == -1) return;
	Push(redoStack, x);
	curPos = x.cursor;
	fromUndo = 1;
	if (x.current == '\b') {
		write(x.prev);
	}
	else {
		write('\b');
	}
	if (shownum == 2 && editor->length >= 280)
		printf("Length UNDO: %d\n", editor->length);
}

void redo(){
	move x = Pop(redoStack);
	if (x.cursor == -1) return;
	Push(undoStack, x);
	curPos = x.cursor;
	fromUndo = 1;
	if (x.current == '\b') {
		curPos++;
		write('\b');
	}
	else {
		curPos--;
		write(x.current);
	}
	if (shownum == 2 && editor->length >= 280)
		printf("Length REDO: %d\n", editor->length);
}

char* show(){
	start = 0;
	shownum++;
	printf("Length SHOW: %d\n", editor->length);
	print(editor, 1, editor->length, str);
	return str;
}
