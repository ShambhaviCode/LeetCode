/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : next(next), val(x) {}
 * };
 */
class Solution {
public:
    int pairSum(ListNode* head) {
        // Find the middle of the list
        ListNode *slow = head, *fast = head;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Reverse the second half
        ListNode *prev = nullptr;
        while (slow) {
            ListNode *nextNode = slow->next;
            slow->next = prev;
            prev = slow;
            slow = nextNode;
        }

        // Calculate maximum twin sum
        int maxi = 0;
        ListNode *first = head;
        ListNode *second = prev;

        while (second) {
            maxi = max(maxi, first->val + second->val);
            first = first->next;
            second = second->next;
        }

        return maxi;
    }
};