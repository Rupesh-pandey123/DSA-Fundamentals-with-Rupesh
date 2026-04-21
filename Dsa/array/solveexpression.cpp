#include <bits/stdc++.h>
using namespace std;
vector<string> split_blocks_with_step(const vector<string> &input_lines, int column_step) {
    // maxw -> max_width
    int max_width = 0;
    for (auto &row : input_lines) max_width = max(max_width, (int)row.size());
    
    // norm -> normalized_lines (padded to max_width)
    vector<string> normalized_lines = input_lines;
    for (auto &row : normalized_lines) if ((int)row.size() < max_width) row += string(max_width - row.size(), ' ');

    // cols -> total_cols
    int total_cols = max_width;
    if (total_cols < 3) return {};
    
    // count -> num_blocks
    int num_blocks = (total_cols + (column_step - 3)) / column_step; 
    vector<string> blocks;
    
    for (int i = 0; i < num_blocks; ++i) {
        int start_col = i * column_step; // start -> start_col
        string pattern_9char = ""; // pattern -> pattern_9char
        for (int r = 0; r < 3; ++r) {
            string row = normalized_lines[r];
            // Pad row if block extends past the end
            if (start_col + 3 > (int)row.size()) row += string(start_col + 3 - row.size(), ' ');
            pattern_9char += row.substr(start_col, 3);
        }
        blocks.push_back(pattern_9char);
    }
    return blocks;
}

/**
 * @brief Automatically selects the best column step (3 or 4) based on which yields more non-empty blocks.
 * @param input_lines The 3 rows of the pattern or expression.
 * @param expected_count Optional expected number of symbols.
 * @return The vector of 3x3 blocks using the chosen step.
 */
vector<string> select_optimal_blocks(const vector<string> &input_lines, int expected_count = -1) {
    // b4 -> blocks_step_4, b3 -> blocks_step_3
    vector<string> blocks_step_4 = split_blocks_with_step(input_lines, 4);
    vector<string> blocks_step_3 = split_blocks_with_step(input_lines, 3);

    if (expected_count > 0) {
        if ((int)blocks_step_4.size() == expected_count) return blocks_step_4;
        if ((int)blocks_step_3.size() == expected_count) return blocks_step_3;
    }
    
    // nonempty -> count_non_empty
    auto count_non_empty = [](const vector<string> &v){
        int count = 0; // c -> count
        for (auto &pattern : v) { // p -> pattern
            bool all_space = true; // allzero -> all_space
            for (char ch : pattern) if (ch != ' ') { all_space = false; break; }
            if (!all_space) ++count;
        }
        return count;
    };
    
    // n4 -> non_empty_4, n3 -> non_empty_3
    int non_empty_4 = count_non_empty(blocks_step_4);
    int non_empty_3 = count_non_empty(blocks_step_3);
    
    if (non_empty_4 >= non_empty_3) return blocks_step_4;
    return blocks_step_3;
}

/**
 * @brief Converts a 3x3 block ('*'/' ') into a 9-bit binary string ('1'/'0').
 * @param block The 9-character block string.
 * @return The 9-bit binary string.
 */
string block_to_bit_pattern(const string &block) {
    string bits;
    for (char c : block) bits.push_back(c == ' ' ? '0' : '1');
    return bits; // length 9
}

/**
 * @brief Creates the mapping from 9-bit pattern string to character symbol.
 * @param training_lines The 3 rows of training data.
 * @param symbols The corresponding symbols (e.g., "0", "1", "|", "&").
 * @return map<bit_pattern, symbol>.
 */
map<string,string> create_pattern_map(const vector<string> &training_lines, const vector<string> &symbols) {
    // blocks -> pattern_blocks
    vector<string> pattern_blocks = select_optimal_blocks(training_lines, (int)symbols.size());
    map<string,string> pattern_dict; // dict -> pattern_dict
    for (size_t i = 0; i < symbols.size() && i < pattern_blocks.size(); ++i) {
        string key = block_to_bit_pattern(pattern_blocks[i]);
        pattern_dict[key] = symbols[i];
    }
    return pattern_dict;
}

/**
 * @brief Parses the expression lines into a vector of tokens (number strings and operator symbols).
 * @param expression_lines The 3 rows of the expression.
 * @param all_patterns Combined map of all recognized symbols.
 * @return vector of tokens.
 */
