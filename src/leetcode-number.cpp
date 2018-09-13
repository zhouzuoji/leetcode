#include <string>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

namespace leetcode {
	static inline bool isDigit(unsigned int c) {
		return (c - 48u) <= 9;
	}
	bool isNumber(string s) {
		size_t len = s.length(), i = 0, dot = 0, n1, n2, n3, n4;
		while (i < len && s[i] <= 32) ++i;
		if (i == len)
			return false;
		if ('+' == s[i] || '-' == s[i]) {
			++i;
		}
		n2 = n1 = i;
		while (n2 < len && isDigit(s[n2])) ++n2;

		if (n2 == len)
			return (n2 > n1);

		if ('.' == s[n2]) {
			dot = 1;
			++n2;
			while (n2 < len && isDigit(s[n2])) ++n2;
		}

		if (n1 + dot >= n2)
			return false;

		n4 = n2;
		if (n2 < len && 'e' == s[n2]) {
			n3 = n2 + 1;
			if (n3 < len && ('+' == s[n3] || '-' == s[n3]))
				++n3;
			n4 = n3;
			while (n4 < len && isDigit(s[n4])) ++n4;
			if (n4 == n3)
				return false;
		}

		while (n4 < len && s[n4] <= 32) ++n4;
		return n4 == len;
	}

	/* 66. Plus One
	Given a non-empty array of digits representing a non-negative integer, plus one to the integer.

	The digits are stored such that the most significant digit is at the head of the list, and each element in the array contain a single digit.

	You may assume the integer does not contain any leading zero, except the number 0 itself.

	Example 1:

	Input: [1,2,3]
	Output: [1,2,4]
	Explanation: The array represents the integer 123.

	Example 2:

	Input: [4,3,2,1]
	Output: [4,3,2,2]
	Explanation: The array represents the integer 4321.
	*/
	vector<int> plusOne(vector<int>& digits) {
		size_t len = digits.size();
		vector<int> result(digits);
		int cf = 1;
		for (size_t i = len; i > 0; --i) {
			int x = result[i - 1] + cf;
			if (x < 10) {
				cf = 0;
				result[i - 1] = x;
				break;
			}
			result[i - 1] = x - 10;
			cf = 1;
		}
		if (cf)
			result.insert(result.begin(), cf);
		return result;
	}


	/* 67. Add Binary
	Given two binary strings, return their sum (also a binary string).

	The input strings are both non-empty and contains only characters 1 or 0.

	Example 1:

	Input: a = "11", b = "1"
	Output: "100"

	Example 2:

	Input: a = "1010", b = "1011"
	Output: "10101"
	*/
	string addBinary(string a, string b) {
		size_t n1 = a.size(), n2 = b.size();
		const string& s1 = n1 < n2 ? b : a, &s2 = n1 < n2 ? a : b;
		if (n1 < n2)
			swap(n1, n2);
		size_t i, diff = n1 - n2;
		string s(n1 + 1, '0');
		int cf = 0;
		for (i = n1; i > diff; --i) {
			int x = s1[i - 1] + s2[i - diff - 1] + cf - 96;
			if (x >= 2) {
				s[i] = x + 46;
				cf = 1;
			}
			else {
				s[i] = x + 48;
				cf = 0;
			}
		}

		while (i > 0) {
			int x = s1[i - 1] + cf - 48;
			if (x >= 2) {
				s[i] = x + 46;
				cf = 1;
			}
			else {
				s[i] = x + 48;
				cf = 0;
			}
			--i;
		}

		if (cf)
			s[0] = 49;
		else
			s.erase(0, 1);
		return s;
	}

	int mySqrt(int x) {
		if (x < 2)
			return x;
		int i = 0, j = x / 2;
		if (j > 65536)
			j = 65536;
		while (i <= j) {
			int m = i + (j - i) / 2;
			int m2 = m * m;
			//cout << m << ", " << m2 << endl;
			if (m2 == x)
				return m;
			if (m2 >= m && m2 < x)
				i = m + 1;
			else
				j = m - 1;
		}
		return i - 1;
	}

