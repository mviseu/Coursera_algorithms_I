#pragma once
#include <functional>
#include <algorithm>
#include <iostream>

template <typename InputIt>
bool AreThereLhsRejects(InputIt lhs_rej, InputIt rhs) {
	return !(lhs_rej == rhs) ? true : false;
}

template <typename InputIt>
bool IsThereTheRhsReject(InputIt rhs_rej, InputIt last) {
	return rhs_rej != last;
}

template <typename InputIt>
bool AreThereNoRejects(InputIt lhs_rej, InputIt rhs_rej, InputIt rhs, InputIt last) {
	return !AreThereLhsRejects(lhs_rej, rhs) && !IsThereTheRhsReject(rhs_rej, last);
}

template <typename InputIt>
bool AreThereLhsRejectsOnly(InputIt lhs_rej, InputIt rhs_rej, InputIt rhs, InputIt last) {
	return AreThereLhsRejects(lhs_rej, rhs) && !IsThereTheRhsReject(rhs_rej, last);
}

template <typename InputIt>
bool AreThereRhsRejectsOnly(InputIt lhs_rej, InputIt rhs_rej, InputIt rhs, InputIt last) {
	return !AreThereLhsRejects(lhs_rej, rhs) && IsThereTheRhsReject(rhs_rej, last);
}

template <typename InputIt>
bool HasRhsRejectReachedEnd(InputIt rhs_rej, InputIt rhs) {
	return rhs_rej + 1 == rhs;
}

template <typename InputIt>
bool HasRhsReachedEnd(InputIt rhs, InputIt end) {
	return rhs == end;
}

template <typename InputIt>
bool HasLhsReachedMiddle(InputIt lhs, InputIt middle) {
	return lhs == middle;
}

template <typename InputIt>
bool HasLhsReachedEnd(InputIt lhs, InputIt rhs, InputIt last) {
	return lhs == last || lhs == rhs;
}


template <typename InputIt>
bool HasMergeCompleted(InputIt lhs, InputIt lhs_rej, InputIt rhs_rej, InputIt rhs, InputIt last) {
	return HasLhsReachedEnd(lhs, rhs, last) || HasRhsReachedEnd(rhs, last) && AreThereNoRejects(lhs_rej, rhs_rej, rhs, last);
}


template <typename T>
void SwapValues(T& val1, T& val2) {
	using std::swap;
	swap(val1, val2);
}

template <typename InputIt>
void IncrementPointers(InputIt& itFirst) {
	++itFirst;
}

template <typename InputIt, typename... Args>
void IncrementPointers(InputIt& itFirst, Args&... args) {
	++itFirst;
	IncrementPointers(args...);
}

/*
General finish step
One Value at the right-most value must be at starting position
The left  values must all shift one position to the right

*/

template<typename InputIt>
void ShiftAllToRightAndPlaceLastValInFirstPos(InputIt& left, InputIt& lastValuePosition, InputIt last) {
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
template<typename InputIt>
void ShiftAllToLeftAndPlaceFirstValInLastPos(InputIt& firstValuePosition, InputIt& right, InputIt last) {
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
template<typename InputIt>
void MergeLhsRejectsAndLhsWithoutRhs(InputIt& lhs, InputIt& lastValuePosition, InputIt last) {
	ShiftAllToRightAndPlaceLastValInFirstPos(lhs, lastValuePosition, last);

}

template <typename InputIt>
void MergeLhsAndLastRhsReject(InputIt& rhs_rej, InputIt& lhs, InputIt rhs) {
	const auto oldLhs = lhs;
	ShiftAllToLeftAndPlaceFirstValInLastPos(rhs_rej, lhs, rhs);
	lhs = oldLhs;
}

template <typename InputIt, typename Compare = std::less<typename InputIt::value_type>>
void MergeWhenNoRejects(InputIt& lhs, InputIt& lhs_rej, InputIt& rhs, InputIt last, Compare compare = Compare()) {
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

template <typename InputIt, typename Compare = std::less<typename InputIt::value_type>>
void MergeWhenLhsRejectsOnly(InputIt& lhs, InputIt& lhs_rej, InputIt& rhs_rej, InputIt& rhs, InputIt last, Compare compare = Compare()) {
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

template <typename InputIt, typename Compare = std::less<typename InputIt::value_type>>
void MergeWhenRhsRejectsOnly(InputIt& lhs, InputIt& lhs_rej, InputIt& rhs_rej, InputIt& rhs, InputIt last, Compare compare = Compare()) {
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

template <typename InputIt, typename Compare = std::less<typename InputIt::value_type>>
void MergeWhenLhsAndRhsRejects(InputIt& lhs, InputIt& lhs_rej, InputIt& rhs_rej, InputIt& rhs, Compare compare = Compare()) {
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

template <typename InputIt, typename Compare = std::less<typename InputIt::value_type>>
void InplaceMerge(InputIt first, InputIt middle, InputIt last, Compare compare = Compare()) {
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