#include <vector>
#include <stack>
using namespace std;

// Next Greater Element to the Right (1-based)
vector<int> nextGreaterToRight(const vector<int> &arr, int n) {
    vector<int> res(n + 1, -1);
    stack<int> s;

    for (int i = 1; i <= n; i++) {
        while (!s.empty() && arr[i] > arr[s.top()]) {
            res[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    return res;
}

// Next Greater Element to the Left (1-based)
vector<int> nextGreaterToLeft(const vector<int> &arr, int n) {
    vector<int> res(n + 1, -1);
    stack<int> s;

    for (int i = n; i >= 1; i--) {
        while (!s.empty() && arr[i] > arr[s.top()]) {
            res[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    return res;
}

// Next Smaller Element to the Right (1-based)
vector<int> nextSmallerToRight(const vector<int> &arr, int n) {
    vector<int> res(n + 1, -1);
    stack<int> s;

    for (int i = 1; i <= n; i++) {
        while (!s.empty() && arr[i] < arr[s.top()]) {
            res[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    return res;
}

// Next Smaller Element to the Left (1-based)
vector<int> nextSmallerToLeft(const vector<int> &arr, int n) {
    vector<int> res(n + 1, -1);
    stack<int> s;

    for (int i = n; i >= 1; i--) {
        while (!s.empty() && arr[i] < arr[s.top()]) {
            res[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    return res;
}
