#include <gtest/gtest.h>
#include "../src/ui_helper/ansi_color.h"

using namespace std;

const std::string vNullColor = "\033[0m";
const std::string vYellowBold = "\033[31;1m";
const std::string vGreen = "\033[32m";
const std::string vCyan = "\033[36m";
const std::string vNewLine = "\n";

TEST(ColorTest, Colors)
{
    std::string test_message = "This is test message";
    std::string result = AnsiColor::Title(test_message);
    EXPECT_EQ(result, vYellowBold + test_message + vNullColor + vNewLine);

    result = AnsiColor::TextWithLineFeed(test_message);
    EXPECT_EQ(result, vNullColor + test_message + vNewLine);

    result = AnsiColor::Text(test_message);
    std::cout << std::endl;
    EXPECT_EQ(result, vNullColor + test_message);

    result = AnsiColor::ReceivedMessage(test_message);
    EXPECT_EQ(result, vCyan + test_message + vNullColor + vNewLine);

    result = AnsiColor::Message(test_message);
    EXPECT_EQ(result, vGreen + test_message + vNullColor + vNewLine);

}