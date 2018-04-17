#include "catch.hpp"
#include "InplaceMerge.h"
#include <algorithm>
#include <string>

void CheckIfMergedInplaceSucceeds(const std::vector<int>& vec) {
	auto vecStd = vec;
	auto vecMyInplace = vec;
	std::cout << "Before" << std::endl;
	for(const auto& elem : vecStd) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;
	const auto halfSize = vec.size() / 2;
	std::inplace_merge(vecStd.begin(), vecStd.begin() + halfSize, vecStd.end());
	InplaceMerge(vecMyInplace.begin(), vecMyInplace.begin() + halfSize, vecMyInplace.end());
	std::cout << "after" << std::endl;
	for(const auto& elem : vecStd) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;
	for(const auto& elem : vecMyInplace) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;
    REQUIRE(vecStd == vecMyInplace);
}

TEST_CASE("test inplace merge") {
	SECTION("should reject lhs the first time") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({-2, 2, 1, -1, 0}));
	}
	SECTION("given sorted vector") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({1, 2, 3, 4, 5, 6}));
	}
	SECTION("given swapped left and right arrays") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({4, 5, 6, 1, 2, 3}));
	}
	SECTION("should reject lhs") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({-2, 2, 1, -1, 0}));
	}
	
	SECTION("should shift all lhs_rejects to the end and at first pos insert last filled pos") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({2, 1, 0, -2, -1}));
	}

	SECTION("should reset lhs reject") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({-2, 0, -1, 2, 1}));
	}

	SECTION("new") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({-1, 2, 0, 1, -2}));
	}

	SECTION("should create rhs reject") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({-1, 1, -2, 0, 2}));
	}

	SECTION("rhs rej is reset to end") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({-1, 2, -2, 1, 0}));
	}

	SECTION("with shift of all lhs elements to before rhs_rej") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({1, 0, -1, -3, -2, 2}));
	}

	SECTION("with shift of all lhs elements to before rhs_rej and rhs_rej before rhs") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({-1, 0, -2, 2, 1}));
	}

	SECTION("with both lhs and rhs rejects") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({-2, 2, 1, -3, 1, 0}));
	}

	SECTION("with shift of rhs_rej to right with lhs elements still left to compare") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({-2, 0, 2, -3, -1, 1}));
	}

	SECTION("and ensure lhs can evaluate last element") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({-1, -3, 1, -2, 0, 2}));		
	}

	SECTION("with lhs not reaching end but no rejects and rhs reaching end") {
		CheckIfMergedInplaceSucceeds(std::vector<int>({-1, 3, 2, 1, -2, 0, -3}));		
	}
}
