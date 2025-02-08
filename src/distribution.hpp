#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <fstream>

class MainDistribution
{
private:
	double v = 0.5;
	double mu = 0;
	double lambda = 1;
	double a, K, P;
	std::mt19937 generator;
	std::uniform_real_distribution<double> uniform{0.0, 1.0};

	void addCalculation();

public:
	MainDistribution();
	MainDistribution(double v, double mu, double lambda);
	MainDistribution(FILE *file);
	MainDistribution(std::string path);
	double pdf(double x);
	double expectation();
	double variance();
	double skewness();
	double excessKurtosis();
	double GetV();
	void SetV(double v);
	double GetMu();
	void SetMu(double mu);
	double GetLambda();
	void SetLambda(double lambda);
	double GetA();
	double GetK();
	double GetP();
	double generate();
	void generateGraphPoints(std::string filename);
};