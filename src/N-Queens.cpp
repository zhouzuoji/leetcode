#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace leetcode {
	int totalNQueens(int colMask, int slashMask, int backslashMask, int n, int pos) {
		int i = 0, result = 0, mask = colMask | slashMask | backslashMask, availableMask = (~mask)&((1 << n) - 1);
		while (availableMask) {
			int bit = (~availableMask + 1)&1;
			if (bit) {
				bit = bit << i;
				if (pos == n - 1) 
					++result;
				else
					result += totalNQueens(colMask | bit, (slashMask | bit) << 1, (backslashMask | bit) >> 1, n, pos + 1);
			}
			availableMask >>= 1;
			++i;
		}
		return result;
	}

	int totalNQueens(int n, int col) {
		int mask, slashMask, backslashMask;
		mask = (1 << col);
		slashMask = mask << 1;
		backslashMask = mask >> 1;
		return totalNQueens(mask, slashMask, backslashMask, n, 1);
	}

	int totalNQueens(int n) {
		switch (n) {
		case 0:;
		case 2:;
		case 3:
			return 0;
		case 1:return 1;
		}
		int result = 0;
		for (int i = 0; i < n / 2; ++i) 
			result += totalNQueens(n, i);
		result *= 2;

		if (n % 2) 
			result += totalNQueens(n, n/2);

		return result;
	}

	int solveNQueens(int colMask, int slashMask, int backslashMask, int n, int pos, 
		vector<int>& rows, vector<vector<string>>& solutions) {
		int j,i = 0, result = 0, bit, mask = colMask | slashMask | backslashMask, availableMask = (~mask)&((1 << n) - 1);
		while (availableMask) {
			int bit = (~availableMask + 1) & 1;
			if (bit) {
				rows[pos] = i;
				bit = bit << i;
				if (pos == n - 1) {
					++result;
					vector<string> strs(n);
					for (j = 0; j < n; ++j) {
						string& s = strs[j];
						s.assign(n, '.');
						s[rows[j]] = 'Q';
					}
					solutions.push_back(strs);
				}
				else 
					result += solveNQueens(colMask | bit, (slashMask | bit) << 1, (backslashMask | bit) >> 1, 
						n, pos + 1, rows, solutions);
			}
			availableMask >>= 1;
			++i;
		}
		return result;
	}

	int solveNQueens(int n, int col, vector<vector<string>>& solutions) {
		int mask, slashMask, backslashMask;
		vector<int> rows(n);
		mask = (1 << col);
		rows[0] = col;
		slashMask = mask << 1;
		backslashMask = mask >> 1;
		return solveNQueens(mask, slashMask, backslashMask, n, 1, rows, solutions);
	}

	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> result;
		switch (n) {
		case 1:  result.push_back(vector<string>({"Q"}));
		case 0:;
		case 2:;
		case 3:
			return result;
		default:
			break;
		}
		for (int i = 0; i < n; ++i)
			solveNQueens(n, i, result);
		return result;
	}
}