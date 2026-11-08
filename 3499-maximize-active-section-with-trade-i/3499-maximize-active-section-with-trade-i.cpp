class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int initialOnes = 0;
        for (char c : s) {
            if (c == '1') initialOnes++;
        }

        string t = "1" + s + "1";

        // Run-length encoding of augmented string.
        vector<pair<char, int>> runs;
        int i = 0, m = t.size();
        while (i < m) {
            int j = i;
            while (j < m && t[j] == t[i]) j++;
            runs.push_back({t[i], j - i});
            i = j;
        }

        int ans = initialOnes;

        // For every interior 1-run (surrounded by 0-runs),
        // gain = left zero-run length + right zero-run length.
        for (int k = 1; k + 1 < (int)runs.size(); k++) {
            if (runs[k].first == '1' &&
                runs[k - 1].first == '0' &&
                runs[k + 1].first == '0') {
                ans = max(ans,
                          initialOnes + runs[k - 1].second + runs[k + 1].second);
            }
        }

        return ans;
    }
};