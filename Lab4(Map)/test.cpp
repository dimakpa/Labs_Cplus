#include <iostream>
#include <string>
#include "Maap.h"

#include "gtest/gtest.h"
#include "tchar.h"

using namespace std;

TEST(Pair, Constructor){
    Pair<int, string> pair2(1, "aaa");
    ASSERT_EQ(1, pair2.first);
    ASSERT_STREQ("aaa", pair2.second.c_str());
    Pair<int, string> pair3(1);
    ASSERT_EQ(1, pair3.first);
}

TEST(Node, Constructor){
    Pair<int, string> pair1(1, "aaa");
    Node<Pair<int, string>> node1(pair1);
    ASSERT_EQ(1, node1.pair.first);
    ASSERT_STREQ("aaa", node1.pair.second.c_str());
}

TEST(Map, Constructor){
    Pair<int, string> pair1(1, "aaa");
    Node<Pair<int, string>> node1(pair1);
    Map<int, string> map1(pair1);
    //map1.AddNode(node1.pair.first, node1.pair.second);
    ASSERT_EQ(1, map1.getRoot()->pair.first);
    ASSERT_STREQ("aaa", map1.getRoot()->pair.second.c_str());
}

TEST(Map, Delete){
    Pair<int, string> pair1(1, "aaa");
    Pair<int, string> pair2(2, "bbb");
    Map<int, string> map1(pair1);
    map1.AddNode(pair2.first, pair2.second);
    ASSERT_EQ(1, map1.getRoot()->pair.first);
    ASSERT_STREQ("aaa", map1.getRoot()->pair.second.c_str());
    map1.DelNode(pair1.first);
    ASSERT_EQ(2, map1.getRoot()->pair.first);
    ASSERT_STREQ("bbb", map1.getRoot()->pair.second.c_str());
}

TEST(Map, ADD){
    Pair<int, string> pair2(2, "bbb");
    Pair<int, string> pair1(1, "aaa");
    Node<Pair<int, string>> node1(pair1);
    Map<int, string> map1(pair2);
    map1.AddNode(node1.pair.first, node1.pair.second);
    ASSERT_EQ(2, map1.getRoot()->pair.first);
    ASSERT_STREQ("bbb", map1.getRoot()->pair.second.c_str());
}

TEST(Map, Print){
    Pair<int, string> pair1(1, "aaa");
    Map<int, string> map1(pair1);
    ASSERT_ANY_THROW( map1.PrintTree());
}

TEST(Map, Begin){
    Pair<int, string> pair2(2, "bbb");
    //Pair<int, string> pair1(1, "aaa");
    Map<int, string> map1(pair2);
    Map<int, string>::Iterator it = map1.begin();
    ASSERT_EQ(2, it->pair.first);
    ASSERT_STREQ("bbb", it->pair.second.c_str());
}

TEST(Map, End){
    Pair<int, string> pair2(2, "bbb");
    Pair<int, string> pair1(1, "aaa");
    Map<int, string> map1(pair1);
    map1.AddNode(pair2.first, pair2.second);
    Map<int, string>::Iterator it = map1.end();
    ASSERT_EQ(2, it->pair.first);
    ASSERT_STREQ("bbb", it->pair.second.c_str());
}

TEST(MapIt, Operators){
    Pair<int, string> pair1(1, "aaa");
    Pair<int, string> pair2(2, "bbb");
    Pair<int, string> pair3(3, "ccc");
    Map<int, string> map1(pair1);
    map1.AddNode(pair2.first, pair2.second);
    map1.AddNode(pair3.first, pair3.second);
    Map<int, string>::Iterator it = map1.begin();
    ASSERT_EQ(1, (it++)->pair.first);
    ASSERT_STREQ("aaa", (--it)->pair.second.c_str());

    ASSERT_EQ(2, (++it)->pair.first);
    ASSERT_STREQ("bbb", (it--)->pair.second.c_str());
}

TEST(MapIT, OperatorsLAB){
    Pair<int, string> pair1(6, "aaa");
    Pair<int, string> pair2(8, "bbb");
    Pair<int, string> pair3(9, "ccc");
    Pair<int, string> pair4(5, "ddd");
    Pair<int, string> pair5(3, "eee");

    Map<int, string> map1(pair1);
    map1.AddNode(pair2.first, pair2.second);
    map1.AddNode(pair3.first, pair3.second);
    map1.AddNode(pair4.first, pair4.second);
    map1.AddNode(pair5.first, pair5.second);
    Map<int, string>::Iterator it = map1.begin();

    ASSERT_EQ(3, (it++)->pair.first);
    ASSERT_STREQ("eee", (--it)->pair.second.c_str());

    ASSERT_EQ(5, (++it)->pair.first);
    ASSERT_STREQ("ddd", (it--)->pair.second.c_str());

    it++;
    ASSERT_EQ(5, it->pair.first);
    ASSERT_STREQ("ddd", it->pair.second.c_str());

    it++;
    ASSERT_EQ(6, it->pair.first);
    ASSERT_STREQ("aaa", it->pair.second.c_str());

    it++;
    ASSERT_EQ(8, it->pair.first);
    ASSERT_STREQ("bbb", it->pair.second.c_str());
}

TEST(Map, Copyconstrcutor){
    Pair<int, string> pair1(1, "aaa");
    Map<int, string> map1(pair1);

    Map<int, string> map2(map1);
    Map<int, string> map3 = map1;

    ASSERT_EQ(1, map2.getRoot()->pair.first);
    ASSERT_STREQ("aaa", map2.getRoot()->pair.second.c_str());

    ASSERT_EQ(1, map3.getRoot()->pair.first);
    ASSERT_STREQ("aaa", map3.getRoot()->pair.second.c_str());
    }

int main(int argc, _TCHAR *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}