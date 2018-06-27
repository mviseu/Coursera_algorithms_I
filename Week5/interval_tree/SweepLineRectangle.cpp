#include "SweepLineRectangle.h"
#include <array>
#include <queue>

namespace {

struct Event;
bool EventOrderByX(const Event& lhs, const Event& rhs);

using OrderedEvents = std::priority_queue<Event, std::vector<Event>, decltype(&EventOrderByX)>;

enum class EventType {start, end};

struct Event {
	Event(EventType ty, int xx, const Interval& yyy) : type(ty), x(xx), yy(yyy) {}
	EventType type;
	int x;
	Interval yy;
};

bool IsThisStartEvent(const Event& event) {
	return event.type == EventType::start;
}

bool EventOrderByX(const Event& lhs, const Event& rhs) {
	return rhs.x < lhs.x;
}

std::array<Event, 2> ExtractEvents(const Rectangle& rectangle) {
	const auto start = Event(EventType::start, rectangle.xx.lo, rectangle.yy);
	const auto end = Event(EventType::end, rectangle.xx.hi, rectangle.yy);
	return std::array<Event, 2>({start, end}); 
}

std::vector<Event> ExtractEvents(const std::vector<Rectangle>& rectangles) {
	std::vector<Event> events;
	for(const auto& rectangle : rectangles) {
		const auto startEndEvents = ExtractEvents(rectangle);
		events.push_back(startEndEvents[0]);
		events.push_back(startEndEvents[1]);
	}
	return events;
}

OrderedEvents SortEvents(const std::vector<Rectangle>& rectangles) {
	OrderedEvents pq(&EventOrderByX);
	// see how to use std::copy instead
	for(const auto& event : ExtractEvents(rectangles)) {
		pq.push(event);
	}
	return pq;
}

Intersection GetOverlapsAtStartOfEvent(const Event& event, const IntervalTree& yyIntervals) {
	const auto overlaps = yyIntervals.AllOverlappingIntervals(event.yy);
	return Intersection(event.x, overlaps);
}

void UpdateOverlapsAtStartOfEvent(std::vector<Intersection>& intersections, const Event& event, const IntervalTree& yyIntervals) {
	const auto intersection = GetOverlapsAtStartOfEvent(event, yyIntervals);
	if(!intersection.yy.empty()) {
		intersections.push_back(intersection);
	}
}

std::vector<Intersection> GetIntersectingYyIntervals(OrderedEvents& events) {
	IntervalTree yyIntervals;
	std::vector<Intersection> intersections;
	while(!events.empty()) {
		const auto event = events.top();
		if(IsThisStartEvent(event)) {
			UpdateOverlapsAtStartOfEvent(intersections, event, yyIntervals);
			yyIntervals.Insert(event.yy);
		} else {
			yyIntervals.Delete(event.yy);
		}
		events.pop();
	}
	return intersections;
}

} // namespace


std::vector<Intersection> SweepLineRectangle(const std::vector<Rectangle>& rectangles) {
	auto events = SortEvents(rectangles);
	return GetIntersectingYyIntervals(events);
}
