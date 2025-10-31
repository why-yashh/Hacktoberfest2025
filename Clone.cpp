#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

// Definition for a Node
struct Node {
    int val;
    vector<Node*> neighbors;
};

// Clone the graph 
Node* cloneGraph(Node* node) {
    if (!node) return nullptr;

    map<Node*, Node*> mp;
    queue<Node*> q;
     
    // Clone the source node
    Node* clone = new Node();
    clone->val = node->val;
    mp[node] = clone;
    q.push(node);

    while (!q.empty()) {
        Node* u = q.front();
        q.pop();

        for (auto neighbor : u->neighbors) {
            
            // Clone neighbor if not already cloned
            if (mp.find(neighbor) == mp.end()) {
                Node* neighborClone = new Node();
                neighborClone->val = neighbor->val;
                mp[neighbor] = neighborClone;
                q.push(neighbor);
            }

            // Link clone of neighbor to clone of current node
            mp[u]->neighbors.push_back(mp[neighbor]);
        }
    }

    return mp[node];
}

// Build graph
Node* buildGraph() {
    Node* node1 = new Node(); node1->val = 0;
    Node* node2 = new Node(); node2->val = 1;
    Node* node3 = new Node(); node3->val = 2;
    Node* node4 = new Node(); node4->val = 3;

    node1->neighbors = {node2, node3};
    node2->neighbors = {node1, node3};
    node3->neighbors = {node1, node2, node4};
    node4->neighbors = {node3};

    return node1;
}
 
// Compare two graphs for structural and value equality
bool compareGraphs(Node* node1, Node* node2, 
                          map<Node*, Node*>& visited) {
    if (!node1 || !node2) 
        return node1 == node2;
        
    if (node1->val != node2->val || node1 == node2)
        return false;

    visited[node1] = node2;

    if (node1->neighbors.size() != node2->neighbors.size()) 
        return false;

    for (size_t i = 0; i < node1->neighbors.size(); ++i) {
        Node* n1 = node1->neighbors[i];
        Node* n2 = node2->neighbors[i];

        if (visited.count(n1)) {
            if (visited[n1] != n2) 
                return false;
        } else {
            if (!compareGraphs(n1, n2, visited))
                return false;
        }
    }

    return true;
}

// Driver Code
int main() {
    Node* original = buildGraph();

    Node* cloned = cloneGraph(original);
    map<Node*, Node*> visited;
    cout << (compareGraphs(original, cloned, visited) ? 
                          "true" : "false") << endl;
    return 0;
}
