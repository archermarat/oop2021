//#include "container.h"
//#include "gtest/gtest.h"
//
//TEST(IteratorContainer, Container) {
//    container::MyContainer<int, int> test;
//    int num1 = 100, num2 = 200, num3 = 300;
//    test.emplace(std::make_pair(1, num1));
//    test.emplace(std::make_pair(2, num2));
//    test.emplace(std::make_pair(3, num3));
//    container::iterator<int, int> it(test.find(1));
//    ASSERT_EQ((*it).first, 1);
//    ASSERT_EQ((*it).second, num1);
//}
//
//TEST(IteratorMethods, ПостфиксныйИнкримент) {
//    container::MyContainer<int, int> test;
//    int num1 = 100, num2 = 200, num3 = 300;
//    test.emplace(std::make_pair(1, num1));
//    test.emplace(std::make_pair(2, num2));
//    test.emplace(std::make_pair(3, num3));
//    container::iterator<int, int> it = ;
//    it++;
//    ASSERT_EQ((*it).first, 2);
//    ASSERT_EQ((*it).second, num2);
//}
//
