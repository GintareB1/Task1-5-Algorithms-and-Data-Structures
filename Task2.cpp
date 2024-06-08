#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
string result;

bool backtrack(int index, int target, string expression, int eval, int prevOperand, char prevOperator) {
    if (index == numbers.size()) {
        if (eval == target) {
            result = expression + " = " + to_string(target);
            return true;
        }
        return false;
    }

    // Adding
    if (backtrack(index + 1, target, expression + "+" + to_string(numbers[index]), eval + numbers[index], numbers[index], '+')) return true;

    // Multiplying
    if (backtrack(index + 1, target, expression + "*" + to_string(numbers[index]), eval * numbers[index], numbers[index], '*')) return true;

    // Concatenating
    int concatenated = prevOperand * 10 + numbers[index];
    if (prevOperator == '+') {
        if (backtrack(index + 1, target, expression.substr(0, expression.size() - 1) + to_string(concatenated), eval - prevOperand + concatenated, concatenated, prevOperator)) return true;
    } else {
        if (backtrack(index + 1, target, expression + to_string(numbers[index]), eval / prevOperand * concatenated, concatenated, prevOperator)) return true;
    }

    return false;
}

int main() {
    int target;
    cout << "Enter the number: ";
    cin >> target;

    if (backtrack(1, target, to_string(numbers[0]), numbers[0], numbers[0], '+')) {
        cout << "Output: " << result << endl;
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
