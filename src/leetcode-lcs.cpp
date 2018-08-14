#include "leetcode-lcs.h"
#include <algorithm>
#include <iostream>
#include "writer.h"

using namespace std;

namespace leetcode {
	int longestCommonSubSequence(const string &word1, const string &word2) {
		size_t m = word1.size(), n = word2.size(), i, j;
		if (0 == m)
			return n;
		if (0 == n)
			return m;
		++m; ++n;
		std::vector<int> lcs(m*n);
		for (i = 0; i < m; ++i)
			lcs[i*n] = 0;
		for (i = 0; i < n; ++i)
			lcs[i] = 0;
		for (i = 1; i < m; ++i) 
			for (j = 1; j < n; ++j) 
				if (word1[i - 1] == word2[j - 1])
					lcs[i*n + j] = lcs[(i - 1)*n + j - 1] + 1;
				else 
					lcs[i*n + j] = max(lcs[(i - 1)*n + j], lcs[i*n + j - 1]);
		return lcs[(m-1)*n + n-1];
	}

	/* 72. Edit Distance
	Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.

	You have the following 3 operations permitted on a word:

	Insert a character
	Delete a character
	Replace a character

	Example 1:

	Input: word1 = "horse", word2 = "ros"
	Output: 3
	Explanation:
	horse -> rorse (replace 'h' with 'r')
	rorse -> rose (remove 'r')
	rose -> ros (remove 'e')

	Example 2:

	Input: word1 = "intention", word2 = "execution"
	Output: 5
	Explanation:
	intention -> inention (remove 't')
	inention -> enention (replace 'i' with 'e')
	enention -> exention (replace 'n' with 'x')
	exention -> exection (replace 'n' with 'c')
	exection -> execution (insert 'u')
	*/
	int minDistance(const string &word1, const string &word2) {
		size_t m = word1.size(), n = word2.size(), i, j;
		if (0 == m)
			return n;
		if (0 == n)
			return m;
		std::vector<int> lcs(m*n);
		lcs[0] = word1[0]==word2[0]?0:1;
		for (i = 1; i < m; ++i)
			lcs[i*n] = word1[i]==word2[0]?i:lcs[(i-1)*n]+1;
		for (i = 1; i < n; ++i)
			lcs[i] = word1[0] == word2[i] ? i : lcs[i - 1] + 1;
		for (i = 1; i < m; ++i)
			for (j = 1; j < n; ++j)
				if (word1[i] == word2[j])
					lcs[i*n + j] = lcs[(i - 1)*n + j - 1];
				else
					lcs[i*n + j] = min(min(lcs[(i - 1)*n + j], lcs[i*n + j - 1]), lcs[(i - 1)*n + j-1]) + 1;
		return lcs[(m - 1)*n + n - 1];
	}
}