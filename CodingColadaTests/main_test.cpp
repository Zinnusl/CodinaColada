// CodingColadaTests.cpp : Main entry point for unit tests
//



#include "..\CodingColada\src\Engine.h"

#include <sstream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"


using std::cout;
using std::endl;

class AppTest : public ::testing::Test {};
class EngineTest : public ::testing::Test {};



class MockRenderer : public IRenderer
{
public:
    MOCK_METHOD(void, Draw, (), ());
    MOCK_METHOD(void, AddShape, (std::unique_ptr<IShape>), ());
    MOCK_METHOD(void, OnClick, (Vector2), ());
    MOCK_METHOD(void, CreateWindow, (int, int, IInput&), ());
};

class MockInput : public IInput
{
public:
    MOCK_METHOD(void, RegisterWindow, (void*), ());
    MOCK_METHOD(void, ProcessInput, (), ());
    MOCK_METHOD(bool, GetKeyDown, (int), ());
    MOCK_METHOD(bool, GetKey, (int), ());
    MOCK_METHOD(void, AddHandler, (int, IInput::handlerCallbackType), ());
};

TEST_F(EngineTest, EngineCreatesWindowExactlyOnce)
{
    using ::testing::Exactly;
    using ::testing::_;

    auto mock_renderer = std::make_unique<MockRenderer>();
    auto mock_input = std::make_unique<MockInput>();
    Engine unit_under_test(*mock_renderer, *mock_input);

    EXPECT_CALL(*mock_renderer, CreateWindow(_, _, _))
        .Times(Exactly(1));

    unit_under_test.StopGame();
    unit_under_test.StartGame();
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}