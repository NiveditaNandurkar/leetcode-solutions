class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> right(n);

        int cnter = 0; // max len of subsequence that can be formed
        int R = m - 1; // this is a pointer in word2

        for (int i = n - 1; i >= 0; i--) {
            right[i] = cnter;
            if (R >= 0 && word2[R] == word1[i] ) {
                R--; // move backword in word2;
                cnter++; // max len of subsequence++;
            }
        }

        vector<int> ans;
        bool change = false;
        int j = 0; // use it to iterate in word2 0->M

        for (int i = 0; i < n && j < m; i++) {
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                j++; // move this beacause we have matched w2[j]
            }

            // now we have a mismatch and we can fix it, if
            // !changed, but we also need to ensure that we have,
            // enough future valid character matches remaining, that,
            // we can match the string that comes afterwards.
            else if (!change && right[i] >= m - j - 1) {
                ans.push_back(i);
                j++;
                change = true;
            }
        }

        if (j == m) {
            return ans;
        }
        return {};
    }
};