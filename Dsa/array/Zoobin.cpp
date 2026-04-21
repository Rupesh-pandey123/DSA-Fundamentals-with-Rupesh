#include <bits/stdc++.h>
using namespace std;

// Lambda to normalize an edge list: ensures (u, v) where u < v and sorts the list.
auto normalize_edges = [](vector<pair<int, int>> edges) {
    for (auto& edge : edges) {
        if (edge.first > edge.second) {
            swap(edge.first, edge.second);
        }
    }
    sort(edges.begin(), edges.end());
    return edges;
};

// Lambda to serialize an edge list into a unique string key for the map/set.
auto serialize_edges = [](const vector<pair<int, int>>& normalized_edges) {
    string key_string;
    for (auto [u, v] : normalized_edges) {
        key_string += to_string(u) + "-" + to_string(v) + ",";
    }
    return key_string;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // a -> num_edges
    int num_edges;
    if (!(cin >> num_edges)) return 0;

    // b -> start_edges
    // c -> target_edges
    vector<pair<int, int>> start_edges(num_edges), target_edges(num_edges);

    // d -> all_nodes (set of unique nodes involved)
    set<int> unique_nodes_set;

    // Read starting edges and collect all unique nodes
    for (int i = 0; i < num_edges; i++) {
        cin >> start_edges[i].first >> start_edges[i].second;
        unique_nodes_set.insert(start_edges[i].first);
        unique_nodes_set.insert(start_edges[i].second);
    }

    // Read target edges
    for (int i = 0; i < num_edges; i++) cin >> target_edges[i].first >> target_edges[i].second;

    // e -> all_nodes_vec (sorted vector of unique nodes)
    vector<int> all_nodes_vec(unique_nodes_set.begin(), unique_nodes_set.end());

    // Normalize and serialize the target state
    vector<pair<int, int>> normalized_target_edges = normalize_edges(target_edges);
    string target_state_key = serialize_edges(normalized_target_edges); // p -> target_state_key

    // Normalize and serialize the start state
    vector<pair<int, int>> normalized_start_edges = normalize_edges(start_edges);
    string start_state_key = serialize_edges(normalized_start_edges); // r -> start_state_key

    // Check if start state is already the target state
    if (start_state_key == target_state_key) {
        cout << 0 << "\n";
        return 0;
    }

    // s -> visited_states (map to store minimum operations to reach a state)
    map<string, int> visited_states;

    // t -> state_queue (BFS queue: {edge_list, operations_count})
    queue<pair<vector<pair<int, int>>, int>> state_queue;

    // Initialize BFS
    state_queue.push({normalized_start_edges, 0});
    visited_states[start_state_key] = 0;

    while (!state_queue.empty()) {
        // u -> current_edges
        // v -> current_ops
        auto [current_edges, current_ops] = state_queue.front();
        state_queue.pop();

        // Build adjacency list for the current graph state
        // w -> current_adj_list
        map<int, vector<int>> current_adj_list;
        for (auto [u_node, v_node] : current_edges) {
            current_adj_list[u_node].push_back(v_node);
            current_adj_list[v_node].push_back(u_node);
        }

        // Find all unique simple cycles (length >= 3) in the current graph
        // z -> found_cycles
        set<vector<int>> found_cycles;

        for (int start_node : all_nodes_vec) { // Iterate over all possible start nodes
            
            // Recursive function to find cycles (Depth-First Search component)
            // ab -> find_cycles_dfs
            function<void(int, int, vector<int>&, set<int>&)> find_cycles_dfs = 
                [&](int current_node, int parent_node, vector<int>& current_path, set<int>& visited_in_path) {
                
                // Add current node to path and mark as visited in this path
                current_path.push_back(current_node);
                visited_in_path.insert(current_node);

                for (int neighbor : current_adj_list[current_node]) {
                    if (neighbor == parent_node) continue; // Don't go back immediately

                    if (visited_in_path.count(neighbor)) {
                        // Cycle found: neighbor is already in the current path
                        auto cycle_start_it = find(current_path.begin(), current_path.end(), neighbor);
                        
                        if (cycle_start_it != current_path.end()) {
                            // ai -> current_cycle_nodes (extract cycle from path)
                            vector<int> current_cycle_nodes(cycle_start_it, current_path.end());
                            
                            if (current_cycle_nodes.size() >= 3) { // Must be a simple cycle
                                // Normalize cycle: start with the minimum element
                                // aj -> min_element_index
                                int min_element_index = min_element(current_cycle_nodes.begin(), current_cycle_nodes.end()) - current_cycle_nodes.begin();
                                rotate(current_cycle_nodes.begin(), 
                                       current_cycle_nodes.begin() + min_element_index, 
                                       current_cycle_nodes.end());
                                
                                found_cycles.insert(current_cycle_nodes); // Store the normalized cycle
                            }
                        }
                    } 
                    // Limit search depth to prevent excessive recursion, 
                    // though the condition 'current_path.size() < all_nodes_vec.size()' 
                    // is a weak optimization and mainly prevents paths longer than the node count.
                    else if (current_path.size() < all_nodes_vec.size()) { 
                        find_cycles_dfs(neighbor, current_node, current_path, visited_in_path);
                    }
                }
                
                // Backtrack
                current_path.pop_back();
                visited_in_path.erase(current_node);
            };

            vector<int> current_path; // ak -> current_path
            set<int> visited_nodes; // al -> visited_nodes
            find_cycles_dfs(start_node, -1, current_path, visited_nodes);
        }

        // Apply each cycle rotation as a new state transition
        for (const auto& cycle_nodes : found_cycles) { // am -> cycle_nodes
            // an -> node_mapping: Stores the mapping of old node ID to new node ID after rotation
            map<int, int> node_mapping;
            for (int node : all_nodes_vec) node_mapping[node] = node; // Initialize identity map
            
            // Apply the cyclic shift: node[i] maps to node[i+1]
            int cycle_length = cycle_nodes.size(); // ap -> cycle_length
            for (int i = 0; i < cycle_length; i++) {
                node_mapping[cycle_nodes[i]] = cycle_nodes[(i + 1) % cycle_length];
            }
            
            // Build the next edge list by applying the node mapping
            vector<pair<int, int>> next_edges; // ar -> next_edges
            for (auto [u_node, v_node] : current_edges) { // as, at -> u_node, v_node
                next_edges.push_back({node_mapping[u_node], node_mapping[v_node]});
            }
            
            // Normalize and serialize the next state
            next_edges = normalize_edges(next_edges);
            string next_state_key = serialize_edges(next_edges); // au -> next_state_key

            // Check for goal
            if (next_state_key == target_state_key) {
                cout << current_ops + 1 << "\n";
                return 0;
            }

            // Continue BFS
            if (visited_states.find(next_state_key) == visited_states.end()) {
                visited_states[next_state_key] = current_ops + 1;
                state_queue.push({next_edges, current_ops + 1});
            }
        }
    }

    // If the queue empties and the target is not found
    cout << -1;
    return 0;
}