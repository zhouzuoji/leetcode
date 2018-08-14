#include <string>
#include <tuple>
#include <iostream>

namespace leetcode {
	using namespace std;

	bool matchAny(const char*p) {
		while ('*' == *p) ++p;
		return 0 == *p;
	}

	tuple<const char*, int> wildcardIndexOf(const char* s, const char*p) {
		const char* p2=p, *s2=s;
		while (true) {
			if ('*'==*p2) 
				return make_tuple(s, s2 - s);
			if (0==*p2) {
				if (0==*s2)
					return make_tuple(s, s2 - s);
				++s2;
				while (*s2) ++s2;
				s2 -= (p2 - p);
				s = s2;
				p2 = p;
				continue;
			}
			if (0==*s2)
				return make_tuple(nullptr, 0);
			if ('?' != *p2 && *p2 != *s2) {
				s2=++s;
				p2=p;
				continue;
			}
			++s2; ++p2;
		}
	}

	bool isMatch(const char* s, const char* p, int depth) {
		cout << "--------------depth: " << depth << "-----------------" << endl << s << endl << p << endl << endl;
		while (*s && *p) {
			if ('*'==*p) {
				++p;
				while ('*'==*p) ++p;
				if (!*p) 
					return true;
				int len;
				tie(s, len) = wildcardIndexOf(s, p);
				return (s && isMatch(s + len, p + len, depth + 1));
			}
			if ('?' != *p && *p != *s)
				return false;
			++s; ++p;
		}

		if (*s) return false;
		if (*p)
			return matchAny(p);
		return true;
	}

	bool isMatch(const string& s, const string& p) {
		bool result;
		if (p.empty())
			result=s.empty();
		else if (s.empty())
			result=matchAny(p.data());
		else
			result=isMatch(s.data(), p.data(), 0);
		cout << '"' << s << (result ? "\" match \"" : "\" can't match \"") << p << '"' << endl;		
		return result;
	}
}