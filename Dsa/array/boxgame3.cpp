#include <bits/stdc++.h>
using namespace std;

struct Cube {
    int N;
    vector<vector<vector<char>>> f;
    Cube(int n): N(n), f(6, vector<vector<char>>(n, vector<char>(n))) {}
};

void rotateFace(vector<vector<char>> &face, bool clockwise) {
    int n = face.size();
    vector<vector<char>> tmp = face;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            face[i][j] = clockwise ? tmp[n - j - 1][i] : tmp[j][n - i - 1];
}

// Return true iff the cube is solved: every face has all identical characters
bool isSolved(Cube &c) {
    for (int f = 0; f < 6; f++) {
        char ch = c.f[f][0][0];
        for (int i = 0; i < c.N; i++) {
            for (int j = 0; j < c.N; j++) {
                if (c.f[f][i][j] != ch)
                    return false;
            }
        }
    }
    return true;
}

void apply(Cube &c, const string &ins) {
    if (ins.empty()) return;
    stringstream ss(ins);
    string a;
    if (!(ss >> a)) return;

    if (a == "turn") {
        // expects: "turn left" or "turn right"
        string b;
        if (!(ss >> b)) return;
        bool left = (b == "left");
        // NOTE: This is a placeholder: rotating every face the same way.
        // A real cube-turn must move strips between faces — not implemented here.
        for (int i = 0; i < 6; i++) rotateFace(c.f[i], left);
    }
    else if (a == "rotate") {
        // expects: "rotate front" or "rotate right" or "rotate top" etc.
        string b;
        if (!(ss >> b)) return;
        // treat front/right/top as clockwise examples (placeholder)
        bool cw = (b == "front" b == "right" b == "top");
        for (int i = 0; i < 6; i++) rotateFace(c.f[i], cw);
    }
    else {
        // other instruction patterns: e.g. "<side> <index> <direction>"
        string b, d;
        if (!(ss >> b >> d)) return;
        bool cw = (d == "right" || d == "down");
        // placeholder: rotate all faces
        for (int i = 0; i < 6; i++) rotateFace(c.f[i], cw);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    if (!(cin >> N >> K)) return 0;

    Cube cube(N);
    for (int f = 0; f < 6; f++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> cube.f[f][i][j];

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<string> instr(K);
    for (int i = 0; i < K; i++) {
        getline(cin, instr[i]);
        if(instr[i].empty()) { i--; continue; } // handle blank lines safely
    }

    string wrong = "";
    bool faulty = false;

    // Try removing one instruction (non-faulty case)
    for (int skip = 0; skip < K && wrong == ""; skip++) {
        Cube temp = cube;
        for (int i = 0; i < K; i++)
            if (i != skip) apply(temp, instr[i]);
        if (isSolved(temp)) {
            wrong = instr[skip];
            break;
        }
    }

    if (!wrong.empty()) {
        cout << wrong << "\n";
        return 0;
    }

    // Try assuming cube faulty (one cube color changed)
    for (int skip = 0; skip < K && wrong == ""; skip++) {
        for (int f = 0; f < 6 && wrong == ""; f++)
            for (int i = 0; i < N && wrong == ""; i++)
                for (int j = 0; j < N && wrong == ""; j++) {
                    char orig = cube.f[f][i][j];
                    for (char ch = 'A'; ch <= 'Z'; ch++) {
                        if (ch == orig) continue;
                        Cube temp = cube;
                        temp.f[f][i][j] = ch;
                        for (int k = 0; k < K; k++)
                            if (k != skip) apply(temp, instr[k]);
                        if (isSolved(temp)) {
                            faulty = true;
                            wrong = instr[skip];
                            break;
                        }
                    }
                }
    }

    if (!wrong.empty() && faulty)
        cout << "Faulty\n" << wrong << "\n";
    else
        cout << "Not Possible\n";

    return 0;
}