#include <bits/stdc++.h> 
using namespace std; 

int main() { 
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    int m, n; 
    if (!(cin >> m >> n)) return 0; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    vector<int> c(n, 0); 
    for (int i = 0; i < m; ++i) { 
        string ln, s; 
        getline(cin, ln); 
        for (char ch : ln) if (ch != ' ') s.push_back(ch); 
        for (int j = 0; j < n; ++j) if (s[j] == '*') ++c[j]; 
    } 

    int k;  
    cin >> k; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    for (int t = 0; t < k; ++t) { 
        string d;  
        getline(cin, d); 

        vector<int> f(m + 1, 0); 
        for (int v : c) ++f[v]; 

        vector<int> sfx(m + 2, 0); 
        int cur = 0; 
        for (int x = m; x >= 0; --x) { 
            cur += f[x]; 
            sfx[x] = cur; 
        } 

        int nm = n, nn = m; 
        vector<int> nc(nn, 0); 

        if (d == "right") { 
            for (int col = 0; col < nn; ++col) nc[col] = sfx[col + 1]; 
        } else { 
            for (int col = 0; col < nn; ++col) nc[col] = sfx[m - col]; 
        } 

        m = nm; n = nn; c.swap(nc); 
    } 

    for (int i = 0; i < m; ++i) { 
        for (int j = 0; j < n; ++j) { 
            char ch = (i >= m - c[j]) ? '*' : '.'; 
            if (j) cout << ' '; 
            cout << ch; 
        } 
        if (i + 1 < m) cout << '\n'; 
    } 
    return 0; 
} 