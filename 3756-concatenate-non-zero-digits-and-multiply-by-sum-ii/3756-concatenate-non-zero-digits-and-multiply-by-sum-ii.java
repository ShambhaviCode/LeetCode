class Solution {
    static final int MOD = 1_000_000_007;

    public int[] sumAndMultiply(String s, int[][] queries) {
        int n = s.length();

        int[] cnt = new int[n + 1];
        long[] prefSum = new long[n + 1];

        int nz = 0;
        for (int i = 0; i < n; i++) {
            int d = s.charAt(i) - '0';
            cnt[i + 1] = cnt[i] + (d != 0 ? 1 : 0);
            prefSum[i + 1] = prefSum[i] + d;
            if (d != 0) nz++;
        }

        long[] pow10 = new long[nz + 1];
        pow10[0] = 1;
        for (int i = 1; i <= nz; i++) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }

        long[] hash = new long[nz + 1];
        int idx = 0;
        for (int i = 0; i < n; i++) {
            int d = s.charAt(i) - '0';
            if (d != 0) {
                hash[idx + 1] = (hash[idx] * 10 + d) % MOD;
                idx++;
            }
        }

        int[] ans = new int[queries.length];

        for (int i = 0; i < queries.length; i++) {
            int l = queries[i][0];
            int r = queries[i][1];

            long sum = prefSum[r + 1] - prefSum[l];

            int left = cnt[l];
            int right = cnt[r + 1];

            long x;
            if (left == right) {
                x = 0;
            } else {
                int len = right - left;
                x = (hash[right] - hash[left] * pow10[len]) % MOD;
                if (x < 0) x += MOD;
            }

            ans[i] = (int) ((x * (sum % MOD)) % MOD);
        }

        return ans;
    }
}