// leetcode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "leetcode-path.h"
#include "leetcode.h"
#include "leetcode-intervals.h"
#include "leetcode-number.h"
#include "leetcode-linklist.h"
#include "leetcode-permutation.h"
#include "leetcode-text.h"
#include "leetcode-string.h"
#include "leetcode-lcs.h"
#include "leetcode-sort.h"
#include "leetcode-palindrome.h"
#include "leetcode-map.h"
#include "leetcode-tree.h"
#include "leetcode-trie.h"
#include "leetcode-graph.h"
#include "leetcode-baselib.h"
#include "leetcode-expr.h"
#include "leetcode-vip.h"
#include "time.h"
#include "writer.h"
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <type_traits>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <map>

using namespace std;
using namespace leetcode;

ostream& operator<<(ostream& out, const Interval& interval) {
	out << '[' << interval.start << ',' << interval.end << ']';
	return out;
}

int findRadius(vector<int>& houses, vector<int>& heaters) {
	std::sort(houses.begin(), houses.end());
	std::sort(heaters.begin(), heaters.end());
	int ans = 0, nHouses = houses.size(), nHeaters = heaters.size();
	int nextHeater = heaters[0], iHeater = 0, priorHeater = -nextHeater;
	for (int i = 0; i<nHouses; ++i) {
		int pHouse = houses[i];
		while (pHouse>nextHeater) {
			priorHeater = nextHeater;
			if (iHeater + 1<nHeaters)
				nextHeater = heaters[++iHeater];
			else
				nextHeater = 2000000000;
		}
		cout << priorHeater << ", " << pHouse << ", " << nextHeater << endl;
		ans = max(ans, min(pHouse - priorHeater, nextHeater - pHouse));
	}
	return ans;
}

int main() {
	cout << std::boolalpha;
	for (int i = 1; i < 15; ++i) {
		cout << " totalNQueens(" << i << "): " << leetcode::totalNQueens(i) << endl;
	}
	for (int i = 1; i < 5; ++i) {
		cout << " solveNQueens(" << i << "): " << leetcode::solveNQueens(i) << endl;
	}
	leetcode::isMatch("aa", "a");
	leetcode::isMatch("aa", "*");
	leetcode::isMatch("cb", "?a");
	leetcode::isMatch("adceb", "*a*b");
	leetcode::isMatch("acdcb", "a*c?b");
	leetcode::isMatch("b", "*?*?");
	leetcode::isMatch("aaaa", "***a");
	leetcode::isMatch("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb",
		"**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb");
	cout << leetcode::findSubstring("aaaaaaaa", { "aa", "aa", "aa" }) << endl;
	cout << leetcode::maxSubArray({ -2,1,-3,4,-1,2,1,-5,4 }) << endl;
	cout << leetcode::spiralOrder({ {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} }) << endl;
	cout << leetcode::canJump({ 2,3,1,1,4 }) << endl;
	vector<Interval> intervals;
	intervals.push_back(Interval(1, 5));
	//intervals.push_back(Interval(6, 9));
	cout << leetcode::merge(intervals) << endl;
	cout << leetcode::insert(intervals, Interval(2, 3)) << endl;
	cout << leetcode::isNumber(".") << endl;
	cout << leetcode::permutation::getPermutation(3, 3) << endl;
	cout << leetcode::fullJustify({ "This", "is", "an", "example", "of", "text", "justification." }, 16) << endl;
	cout << leetcode::uniquePaths2(3, 3) << endl;
	cout << leetcode::minPathSum({ {1, 3, 1}, {1, 5, 1}, {4, 2, 1} }) << endl;
	cout << leetcode::addBinary("0", "0") << endl;
	cout << leetcode::mySqrt(2147395599) << endl;
	cout << leetcode::climbStairs(3) << endl;
	cout << leetcode::simplifyPath("/home/") << endl;
	cout << leetcode::minDistance("intention", "execution") << endl;
	vector<int> colors({ 2 });
	leetcode::sort::sortColors(colors);
	cout << leetcode::minWindow("ADOBECODEBANC", "ABC") << endl;
	cout << leetcode::maximalRectangle({ {'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'} }) << endl;
	cout << leetcode::maximalRectangle({ {'1', '0'} }) << endl;
	cout << leetcode::maximalRectangle({ { '0', '1' } }) << endl;
	leetcode::isScramble("abb", "bab");
	leetcode::isScramble("ababcbaccbabbcbca", "bbbbbaaaacccccbba");
	cout << leetcode::permutation::grayCode(5) << endl;
	cout << leetcode::numDecodings("12") << endl;
	cout << leetcode::permutation::restoreIpAddresses("1203450") << endl;

	leetcode::linklist::ListNode node1(1), node2(2);
	node1.next = &node2;
	node2.next = &node1;
	cout << linklist::detectCycle(&node1)->val << endl;
	cout << leetcode::checkPerfectNumber(28) << endl;
	cout << leetcode::judgeSquareSum(4) << endl;
	cout << leetcode::palindrome::validPalindrome("deeee") << endl;
	cout << leetcode::findNthDigit(2147483647) << endl;
	//test1();
	vector<int> houses = { 617819336,399125485,156091745,356425228 }, heaters = { 585640194,937186357 };
	cout << findRadius(houses, heaters) << endl;
	cout << leetcode::findUnsortedSubarray({ 2,6,4,8,10,9,15 }) << endl;
	cout << std::is_constructible<int, string>::value << endl;
	cout << std::is_destructible<bool>::value << endl;
	
	cout << leetcode::isInterleave("aabc", "abad", "aabcabad") << endl;
	
	btree::TreeNode* bt = btree::makeTree({ 1,2,2,3,3,3,3,4,4,4,4,4,4,INT_MIN,INT_MIN,5,5 });
	cout << isBalanced(bt) << endl;
	btree::destroy(bt);

	cout << leetcode::graph::findLadders("hot", "dog", {"hot", "dog", "dot"}) << endl;

	{
		vector<vector<char>> t = {{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X'}};
		leetcode::graph::flipSurroundedRegions(t);
		cout << t << endl;
	}
	cout << leetcode::expr::eval("(5)-((16-2*9)-((3-4)-(6+7)))") << endl;
	cout << leetcode::kmp("ll", "hello") << endl;
	cout << leetcode::shortestDistance({ "practice", "makes", "perfect", "coding", "makes" }, "makes", "coding") << endl;
	cout << leetcode::shortestDistance({ "makes", "practice", "makes", "perfect", "coding", "makes" }, "makes", "makes") << endl;
	{
		auto nums = leetcode::findStrobogrammatic(6);
		cout << leetcode::numOfStrobogrammatic(100) << " " << leetcode::numOfStrobogrammatic(0, 5) << " " << nums << " " << nums.size() << endl;
	}
	map<int, int> dict;

	std::nth_element
	cout << numberToWords(1234567891) << endl;
	cout << "press any key to exit..." << endl;
	_getch();
	return 0;
}

