// CodingColadaTests.cpp : Main entry point for unit tests
//

#include "..\CodingColada\App.h"

#include "gtest/gtest.h"
#include <sstream>

using std::cout;
using std::endl;

class AppTest : public ::testing::Test {};

TEST_F(AppTest, runOutputsANonEmptyString)
{
    std::stringstream ss;
    App a(ss);

    a.run();

    EXPECT_GT(ss.str().length(), 0);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}