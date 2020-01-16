/*
** EPITECH PROJECT, 2019
** Trade
** File description:
** Parsing.cpp
*/

#include <sstream>
#include <iterator>
#include <algorithm>
#include "Settings.hpp"

size_t parser::Settings::countWords(const std::string &input) const
{
    std::istringstream sstream;
    std::size_t count;

    sstream.rdbuf()->pubsetbuf(const_cast<char *>(input.c_str()),
    input.length());
    count = std::distance(std::istream_iterator<std::string>(sstream),
    std::istream_iterator<std::string>());
    if (count == 3)
        return parser::SUCCESS;
    return parser::FAILURE;
}

bool parser::Settings::lookTileTypeValue(PAIR_STR &tmp, const int &i) const
{
    if (i == 1 and tmp.first.compare("settings") != 0)
        return parser::FAILURE;
    if (i == 2 and tmp.first != "timebank" and tmp.first != "time_per_move"
    and tmp.first != "player_names" and tmp.first != "your_bot"
    and tmp.first != "candle_interval" and tmp.first != "candles_total"
    and tmp.first != "candles_given" and tmp.first != "initial_stack"
    and tmp.first != "transaction_fee_percent" and tmp.first != "candle_format")
            return parser::FAILURE;
    else if (i == 2)
        tmp.second.assign(tmp.first);
    if ((i == 3 and tmp.second == "your_bot"
    and stringToNumber<int>(tmp.first) != 0)
    or (i == 3 and tmp.second == "player_names"
    and stringToNumber<int>(tmp.first) != 0))
        return parser::FAILURE;
    if (i == 3 and tmp.second != "your_bot" and tmp.second != "player_names"
    and tmp.second != "candle_format" and tmp.second != "transaction_fee_percent"
    and stringToNumber<int>(tmp.first) <= 0)
        return parser::FAILURE;
    return parser::SUCCESS;
}

bool parser::Settings::lookFormat(PAIR_STR &tmp, const int &i) const
{
    std::pair<size_t, size_t> boundary(0, 0);
    std::string token("");
    size_t countElem(0);

    while (i == 3 and tmp.second == "candle_format"
    and boundary.second != std::string::npos) {
        boundary.first = tmp.first.find_first_not_of(",");
        boundary.second = tmp.first.find_first_of(",");
        token = tmp.first.substr(boundary.first, boundary.second);
        if (token != "pair" and token != "date" and token != "high"
        and token != "low" and token != "open" and token != "close"
        and token != "volume")
            return parser::FAILURE;
        tmp.first = tmp.first.substr(boundary.second + 1);
        countElem++;
    }
    if (countElem != 7 and countElem != 0)
         return parser::FAILURE;
    return parser::SUCCESS;
}

bool parser::Settings::verifyData(const std::string &input)
{
    std::stringstream ss(input);
    PAIR_STR tmp("", "");

    for (int i(1); ss >> tmp.first; i++)
        if (this->lookTileTypeValue(tmp, i) == FAILURE
        or this->lookFormat(tmp, i) == FAILURE)
            return parser::FAILURE;
    return parser::SUCCESS;
}

bool parser::Settings::fillData(const std::string &input)
{
    std::istringstream sstream(input);
    std::string type("");
    auto fillSettings = [&](const std::string &str) -> void
    {
        if (str == "timebank" or str == "time_per_move"
        or str == "player_names" or str == "your_bot"
        or str == "candle_interval" or str == "candles_total"
        or str == "candles_given" or str == "initial_stack"
        or str == "transaction_fee_percent")
            type.assign(str);
        else if (str != "settings" and str != "candle_format"
        and str != "pair,date,high,low,open,close,volume")
            _settings[type] = str;
    };

    if (!this->countWords(input) or !this->verifyData(input))
            return parser::FAILURE;
    std::for_each(std::istream_iterator<std::string>(sstream),
    std::istream_iterator<std::string>(), fillSettings);
    return parser::SUCCESS;
}
