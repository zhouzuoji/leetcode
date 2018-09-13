#pragma once

#include <iostream>
#include <vector>
#include <string>

template<typename _Type>
void writeJson(std::ostream& out, const _Type& value) {
	out << value;
}

template<>
inline void writeJson(std::ostream& out, const std::string& value) {
	out << '"' << value << '"';
}

template<char*>
inline void writeJson(std::ostream& out, const char* &value) {
	out << '"' << value << '"';
}

template<typename _Iterator>
void writeArray(std::ostream& out, _Iterator begin, _Iterator end) {
	if (begin == end)
		out << "[]";
	else {
		out << '[';
		writeJson(out, *(begin++));
		while (begin != end) {
			out << ", ";
			writeJson(out, *(begin++));
		}
		out << ']';
	}
}

template<typename _Type>
void writeJson(std::ostream& out, const std::vector<_Type> &arr) {
	writeArray(out, arr.begin(), arr.end());
}

template<typename _Type>
std::ostream& operator<<(std::ostream& out, const std::vector<_Type> &arr) {
	writeArray(out, arr.begin(), arr.end());
	return out;
}