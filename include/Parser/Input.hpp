/*
** EPITECH PROJECT, 2019
** Trade
** File description:
** Input.hpp
*/

#pragma once

#include <unordered_map>
#include <iostream>

namespace parser {

    static const bool SUCCESS = true;
    static const bool FAILURE = false;

    using MAP_STR = std::unordered_map<std::string, std::string>;
    using PAIR_STR = std::pair<std::string, std::string>;

    enum PERIOD {
        EARLY = 0,
        LATE,
    };

    enum CANDLE {
        DATE = 0,
        HIGH,
        LOW,
        OPEN,
        CLOSE,
        VOLUME
    };

    template<typename T>
    T stringToNumber(const std::string &str)
    {
        std::istringstream strStream(str);
        T nb;

        return strStream >> nb ? nb : 0;
    };

    class UserInput {
    public:
        explicit inline UserInput() : _input("") {}
        ~UserInput() = default;
        inline bool readUserInput(void) { return static_cast<bool>(getline(std::cin, _input)); }
        inline std::string getUserInput(void) const { return _input; }
    private:
        std::string _input;
    };

    class IManageInput {
    public:
        virtual ~IManageInput() = default;
        virtual bool fillData(const std::string &input) = 0;
    protected:
        virtual size_t countWords(const std::string &input) const = 0;
        virtual bool verifyData(const std::string &input) = 0;
    };

}
