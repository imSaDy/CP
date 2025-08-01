#include <bits/stdc++.h> 

using namespace std ; 

typedef long long ll ; 
typedef pair<int, int> pii ; 
typedef pair<ll, ll> pll ; 
typedef long double ld ; 
typedef vector <int> vi ;
typedef vector <ll> vll ;
typedef vector <vi> vvi ; 
typedef vector <pii> vp;

void debug_out() { cerr << endl; }
 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
	cerr << " " << H ;
	debug_out(T...);
}

#define debug(...)             cerr << "(" << #__VA_ARGS__ << "): ", debug_out(__VA_ARGS__)
#define hey                    cerr << "Ey BABA!\n"
#define MP                     make_pair
#define F                     first
#define S                     second
#define pb 					   push_back
#define ppb                    pop_back 
#define all(v)                 v.begin() ,v.end() 
#define len(v)                 (int) v.size()
#define uniq(v)                 v.resize(unique(all(v)) - v.begin());

const int maxn = 1e6 + 5; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const ll INF = 1e18;

// O(n) 0-indexed
int recJosephus(int n, int k){
    return n > 1 ? (recJosephus(n - 1, k) + k) % n : 0; 
}
int josephus(int n, int k){
    int res = 0; 
    for (int i = 1; i <= n; i++)
        res = (res + k) % i;
    return res;
}

// O(klogn) if k is small
int josephusK(int n, int k){
    if (n == 1)
        return 0; 
    if (k == 1)
        return n - 1;
    if (k > n)
        return (josephusK(n - 1, k) + k) % n; 
    int cnt = n / k; 
    int res = josephus(n - cnt, k); 
    res -= n % k;
    if (res < 0)
        res += n; 
    else
        res += res / (k - 1); 
    return res; 
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, k;
    cin >> n >> k; 
    cout << recJosephus(n, k + 1) + 1;
}


