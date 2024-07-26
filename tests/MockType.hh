#pragma once

#include <string>
#include <vector>

struct MockType {
    std::string string;
    std::vector<int> vector;
    int integer;

    MockType(
        const std::string& string,
        const std::vector<int>& vector,
        int integer
    ) : string(string), vector(vector), integer(integer)
    {}
};

bool operator==(const MockType& obj1, const MockType& obj2) {
    return
        obj1.integer == obj2.integer &&
        obj1.string == obj2.string && 
        obj1.vector == obj2.vector;
}