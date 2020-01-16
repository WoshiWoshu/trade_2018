/*
** EPITECH PROJECT, 2019
** Trade
** File description:
** Flows.hpp
*/

#pragma once

#include "Input.hpp"

namespace parser {

    class Settings : public parser::IManageInput {
    public:
        explicit inline Settings() : _settings{{"timebank", "10000"},
        {"time_per_move", "100"}, {"player_names", "player0"},
        {"your_bot", "player0"}, {"candle_interval", "1800"},
        {"candles_total", "720"}, {"candles_given", "336"},
        {"initial_stack", "1000"}, {"transaction_fee_percent", "0.2"}} {}
        ~Settings() = default;
        bool fillData(const std::string &input) final;
        inline MAP_STR getSettings(void) { return _settings; }
        inline std::string getBotName(void) { return _settings["your_bot"]; }
    private:
        size_t countWords(const std::string &input) const final;
        bool verifyData(const std::string &input) final;
        bool lookTileTypeValue(PAIR_STR &tmp, const int &i) const;
        bool lookFormat(PAIR_STR &tmp, const int &i) const;

        MAP_STR _settings;
    };

}
