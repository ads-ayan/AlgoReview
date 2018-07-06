// Trie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>

#define ALPHA_SIZE 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

int strlen(char * s) {
	char *p = s;
	for (; *p != '\0'; p++) {}
	return p - s;
}

typedef struct trieNode{
	trieNode *children[ALPHA_SIZE];

	int isEndofWord;
} trieNode;

trieNode *getNode() {
	trieNode *p = NULL;

	p = (trieNode*)malloc(sizeof(trieNode));

	if (p) {
		int i;
		p->isEndofWord = 0;
		for (i = 0; i < ALPHA_SIZE; i++) {
			p->children[i] = NULL;
		}
	}

	return p;
}

void insert(trieNode *root, char *key) {
	int level;
	int length = strlen(key);
	int index;

	trieNode *pcrawl = root;

	for (level = 0; level < length; level++) {
		index = CHAR_TO_INDEX(key[level]);
		if (!pcrawl->children[index]) {
			pcrawl->children[index] = getNode();
		}
		pcrawl = pcrawl->children[index];
	}

	pcrawl->isEndofWord = 1;
}

int search(trieNode *root, char *key) {
	int level;
	int length = strlen(key);
	int index;
	trieNode *pcrawl = root;

	for (level = 0; level < length; level++) {
		index = CHAR_TO_INDEX(key[level]);
		if (!pcrawl->children[index]) return false;

		pcrawl = pcrawl->children[index];
	}

	return (pcrawl != NULL && pcrawl->isEndofWord);
}

int isFree(trieNode *p) {
	int i;
	for (i = 0; i < ALPHA_SIZE; i++) {
		if (p->children[i]) return 0;
	}

	return 1;
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
				free(root->children[index]);
				root->children[index] = NULL;
				return((root->isEndofWord == 0) && isFree(root));
			}
		}
	}

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	trieNode *start = getNode();
	insert(start, "ads");
	insert(start, "adrian");
	printf("%s %s\n", "ads", search(start, "ads") ? "Present in trie" : "Not present in trie");
	printf("%s %s\n", "add", search(start, "add") ? "Present in trie" : "Not present in trie");
	del(start, "ads", 0, strlen("ads"));
	printf("%s %s\n", "ads", search(start, "ads") ? "Present in trie" : "Not present in trie");
	return 0;
}

