#include "leetcode-palindrome.h"

using namespace std;

namespace leetcode {
	namespace palindrome {

		bool validPalindrome(const string& s, int i, int j);
		/* 680. Valid Palindrome II
		Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

		Example 1:

		Input: "aba"
		Output: True

		Example 2:

		Input: "abca"
		Output: True
		Explanation: You could delete the character 'c'.

		Note:

		The string will only contain lowercase characters a-z. The maximum length of the string is 50000.
		*/
		bool validPalindrome(const string& s) {
			int len = static_cast<int>(s.size()), i = 0, j = len - 1, i2, j2;
			while (i <= j) {
				if (s[i] == s[j]) {
					++i; --j;
					continue;
				}
				i2 = i; j2 = j - 1;
				while (i2 <= j2) {
					if (s[i2] != s[j2]) break;
					++i2; --j2;
				}
				if (i2 <= j2) {
					i2 = i + 1; j2 = j;
					while (i2 <= j2) {
						if (s[i2] != s[j2]) break;
						++i2; --j2;
					}
				}
				i = i2; j = j2;
				break;
			}
			return i>j;
		}

		bool validPalindrome(const string& s, int i, int j) {
			while (i <= j) {
				if (s[i] == s[j]) {
					++i; --j;
				}
				else
					return false;
			}
			return true;
		}


	} // namespace palindrome
} // namespace leetcode