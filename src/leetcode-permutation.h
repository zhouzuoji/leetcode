#pragma once
#include <string>
#include <vector>

namespace leetcode {
	namespace permutation {
		std::string getPermutation(int n, int k);
		std::vector<std::vector<int>> combine(int n, int k);
		std::vector<std::vector<int>> subsets(const std::vector<int>& nums);
		std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums);
		std::vector<int> grayCode(int n);
		std::vector<std::string> restoreIpAddresses(const std::string &s);
	}
}
