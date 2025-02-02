#pragma once

#include "distribution.hpp"
#include "mix_distribution.hpp"

namespace EmpDistribution
{
    double pdf(double x, std::vector<double> &samples);
    double expectation(std::vector<double> &samples);
    double variance(std::vector<double> &samples);
    double skewness(std::vector<double> &samples);
    double excessKurtosis(std::vector<double> &samples);
    std::vector<double> generate(int n, std::vector<double> &samples);
    std::vector<double> samples(int n, double v, double mu, double lambda);
    std::vector<double> samples(int n, double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p);
    std::vector<double> samples(int n, std::vector<double> &samples);
    void generateGraphPoints(std::vector<double> &samples, std::string filename);
}