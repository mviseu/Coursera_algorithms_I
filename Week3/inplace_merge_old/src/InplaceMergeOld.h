#pragma once
#include <functional>
#include <algorithm>
#include <iostream>

template <typename ForwardIt>
bool AreThereLhsRejects(ForwardIt lhs_rej, ForwardIt rhs) {
	return !(lhs_rej == rhs) ? true : false;
}

template <typename ForwardIt>
bool IsThereTheRhsReject(ForwardIt rhs_rej, ForwardIt last) {
	return rhs_rej != last;
}

template <typename ForwardIt>
bool AreThereNoRejects(ForwardIt lhs_rej, ForwardIt rhs_rej, ForwardIt rhs, ForwardIt last) {
	return !AreThereLhsRejects(lhs_rej, rhs) && !IsThereTheRhsReject(rhs_rej, last);
}

template <typename ForwardIt>
bool AreThereLhsRejectsOnly(ForwardIt lhs_rej, ForwardIt rhs_rej, ForwardIt rhs, ForwardIt last) {
	return AreThereLhsRejects(lhs_rej, rhs) && !IsThereTheRhsReject(rhs_rej, last);
}

template <typename ForwardIt>
bool AreThereRhsRejectsOnly(ForwardIt lhs_rej, ForwardIt rhs_rej, ForwardIt rhs, ForwardIt last) {
	return !AreThereLhsRejects(lhs_rej, rhs) && IsThereTheRhsReject(rhs_rej, last);
}

template <typename ForwardIt>
bool HasRhsRejectReachedEnd(ForwardIt rhs_rej, ForwardIt rhs) {
	return rhs_rej + 1 == rhs;
}

template <typename ForwardIt>
bool HasRhsReachedEnd(ForwardIt rhs, ForwardIt end) {
	return rhs == end;
}

template <typename ForwardIt>
bool HasLhsReachedMiddle(ForwardIt lhs, ForwardIt middle) {
	return lhs == middle;
}

template <typename ForwardIt>
bool HasLhsReachedEnd(ForwardIt lhs, ForwardIt rhs, ForwardIt last) {
	return lhs == last || lhs == rhs;
}


template <typename ForwardIt>
bool HasMergeCompleted(ForwardIt lhs, ForwardIt lhs_rej, ForwardIt rhs_rej, ForwardIt rhs, ForwardIt last) {
	return HasLhsReachedEnd(lhs, rhs, last) || HasRhsReachedEnd(rhs, last) && AreThereNoRejects(lhs_rej, rhs_rej, rhs, last);
}


template <typename T>
void SwapValues(T& val1, T& val2) {
	using std::swap;
	swap(val1, val2);
}

template <typename ForwardIt>
void IncrementPointers(ForwardIt& itFirst) {
	++itFirst;
}

template <typename ForwardIt, typename... Args>
void IncrementPointers(ForwardIt& itFirst, Args&... args) {
	++itFirst;
	IncrementPointers(args...);
}

/*
General finish step
One Value at the right-most value must be at starting position
The left  values must all shift one position to the right

*/

template<typename ForwardIt>
void ShiftAllToRightAndPlaceLastValInFirstPos(ForwardIt& left, ForwardIt& lastValuePosition, ForwardIt last) {
	if(lastValuePosition == left) {
		left = last;
	} else {
		SwapValues(*left, *lastValuePosition);
		IncrementPointers(left);
		ShiftAllToRightAndPlaceLastValInFirstPos(left, lastValuePosition, last);
	}
}
/*
General finish step
*/
template<typename ForwardIt>
void ShiftAllToLeftAndPlaceFirstValInLastPos(ForwardIt& firstValuePosition, ForwardIt& right, ForwardIt last) {
	while(right != last) {
		SwapValues(*firstValuePosition, *right);
		IncrementPointers(firstValuePosition, right);
	}

}


/*
Finish step
There is one value Val at the right that is left
Val must be at the starting position
All other elements must shift 1 pos to the right, after Val
*/
template<typename ForwardIt>
void MergeLhsRejectsAndLhsWithoutRhs(ForwardIt& lhs, ForwardIt& lastValuePosition, ForwardIt last) {
	ShiftAllToRightAndPlaceLastValInFirstPos(lhs, lastValuePosition, last);

}

template <typename ForwardIt>
void MergeLhsAndLastRhsReject(ForwardIt& rhs_rej, ForwardIt& lhs, ForwardIt rhs) {
	const auto oldLhs = lhs;
	ShiftAllToLeftAndPlaceFirstValInLastPos(rhs_rej, lhs, rhs);
	lhs = oldLhs;
}

template <typename ForwardIt, typename Compare = std::less<typename ForwardIt::value_type>>
void MergeWhenNoRejects(ForwardIt& lhs, ForwardIt& lhs_rej, ForwardIt& rhs, ForwardIt last, Compare compare = Compare()) {
	if(lhs == rhs) {
		std::cout << "lhs == rhs" << std::endl;
		lhs = last;
	} else {
		if(compare(*rhs, *lhs)) {
			SwapValues(*rhs, *lhs);
			IncrementPointers(lhs);
			if(rhs + 1 == last) {
				MergeLhsRejectsAndLhsWithoutRhs(lhs, rhs, last);
			}
			IncrementPointers(rhs);
			std::cout << "lhs rej between lhs and rhs: " << *lhs_rej << std::endl;
		} else {
			std::cout << "Increment left pointer" << std::endl;
			IncrementPointers(lhs);
		}
	}
	if(lhs == lhs_rej) {
		std::cout << "Reset lhs rej" << std::endl;
		lhs_rej = rhs;
	}
}

