#pragma once

#include "distribution.hpp"
#include "mix_distribution.hpp"

class EmpiricalDistribution
{
private:
    std::vector<double> samples_;
    std::vector<double> density_;
    size_t size_;
    double min_;
    double max_;

    void calculateDensity();

public:
    // Конструкторы
    EmpiricalDistribution();
    EmpiricalDistribution(const std::vector<double> &samples, size_t size);
    EmpiricalDistribution(const MainDistribution &dist, int n);
    EmpiricalDistribution(const MixDistribution &dist, int n);

    // Конструктор копирования
    EmpiricalDistribution(const EmpiricalDistribution &other);

    // Оператор присваивания
    EmpiricalDistribution &operator=(const EmpiricalDistribution &other);

    // Деструктор
    ~EmpiricalDistribution();

    // Методы
    double pdf(double x) const;
    double expectation() const;
    double variance() const;
    double skewness() const;
    double excessKurtosis() const;
    std::vector<double> generate(int n) const;
    void generateGraphPoints(const std::string &filename) const;
};