#include "leetcode-linklist.h"

namespace leetcode {
	namespace linklist {
		/** Initialize your data structure here. */
		MyLinkedList::MyLinkedList() {
			m_rear = &m_head;
			m_head.next = m_rear;
		}

		MyLinkedList::~MyLinkedList() {
			clear();
		}

		void MyLinkedList::clear() {
			ListNode *p = m_head.next, *cur;
			while (p != &m_head) {
				cur = p;
				p = p->next;
				delete cur;
			}
			m_rear = &m_head;
			m_head.next = m_rear;
		}

		/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
		int MyLinkedList::get(int index) {
			int n = 0;
			ListNode* p = m_head.next;
			while (p != m_rear && n < index) {
				++n;
				p = p->next;
			}

			if (p != &m_head && n == index)
				return p->val;
			else
				return -1;
		}

		/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
		void MyLinkedList::addAtHead(int val) {
			ListNode* p = new ListNode(val, m_head.next);
			m_head.next = p;
			if (m_rear == &m_head)
				m_rear = p;
		}

		/** Append a node of value val to the last element of the linked list. */
		void MyLinkedList::addAtTail(int val) {
			ListNode* p = new ListNode(val, &m_head);
			m_rear->next = p;
			m_rear = p;
		}

		/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
		void MyLinkedList::addAtIndex(int index, int val) {
			int n = 0;
			ListNode *prior = &m_head, *p = m_head.next;
			while (p != &m_head && n < index) {
				++n;
				prior = p;
				p = p->next;
			}

			if (n == index) {
				ListNode* added = new ListNode(val, p);
				prior->next = added;
				if (m_rear == p)
					m_rear = added;
			}
		}

		/** Delete the index-th node in the linked list, if the index is valid. */
		void MyLinkedList::deleteAtIndex(int index) {
			int n = 0;
			ListNode *prior = &m_head, *p = m_head.next;
			while (p != m_rear && n < index) {
				++n;
				prior = p;
				p = p->next;
			}

			if (p != &m_head && n == index) {
				prior->next = p->next;
				if (p == m_rear)
					m_rear = prior;
			}
		}

		int length(ListNode* head) {
			if (!head)
				return 0;
			int result = 1;
			while (head->next) {
				head = head->next;
				++result;
			}
			return result;
		}
		/*
		Given a linked list, rotate the list to the right by k places, where k is non-negative.

		Example 1:

		Input: 1->2->3->4->5->NULL, k = 2
		Output: 4->5->1->2->3->NULL
		Explanation:
		rotate 1 steps to the right: 5->1->2->3->4->NULL
		rotate 2 steps to the right: 4->5->1->2->3->NULL

		Example 2:

		Input: 0->1->2->NULL, k = 4
		Output: 2->0->1->NULL
		Explanation:
		rotate 1 steps to the right: 2->0->1->NULL
		rotate 2 steps to the right: 1->2->0->NULL
		rotate 3 steps to the right: 0->1->2->NULL
		rotate 4 steps to the right: 2->0->1->NULL
		*/
		ListNode* rotateRight(ListNode* head, int k) {
			if (!head || !k) return head;
			ListNode* p = head, *prior = nullptr, *p1 = nullptr, *p2 = nullptr; // p1...p2 are to be moved to head
			int n = 1;
			if (1 == k) {
				p2 = p1 = head;
			}
			else {
				while (p->next) {
					p = p->next;
					if (++n == k) {
						p1 = head;
						p2 = p;
						break;
					}
				}

				if (n < k)
					return rotateRight(head, k%n);
			}

			while (p->next) {
				p2 = p = p->next;
				prior = p1;
				p1 = p1->next;
				++n;
			}

			if (k == n)
				return head;

			prior->next = nullptr;
			p2->next = head;
			return p1;
		}

		/* 83. Remove Duplicates from Sorted List
		Given a sorted linked list, delete all duplicates such that each element appear only once.

		Example 1:

		Input: 1->1->2
		Output: 1->2

		Example 2:

		Input: 1->1->2->3->3
		Output: 1->2->3
		*/
		ListNode* deleteDuplicates83(ListNode* head) {
			ListNode dummy(0);
			ListNode *p = head, *prior = &dummy, *p2, *tmp;
			while (p) {
				p2 = p;
				while (p2->next && p2->next->val == p2->val) {
					tmp = p2;
					p2 = p2->next;
					delete tmp;
				}
				prior->next = p2;
				prior = p2;
				p = p2->next;
			}
			prior->next = nullptr;
			return dummy.next;
		}

		/* 82. Remove Duplicates from Sorted List II
		Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

		Example 1:

		Input: 1->2->3->3->4->4->5
		Output: 1->2->5

		Example 2:

		Input: 1->1->1->2->3
		Output: 2->3
		*/
		ListNode* deleteDuplicates82(ListNode* head) {
			ListNode dummy(0);
			ListNode *p = head, *prior = &dummy, *p2, *tmp;
			while (p) {
				p2 = p;
				while (p2->next && p2->next->val == p2->val) {
					tmp = p2;
					p2 = p2->next;
					delete tmp;
				}
				tmp = p2->next;
				if (p2 == p) {
					prior->next = p2;
					prior = p2;
				}
				else
					delete p2;
				p = tmp;
			}
			prior->next = nullptr;
			return dummy.next;
		}

