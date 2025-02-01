#pragma once

#include "distribution.hpp"

namespace MixDistribution
{
    double pdf(double x, double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p);
    double expectation(double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p);
    double variance(double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p);
    double skewness(double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p);
    double excessKurtosis(double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p);
    double generate(double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p);
    void generateGraphPoints(double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p, std::string filename);
}
