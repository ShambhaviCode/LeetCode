void backtrack(char* path, int idx, int opens, int closes, int n,
               char** result, int* resultIdx) {
    if (idx == 2 * n) {
        // Complete string — copy into result
        char* combo = (char*)malloc(2 * n + 1);
        for (int i = 0; i < 2 * n; i++) combo[i] = path[i];
        combo[2 * n] = '\0';
        result[*resultIdx] = combo;
        (*resultIdx)++;
        return;
    }
    
    // Try adding '(' if we have opens left
    if (opens < n) {
        path[idx] = '(';
        backtrack(path, idx + 1, opens + 1, closes, n, result, resultIdx);
    }
    
    // Try adding ')' if it would still be valid
    if (closes < opens) {
        path[idx] = ')';
        backtrack(path, idx + 1, opens, closes + 1, n, result, resultIdx);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    // 1430 is Catalan(8), upper bound for n <= 8
    char** result = (char**)malloc(1430 * sizeof(char*));
    char* path = (char*)malloc(2 * n + 1);
    *returnSize = 0;
    
    backtrack(path, 0, 0, 0, n, result, returnSize);
    
    free(path);
    return result;
}