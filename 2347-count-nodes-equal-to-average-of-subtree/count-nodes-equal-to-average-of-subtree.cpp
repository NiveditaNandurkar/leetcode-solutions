/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    pair<int,int> avg(TreeNode* node, int &count){
        if(node == NULL){
            return {0,0};
        }

        auto l = avg(node->left, count);
        auto r = avg(node->right, count);

        int sum = node->val + l.first + r.first;
        int cnt = l.second + r.second + 1;

        if(sum / cnt == node->val) count++;

        return {sum, cnt};
    }
    int averageOfSubtree(TreeNode* root) {
        int count = 0;
        avg(root, count);
        return count;
    }
};