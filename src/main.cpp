#include "distribution.hpp"
#include "mix_distribution.hpp"
#include "emp_distribution.hpp"

std::string distributions_path = "../graphs/distributions/";
std::string mix_distributions_path = "../graphs/mix_distributions/";
std::string emp_distributions_path = "../graphs/emp_distributions/";

void MainDistributionWork()
{
	double v, mu, lambda, x;
	static int s_number = 1;
	std::cout << "X: ";
	std::cin >> x;
	std::string name = "distribution";
	std::cout << "Form Parameter(v): ";
	std::cin >> v;
	std::cout << "Shift Parameter(mu): ";
	std::cin >> mu;
	std::cout << "Scale Parameter(lambda): ";
	std::cin >> lambda;

	MainDistribution dist(v, mu, lambda);
	std::cout << "Mathematical Expectation: " << dist.expectation() << std::endl;
	std::cout << "Variance: " << dist.variance() << std::endl;
	std::cout << "Excess Kurtosis: " << dist.excessKurtosis() << std::endl;
	std::cout << "P: " << dist.GetP() << std::endl;
	std::cout << "PDF: " << dist.pdf(x) << std::endl;
	std::cout << "Skewness: " << dist.skewness() << std::endl;
	std::cout << "Random sample: " << dist.generate() << std::endl;

	std::string file_name = distributions_path + name + std::to_string(s_number) + ".txt";
	dist.generateGraphPoints(file_name);
	s_number++;
}

// void MainDistributionWork(double v, double mu, double lambda)
// {
// 	static int s_test_number = 1;

// 	std::cout << "Form Parameter(v): " << v << std::endl;
// 	std::cout << "Shift Parameter(mu): " << mu << std::endl;
// 	std::cout << "Scale Parameter(lambda): " << lambda << std::endl;

// 	MainDistribution dist(v, mu, lambda);
// 	std::cout << "Mathematical Expectation: " << dist.expectation() << std::endl;
// 	std::cout << "Variance: " << dist.variance() << std::endl;
// 	std::cout << "Excess Kurtosis: " << dist.excessKurtosis() << std::endl;
// 	std::cout << "P: " << dist.GetP() << std::endl;
// 	std::cout << "PDF at x=0: " << dist.pdf(0) << std::endl;
// 	std::cout << "Random sample: " << dist.generate() << std::endl;

// 	std::string file_name = distributions_path + "test" + std::to_string(s_test_number) + ".txt";
// 	dist.generateGraphPoints(file_name);
// 	s_test_number++;
// }

void MixDistributionWork()
{
	double x, v1, mu1, lambda1, v2, mu2, lambda2, p;
	static int s_mix_number = 1;

	std::cout << "X: ";
	std::cin >> x;
	std::string name = "mix_distribution";
	std::cout << "Form Parameter(v1): ";
	std::cin >> v1;
	std::cout << "Shift Parameter(mu1): ";
	std::cin >> mu1;
	std::cout << "Scale Parameter(lambda1): ";
	std::cin >> lambda1;

	std::cout << "Form Parameter(v2): ";
	std::cin >> v2;
	std::cout << "Shift Parameter(mu2): ";
	std::cin >> mu2;
	std::cout << "Scale Parameter(lambda2): ";
	std::cin >> lambda2;

	std::cout << "Mix Parameter(p): ";
	std::cin >> p;

	std::cout << "Mathematical Expectation: " << MixDistribution::expectation(v1, mu1, lambda1, v2, mu2, lambda2, p) << std::endl;
	std::cout << "Variance: " << MixDistribution::variance(v1, mu1, lambda1, v2, mu2, lambda2, p) << std::endl;
	std::cout << "Excess Kurtosis: " << MixDistribution::excessKurtosis(v1, mu1, lambda1, v2, mu2, lambda2, p) << std::endl;
	std::cout << "Skewness: " << MixDistribution::skewness(v1, mu1, lambda1, v2, mu2, lambda2, p) << std::endl;
	std::cout << "PDF: " << MixDistribution::pdf(x, v1, mu1, lambda1, v2, mu2, lambda2, p) << std::endl;
	std::cout << "Random sample: " << MixDistribution::generate(v1, mu1, lambda1, v2, mu2, lambda2, p) << std::endl;

	std::string file_name = mix_distributions_path + name + std::to_string(s_mix_number) + ".txt";
	MixDistribution::generateGraphPoints(v1, mu1, lambda1, v2, mu2, lambda2, p, file_name);
	s_mix_number++;
}

void EmpDistributionWork()
{
	int n;
	double x, v, mu, lambda, v2, mu2, lambda2, p;
	static int s_emp_number = 1;
	std::string name = "emp_distribution";

	double temp;
	std::vector<double> samples;

	std::cout << "X: ";
	std::cin >> x;
	std::cout << "N: ";
	std::cin >> n;
	std::cout << "Form Parameter(v): ";
	std::cin >> v;
	std::cout << "Shift Parameter(mu): ";
	std::cin >> mu;
	std::cout << "Scale Parameter(lambda): ";
	std::cin >> lambda;

	MainDistribution dist(v, mu, lambda);

	samples = EmpDistribution::samples(1000, v, mu, lambda);

	std::cout << "PDF: " << EmpDistribution::pdf(x, samples) << std::endl;
	std::cout << "ER PDF: " << fabs(EmpDistribution::pdf(x, samples) - dist.pdf(x)) << std::endl;
	std::cout << "Mathematical Expectation: " << EmpDistribution::expectation(samples) << std::endl;
	std::cout << "ER Mathematical Expectation: " << fabs(EmpDistribution::expectation(samples) - dist.expectation()) << std::endl;
	std::cout << "Variance: " << EmpDistribution::variance(samples) << std::endl;
	std::cout << "ER Variance: " << fabs(EmpDistribution::variance(samples) - dist.variance()) << std::endl;
	std::cout << "Skewness: " << EmpDistribution::skewness(samples) << std::endl;
	std::cout << "ER Skewness: " << fabs(EmpDistribution::skewness(samples) - dist.skewness()) << std::endl;
	std::cout << "Excess Kurtosis: " << EmpDistribution::excessKurtosis(samples) << std::endl;
	std::cout << "ER Excess Kurtosis: " << fabs(EmpDistribution::excessKurtosis(samples) - dist.skewness()) << std::endl;

	// std::cout << "Form Parameter(v2): ";
	// std::cin >> v2;
	// std::cout << "Shift Parameter(mu2): ";
	// std::cin >> mu2;
	// std::cout << "Scale Parameter(lambda2): ";
	// std::cin >> lambda2;

	// std::cout << "Mix Parameter(p): ";
	// std::cin >> p;

	std::string file_name = emp_distributions_path + name + std::to_string(s_emp_number) + ".txt";
	EmpDistribution::generateGraphPoints(samples, file_name);
	s_emp_number++;
}

int main()
{
	int switcher;
	bool exit = false;

	while (!exit)
	{
		std::cout << "1. Main Distribution" << std::endl;
		std::cout << "2. Mix Distribution" << std::endl;
		std::cout << "3. Empiric Distribution" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cin >> switcher;

		switch (switcher)
		{
		case (1):
			MainDistributionWork();
			break;
		case (2):
			MixDistributionWork();
			break;
		case (3):
			EmpDistributionWork();
			break;
		case (0):
			exit = true;
			break;

		default:
			std::cout << "Error! Try again." << std::endl;
			break;
		}
	}
}