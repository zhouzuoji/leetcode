#include "leetcode-tree.h"
#include "leetcode-linklist.h"
#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

namespace leetcode {
	namespace btree {
		TreeNode* forceNode(vector<TreeNode*> &nodes, size_t idx,
			const std::vector<int>& data) {
			if (nodes.size() <= idx)
				return nullptr;
			if (!nodes[idx] && data[idx]!=INT_MIN)
				nodes[idx] = new TreeNode(data[idx]);
			return nodes[idx];
		}

		TreeNode* makeTree(const std::vector<int>& data) {
			size_t len = data.size();
			if (!len)
				return nullptr;
			vector<TreeNode*> nodes(len, nullptr);
			for (size_t i = 0; i < len / 2; ++i) {
				forceNode(nodes, i, data);
				if (nodes[i]) {
					nodes[i]->left = forceNode(nodes, i * 2 + 1, data);
					nodes[i]->right = forceNode(nodes, i * 2 + 2, data);
				}
			}
			return nodes[0];
		}

		void destroy(TreeNode* root) {
			if (root->left)
				destroy(root->left);
			if (root->right)
				destroy(root->right);
			delete root;
		}

		int minDepth(TreeNode* root) {
			if (!root) return 0;
			int left = root->left ? minDepth(root->left) : 0;
			int right = root->right ? minDepth(root->right) : 0;
			if (!left)
				return ++right;
			if (!right)
				return ++left;
			return 1 + min(left, right);
		}

		/* 687. Longest Univalue Path
		Given a binary tree, find the length of the longest path where each node in the path has the same value.
		This path may or may not pass through the root.

		Note: The length of path between two nodes is represented by the number of edges between them.

		Example 1:

		Input:

		5
		/ \
		4   5
		/ \   \
		1   1   5

		Output:

		2

		Example 2:

		Input:

		1
		/ \
		4   5
		/ \   \
		4   4   5

		Output:

		2

		Note: The given binary tree has not more than 10000 nodes. The height of the tree is not more than 1000.
		*/
		int longestUnivaluePath(TreeNode* root, int& longest) {
			TreeNode *left = root->left, *right = root->right;
			int pathLeftRoot = 1, pathRightRoot = 1, pathThroughRoot = 1;
			if (left) {
				int x = longestUnivaluePath(left, longest);
				if (left->val == root->val) {
					pathThroughRoot += x;
					pathLeftRoot += x;
				}
			}
			if (right) {
				int x = longestUnivaluePath(right, longest);
				if (right->val == root->val) {
					pathThroughRoot += x;
					pathRightRoot += x;
				}
			}

			if (pathThroughRoot > longest)
				longest = pathThroughRoot;
			return max(pathLeftRoot, pathRightRoot);
		}

		int longestUnivaluePath(TreeNode* root) {
			if (!root)
				return 0;
			int longest = 0;
			longestUnivaluePath(root, longest);
			return longest;
		}

		/* 99. Recover Binary Search Tree
		Two elements of a binary search tree (BST) are swapped by mistake.

		Recover the tree without changing its structure.

		Example 1:

		Input: [1,3,null,null,2]

		  1
		 /
		3
		 \
		  2

		Output: [3,1,null,null,2]

		  3
		 /
		1
		 \
		  2

		Example 2:

		Input: [3,1,4,null,null,2]

			 3
			/ \
		   1   4
		  /
		 2

		Output: [2,1,4,null,null,3]

			 2
			/ \
		   1   4
		  /
		 3

		Follow up:

		A solution using O(n) space is pretty straight forward.
		Could you devise a constant space solution?
		*/
		void recoverTree(TreeNode* root, TreeNode* &prior, TreeNode* &first, TreeNode* &second) {
			if (root->left)
				recoverTree(root->left, prior, first, second);

			if (prior && prior->val >= root->val) {
				if (!first) {
					first = prior;
					second = root;
				}
				else
					second = root;
			}
			prior = root;

			if (root->right)
				recoverTree(root->right, prior, first, second);
		}

		void recoverTree(TreeNode* root) {
			if (!root)
				return;
			TreeNode* prior = nullptr, *first = nullptr, *second = nullptr;
			recoverTree(root, prior, first, second);
			swap(first->val, second->val);
		}

