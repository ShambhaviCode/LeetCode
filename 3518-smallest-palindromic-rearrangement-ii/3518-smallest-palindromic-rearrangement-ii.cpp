class Solution {
public:
    static const int CAP = 1000001;

    long long combCap(int n, int r) {
        r = min(r, n - r);
        __int128 res = 1;
        for (int i = 1; i <= r; i++) {
            res = (res * (n - r + i)) / i;
            if (res >= CAP) return CAP;
        }
        return (long long)res;
    }

    long long countWays(vector<int> &cnt) {
        __int128 ways = 1;
        int used = 0;

        for (int c : cnt) {
            if (c == 0) continue;
            ways *= combCap(used + c, c);
            if (ways >= CAP) return CAP;
            used += c;
        }
        return (long long)ways;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        vector<int> half(26, 0);
        char mid = 0;
        int halfLen = 0;

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            halfLen += half[i];
            if (freq[i] % 2) mid = char('a' + i);
        }

        if (countWays(half) < k) return "";

        string left;

        for (int pos = 0; pos < halfLen; pos++) {
            for (int ch = 0; ch < 26; ch++) {
                if (half[ch] == 0) continue;

                half[ch]--;
                long long ways = countWays(half);

                if (ways >= k) {
                    left.push_back(char('a' + ch));
                    break;
                } else {
                    k -= ways;
                    half[ch]++;
                }
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (mid) return left + string(1, mid) + right;
        return left + right;
    }
};