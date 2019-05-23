// SimpleSearch.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

int strlen(char * s) {
	char *p = s;
	for (; *p != '\0'; p++) {}
	return p - s;
}

int X = 101;


int search(char s[], char p[]) {
	long long curHash, tarHash, xPow;
	curHash = 0;
	tarHash = 0;
	xPow = 1;
	int M = strlen(p);
	int N = strlen(s);
	for (int i = 0; i < M; i++) {
		tarHash = tarHash*X + (p[i] - 'A');
		curHash = curHash*X + (s[i] - 'A');
	}
	for (int i = 0; i < (M - 1); i++) {
		xPow = xPow*X;
	}
	int found = -1;
	for (int i = 0; i <= (N - M); i++) {
		found = i;
		if (curHash == tarHash) {
			for (int j = 0; j < M; j++) {
				if (s[i + j] != p[j]) {
					found = -1;
					break;
				}
			}
			if (found >= 0) {
				break;
			}
		}
		else {
			found = -1;
		}
		if (i < (N - M)) {
			curHash = (curHash - (s[i] - 'A')*xPow)*X + (s[i + M] - 'A');
		}
	}

	return found;
}

int main(int argc, char* argv[])
{
	int T;
	//freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	for (int i = 1; i <= T; i++) {
		printf("Case #%d:", i);
		char s[100005];
		char p[50005];
		scanf("%s %s", s, p);
		printf(" %d", search(s, p));
		printf("\n");
	}
	return 0;
}

