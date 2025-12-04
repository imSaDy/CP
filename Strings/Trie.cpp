#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Insert/Search strings: O(L)
   - Count strings with given prefix.
   - MAX XOR PAIR: Insert numbers as binary strings (30 bits). 
     Query by traversing opposite bit (1->0, 0->1) if possible.
*/

const int MAX_NODES = 100005; 
const int ALPHABET = 26;

struct Trie {
    int next[MAX_NODES][ALPHABET];
    int count[MAX_NODES]; // Count of words ending at or passing through node
    int end[MAX_NODES];   // Count of words exactly ending here
    int nodes;

    Trie() {
        nodes = 1; // Root is 0
        memset(next, -1, sizeof(next));
        memset(count, 0, sizeof(count));
        memset(end, 0, sizeof(end));
    }

    void insert(string& s) {
        int v = 0;
        for (char c : s) {
            int idx = c - 'a'; // or c - '0' for binary
            if (next[v][idx] == -1) {
                next[v][idx] = nodes++;
            }
            v = next[v][idx];
            count[v]++;
        }
        end[v]++;
    }

    int search_prefix_count(string& s) {
        int v = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (next[v][idx] == -1) return 0;
            v = next[v][idx];
        }
        return count[v];
    }
};

// --- SPECIAL: XOR TRIE (For Max XOR Pair) ---
struct BinaryTrie {
    int next[MAX_NODES * 30][2]; // 0 or 1
    int nodes = 1;
    
    BinaryTrie() { memset(next, -1, sizeof(next)); }

    void insert(int num) {
        int v = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (next[v][bit] == -1) next[v][bit] = nodes++;
            v = next[v][bit];
        }
    }

    int get_max_xor(int num) {
        int v = 0, res = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (num >> i) & 1;
            // Try to go opposite direction (0->1, 1->0) to maximize XOR
            if (next[v][1 - bit] != -1) {
                res |= (1 << i);
                v = next[v][1 - bit];
            } else {
                v = next[v][bit];
            }
        }
        return res;
    }
};

int main() {
    BinaryTrie bt;
    bt.insert(3); // 011
    bt.insert(5); // 101
    // Max XOR with 4 (100): Should match with 3 (011) -> 100 ^ 011 = 111 (7)
    cout << bt.get_max_xor(4) << endl; 
    return 0;
}