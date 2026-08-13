class Solution {
public:
    struct Node {
        char leftChar = 0;
        char rightChar = 0;
        int len = 0;
        int prefix = 0;
        int suffix = 0;
        int best = 0;
    };

    vector<Node> tree;

    Node merge(Node left, Node right) {
        Node res;

        res.leftChar = left.leftChar;
        res.rightChar = right.rightChar;
        res.len = left.len + right.len;

        res.best = max(left.best, right.best);

        res.prefix = left.prefix;

        if (left.prefix == left.len &&
            left.rightChar == right.leftChar) {
            res.prefix = left.len + right.prefix;
        }

        res.suffix = right.suffix;

        if (right.suffix == right.len &&
            left.rightChar == right.leftChar) {
            res.suffix = left.suffix + right.len;
        }

        if (left.rightChar == right.leftChar) {
            res.best = max(res.best, left.suffix + right.prefix);
        }

        return res;
    }

    void build(int node, int l, int r, const string& s) {
        if (l == r) {
            tree[node].leftChar = s[l];
            tree[node].rightChar = s[l];
            tree[node].len = 1;
            tree[node].prefix = 1;
            tree[node].suffix = 1;
            tree[node].best = 1;
            return;
        }

        int mid = l + (r - l) / 2;

        build(node * 2, l, mid, s);

        build(node * 2 + 1, mid + 1, r, s);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, char c) {
        if (l == r) {
            tree[node].leftChar = c;
            tree[node].rightChar = c;
            tree[node].len = 1;
            tree[node].prefix = 1;
            tree[node].suffix = 1;
            tree[node].best = 1;
            return;
        }

        int mid = l + (r - l) / 2;

        if (idx <= mid) {
            update(node * 2, l, mid, idx, c);
        } else {
            update(node * 2 + 1, mid + 1, r, idx, c);
        }

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.size();
        int k = queryCharacters.size();

        tree.resize(4 * n);

        build(1, 0, n - 1, s);

        vector<int> answer;
        answer.reserve(k);

        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);

            answer.push_back(tree[1].best);
        }

        return answer;
    }
};