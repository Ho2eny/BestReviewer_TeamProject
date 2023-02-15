#ifndef ANSI_COLOR_H_
#define ANSI_COLOR_H_

#include <iostream>
#include <string>
#include <sstream>

class AnsiColor
{
public:
    std::string TextWithLineFeed(std::string str)
    {
        std::stringstream ss;
        ss << vNullColor << str << std::endl;
        std::cout << ss.str();
        return ss.str();
    }

    std::string Text(std::string str)
    {
        std::stringstream ss;
        ss << vNullColor << str;
        std::cout << ss.str();
        return ss.str();
    }

    std::string ReceivedMessage(std::string str)
    {
        std::stringstream ss;
        ss << vCyan << str << vNullColor << std::endl;
        std::cout << ss.str();
        return ss.str();
    }

    std::string Message(std::string str)
    {
        std::stringstream ss;
        ss << vGreen << str << vNullColor << std::endl;
        std::cout << ss.str();
        return ss.str();
    }

    std::string Title(std::string str)
    {
        std::stringstream ss;
        ss << vYellowBold << str << vNullColor << std::endl;
        std::cout << ss.str();
        return ss.str();
    }

    std::string Important(std::string str)
    {
        std::stringstream ss;
        ss << vMagent << str << vNullColor;
        std::cout << ss.str();
        return ss.str();
    }

    std::string ImportantWithLineFeed(std::string str)
    {
        std::stringstream ss;
        ss << vMagent << str << vNullColor << std::endl;
        std::cout << ss.str();
        return ss.str();
    }

    std::string ErrorWithLineFeed(std::string str)
    {
        std::stringstream ss;
        ss << vRed << "[Warning] " << str << vNullColor << std::endl;
        std::cout << ss.str();
        return ss.str();
    }

private:
    const std::string vNullColor = "\033[0m";
    const std::string vRed = "\033[31m";
    const std::string vYellowBold = "\033[33;1m";
    const std::string vGreen = "\033[32m";
    const std::string vCyan = "\033[36m";
    const std::string vMagent = "\033[95m";
};

#endif
