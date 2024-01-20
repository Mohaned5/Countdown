#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
#include <sstream>
#include <vector>

std::string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

/* Stores solutions to Countdown numbers problems: a 
string containing an RPN numeric expression, and an int
containing the value that expression evaluates to. */
class CountdownSolution {
  
private:
    std::string solution;
    int value;
    
public:
    
    CountdownSolution() : solution(), value(0) {}
    CountdownSolution(const std::string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }
    
    const std::string & getSolution() const {
        return solution;
    }
    
    int getValue() const {
        return value;
    }
    
};


std::vector<std::vector<int>> combinations;

double calculate(double a, double b, std::string oprtr)
{
    if (oprtr == "+"){
        return a + b;
    }
    else if (oprtr == "-"){
        return a - b;
    }
    else if (oprtr == "*"){
        return a * b;
    }
    else if (oprtr == "/"){
        return a / b;
    }
    return 0;


}

/*  Takes a `string` containing a mathematical expression written in
Reverse Polish Notation (RPN) and returns the result of that expression 
as an `double`. */
int evaluateCountdown(std::string expression)
{
    std::vector<double> expressionList;
    std::stringstream expressionStream(expression);
    std::string temp;
    double a, b;
    while (std::getline(expressionStream, temp, ' ')){
        if (temp == "+" || temp == "-" || temp == "/" || temp == "*"){
            b = expressionList.back();
            expressionList.pop_back();
            a = expressionList.back();
            expressionList.pop_back();
            expressionList.push_back(calculate(a, b, temp));
        }
        else{
            expressionList.push_back(stod(temp));
        }
    }
    return expressionList.back();
}

void recursiveCombos(std::vector<int> numbers, std::vector<int> combo, int start, int end, int index, int size);

void storeCombinations(std::vector<int> numbers, int size){
    std::vector<int> combo;
    recursiveCombos(numbers, combo, 0, size - 1, 0, size);
}

void recursiveCombos(std::vector<int> numbers, std::vector<int> combo, int start, int end, int index, int size)
{
    if(index == size){
        combinations.push_back(combo);
        return;
    }

    for (int i = start; i <= end && end - i + 1 >= size - index; i++){
        combo.push_back(numbers[i]);
    }
}


CountdownSolution best;  
int closestVal;

void findSolution(std::vector<int> remainingNums, std::string expression, int cur, int target, bool isFirst) {
    if (std::abs(target - cur) < std::abs(target - best.getValue())) {
        best = CountdownSolution(expression, cur);
    }
    if (remainingNums.empty() || cur == target) {
        return;
    }
    for (size_t i = 0; i < remainingNums.size(); ++i) {
        std::vector<int> newRemainingNums = remainingNums;
        newRemainingNums.erase(newRemainingNums.begin() + i);
        std::stringstream ss;

        if (isFirst) {
            ss << expression << remainingNums[i];
            findSolution(newRemainingNums, ss.str(), cur + remainingNums[i], target, false);
        } else {
            ss << expression << " " << remainingNums[i];
            findSolution(newRemainingNums, ss.str() + " +", cur + remainingNums[i], target, false);
            findSolution(newRemainingNums, ss.str() + " -", cur - remainingNums[i], target, false);
            findSolution(newRemainingNums, ss.str() + " *", cur * remainingNums[i], target, false);
            if (remainingNums[i] != 0 && cur % remainingNums[i] == 0) {
                findSolution(newRemainingNums, ss.str() + " /", cur / remainingNums[i], target, false);
            }
        }
    }
}

/* Takes a `vector<int>` containing 6 numbers, and a target number; and returns 
a `CountdownSolution` object containing the solution to the problem that gets as 
close as possible to the target. */
CountdownSolution solveCountdownProblem(const std::vector<int>& numbers, int target) {
    closestVal = 99999999;
    best = CountdownSolution("", 0);

    findSolution(numbers, "", 0, target, true);

    if (best.getSolution().empty()) {
        std::string expression = std::to_string(best.getValue());
        return CountdownSolution(expression, best.getValue());
    }
    return best;
}


#endif
