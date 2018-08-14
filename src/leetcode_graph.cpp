#include <vector>
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>

namespace leetcode {
	namespace graph {
		using namespace std;

		size_t wordDistance(const string& s1, const string& s2) {
			size_t ans = 0, len = s1.size();
			for (size_t i = 0; i < len; ++i)
				if (s1[i] != s2[i])
					if (++ans > 1) break;
			return ans;
		}

		int ladderLength(const string& beginWord, const string& endWord, const vector<string>& wordList) {
			auto it = find(wordList.begin(), wordList.end(), endWord);
			if (it == wordList.end())
				return 0;

			const string* pEndWord = &(*it);
			vector<const string*> outer;
			outer.reserve(wordList.size());
			for (const auto &word : wordList)
				if (word != beginWord)
					outer.push_back(&word);
			vector<const string*> inner({ &beginWord });
			size_t i = 0, j = 1, len = 1, wordLen = beginWord.size();
			int ans = 1;
			do {
				++ans;
				for (size_t k = j; k > i && !outer.empty(); --k) {
					const string* s1 = inner[k - 1];
					size_t idx = outer.size();
					do {
						const string* s2 = outer[idx - 1];
						size_t dist = 0;
						for (size_t si = 0; si < wordLen; ++si) {
							if ((*s1)[si] != (*s2)[si])
								if (++dist > 1) break;
						}

						if (dist > 1) continue;

						if (s2 == pEndWord)
							return ans;
						inner.push_back(s2);
						outer.erase(outer.begin() + idx - 1);
						--idx;
					} while (idx > 0);
				}
				i = j; j = inner.size();
			} while (!outer.empty() && i < j);

			return 0;
		}

		void convertLadders(vector<vector<string>>& ans, unordered_map<string, vector<const string*>>& neighborMap,
			vector<string>& path, const string& start) {
			auto &neighbors = neighborMap[start];
			path.push_back(start);
			if (neighbors.empty()) {
				ans.push_back(path);
				auto &back = ans.back();
				reverse(back.begin(), back.end());
			}
			else
				for (auto& neighbor : neighbors)
					convertLadders(ans, neighborMap, path, *neighbor);
			path.pop_back();
		}

		vector<vector<string>> findLadders(const string& beginWord, const string& endWord, const vector<string>& wordList) {
			vector<vector<string>> ans;
			auto it = find(wordList.begin(), wordList.end(), endWord);
			if (it == wordList.end())
				return ans;
			const string* pEndWord = &(*it);
			unordered_map<string, vector<const string*>> neighborMap;

			vector<const string*> outer;
			outer.reserve(wordList.size());
			for (const auto &word : wordList)
				if (beginWord != word)
					outer.push_back(&word);
			vector<const string*> inner({ &beginWord });
			int reached = false;
			size_t i = 0, j = 1, wordLen = beginWord.size();
			do {
				for (size_t k = j; k > i; --k) {
					const string* s1 = inner[k - 1];
					size_t idx = outer.size();
					do {
						const string* s2 = outer[idx - 1];
						size_t dist = 0;
						for (size_t si = 0; si < wordLen; ++si) {
							if ((*s1)[si] != (*s2)[si])
								if (++dist > 1) break;
						}

						if (1 == dist) {
							neighborMap[*s2].push_back(s1);
							if (s2 == pEndWord)
								reached = true;
						};
						--idx;
					} while (idx > 0);
				}

				if (reached)
					break;

				size_t idx = outer.size();
				do {
					const string* s2 = outer[idx - 1];
					if (neighborMap[*s2].size()) {
						inner.push_back(s2);
						outer.erase(outer.begin() + idx - 1);
					}
					--idx;
				} while (idx > 0);

				i = j; j = inner.size();
			} while (!outer.empty() && i < j);

			vector<string> path;
			if (neighborMap[*pEndWord].size())
				convertLadders(ans, neighborMap, path, *pEndWord);
			return ans;
		}

		void dfs_flipSurroundedRegions(vector<vector<char>>& board, unordered_set<size_t>& g, size_t i, size_t j, bool& state) {
			cout << "board[" << i << "," << j << "]: " << board[i][j] << endl;
			if ('X' == board[i][j]) return;
			if (i == 0 || i == board.size() - 1 || j == 0 || j == board[0].size() - 1) {
				state = true; return;
			}
			size_t key = i * board[0].size() + j;
			if (g.count(key) > 0) return;
			g.insert(key);
			dfs_flipSurroundedRegions(board, g, i - 1, j, state);
			dfs_flipSurroundedRegions(board, g, i, j - 1, state);
			dfs_flipSurroundedRegions(board, g, i + 1, j, state);
			dfs_flipSurroundedRegions(board, g, i, j + 1, state);
		}

		void floodFill(vector<vector<char>>& board, size_t i, size_t j) {
			if ('*' == board[i][j]) {
				board[i][j] = 'O';
				if (i > 0)
					floodFill(board, i - 1, j);
				if (i + 1 < board.size())
					floodFill(board, i + 1, j);
				if (j > 0)
					floodFill(board, i, j - 1);
				if (j + 1 < board[0].size())
					floodFill(board, i, j + 1);
			}
		}

		void flipSurroundedRegions(vector<vector<char>>& board) {
			size_t nRow = board.size(), nCol = nRow ? board[0].size() : 0;
			if (nCol<=2 || nRow<=2) return;
			for (size_t i = 0; i < nRow; ++i)
				for (size_t j = 0; j < nCol; ++j)
					if ('O' == board[i][j])
						board[i][j] = '*';

			for (size_t i = 0; i < nCol; ++i) {
				floodFill(board, 0, i);
				floodFill(board, nRow-1, i);
			}

			for (size_t i = 1; i < nRow - 1; ++i) {
				floodFill(board, i, 0);
				floodFill(board, i, nCol-1);
			}

			for (size_t i = 1; i < nRow - 1; ++i)
				for (size_t j = 1; j < nCol - 1; ++j)
					if ('*' == board[i][j])
						board[i][j] = 'X';
		}
	}
}