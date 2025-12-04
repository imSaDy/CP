#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Dynamic Array Operations in O(log N).
   - Reverse Range, Cut & Paste Range, Range Sum/Min/Max.
   - Insert/Delete at arbitrary position.
*/

typedef long long ll;

struct Node {
    int prior, size;
    ll val, sum; // Value and Aggregate
    bool rev;    // Lazy Reverse Tag
    Node *l, *r;
    
    Node(ll v) {
        val = sum = v;
        prior = rand();
        size = 1;
        rev = false;
        l = r = nullptr;
    }
};

int cnt(Node* t) { return t ? t->size : 0; }
ll get_sum(Node* t) { return t ? t->sum : 0; }

void update_cnt(Node* t) {
    if (t) {
        t->size = 1 + cnt(t->l) + cnt(t->r);
        t->sum = t->val + get_sum(t->l) + get_sum(t->r);
    }
}

// Push Lazy Tags
void push(Node* t) {
    if (t && t->rev) {
        t->rev = false;
        swap(t->l, t->r);
        if (t->l) t->l->rev ^= true;
        if (t->r) t->r->rev ^= true;
    }
}

// Split t into l (first k elements) and r (rest)
void split(Node* t, Node*& l, Node*& r, int k) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    push(t);
    int current_key = cnt(t->l); // Implicit Index
    if (current_key < k) {
        split(t->r, t->r, r, k - 1 - current_key);
        l = t;
    } else {
        split(t->l, l, t->l, k);
        r = t;
    }
    update_cnt(t);
}

// Merge l and r into t
void merge(Node*& t, Node* l, Node* r) {
    push(l); push(r);
    if (!l || !r) t = l ? l : r;
    else if (l->prior > r->prior) {
        merge(l->r, l->r, r);
        t = l;
    } else {
        merge(r->l, l, r->l);
        t = r;
    }
    update_cnt(t);
}

// Wrapper: Reverse range [l, r] (0-based)
void reverse_range(Node*& root, int l, int r) {
    Node *t1, *t2, *t3;
    // Split into [0...l-1], [l...r], [r+1...end]
    split(root, t1, t2, l);
    split(t2, t2, t3, r - l + 1);
    
    // Apply reverse
    if(t2) t2->rev ^= true;
    
    // Merge back
    merge(root, t1, t2);
    merge(root, root, t3);
}

// Wrapper: Query range [l, r]
ll query(Node*& root, int l, int r) {
    Node *t1, *t2, *t3;
    split(root, t1, t2, l);
    split(t2, t2, t3, r - l + 1);
    
    ll ans = get_sum(t2);
    
    merge(root, t1, t2);
    merge(root, root, t3);
    return ans;
}

// Print array (In-order traversal)
void output(Node* t) {
    if (!t) return;
    push(t);
    output(t->l);
    cout << t->val << " ";
    output(t->r);
}

int main() {
    srand(time(0));
    Node* root = nullptr;
    
    // Create array: 1, 2, 3, 4, 5
    for(int i=1; i<=5; i++) merge(root, root, new Node(i));
    
    // Reverse indices 1 to 3 -> 1, 4, 3, 2, 5
    reverse_range(root, 1, 3);
    
    output(root); cout << endl;
    cout << "Sum [1, 3]: " << query(root, 1, 3) << endl; // 4+3+2 = 9
    
    return 0;
}