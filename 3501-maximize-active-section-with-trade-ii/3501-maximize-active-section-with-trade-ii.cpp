class Solution {
public:
    struct Group {
        int start;
        int len;
    };

    class SparseTable {
    public:
        vector<vector<int>> st;
        vector<int> lg;

        SparseTable() {}

        SparseTable(const vector<int>& a) {
            int n = a.size();
            if (n == 0) return;

            lg.resize(n + 1);
            for (int i = 2; i <= n; i++)
                lg[i] = lg[i / 2] + 1;

            st.assign(lg[n] + 1, vector<int>(n));
            st[0] = a;

            for (int k = 1; k <= lg[n]; k++) {
                for (int i = 0; i + (1 << k) <= n; i++) {
                    st[k][i] = max(st[k - 1][i],
                                   st[k - 1][i + (1 << (k - 1))]);
                }
            }
        }

        int query(int l, int r) {
            if (l > r) return 0;
            int k = lg[r - l + 1];
            return max(st[k][l], st[k][r - (1 << k) + 1]);
        }
    };

    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();
        int ones = 0;
        for (char c : s)
            if (c == '1') ones++;

        vector<Group> zeroGroups;
        vector<int> zeroIdx(n);

        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                if (i && s[i - 1] == '0')
                    zeroGroups.back().len++;
                else
                    zeroGroups.push_back({i, 1});
            }
            zeroIdx[i] = (int)zeroGroups.size() - 1;
        }

        if (zeroGroups.empty())
            return vector<int>(queries.size(), ones);

        vector<int> merge;
        for (int i = 0; i + 1 < (int)zeroGroups.size(); i++)
            merge.push_back(zeroGroups[i].len + zeroGroups[i + 1].len);

        SparseTable st(merge);

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            int left =
                zeroIdx[l] == -1
                    ? -1
                    : zeroGroups[zeroIdx[l]].len -
                          (l - zeroGroups[zeroIdx[l]].start);

            int right =
                zeroIdx[r] == -1
                    ? -1
                    : (r - zeroGroups[zeroIdx[r]].start + 1);

            int startAdj = zeroIdx[l] + 1;
            int endGroup = (s[r] == '1') ? zeroIdx[r] : zeroIdx[r] - 1;

            int best = ones;

            if (s[l] == '0' && s[r] == '0' &&
                zeroIdx[l] + 1 == zeroIdx[r]) {
                best = max(best, ones + left + right);
            } else if (startAdj <= endGroup - 1) {
                best = max(best,
                           ones + st.query(startAdj, endGroup - 1));
            }

            if (s[l] == '0' &&
                zeroIdx[l] + 1 <= endGroup) {
                best = max(best,
                           ones + left +
                               zeroGroups[zeroIdx[l] + 1].len);
            }

            if (s[r] == '0' &&
                zeroIdx[l] < zeroIdx[r] - 1) {
                best = max(best,
                           ones + right +
                               zeroGroups[zeroIdx[r] - 1].len);
            }

            ans.push_back(best);
        }

        return ans;
    }
};