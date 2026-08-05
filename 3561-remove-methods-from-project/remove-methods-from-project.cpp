#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        // Tumhara code
    
    // Build adjacency list
    vector<vector<int>> adj(n);
    for (auto &edge : invocations) {
        adj[edge[0]].push_back(edge[1]);
    }

    // Find all suspicious methods using DFS
    vector<bool> suspicious(n, false);
    stack<int> st;
    st.push(k);
    suspicious[k] = true;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        for (int v : adj[u]) {
            if (!suspicious[v]) {
                suspicious[v] = true;
                st.push(v);
            }
        }
    }

    // Check if any non-suspicious method calls a suspicious method
    for (auto &edge : invocations) {
        int from = edge[0];
        int to = edge[1];

        if (!suspicious[from] && suspicious[to]) {
            // Cannot remove suspicious methods
            vector<int> allMethods;
            for (int i = 0; i < n; i++)
                allMethods.push_back(i);
            return allMethods;
        }
    }

    // Return remaining methods
    vector<int> remaining;
    for (int i = 0; i < n; i++) {
        if (!suspicious[i])
            remaining.push_back(i);
    }

    return remaining;
}
};

