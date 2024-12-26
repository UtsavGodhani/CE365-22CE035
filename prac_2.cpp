#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;

struct Transition {
    int from;
    char input;
    int to;
};

bool validateString(
    const set<int> &states,
    const set<char> &inputSymbols,
    int startState,
    const set<int> &acceptingStates,
    const map<pair<int, char>, int> &transitions,
    const string &inputString
) {
    int currentState = startState;

    for (char c : inputString) {
        if (inputSymbols.find(c) == inputSymbols.end()) {
            return false;
        }

        auto transition = transitions.find({currentState, c});
        if (transition == transitions.end()) {
            return false;
        }

        currentState = transition->second;
    }

    return acceptingStates.find(currentState) != acceptingStates.end();
}

int main() {
    set<int> states;
    set<char> inputSymbols;
    int startState;
    set<int> acceptingStates;
    map<pair<int, char>, int> transitions;

    int numStates;
    cout << "Enter number of states: ";
    cin >> numStates;
    cout << "Enter states (e.g., 1 2 3 ...): ";
    for (int i = 0; i < numStates; i++) {
        int state;
        cin >> state;
        states.insert(state);
    }

    int numInputSymbols;
    cout << "Enter number of input symbols: ";
    cin >> numInputSymbols;
    cout << "Enter input symbols (e.g., a b ...): ";
    for (int i = 0; i < numInputSymbols; i++) {
        char symbol;
        cin >> symbol;
        inputSymbols.insert(symbol);
    }

    cout << "Enter start state: ";
    cin >> startState;

    int numAcceptingStates;
    cout << "Enter number of accepting states: ";
    cin >> numAcceptingStates;
    cout << "Enter accepting states (e.g., 2 3 ...): ";
    for (int i = 0; i < numAcceptingStates; i++) {
        int state;
        cin >> state;
        acceptingStates.insert(state);
    }

    int numTransitions;
    cout << "Enter number of transitions: ";
    cin >> numTransitions;
    cout << "Enter transitions in the format 'from input to' (e.g., 1 a 2):\n";
    for (int i = 0; i < numTransitions; i++) {
        int from, to;
        char input;
        cin >> from >> input >> to;
        transitions[{from, input}] = to;
    }

    while (true) {
        string inputString;
        cout << "Enter input string (or type 'exit' to quit): ";
        cin >> inputString;

        if (inputString == "exit") {
            break;
        }

        if (validateString(states, inputSymbols, startState, acceptingStates, transitions, inputString)) {
            cout << "Valid String" << endl;
        } else {
            cout << "Invalid String" << endl;
        }
    }

    return 0;
}