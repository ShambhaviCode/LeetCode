
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        deque<pair<int, int>> dq;

        long long cost = 0;
        long long ans = 0;

        int j = n - 1;

        for (int i = n - 1; i >= 0; i--) {

            int num = nums[i];
            int cnt = 1;

            // Merge smaller groups into the current group
            while (!dq.empty() && dq.back().first < num) {

                int val = dq.back().first;
                int count = dq.back().second;

                dq.pop_back();

                cnt += count;

                cost += 1LL * (num - val) * count;
            }

            dq.push_back({num, cnt});

            // Shrink window while cost exceeds k
            while (cost > k) {

                int val = dq.front().first;
                int count = dq.front().second;

                dq.pop_front();

                cost -= val - nums[j];
                j--;

                if (count > 1) {
                    dq.push_front({val, count - 1});
                }
            }

            // Count all valid subarrays ending at j
            ans += j - i + 1;
        }

        return ans;
    }
};