template <typename ForwardIt, typename Compare = std::less<typename ForwardIt::value_type>>
void MergeWhenLhsRejectsOnly(ForwardIt& lhs, ForwardIt& lhs_rej, ForwardIt& rhs_rej, ForwardIt& rhs, ForwardIt last, Compare compare = Compare()) {
	if(compare(*rhs, *lhs_rej)) {
		SwapValues(*rhs, *lhs);
		IncrementPointers(lhs);
		if(lhs_rej < lhs) {
			lhs_rej = lhs;
			if(rhs + 1 == last) {
				MergeLhsRejectsAndLhsWithoutRhs(lhs, rhs, last);
			}
		}
		IncrementPointers(rhs);
	} else {
		SwapValues(*lhs, *rhs);
		SwapValues(*lhs, *lhs_rej);
		rhs_rej = lhs_rej;
		IncrementPointers(lhs, lhs_rej, rhs);
	}
	if(lhs == rhs_rej) {
		lhs = lhs_rej;
	}
	if(lhs_rej == lhs){
		lhs_rej = rhs;
	}
}

template <typename ForwardIt, typename Compare = std::less<typename ForwardIt::value_type>>
void MergeWhenRhsRejectsOnly(ForwardIt& lhs, ForwardIt& lhs_rej, ForwardIt& rhs_rej, ForwardIt& rhs, ForwardIt last, Compare compare = Compare()) {
	if(compare(*rhs_rej, *lhs)) {
		if(lhs > rhs_rej) {
			IncrementPointers(rhs_rej);
			if(rhs_rej == lhs) {
				rhs_rej = last;
			}
		} else {
			SwapValues(*lhs, *rhs);
			SwapValues(*lhs, *rhs_rej);
			IncrementPointers(lhs, rhs);
			if(lhs == rhs_rej) {
				lhs = lhs_rej;
			}
		}
	} else {
		if(rhs_rej + 1 == lhs) {
			std::cout << "move rhs rej next to rhs" << std::endl;
			MergeLhsAndLastRhsReject(rhs_rej, lhs, rhs);
			if(rhs_rej + 1 == rhs) {
				rhs = rhs_rej;
				lhs_rej = rhs;
				rhs_rej = last;
			}
		} else {
			IncrementPointers(lhs);
		}
		if(lhs == rhs_rej) {
			lhs = lhs_rej;
		}
	}
	if(lhs_rej == lhs){
		lhs_rej = rhs;
	}
}

template <typename ForwardIt, typename Compare = std::less<typename ForwardIt::value_type>>
void MergeWhenLhsAndRhsRejects(ForwardIt& lhs, ForwardIt& lhs_rej, ForwardIt& rhs_rej, ForwardIt& rhs, Compare compare = Compare()) {
	if(compare(*rhs_rej, *lhs_rej)) {
		SwapValues(*rhs_rej, *rhs);
		SwapValues(*rhs, *lhs);
		IncrementPointers(lhs, rhs);
	} else {
		SwapValues(*lhs_rej, *rhs_rej);
		SwapValues(*lhs, *rhs_rej);
		IncrementPointers(lhs, lhs_rej, rhs_rej);
	}
	if(lhs == rhs_rej) {
		lhs = lhs_rej;
	}
	if(lhs_rej == lhs){
		lhs_rej = rhs;
		std::cout << "eliminated lhs rej" << std::endl;
	}
}

template <typename ForwardIt, typename Compare = std::less<typename ForwardIt::value_type>>
void InplaceMerge(ForwardIt first, ForwardIt middle, ForwardIt last, Compare compare = Compare()) {
	auto lhs = first, rhs = middle, lhs_rej = rhs, rhs_rej = last;
	while(!HasMergeCompleted(lhs, lhs_rej, rhs_rej, rhs, last)) {
		if(AreThereNoRejects(lhs_rej, rhs_rej, rhs, last)) {
			// compare lhs to rhs
			std::cout << "case 1" << std::endl;
			MergeWhenNoRejects(lhs, lhs_rej, rhs, last, compare);
		} else {
			// compare lhs_rej to rhs
			if(AreThereLhsRejectsOnly(lhs_rej, rhs_rej, rhs, last)) {
				std::cout << "case 2" << std::endl;
				MergeWhenLhsRejectsOnly(lhs, lhs_rej, rhs_rej, rhs, last, compare);
			} else {
				// compare lhs to rhs_rej
				if(AreThereRhsRejectsOnly(lhs_rej, rhs_rej, rhs, last)) {
					std::cout << "case 3" << std::endl;
					MergeWhenRhsRejectsOnly(lhs, lhs_rej, rhs_rej, rhs, last, compare);
				} else {
					std::cout << "case 4" << std::endl;
					// compare lhs_rej to rhs_rej
					MergeWhenLhsAndRhsRejects(lhs, lhs_rej, rhs_rej, rhs, compare);

				}
			}
		}
	}
}

/*
tomorrow:
think of what happens when rhs reaches end / lhs reaches middle before end condition is met
For all four cases, consider these options
*/