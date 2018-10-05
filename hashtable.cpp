// Coding_Exer_HashMap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>
#define MAX 50

typedef struct keypair {
	unsigned char *key;
	int value;
	int dib;
	unsigned long hash;
} keypair;

typedef struct hashmap {
	int table_size;
	int size;
	keypair *data[MAX];
} hashmap;

int strlen(unsigned char *s) {
	unsigned char *p = s;
	for (; *p != '\0'; p++) {}
	return p - s;
}

int strCmp(unsigned char *s1, unsigned char *s2) {
	while (*s1 == *s2) {
		if (*s1 == '\0') return(0);
		s1++;
		s2++;
	}
	return *(unsigned char*)s1 - *(unsigned char*)s2;
}

unsigned long hash_function(unsigned char *str) {
	unsigned long hash = 5381;
	int c;

	while (c = *str++) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

unsigned long hash_key(hashmap *h, unsigned char *str) {
	unsigned long key = hash_function(str);
	return key%h->table_size;
}

hashmap *hashmap_new(int size) {
	hashmap *h;
	h = (hashmap*)malloc(sizeof(hashmap));

	for (int i = 0; i < MAX; i++) {
		h->data[i] = NULL;
	}

	h->table_size = size;
	h->size = 0;
	return h;
}

int hashmap_add(hashmap *h, unsigned char *key, int val) {
	if (h->table_size == h->size) {
		return -1; //full
	}
	if (!h || !key) {
		return -1;
	}
	unsigned long hash = hash_function(key);
	unsigned long index_init = hash % h->table_size;
	int dib_current = 0;
	unsigned long index_current = index_init;
	int i = 0;
	for (i = 0; i < h->table_size; i++) {
		index_current = (index_init + i) % h->table_size;
		if (h->data[index_current] == NULL) {
			h->data[index_current] = (keypair*)malloc(sizeof(keypair));
			h->data[index_current]->key = key;
			h->data[index_current]->value = val;
			h->data[index_current]->dib = dib_current;
			h->data[index_current]->hash = hash;
			h->size++;
			break;
		}
		else if (h->data[index_current]->hash == hash && !strCmp(key, h->data[index_current]->key)) {
			h->data[index_current]->value = val;
			break;
		}
		else {
			if (h->data[index_current]->dib < dib_current) {
				int loc_val = h->data[index_current]->value;
				unsigned char *loc_key = h->data[index_current]->key;
				unsigned long loc_hash = h->data[index_current]->hash;
				unsigned long loc_dib = h->data[index_current]->dib;

				h->data[index_current]->key = key;
				h->data[index_current]->value = val;
				h->data[index_current]->hash = hash;
				h->data[index_current]->dib = dib_current;

				dib_current = loc_dib;
				key = loc_key;
				val = loc_val;
				hash = loc_hash;
			}
		}
		dib_current++;
	}

	return 0;
}

int hashmap_get_int(hashmap *h, unsigned char *key) {
	unsigned long hash = hash_function(key);
	unsigned long index_init = hash % h->table_size;
	int found = -1;
	int i = 0;
	for (i = 0; i < h->table_size; i++) {
		unsigned long index_current = (index_init + i) % h->table_size;
		if (h->data[index_current] == NULL) {
			break;
		}
		if (i > h->data[index_current]->dib) {
			break;
		}
		if (h->data[index_current]->hash == hash && !strCmp(key, h->data[index_current]->key)) {
			found = index_current;
			break;
		}
	}
	
	return found;
}

int hashmap_del(hashmap *h, unsigned char *key) {
	int index_current = hashmap_get_int(h, key);
	if (index_current < 0) {
		return -1;
	}

	free(h->data[index_current]);
	h->data[index_current] = NULL;

	int index_previous = 0, index_swap = 0;
	int i = 1;
	for (i = 1; i < h->table_size; i++) {
		index_previous = (index_current + i - 1) % h->table_size;
		index_swap = (index_current + i) % h->table_size;
		if (h->data[index_swap] == NULL) {
			free(h->data[index_previous]);
			h->data[index_previous] = NULL;
			break;
		}

		if (h->data[index_swap]->dib == 0) {
			free(h->data[index_previous]);
			h->data[index_previous] = NULL;
			break;
		}

		h->data[index_previous]->key = h->data[index_swap]->key;
		h->data[index_previous]->value = h->data[index_swap]->value;
		h->data[index_previous]->hash = h->data[index_swap]->hash;
		h->data[index_previous]->dib = h->data[index_swap]->dib;
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned char one[4] = { 'o', 'n', 'e', '\0' };
	unsigned char twentytwo[] = { 't', 'w', 'e', 'n', 't', 'y', '-', 't', 'w', 'o', '\0' };
	unsigned char thirteen[] = { 't', 'h', 'i', 'r', 't', 'e', 'e', 'n', '\0' };
	hashmap *a = hashmap_new(50);
	hashmap_add(a, &(one[0]), 1);
	hashmap_add(a, &twentytwo[0], 22);
	hashmap_add(a, &thirteen[0], 13);
	int ans = hashmap_get_int(a, twentytwo);
	hashmap_del(a, one);
	ans = hashmap_get_int(a, one);
	ans = hashmap_get_int(a, twentytwo);
	return 0;
}



