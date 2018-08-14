#pragma once

namespace leetcode {
	namespace linklist {
		typedef struct _ListNode {
			int val;
			struct _ListNode *next;
			_ListNode() : val(-1), next(nullptr) {}
			_ListNode(int x, struct _ListNode* p = nullptr) : val(x), next(p) {}
		} ListNode;

		class MyLinkedList {
		public:
			/** Initialize your data structure here. */
			MyLinkedList();
			~MyLinkedList();
			void clear();
			/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
			int get(int index);
			/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
			void addAtHead(int val);
			/** Append a node of value val to the last element of the linked list. */
			void addAtTail(int val);
			/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
			void addAtIndex(int index, int val);
			/** Delete the index-th node in the linked list, if the index is valid. */
			void deleteAtIndex(int index);
		private:
			ListNode m_head, *m_rear;
		};

		ListNode* rotateRight(ListNode* head, int k);
		ListNode* deleteDuplicates82(ListNode* head);
		ListNode* deleteDuplicates83(ListNode* head);
		ListNode* partition(ListNode* head, int x);
		ListNode* detectCycle(ListNode *head);
		bool isPalindrome(ListNode* head);
		ListNode *getIntersectionNode(ListNode *headA, ListNode *headB);
	}
}