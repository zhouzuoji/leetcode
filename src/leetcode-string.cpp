#include "leetcode-string.h"
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

namespace leetcode {
	bool sameChars2(const char *s1, const char *s2, size_t len) {
		int cnt1[256] = {0}, cnt2[256] = { 0 };
		unsigned char *s11 = (unsigned char*)s1;
		unsigned char *s22 = (unsigned char*)s2;
		for (size_t i = 0; i < len; ++i) {
			cnt1[s11[i]]++;
			cnt2[s22[i]]++;
		}
		return 0==memcmp(cnt1, cnt2, sizeof(cnt1));
	}

	bool sameChars(const char *s1, const char *s2, size_t len) {
		char s11[64], s22[64];
		switch (len)
		{
		case 0:
			return true;
		case 1:
			return *s1 == *s2;
		case 2:
			return (s1[0] == s2[0] && s1[1] == s2[1]) || (s1[0] == s2[1] && s1[1] == s2[0]);
		default:
			if (len > 64) 
				return sameChars2(s1, s2, len); 
			memcpy(s11, s1, len);
			memcpy(s22, s2, len);
			sort(s11, s11 + len);
			sort(s22, s22 + len);
			return 0==memcmp(s11, s22, len);
		}
	}

	bool sameChars(const std::string &s1, const std::string &s2) {
		if (s1.size() != s2.size())
			return false;
		return sameChars(s1.data(), s2.data(), s1.size());
	}
	/* 71. Simplify Path
	Given an absolute path for a file (Unix-style), simplify it.

	For example,
	path = "/home/", => "/home"
	path = "/a/./b/../../c/", => "/c"

	Corner Cases:

	Did you consider the case where path = "/../"?
	In this case, you should return "/".
	Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
	In this case, you should ignore redundant slashes and return "/home/foo".
	*/
	void appendDir(vector<pair<int, int>> &stk, const std::string& path, int offset, int len) {
		if (path[offset] == '.') {
			if (1 == len)
				return;
			if (2 == len && path[offset + 1] == '.') {
				if (!stk.empty())
					stk.pop_back();
				return;
			}
		}
		stk.push_back(pair<int, int>(offset,len));
	}

	std::string simplifyPath(const std::string& path) {
		vector<pair<int, int>> stk;
		pair<int, int> dir;
		const char* s = path.data();
		int len = path.size(), i = 1, p1=1, rlen;
		while (i < len) {
			if (s[i]=='/') {
				if (i>p1) 
					appendDir(stk, path, p1, i-p1);
				p1 = i + 1;
			}
			++i;
		}

		if (len>p1)
			appendDir(stk, path, p1, len - p1);

		len = stk.size();
		if (!len)
			return "/";
		rlen = 0;
		for (i = 0; i < len; ++i)
			rlen += 1 + stk[i].second;
		string r;
		r.reserve(rlen);
		for (i = 0; i < len; ++i) {
			dir = stk[i];
			r.append(s + dir.first - 1, dir.second + 1);
		}
		return r;
	}

	uint32_t RSHash(const void* buf, int len) {
		uint32_t b = 378551;
		uint32_t a = 63689;
		uint32_t result = 0;
		const uint8_t* str = (const uint8_t*)buf;

		if (len < 0) {
			while (*str) {
				result = result * a + (*str++);
				a *= b;
			}
		}
		else {
			int i;
			for (i = 0; i < len; ++i) {
				result = result * a + str[i];
				a *= b;
			}
		}

		return result;
	}

	typedef pair<const char*, size_t> CharArray;
	struct strhasher {
		inline size_t operator()(const CharArray & key) const noexcept {
			return RSHash(key.first, key.second == (size_t)-1 ? -1 : (int)key.second);
		}
	};

	struct strcmper
	{
		inline bool operator()(const CharArray& _Left, const CharArray& _Right) const {
			return 0 == memcmp(_Left.first, _Right.first, _Left.second);
		}
	};

	vector<int> findSubstring(const string& s, const vector<string>& words) {
		typedef unordered_map<CharArray, int, strhasher, strcmper> WordsMap;
		vector<int> ans;
		size_t i, j, n = s.size(), cnt = words.size(), wl = cnt ? words[0].size() : 0, sublen = wl * cnt;
		if (!cnt || n < sublen) return ans;
		size_t r, rightMax = n - sublen;
		const char* p = s.data();
		size_t left, count;
		int wordCount;
		CharArray str(nullptr, wl), str1(nullptr, wl);
		// init word occurence
		WordsMap dict;
		for (i = 0; i < cnt; ++i) {
			str.first = words[i].data();
			++dict[str];
		}
		WordsMap tdict(dict);
		auto it1 = tdict.begin(), it2 = tdict.end(), it = it1;
		for (it = it1; it != it2; ++it)
			it->second = 0;

		// travel all sub string combinations
		for (i = 0; i < wl; ++i) {
			left = i; count = 0;
			r = rightMax;
			for (it = it1; it != it2; ++it)
				it->second = 0;
			for (j = i; j <= r; j += wl) {
				str.first = p + j;
				// a valid word, accumulate results
				it = dict.find(str);
				if (it == dict.end()) {
					// not a valid word, reset all vars
					for (it = it1; it != it2; ++it)
						it->second = 0;
					count = 0;
					left = j + wl;
					r = rightMax;
					continue;
				}
				wordCount = it->second;
				++count;
				r += wl;
				if (++(tdict[str]) > wordCount) {
					// a more word, advance the window left side possiablly
					while (true) {
						--count;
						r -= wl;
						str1.first = p + left;
						left += wl;
						if (--(tdict[str1]) == wordCount)
							break;
					}
				}
				// come to a result
				if (count == cnt) {
					ans.push_back((int)left);
					// advance one word
					str1.first = p + left;
					--tdict[str1];
					--count;
					r -= wl;
					left += wl;
				}
			}
		}

		return ans;
	}


