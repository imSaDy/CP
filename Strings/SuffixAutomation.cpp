#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Count Distinct Substrings: Sum (len[i] - len[link[i]]).
   - Check if substring exists: O(Length of substring).
   - Longest Common Substring of S and T.
   - O(N) Time and Space.
*/

struct SuffixAutomaton {
    struct State {
        int len, link;
        map<char, int> next; // Use map for simplicity, or vector<int>(26, -1) for speed
    };

    const int MAXLEN = 100005;
    vector<State> st;
    int sz, last;

    SuffixAutomaton(string &s) {
        st.resize(MAXLEN * 2);
        st[0].len = 0;
        st[0].link = -1;
        sz = 1;
        last = 0;
        
        for (char c : s) extend(c);
    }

    void extend(char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && st[p].next.find(c) == st[p].next.end()) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    long long count_distinct_substrings() {
        long long cnt = 0;
        for (int i = 1; i < sz; i++) {
            cnt += st[i].len - st[st[i].link].len;
        }
        return cnt;
    }
};

int main() {
    string s = "ababa";
    SuffixAutomaton sa(s);
    // Substrings: a, b, ab, ba, aba, bab, abab, baba, ababa (9 distinct)
    cout << "Distinct Substrings: " << sa.count_distinct_substrings() << endl;
    return 0;
}