#include "distribution.hpp"

std::string distributions_path = "../graphs/distributions/";
std::string mix_distributions_path = "../graphs/mix_distributions/";
std::string emp_distributions_path = "../graphs/emp_distributions/";

void MainDistributionWork()
{
	double v, mu, lambda;
	static int s_number = 1;
	std::string name = "distribution";
	std::cout << "Form Parameter(v): ";
	std::cin >> v;
	std::cout << "Shift Parameter(mu): ";
	std::cin >> mu;
	std::cout << "Scale Parameter(lambda): ";
	std::cin >> lambda;

	MainDistribution dist(v, mu, lambda);
	std::cout << "Variance: " << dist.variance() << std::endl;
	std::cout << "Excess Kurtosis: " << dist.excessKurtosis() << std::endl;
	std::cout << "P: " << dist.GetP() << std::endl;
	std::cout << "PDF at x=0: " << dist.pdf(0) << std::endl;
	std::cout << "Random sample: " << dist.generate() << std::endl;

	std::string file_name = distributions_path + name + std::to_string(s_number) + ".txt";
	dist.generateGraphPoints(file_name);
	s_number++;
}

void MainDistributionWork(double v, double mu, double lambda)
{
	static int s_test_number = 1;

	std::cout << "Form Parameter(v): " << v << std::endl;
	std::cout << "Shift Parameter(mu): " << mu << std::endl;
	std::cout << "Scale Parameter(lambda): " << lambda << std::endl;

	MainDistribution dist(v, mu, lambda);
	std::cout << "Variance: " << dist.variance() << std::endl;
	std::cout << "Excess Kurtosis: " << dist.excessKurtosis() << std::endl;
	std::cout << "P: " << dist.GetP() << std::endl;
	std::cout << "PDF at x=0: " << dist.pdf(0) << std::endl;
	std::cout << "Random sample: " << dist.generate() << std::endl;

	std::string file_name = distributions_path + "test" + std::to_string(s_test_number) + ".txt";
	dist.generateGraphPoints(file_name);
	s_test_number++;
}

int main()
{
	int switcher;
	bool exit = false;

	while (!exit)
	{
		std::cout << "1. Manual setting of parameters" << std::endl;
		std::cout << "2. Test 1" << std::endl;
		std::cout << "3. Test 2" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cin >> switcher;

		switch (switcher)
		{
		case (1):
			MainDistributionWork();
			break;
		case (2):
			MainDistributionWork(0.5, 0, 1);
			break;
		case (3):
			MainDistributionWork(0.2, 2, 2);
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