	int largestRectangleArea(const vector<int>& heights) {
		size_t len = heights.size();
		if (!len) return 0;
		if (1 == len) return heights[0];
		int result = 0;
		vector<int> index;
		for (size_t i = 0; i < len; i++) {
			while (!index.empty())
			{
				size_t j = index.back();
				int h = heights[j];
				if (heights[i] > h) break;
				index.pop_back();
				int sidx = index.empty() ? -1 : index.back();
				int x = h * (i - sidx - 1);
				if (x > result)
					result = x;
			}
			index.push_back(i);
		}
		while (!index.empty()) {
			size_t j = index.back();
			int h = heights[j];
			index.pop_back();
			int sidx = index.empty() ? -1 : index.back();
			int x = h * (len - sidx - 1);
			if (x > result)
				result = x;
		}
		return result;
	}

	int largestRectangleArea2(const vector<int>& heights, vector<int>& index) {
		int len = heights.size();
		if (2 == len)
			return heights[0];
		int top = 1, result = 0, h, cur;
		index[0] = 0;
		for (int i = 1; i < len; i++) {
			cur = heights[i];
			while (top) {
				h = heights[index[top - 1]];
				if (cur > h) break;
				--top;
				result = max(result, h * (i - (top ? index[top - 1] : -1) - 1));
			}
			index[top++] = i;
		}
		return result;
	}

	int maximalRectangle(const vector<vector<char>>& matrix) {
		size_t m = matrix.size(), n = m ? matrix[0].size() : 0;
		if (!n) return 0;
		int result = 0;
		vector<int> heights(n + 1, 0), index(n + 1);
		for (size_t i = 0; i < m; ++i) {
			const vector<char>& row = matrix[i];
			for (size_t j = 0; j < n; ++j)
				heights[j] = row[j] == '1' ? heights[j] + 1 : 0;
			result = max(result, largestRectangleArea2(heights, index));
		}
		return result;
	}

	/* 91. Decode Ways
	A message containing letters from A-Z is being encoded to numbers using the following mapping:

	'A' -> 1
	'B' -> 2
	...
	'Z' -> 26

	Given a non-empty string containing only digits, determine the total number of ways to decode it.

	Example 1:

	Input: "12"
	Output: 2
	Explanation: It could be decoded as "AB" (1 2) or "L" (12).

	Example 2:

	Input: "226"
	Output: 3
	Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
	*/
	int numDecodings(vector<int>& dp, const char* p, size_t len) {
		if (0 == len)
			return 1;
		if (dp[len - 1] >= 0)
			return dp[len - 1];
		int result;
		switch (*p) {
		case '0':
			result = 0;
			break;
		case '1':
			if (0 == p[1])
				result = 1;
			else
				result = numDecodings(dp, p + 2, len - 2) + numDecodings(dp, p + 1, len - 1);
			break;
		case '2':
			if (0 == p[1])
				result = 1;
			else if (p[1] > '6')
				result = numDecodings(dp, p + 1, len - 1);
			else
				result = numDecodings(dp, p + 2, len - 2) + numDecodings(dp, p + 1, len - 1);
			break;
		default:
			result = numDecodings(dp, p + 1, len - 1);
			break;
		}
		dp[len - 1] = result;
		return result;
	}

	int numDecodings(const string &s) {
		vector<int> dp(s.size(), -1);
		return numDecodings(dp, s.data(), s.size());
	}

	/* 287. Find the Duplicate Number
	Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

	Example 1:

	Input: [1,3,4,2,2]
	Output: 2

	Example 2:

	Input: [3,1,3,4,2]
	Output: 3

	Note:

	1. You must not modify the array (assume the array is read only).
	2. You must use only constant, O(1) extra space.
	3. Your runtime complexity should be less than O(n2).
	4. There is only one duplicate number in the array, but it could be repeated more than once.
	*/
	int findDuplicate(vector<int>& nums) {
		size_t len = nums.size();
		if (len < 2) return -1;
		if (len == 2)
			return nums[0] == nums[1] ? nums[0] : -1;
		/*
		if we interpret nums such that for each pair of index i and value nums[i],
		the next pair is (nums[i], nums[nums[i]]), we can reduce this problem to cycle detection
		*/
		size_t p1 = 0, p2 = 0;
		do {
			p1 = nums[p1];
			p2 = nums[nums[p2]];
		} while (p1 != p2);

		p2 = 0;
		do {
			p2 = nums[p2];
			p1 = nums[p1];
		} while (p1 != p2);
		return p1;
	}

