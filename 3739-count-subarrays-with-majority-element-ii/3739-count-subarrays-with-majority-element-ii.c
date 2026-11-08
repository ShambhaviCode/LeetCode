#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a) - (*(int *)b);
}

int lowerBound(int *arr, int n, int x) {
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (arr[m] < x)
            l = m + 1;
        else
            r = m;
    }
    return l;
}

void update(int *bit, int n, int idx) {
    while (idx <= n) {
        bit[idx]++;
        idx += idx & (-idx);
    }
}

long long query(int *bit, int idx) {
    long long sum = 0;
    while (idx > 0) {
        sum += bit[idx];
        idx -= idx & (-idx);
    }
    return sum;
}

long long countMajoritySubarrays(int* nums, int numsSize, int target) {
    int n = numsSize;

    int *pref = (int *)malloc((n + 1) * sizeof(int));
    int *vals = (int *)malloc((n + 1) * sizeof(int));

    pref[0] = 0;
    vals[0] = 0;

    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + (nums[i - 1] == target ? 1 : -1);
        vals[i] = pref[i];
    }

    qsort(vals, n + 1, sizeof(int), cmp);

    int m = 0;
    for (int i = 0; i <= n; i++) {
        if (i == 0 || vals[i] != vals[i - 1])
            vals[m++] = vals[i];
    }

    int *bit = (int *)calloc(m + 2, sizeof(int));

    long long ans = 0;

    for (int i = 0; i <= n; i++) {
        int idx = lowerBound(vals, m, pref[i]) + 1;
        ans += query(bit, idx - 1);   // count previous prefix sums < current
        update(bit, m, idx);
    }

    free(pref);
    free(vals);
    free(bit);

    return ans;
}