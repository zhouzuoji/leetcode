#pragma once
#include <string>
#include <vector>

namespace leetcode {
	std::string simplifyPath(const std::string &path);
	std::string minWindow(const std::string& s, const std::string& t);
	bool sameChars(const std::string &s1, const std::string &s2);
	bool isScramble(const std::string &s1, const std::string &s2);
	bool wordPattern(const std::string & pattern, const std::string & str);
	bool isInterleave(const std::string& s1, const std::string& s2, const std::string& s3);
	size_t kmp(const std::string& pattern, const std::string& text);
	size_t BoyerMoore(const std::string& pattern, const std::string& text);
}