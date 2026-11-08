bool isValid(char* s) {
    int n = strlen(s);
    
    // Odd length can never be balanced
    if (n % 2 != 0) return false;
    
    // Stack worst case: all openers, so n slots needed
    char* stack = (char*)malloc(n * sizeof(char));
    int top = -1;
    
    for (int i = 0; i < n; i++) {
        char c = s[i];
        
        if (c == '(' || c == '[' || c == '{') {
            stack[++top] = c;
        } else {
            if (top == -1) {
                free(stack);
                return false;
            }
            
            char open = stack[top];
            if ((c == ')' && open != '(') ||
                (c == ']' && open != '[') ||
                (c == '}' && open != '{')) {
                free(stack);
                return false;
            }
            top--;
        }
    }
    
    bool valid = (top == -1);
    free(stack);
    return valid;
}