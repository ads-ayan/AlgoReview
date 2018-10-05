// Trie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>

#define ALPHA_SIZE 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define INDEX_TO_CHAR(i) (char)((int)'a' + i)

int strlen(char * s) {
	char *p = s;
	for (; *p != '\0'; p++) {}
	return p - s;
}

typedef struct trieNode{
	trieNode *children[ALPHA_SIZE];

	int isEndofWord;
	int nchild;
	int ndescendants;
	int val;
} trieNode;

trieNode *getNode(int val) {
	trieNode *p = NULL;

	p = (trieNode*)malloc(sizeof(trieNode));

	if (p) {
		int i;
		p->isEndofWord = 0;
		p->nchild = 0;
		p->ndescendants = 0;
		p->val = val;
		for (i = 0; i < ALPHA_SIZE; i++) {
			p->children[i] = NULL;
		}
	}

	return p;
}

void insert(trieNode *root, char *key, int val) {
	int index;

	trieNode *pcrawl = root;

	while (*key != '\0') {
		index = CHAR_TO_INDEX(*key);
		if (!pcrawl->children[index]) {
			pcrawl->children[index] = getNode(val);
			pcrawl->nchild++;
		}
		pcrawl->children[index]->ndescendants++;
		pcrawl = pcrawl->children[index];
		key++;
	}

	pcrawl->isEndofWord = 1;
}

int search(trieNode *root, char *key) {
	int index;
	trieNode *pcrawl = root;

	while (*key != '\0') {
		index = CHAR_TO_INDEX(*key);
		if (!pcrawl->children[index]) return false;

		pcrawl = pcrawl->children[index];
		key++;
	}

	return (pcrawl != NULL && pcrawl->isEndofWord);
}

int isFree(trieNode *p) {
	/*
	int i;
	for (i = 0; i < ALPHA_SIZE; i++) {
	if (p->children[i]) return 0;
	}

	return 1;
	*/
	if (p->nchild > 0) return 0;
	return 1;
}

void kth_word(trieNode *root, int k, char *str, int a) {
	trieNode *pcrawl = root;
	int i;
	int ab = 0;
	int ac = 0;
	if (pcrawl->isEndofWord && k == 1) {
		str[a] ='\0';
		a++;
		return;
	}
	if (pcrawl->isEndofWord) {
		ac = 1;
	}
	for (i = 0; i < ALPHA_SIZE; i++) {
		if (root->children[i]) {
			ac = root->children[i]->ndescendants + ac;
			pcrawl = root->children[i];
			ab = i;
			if (k <= ac) break;
		}
	}
	str[a] = INDEX_TO_CHAR(ab);
	a++;
	kth_word(pcrawl, k - (ac - root->children[ab]->ndescendants), str, a);
}

int del(trieNode *root, char *key, int level, int len) {
	if (root) {
		if (level == len) {
			if (root->isEndofWord) {
				root->isEndofWord = 0;

				if (isFree(root)) {
					return 1;
				}

				return 0;
			}
		}
		else {
			int index = CHAR_TO_INDEX(key[level]);

			if (del(root->children[index], key, level + 1, len)) {
				if ((root->children[index]->isEndofWord == 0) && isFree(root->children[index])) {
					free(root->children[index]);
					root->children[index] = NULL;
					root->nchild--;
				}
				root->ndescendants--;
				return 1;
			}
		}
	}

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	trieNode *start = getNode(-1);
	insert(start, "ads", 1);
	insert(start, "adrian", 2);
	insert(start, "in", 3);
	insert(start, "insert", 4);
	insert(start, "inn", 5);
	printf("%s %s\n", "ads", search(start, "ads") ? "Present in trie" : "Not present in trie");
	printf("%s %s\n", "add", search(start, "add") ? "Present in trie" : "Not present in trie");
	del(start, "ads", 0, strlen("ads"));
	printf("%s %s\n", "ads", search(start, "ads") ? "Present in trie" : "Not present in trie");
	char str[50];
	kth_word(start, 2, &str[0], 0);
	return 0;
}

