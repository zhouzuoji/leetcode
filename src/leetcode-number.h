#pragma once
#include <string>
#include <vector>

namespace leetcode {
	bool isNumber(std::string s);
	int mySqrt(int x);
	std::vector<int> plusOne(std::vector<int>& digits);
	std::string addBinary(std::string a, std::string b);
	int maximalRectangle(const std::vector<std::vector<char>>& matrix);
	int largestRectangleArea(const std::vector<int>& heights);
	int numDecodings(const std::string &s);
	bool containsNearbyDuplicate(const std::vector<int>& nums, int k);
	bool checkPerfectNumber(int num);
	bool judgeSquareSum(int c);
	int findNthDigit(int n);
	int findUnsortedSubarray(const std::vector<int>& nums);
}