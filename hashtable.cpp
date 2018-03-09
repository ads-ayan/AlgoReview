// HashTable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>

typedef struct keypair {
	unsigned char *key;
	int value;
	int in_use;
	int dib;
	unsigned long hash;
} keypair;

typedef struct hashmap {
	int table_size;
	int size;
	keypair *data[1000];
} hashmap;

int strlen(unsigned char * s) {
	unsigned char *p = s;
	for (; *p != '\0'; p++) {}
	return p - s;
}

int strCmp(unsigned char* s1, unsigned char* s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0') return(0);
		s1++;
		s2++;
	}
	return *(unsigned char*)s1 - *(unsigned char*)s2;
}

unsigned long hash(unsigned char *str, int len) {
	unsigned long hash = 5381;
	int c;

	while (c = *str++) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

unsigned long hash_key(hashmap *h, unsigned char *str, int len) {
	unsigned long key = hash(str, len);
	return key % h->table_size;
}

hashmap *hashmap_new(int size) {
	hashmap *h;
	h = (hashmap*)malloc(sizeof(hashmap));

	for (int i = 0; i < 1000; i++) {
		h->data[i] = NULL;
	}

	h->table_size = size;
	h->size = 0;
	return h;
}

/*

int hashmap_resize(hashmap *h) {
	int new_size = h->table_size;
	int factor = 2;

	while (new_size <= (factor * h->size)) {
		new_size *= 2;
	}
	if (new_size == h->table_size) {
		return 0;
	}

	hashmap *nd = hashmap_new(new_size);
}

*/

int hashmap_add(hashmap *h, unsigned char *key, int val) {
	if (!h || !key) {
		return -1;
	}

	unsigned long hash = hash_key(h, key, strlen(key));
	unsigned long hashvalue = hash;
	int dib = 0;
	while (1) {
		if (h->data[hash] == NULL || h->data[hash]->in_use != 1) {
			if (h->data[hash] == NULL) {
				h->data[hash] = (keypair*)malloc(sizeof(keypair));
			}
			h->data[hash]->key = key;
			h->data[hash]->value = val;
			h->data[hash]->in_use = 1;
			h->data[hash]->dib = dib;
			h->data[hash]->hash = hashvalue;
			h->size++;
			break;
		}
		if (h->data[hash]->dib < dib) {
			int loc_val = h->data[hash]->value;
			unsigned char *loc_key = h->data[hash]->key;

			h->data[hash]->key = key;
			h->data[hash]->value = val;
			h->data[hash]->dib = dib;
			h->data[hash]->hash = hashvalue;
			h->data[hash]->in_use = 1;
			hashmap_add(h, loc_key, loc_val);
			free(loc_key);
			break;
		}
		dib++;
		hash = hash + 1;
	}

	if (3 * h->size > 2 * h->table_size) {
		//resize
	}

	return 0;
}
int hashmap_get_int(hashmap *h, unsigned char *key) {
	unsigned long hash = hash_key(h, key, strlen(key));
	int found = -1;
	while (1) {
		if (h->data[hash]->key == NULL || h->data[hash]->in_use != 1) {
			break;
		}
		if (h->data[hash]->hash == hash && !strCmp(key, h->data[hash]->key)) {
			found = hash;
			break;
		}

		hash = hash + 1;

	}

	return found;
}

int hashmap_get(hashmap *h, unsigned char *key) {
	unsigned long hash = hash_key(h, key, strlen(key));
	unsigned long hashvalue = hash;
	int found = -1;
	while (1) {
		if (h->data[hash] == NULL || h->data[hash]->in_use != 1) {
			break;
		}
		if (h->data[hash]->hash == hashvalue && !strCmp(key, h->data[hash]->key)) {
			found = hash;
			break;
		}

		hash = hash + 1;

	}
	if (found != -1) {
		return h->data[hash]->value;
	}
	else {
		return found;
	}
	
}

int hashmap_del(hashmap *h, unsigned char *key) {
	int pos = hashmap_get_int(h, key);

	if (pos < 0) {
		return 0;
	}

	if (h->data[pos]->in_use) {
		if (strCmp(h->data[pos]->key, key) == 0) {
			h->data[pos]->in_use = 0;
			h->data[pos]->value = 0;
			h->data[pos]->key = NULL;

			h->size--;
		}
	}

	int npos;

	while (1) {
		npos = pos + 1;
		if (h->data[npos] == NULL || h->data[npos]->in_use != 1) {
			break;
		}

		if (h->data[npos]->dib == 0) {
			break;
		}

		h->data[pos]->key = h->data[npos]->key;
		h->data[pos]->value = h->data[npos]->value;
		h->data[pos]->hash = h->data[npos]->hash;
		h->data[pos]->dib = h->data[npos]->dib - 1;
		h->data[pos]->in_use = 1;

		h->data[npos]->key = NULL;
		h->data[npos]->value = 0;
		h->data[npos]->in_use = 0;

		pos = npos;
	}

	return -1;
}


int _tmain(int argc, _TCHAR* argv[])
{
	unsigned char one[4] = { 'o', 'n', 'e', '\0' };
	unsigned char twentytwo[] = { 't', 'w', 'e', 'n', 't', 'y', '-', 't', 'w', 'o','\0' };
	unsigned char thirteen[] = { 't', 'h', 'i', 'r', 't', 'e', 'e', 'n', '\0' };
	hashmap *a = hashmap_new(10);
	hashmap_add(a, &(one[0]), 1);
	hashmap_add(a, &twentytwo[0], 22);
	hashmap_add(a, &thirteen[0], 13);
	hashmap_get(a, twentytwo);
	hashmap_del(a, one);
	hashmap_get(a, one);
	hashmap_get(a, twentytwo);
	return 0;
}

