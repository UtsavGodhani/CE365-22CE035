#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

map<char, set<char>> computeFirstFollow(map<char, set<char>>& follow, set<char>& terminals) {
    map<char, set<char>> first = {
        {'S', {'a', 'b', '(', 'c'}},
        {'A', {'a', '@'}},
        {'B', {'b', '@'}},
        {'C', {'(', 'c'}},
        {'D', {'a', '('}}
    };
    
    follow = {
        {'S', {')', '$'}},
        {'A', {'b', '(', ')', '$'}},
        {'B', {'c', ')', '$'}},
        {'C', {')', '$'}},
        {'D', {')', '$'}}
    };

    terminals = {'a', 'b', 'c', '(', ')', '$'};
    return first;
}

map<char, map<char, string>> constructParsingTable(map<char, set<char>>& first, map<char, set<char>>& follow, set<char>& terminals) {
    map<char, vector<string>> grammar = {
        {'S', {"A B C", "D"}},
        {'A', {"a", "@"}},
        {'B', {"b", "@"}},
        {'C', {"( S )", "c"}},
        {'D', {"A C"}}
    };

    map<char, map<char, string>> table;

    for (auto& rule : grammar) {
        char non_terminal = rule.first;
        for (string production : rule.second) {
            set<char> first_set;
            if (production == "@") {
                first_set = follow[non_terminal];
            } else {
                istringstream iss(production);
                string symbol;
                while (iss >> symbol) {
                    if (terminals.count(symbol[0])) {
                        first_set.insert(symbol[0]);
                        break;
                    }
                    first_set.insert(first[symbol[0]].begin(), first[symbol[0]].end());
                    if (!first[symbol[0]].count('@')) {
                        break;
                    }
                }
            }
            for (char terminal : first_set) {
                if (terminal != '@') {
                    table[non_terminal][terminal] = production;
                }
            }
            if (first_set.count('@')) {
                for (char terminal : follow[non_terminal]) {
                    table[non_terminal][terminal] = production;
                }
            }
        }
    }
    return table;
}

bool isLL1(map<char, map<char, string>>& parsing_table) {
    for (auto& entry : parsing_table) {
        set<char> seen;
        for (auto& rule : entry.second) {
            if (seen.count(rule.first)) {
                return false;
            }
            seen.insert(rule.first);
        }
    }
    return true;
}

string validateString(map<char, map<char, string>>& parsing_table, string input_string) {
    stack<char> parse_stack;
    parse_stack.push('$');
    parse_stack.push('S');
    input_string += '$';
    int i = 0;
    
    while (!parse_stack.empty()) {
        char top = parse_stack.top();
        parse_stack.pop();

        if (top == input_string[i]) {
            i++;
        } else if (parsing_table.count(top)) {
            if (parsing_table[top].count(input_string[i])) {
                string production = parsing_table[top][input_string[i]];
                if (production != "@") {
                    vector<char> symbols;
                    for (int j = production.size() - 1; j >= 0; j--) {
                        if (production[j] != ' ') {
                            symbols.push_back(production[j]);
                        }
                    }
                    for (char symbol : symbols) {
                        parse_stack.push(symbol);
                    }
                }
            } else {
                return "Invalid string";
            }
        } else {
            return "Invalid string";
        }
    }
    return (i == input_string.size()) ? "Valid string" : "Invalid string";
}

int main() {
    map<char, set<char>> follow;
    set<char> terminals;
    map<char, set<char>> first = computeFirstFollow(follow, terminals);
    map<char, map<char, string>> parsing_table = constructParsingTable(first, follow, terminals);
    
    cout << "Predictive Parsing Table:\n";
    for (auto& entry : parsing_table) {
        cout << entry.first << " -> ";
        for (auto& rule : entry.second) {
            cout << "[" << rule.first << " : " << rule.second << "] ";
        }
        cout << endl;
    }
    
    if (isLL1(parsing_table)) {
        cout << "The grammar is LL(1)" << endl;
    } else {
        cout << "The grammar is NOT LL(1)" << endl;
    }
    
    int num_tests;
    cout << "Enter number of test cases: ";
    cin >> num_tests;
    cin.ignore();
    
    for (int i = 0; i < num_tests; i++) {
        string test_string;
        cout << "Enter a string: ";
        getline(cin, test_string);
        cout << validateString(parsing_table, test_string) << endl;
    }
    
    return 0;
}
