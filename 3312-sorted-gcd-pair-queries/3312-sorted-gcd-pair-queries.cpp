class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<long long> freq(mx + 1, 0);
        for (int x : nums) freq[x]++;

        // cntDiv[d] = how many numbers are divisible by d
        vector<long long> cntDiv(mx + 1, 0);
        for (int d = 1; d <= mx; d++) {
            for (int m = d; m <= mx; m += d)
                cntDiv[d] += freq[m];
        }

        // exact[d] = number of pairs with gcd exactly d
        vector<long long> exact(mx + 1, 0);
        for (int d = mx; d >= 1; d--) {
            long long pairs = cntDiv[d] * (cntDiv[d] - 1) / 2;
            for (int m = d + d; m <= mx; m += d)
                pairs -= exact[m];
            exact[d] = pairs;
        }

        // Prefix counts over gcd values
        vector<long long> pref(mx + 1, 0);
        for (int d = 1; d <= mx; d++)
            pref[d] = pref[d - 1] + exact[d];

        vector<int> ans;
        ans.reserve(queries.size());

        for (long long q : queries) {
            // first gcd value whose prefix count >= q+1
            int g = lower_bound(pref.begin() + 1, pref.end(), q + 1) - pref.begin();
            ans.push_back(g);
        }

        return ans;
    }
};