	/* 238. Product of Array Except Self
	Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal to
	the product of all the elements of nums except nums[i].

	Example:

	Input:  [1,2,3,4]
	Output: [24,12,8,6]

	Note: Please solve it without division and in O(n).

	Follow up:
	Could you solve it with constant space complexity?
	(The output array does not count as extra space for the purpose of space complexity analysis.)
	*/
	vector<int> productExceptSelf(vector<int>& nums) {
		// https://leetcode.com/problems/product-of-array-except-self/discuss/148153/C++-solution-O(n)-without-extra-space-with-explanation
		size_t len = nums.size(), end = len - 1;
		vector<int> ans(len, 1);
		int pre = 1, post = 1;
		for (size_t start = 0; start < len; ++start, --end) {
			ans[start] *= pre;
			ans[end] *= post;
			pre *= nums[start];
			post *= nums[end];
		}
		return ans;
	}

	/* 219. Contains Duplicate II
	Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the absolute difference between i and j is at most k.

	Example 1:

	Input: nums = [1,2,3,1], k = 3
	Output: true

	Example 2:

	Input: nums = [1,0,1,1], k = 1
	Output: true

	Example 3:

	Input: nums = [1,2,3,1,2,3], k = 2
	Output: false
	*/
	bool containsNearbyDuplicate(const vector<int>& nums, int k) {
		size_t len = nums.size();
		for (size_t i = 1; i < len; ++i) {
			size_t j = min(i + k, len);
			int x = nums[i - 1];
			for (size_t k = i + 1; k <= j; ++k)
				if (nums[k - 1] == x)
					return true;
		}
		return false;
	}

	bool containsNearbyDuplicate_hash(const vector<int>& nums, int k) {
		int len = nums.size();
		unordered_map<int, int> dict;
		for (int i = 0; i < len; ++i) {
			auto it = dict.find(nums[i]);
			if (it == dict.end())
				dict[nums[i]] = i;
			else if (it->second + k >= i)
				return true;
			else
				it->second = i;
		}
		return false;
	}

	bool checkPerfectNumber(int num) {
		if (num <= 1)
			return false;
		int sum = 1, factor = 2, n;
		while (true) {
			n = factor * factor;
			if (n > num) break;
			if (n == num) {
				sum += factor;
				break;
			}
			if (num % factor)
				sum += (factor + num / factor);
			++factor;
		}
		return sum == num;
	}

	/* 633. Sum of Square Numbers
	Given a non-negative integer c, your task is to decide whether there're two integers a and b such that a*a + b*b = c.

	Example 1:

	Input: 5
	Output: True
	Explanation: 1 * 1 + 2 * 2 = 5

	Example 2:

	Input: 3
	Output: False
	*/
	bool isSquareOfInteger(int c) {
		int i = 0, j = 46340, m;
		while (i <= j) {
			m = (i + j) / 2;
			int ii = m * m;
			if (ii == c)
				return true;
			if (ii > c)
				j = m - 1;
			else
				i = m + 1;
		}
		return false;
	}

	int isqrt(int c) {
		int i = 0, j = 46340, m;
		while (i <= j) {
			m = (i + j) / 2;
			int ii = m * m;
			if (ii == c)
				return m;
			if (ii > c)
				j = m - 1;
			else
				i = m + 1;
		}
		return j;
	}

	bool judgeSquareSum(int c) {
		int i = 0, j = isqrt(c);
		while (i <= j) {
			int n = i * i + j * j;
			if (n == c)
				return true;
			if (n > c)
				--j;
			else
				++i;
		}
		return false;
	}

	/* 400. Nth Digit
	Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...

	Note:
	n is positive and will fit within the range of a 32-bit signed integer (n < 231).

	Example 1:

	Input:
	3

	Output:
	3

	Example 2:

	Input:
	11

	Output:
	0

	Explanation:
	The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.
	*/
	int findNthDigit(int n) {
		static const int TABLE[10] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
		if (n < 10)
			return n;
		int total = 9, x = 90, bits = 2;
		while (x<900000000 && n>total && n - total > x*bits) {
			total += x * bits;
			x *= 10;
			++bits;
		}

		int val = TABLE[bits - 1] + (n - total - 1) / bits;
		int bit_idx = (n - total - 1) % bits + 1;
		val /= TABLE[bits - bit_idx];
		return val % 10;
	}

