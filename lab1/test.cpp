#include "astroid.h"
#include "gtest/gtest.h"
#include <cmath>

//тест конструкторов
TEST(AstroidConstructor, DefaultConstructor) {
    Lab::Astroid a1, a2(3);
    ASSERT_EQ(1, a1.getR());
    ASSERT_EQ(3, a2.getR());
    ASSERT_ANY_THROW(Lab::Astroid a(-3));
}

//тест других методов
TEST(AstroidMethods, Setters) {
    Lab::Astroid a1;
    a1.setR(1);
    ASSERT_EQ(1, a1.getR());
    ASSERT_ANY_THROW(a1.setR(-1));
}

TEST(AstroidMethods, Parameters) {
    Lab::Astroid a1;
    const double err = 0.00001;
    ASSERT_NEAR(3.0 / 8.0 * M_PI * 4 * 4, a1.area(), err);
    ASSERT_NEAR(24, a1.curve_len(), err);

    ASSERT_NEAR(1, a1.init_angle(1), err);
    ASSERT_ANY_THROW(a1.init_angle(3));

    ASSERT_NEAR(3.0 / 2.0 * 4 * 4 * sin(2.0 * 1), a1.curve_rad(1), err);
    ASSERT_NEAR(3.0 / 2.0 * 4 * 4 * sin(1) * sin(1), a1.arc_len(1), err);
    ASSERT_NEAR(4 * cos(1) * cos(1) * cos(1), a1.x_of_t(1), err);
    ASSERT_NEAR(4 * sin(1) * sin(1) * sin(1), a1.y_of_t(1), err);

    ASSERT_NEAR(pow(pow(4.0, 2.0 / 3.0) - pow(1, 2.0 / 3.0), 3.0 / 2.0), a1.y_of_x(1), err);
    ASSERT_ANY_THROW(a1.y_of_x(10));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
