#include <vector>

using namespace std;

namespace leetcode {
	vector<int> spiralOrder(const vector<vector<int>>& matrix) {
		int m = (int)matrix.size();
		int n = m ? (int)matrix[0].size() : 0;
		vector<int> result(m*n);
		if (!n)
			return result;
		int idx = 0;
		int n1 = 0, n2 = n, m1 = 0, m2 = m, i;
		while (n1<n2 && m1<m2) {
			const vector<int>& row = matrix[m1];
			for (i = n1; i < n2; ++i)
				result[idx++] = row[i];
			for (i = m1 + 1; i < m2; ++i)
				result[idx++] = matrix[i][n2 - 1];
			if (m1+1<m2) {
				const vector<int>& row2 = matrix[m2 - 1];
				for(i=n2-2;i>=n1;--i)
					result[idx++] = row2[i];
			}

			for (i = m2 - 2; i > m1; --i) 
				result[idx++] = matrix[i][m1];
			++n1; --n2; ++m1; --m2;
		}
		return result;
	}

/*
Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

Example:

Input: 3
Output:
[
[ 1, 2, 3 ],
[ 8, 9, 4 ],
[ 7, 6, 5 ]
]
*/
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> result(n);
		int i,value=1, n1 = 0, n2 = n, m1 = 0, m2 = n;
		for (i = 0; i < n; ++i)
			result[i].resize(n);
		if (!n)
			return result;
		while (n1<n2 && m1<m2) {
			vector<int>& row = result[m1];
			for (i = n1; i < n2; ++i)
				row[i]=value++;
			for (i = m1 + 1; i < m2; ++i)
				result[i][n2 - 1]=value++;
			if (m1 + 1<m2) {
				vector<int>& row2 = result[m2 - 1];
				for (i = n2 - 2; i >= n1; --i)
					row2[i]=value++;
			}

			for (i = m2 - 2; i > m1; --i)
				result[i][m1]=value++;
			++n1; --n2; ++m1; --m2;
		}
		return result;
	}
}