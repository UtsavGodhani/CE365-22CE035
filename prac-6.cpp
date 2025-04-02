#include <iostream>
#include <string>
using namespace std;

bool isValid(string str) {
    if (str == "a") return true;
    
    if (str.length() >= 2 && str[0] == '(' && str[str.length()-1] == ')') {
        string inner = str.substr(1, str.length()-2);
        
        int pos = 0;
        string part;
        if(inner.empty()) return false;
        
        while (pos < inner.length()) {
            int parenthesesCount = 0;
            int start = pos;
            
            while (pos < inner.length()) {
                if (inner[pos] == '(') parenthesesCount++;
                if (inner[pos] == ')') parenthesesCount--;
                if (parenthesesCount == 0 && inner[pos] == ',') break;
                pos++;
            }
            
            part = inner.substr(start, pos - start);
            
            if (!isValid(part)) return false;
            
            pos++;
            
            if (pos >= inner.length() && inner[inner.length()-1] == ',') 
                return false;
        }
        return true;
    }
    
    return false;
}

int main() {
    string input;
       
    cout << "\nEnter a string to check: ";
    getline(cin, input);
    
    if (isValid(input)) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }
    
    return 0;
}