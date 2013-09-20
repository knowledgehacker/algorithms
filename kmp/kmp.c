#include "string.h"
#include "stdlib.h"
#include "stdio.h"

/*
 * Knuth-Morris-Pratt algorithm for searching "pattern" in string "text".
 * It based on the key observation that when dismatch occurs, you don't have to move back pointer that points to the current position in string "text".
 * You only have to move back pointer that points to the current position in "pattern".
 * For example, assume the pointers i and j are used when matching "pattern" with string "text", and dismatch occurs in pattern[j] and text[i], that is,
 * ... Ti-j ... Ti-1 Ti ...
 * 	  =         =   !=
 *    P0 ...   Pj-1 Pj ...		(1)
 *
 * And we assume that we move back pointer j to postion k(k < j), and use Pk to compare with Ti for the next round. 
 * If position k is the proper one, it should satisfy the following condition:
 * ... Ti-k ... Ti-1 Ti ...
 * 		=        =   !=
 * 	   P0       Pk-1 Pk ...	    (2)
 *
 * combine (1) and (2), we get the following result:
 *
 * ... Ti-j ... Ti-k ... Ti-1 Ti ...
 *     =        =         =   !=
 *     P0 ...   Pj-k ... Pj-1 Pj ...
 *     			=         =   =?
 *              P0 ...   Pk-1 Pk ...	(3)
 *
 * That is, P0...Pk-1 = Pj-k...Pj-1.    (4)
 *
 * So we get the follwing thoughts for the pattern matching based on the observation above, that is the implementation of kmp function below:
 * a) Let pointer i and j points to the first character in "pattern" and "text" respectively, that is, i = 0, j = 0;
 * Compare text[i] and text[j] one by one, if dismatch occurs, i stays unchanged, and move back j to k(k is calculated by (4)), then begins the next round
 * pattern matching(You should pay attention to a special case tha when dismatch occurs j = 0, in such a case, you should move forward pointer i, and move
 * back pointer j to positon 0, that is, ++i, j = 0). if match, just move pointer i and j to the next position.
 * b) if a match of the whole "pattern" is found in "text", set pointer j to 0, and begin the possible pattern match in "text".
 * 
 * The kmp algorithm described above calculates the postion k based on (4) during pattern matching. Actually we can calculate the position k that pointer j 
 * should move back to in advance, that is, next[j] = k. Then when dismatch occurs in pointer j, we know we need to move back to position k = next[j]. 
 * This is based on another key observation that for position k that pointer j should move back to when dismatch occurs only depends on "pattern", it is
 * irrelevant to "text". nextCalc below is calculated based on this observation and (4), remember that we set next[0] to -1 to indicate the special case.
 */

void nextCalc(char* pat, int patLen, int* next){
	next[0] = -1;
	next[1] = 0;

	int i;
	for(i = 2; i < patLen; ++i){
		int k;
		for(k = 1; k < i; ++k){
			if(0 == strncmp(&pat[0], &pat[i-k], k)){
				next[i] = k;
				break;
			}
		}
	}
}

void kmp(char* text, char* pat){
	int patLen = strlen(pat);
	int* next = (int*)malloc(patLen);
	if(0 == next){
		fprintf(stderr, "allocate for next array failed.\n");
		return;
	}

	nextCalc(pat, patLen, next);
#ifdef DEBUG
	int k;
	for(k = 0; k < patLen-1; ++k)
		printf("%d: %d, ", k, next[k]);
	printf("%d: %d.\n", patLen-1, next[patLen-1]);
#endif

	int textLen = strlen(text);
	int i = 0, j = 0;
	while(i < textLen){
		if(text[i] != pat[j]){
			if(next[j] == -1){
				++i;
				j = 0;
			}else
				j = next[j];

			continue;
		}

		++i;
		++j;

		if(j == patLen){
			printf("text[%d, %d) matches pattern %s.\n", i-patLen, i, pat);

			j = 0;
		}
	}		
}

int main(){
	char* text = "DBCCABACABABACDECCABABACDDEBA";
	char* pat = "ABABAC";

	kmp(text, pat);

	return 0;
}