		vector<vector<int>> levelOrder(TreeNode* root) {
			if (!root)
				return {};
			vector<vector<int>> ans;
			queue<TreeNode*> _q1, _q2, *q1 = &_q1, *q2 = &_q2;
			q1->push(root);
			vector<int> row;
			while (!q1->empty()) {
				row.resize(q1->size());
				int i = 0;
				while (!q1->empty()) {
					TreeNode* x = q1->front();
					row[i++] = x->val;
					if (x->left)
						q2->push(x->left);
					if (x->right)
						q2->push(x->right);
					q1->pop();
				}
				ans.push_back(row);
				swap(q1, q2);
			}
			return ans;
		}

		/* 101. Symmetric Tree
		Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

		For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

		1
		/ \
		2   2
		/ \ / \
		3  4 4  3

		But the following [1,2,2,null,3,null,3] is not:

		1
		/ \
		2   2
		\   \
		3    3

		Note:
		Bonus points if you could solve it both recursively and iteratively.
		*/
		bool isSymmetric(TreeNode* left, TreeNode* right) {
			if (!left && !right)
				return true;
			if (!left || !right || left->val != right->val)
				return false;
			return isSymmetric(left->left, right->right)
				&& isSymmetric(left->right, right->left);
		}

		bool isSymmetric(TreeNode* root) {
			return !root || isSymmetric(root->left, root->right);
		}

		// iteratively
		bool isSymmetric2(TreeNode* root) {
			if (!root)
				return true;
			vector<TreeNode*> _lefts1, _lefts2, _rights1, _rights2, *lefts1 = &_lefts1, *lefts2 = &_lefts2,
				*rights1 = &_rights1, *rights2 = &_rights2;
			if (root->left)
				lefts1->push_back(root->left);
			if (root->right)
				rights1->push_back(root->right);
			while (lefts1->size() && lefts1->size() == rights1->size()) {
				size_t n = lefts1->size();
				lefts2->clear();
				rights2->clear();
				for (size_t i = 0; i < n; ++i) {
					TreeNode *left = lefts1->at(i), *right = rights1->at(n - 1 - i);
					if (left->val != right->val)
						return false;
					if (left->left && !right->right)
						return false;
					if (!left->left && right->right)
						return false;
					if (left->right && !right->left)
						return false;
					if (!left->right && right->left)
						return false;
				}
				for (size_t i = 0; i < n; ++i) {
					TreeNode *left = lefts1->at(i), *right = rights1->at(i);
					if (left->left)
						lefts2->push_back(left->left);
					if (left->right)
						lefts2->push_back(left->right);
					if (right->left)
						rights2->push_back(right->left);
					if (right->right)
						rights2->push_back(right->right);
				}
				swap(lefts1, lefts2);
				swap(rights1, rights2);
			}
			return lefts1->size() == rights1->size();
		}

		/* 103. Binary Tree Zigzag Level Order Traversal
		Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

		For example:
		Given binary tree [3,9,20,null,null,15,7],

		3
		/ \
		9  20
		/  \
		15   7

		return its zigzag level order traversal as:

		[
		[3],
		[20,9],
		[15,7]
		]
		*/
		vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
			if (!root)
				return {};
			vector<vector<int>> ans;
			vector<TreeNode*> _parents, _children, *parents = &_parents, *children = &_children;
			bool leftToRight = true;
			parents->push_back(root);
			size_t len = 1;
			while (len) {
				vector<int> r(len);
				children->resize(0);
				for (size_t i = 0; i < len; ++i) {
					TreeNode* node = parents->at(i);
					r[i] = leftToRight?node->val: parents->at(len-1-i)->val;
					if (node->left)
						children->push_back(node->left);
					if (node->right)
						children->push_back(node->right);
				}
				ans.push_back(r);
				leftToRight = !leftToRight;
				swap(parents, children);
				len = parents->size();
			}
			return ans;
		}

		/* 105. Construct Binary Tree from Preorder and Inorder Traversal
		Given preorder and inorder traversal of a tree, construct the binary tree.

		Note:
		You may assume that duplicates do not exist in the tree.

		For example, given

		preorder = [3,9,20,15,7]
		inorder = [9,3,15,20,7]

		Return the following binary tree:

		3
		/ \
		9  20
		/  \
		15   7
		*/
		TreeNode* buildTreeFromPreorderAndInorder(vector<int>::const_iterator preorderBegin, vector<int>::const_iterator preorderEnd,
			vector<int>::const_iterator inorderBegin, vector<int>::const_iterator inorderEnd) {
			if (preorderBegin == preorderEnd)
				return nullptr;
			auto it = find(inorderBegin, inorderEnd, *preorderBegin);
			TreeNode* ans = new TreeNode(*preorderBegin);
			size_t leftLen = it - inorderBegin;
			auto preMiddle = preorderBegin + 1 + leftLen;
			ans->left = buildTreeFromPreorderAndInorder(preorderBegin + 1, preMiddle, inorderBegin, it);
			ans->right = buildTreeFromPreorderAndInorder(preMiddle, preorderEnd, it+1, inorderEnd);
			return ans;
		}

