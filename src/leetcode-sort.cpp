#include "leetcode-sort.h"

using namespace std;

namespace leetcode {
	namespace sort {
		/* 75. Sort Colors
		Given an array with n objects colored red, white or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white and blue.

		Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

		Note: You are not suppose to use the library's sort function for this problem.

		Example:

		Input: [2,0,2,1,1,0]
		Output: [0,0,1,1,2,2]

		Follow up:

		A rather straight forward solution is a two-pass algorithm using counting sort.
		First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.
		Could you come up with a one-pass algorithm using only constant space?
		*/
		void sortColors(vector<int>& nums) {
			size_t len = nums.size(), i0 = 0, i2 = len;
			for (size_t i = 0; i < i2; ++i) {
				if (nums[i] == 0)
					swap(nums[i], nums[i0++]);
				else if (nums[i] == 2)
					swap(nums[i--], nums[--i2]);
			}
		}

		/* 88. Merge Sorted Array
		Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

		Note:

		The number of elements initialized in nums1 and nums2 are m and n respectively.
		You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2.

		Example:

		Input:
		nums1 = [1,2,3,0,0,0], m = 3
		nums2 = [2,5,6],       n = 3

		Output: [1,2,2,3,5,6]
		*/
		void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
			int last = m + n - 1;  --m; --n;
			while (last >= 0 && m >= 0 && n >= 0) {
				if (nums1[m] > nums2[n])
					nums1[last--] = nums1[m--];
				else
					nums1[last--] = nums2[n--];
			}
			while (n >= 0)
				nums1[last--] = nums2[n--];
		}
	}
}