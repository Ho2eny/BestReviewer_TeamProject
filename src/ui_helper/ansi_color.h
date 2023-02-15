#ifndef ANSI_COLOR_H_
#define ANSI_COLOR_H_

#include <iostream>
#include <string>
#include <sstream>

class AnsiColor
{
public:
    static std::string TextWithLineFeed(std::string str)
    {
        std::stringstream ss;
        ss << vNullColor << str << std::endl;
        std::cout << ss.str();
        return ss.str();
    }

    static std::string Text(std::string str)
    {
        std::stringstream ss;
        ss << vNullColor << str;
        std::cout << ss.str();
        return ss.str();
    }

    static std::string ReceivedMessage(std::string str)
    {
        std::stringstream ss;
        ss << vCyan << str << vNullColor << std::endl;
        std::cout << ss.str();
        return ss.str();
    }

    static std::string Message(std::string str)
    {
        std::stringstream ss;
        ss << vGreen << str << vNullColor << std::endl;
        std::cout << ss.str();
        return ss.str();
    }

    static std::string Title(std::string str)
    {
        std::stringstream ss;
        ss << vYellowBold << str << vNullColor << std::endl;
        std::cout << ss.str();
        return ss.str();
    }

private:
    static const std::string vNullColor;
    static const std::string vYellowBold;
    static const std::string vGreen;
    static const std::string vCyan;
};

const std::string AnsiColor::vNullColor = "\033[0m";
const std::string AnsiColor::vYellowBold = "\033[31;1m";
const std::string AnsiColor::vGreen = "\033[32m";
const std::string AnsiColor::vCyan = "\033[36m";

#endif