		TreeNode* buildTreeFromPreorderAndInorder(const vector<int>& preorder, const vector<int>& inorder) {
			return buildTreeFromPreorderAndInorder(preorder.cbegin(), preorder.cend(),
				inorder.cbegin(), inorder.cend());
		}

		/* 106. Construct Binary Tree from Inorder and Postorder Traversal
		*/
		TreeNode* buildTreeFromPostorderAndInorder(vector<int>::const_iterator inorderBegin, vector<int>::const_iterator inorderEnd,
			vector<int>::const_iterator postorderBegin, vector<int>::const_iterator postorderEnd) {
			if (postorderBegin == postorderEnd)
				return nullptr;
			auto root = postorderEnd - 1;
			auto it = find(inorderBegin, inorderEnd, *root);
			TreeNode* ans = new TreeNode(*root);
			size_t leftLen = it - inorderBegin;
			auto postMiddle = postorderBegin + leftLen;
			ans->left = buildTreeFromPostorderAndInorder(inorderBegin, it, postorderBegin, postMiddle);
			ans->right = buildTreeFromPostorderAndInorder(it + 1, inorderEnd, postMiddle, root);
			return ans;
		}

		TreeNode* buildTreeFromPostorderAndInorder(const vector<int>& inorder, const vector<int>& postorder) {
			return buildTreeFromPostorderAndInorder(inorder.cbegin(), inorder.cend(),
				postorder.cbegin(), postorder.cend());
		}

		/* 108. Convert Sorted Array to Binary Search Tree */
		TreeNode* sortedArrayToBST(const vector<int>& nums, size_t i, size_t j) {
			if (i>=j)
				return nullptr;
			size_t root = (i + j - 1) / 2;
			TreeNode* ans = new TreeNode(nums[root]);
			ans->left = sortedArrayToBST(nums, i, root);
			ans->right = sortedArrayToBST(nums, root+1, j);
			return ans;
		}

		TreeNode* sortedArrayToBST(const vector<int>& nums) {
			return sortedArrayToBST(nums, 0, nums.size());
		}

		TreeNode* sortedListToBST(linklist::ListNode* head) {
			using namespace linklist;
			ListNode* p1 = head, p2, p3;
			return nullptr;
		}

		/* 110. Balanced Binary Tree
		Given a binary tree, determine if it is height-balanced.

		For this problem, a height-balanced binary tree is defined as:

		a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
		*/
		bool isBalancedBST(TreeNode* root, int& deep, int &shallow) {
			deep = shallow = 0;
			if (!root)
				return true;
			int l1 = 0, l2 = 0, r1 = 0, r2 = 0;
			if (root->left) {
				if (root->val<root->left->val || !isBalancedBST(root->left, l1, l2))
					return false;
			}

			if (root->right) {
				if (root->val>root->right->val || !isBalancedBST(root->right, r1, r2))
					return false;
			}

			deep = max(l2, r2) + 1;
			shallow = min(l1, r1) + 1;
			return shallow + 1 >= deep;
		}

		bool isBalancedBST(TreeNode* root) {
			int deep, shallow;
			return isBalancedBST(root, deep, shallow);
		}
		
		bool isBalanced(TreeNode* root, int& deep, int &shallow) {
			deep = shallow = 0;
			if (!root)
				return true;
			int l1 = 0, l2 = 0, r1 = 0, r2 = 0;
			if (root->left && !isBalanced(root->left, l1, l2)) 
				return false;

			if (root->right && !isBalanced(root->right, r1, r2)) 
				return false;
			deep = max(l1, r1) + 1;
			shallow = min(l2, r2) + 1;
			cout << root->val << "," << deep << "," << shallow << endl;
			return shallow + 1 >= deep;
		}

		bool isBalanced(TreeNode* root) {
			int deep, shallow;
			return isBalanced(root, deep, shallow);
		}

	} //namespace btree
} //namespace leetcode