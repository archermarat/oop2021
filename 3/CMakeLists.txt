cmake_minimum_required(VERSION 3.20)
project(lab4)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab4 main.cpp room.cpp container.h room.h main.h)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test container_test.cpp iterator_test.cpp container.h room.h room.cpp)
target_link_libraries(test gtest_main)
add_test(NAME container_test COMMAND test)
add_test(NAME iterator_test COMMAND test)