	/* 76. Minimum Window Substring
	Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

	Example:

	Input: S = "ADOBECODEBANC", T = "ABC"
	Output: "BANC"

	Note:

	If there is no such window in S that covers all characters in T, return the empty string "".
	If there is such window, you are guaranteed that there will always be only one unique minimum window in S.
	*/
	string minWindow(const string& s, const string& t) {
		size_t tlen = t.size(), slen = s.size();
		if (0 == tlen * slen)
			return "";
		size_t i = 0, j = slen, minPos=0, minLen=(size_t)-1, p1, curLen, n=0;
		char c;
		int dict[256] = { 0 }, dict2[256] = { 0 };
		for (i = 0; i < tlen; ++i)
			++dict[t[i]];
		dict[0] = 1;
		i = 0;
		while (!dict[s[i]]) ++i;
		while (j && !dict[s[j - 1]]) --j;
		if (i+tlen > j)
			return "";
		p1 = i;
		while (i+tlen<=j+n) {
			c = s[i];
			if (0 == dict[c]) {
				++i;
				continue;
			}
				
			if (dict2[c]++ < dict[c])
				++n;
			if (n == tlen) {
				while (p1 <= i) {
					c = s[p1];
					if (dict[c] && --dict2[c] < dict[c]) {
						--n;
						curLen = i + 1 - p1;
						if (minLen > curLen) {
							minPos = p1;
							minLen = curLen;
						}
						++p1;
						while (p1 < j && !dict[s[p1]]) ++p1;
						if (p1 > i)
							i=p1-1;
						break;
					}
					++p1;
				}
			}
			++i;
		}

		if (minLen != (size_t)-1)
			return s.substr(minPos, minLen);
		else
			return "";
	}

	/* 87. Scramble String
	Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

	Below is one possible representation of s1 = "great":

	great
	/    \
	gr    eat
	/ \    /  \
	g   r  e   at
	/ \
	a   t

	To scramble the string, we may choose any non-leaf node and swap its two children.

	For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

	rgeat
	/    \
	rg    eat
	/ \    /  \
	r   g  e   at
	/ \
	a   t

	We say that "rgeat" is a scrambled string of "great".

	Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

	rgtae
	/    \
	rg    tae
	/ \    /  \
	r   g  ta  e
	/ \
	t   a

	We say that "rgtae" is a scrambled string of "great".
	Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
	*/

	typedef struct _ScrambleStringRef {
	public:
		inline bool operator==(const struct _ScrambleStringRef& other) const {
			return (other.len == len && other.begin1 == begin1 && other.begin2 == begin2);
		}
		int begin1;
		int begin2;
		int len;	
	} ScrambleStringRef;

	struct ScrambleContextHahser {
		inline size_t operator()(const ScrambleStringRef & key) const noexcept {
			return RSHash(&key, sizeof(key));
		}
	};

	typedef struct _ScrambleContext {
		const char *s1, *s2;
		unordered_map<ScrambleStringRef, bool, ScrambleContextHahser> dp;
	} ScrambleContext;

	/*
	struct strcmper
	{
		inline bool operator()(const pair<const char*, size_t>& _Left, const pair<const char*, size_t>& _Right) const {
			return 0 == memcmp(_Left.first, _Right.first, _Left.second);
		}
	};
	*/
	
	bool isScramble(ScrambleContext& ctx, const char* s1, const char* s2, size_t len) {
		bool result;
		switch (len) {
		case 0: result = true; break;
		case 1: result = *s1 == *s2; break;
		case 2: result = (s1[0] == s2[0] && s1[1] == s2[1]) || (s1[0] == s2[1] && s1[1] == s2[0]); break;
		default:
			ScrambleStringRef key;
			key.begin1 = s1 - ctx.s1;
			key.begin2 = s2 - ctx.s2;
			key.len = len;
			result = false;
			auto it=ctx.dp.find(key);
			if (it != ctx.dp.end())
				result = it->second;
			else {
				result = false;
				if (sameChars(s1, s2, len)) {
					for (size_t i = 1; i < len; ++i) {
						if ((isScramble(ctx, s1, s2, i) && isScramble(ctx, s1 + i, s2 + i, len - i))
							|| (isScramble(ctx, s1, s2 + len - i, i) && isScramble(ctx, s1 + i, s2, len - i))) {
							result = true;
							break;
						}
					}
				}
				ctx.dp[key] = result;
			}		
		}
		//cout << "isScramble(" << string(s1, len) << ", " << string(s2, len) << "): " << result << endl;
		return result;
	}

