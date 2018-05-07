#include "SearchNodeFactory.h"
#include "SearchNodeHamming.h"
#include "SearchNodeManhattan.h"


std::shared_ptr<SearchNode> CreateSearchNode(Priority priority, const Board& currBoard, std::shared_ptr<SearchNode> prevNode, int movesSoFar) {

	switch(priority) {
	case Priority::hamming:
		return std::make_shared<SearchNodeHamming>(SearchNodeData(currBoard, prevNode, movesSoFar));
	case Priority::manhattan:
		return std::make_shared<SearchNodeManhattan>(SearchNodeData(currBoard, prevNode, movesSoFar));
	}
}

std::shared_ptr<SearchNode> CreateFirstSearchNode(Priority priority, const Board& firstBoard) {
	return CreateSearchNode(priority, firstBoard, nullptr, 0);
}

std::shared_ptr<SearchNode> CreateNextSearchNode(const Board& currBoard, std::shared_ptr<SearchNode> oldNode) {
	if(typeid(*oldNode) == typeid(SearchNodeHamming)) {
		return CreateSearchNode(Priority::hamming, currBoard, oldNode, oldNode->IncrementNrMoves());
	} else {
		return CreateSearchNode(Priority::manhattan, currBoard, oldNode, oldNode->IncrementNrMoves());		
	}
}