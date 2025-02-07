#include "distribution.hpp"

void MainDistribution::addCalculation()
{
	a = M_PI * tan((M_PI * v) / 2.0);
	K = sin(M_PI * v) * ((1.0 / M_PI) + (M_PI / pow(a, 2))) + v;
	P = (sin(M_PI * v) / M_PI + v) / K;
}

MainDistribution::MainDistribution(double v, double mu, double lambda)
	: v(v), mu(mu), lambda(lambda), generator(std::random_device{}()), uniform(0.0, 1.0)
{
	addCalculation();
}

MainDistribution::~MainDistribution() {};

double MainDistribution::pdf(double x)
{
	double z = (x - mu) / lambda;
	double density;
	if (std::abs(z) <= v)
		density = cos((M_PI * z) / 2.0) * cos((M_PI * z) / 2.0);
	else
		density = cos((M_PI * v) / 2.0) * cos((M_PI * v) / 2.0) * exp(-a * (std::abs(z) - v));
	return density / (lambda * K);
}

double MainDistribution::expectation() { return mu; }

double MainDistribution::variance()
{
	double term1 = (pow(M_PI * v, 3) / 6.0 + (pow(M_PI * v, 2) / 2.0 - 1.0) * sin(M_PI * v) + M_PI * v * cos(M_PI * v));
	double term2 = (2.0 * pow(cos((M_PI * v) / 2.0), 2) / (a * K)) * ((2.0 / (a * a)) + ((2.0 * v) / a) + v * v);
	double varianceValue = (2.0 / (pow(M_PI, 3) * K)) * term1 + term2;
	return varianceValue * lambda * lambda;
}

double MainDistribution::skewness() { return 0; }

double MainDistribution::excessKurtosis()
{
	double term1 = (pow(M_PI * v, 5) / 20.0 + sin(M_PI * v) * ((pow(M_PI * v, 4) / 4.0) - 3.0 * pow(M_PI * v, 2) + 6.0));
	double term2 = cos(M_PI * v) * (pow(M_PI * v, 3) - 6.0 * M_PI * v);
	double term3 = (2.0 * pow(cos(M_PI * v / 2.0), 2) / (pow(variance(), 2) * K)) * (24.0 / pow(a, 5) + (24.0 * v) / pow(a, 4) + (12.0 * v * v) / pow(a, 3) + (4.0 * v * v * v) / (a * a) + (v * v * v * v) / a);
	return 4.0 / (pow(variance(), 2) * pow(M_PI, 5) * K) * (term1 + term2) + term3 - 3.0;
}

double MainDistribution::GetV() { return v; }

double MainDistribution::SetV(double v) { this->v = v; }

double MainDistribution::GetMu() { return mu; }

double MainDistribution::SetMu(double mu) { this->mu = mu; }

double MainDistribution::GetLambda() { return lambda; }

double MainDistribution::SetLambda(double lambda) { this->lambda = lambda; }

double MainDistribution::GetA() { return a; }

double MainDistribution::SetA(double a) { this->a = a; }

double MainDistribution::GetK() { return K; }

double MainDistribution::SetK(double K) { this->K = K; }

double MainDistribution::GetP() { return P; }

double MainDistribution::SetP(double P) { this->P = P; }

double MainDistribution::generate()
{
	while (true)
	{
		double r1 = uniform(generator);
		if (r1 < P)
		{
			while (true)
			{
				double r2 = uniform(generator);
				double r3 = uniform(generator);
				double x1 = (2 * r2 - 1) * v;
				if (r3 < pow(cos(M_PI * x1 / 2.0), 2))
					return mu + lambda * x1;
			}
		}
		else
		{
			double r4 = uniform(generator);
			double x2 = v - log(r4) / a;
			return (r1 < (1 + P) / 2.0) ? (mu + lambda * x2) : (mu - lambda * x2);
		}
	}
}

void MainDistribution::generateGraphPoints(std::string filename)
{
	std::ofstream file(filename);
	if (!file)
	{
		std::cerr << "Error: Unable to open file." << std::endl;
		return;
	}

	double minX = -10;
	double maxX = 10;
	double numPoints = 1000;
	double step = (maxX - minX) / (numPoints - 1);

	for (int i = 0; i < numPoints; ++i)
	{
		double x = minX + i * step;
		double y = pdf(x);
		file << x << " " << y << "\n";
	}
	file.close();
}