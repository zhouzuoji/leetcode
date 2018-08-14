#include "leetcode-search.h"
#include <algorithm>

using namespace std;

namespace leetcode {
	/* 33. Search in Rotated Sorted Array
	Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

	(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

	You are given a target value to search. If found in the array return its index, otherwise return -1.

	You may assume no duplicate exists in the array.

	Your algorithm's runtime complexity must be in the order of O(log n).

	Example 1:

	Input: nums = [4,5,6,7,0,1,2], target = 0
	Output: 4

	Example 2:

	Input: nums = [4,5,6,7,0,1,2], target = 3
	Output: -1
	*/
	int search_RotatedSortedArray(const vector<int>& nums, int target) {
		int len = nums.size();
		if (0 == len)
			return -1;
		int i = 0, j = len - 1;
		int n1 = nums[0];
		if (target == n1)
			return 0;
		if (target > n1) {
			while (i <= j) {
				int m = (i + j) / 2;
				int nm = nums[m];
				if (nm == target)
					return m;
				if (nm<n1 || nm>target)
					j = m - 1;
				else
					i = m + 1;
			}
		}
		else {
			while (i <= j) {
				int m = (i + j) / 2;
				int nm = nums[m];
				if (nm == target)
					return m;
				if (nm >= n1 || nm < target)
					i = m + 1;
				else
					j = m - 1;
			}
		}
		return -1;
	}

	/* 81. Search in Rotated Sorted Array II
	Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

	(i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).

	You are given a target value to search. If found in the array return true, otherwise return false.

	Example 1:

	Input: nums = [2,5,6,0,0,1,2], target = 0
	Output: true

	Example 2:

	Input: nums = [2,5,6,0,0,1,2], target = 3
	Output: false

	Follow up:

	This is a follow up problem to Search in Rotated Sorted Array, where nums may contain duplicates.
	Would this affect the run-time complexity? How and why?
	*/
	int search_RotatedSortedDuplicateArray(const vector<int>& nums, int target) {
		int len = nums.size(), i = 0, j = len - 1;
		if (0 == len)
			return -1;
		int n1 = nums[0];
		if (target == n1)
			return 0;
		while (nums[j] == n1) --j;
		if (target > n1) {
			while (i <= j) {
				int m = (i + j) / 2;
				int nm = nums[m];
				if (nm == target)
					return m;
				if (nm<n1 || nm>target)
					j = m - 1;
				else
					i = m + 1;
			}
		}
		else {
			while (i <= j) {
				int m = (i + j) / 2;
				int nm = nums[m];
				if (nm == target)
					return m;
				if (nm >= n1 || nm < target)
					i = m + 1;
				else
					j = m - 1;
			}
		}
		return -1;
	}
}