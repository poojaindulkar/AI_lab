#include<bits/stdc++.h>
using namespace std;

const int N = 8;

int calcEvaluationFunction(int (&board)[N])
{
	int cnt = 0;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = i+1; j < 8; ++j)
		{
			if(board[i] == board[j])
				++cnt;
			else if(abs(i-j) == abs(board[i]-board[j]))
				++cnt;
		}
	}
	return 28-cnt;			
}

void printBoard(int (&board)[N])
{
	int grid[10][10];
	memset(grid, 0, sizeof grid);
	for(int i = 0; i < 8; ++i)
		grid[ board[i] ][i] = 1;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
			cout << grid[i][j] << " ";
		cout << endl;
	}
	return;
}

void copyBoard(int (&board1)[N], int (&board2)[N])
{
	for(int i = 0; i < 8; ++i)
		board1[i] = board2[i];
}
	
bool hillClimbing(int (&board)[N])
{
	int bestBoard[N], bestValue, boardValue;
	copyBoard(bestBoard, board);
	
	int cnt = 0;
	while(1)
	{
		int currBoard[N], currValue;
		copyBoard(currBoard, board);
		boardValue = bestValue = calcEvaluationFunction(board);
		
		if(bestValue == 28)
		{
			cout << "Reached Global Maxima after " << cnt << " moves" << endl;
			printBoard(bestBoard);
			return 1;
		}
		
		++cnt;		
		for(int i = 0; i < 8; ++i)
		{
			int temp = currBoard[i];
			for(int j = 0; j < 8; ++j)
			{
				if(j == board[i])
					continue;
				currBoard[i] = j;
				currValue = calcEvaluationFunction(currBoard);
				if(currValue > bestValue)
				{
					bestValue = currValue;
					copyBoard(bestBoard, currBoard);
				}
			}
			currBoard[i] = temp;
		}
		if(bestValue <= boardValue)
		{
			cout << "Stucked in Local Maxima after " << cnt << " moves" << endl;
			printBoard(bestBoard);
			return 0;
		}
		copyBoard(board, bestBoard);
	}
}

int main()
{
	//~ freopen("output.txt", "w", stdout);
	srand(time(NULL));
	bool success = 0;
	int cnt = 1, board[N];
	while(1)
	{
		for(int i = 0; i < 8; ++i)
			board[i] = rand()%8;			
	
		cout << "======================== Iteration : " << cnt << endl;
		cout << "Initial Board" << endl;
		printBoard(board);
		success = hillClimbing(board);
		++cnt;
		
		if(success)
			break;
	}
	
	
	return 0;
}
/*
This C++ code implements the N-Queens problem using the Hill Climbing algorithm with random restarts. Let's break down the code and understand its components:

Header inclusion: The code includes the necessary header file <bits/stdc++.h> which includes most of the standard C++ libraries.

Constants and Variables:

const int N = 8;: Defines the size of the chessboard and the number of queens (N-Queens problem).
int board[N];: Represents the current state of the chessboard, where board[i] stores the column index of the queen in the ith row.
Evaluation Function (calcEvaluationFunction):

This function evaluates the current state of the board based on the number of conflicts between queens.
It iterates over all pairs of queens and increments the count (cnt) if they threaten each other.
The evaluation function returns a score indicating the quality of the current state. The higher the score, the better the state.
Print Board Function (printBoard):

This function prints the current state of the chessboard, where 1 represents the presence of a queen and 0 represents an empty cell.
Copy Board Function (copyBoard):

This function copies the contents of one board array to another.
Hill Climbing Algorithm (hillClimbing):

The Hill Climbing algorithm iteratively tries to improve the current state by making small modifications.
It starts with the initial state and iteratively explores neighboring states to find the one with the highest score.
If a better state is found, it becomes the new current state, and the process continues until no improvement can be made.
The function returns true if the global maxima is reached (i.e., a solution is found), otherwise false if it gets stuck in a local maxima.
Main Function:

In the main function, a loop iterates until a solution is found.
In each iteration, a random initial state is generated, and the hill climbing algorithm is applied.
If the hill climbing algorithm successfully finds a solution, the loop terminates.
Random Restart:

If the hill climbing algorithm gets stuck in a local maxima (i.e., it cannot find a better state), the program performs a random restart by generating a new random initial state and trying again.
Overall, this code demonstrates a basic implementation of the N-Queens problem using the Hill Climbing algorithm with random restarts to find a solution.

*/