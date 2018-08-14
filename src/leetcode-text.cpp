#include "leetcode-text.h"

using namespace std;

namespace leetcode {

	/* 68. Text Justification
	Given an array of words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.

	You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.

	Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

	For the last line of text, it should be left justified and no extra space is inserted between words.

	Note:

	A word is defined as a character sequence consisting of non-space characters only.
	Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
	The input array words contains at least one word.

	Example 1:

	Input:
	words = ["This", "is", "an", "example", "of", "text", "justification."]
	maxWidth = 16
	Output:
	[
	"This    is    an",
	"example  of text",
	"justification.  "
	]

	Example 2:

	Input:
	words = ["What","must","be","acknowledgment","shall","be"]
	maxWidth = 16
	Output:
	[
	"What   must   be",
	"acknowledgment  ",
	"shall be        "
	]
	Explanation: Note that the last line is "shall be    " instead of "shall     be",
	because the last line must be left-justified instead of fully-justified.
	Note that the second line is also left-justified becase it contains only one word.

	Example 3:

	Input:
	words = ["Science","is","what","we","understand","well","enough","to","explain",
	"to","a","computer.","Art","is","everything","else","we","do"]
	maxWidth = 20
	Output:
	[
	"Science  is  what we",
	"understand      well",
	"enough to explain to",
	"a  computer.  Art is",
	"everything  else  we",
	"do                  "
	]
	*/
	void fullJustify_AppendLine(vector<string>::const_iterator begin, size_t n, size_t line,
		size_t maxWidth, vector<string>& r) {
		r.push_back(string());
		string &s=r[r.size()-1]; 
		s.reserve(maxWidth);
		if (n == 1) {
			s.append(*begin);
			s.append(maxWidth - begin->size(), '\x20');
		}
		else if (line==maxWidth){
			auto it = begin;
			for (; it != begin + n-1; ++it) {
				s.append(*it);
				s.append(1, '\x20');
			}
			s.append(*it);
		}
		else {
			size_t nSpace = (maxWidth-line)/(n-1);
			size_t x = (maxWidth - line) % (n - 1);
			auto it = begin;
			for (; it != begin+x; ++it) {
				s.append(*it);
				s.append(nSpace+2, '\x20');
			}
			for (; it != begin+n-1; ++it) {
				s.append(*it);
				s.append(nSpace + 1, '\x20');
			}
			s.append(*it);
		}
	}

	vector<string> fullJustify(const vector<string>& words, int _maxWidth) {
		size_t numWords = words.size();
		size_t i1 = 0, i2 = 1, maxWidth=_maxWidth, line=words[0].size(),slen,i,j; 
		vector<string> result;
		while (i2 < numWords) {
			slen = words[i2].size();
			if (line + 1 + slen > maxWidth) {
				fullJustify_AppendLine(words.begin() + i1, i2-i1, line, maxWidth, result);
				i1 = i2++;
				line = slen;
			}
			else {
				line += 1 + slen;
				++i2;
			}
		}

		result.push_back(string());
		string &s = result[result.size() - 1];
		s.reserve(maxWidth);
		for (i=i1; i<i2-1; ++i) {
			s.append(words[i]);
			s.append(1, '\x20');
		}
		s.append(words[i2-1]);
		slen = maxWidth - line;
		if (slen)
			s.append(slen, '\x20');
		return result;
	}
}