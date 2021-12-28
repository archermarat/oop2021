#include "vector.h"
#include "gtest/gtest.h"
#include <vector>
//#include "cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest.h"

TEST(VectorConstructor, DefaultConstructor) {
    lab3::Vector a;
    ASSERT_EQ(0, a.getSize());
    ASSERT_EQ(3, a.getCapacity());
}

TEST(VectorConstructor, NumConstructor) {
    lab3::Vector a(5);
    ASSERT_EQ(5, a.getElem(0));
    ASSERT_EQ(1, a.getSize());
    ASSERT_EQ(3, a.getCapacity());
}

TEST(VectorConstructor, MasConstructor) {
    int mas[] = {-555, 323, -453, 26, 0, 664 , 1213};
    lab3::Vector a(mas, sizeof(mas)/sizeof(int));
    ASSERT_EQ(7, a.getSize());
    ASSERT_EQ(10, a.getCapacity());
    for(int i = 0; i < a.getSize(); i++) {
        ASSERT_EQ(mas[i], a.getElem(i));
    }
}

TEST(VectorConstructor, CopyConstructor) {
    int mas[] = {-555, 323, -453, 26, 0, 664 , 1213};
    lab3::Vector b(mas, sizeof(mas)/sizeof(int));
    lab3::Vector a(b);
    ASSERT_EQ(7, a.getSize());
    ASSERT_EQ(10, a.getCapacity());
    for(int i = 0; i < a.getSize(); i++) {
        ASSERT_EQ(mas[i], a.getElem(i));
    }
}

TEST(VectorConstructor, MoveConstructor) {
    int mas[] = {-555, 323, -453, 26, 0, 664 , 1213};
    size_t size = sizeof(mas)/sizeof(int);
    std::vector<lab3::Vector> a;
    a.push_back(lab3::Vector(mas, size));
    ASSERT_EQ(7, a[0].getSize());
    ASSERT_EQ(10, a[0].getCapacity());
    for(int i = 0; i < a[0].getSize(); i++) {
        ASSERT_EQ(mas[i], a[0].getElem(i));
    }
}

TEST(VectorMethods, Reserve) {
    lab3::Vector a;
    a.reserve(10);
    ASSERT_EQ(10, a.getCapacity());
    lab3::Vector b(nullptr, 0);
}

TEST(VectorMethods, Push) {
    lab3::Vector a;
    a.push(1);
    a.push(2);
    a.push(3);
    a.push(4);
    ASSERT_EQ(1, a[0]);
    ASSERT_EQ(2, a[1]);
    ASSERT_EQ(3, a[2]);
    ASSERT_EQ(4, a[3]);
    ASSERT_EQ(6, a.getCapacity());
}

TEST(VectorMethods, Sort) {
    int mas[] = {-555, 323, -453, 26, 0, 664 , 1213};
    lab3::Vector a(mas, sizeof(mas)/sizeof(int));
    a.sort();
    for(int i = 0; i < a.getSize() - 1; ++i) {
        ASSERT_GE(a[i], a[i+1]);
    }
    lab3::Vector b;
    ASSERT_ANY_THROW(b.sort());
}

TEST(VectorMethods, FindMax) {
    int mas[] = {-555, 323, -453, 26, 0, 664 , 1213};
    lab3::Vector a(mas, sizeof(mas)/sizeof(int));
    ASSERT_EQ(1213, a.findMax());
    lab3::Vector b;
    ASSERT_ANY_THROW(b.findMax());
}

TEST(VectorMethods, Index) {
    int mas[] = {-555, 323, -453, 26, 0, 664 , 1213};
    lab3::Vector a(mas, sizeof(mas)/sizeof(int));
    ASSERT_EQ(323, a[1]);
    ASSERT_ANY_THROW(a[-1]);
}

TEST(VectorMethods, IndexConst) {
    int mas[] = {-555, 323, -453, 26, 0, 664 , 1213};
    lab3::Vector const a(mas, sizeof(mas)/sizeof(int));
    ASSERT_EQ(323, a[1]);
    ASSERT_ANY_THROW(a[-1]);
}

TEST(VectorMethods, CopyOperator) {
    int mas[] = {-555, 323, -453, 26, 0, 664 , 1213};
    lab3::Vector a(mas, sizeof(mas)/sizeof(int));
    lab3::Vector b;
    b = a;
    for(int i = 0; i < a.getSize(); ++i) {
        ASSERT_EQ(a[i], b[i]);
    }
    ASSERT_EQ(a.getSize(), b.getSize());
    ASSERT_EQ(a.getCapacity(), b.getCapacity());
    a.push(222);
    ASSERT_EQ(222, a[7]);
    b.push(111);
    ASSERT_EQ(111, b[7]);
}

TEST(VectorMethods, MoveOperator) {
    int mas[] = {-555, 323, -453, 26, 0, 664 , 1213};
    //std::vector<lab3::Vector> a;
    lab3::Vector a;
    //a.emplace_back(1);
    a = lab3::Vector( mas, sizeof(mas)/sizeof(int));
    for(int i = 0; i < a.getSize(); ++i) {
        ASSERT_EQ(a[i], mas[i]);
    }
    ASSERT_EQ(a.getSize(), 7);
    ASSERT_EQ(a.getCapacity(), 10);
}

TEST(VectorMethods, AddOperator) {
    int mas[] = {1, 323, -453, 26, 0, 664 , 1213};
    lab3::Vector b(3);
    lab3::Vector c(mas, sizeof(mas)/sizeof(int));
    lab3::Vector a;
    a = c + b;
    if(b.getSize() < c.getSize()) {
        for(size_t i = 0; i < b.getSize(); ++i) {
            ASSERT_EQ(a[i], b[i] + c[i]);
        }
        for(size_t i = b.getSize(); i < c.getSize(); ++i) {
            ASSERT_EQ(a[i], c[i]);
        }
        ASSERT_EQ(a.getSize(), c.getSize());
    } else {
        for(size_t i = 0; i < c.getSize(); ++i) {
            ASSERT_EQ(a[i], b[i] + c[i]);
        }
        for(size_t i = c.getSize(); i < b.getSize(); ++i) {
            ASSERT_EQ(a[i], b[i]);
        }
        ASSERT_EQ(a.getSize(), b.getSize());
    }
}

TEST(VectorMethods, OutOperator) {
    int mas[] = {1, 323, -453, 26, 0, 664 , 1213};
    std::ostringstream out;
    lab3::Vector a(mas, sizeof(mas)/sizeof(int));
    out << a;
    std::cout << a;
    EXPECT_EQ("\nCurrent Size = 7\n{}\n", out.str());
}

TEST(VectorMethods, InOperator) {
    lab3::Vector a;
    std::istringstream in;
    std::string string = "4 2 3 4 5 ";
    in.str(string);
    in >> a;
    EXPECT_EQ("4 2 3 4 5 ", in.str());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}