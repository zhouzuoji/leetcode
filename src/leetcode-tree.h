#pragma once
#include <vector>

namespace leetcode {
	namespace btree {
		typedef struct _TreeNode {
			int val;
			struct _TreeNode *left;
			struct _TreeNode *right;
			_TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		} TreeNode;

		int minDepth(TreeNode* root);
		void destroy(TreeNode* root);
		TreeNode* makeTree(const std::vector<int>& data);
		TreeNode* buildTreeFromPreorderAndInorder(const std::vector<int>& preorder, const std::vector<int>& inorder);
		bool isBalanced(TreeNode* root);
	}
}