		/* 86. Partition List
		Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

		You should preserve the original relative order of the nodes in each of the two partitions.

		Example:

		Input: head = 1->4->3->2->5->2, x = 3
		Output: 1->2->2->4->3->5
		*/
		ListNode* partition(ListNode* head, int x) {
			ListNode lt(0), gt(0), *p, *plt = &lt, *pgt = &gt;
			while (head) {
				if (head->val < x) {
					p = head;
					while (p->next && p->next->val < x)
						p = p->next;
					plt->next = head;
					plt = p;
				}
				else {
					p = head;
					while (p->next && p->next->val >= x)
						p = p->next;
					pgt->next = head;
					pgt = p;
				}
				head = p->next;
			}
			pgt->next = nullptr;
			plt->next = gt.next;
			return lt.next;
		}

		/* 92. Reverse Linked List II
		Reverse a linked list from position m to n. Do it in one-pass.

		Note: 1 ¡Ü m ¡Ü n ¡Ü length of list.

		Example:

		Input: 1->2->3->4->5->NULL, m = 2, n = 4
		Output: 1->4->3->2->5->NULL
		*/
		ListNode* reverseBetween(ListNode* head, int m, int n) {
			if (m == n)
				return head;
			int x1 = 1;
			ListNode dummy(0), rvs(0), *pm = head, *pr = &dummy, *p, *pre;
			while (x1 < m - 1) {
				pm = pm->next;
				++x1;
			}
			if (x1 < m) {
				dummy.next = head;
				pr = pm;
				pm = pm->next;
				++x1;
			}
			pre = pm;
			while (x1 < n + 1) {
				p = pm;
				pm = pm->next;
				p->next = rvs.next;
				rvs.next = p;
				++x1;
			}

			pr->next = rvs.next;
			pre->next = pm;
			return dummy.next;
		}

		/* 142. Linked List Cycle II
		Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

		Note: Do not modify the linked list.

		Follow up:
		Can you solve it without using extra space?
		*/
		ListNode* detectCycle(ListNode *head) {
			ListNode *p1 = head, *p2 = head;
			do {
				if (!p2 || !p2->next)
					return nullptr;
				p2 = p2->next->next;
				p1 = p1->next;
			} while (p1 != p2);

			p2 = head;
			while (p1 != p2) {
				p2 = p2->next;
				p1 = p1->next;
			}
			return p1;
		}

		/* 234. Palindrome Linked List
		Given a singly linked list, determine if it is a palindrome.

		Example 1:

		Input: 1->2
		Output: false

		Example 2:

		Input: 1->2->2->1
		Output: true

		Follow up:
		Could you do it in O(n) time and O(1) space?
		*/
		bool isPalindrome(ListNode* head) {
			ListNode rvs(-1), *p1 = head, *p2 = head, *p;
			while (p2) {
				p = p1;
				p1 = p1->next;
				p2 = p2->next;			
				if (p2) {
					p->next = rvs.next;
					rvs.next = p;
					p2 = p2->next;
				}					
			}
			p = p1;
			p2 = rvs.next;
			while (p2 && p2->val == p1->val) {
				p2 = p2->next;
				p1 = p1->next;
			}
			return (!p1);
		}
		
		/* 160. Intersection of Two Linked Lists
		Write a program to find the node at which the intersection of two singly linked lists begins.

		For example, the following two linked lists:

		A:          a1 ¡ú a2
		¨K
		c1 ¡ú c2 ¡ú c3
		¨J
		B:     b1 ¡ú b2 ¡ú b3

		begin to intersect at node c1.

		Notes:

		If the two linked lists have no intersection at all, return null.
		The linked lists must retain their original structure after the function returns.
		You may assume there are no cycles anywhere in the entire linked structure.
		Your code should preferably run in O(n) time and use only O(1) memory.

		Credits:
		Special thanks to @stellari for adding this problem and creating all test cases.
		*/
		ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
			if (!headA || !headB)
				return nullptr;
			int lenA = 0, lenB = 0;
			ListNode *pA = headA, *pB = headB;
			while (pA && pB) {
				if (pA == pB)
					return pA;
				++lenA; ++lenB;
				pA = pA->next;
				pB = pB->next;
			}
			while (pA) {
				++lenA; 
				pA = pA->next;
			}
			while (pB) {
				++lenB;
				pB = pB->next;
			}

			if (lenA == lenB)
				return nullptr;

			pA = headA;
			pB = headB;
			if (lenA > lenB) {
				int n = lenA - lenB;
				while (n > 0) {
					--n;
					pA = pA->next;
				}
			}
			else {
				int n = lenB - lenA;
				while (n > 0) {
					--n;
					pB = pB->next;
				}
			}

			while (pA) {
				if (pA == pB)
					return pA;
				pA = pA->next;
				pB = pB->next;
			}
			return nullptr;
		}
	} // namespace linklist
} // namespace leetcode