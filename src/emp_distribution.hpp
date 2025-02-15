#pragma once

#include "distribution.hpp"
#include "mix_distribution.hpp"
#include "interface.hpp"

class EmpiricalDistribution : public IDistribution, public IPersistent
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
    EmpiricalDistribution(const IDistribution &dist, int n);
    EmpiricalDistribution(const MixDistribution<MainDistribution, MainDistribution> &dist, int n);

    // Конструктор копирования
    EmpiricalDistribution(const EmpiricalDistribution &other);

    // Оператор присваивания
    EmpiricalDistribution &operator=(const EmpiricalDistribution &other);

    // Деструктор
    ~EmpiricalDistribution();

    // Методы
    double pdf(double x) const override;
    double expectation() const override;
    double variance() const override;
    double skewness() const override;
    double excessKurtosis() const override;
    double generate() const override;          // генерация одного случайного числа
    std::vector<double> generate(int n) const; // генерация n случайных чисел
    void generateGraphPoints(const std::string &filename) const;

    void save_params(std::string filename) const override; // сохранение атрибутов в файл
    void load_params(std::string filename) override;
};