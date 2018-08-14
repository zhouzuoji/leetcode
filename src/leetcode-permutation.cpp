#include "leetcode-permutation.h"
#include <algorithm>

using namespace std;

namespace leetcode {
	namespace permutation {

		/* 60. Permutation Sequence
		The set [1,2,3,...,n] contains a total of n! unique permutations.

		By listing and labeling all of the permutations in order, we get the following sequence for n = 3:

		"123"
		"132"
		"213"
		"231"
		"312"
		"321"

		Given n and k, return the kth permutation sequence.

		Note:

		Given n will be between 1 and 9 inclusive.
		Given k will be between 1 and n! inclusive.

		Example 1:

		Input: n = 3, k = 3
		Output: "213"

		Example 2:

		Input: n = 4, k = 9
		Output: "2314"
		*/
		string getPermutation(int n, int k) {
			if (1 == n)
				return "1";
			string result, s = "123456789";
			result.resize(9);
			static const int facts[10] = { 1, 1,2,6,24,120,720,720 * 7,720 * 56,720 * 56 * 9 };
			int i, total = n;
			i = 0;
			while (n > 0) {
				int m = (k - 1) / facts[n - 1];
				result[i++] = s[m];
				s.erase(s.begin() + m);
				k = (k - 1) % facts[n - 1] + 1;
				--n;
			}
			return result;
		}

		/* 77. Combinations
		Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

		Example:

		Input: n = 4, k = 2
		Output:
		[
		[2,4],
		[3,4],
		[2,3],
		[1,2],
		[1,3],
		[1,4],
		]
		*/
		void combine(vector<vector<int>>& vv, size_t begin, size_t end, size_t k, vector<int>& v, size_t idx) {
			size_t i;
			if (k == 1) {
				for (i = begin; i <= end; ++i) {
					v[idx] = i;
					vv.push_back(v);
				}
			}
			else {
				for (i = begin; i <= end + 1 - k; ++i) {
					v[idx] = i;
					combine(vv, i + 1, end, k - 1, v, idx + 1);
				}
			}
		}

		void combine(vector<vector<int>> vv, int n, int k) {
			if (k > n || k <= 0 || n <= 0)
				return;
			if (k == n) {
				vv.push_back(vector<int>());
				vector<int> &tmp = vv.back();
				tmp.resize(n);
				for (int i = 0; i < n; ++i)
					tmp[i] = i + 1;
				return;
			}
			vector<int> r(k);
			combine(vv, 1, n, k, r, 0);
		}

		vector<vector<int>> combine(int n, int k) {
			vector<vector<int>> result;
			combine(result, n, k);
			return result;
		}

		/* 78. Subsets
		Given a set of distinct integers, nums, return all possible subsets (the power set).

		Note: The solution set must not contain duplicate subsets.

		Example:

		Input: nums = [1,2,3]
		Output:
		[
		[3],
		[1],
		[2],
		[1,2,3],
		[1,3],
		[2,3],
		[1,2],
		[]
		]
		*/
		void combine(vector<vector<int>>& vv, const vector<int>& nums, size_t begin, size_t k, vector<int>& v, size_t idx) {
			size_t i, end = nums.size();
			if (k == 1) {
				for (i = begin; i < end; ++i) {
					v[idx] = nums[i];
					vv.push_back(v);
				}
			}
			else {
				for (i = begin; i < end + 1 - k; ++i) {
					v[idx] = nums[i];
					combine(vv, nums, i + 1, k - 1, v, idx + 1);
				}
			}
		}

		void combine(vector<vector<int>>& vv, const vector<int>& nums, int k) {
			int n = nums.size();
			if (k > n || k <= 0 || n <= 0)
				return;
			if (k == n) {
				vv.push_back(nums);
				return;
			}
			vector<int> r(k);
			combine(vv, nums, 0, k, r, 0);
		}

		vector<vector<int>> subsets(const vector<int>& nums) {
			vector<vector<int>> result;
			for (size_t i = 1; i <= nums.size(); ++i)
				combine(result, nums, i);
			result.resize(result.size() + 1); // add an empty set
			return result;
		}

		/* 90. Subsets II
		Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

		Note: The solution set must not contain duplicate subsets.

		Example:

		Input: [1,2,2]
		Output:
		[
		[2],
		[1],
		[1,2,2],
		[2,2],
		[1,2],
		[]
		]
		*/
		void combineWithDup(vector<vector<int>>& vv, const vector<int>& nums, size_t begin, size_t k, vector<int>& v, size_t idx) {
			size_t i, end = nums.size();
			if (k == 1) {
				for (i = begin; i < end; ++i) {
					if (i == begin || nums[i] != nums[i-1]) {
						v[idx] = nums[i];
						vv.push_back(v);
					}
				}
			}
			else {
				for (i = begin; i < end + 1 - k; ++i) {
					if (i == begin || nums[i] != nums[i - 1]) {
						v[idx] = nums[i];
						combineWithDup(vv, nums, i + 1, k - 1, v, idx + 1);
					}
				}
			}
		}

