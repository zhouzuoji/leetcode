#pragma once

#include "stdint.h"

namespace leetcode {
	class bitset {
	public:
		bitset(size_t nBits) : m_size(nBits) {
			if (nBits > sizeof(m_buf) * 8)
				m_bits = new uint32_t[(nBits + sizeof(*m_bits) * 8 - 1) / (sizeof(*m_bits) * 8)];
			else
				m_bits = m_buf;
		}

		~bitset() {
			if (m_bits != m_buf)
				delete[]m_bits;
		}

		void setAll() {
			for (size_t i = 0; i < (m_size + sizeof(*m_bits) * 8 - 1) / (sizeof(*m_bits) * 8); ++i)
				m_bits[i] = (uint32_t)-1;
		}

		void resetAll() {
			for (size_t i = 0; i < (m_size + sizeof(*m_bits) * 8 - 1) / (sizeof(*m_bits) * 8); ++i)
				m_bits[i] = 0;
		}

		uint32_t set(size_t idx) {
			uint32_t& num = m_bits[idx / (sizeof(*m_bits) * 8)];
			idx = (idx % (sizeof(*m_bits) * 8));
			uint32_t result = num & (1 << idx);
			num |= (1 << idx);
			return result;
		}

		uint32_t reset(size_t idx) {
			uint32_t& num = m_bits[idx / (sizeof(*m_bits) * 8)];
			idx = (idx % (sizeof(*m_bits) * 8));
			uint32_t result = num & (1 << idx);
			num &= ~(1 << idx);
			return result;
		}

		uint32_t operator[](size_t idx) {
			return m_bits[idx / (sizeof(*m_bits) * 8)] & (1 << (idx % (sizeof(*m_bits) * 8)));
		}
	private:
		size_t m_size;
		uint32_t m_buf[16], *m_bits;
	};
}
