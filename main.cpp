/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** main.cpp
*/

#include <iomanip>
#include "Compute.hpp"
#include "Settings.hpp"
#include "Data.hpp"

void computations(parser::Data &data, Compute &compute)
{
    if (!data.getActionOrder() and !data.isStacks())
        compute.updateData(data.getChartsCandles());
    if (data.getActionOrder())
        compute.prepareAction(data.getChartsCandles(), data.getStacks());
    // for (auto i : stacks)
    //     std::cout << std::fixed << std::setprecision(8)
    //               << i.first << " " << i.second << std::endl;
    // for (auto i : chartCandle["USDT_ETH"])
    //     std::cout << std::fixed << std::setprecision(8) << i << std::endl;
    // std::cout << std::endl;
}

bool parsing(std::pair<bool, bool> errorParsing)
{
    parser::UserInput userInput;
    parser::Settings settings;
    parser::Data data;
    Compute compute;

    while (userInput.readUserInput()) {
    errorParsing.first = settings.fillData(userInput.getUserInput());
    data = settings.getBotName();
    errorParsing.second = data.fillData(userInput.getUserInput());
    if (!errorParsing.first and !errorParsing.second)
        break;
    if (parser::Data::getCandleNb()
    > static_cast<long>(std::stoi(settings.getSettings()["candles_total"])))
        break;
    if (!errorParsing.first)
        computations(data, compute);
    }
    return parser::SUCCESS;
}

int main(void)
{
    std::pair<bool, bool> errorParsing(true, true);

    if (!parsing(errorParsing))
        return 84;
    return 0;
}
