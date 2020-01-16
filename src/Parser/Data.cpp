/*
** EPITECH PROJECT, 2019
** Trade
** File description:
** Data.cpp
*/

#include <algorithm>
#include <sstream>
#include <iterator>
#include "Data.hpp"

long parser::Data::_candleNb_ = 1;

size_t parser::Data::countWords(const std::string &input) const
{
    std::istringstream sstream;
    std::size_t count(0);

    sstream.rdbuf()->pubsetbuf(const_cast<char *>(input.c_str()),
    input.length());
    count = std::distance(std::istream_iterator<std::string>(sstream),
    std::istream_iterator<std::string>());
    if (count == 3 or count == 4)
        return count;
    return parser::FAILURE;
}

template<>
double parser::stringToNumber<double>(const std::string &str)
{
    std::istringstream strStream(str);
    double nb;

    return strStream >> nb ? nb : -1;
};

bool parser::Data::checkFillChart(PAIR_STR &dataElem)
{
    PAIR_STR token("", "");
    PAIR_STR delimiter(";", ",");
    std::tuple<size_t, size_t> checkError(0, 0);
    std::string pairName("");

    _candleNb_++;
    _chartCandle.clear();
    _isStacks = false;
    for (size_t posCandle(0);
    posCandle != std::string::npos;) {
        std::get<0>(checkError) = 0;
        std::get<1>(checkError) = 0;
        posCandle = dataElem.first.find(delimiter.first);
        token.first = dataElem.first.substr(0, posCandle);
        dataElem.first.erase(0, posCandle + delimiter.first.length());
        for (size_t posName(0); posName != std::string::npos;) {
            posName = token.first.find(delimiter.second);
            token.second = token.first.substr(0, posName);
            if ((std::get<0>(checkError) == 0 and token.second != "BTC_ETH"
            and token.second != "USDT_ETH" and token.second != "USDT_BTC")
            or (std::get<0>(checkError) > 0
            and stringToNumber<double>(token.second) < 0))
                return parser::FAILURE;
            else if (token.second == "BTC_ETH" or token.second == "USDT_ETH"
            or token.second == "USDT_BTC")
                pairName = token.second;
            else
                _chartCandle[pairName].
                push_back(stringToNumber<double>(token.second));
            token.first.erase(0, posName + delimiter.second.length());
            std::get<0>(checkError)++;
            std::get<1>(checkError)++;
        }
        if (std::get<1>(checkError) != 7)
            return parser::FAILURE;
    }
    return parser::SUCCESS;
}

bool parser::Data::checkFillStacks(PAIR_STR &dataElem)
{
    PAIR_STR token("", "");
    PAIR_STR delimiter(",", ":");
    std::tuple<size_t, size_t, size_t> checkError(0, 0, 0);
    std::string pairName("");

    _isStacks = true;
    for (size_t posStacks(0); posStacks != std::string::npos;) {
        std::get<1>(checkError) = 0;
        std::get<2>(checkError) = 0;
        posStacks = dataElem.first.find(delimiter.first);
        token.first = dataElem.first.substr(0, posStacks);
        dataElem.first.erase(0, posStacks + delimiter.first.length());
        for (size_t posCurrency(0); posCurrency != std::string::npos;) {
            posCurrency = token.first.find(delimiter.second);
            token.second = token.first.substr(0, posCurrency);
            if ((std::get<2>(checkError) == 0 and token.second != "BTC"
            and token.second != "ETH" and token.second != "USDT")
            or (std::get<2>(checkError) > 0
            and stringToNumber<double>(token.second) < 0))
                return parser::FAILURE;
            else if (token.second == "BTC" or token.second == "USDT"
            or token.second == "ETH")
                pairName = token.second;
            else
                _stacks[pairName] = stringToNumber<double>(token.second);
            token.first.erase(0, posCurrency + delimiter.second.length());
            std::get<1>(checkError)++;
            std::get<2>(checkError)++;
        }
        if (std::get<1>(checkError) != 2)
            return parser::FAILURE;
        std::get<0>(checkError)++;
    }
    if (std::get<0>(checkError) != 3)
        return parser::FAILURE;
    return parser::SUCCESS;
}

bool parser::Data::verifyData(const std::string &input)
{
    std::stringstream ss(input);
    PAIR_STR dataElem("", "");

    for (int i(1); ss >> dataElem.first; i++) {
        if ((i == 1 and dataElem.first != "update")
        or (i == 2 and dataElem.first != "game" and dataElem.first != _botName)
        or (i == 3 and dataElem.first != "stacks"
        and dataElem.first != "next_candles"))
            return parser::FAILURE;
        else if (i == 3)
            dataElem.second = dataElem.first;
        if ((i == 4 and dataElem.second == "next_candles"
        and !this->checkFillChart(dataElem)) or (i == 4 and
        dataElem.second == "stacks" and !this->checkFillStacks(dataElem)))
            return parser::FAILURE;
    }
    return parser::SUCCESS;
}

bool parser::Data::fillData(const std::string &input)
{
    if (this->countWords(input) == 3
    and input.find("action") != std::string::npos
    and input.find("order") != std::string::npos
    and input.find_first_of("0123456789") != std::string::npos) {
        _actionTime
        = std::stoll(input.substr(input.find_last_not_of("0123456789") + 1));
        _isActionOrder = true;
    }
    else if (this->countWords(input) != 4 or !this->verifyData(input))
        return parser::FAILURE;
    else
        _isActionOrder = false;
    return parser::SUCCESS;
}
