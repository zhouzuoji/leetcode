#pragma once
#include <string>
#include <vector>

namespace leetcode{
	namespace graph {
		// https://leetcode.com/problems/word-ladder/description/
		int ladderLength(const std::string& beginWord, const std::string& endWord, const std::vector<std::string>& wordList);
		
		// https://leetcode.com/problems/word-ladder-ii/description/
		std::vector<std::vector<std::string>> findLadders(const std::string& beginWord, 
			const std::string& endWord, 
			const std::vector<std::string>& wordList);

		// https://leetcode.com/problems/surrounded-regions/description/
		void flipSurroundedRegions(std::vector<std::vector<char>>& board);
	}
}
