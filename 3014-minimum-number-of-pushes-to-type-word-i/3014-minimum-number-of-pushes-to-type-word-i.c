int minimumPushes(char* word) {
    int ans = 0;
    int i = 0;

    while (word[i] != '\0') {
        ans += (i / 8) + 1;
        i++;
    }

    return ans;
}