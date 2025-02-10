#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <fstream>
#include <algorithm>

class MainDistribution
{
private:
	double v;
	double mu;
	double lambda;
	double a, K, P;
	mutable std::mt19937 generator;
	mutable std::uniform_real_distribution<double> uniform;

	void addCalculation();

public:
	MainDistribution();
	MainDistribution(double v, double mu, double lambda);
	MainDistribution(FILE *file);
	MainDistribution(std::string path);
	~MainDistribution();
	double pdf(double x) const;
	double expectation() const;
	double variance() const;
	double skewness() const;
	double excessKurtosis() const;
	double GetV() const;
	void SetV(double v);
	double GetMu() const;
	void SetMu(double mu);
	double GetLambda() const;
	void SetLambda(double lambda);
	double GetA() const;
	double GetK() const;
	double GetP() const;
	double generate() const;
	void generateGraphPoints(std::string filename);
};