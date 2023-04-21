#include "container.h"
#include "gtest/gtest.h"

TEST(TreeConstructor, CopyCounstructor) {
    container::AVLTree<int, int> tmp;
    for(int i = 1; i < 11; i++) {
        tmp.insert(std::make_pair(i, 10*i));
    }
    container::AVLTree<int, int> test(tmp);

    std::ostringstream output_buffer1, output_buffer2;
    tmp.inorder(tmp.GetRoot(), output_buffer1);
    std::cout << std::endl;
    tmp.inorder(test.GetRoot(), output_buffer2);

    ASSERT_EQ(output_buffer1.str() ,output_buffer2.str());
}

TEST(TreeConstructor, MoveCounstructor) {
    std::ostringstream output_buffer1, output_buffer2;
    container::AVLTree<int, int> tmp;
    for(int i = 1; i < 11; i++) {
        tmp.insert(std::make_pair(i, 10*i));
    }
    tmp.inorder(tmp.GetRoot(), output_buffer1);
    container::AVLTree<int, int> test(std::move(tmp));
    std::cout << std::endl;
    tmp.inorder(test.GetRoot(), output_buffer2);
    ASSERT_STREQ(output_buffer1.str().c_str(),"1. 10 2. 20 3. 30 4. 40 5. 50 6. 60 7. 70 8. 80 9. 90 10. 100 ");
}

TEST(TreeMethods, CopyOperator) {
    container::AVLTree<int, int> tmp;
    for(int i = 1; i < 11; i++) {
        tmp.insert(std::make_pair(i, 10*i));
    }
    container::AVLTree<int, int> test;
    test = tmp;

    std::ostringstream output_buffer1, output_buffer2;
    tmp.inorder(tmp.GetRoot(), output_buffer1);
    std::cout << std::endl;
    tmp.inorder(test.GetRoot(), output_buffer2);
    ASSERT_EQ(output_buffer1.str() ,output_buffer2.str());
}

TEST(TreeMethods, MoveOperator) {
    std::ostringstream output_buffer1, output_buffer2;
    container::AVLTree<int, int> tmp;
    for(int i = 1; i < 11; i++) {
        tmp.insert(std::make_pair(i, 10*i));
    }
    tmp.inorder(tmp.GetRoot(), output_buffer1);
    std::cout << std::endl;

    container::AVLTree<int, int> test = std::move(tmp);
    tmp.inorder(test.GetRoot(), output_buffer2);

    ASSERT_STREQ(output_buffer2.str().c_str(),"1. 10 2. 20 3. 30 4. 40 5. 50 6. 60 7. 70 8. 80 9. 90 10. 100 ");
}

TEST(ContainerMethods, Emplace) {
    container::MyContainer<int, int *> test;
    int first = 1, num = 100;
    int *second = &num;
    auto it = test.emplace(std::make_pair(first, second));
    ASSERT_EQ(first, (*it).first);
    ASSERT_EQ(second, (*it).second);
    ASSERT_ANY_THROW(test.emplace(std::make_pair(first, second)));
}

TEST(ContainerMethods, Find) {
    container::MyContainer<int, int *> test;
    int first = 1, num = 100;
    int *second = &num;
    auto it = test.emplace(std::make_pair(first, second));
    ASSERT_EQ(first, (*test.find(first)).first);
    ASSERT_EQ(second, (*test.find(first)).second);
    ASSERT_EQ(nullptr, test.find(2));
}

TEST(ContainerMethods, Erase) {
    container::MyContainer<int, int *> test;
    int first = 1, num = 100;
    int *second = &num;
    auto it = test.emplace(std::make_pair(first, second));
    test.erase(it);
    ASSERT_EQ(nullptr, test.find(first));
}

//TEST(ContainerMethods, Print) {
//    container::MyContainer<int, int> test;
//    int num1 = 100, num2 = 200, num3 = 300;
//    //int *second1 = &num1, *second2 = &num2, *second3 = &num3;
//    test.emplace(std::make_pair(1, num1));
//    test.emplace(std::make_pair(2, num2));
//    test.emplace(std::make_pair(3, num3));
//
//    std::ostringstream output_buffer;
//    test.print(output_buffer);
//
//    assert(output_buffer.str() == "1. 1003. 300");
//}

TEST(ContainerMethods, Begin) {
    container::MyContainer<int, int> test;
    int num1 = 100, num2 = 200, num3 = 300;
    test.emplace(std::make_pair(1, num1));
    test.emplace(std::make_pair(2, num2));
    test.emplace(std::make_pair(3, num3));
    auto it = test.begin();
    ASSERT_EQ(1, (*it).first);
    ASSERT_EQ(num1, (*it).second);
}

TEST(ContainerMethods, End) {
    container::MyContainer<int, int> test;
    ASSERT_EQ(test.begin(), test.end());
}

TEST(ContainerMethods, Index) {
    container::MyContainer<int, int*> test;
    int num1 = 100, num2 = 200, num3 = 300;
    test.emplace(std::make_pair(1, &num1));
    test.emplace(std::make_pair(2, &num2));
    test.emplace(std::make_pair(3, &num3));
    ASSERT_EQ(&num1, test[1]);
    ASSERT_EQ(&num2, test[2]);
    ASSERT_EQ(&num3, test[3]);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


