#pragma once
#include "Priority.h"
#include "Board.h"
#include "SearchNode.h"
#include <memory>

std::shared_ptr<SearchNode> CreateSearchNode(Priority priority, const Board& currBoard, std::shared_ptr<SearchNode> prevNode, int movesSoFar);
std::shared_ptr<SearchNode> CreateFirstSearchNode(Priority priority, const Board& firstBoard);
std::shared_ptr<SearchNode> CreateNextSearchNode(const Board& currBoard, std::shared_ptr<SearchNode> oldNode);