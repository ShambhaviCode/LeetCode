 import java.util.*;

class Solution {
    public int[] pathExistenceQueries(int n, int[] nums, int maxDiff, int[][] queries) {

        int[][] arr = new int[n][2];
        for (int i = 0; i < n; i++) {
            arr[i][0] = nums[i];
            arr[i][1] = i;
        }

        Arrays.sort(arr, Comparator.comparingInt(a -> a[0]));

        int[] value = new int[n];
        int[] pos = new int[n];      // original index -> position in sorted order
        int[] comp = new int[n];

        for (int i = 0; i < n; i++) {
            value[i] = arr[i][0];
            pos[arr[i][1]] = i;
        }

        // Connected components in sorted order
        int cid = 0;
        comp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (value[i] - value[i - 1] > maxDiff) cid++;
            comp[i] = cid;
        }

        // Furthest index reachable in one edge
        int[] next = new int[n];
        int r = 0;
        for (int i = 0; i < n; i++) {
            while (r + 1 < n && value[r + 1] - value[i] <= maxDiff) {
                r++;
            }
            next[i] = r;
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        int[][] up = new int[LOG][n];
        up[0] = next;

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        int[] ans = new int[queries.length];

        for (int qi = 0; qi < queries.length; qi++) {
            int u = pos[queries[qi][0]];
            int v = pos[queries[qi][1]];

            if (u == v) {
                ans[qi] = 0;
                continue;
            }

            if (u > v) {
                int t = u;
                u = v;
                v = t;
            }

            if (comp[u] != comp[v]) {
                ans[qi] = -1;
                continue;
            }

            int cur = u;
            int steps = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < v) {
                    cur = up[k][cur];
                    steps += 1 << k;
                }
            }

            ans[qi] = steps + 1;
        }

        return ans;
    }
}