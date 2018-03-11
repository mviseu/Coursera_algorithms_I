#include "BidirectionalLinkedList.h"

int main() {
	BidirectionalLinkedList<int> list;
	for(auto i = 0; i < 1E6; ++i) {
		list.PushFront(i);
		list.PushBack(i);
		list.PopFront();
		list.PopBack();
	}
	return 0;
}