/*
** EPITECH PROJECT, 2019
** Trade
** File description:
** Data.hpp
*/

#pragma once

#include <deque>
#include <vector>
#include "Input.hpp"

namespace parser {

    using MAP_VECT = std::unordered_map<std::string, std::vector<double>>;

    class Data : public parser::IManageInput {
    public:
        explicit inline Data() : _botName(""), _chartCandle(0), _stacks(0),
        _actionTime(0), _isActionOrder(false), _isStacks(false) {
            _candleNb_ = 0;
        };
        ~Data() = default;
        bool fillData(const std::string &input) final;
        inline void operator=(const std::string botName) { _botName = botName; }
        inline std::unordered_map<std::string, double> getStacks(void)
        { return _stacks; }
        inline long long getActionTime(void) { return _actionTime; }
        inline MAP_VECT getChartsCandles(void) { return _chartCandle; }
        inline static long getCandleNb(void) { return _candleNb_; }
        inline bool getActionOrder(void) { return _isActionOrder; }
        inline bool isStacks(void) { return _isStacks; }
    private:
        size_t countWords(const std::string &input) const final;
        bool verifyData(const std::string &input) final;
        bool checkFillChart(PAIR_STR &dataElem);
        bool checkFillStacks(PAIR_STR &dataElem);
        bool isPosNum(const std::string &str) const;

        std::string _botName;
        MAP_VECT _chartCandle;
        std::unordered_map<std::string, double> _stacks;
        long long _actionTime;
        bool _isActionOrder;
        bool _isStacks;
        static long _candleNb_;
    };
}
