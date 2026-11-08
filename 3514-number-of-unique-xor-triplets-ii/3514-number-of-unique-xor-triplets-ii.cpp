class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048; // nums[i] <= 1500 < 2^11

        vector<vector<char>> dp(4, vector<char>(MAXX, 0));
        dp[0][0] = 1;

        for (int v : nums) {
            auto ndp = dp; // option: use this index 0 times

            for (int cnt = 0; cnt <= 3; cnt++) {
                for (int x = 0; x < MAXX; x++) {
                    if (!dp[cnt][x]) continue;

                    // Use current index once
                    if (cnt + 1 <= 3)
                        ndp[cnt + 1][x ^ v] = 1;

                    // Use current index twice (v ^ v = 0)
                    if (cnt + 2 <= 3)
                        ndp[cnt + 2][x] = 1;

                    // Use current index three times (v ^ v ^ v = v)
                    if (cnt + 3 <= 3)
                        ndp[cnt + 3][x ^ v] = 1;
                }
            }

            dp.swap(ndp);
        }

        int ans = 0;
        for (int x = 0; x < MAXX; x++)
            if (dp[3][x]) ans++;

        return ans;
    }
};