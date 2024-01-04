#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <set>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

 // Function: PutInLine
// Description: This function finds all possible ways to arrange a group of students in a line
//              such that no two incompatible students are next to each other.
// Parameters:
//   - all_students: A reference to a vector of integers representing all the students.
//   - incompatible_students: A reference to a vector of sets containing incompatible student pairs.
// Returns:
//   - std::vector<std::vector<int>>: A vector of vectors, each representing a valid arrangement of students.

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


// Note: The parameter `incompatible_students` is a vector of sets where each set contains
//       a pair of students who cannot be placed next to each other in the line. For example,
//       {{0, 1}} means that student 0 cannot be placed before or after student 1 in the line.

//global variables:
std::vector<int> current;
std::vector<std::vector<int>> output;

// compatable check: is trying to find the incompatible ones
bool compatable(int first, int second, std::vector<std::set<int>> &incompatible_students)
{
    auto size = incompatible_students.size();
    for (int x = 0; x < size; x++)
    {
        if ((incompatible_students[x].count(first) > 0 && incompatible_students[x].count(second) > 0))
        {
            return true;
        }
    }
    return false;
}

// helper function:
void helper_func(std::vector<int> &all_students, std::vector<std::set<int>> &incompatible_students)
{
    // base case
    if (current.size() == all_students.size())
    {
        output.push_back(current);
        return;
    }

    auto size = all_students.size();
    for (auto i = 0; i < size; i++)
    {
        if (std::find(current.begin(), current.end(), all_students[i]) != current.end())
        {
            continue;
        }
        // compatability test:
        if (!current.empty() && compatable(current.back(), all_students[i], incompatible_students))
        {
            continue;
        }
        current.push_back(all_students[i]);
        helper_func(all_students, incompatible_students);
        current.pop_back();
    }
}
std::vector<std::vector<int>> PutInLine(std::vector<int> &all_students, std::vector<std::set<int>> &incompatible_students)
{
    // base case
    if (all_students.empty())
    {
        return {}; //if empty return empty vec 
    }
    // reset the global variables
    current.clear();
    output.clear();
    helper_func(all_students, incompatible_students);
    return output;
}