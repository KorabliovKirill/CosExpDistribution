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
	double v, mu, lambda, a, K, P;
	std::mt19937 generator;
	std::uniform_real_distribution<double> uniform;

	void addCalculation();

public:
	MainDistribution(double v, double mu, double lambda);
	~MainDistribution();
	double pdf(double x);
	double expectation();
	double variance();
	double skewness();
	double excessKurtosis();
	double GetV();
	double SetV(double v);
	double GetMu();
	double SetMu(double mu);
	double GetLambda();
	double SetLambda(double lambda);
	double GetA();
	double SetA(double a);
	double GetK();
	double SetK(double K);
	double GetP();
	double SetP(double P);
	double generate();
	void generateGraphPoints(std::string filename);
};