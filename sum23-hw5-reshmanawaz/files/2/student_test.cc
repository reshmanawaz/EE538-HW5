#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------


// Example 1:
// all_students = {0, 1};
// incompatible_students = {};
// output = {{0, 1}, {1, 0}};

// Example 2:
// all_students = {0, 1, 2};
// incompatible_students = {};
// output = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2},
//           {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};

// Example 3:
// all_students = {0, 1, 2};
// incompatible_students = {{0, 1}};
// output = {{0, 2, 1}, {1, 2, 0}};

// Example 4:
// all_students = {1, 7, 4}
// incompatible_students = {}
// Expected output: There are six possible valid arrangements of the three students:
// - {1, 7, 4}, {1, 4, 7}, {7, 1, 4}, {7, 4, 1}, {4, 1, 7}, {4, 7, 1}.


TEST(q2, t1){
    std::vector<int> a = {0,1};
    std::vector<std::set<int>> b = {};
    std::vector<std::vector<int>> expected = {{0,1}, {1,0}};
    std::vector<std::vector<int>> output = PutInLine(a, b); 
    EXPECT_EQ(expected, output);
}

TEST(q2, t2){
    std::vector<int> a = {0, 1, 2};
    std::vector<std::set<int>> b = {};
    std::vector<std::vector<int>> expected = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};
    std::vector<std::vector<int>> output = PutInLine(a, b); 
    EXPECT_EQ(expected, output);
}

TEST(q2, t3){
    std::vector<int> a = {0, 1, 2};
    std::vector<std::set<int>> b = {{0, 1}};
    std::vector<std::vector<int>> expected = {{0, 2, 1}, {1, 2, 0}};
    std::vector<std::vector<int>> output = PutInLine(a, b); 
    EXPECT_EQ(expected, output);
}
TEST(q2, t4){
    std::vector<int> a = {};
    std::vector<std::set<int>> b = {};
    std::vector<std::vector<int>> expected = {};
    std::vector<std::vector<int>> output = PutInLine(a, b); 
    EXPECT_EQ(expected, output);
}


