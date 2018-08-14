#include "leetcode-path.h"
#include <algorithm>
#include <iostream>

using namespace std;

namespace leetcode {
	/* 62. Unique Paths
	A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

	The robot can only move either down or right at any point in time. 
	The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

	How many possible unique paths are there?


	Above is a 7 x 3 grid. How many possible unique paths are there?

	Note: m and n will be at most 100.

	Example 1:

	Input: m = 3, n = 2
	Output: 3
	Explanation:
	From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
	1. Right -> Right -> Down
	2. Right -> Down -> Right
	3. Down -> Right -> Right

	Example 2:

	Input: m = 7, n = 3
	Output: 28
	*/
	int uniquePaths2(int m, int n) {
		vector<int> dp(n);
		int i, j;
		for (i = 0; i < n; ++i)
			dp[i] = 1;
		for (i = 1; i < m; ++i) 
			for (j = n - 2; j >= 0; --j) 
				dp[j] += dp[j + 1];
		return dp[0];
	}

	int uniquePaths(int m, int n) {
		vector<int> dp(m*n);
		int i,j;
		for (i = 0; i < m; ++i) 
			dp[i*n] = 1;
		for (i = 0; i < n; ++i)
			dp[i] = 1;
		for (i = 1; i < m; ++i)
			for (j = 1; j < n; ++j)
				dp[i*n + j] = dp[(i - 1)*n + j] + dp[i*n + j - 1];
		return dp[(m - 1)*n + n - 1];
	}

	/* 63. Unique Paths II
	A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

	The robot can only move either down or right at any point in time. 
	The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

	Now consider if some obstacles are added to the grids. How many unique paths would there be?

	An obstacle and empty space is marked as 1 and 0 respectively in the grid.

	Note: m and n will be at most 100.

	Example 1:

	Input:
	[
	[0,0,0],
	[0,1,0],
	[0,0,0]
	]
	Output: 2
	Explanation:
	There is one obstacle in the middle of the 3x3 grid above.
	There are two ways to reach the bottom-right corner:
	1. Right -> Right -> Down -> Down
	2. Down -> Down -> Right -> Right
	*/
	int uniquePathsWithObstacles(const vector<vector<int>>& obstacleGrid) {
		int i, j, m = obstacleGrid.size(), n = obstacleGrid[0].size();
		const vector<int>& lastRow = obstacleGrid[m - 1];
		vector<int> dp(n);
		dp[n-1] = lastRow[n-1]?0:1;
		for (i = n-2; i >= 0; --i)
			dp[i] = lastRow[i]?0:dp[i+1];		
		for (i=m-2; i>=0; --i) {
			const vector<int>& thisRow = obstacleGrid[i];
			if (thisRow[n-1])
				dp[n-1] = 0;
			for (j = n - 2; j >= 0; --j) {
				if (thisRow[j])
					dp[j] = 0;
				else 
					dp[j] += dp[j + 1];
			}
		}
		return dp[0];
	}

	/* 64. Minimum Path Sum
	Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right 
	which minimizes the sum of all numbers along its path.

	Note: You can only move either down or right at any point in time.

	Example:

	Input:
	[
	[1,3,1],
	[1,5,1],
	[4,2,1]
	]
	Output: 7
	Explanation: Because the path 1¡ú3¡ú1¡ú1¡ú1 minimizes the sum.
	*/
	int minPathSum(const vector<vector<int>>& grid) {
		int i, j, m = grid.size(), n = grid[0].size();
		const vector<int>& lastRow = grid[m - 1];
		vector<int> dp(n);
		dp[n-1] = lastRow[n - 1];
		for (i=n-2; i>=0; --i)
			dp[i]=dp[i+1]+lastRow[i];
		for (i=m-2; i>=0; --i) {
			const vector<int>& thisRow = grid[i];
			dp[n-1] += thisRow[n-1];
			for (j = n - 2; j >= 0; --j) 
				dp[j] = thisRow[j]+min(dp[j+1],dp[j]);
		}
		return dp[0];
	}

	/* 70. Climbing Stairs
	You are climbing a stair case. It takes n steps to reach to the top.

	Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

	Note: Given n will be a positive integer.

	Example 1:

	Input: 2
	Output: 2
	Explanation: There are two ways to climb to the top.
	1. 1 step + 1 step
	2. 2 steps

	Example 2:

	Input: 3
	Output: 3
	Explanation: There are three ways to climb to the top.
	1. 1 step + 1 step + 1 step
	2. 1 step + 2 steps
	3. 2 steps + 1 step
	*/
	int climbStairs(int n) {
		if (n == 1) return 1;
		if (n == 2) return 2;
		vector<int> dp(n);
		dp[0] = 1;
		dp[1] = 2;
		for (int i = 2; i < n; ++i)
			dp[i] = dp[i-1] + dp[i-2];
		return dp[n - 1];
	}
}