	int binarySearch(vector<int>& nums, int i, int j, int target) {
		return 1;
	}
	/* 581. Shortest Unsorted Continuous Subarray
	Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, 
	then the whole array will be sorted in ascending order, too.

	You need to find the shortest such subarray and output its length.

	Example 1:

	Input: [2, 6, 4, 8, 10, 9, 15]
	Output: 5
	Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.

	Note:
		1. Then length of the input array is in range [1, 10,000].
		2. The input array may contain duplicates, so ascending order here means <=.
	*/
	int findUnsortedSubarray(const vector<int>& nums) {
		int len = (int)nums.size(), i = 0, j = len - 1;
		while (i < j && nums[i] <= nums[i + 1]) ++i;
		if (i == j)
			return 0;
		while (nums[j] >= nums[i] && nums[j] >= nums[j - 1]) --j;

		if (i == 0 && j == len - 1)
			return len;

		int minValue = nums[i], maxValue = minValue;
		for (int k = i + 1; k <= j; ++k) {
			minValue = min(minValue, nums[k]);
			maxValue = max(maxValue, nums[k]);
		}

		if (i>0) {
			if (minValue < nums[0])
				i = 0;
			else if (minValue < nums[i - 1]) {
				int i1 = 0, i2 = i - 1;
				while (i1 <= i2) {
					int m = (i1 + i2) / 2;
					if (nums[m] == minValue) {
						++m;
						while (nums[m] == minValue) ++m;
						i1 = m;
						break;
					}
					if (nums[m] < minValue)
						i1 = m + 1;
					else
						i2 = m - 1;
				}
				i = i1;
			}
		}

		if (j < len - 1) {
			if (maxValue > nums[len - 1])
				j = len-1;
			else if (maxValue > nums[j + 1]) {
				int j1 = j+1, j2 = len - 1;
				while (j1 <= j2) {
					int m = (j1 + j2) / 2;
					if (nums[m] == maxValue) {
						--m;
						while (nums[m] == maxValue) --m;
						j1 = m;
						break;
					}
					if (nums[m] < maxValue)
						j1 = m + 1;
					else
						j2 = m - 1;
				}
				j = j1-1;
			}
		}
		return j + 1 - i;
	}

	int longestConsecutive(vector<int>& nums) {
		unordered_map<int, bool> dict;
		dict.reserve(nums.size());
		for (int num : nums)
			dict[num] = true;
		auto end = dict.end(), adj=end;
		int ans = 0;
		for (auto &it : dict) {
			if (!it.second) continue;
			it.second = false;
			int cnt = 1, num = it.first-1;
			while (end != (adj = dict.find(num))) {
				adj->second = false;
				++cnt; --num;
			}
			num = it.first + 1;
			while (end != (adj = dict.find(num))) {
				adj->second = false;
				++cnt; ++num;
			}
			if (cnt > ans)
				ans = cnt;
		}
		return ans;
	}

	static constexpr const char* Ones[19] = { "One ", "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ", "Nine ",
						 "Ten ", "Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen " };
	static constexpr const char* Tens[8] = { "Twenty ", "Thirty ", "Forty ", "Fifty ", "Sixty ", "Seventy ", "Eighty ", "Ninety " };
	static void belowThousand(string& ans, int num) {
		int x = num / 100;
		if (x) {
			num %= 100;
			ans.append(Ones[x - 1]);
			ans.append("Hundred ");
		}
		if (!num)
			return;
		if (num < 20) {
			ans.append(Tens[num - 1]);
			return;
		}
		x = num / 10;
		num %= 10;
		ans.append(Tens[x - 2]);
		if (num)
			ans.append(Ones[num - 1]);
	}

	string numberToWords(int num) {
		string ans;
		int x = num / 1000000000;
		if (x) {
			num %= 1000000000;
			ans.append(Ones[x - 1]);
			ans.append("Billion ");
		}

		x = num / 1000000;
		if (x) {
			num %= 1000000;
			belowThousand(ans, x);
			ans.append("Million ");
		}

		x = num / 1000;
		if (x) {
			num %= 1000;
			belowThousand(ans, x);
			ans.append("Thousand ");
		}

		belowThousand(ans, num);
		ans.pop_back();
		return ans;
	}
}