	bool isScramble(const string &s1, const string &s2) {
		size_t len1 = s2.size(), len2 = s2.size();
		if (len1 != len2)
			return false;
		ScrambleContext ctx;
		ctx.s1 = s1.data();
		ctx.s2 = s2.data();
		return isScramble(ctx, ctx.s1, ctx.s2, len1);
	}

	/* 290. Word Pattern
	Given a pattern and a string str, find if str follows the same pattern.

	Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

	Example 1:

	Input: pattern = "abba", str = "dog cat cat dog"
	Output: true

	Example 2:

	Input:pattern = "abba", str = "dog cat cat fish"
	Output: false

	Example 3:

	Input: pattern = "aaaa", str = "dog cat cat dog"
	Output: false

	Example 4:

	Input: pattern = "abba", str = "dog dog dog dog"
	Output: false

	Notes:
	You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.
	*/
	bool wordPattern(const string & pattern, const string & str) {
		size_t len = pattern.size(), slen = str.size();
		const char*s = str.data();
		vector<bool> meet(256, false);
		unordered_map<string, char> map;
		string word;
		size_t p1 = 0, p2;
		for (size_t i = 0; i < len; ++i) {
			while (p1 < slen && str[p1] < 33) ++p1;
			p2 = p1;
			while (p2 < slen && str[p2]>32) ++p2;
			if (p2 == p1)
				return false;
			word = str.substr(p1, p2 - p1);
			auto it = map.find(word);
			if (it == map.end()) {
				if (meet[pattern[i]])
					return false;
				meet[pattern[i]] = true;
				map[word] = pattern[i];
			}
			else if (it->second != pattern[i])
				return false;
			p1 = p2 + 1;
		}
		while (p1 < slen && str[p1] < 33) ++p1;
		return p1>slen;
	}

	bool wordPattern2(const string & pattern, const string & str) {
		size_t len = pattern.size(), slen=str.size();
		const char*s = str.data();
		pair<int, int> map[256];
		memset(map, 0, sizeof(map));
		size_t p1 = 0, p2;		
		for (size_t i = 0; i < len; ++i) {
			while (p1 < slen && str[p1] < 33) ++p1;
			p2 = p1;
			while (p2 < slen && str[p2]>32) ++p2;
			if (p2 == p1)
				return false;
			pair<int, int>& word = map[pattern[i]];
			if (!word.second) {
				word.first = (int)p1;
				word.second = (int)(p2 - p1);
			}
			else if (p2 - p1 != word.second || memcmp(s + word.first, s + p1, word.second))
					return false;
			p1 = p2 + 1;
		}
		while (p1 < slen && str[p1] < 33) ++p1;
		return p1>slen;
	}

	int repeatedStringMatch(string A, string B) {
		size_t lenA = A.size(), lenB = B.size();
		//if (lenA*lenB == 0)
			//return -1;
		size_t n = (lenB + lenA - 1) / lenA;
		string s; 
		s.reserve((n+1)*lenA);
		for (size_t i = 0; i < n; ++i)
			s.append(A);
		if (s.find(B) != (size_t)-1)
			return n;
		s.append(A);
		if (s.find(B) != (size_t)-1)
			return n + 1;
		return -1;
	}

	/* 97. Interleaving String
	Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

	Example 1:

	Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
	Output: true

	Example 2:

	Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
	Output: false
	*/
	bool isInterleave(const string& s1, const string& s2, const string& s3) {
		size_t len1 = s1.size(), len2 = s2.size(), len3 = s3.size();
		if (len1 + len2 != len3)
			return false;
		if (!len1)
			return s2 == s3;
		if (!len2)
			return s1 == s3;
		vector<vector<bool>> dp(len1 + 1, vector<bool>(len2 + 1, false));
		dp[0][0] = true;
		dp[0][1] = s2[0] == s3[0];
		dp[1][0] = s1[0] == s3[0];
		for (size_t i = 1; i<len3; ++i) {
			size_t minj=i>len2?i-len2:0, maxj = min(i, len1-1);
			for (size_t j = minj; j <= maxj; ++j) 
				if (s1[j] == s3[i] && dp[j][i - j]) {
					dp[j + 1][i - j] = true;
					cout << "dp[" << j + 1 << ", " << i - j << "]: " << true << endl;
				}

			minj = i>len1 ? i - len1 : 0, maxj = min(i, len2 - 1);
			for (size_t j = minj; j <= maxj; ++j)
				if (s2[j] == s3[i] && dp[i-j][j]) {
					dp[i - j][j + 1] = true;
					cout << "dp[" << i-j << ", " << j+1 << "]: " << true << endl;
				}
		}

		return dp[len1][len2];
	}
}