vector<string> parse_expression_tokens(const vector<string> &expression_lines, const map<string,string> &all_patterns) {
    // blocks -> expression_blocks
    vector<string> expression_blocks = select_optimal_blocks(expression_lines, -1);
    vector<string> tokens;
    string number_buffer = ""; // numbuf -> number_buffer
    
    for (auto &block : expression_blocks) { // blk -> block
        string key = block_to_bit_pattern(block);
        auto it = all_patterns.find(key);
        
        if (it != all_patterns.end()) {
            string symbol = it->second; // sym -> symbol
            if (symbol.size() == 1 && isdigit(symbol[0])) {
                number_buffer.push_back(symbol[0]);
            } else {
                if (!number_buffer.empty()) {
                    tokens.push_back(number_buffer);
                    number_buffer.clear();
                }
                tokens.push_back(symbol);
            }
        } else {
            // allzero -> all_zero
            bool all_zero = true;
            for (char c : key) if (c != '0') { all_zero = false; break; }
            if (all_zero) continue;
            continue; // Unrecognized, non-empty pattern is skipped
        }
    }
    if (!number_buffer.empty()) tokens.push_back(number_buffer);
    return tokens;
}

// --- Bitwise Operations ---

/**
 * @brief Performs bitwise OR on two binary strings (right-aligned).
 */
string bitwise_or(const string &bin_a, const string &bin_b) {
    int max_len = max((int)bin_a.size(), (int)bin_b.size()); // L -> max_len
    // A, B, r -> padded_a, padded_b, result
    string padded_a(max_len - (int)bin_a.size(), '0'); padded_a += bin_a;
    string padded_b(max_len - (int)bin_b.size(), '0'); padded_b += bin_b;
    string result; result.reserve(max_len);
    for (int i = 0; i < max_len; ++i) result.push_back((padded_a[i] == '1' || padded_b[i] == '1') ? '1' : '0');
    return result;
}

/**
 * @brief Performs bitwise AND on two binary strings (right-aligned).
 */
string bitwise_and(const string &bin_a, const string &bin_b) {
    int max_len = max((int)bin_a.size(), (int)bin_b.size());
    string padded_a(max_len - (int)bin_a.size(), '0'); padded_a += bin_a;
    string padded_b(max_len - (int)bin_b.size(), '0'); padded_b += bin_b;
    string result; result.reserve(max_len);
    for (int i = 0; i < max_len; ++i) result.push_back((padded_a[i] == '1' && padded_b[i] == '1') ? '1' : '0');
    return result;
}

/**
 * @brief Performs bitwise NOT on a binary string.
 */
string bitwise_not(const string &bin_a) {
    string result; // r -> result
    result.reserve(bin_a.size());
    for (char c : bin_a) result.push_back(c == '1' ? '0' : '1');
    return result;
}

/**
 * @brief Converts a decimal number string into its concatenated binary pattern string.
 */
string number_to_binary_pattern(const string &number_str, const map<string,string> &digit_to_binary) {
    string output_binary; // out -> output_binary
    for (char digit_char : number_str) { // ch -> digit_char
        string key(1, digit_char);
        auto it = digit_to_binary.find(key);
        if (it != digit_to_binary.end()) output_binary += it->second;
        else output_binary += string(9, '0');
    }
    return output_binary;
}

/**
 * @brief Converts a binary pattern string back into a decimal number string.
 */
string binary_pattern_to_number(const string &binary_str, const map<string,string> &binary_to_digit) {
    if (binary_str.empty()) return "0";
    
    // L, rem -> length, remainder
    int length = (int)binary_str.size();
    int remainder = length % 9;
    string padded_binary = binary_str; // s -> padded_binary
    if (remainder != 0) padded_binary = string(9 - remainder, '0') + padded_binary;
    
    string output_number; // out -> output_number
    for (int i = 0; i < (int)padded_binary.size(); i += 9) {
        string chunk = padded_binary.substr(i, 9);
        auto it = binary_to_digit.find(chunk);
        if (it != binary_to_digit.end()) output_number += it->second;
        else output_number += '0';
    }
    
    // p -> first_non_zero
    int first_non_zero = 0;
    while (first_non_zero + 1 < (int)output_number.size() && output_number[first_non_zero] == '0') ++first_non_zero;
    
    return output_number.substr(first_non_zero);
}

/**
 * @brief Evaluates the tokenized expression using shunting-yard (precedence) logic.
 */
