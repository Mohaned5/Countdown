# Countdown
Countdown game solver

## The Game 
The Countdown numbers game is speciﬁed as follows:
- Players are given six integer numbers and a target integer number

- The six numbers should be combined using the mathematical operators + - * and / in a way
that gets as close as possible to the target number.
-Each number can only be used once at most, but it is okay not to use any given number/s.
-Divisions by zero can be discarded
For instance if the numbers are (100,4,17,9,3,2) and the target is 37, then one way to do is
`(100 / (3 + 2)) + 17)`

## Input
To run this code:
e.g
vector<int> numbers{1,2,3,4,5,6};
CountdownSolution answer = solveCountdownProblem(numbers, 123);
