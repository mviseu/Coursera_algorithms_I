#include "Event.h"
#include "IntersectOrthogonalLines.h"
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


void AddToIntersectionsIfWithinRange(std::back_insert_iterator<std::vector<Point>> intersections, const std::set<double>& yCoords, const Event& event) {
	const auto limits = std::get<VerticalLineYy>(event.yy); 
	const auto lo = GetLowerLimit(limits); 
	const auto hi = GetUpperLimit(limits);
	for(auto it = yCoords.lower_bound(lo); it != yCoords.upper_bound(hi); ++it) {
		intersections = Point(event.x, *it);
	}
}

std::vector<Point> GetIntersectionPoints(std::priority_queue<Event>& events) {
	std::vector<Point> intersections;
	std::set<double> yCoord;
	while(!events.empty()) {
		const auto nextEvent = events.top();
		if(IsEventPartOfHorizontalLine(nextEvent)) {
			auto coordOfEvent = std::get<double>(nextEvent.yy);
			if(yCoord.find(coordOfEvent) != yCoord.end()) {
				yCoord.erase(coordOfEvent);
			} else {
				yCoord.insert(coordOfEvent);
			}
		} else {
			AddToIntersectionsIfWithinRange(std::back_inserter(intersections), yCoord, nextEvent);
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