class Solution {
public:
    char processStr(string s, long long k) {
        int n = s.size();

        vector<long long> len(n + 1, 0);
        const long long LIM = 1e15 + 5;

        // Compute lengths
        for (int i = 0; i < n; i++) {
            char ch = s[i];

            if ('a' <= ch && ch <= 'z') {
                len[i + 1] = min(LIM, len[i] + 1);
            }
            else if (ch == '*') {
                len[i + 1] = max(0LL, len[i] - 1);
            }
            else if (ch == '#') {
                len[i + 1] = min(LIM, len[i] * 2);
            }
            else { // '%'
                len[i + 1] = len[i];
            }
        }

        if (k >= len[n]) return '.';

        // Backtrack
        for (int i = n - 1; i >= 0; i--) {
            char ch = s[i];

            if ('a' <= ch && ch <= 'z') {
                if (k == len[i]) return ch;
            }
            else if (ch == '*') {
                // k unchanged
            }
            else if (ch == '#') {
                k %= len[i];
            }
            else { // '%'
                k = len[i] - 1 - k;
            }
        }

        return '.';
    }
};