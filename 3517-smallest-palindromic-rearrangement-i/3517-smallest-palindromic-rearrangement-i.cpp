class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        string half = "";
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) mid = char('a' + i);
            half.append(freq[i] / 2, char('a' + i));
        }

        string ans = half;
        if (mid) ans.push_back(mid);

        reverse(half.begin(), half.end());
        ans += half;

        return ans;
    }
};