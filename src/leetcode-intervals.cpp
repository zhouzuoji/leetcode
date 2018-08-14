#include "leetcode-intervals.h"
#include <algorithm>

using namespace std;

namespace leetcode {

	/*
	Given a collection of intervals, merge all overlapping intervals.

	Example 1:

	Input: [[1,3],[2,6],[8,10],[15,18]]
	Output: [[1,6],[8,10],[15,18]]
	Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

	Example 2:

	Input: [[1,4],[4,5]]
	Output: [[1,5]]
	Explanation: Intervals [1,4] and [4,5] are considerred overlapping.
	*/
	vector<Interval> merge(vector<Interval>& intervals) {
		size_t len = intervals.size();
		if (len < 2)
			return intervals;
		vector<Interval> result;
		std::sort(intervals.begin(), intervals.end(), [](const Interval&a, const Interval& b) {
			return a.start < b.start;
		});

		int start = intervals[0].start, end = intervals[0].end;
		for (size_t i = 1; i < len; ++i) {
			const Interval& cur = intervals[i];
			if (cur.start > end) {
				result.push_back(Interval(start, end));
				start = cur.start;
				end = cur.end;
			}
			else {
				if (cur.end > end)
					end = cur.end;
			}
		}
		result.push_back(Interval(start, end));
		return result;
	}

	/*
	Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

	You may assume that the intervals were initially sorted according to their start times.

	Example 1:

	Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
	Output: [[1,5],[6,9]]

	Example 2:

	Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
	Output: [[1,2],[3,10],[12,16]]
	Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
	*/
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		vector<Interval> result;
		size_t i = 0, idx = 0, len = intervals.size();
		size_t left = 1, right = len, m;
		int start = newInterval.start, mstart, end = newInterval.end;
		if (!len) {
			result.push_back(newInterval);
			return result;
		}
		while (left <= right) {
			m = (left + right) / 2;
			mstart = intervals[m - 1].start;
			if (mstart > start)
				right = m - 1;
			else if (mstart < start)
				left = m + 1;
			else {
				left = m;
				break;
			}
		}
		right = left;
		while (right <= len) {
			if (intervals[right - 1].start > end)
				break;
			if (intervals[right - 1].end > end)
				end = intervals[right - 1].end;
			++right;
		}

		--left;
		while (left > 0) {
			if (intervals[left - 1].end < start)
				break;
			if (intervals[left - 1].start < start)
				start = intervals[left - 1].start;
			if (intervals[left - 1].end > end)
				end = intervals[left - 1].end;
			--left;
		}

		result.resize(left+len+1-right+1);
		for (i = 0; i < left; ++i)
			result[i] = intervals[i];
		result[left].start = start;
		result[left].end = end;
		for (i = 0; i < len + 1 - right; ++i)
			result[left+i+1] = intervals[right+i-1];
		return result;
	}
};