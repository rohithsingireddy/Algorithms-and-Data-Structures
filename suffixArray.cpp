#include <bits/stdc++.h>
using namespace std;


#ifdef NANANA
	#include "containerHelper.h"
#endif

#define ll long long
//#define p(i,j) pair<i,j>
#define v(i) vector<i>
#define pb push_back
#define pf push_front
#define x first
#define y second
#define all(x) begin(x), end(x)
#define FASTIO ios::sync_with_stdio(false);cin.tie(NULL);

const int alp = 256;
const int N = 1e6;
const int MOD = 1e9+7;
//From site::CP-Algorithms
vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
   
    vector<int> p(n);
    int c[n], cnt[max(n,alp)];
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alp; i++)
        cnt[i] += cnt[i-1];
    for (int i = n-1; i >= 0; i--)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }

    int pn[n], cn[n];
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        memset(cnt, 0, sizeof cnt);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
	cout << p;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        memcpy(c, cn, sizeof cn);
        
        
    }
    return p;
}

v(int) lcpConst(string s, v(int) suffArr)
{
    int n = s.size();
    int rank[n];
    memset(rank, 0, sizeof rank);
    for( int i = 0; i < n; ++i ) rank[suffArr[i]] = i;
    int k = 0;
    v(int) lcp(n-1, 0);
    for( int i = 0; i < n; ++i )
    {
        if(rank[i] == n-1)
            k = 0;
        else
        {
            int j = suffArr[rank[i]+1];
            while(i+k < n && j+k < n && s[i+k] == s[j+k]) k++;
            lcp[rank[i]] = k;
            if(k) k--;
        }
    }
    return lcp;
}



int main()
{
    string s;
    cin >> s;
    s += '$';
    auto t = sort_cyclic_shifts(s);
    t.erase(t.begin());
    s.pop_back();
    
    cout << t;
    
        //cout << sort_cyclic_shifts(s);    
    return 0;
}
