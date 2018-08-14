#pragma once
#include <vector>
#include <string>

namespace leetcode {
	using namespace std;
	int totalNQueens(int n);
	vector<vector<string>> solveNQueens(int n);
	bool isMatch(const std::string& s, const std::string& p);
	vector<int> findSubstring(const string& s, const vector<string>& words);
	int maxSubArray(const vector<int>& nums);
	vector<int> spiralOrder(const vector<vector<int>>& matrix);
	bool canJump(const std::vector<int>& nums);
}