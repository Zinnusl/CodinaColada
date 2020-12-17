// CodingColadaTests.cpp : Main entry point for unit tests
//

/*

#include "..\CodingColada\src\App.h"

#include <sstream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"


using std::cout;
using std::endl;

class AppTest : public ::testing::Test {};

*/

/*class MockEngine : public IEngine
{
    void CreateWindow(const int x, const int y) override
    {
        // Ich tu nur so als waere ich eine Engine
        // hier koennte man mit google_mock testen, ob der CreateWindow aufruft, oder so
    }
};*/

/*
class MockEngine : public IEngine
{
public:
   // MOCK_METHOD(void, CreateWindow, (const int, const int), (override));
};

TEST_F(AppTest, runOutputsANonEmptyString)
{
    using ::testing::AtLeast;
    using ::testing::_;

    std::stringstream ss;
    //std::unique_ptr<IEngine> mock_engine = std::make_unique<MockEngine>();
    //App a(ss, std::move(mock_engine));

    //EXPECT_CALL(*mock_engine, CreateWindow(_, _))
    //    .Times(AtLeast(1));

    //a.run();
        
    EXPECT_GT(ss.str().length(), 0);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}*/