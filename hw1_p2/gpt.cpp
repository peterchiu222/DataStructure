#include <iostream>
#include <vector>

using namespace std;

// Structure to represent a disjoint-set element
struct DisjointSetElement {
    int parent;
    int rank; // Height of the tree
};

// Initialize a disjoint-set element
void makeSet(vector<DisjointSetElement> &sets, int n) {
    for (int i = 0; i < n; ++i) {
        sets[i].parent = -i; // Each element is its own root initially
        sets[i].rank = 0;    // Initial height is 0
    }
}

// Find the root of the set containing element x (with path compression)
int findSet(vector<DisjointSetElement> &sets, int x) {
    if (sets[x].parent < 0) {
        return x; // x is the root
    } else {
        sets[x].parent = findSet(sets, sets[x].parent); // Path compression
        return sets[x].parent;
    }
}

// Union two sets using the height rule
void unionSets(vector<DisjointSetElement> &sets, int a, int b) {
    a = findSet(sets, a);
    b = findSet(sets, b);
    
    if (a != b) {
        if (sets[a].rank < sets[b].rank) {
            sets[a].parent = b; // Make b the parent
        } else if (sets[a].rank > sets[b].rank) {
            sets[b].parent = a; // Make a the parent
        } else {
            // Heights are equal, choose one as the parent and increase its rank
            sets[b].parent = a;
            sets[a].rank++;
        }
    }
}

int main() {
    int t;
    cin >> t; // Number of test cases
    
    while (t--) {
        int n, ops;
        cin >> n >> ops;
        
        vector<DisjointSetElement> sets(n);
        makeSet(sets, n);

        while (ops--) {
            int op, a, b;
            cin >> op;
            if (op == 1) {
                cin >> a >> b;
                unionSets(sets, a, b);
            } else if (op == 2) {
                cin >> a;
                cout << findSet(sets, a) << endl;
            } else if (op == 3) {
                cin >> a >> b;
                cout << (findSet(sets, a) == findSet(sets, b) ? "true" : "false") << endl;
            }
        }
    }

    return 0;
}
