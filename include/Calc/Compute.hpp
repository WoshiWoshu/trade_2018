/*
** EPITECH PROJECT, 2019
** Compute.hpp
** File description:
** trade
*/

#ifndef COMPUTE_HPP_
#define COMPUTE_HPP_

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include "Input.hpp"

#define MIN_BENEF_RATE 0.4
#define MAX_PURCHASE_RATE 0.3
#define MAX_SELL_RATE 0.6

class Compute {
public:
    Compute() : averageValue{0}, lastCandleVariation{0}, newCandleVariation{0}, lowestValue{0}, highestValue{0}, beneficeRate{0}, purchaseOccasion{false}, sellOccasion{false} {};
    ~Compute() {};
    void computeAverageValue(std::unordered_map<std::string, std::vector<double>> data);
    void computeCandleVariation(std::unordered_map<std::string, std::vector<double>> data);
    void setExtremeValue(std::unordered_map<std::string, std::vector<double>> data);
    void computeBeneficeRate(std::unordered_map<std::string, std::vector<double>> data);
    void isOccasionToBuy();
    void isOccasionToSell();
    void purchaseAction(std::unordered_map<std::string, std::vector<double>> data, std::unordered_map<std::string, double> stacks);
    void sellAction(std::unordered_map<std::string, double> stacks);
    void prepareAction(std::unordered_map<std::string, std::vector<double>> data, std::unordered_map<std::string, double> stacks);
    void updateData(std::unordered_map<std::string, std::vector<double>> data);
private:
    std::array<double, 3> averageValue;
    std::array<double, 3> lastCandleVariation;
    std::array<double, 3> newCandleVariation;
    std::array<double, 3> lowestValue;
    std::array<double, 3> highestValue;
    std::array<double, 3> beneficeRate;
    std::array<bool, 3> purchaseOccasion;
    std::array<bool, 3> sellOccasion;
    std::string actionLine;
};

#endif /* !COMPUTE_HPP_ */