		void combineWithDup(vector<vector<int>>& vv, const vector<int>& nums, int k) {
			int n = nums.size();
			if (k > n || k <= 0 || n <= 0)
				return;
			if (k == n) {
				vv.push_back(nums);
				return;
			}
			vector<int> r(k);
			combineWithDup(vv, nums, 0, k, r, 0);
		}

		vector<vector<int>> subsetsWithDup(vector<int>& nums) {
			vector<vector<int>> result;
			sort(nums.begin(), nums.end());
			for (size_t i = 1; i <= nums.size(); ++i)
				combineWithDup(result, nums, i);
			result.resize(result.size() + 1); // add an empty set
			return result;
		}

		/* 89. Gray Code
		The gray code is a binary numeral system where two successive values differ in only one bit.

		Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

		Example 1:

		Input: 2
		Output: [0,1,3,2]
		Explanation:
		00 - 0
		01 - 1
		11 - 3
		10 - 2

		For a given n, a gray code sequence may not be uniquely defined.
		For example, [0,2,3,1] is also a valid gray code sequence.

		00 - 0
		10 - 2
		11 - 3
		01 - 1

		Example 2:

		Input: 0
		Output: [0]
		Explanation: We define the gray code sequence to begin with 0.
		A gray code sequence of n has size = 2n, which for n = 0 the size is 20 = 1.
		Therefore, for n = 0 the gray code sequence is [0].
		*/
		void grayCode(vector<int>& r, int high, int n, int start) {
			if (1 == n) {
				r.push_back(high + start);
				r.push_back(high + (start ? 0 : 1));
				return;
			}
			int b = 1 << (n - 1);
			int high2 = start & b;
			grayCode(r, high + high2, n - 1, start & (b - 1));
			high2 = high2 ? 0 : b;
			grayCode(r, high + high2, n - 1, r.back() & (b - 1));
		}

		vector<int> grayCode(int n) {
			if (0 == n) return { 0 };
			if (1 == n) return { 0, 1 };
			vector<int> result;
			result.reserve(1 << n);
			grayCode(result, 0, n, 0);
			return result;
		}

		/* 93. Restore IP Addresses
		Given a string containing only digits, restore it by returning all possible valid IP address combinations.

		Example:

		Input: "25525511135"
		Output: ["255.255.11.135", "255.255.111.35"]
		*/
		void restoreIpAddresses(vector<string> &ans, string& ip, size_t offset, const char* s, size_t len, size_t remain) {
			size_t max1 = min(len + 1 - remain, (size_t)3), maxRemain = (remain - 1) * 3, min1 = len>maxRemain ? len-maxRemain : 1;
			if (s[0] == '0') {
				if (min1 == 1) {
					ip[offset] = '0';
					if (remain == 1) 
						ans.push_back(ip);
					else {
						ip[offset+1] = '.';
						restoreIpAddresses(ans, ip, offset+2, s+1, len-1, remain - 1);
					}
				}
				return;
			}
			int v=0;
			if (min1 == max1)
				--min1;
			if (1 == min1) {
				v = s[0] - '0';
				ip[offset++]=s[0];
				if (remain > 1) {
					ip[offset] = '.';
					restoreIpAddresses(ans, ip, offset+1, s + 1, len - 1, remain - 1);
				}
			}
			else if (2 == min1) {
				ip[offset++] = s[0];
				ip[offset++] = s[1];
				v = (s[0] - '0') * 10 + s[1] - '0';
				if (remain > 1) {
					ip[offset] = '.';
					restoreIpAddresses(ans, ip, offset+1, s + 2, len - 2, remain - 1);
				}
			}
			for (size_t i = min1; i < max1; ++i) {
				v = v * 10 + s[i] - '0';
				if (v < 256) {
					ip[offset++] = s[i];
					if (remain == 1)
						ans.push_back(ip);
					else {
						ip[offset] = '.';
						restoreIpAddresses(ans, ip, offset + 1, s + i + 1, len - i - 1, remain - 1);
					}
				}
			}
		}

		vector<string> restoreIpAddresses(const string &s) {
			size_t len = s.size();
			if (len < 4 || len>12)
				return {};
			string ip;
			ip.resize(len + 3);
			vector<string> ans;
			restoreIpAddresses(ans, ip, 0, s.data(), len, 4);
			return ans;
		}
	}
}