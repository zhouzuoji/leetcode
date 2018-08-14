#include <vector>

namespace leetcode {
	typedef struct _Interval {
		int start;
		int end;
		_Interval() : start(0), end(0) {}
		_Interval(int s, int e) : start(s), end(e) {}
	} Interval;
	std::vector<Interval> merge(std::vector<Interval>& intervals);
	std::vector<Interval> insert(std::vector<Interval>& intervals, Interval newInterval);
}
