#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <fstream>
#include <algorithm>
#include "interface.hpp"

class MainDistribution : public IDistribution, public IPersistent
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
	double pdf(double x) const override;
	double expectation() const override;
	double variance() const override;
	double skewness() const override;
	double excessKurtosis() const override;
	double GetV() const;
	void SetV(double v);
	double GetMu() const;
	void SetMu(double mu);
	double GetLambda() const;
	void SetLambda(double lambda);
	double GetA() const;
	double GetK() const;
	double GetP() const;
	double generate() const override;
	void generateGraphPoints(std::string filename);
	void save_params(std::string filename) const override; // сохранение атрибутов в файл
	void load_params(std::string filename) override;	   // загрузка атрибутов из файла
};