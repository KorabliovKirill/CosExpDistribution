#pragma once

#include "../src/distribution.hpp"
#include "../src/mix_distribution.hpp"
#include "../src/emp_distribution.hpp"

void EmpDistributionTest1(std::string emp_distributions_path, double v, double mu, double lambda, int n, std::ofstream &logFile);
void EmpDistributionTest1(std::string emp_distributions_path, double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p, int n, std::ofstream &logFile);
void EmpDistributionTest2(std::string emp_distributions_path, double v, double mu, double lambda, int n, std::ofstream &logFile);
void EmpDistributionTest2(std::string emp_distributions_path, double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p, int n, std::ofstream &logFile);