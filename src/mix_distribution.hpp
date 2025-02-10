#pragma once

#include "distribution.hpp"

class MixDistribution
{
private:
    MainDistribution M1;
    MainDistribution M2;
    double p;
    mutable std::mt19937 generator;
    mutable std::uniform_real_distribution<double> uniform;

public:
    MixDistribution();
    MixDistribution(const MainDistribution &M1, const MainDistribution &M2, double p);
    MixDistribution(FILE *file);
    MixDistribution(std::string path);
    ~MixDistribution();
    double pdf(double x) const;
    double expectation() const;
    double variance() const;
    double skewness() const;
    double excessKurtosis() const;
    double generate() const;

    const MainDistribution &GetM1() const;
    const MainDistribution &GetM2() const;
    double GetP() const;
    void SetP(double p);
    void SetM1(const MainDistribution &M1);
    void SetM2(const MainDistribution &M2);

    void generateGraphPoints(std::string filename);
};