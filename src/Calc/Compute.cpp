/*
** EPITECH PROJECT, 2019
** Compute.cpp
** File description:
** trade
*/

#include <algorithm>
#include <sstream>
#include <iomanip>
#include "Compute.hpp"

void Compute::computeAverageValue(std::unordered_map<std::string, std::vector<double>> data)
{
    static unsigned int index = 0;

    averageValue[0] = averageValue[0] * index + data["USDT_BTC"][parser::OPEN] + data["USDT_BTC"][parser::CLOSE];
    averageValue[1] = averageValue[1] * index + data["USDT_ETH"][parser::OPEN] + data["USDT_ETH"][parser::CLOSE];
    averageValue[2] = averageValue[2] * index + data["BTC_ETH"][parser::OPEN] + data["BTC_ETH"][parser::CLOSE];
    index += 2;
    averageValue[0] = averageValue[0] / index;
    averageValue[1] = averageValue[1] / index;
    averageValue[2] = averageValue[2] / index;
}

void Compute::computeCandleVariation(std::unordered_map<std::string, std::vector<double>> data)
{
    newCandleVariation[0] = data["USDT_BTC"][parser::CLOSE] - data["USDT_BTC"][parser::OPEN];
    newCandleVariation[1] = data["USDT_ETH"][parser::CLOSE] - data["USDT_ETH"][parser::OPEN];
    newCandleVariation[2] = data["BTC_ETH"][parser::CLOSE] - data["BTC_ETH"][parser::OPEN];
}

void Compute::setExtremeValue(std::unordered_map<std::string, std::vector<double>> data)
{
    std::array<double, 4> usdtBtc({lowestValue[0], highestValue[0], data["USDT_BTC"][parser::OPEN], data["USDT_BTC"][parser::CLOSE]});
    std::array<double, 4> usdtEth({lowestValue[1], highestValue[1], data["USDT_ETH"][parser::OPEN], data["USDT_ETH"][parser::CLOSE]});
    std::array<double, 4> btcEth({lowestValue[2], highestValue[2], data["BTC_ETH"][parser::OPEN], data["BTC_ETH"][parser::CLOSE]});

    if (lowestValue[0] == 0 && lowestValue[1] == 0 && lowestValue[2] == 0) {
        lowestValue[0] = *std::min_element(usdtBtc.begin() + 2, usdtBtc.end());
        lowestValue[1] = *std::min_element(usdtEth.begin() + 2, usdtEth.end());
        lowestValue[2] = *std::min_element(btcEth.begin() + 2, btcEth.end());
    } else {
        lowestValue[0] = *std::min_element(usdtBtc.begin(), usdtBtc.end());
        lowestValue[1] = *std::min_element(usdtEth.begin(), usdtEth.end());
        lowestValue[2] = *std::min_element(btcEth.begin(), btcEth.end());
    }
    highestValue[0] = *std::max_element(usdtBtc.begin(), usdtBtc.end());
    highestValue[1] = *std::max_element(usdtEth.begin(), usdtEth.end());
    highestValue[2] = *std::max_element(btcEth.begin(), btcEth.end());
}

void Compute::computeBeneficeRate(std::unordered_map<std::string, std::vector<double>> data)
{
    if (data["USDT_BTC"][parser::CLOSE] >= averageValue[0]) {
        if ((highestValue[0] - averageValue[0]) == 0)
            beneficeRate[0] = 0;
        else
            beneficeRate[0] = (data["USDT_BTC"][parser::CLOSE] - averageValue[0]) / (highestValue[0] - averageValue[0]);
    } else {
        if ((lowestValue[0] - averageValue[0]) == 0)
            beneficeRate[0] = 0;
        else
            beneficeRate[0] = (data["USDT_BTC"][parser::CLOSE] - averageValue[0]) / (lowestValue[0] - averageValue[0]) * (-1);
    }
    if (data["USDT_ETH"][parser::CLOSE] >= averageValue[1]) {
        if ((highestValue[1] - averageValue[1]) == 0)
            beneficeRate[1] = 0;
        else
            beneficeRate[1] = (data["USDT_ETH"][parser::CLOSE] - averageValue[1]) / (highestValue[1] - averageValue[1]);
    } else {
        if ((lowestValue[1] - averageValue[1]) == 0)
            beneficeRate[1] = 0;
        else
            beneficeRate[1] = (data["USDT_ETH"][parser::CLOSE] - averageValue[1]) / (lowestValue[1] - averageValue[1]) * (-1);
    }
    if (data["BTC_ETH"][parser::CLOSE] >= averageValue[2]) {
        if ((highestValue[2] - averageValue[2]) == 0)
            beneficeRate[2] = 0;
        else
            beneficeRate[2] = (data["BTC_ETH"][parser::CLOSE] - averageValue[2]) / (highestValue[2] - averageValue[2]);
    } else {
        if ((lowestValue[2] - averageValue[2]) == 0)
            beneficeRate[2] = 0;
        else
            beneficeRate[2] = (data["BTC_ETH"][parser::CLOSE] - averageValue[2]) / (lowestValue[2] - averageValue[2]) * (-1);
    }
}

void Compute::isOccasionToBuy()
{
    if (beneficeRate[0] < -MIN_BENEF_RATE && lastCandleVariation[0] < 0 && newCandleVariation[0] >= 0)
        purchaseOccasion[0] = true;
    else
        purchaseOccasion[0] = false;
    if (beneficeRate[1] < -MIN_BENEF_RATE && lastCandleVariation[1] < 0 && newCandleVariation[1] >= 0)
        purchaseOccasion[1] = true;
    else
        purchaseOccasion[1] = false;
    if (beneficeRate[2] < -MIN_BENEF_RATE && lastCandleVariation[2] < 0 && newCandleVariation[2] >= 0)
        purchaseOccasion[2] = true;
    else
        purchaseOccasion[2] = false;
}

