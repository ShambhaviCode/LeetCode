int minOperations(int* nums, int n) {
    if (n == 1) return 0;
    int s = nums[0], ok = 1;
    for (int i = 0; i < n; i++) if (nums[i] != (i + s) % n) { ok = 0; break; }
    if (ok) {
        if (s == 0) return 0;
        int a = (n - s) % n, b = s + 2;
        return a < b ? a : b;
    }
    s = nums[0]; ok = 1;
    for (int i = 0; i < n; i++) if (nums[i] != ((s - i) % n + n) % n) { ok = 0; break; }
    if (!ok) return -1;
    int A = 1 + ((n - s - 1) % n + n) % n;
    int B = ((s + 1) % n) + 1;
    return A < B ? A : B;
}

