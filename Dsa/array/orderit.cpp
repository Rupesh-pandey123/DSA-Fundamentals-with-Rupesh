#include<bits/stdc++.h> 
using namespace std; 
static int min_rearrange_operations(const vector<int>& a) {
    int n = (int)a.size();
    
    // 1. Convert integer array to string for use as map keys (state representation)
    string start_state(n, '\0');
    string goal_state(n, '\0');
    for (int i = 0; i < n; ++i) start_state[i] = char(a[i]);
    for (int i = 0; i < n; ++i) goal_state[i] = char(i); // The identity permutation: (0, 1, 2, ...)

    if (start_state == goal_state) return 0;

    // 2. Pre-calculate all possible segment moves (i, j, k)
    // i: start index of segment (inclusive); j: end index (exclusive); k: new insertion index
    vector<array<int,3>> segment_moves;
    segment_moves.reserve(n * n * n);
    for (int i = 0; i < n; ++i) { 
        for (int j = i + 1; j <= n; ++j) { 
            int segment_length = j - i;
            for (int k = 0; k <= n - segment_length; ++k) { 
                if (k == i) continue;
                segment_moves.push_back({i, j, k});
            }
        }
    }

    // 3. Bidirectional BFS Setup
    deque<string> queue_start, queue_goal;
    unordered_map<string, int> dist_start, dist_goal;

    queue_start.push_back(start_state); 
    dist_start.emplace(start_state, 0);

    queue_goal.push_back(goal_state); 
    dist_goal.emplace(goal_state, 0);

    // 4. Expansion Lambda Function
    auto expand_search = [&](deque<string>& current_queue, 
                             unordered_map<string, int>& dist_self,
                             unordered_map<string, int>& dist_other) -> int {
        int queue_size = (int)current_queue.size();
        while (queue_size--) {
            string current_state = current_queue.front(); current_queue.pop_front();
            int current_distance = dist_self[current_state];
            
            for (auto &move_triple : segment_moves) {
                int i = move_triple[0]; 
                int j = move_triple[1]; 
                int k = move_triple[2]; 
                int segment_length = j - i;
                
                // Cut segment
                string segment = current_state.substr(i, segment_length);
                
                // Remaining part
                string remaining_part = current_state.substr(0, i) + current_state.substr(j);
                
                // Paste segment
                string next_state = remaining_part.substr(0, k) + segment + remaining_part.substr(k);
                
                if (dist_self.count(next_state)) continue;

                int new_distance = current_distance + 1;
                
                // Check for meeting point
                auto it = dist_other.find(next_state);
                if (it != dist_other.end()) {
                    return new_distance + it->second; 
                }
                
                // Continue search
                dist_self.emplace(next_state, new_distance);
                current_queue.push_back(next_state);
            }
        }
        return -1;
    };

    // 5. Bidirectional Search Loop
    while (!queue_start.empty() && !queue_goal.empty()) {
        int answer;
        // Expand the smaller queue
        if (queue_start.size() <= queue_goal.size()) {
            answer = expand_search(queue_start, dist_start, dist_goal);
        } else {
            answer = expand_search(queue_goal, dist_goal, dist_start);
        }

        if (answer != -1) return answer;
    }
    
    return 0; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    string line;
    getline(cin, line);           // consume endline after n
    getline(cin, line);           // blank line
    
    vector<string> shuffled_strings(n), original_strings(n);
    
    // Read the shuffled list of strings
    for (int i = 0; i < n; ++i) getline(cin, shuffled_strings[i]);
    
    getline(cin, line);           // blank line
    
    // Read the original list of strings
    for (int i = 0; i < n; ++i) getline(cin, original_strings[i]);

    // 1. Create a map to convert original strings to their identity index (0 to n-1)
    unordered_map<string, int> string_to_index_map;
    string_to_index_map.reserve(n * 2);
    for (int i = 0; i < n; ++i) string_to_index_map[original_strings[i]] = i;

    // 2. Convert the problem into a permutation sorting problem
    vector<int> permutation_array(n);
    for (int i = 0; i < n; ++i) {
        // 'permutation_array[i]' is the identity index of the string currently at position 'i'.
        permutation_array[i] = string_to_index_map[shuffled_strings[i]];
    }

    // 3. Solve the minimum operations problem
    cout << min_rearrange_operations(permutation_array) << "\n";
    return 0;
}