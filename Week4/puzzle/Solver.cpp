#include "Solver.h"
#include "SearchNode.h"
#include "SearchNodeFactory.h"
#include "PriorityQueue.h"
#include <stdexcept>
#include <functional>

namespace {

bool GetPriorityComparePtr(std::shared_ptr<SearchNode> lhs, std::shared_ptr<SearchNode> rhs) {
	return GetPriorityCompare(*lhs, *rhs);
}

void ThrowIfNotSolvable(const Board& initial) {
	if(!initial.IsSolvable()) {
		throw std::runtime_error("Initial board is not solvable");
	}
}

void EraseNeighborIfEqualToPrevious(const SearchNode& oldNode, std::vector<Board>& candidates) {
	if(!(oldNode.IsThereAPreviousNode())) {
		return;
	}
	const auto sameBoard = std::find_if(candidates.begin(), candidates.end(), [&oldNode](const Board& candidate) {
		return oldNode.IsThisThePreviousBoard(candidate);
	});
	if(sameBoard != candidates.end()) {
		candidates.erase(sameBoard);
	}
}

std::vector<std::shared_ptr<SearchNode>> GetNeighborNodes(std::shared_ptr<SearchNode> oldNode, const std::vector<Board>& neighborBoards) {
	std::vector<std::shared_ptr<SearchNode>> searchNodes;
	std::transform(neighborBoards.cbegin(), neighborBoards.cend(), std::back_inserter(searchNodes), 
		[oldNode](const Board& board) {return CreateNextSearchNode(board, oldNode);});
	return searchNodes;
}

void PushAllNeighbors(const std::vector<std::shared_ptr<SearchNode>>& neighbors, PriorityQueue<std::shared_ptr<SearchNode>, decltype(&GetPriorityComparePtr)>& pq) {
	std::for_each(neighbors.cbegin(), neighbors.cend(), [&pq] (std::shared_ptr<SearchNode> sn) {return pq.Push(sn);});
}

void InsertNeighbors(std::shared_ptr<SearchNode> oldNode,  PriorityQueue<std::shared_ptr<SearchNode>, decltype(&GetPriorityComparePtr)>& pq) {
	auto neighborBoards = oldNode->GetAllNeighbors();
	EraseNeighborIfEqualToPrevious(*oldNode, neighborBoards);
	const auto neighborNodes = GetNeighborNodes(oldNode, neighborBoards);
	PushAllNeighbors(neighborNodes, pq);
}

void NextMove(PriorityQueue<std::shared_ptr<SearchNode>, decltype(&GetPriorityComparePtr)>& pq) {
	auto top = pq.Top();
	pq.Pop();
	InsertNeighbors(top, pq);
}

bool HasGoalBeenReached(const SearchNode& nd) {
	return nd.HasGoalBeenReached();
}

void FirstMove(const Board& firstBoard, PriorityQueue<std::shared_ptr<SearchNode>, decltype(&GetPriorityComparePtr)>& pq, Priority priority) {
	auto firstSearch = CreateFirstSearchNode(priority, firstBoard);
	pq.Push(firstSearch);
}

std::vector<Board> GetAStarSearchPath(const SearchNode& lastNode) {
	return lastNode.GetSequenceOfBoards();
}

int GetAStarSearchLength(const SearchNode& lastNode) {
	return lastNode.GetSizeOfNodeChain();
}

std::shared_ptr<SearchNode> Play(const Board& firstBoard, Priority priority) {
	PriorityQueue<std::shared_ptr<SearchNode>, decltype(&GetPriorityComparePtr)> pq(&GetPriorityComparePtr);
	FirstMove(firstBoard, pq, priority);
	auto top =  pq.Top();
	while(!HasGoalBeenReached(*top)) {
		NextMove(pq);
		top = pq.Top();
	}
	return top;
}

} // namespace

Solver::Solver(const Board& firstBoard, Priority priority) {
	ThrowIfNotSolvable(firstBoard);
	goalBoard = Play(firstBoard, priority);
}

int Solver::Moves() const {
	return GetAStarSearchLength(*goalBoard);
}

std::vector<Board> Solver::Solution() const {
	return GetAStarSearchPath(*goalBoard);
}
