#include <bits/stdc++.h>
using namespace std;

// Represents a 2D coordinate point
struct Point {
    int x, y;
    bool operator==(const Point &o) const { return x == o.x && y == o.y; }
};

// Hash function for Point (P -> PH)
struct PointHasher {
    size_t operator()(Point const &p) const {
        // Combines x and y into a single size_t using bit manipulation
        return (uint64_t(uint32_t(p.x)) << 32) ^ uint32_t(p.y);
    }
};

// Represents a state: position (x, y) and the ID of the current slide (s)
struct State {
    int x, y, slide_id;
    bool operator==(const State &o) const { return x == o.x && y == o.y && slide_id == o.slide_id; }
};

// Hash function for State (K -> KH)
struct StateHasher {
    size_t operator()(State const &k) const {
        uint64_t h = k.x;
        h = (h << 21) ^ k.y;
        h = (h << 21) ^ k.slide_id;
        return size_t(h);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read all input into a vector of long long
    vector<long long> all_input_values;
    long long v;
    while (cin >> v) all_input_values.push_back(v);

    int input_idx = 0;
    
    // Read N, the number of slides
    int num_slides = (int)all_input_values[input_idx++];
    
    // Read slide definitions (x1, y1, x2, y2)
    vector<array<int, 4>> slide_definitions(num_slides); // sl -> slide_definitions
    for (int j = 0; j < num_slides; j++) {
        slide_definitions[j][0] = (int)all_input_values[input_idx++];
        slide_definitions[j][1] = (int)all_input_values[input_idx++];
        slide_definitions[j][2] = (int)all_input_values[input_idx++];
        slide_definitions[j][3] = (int)all_input_values[input_idx++];
    }
    
    // Read starting position (x, y) and initial energy/state count (E)
    int start_x = (int)all_input_values[input_idx++]; // sx -> start_x
    int start_y = (int)all_input_values[input_idx++]; // sy -> start_y
    int initial_energy = (int)all_input_values[input_idx++]; // e -> initial_energy

    // Maps a Point to the IDs of all slides that pass through it
    unordered_map<Point, vector<int>, PointHasher> grid_slide_ids; // g -> grid_slide_ids
    
    // Maps a State (x, y, slide_id) to the coordinates of the next point on that slide
    unordered_map<State, pair<int, int>, StateHasher> next_point_on_slide; // nx -> next_point_on_slide

    // Pre-processing: Build the grid and next-point maps
    for (int s = 0; s < num_slides; s++) {
        int x1 = slide_definitions[s][0], y1 = slide_definitions[s][1];
        int x2 = slide_definitions[s][2], y2 = slide_definitions[s][3];
        
        // Assuming slides are diagonal (y changes by 1 for every step)
        int dx = (x2 > x1) ? 1 : (x2 < x1) ? -1 : 0;
        int dy = (y2 > y1) ? 1 : (y2 < y1) ? -1 : 0;
        
        // This logic seems specific to slides where one coordinate changes more than the other, 
        // or a specific input format where the number of steps L is defined by x difference.
        int L = abs(x2 - x1); 

        // Block handles (x1, y1) to (x2, y2) with y decreasing
        if (dy == -1 || dy == 1) { // Based on the original code's logic
            // The original logic seems to assume the steps are diagonal with |dy|=1
            // and L steps are taken, determined by |x2 - x1|. This is unusual but 
            // preserved for functional correctness.
            
            if (y2 < y1) { // Original 'if (dy == -1)' condition
                L = abs(x2 - x1); // Steps based on x difference
                for (int k = 0; k < L; k++) {
                    int x = x1 + dx * k;
                    int y = y1 - k; // y steps by -1
                    grid_slide_ids[{x, y}].push_back(s);
                    next_point_on_slide[{x, y, s}] = {x + dx, y - 1};
                }
                grid_slide_ids[{x2, y2}].push_back(s); // Add end point
            } else { // Original 'else' block, likely for y increasing
                L = abs(y2 - y1); // Steps based on y difference for this case
                dx = (x2 > x1) ? 1 : (x2 < x1) ? -1 : 0;
                
                // This 'else' block's loop logic is highly unusual, reversing the order and direction
                // It seems to be building the slide from (x2, y2) back to (x1, y1)
                for (int k = 0; k < L; k++) {
                    int x = x2 - dx * k;
                    int y = y2 - k;
                    grid_slide_ids[{x, y}].push_back(s);
                    next_point_on_slide[{x, y, s}] = {x - dx, y - 1}; // Next point goes 'backwards' and down
                }
                grid_slide_ids[{x1, y1}].push_back(s); // Add start point
            }
        }
    }

    // Function to find the first point directly below (x, y) that is on a slide (or y=0)
    auto find_fall_destination = [&](int x, int y) -> pair<int, int> { // fall -> find_fall_destination
        for (int yy = y - 1; yy >= 0; yy--) {
            auto it = grid_slide_ids.find({x, yy});
            if (it != grid_slide_ids.end()) return {x, yy};
        }
        return {x, 0}; // Fall to the base (y=0)
    };

    // Main Simulation Loop
    int current_x = start_x; // x -> current_x
    int current_y = start_y; // y -> current_y
    int remaining_energy = initial_energy; // e -> remaining_energy

    // Initial fall check if starting point is not on a slide
    if (grid_slide_ids.find({current_x, current_y}) == grid_slide_ids.end()) {
        auto destination = find_fall_destination(current_x, current_y);
        current_x = destination.first; 
        current_y = destination.second;
    }

    // The simulation continues until a termination condition is met
    while (true) {
        // Termination condition 1: Reached the base
        if (current_y == 0) break;
        
        auto current_point_it = grid_slide_ids.find({current_x, current_y});
        
        // If the current position is not on a slide, fall straight down
        if (current_point_it == grid_slide_ids.end()) {
            auto destination = find_fall_destination(current_x, current_y);
            current_x = destination.first; 
            current_y = destination.second;
            continue;
        }
        
        auto &slide_ids_at_point = current_point_it->second; // ids -> slide_ids_at_point
        
        // Case 1: Only one slide passes through the current point
        if (slide_ids_at_point.size() == 1) {
            int unique_slide_id = slide_ids_at_point[0]; // s -> unique_slide_id
            auto next_point_it = next_point_on_slide.find({current_x, current_y, unique_slide_id});
            
            // If the slide ends here, fall straight down
            if (next_point_it == next_point_on_slide.end()) {
                auto destination = find_fall_destination(current_x, current_y);
                current_x = destination.first; 
                current_y = destination.second;
                continue;
            }
            
            // Termination condition 2: Energy runs out before moving
            if (remaining_energy == 0) break; 
            
            // Consume energy and move along the slide
            remaining_energy--;
            current_x = next_point_it->second.first;
            current_y = next_point_it->second.second;
        
        // Case 2: Multiple slides intersect at the current point
        } else {
            // Cost to stay/pass through the intersection
            long long passage_cost = 1LL * current_x * current_y; // c -> passage_cost
            
            // Collect all possible next destinations from this intersection
            vector<pair<int, pair<int, int>>> valid_next_destinations; // dn -> valid_next_destinations
            valid_next_destinations.reserve(slide_ids_at_point.size());
            for (int slide_id : slide_ids_at_point) {
                auto next_it = next_point_on_slide.find({current_x, current_y, slide_id});
                if (next_it != next_point_on_slide.end()) {
                    valid_next_destinations.push_back({slide_id, next_it->second});
                }
            }
            
            // Sub-case 2a: Not enough energy for passage cost
            if ((long long)remaining_energy <= passage_cost) {
                // If there are valid paths, the simulation breaks (stuck)
                if (!valid_next_destinations.empty()) break;
                
                // Otherwise, fall straight down
                auto destination = find_fall_destination(current_x, current_y);
                current_x = destination.first; 
                current_y = destination.second;
                continue;
            }
            
            // Sub-case 2b: Enough energy for passage cost, but no valid path to take
            remaining_energy -= (int)passage_cost;
            if (valid_next_destinations.empty()) {
                auto destination = find_fall_destination(current_x, current_y);
                current_x = destination.first; 
                current_y = destination.second;
                continue;
            }
            
            // Sub-case 2c: Choose the next slide that leads to the highest y-coordinate
            int best_next_x = 0; // bx -> best_next_x
            int best_next_y = -1; // by -> best_next_y
            for (auto &next_state : valid_next_destinations) {
                int next_x = next_state.second.first; // xx -> next_x
                int next_y = next_state.second.second; // yy -> next_y
                if (next_y > best_next_y) {
                    best_next_y = next_y;
                    best_next_x = next_x;
                }
            }
            
            // Termination condition 3: Energy runs out for the final step
            if (remaining_energy == 0) break;
            
            // Consume final energy unit and move to the best path
            remaining_energy--;
            current_x = best_next_x; 
            current_y = best_next_y;
        }
    }

    // Output the final position
    cout << current_x << " " << current_y;
    return 0;
}