#include "Event.h"
#include "SweepLine.h"
#include "VerticalLineYy.h"
#include <queue>
#include <set>

namespace {

std::vector<Event> GetEvent(const OrthogonalLineSegment& line) {
	std::vector<Event> events;
	if(IsLineHorizontal(line)) {
		events.emplace_back(line.start.x, line.start.y);
		events.emplace_back(line.end.x, line.end.y);
	} else {
		events.emplace_back(line.start.x, VerticalLineYy(line.start.y, line.end.y));
	}
	return events;
}


std::priority_queue<Event> SortEventsByXCoordinate(const std::vector<OrthogonalLineSegment>& lines) {
	auto pq = std::priority_queue<Event>();
	for(const auto& line : lines) {
		const auto events = GetEvent(line);
		for(const auto& event : events) {
			pq.push(event);
		}
	}
	return pq;
}


std::back_insert_iterator<std::vector<Point>> AddToIntersectionsIfWithinRange(std::back_insert_iterator<std::vector<Point>> intersections, const std::set<double>& yCoords, const Event& event) {
	const auto limits = std::get<VerticalLineYy>(event.yy); 
	const auto lo = GetLowerLimit(limits); 
	const auto hi = GetUpperLimit(limits);
	for(auto it = yCoords.lower_bound(lo); it != yCoords.upper_bound(hi); ++it) {
		intersections = Point(event.x, *it);
	}
	return intersections;
}

void AddOrRemoveFromHorizontalCandidates(std::set<double>& candidates, double candidate) {
	if(candidates.find(candidate) != candidates.end()) {
		candidates.erase(candidate);
	} else {
		candidates.insert(candidate);
	}	
}

std::vector<Point> GetIntersectionPoints(std::priority_queue<Event>& events) {
	std::vector<Point> intersections;
	auto intersectInsert = std::back_inserter(intersections);
	std::set<double> candidates;
	while(!events.empty()) {
		const auto nextEvent = events.top();
		if(IsEventPartOfHorizontalLine(nextEvent)) {
			AddOrRemoveFromHorizontalCandidates(candidates, std::get<double>(nextEvent.yy));
		} else {
			intersectInsert = AddToIntersectionsIfWithinRange(intersectInsert, candidates, nextEvent);
		}
		events.pop();
	}
	return intersections;
}

} // namespace


std::vector<Point> SweepLine(const std::vector<OrthogonalLineSegment>& lines) {
	auto events =  SortEventsByXCoordinate(lines);
	return GetIntersectionPoints(events);
}