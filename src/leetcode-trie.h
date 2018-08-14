#pragma once
#include "stdint.h"
#include <string>
#include <vector>

namespace leetcode {
	typedef std::string string;

	typedef struct _TrieNode {
		struct _TrieNode* firstChild;
		struct _TrieNode* next;
		int ref;
		char data;
		bool isEnd;
	} TrieNode;

	void trie_insert(TrieNode* root, const string &word) {
		if (word.empty()) return;
		TrieNode *parent = root;
		for (char c : word) {
			TrieNode* child = parent->firstChild;
			while (child && child->data != c)
				child = child->next;
			if (!child) {
				child = new TrieNode;
				child->data = c;
				child->ref = 0;
				child->firstChild = nullptr;
				child->isEnd = false;
				child->next = parent->firstChild;
				parent->firstChild = child;
			}
			child->ref++;
			parent = child;
		}
		parent->isEnd = true;
	}

	TrieNode* trie_find(TrieNode* root, const string &prefix, size_t offset=0) {
		size_t len = prefix.size();
		if (offset==len)
			return root;
		TrieNode *p = root;
		for(size_t i=offset; i<len; ++i) {
			p = p->firstChild;
			while (p && p->data != prefix[i])
				p = p->next;
			if (!p) break;
		}
		return p;
	}

	int findWords(std::vector<string> &ans, string& path, TrieNode* trie,
		std::vector<std::vector<char>>& board, int row, int col) {
		int m = board.size(), n = m ? board[0].size() : 0;
		if (row < 0 || row >= m || col < 0 || col >= n) 
			return 0;
		char c = board[row][col];
		if (0 == c) 
			return 0;
		TrieNode* child = trie->firstChild;
		while (child && child->data != c)
			child = child->next;
		if (!child || !child->ref)
			return 0;
		int found = 0;
		path.push_back(c);
		board[row][col] = 0;
		if (child->isEnd) {
			child->isEnd = false;
			ans.push_back(path);
			++found;
		}
		found += findWords(ans, path, child, board, row - 1, col);
		found += findWords(ans, path, child, board, row + 1, col);
		found += findWords(ans, path, child, board, row, col - 1);
		found += findWords(ans, path, child, board, row, col + 1);
		board[row][col] = c;
		path.pop_back();
		child->ref -= found;
		return found;
	}

	std::vector<string> findWords(std::vector<std::vector<char>>& board, std::vector<string>& words) {
		int m = board.size(), n = m ? board[0].size() : 0;
		if (!n) return {};
		TrieNode root;
		root.firstChild = nullptr;
		root.isEnd = false;
		for (const string& word : words)
			trie_insert(&root, word);
		std::vector<string> ans;
		string path;
		for (int row = 0; row < m; ++row) {
			for (int col = 0; col < n; ++col) {
				findWords(ans, path, &root, board, row, col);
				if (ans.size() == words.size())
					return ans;
			}
		}
		return ans;
	}

	class Trie {
	public:
		/** Initialize your data structure here. */
		Trie() {
			m_root.firstChild = nullptr;
		}

		/** Inserts a word into the trie. */
		inline void insert(const string &word) {
			trie_insert(&m_root, word);
		}

		/** Returns if the word is in the trie. */
		bool search(const string &word) {
			TrieNode* p = trie_find(&m_root, word, 0);
			return (p && p->isEnd);
		}

		/** Returns if there is any word in the trie that starts with the given prefix. */
		bool startsWith(const string &prefix) {
			return (trie_find(&m_root, prefix, 0) != nullptr);
		}
	private:
		TrieNode m_root;
	};

	class WordDictionary {
	private:
		bool find(TrieNode* p, const string &prefix, size_t offset) {
			size_t len = prefix.size();
			if (offset == len)
				return p->isEnd;
			p = p->firstChild;
			char c = prefix[offset];
			while (p) {
				if (('.' == c || p->data == c) && find(p, prefix, offset + 1))
					return true;
				p = p->next;
			}
			return false;
		}
	public:
		/** Initialize your data structure here. */
		WordDictionary() {
			m_root.firstChild = nullptr;
			m_root.isEnd = false;
		}

		/** Adds a word into the data structure. */
		inline void addWord(const string & word) {
			trie_insert(&m_root, word);
		}

		/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
		bool search(const string &word) {
			return find(&m_root, word, 0);
		}
	private:
		TrieNode m_root;
	};

} // namespace leetcode