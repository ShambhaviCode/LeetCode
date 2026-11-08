class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> lastIndex(26);
        vector<bool> visited(26, false);

        // Store last occurrence of every character
        for (int i = 0; i < s.size(); i++) {
            lastIndex[s[i] - 'a'] = i;
        }

        string st;

        for (int i = 0; i < s.size(); i++) {
            char c = s[i];

            if (visited[c - 'a'])
                continue;

            while (!st.empty() &&
                   st.back() > c &&
                   lastIndex[st.back() - 'a'] > i) {
                visited[st.back() - 'a'] = false;
                st.pop_back();
            }

            st.push_back(c);
            visited[c - 'a'] = true;
        }

        return st;
    }
};