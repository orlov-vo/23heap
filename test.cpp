#define CATCH_CONFIG_MAIN

#include <heap23.hpp>
#include "deps/catch.hpp"

using namespace std;

TEST_CASE("Inserting changes isEmpty", "[23heap]")
{
    Heap23<string> a;

    REQUIRE(a.isEmpty());
    a.insert(24, "002"); // 2
    REQUIRE_FALSE(a.isEmpty());
}

TEST_CASE("Can use other types", "[23heap]")
{
    Heap23<string> a;

    Heap23<int> intHeap;
    intHeap.insert(20, 15);
    Node23<int> *intNode = intHeap.extractMin();
    REQUIRE(intNode->priority() == 20);
    REQUIRE(intNode->value() == 15);

    Heap23<double> doubleHeap;
    doubleHeap.insert(-12, 15.12375);
    Node23<double> *doubleNode = doubleHeap.extractMin();
    REQUIRE(doubleNode->priority() == -12);
    REQUIRE(doubleNode->value() == 15.12375);

    Heap23<std::set<int>> setHeap;
    setHeap.insert(3, std::set<int>({4, 8, 9, 2}));
    Node23<std::set<int>> *setNode = setHeap.extractMin();
    REQUIRE(setNode->priority() == 3);
    REQUIRE(setNode->value() == std::set<int>({4, 8, 9, 2}));
}

TEST_CASE("Extracting in priority", "[23heap]")
{
    Heap23<string> a;

    REQUIRE(a.isEmpty());
    auto ptr1 = a.insert(24, "002"); // 2
    auto ptr2 = a.insert(18, "001"); // 1
    auto ptr3 = a.insert(52, "010"); // 10
    auto ptr4 = a.insert(38, "006"); // 6
    auto ptr5 = a.insert(30, "004"); // 4
    auto ptr6 = a.insert(26, "003"); // 3
    auto ptr7 = a.insert(46, "009"); // 9
    auto ptr8 = a.insert(39, "007"); // 7
    auto ptr9 = a.insert(41, "008"); // 8
    auto ptr0 = a.insert(35, "005"); // 5
    REQUIRE_FALSE(a.isEmpty());
    REQUIRE(a.extractMin() == ptr2);
    REQUIRE(a.extractMin() == ptr1);
    REQUIRE(a.extractMin() == ptr6);
    REQUIRE(a.extractMin() == ptr5);
    REQUIRE(a.extractMin() == ptr0);
    REQUIRE(a.extractMin() == ptr4);
    REQUIRE(a.extractMin() == ptr8);
    REQUIRE(a.extractMin() == ptr9);
    REQUIRE(a.extractMin() == ptr7);
    REQUIRE(a.extractMin() == ptr3);
    REQUIRE(a.isEmpty());
}

TEST_CASE("Merge two heaps", "[23heap]")
{
    Heap23<string> a;
    Heap23<string> b;

    REQUIRE(a.isEmpty());
    REQUIRE(b.isEmpty());
    auto ptr1 = a.insert(24, "002");
    auto ptr2 = a.insert(18, "001");
    auto ptr3 = a.insert(52, "006");
    auto ptr4 = b.insert(30, "004");
    auto ptr5 = b.insert(26, "003");
    auto ptr6 = b.insert(46, "005");
    REQUIRE_FALSE(a.isEmpty());
    REQUIRE_FALSE(b.isEmpty());
    REQUIRE(a.min() == ptr2);
    REQUIRE(b.min() == ptr5);
    a.merge(b);
    REQUIRE(b.isEmpty());
    REQUIRE_FALSE(a.isEmpty());
    REQUIRE(a.extractMin() == ptr2);
    REQUIRE(a.extractMin() == ptr1);
    REQUIRE(a.extractMin() == ptr5);
    REQUIRE(a.extractMin() == ptr4);
    REQUIRE(a.extractMin() == ptr6);
    REQUIRE(a.extractMin() == ptr3);
    REQUIRE(a.isEmpty());
}

TEST_CASE("Decrease key of node in heap", "[23heap]")
{
    Heap23<string> a;

    auto ptr1 = a.insert(24, "002");
    auto ptr2 = a.insert(18, "001");
    auto ptr3 = a.insert(52, "010");
    auto ptr4 = a.insert(38, "006");
    REQUIRE(a.min() == ptr2);
    a.decreaseKey(ptr1, 14);
    REQUIRE(a.min() == ptr1);
}
