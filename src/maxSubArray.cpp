#include <iostream>
#include <vector>

/*
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum,
	and return its sum.

Example:

Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Follow up:

If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/

using namespace std;

namespace leetcode {
	int maxSubArray(const vector<int>& nums, size_t offset, int addend) {
		if (addend < 0)
			addend = 0;
		size_t len = nums.size();
		int posSum = addend;
		while (offset < len && nums[offset] >= 0)
			posSum += nums[offset++];
		if (offset == len)
			return posSum;
		int negSum = 0;
		while (offset < len && nums[offset] < 0)
			negSum += nums[offset++];
		int next = maxSubArray(nums, offset, posSum + negSum);
		return posSum > next ? posSum : next;
	}

	int maxSubArray(const vector<int>& nums) {
		size_t len = nums.size();
		if (!len) return 0;
		if (1 == len) return nums[0];
		int first = nums[0];
		if (first >= 0)
			return maxSubArray(nums, 1, first);
		size_t i = 1;
		while (i < len && nums[i] < 0) {
			if (nums[i] > first)
				first = nums[i];
			++i;
		}
		if (i == len)
			return first;
		return maxSubArray(nums, i+1, nums[i]);
	}
}