string evaluate_tokens(const vector<string> &tokens, const map<string,string> &digit_to_binary) {
    stack<string> value_stack; // val -> value_stack
    stack<string> operator_stack; // op -> operator_stack

    // apply -> apply_operation
    auto apply_operation = [&](const string &oper){
        if (oper == "~") {
            if (value_stack.empty()) { value_stack.push(string(9,'0')); return; }
            string operand_a = value_stack.top(); value_stack.pop(); // a -> operand_a
            value_stack.push(bitwise_not(operand_a));
        } else {
            if (value_stack.empty()) { value_stack.push(string(9,'0')); return; }
            string operand_b = value_stack.top(); value_stack.pop(); // b -> operand_b
            
            // a -> operand_a
            string operand_a = value_stack.empty() ? string(9,'0') : value_stack.top(); 
            if(!value_stack.empty()) value_stack.pop();
            
            if (oper == "|") value_stack.push(bitwise_or(operand_a, operand_b));
            else if (oper == "&") value_stack.push(bitwise_and(operand_a, operand_b));
        }
    };

    // prec -> get_precedence
    auto get_precedence = [&](const string &op)->int { // o -> op
        if (op == "~") return 3;
        if (op == "|") return 2; 
        if (op == "&") return 1;
        return 0;
    };

    for (size_t i = 0; i < tokens.size(); ++i) {
        string token = tokens[i]; // t -> token
        if (token == "(") {
            operator_stack.push(token);
        } else if (token == ")") {
            while (!operator_stack.empty() && operator_stack.top() != "(") {
                string op_token = operator_stack.top(); operator_stack.pop(); // o -> op_token
                apply_operation(op_token);
            }
            if (!operator_stack.empty() && operator_stack.top() == "(") operator_stack.pop();
        } else if (token == "~" || token == "|" || token == "&") {
            while (!operator_stack.empty() && operator_stack.top() != "(" && get_precedence(operator_stack.top()) >= get_precedence(token)) {
                string op_token = operator_stack.top(); operator_stack.pop();
                apply_operation(op_token);
            }
            operator_stack.push(token);
        } else {
            value_stack.push(number_to_binary_pattern(token, digit_to_binary));
        }
    }

    while (!operator_stack.empty()) {
        string op_token = operator_stack.top(); operator_stack.pop(); // o -> op_token
        apply_operation(op_token);
    }

    if (value_stack.empty()) return string();
    return value_stack.top();
}

// --- Main Execution ---

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // all -> all_input_lines
    vector<string> all_input_lines(9);
    for (int i = 0; i < 9; ++i) {
        if (!std::getline(cin, all_input_lines[i])) all_input_lines[i] = "";
    }

    // Separate input sections
    vector<string> digit_training_lines = {all_input_lines[0], all_input_lines[1], all_input_lines[2]}; // digitLines
    vector<string> operator_training_lines = {all_input_lines[3], all_input_lines[4], all_input_lines[5]}; // opLines
    vector<string> expression_lines = {all_input_lines[6], all_input_lines[7], all_input_lines[8]}; // exprLines

    // Define the symbols
    vector<string> digits = {"0","1","2","3","4","5","6","7","8","9"};
    vector<string> operators = {"|","&","~","(",")"}; // ops -> operators

    // Create pattern dictionaries
    auto digit_patterns = create_pattern_map(digit_training_lines, digits); // digitPatterns
    auto operator_patterns = create_pattern_map(operator_training_lines, operators); // opPatterns

    // Prepare combined maps for evaluation
    map<string,string> digit_to_binary; // digitRev
    map<string,string> binary_to_digit; // binary2digit
    for (auto &pair : digit_patterns) { // p -> pair
        binary_to_digit[pair.first] = pair.second;
        digit_to_binary[pair.second] = pair.first;
    }

    map<string,string> all_patterns = digit_patterns; // allPatterns
    for (auto &pair : operator_patterns) all_patterns[pair.first] = pair.second;

    // Parse expression
    auto tokens = parse_expression_tokens(expression_lines, all_patterns); // tokens

    // Evaluate expression
    string result_binary = evaluate_tokens(tokens, digit_to_binary); // resBin

    // Convert final result back to number string
    string final_answer = binary_pattern_to_number(result_binary, binary_to_digit); // ans

    cout << final_answer << "\n";
    return 0;
}