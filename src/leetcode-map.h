#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>

namespace leetcode {
	class MyHashMap {
	private:
		class HashSlot {
		public:
			int val;
			int key;
			HashSlot* next;
			HashSlot() : next(nullptr) {}
			~HashSlot() {
				if (next)
					delete next;
			}
		};
	public:
		/** Initialize your data structure here. */
		MyHashMap() : m_size(0) {
			m_slots.resize(10949);
			for (size_t i = 0; i < m_slots.size(); ++i)
				m_slots[i].key = i + 1;
		}

		HashSlot* find(int key, bool create=false) {
			size_t idx = (size_t)key % m_slots.size();
			HashSlot& slot = m_slots[idx];
			if (slot.key == key)
				return &slot;

			if ((size_t)slot.key % m_slots.size() != idx) {
				if (!create)
					return nullptr;
				slot.key = key;
				++m_size;
				return &slot;
			}

			HashSlot* p = slot.next;
			while (p) {
				if (p->key == key)
					return p;
				p = p->next;
			}

			if (!create)
				return nullptr;

			p = new HashSlot();
			p->key = key;
			p->next = slot.next;
			slot.next = p;
			++m_size;
			return p;
		}

		/** value will always be non-negative. */
		void put(int key, int value) {
			HashSlot* p = find(key, true);
			p->val = value;
		}

		/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
		int get(int key) {
			HashSlot* p = find(key, false);
			return p ? p->val : -1;
		}

		/** Removes the mapping of the specified value key if this map contains a mapping for the key */
		void remove(int key) {
			size_t idx = (size_t)key % m_slots.size();
			HashSlot& slot = m_slots[idx];
			if ((size_t)slot.key % m_slots.size() != idx)
				return;
			
			if (slot.key == key) {
				HashSlot* p = slot.next;
				if (p) {
					slot.key = p->key;
					slot.val = p->val;
					slot.next = p->next;
					delete p;
				}
				else 
					slot.key = idx + 1;
				--m_size;
				return;
			}

			HashSlot *prior = &slot, *cur = slot.next;
			while (cur) {
				if (cur->key == key) {
					prior->next = cur->next;
					delete cur;
					--m_size;
					return;
				}
				prior = cur;
				cur = cur->next;
			}
		}

		static size_t suitableCapacity(size_t elementCount) {
			static const size_t PRIME_TABLE[] = { 17, 37, 79, 163, 331, 673, 1361, 2729, 5471, 10949, 21911, 43853, 87719,
				175447, 350899, 701819, 1403641, 2807303, 5614657, 11229331, 22458671, 44917381, 89834777, 179669557,
				359339171, 718678369, 1437356741, 2147483647 };
			size_t cnt = (elementCount * 3) / 2;
			for (size_t i = 0; i < sizeof(PRIME_TABLE) / sizeof(PRIME_TABLE[0]); ++i) {
				if (PRIME_TABLE[i] > cnt) {
					cnt = PRIME_TABLE[i];
					break;
				}
			}
			return cnt;
		}
	private:
		std::vector<HashSlot> m_slots;
		size_t m_size;
	};
}