void Compute::isOccasionToSell()
{
    if (beneficeRate[0] > MIN_BENEF_RATE && lastCandleVariation[0] > 0 && newCandleVariation[0] <= 0)
        sellOccasion[0] = true;
    else
        sellOccasion[0] = false;
    if (beneficeRate[1] > MIN_BENEF_RATE && lastCandleVariation[1] > 0 && newCandleVariation[1] <= 0)
        sellOccasion[1] = true;
    else
        sellOccasion[1] = false;
    if (beneficeRate[2] > MIN_BENEF_RATE && lastCandleVariation[2] > 0 && newCandleVariation[2] <= 0)
        sellOccasion[2] = true;
    else
        sellOccasion[2] = false;
}

void Compute::purchaseAction(std::unordered_map<std::string, std::vector<double>> data, std::unordered_map<std::string, double> stacks)
{
    std::ostringstream flux;
    double rate;
    double purchaseQuantity;
    
    if (purchaseOccasion[0] == true) {
        flux.str("");
        flux.clear();
        rate = ((-1) * beneficeRate[0] - MIN_BENEF_RATE) / (1 - MIN_BENEF_RATE) * MAX_PURCHASE_RATE;
        purchaseQuantity = stacks["USDT"] * rate / data["USDT_BTC"][parser::CLOSE];
        flux << std::fixed << std::setprecision(8) << "buy USDT_BTC " << purchaseQuantity;
        std::cout << "test " << flux.str() << std::endl;
        if (purchaseQuantity > 0.0009)
            actionLine = actionLine + ';' + flux.str();
    }
    if (purchaseOccasion[1] == true) {
        flux.str("");
        flux.clear();
        rate = ((-1) * beneficeRate[1] - MIN_BENEF_RATE) / (1 - MIN_BENEF_RATE) * MAX_PURCHASE_RATE;
        purchaseQuantity = stacks["USDT"] * rate / data["USDT_ETH"][parser::CLOSE];
        flux << std::fixed << std::setprecision(8) << "buy USDT_ETH " << purchaseQuantity;
        std::cout << "test " << flux.str() << std::endl;
        if (purchaseQuantity > 0.0009)
            actionLine = actionLine + ';' + flux.str();
    }
    if (purchaseOccasion[2] == true) {
        flux.str("");
        flux.clear();
        rate = ((-1) * beneficeRate[2] - MIN_BENEF_RATE) / (1 - MIN_BENEF_RATE) * MAX_PURCHASE_RATE;
        purchaseQuantity = stacks["BTC"] * rate / data["BTC_ETH"][parser::CLOSE];
        flux << std::fixed << std::setprecision(8) << "buy BTC_ETH " << purchaseQuantity;
        if (purchaseQuantity > 0.0009)
            actionLine = actionLine + ';' + flux.str();
    }
}

void Compute::sellAction(std::unordered_map<std::string, double> stacks)
{
    std::ostringstream flux;
    double rate;
    double sellQuantity;

    if (sellOccasion[0] == true) {
        flux.str("");
        flux.clear();
        rate = (beneficeRate[0] - MIN_BENEF_RATE) / (1 - MIN_BENEF_RATE) * MAX_SELL_RATE;
        sellQuantity = stacks["BTC"] * rate;
        flux << std::fixed << std::setprecision(8) << "sell USDT_BTC " << sellQuantity;
        if (sellQuantity > 0.0009)
            actionLine = actionLine + ';' + flux.str();
    }
    if (sellOccasion[1] == true) {
        flux.str("");
        flux.clear();
        rate = (beneficeRate[1] - MIN_BENEF_RATE) / (1 - MIN_BENEF_RATE) * MAX_SELL_RATE;
        sellQuantity = stacks["ETH"] * rate;
        flux << std::fixed << std::setprecision(8) << "sell USDT_ETH " << sellQuantity;
        if (sellQuantity > 0.0009)
            actionLine = actionLine + ';' + flux.str();
    }
    if (sellOccasion[2] == true) {
        flux.str("");
        flux.clear();
        rate = (beneficeRate[2] - MIN_BENEF_RATE) / (1 - MIN_BENEF_RATE) * MAX_SELL_RATE;
        sellQuantity = stacks["ETH"] * rate;
        flux << std::fixed << std::setprecision(8) << "sell BTC_ETH " << sellQuantity;
        if (sellQuantity > 0.0009)
            actionLine = actionLine + ';' + flux.str();
    }
}

void Compute::prepareAction(std::unordered_map<std::string, std::vector<double>> data, std::unordered_map<std::string, double> stacks)
{
    actionLine.clear();
    purchaseAction(data, stacks);
    sellAction(stacks);
    if (actionLine.empty() == true)
        actionLine = "pass";
    if (actionLine[0] == ';')
        actionLine.erase(actionLine.begin());
    std::cout << actionLine << std::endl;
}

void Compute::updateData(std::unordered_map<std::string, std::vector<double>> data)
{
    computeAverageValue(data);
    setExtremeValue(data);
    lastCandleVariation = newCandleVariation;
    computeCandleVariation(data);
    computeBeneficeRate(data);
    isOccasionToBuy();
    isOccasionToSell();
}
