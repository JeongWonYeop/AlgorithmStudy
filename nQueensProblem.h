#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <stdlib.h>
using std::vector;


class QueensProblem
{
	vector<vector<int>> chessTable;
	int numOfQueens = 0;

public:
	QueensProblem(int _numOfQueens);
	void solve();

private:
	bool setQueens(int colIndex);
	bool isPlaceValid(int rowIndex, int colIndex) const;
	void printQueens() const;
};