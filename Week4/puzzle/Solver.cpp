#include "Solver.h"
#include "SearchNode.h"
#include "PriorityQueue.h"
#include <stdexcept>
#include <functional>

namespace {

bool GetHammingComparePtr(std::shared_ptr<SearchNode> lhs, std::shared_ptr<SearchNode> rhs) {
	return GetHammingCompare(*lhs, *rhs);
}

void ThrowIfNotSolvable(const Board& initial) {
	if(!initial.IsSolvable()) {
		throw std::runtime_error("Initial board is not solvable");
	}
}

void EraseNeighborIfEqualToPrevious(const SearchNode& oldNode, std::vector<Board>& candidates) {
	if(!(oldNode.prevNode)) {
		return;
	}
	const auto sameBoard = std::find_if(candidates.begin(), candidates.end(), [&oldNode](const Board& candidate) {
		return candidate == (*oldNode.prevNode).currBoard;
	});
	if(sameBoard != candidates.end()) {
		candidates.erase(sameBoard);
	}
}

std::vector<std::shared_ptr<SearchNode>> GetNeighborNodes(std::shared_ptr<SearchNode> oldNode, const std::vector<Board>& neighborBoards) {
	std::vector<std::shared_ptr<SearchNode>> searchNodes;
	std::transform(neighborBoards.cbegin(), neighborBoards.cend(), std::back_inserter(searchNodes), 
		[oldNode](const Board& board) {return std::make_shared<SearchNode>(SearchNode(board, oldNode, (*oldNode).movesSoFar + 1));});
	return searchNodes;
}

void PushAllNeighbors(const std::vector<std::shared_ptr<SearchNode>>& neighbors, PriorityQueue<std::shared_ptr<SearchNode>, decltype(&GetHammingComparePtr)>& pq) {
	std::for_each(neighbors.cbegin(), neighbors.cend(), [&pq] (std::shared_ptr<SearchNode> sn) {return pq.Push(sn);});
}

void InsertNeighbors(std::shared_ptr<SearchNode> oldNode,  PriorityQueue<std::shared_ptr<SearchNode>, decltype(&GetHammingComparePtr)>& pq) {
	auto neighborBoards = (*oldNode).currBoard.Neighbors();
	EraseNeighborIfEqualToPrevious(*oldNode, neighborBoards);
	const auto neighborNodes = GetNeighborNodes(oldNode, neighborBoards);
	PushAllNeighbors(neighborNodes, pq);
}

void NextMove(PriorityQueue<std::shared_ptr<SearchNode>, decltype(&GetHammingComparePtr)>& pq) {
	auto top = pq.Top();
	pq.Pop();
	InsertNeighbors(top, pq);
}

bool HasGoalBeenReached(const SearchNode& nd) {
	return nd.currBoard.IsGoal();
}

void FirstMove(const Board& firstBoard, PriorityQueue<std::shared_ptr<SearchNode>, decltype(&GetHammingComparePtr)>& pq) {
	auto firstSearch = std::make_shared<SearchNode>(SearchNode(firstBoard, nullptr, 0));
	pq.Push(firstSearch);
}

std::vector<Board> GetAStarSearchPath(const SearchNode& lastNode) {
	std::vector<Board> searchPath;
	auto node = lastNode;
	while(node.prevNode) {
		searchPath.push_back(node.currBoard);
		node = *node.prevNode;
	}
	searchPath.push_back(node.currBoard);
	std::reverse(searchPath.begin(), searchPath.end());
	return searchPath;
}

int GetAStarSearchLength(const SearchNode& lastNode) {
	auto length{0};
	auto node = lastNode;
	while(node.prevNode) {
		++length;
		node = *node.prevNode;
	}
	return length;
}

SearchNode Play(const Board& firstBoard) {
	PriorityQueue<std::shared_ptr<SearchNode>, decltype(&GetHammingComparePtr)> pq(&GetHammingComparePtr);
	FirstMove(firstBoard, pq);
	auto top =  pq.Top();
	while(!HasGoalBeenReached(*top)) {
		NextMove(pq);
		top = pq.Top();
	}
	return *top;
}

} // namespace

Solver::Solver(const Board& firstBoard) {
	ThrowIfNotSolvable(firstBoard);
	goalBoard = Play(firstBoard);
}

int Solver::Moves() const {
	return GetAStarSearchLength(goalBoard);
}

std::vector<Board> Solver::Solution() const {
	return GetAStarSearchPath(goalBoard);
}
