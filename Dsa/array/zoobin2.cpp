#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int z;
    cin >> z;
    vector<pair<int,int>> b(z), c(z);
    set<int> d;
    for (int i = 0; i < z; i++) {
        cin >> b[i].first >> b[i].second;
        d.insert(b[i].first);
        d.insert(b[i].second);
    }
    for (int i = 0; i < z; i++) cin >> c[i].first >> c[i].second;
    vector<int> e(d.begin(), d.end());
    auto f = [](vector<pair<int,int>> g) {
        for (auto& [h, i] : g) if (h > i) swap(h, i);
        sort(g.begin(), g.end());
        return g;
    };
    auto j = [](const vector<pair<int,int>>& k) {
        string l;
        for (auto [m, n] : k) l += to_string(m) + "-" + to_string(n) + ",";
        return l;
    };
    vector<pair<int,int>> o = f(c);
    string p = j(o);
    vector<pair<int,int>> q = f(b);
    string r = j(q);
    if (r == p) {
        cout << 0;
        return 0;
    }
    map<string,int> s;
    queue<pair<vector<pair<int,int>>,int>> t;
    t.push({q,0});
    s[r] = 0;
    while (!t.empty()) {
        auto [u,v] = t.front();
        t.pop();
        map<int,vector<int>> w;
        for (auto [x,y] : u) {
            w[x].push_back(y);
            w[y].push_back(x);
        }
        set<vector<int>> z;
        for (int aa : e) {
            function<void(int,int,vector<int>&,set<int>&)> ab = [&](int ac,int ad,vector<int>& ae,set<int>& af) {
                ae.push_back(ac);
                af.insert(ac);
                for (int ag : w[ac]) {
                    if (ag == ad) continue;
                    if (af.count(ag)) {
                        auto ah = find(ae.begin(), ae.end(), ag);
                        if (ah != ae.end()) {
                            vector<int> ai(ah, ae.end());
                            if (ai.size() >= 3) {
                                int aj = min_element(ai.begin(), ai.end()) - ai.begin();
                                rotate(ai.begin(), ai.begin() + aj, ai.end());
                                z.insert(ai);
                            }
                        }
                    } else if (ae.size() < e.size()) ab(ag, ac, ae, af);
                }
                ae.pop_back();
                af.erase(ac);
            };
            vector<int> ak;
            set<int> al;
            ab(aa, -1, ak, al);
        }
        for (const auto& am : z) {
            map<int,int> an;
            for (int ao : e) an[ao] = ao;
            int ap = am.size();
            for (int aq = 0; aq < ap; aq++) an[am[aq]] = am[(aq + 1) % ap];
            vector<pair<int,int>> ar;
            for (auto [as, at] : u) ar.push_back({an[as], an[at]});
            ar = f(ar);
            string au = j(ar);
            if (au == p) {
                cout << v + 1;
                return 0;
            }
            if (!s.count(au)) {
                s[au] = v + 1;
                t.push({ar, v + 1});
            }
        }
    }
    cout << -1;
    return 0;
}