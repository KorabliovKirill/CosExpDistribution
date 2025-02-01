#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <fstream>

class MainDistribution {
private:
	double v, mu, lambda, a, K, P;
	std::mt19937 generator;
	std::uniform_real_distribution<double> uniform;

	void addCalculation();

public:
	MainDistribution(double v, double mu, double lambda);
	MainDistribution();
	double pdf(double x);
	double expectation();
	double variance();
	double skewness();
	double excessKurtosis();
	double GetP();
	double generate();
	void generateGraphPoints(double minX, double maxX, int numPoints, const std::string& filename);
};