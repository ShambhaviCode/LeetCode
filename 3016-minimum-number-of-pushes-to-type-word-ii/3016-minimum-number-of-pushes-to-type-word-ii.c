#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int minimumPushes(char* word) {
    int freq[26] = {0};
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        freq[word[i] - 'a']++;
    }
    
    qsort(freq, 26, sizeof(int), cmp);
    
    int total = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] == 0) break;
        int presses = i / 8 + 1;
        total += presses * freq[i];
    }
    
    return total;
}