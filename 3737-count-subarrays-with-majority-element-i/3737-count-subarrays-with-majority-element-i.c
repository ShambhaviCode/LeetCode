int countMajoritySubarrays(int* nums, int numsSize, int target) {
    int ans = 0;

    for (int i = 0; i < numsSize; i++) {
        int count = 0;

        for (int j = i; j < numsSize; j++) {
            if (nums[j] == target)
                count++;

            int len = j - i + 1;

            if (count > len / 2)
                ans++;
        }
    }

    return ans;
}