//example code for my sliding window template.
typedef long long ll;
#include <bits/stdc++.h>
using namespace std;
 
#define nline "\n"
#define lld long double
#define ull unsigned long long
#define maxbit(n) 31 - __builtin_clz(n)
#define maxbitll(n) 63 - __builtin_clzll(n)
#define minbit(n) __builtin_ctz(n)
#define minbitll(n) __builtin_ctzll(n)
#define bits(n) __builtin_popcount(n)
#define bitsll(n) __builtin_popcountll(n)
#ifndef ONLINE_JUDGE
#define debug(x)       \
    cerr << #x << " "; \
    _print(x);         \
    cerr << endl;
#else
#define debug(x)
#endif
 
void _print(ll t) { cerr << t; }
void _print(int t) { cerr << t; }
void _print(string t) { cerr << t; }
void _print(char t) { cerr << t; }
void _print(lld t) { cerr << t; }
void _print(double t) { cerr << t; }
void _print(ull t) { cerr << t; }
 
template <class T, class V>
void _print(pair<T, V> p);
template <class T>
void _print(vector<T> v);
template <class T>
void _print(deque<T> v);
template <class T>
void _print(set<T> v);
template <class T, class V>
void _print(map<T, V> v);
template <class T>
void _print(multiset<T> v);
template <class T, class V>
void _print(pair<T, V> p)
{
    cerr << "{";
    _print(p.first);
    cerr << ",";
    _print(p.second);
    cerr << "}";
}
template <class T>
void _print(vector<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T>
void _print(deque<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T>
void _print(set<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T>
void _print(multiset<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T, class V>
void _print(map<T, V> v)
{
    cerr << "[ ";
    for (auto i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
struct Info
{
    // ll mi = LONG_LONG_MAX;
    ll val = 0;
    // ll ma = LONG_LONG_MIN;
    // ll g = 0;
    ll orr = 0;
};
 
Info operator+(const Info &a, const Info &b)
{
    Info c;
    c.val = a.val;
    // c.ma = max(a.ma, b.ma);
    // c.mi = min(a.mi, b.mi);
    // c.g = __gcd(a.g, b.g);
    c.orr = (a.orr | b.orr);
    return c;
}
void restart(Info &a)
{
    // a.ma = a.val;
    // a.mi = a.val;
    // a.g = a.val;
    a.orr = a.val;
}
 
struct AggStack
{
    // Each element is stored as (value, current_min)
    stack<Info> st;
 
    // Push a new number; compute the new min.
    void push(Info x)
    {
        if (!st.empty())
        {
            Info y = st.top();
            Info z = x + y;
            st.push(z);
        }
        else
        {
            st.push(x); // first element, so push as-is
        }
    }
 
    // Pop the top element.
    void pop()
    {
        st.pop();
    }
 
    // Return the current minimum.
    Info agg() const
    {
        return st.top();
    }
};
struct AggQueue
{
    AggStack in, out;
 
    // Push a new number into the queue.
    void push(Info x)
    {
        in.push(x);
    }
 
    // Pop the oldest number.
    void pop()
    {
        if (out.st.empty())
        {
            while (!in.st.empty())
            {
                Info v = in.st.top();
                in.pop();
                restart(v);
                out.push(v);
            }
        }
        out.pop();
    }
    // Query the current minimum.
    Info query() const
    {
        if (in.st.empty())
            return out.agg();
        if (out.st.empty())
            return in.agg();
        return in.agg() + out.agg();
    }
};
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        int K;
        cin >> K;
        int x, a, b, c;
        cin >> x >> a >> b >> c;
        vector<int> arr(n);
        arr[0] = x;
        for (int i = 1; i < n; i++)
        {
            arr[i] = (a * 1LL * arr[i - 1]) % c;
            arr[i] = (arr[i] + b) % c;
        }
        vector<Info> info_(n);
        for (int i = 0; i < n; i++)
        {
            info_[i].val = arr[i];
            // info_[i].ma = arr[i];
            // info_[i].mi = arr[i];
            // info_[i].g = arr[i];
            info_[i].orr = arr[i];
        }
        vector<int> ans;
        AggQueue mq; // Our aggregated queue maintains the minimum
 
        // Build the initial window of size K.
        for (int i = 0; i < min(n, K); i++)
        {
            mq.push(info_[i]);
        }
 
        ans.push_back(mq.query().orr);
        // Slide the window: add a new element and remove the oldest.
        for (int i = K; i < n; i++)
        {
            mq.push(info_[i]); // add new element
            mq.pop();          // remove element that's left the window
            ans.push_back(mq.query().orr);
        }
        int res = 0;
        for (int i : ans)
            res = res ^ i;
        cout << res;
    }
    return 0;
}
