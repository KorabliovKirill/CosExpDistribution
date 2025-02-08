#include "distribution.hpp"
#include "mix_distribution.hpp"
#include "emp_distribution.hpp"
#include "../tests/main_distribution_test.hpp"
#include "../tests/mix_distribution_test.hpp"
#include "../tests/emp_distribution_test.hpp"

std::string distributions_path = "../graphs/distributions/";
std::string mix_distributions_path = "../graphs/mix_distributions/";
std::string emp_distributions_path = "../graphs/emp_distributions/";

void MainDistributionWork()
{
	double v, mu, lambda, x;
	static int s_number = 1;
	MainDistribution dist;
	std::string name = "distribution";

	std::cout << "X: ";
	std::cin >> x;
	std::cout << "Form Parameter(v, default = 0.5): ";
	std::cin >> v;
	std::cout << "Shift Parameter(mu, default = 0): ";
	std::cin >> mu;
	std::cout << "Scale Parameter(lambda, default = 1): ";
	std::cin >> lambda;

	try
	{
		dist.SetV(v);
	}
	catch (char const *exV)
	{
		std::cout << exV << std::endl;
		std::abort();
	}

	try
	{
		dist.SetLambda(lambda);
	}
	catch (char const *exLambda)
	{
		std::cout << exLambda << std::endl;
		std::abort();
	}

	dist.SetMu(mu);

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

void MixDistributionWork()
{
	double x, v1, mu1, lambda1, v2, mu2, lambda2, p;
	static int s_mix_number = 1;

	std::cout << "X: ";
	std::cin >> x;
	std::string name = "mix_distribution";
	std::cout << "Form Parameter(v1, default = 0.5): ";
	std::cin >> v1;
	std::cout << "Shift Parameter(mu1, default = 0): ";
	std::cin >> mu1;
	std::cout << "Scale Parameter(lambda1, default = 1): ";
	std::cin >> lambda1;

	std::cout << "Form Parameter(v2, default = 0.5): ";
	std::cin >> v2;
	std::cout << "Shift Parameter(mu2, default = 0): ";
	std::cin >> mu2;
	std::cout << "Scale Parameter(lambda2, default = 1): ";
	std::cin >> lambda2;

	std::cout << "Mix Parameter(p): ";
	std::cin >> p;

	if (p < 0 || p > 1)
	{
		std::cout << "0 < p < 1 !!!" << std::endl;
		std::abort();
	}
	else if (v1 < 0 || v1 > 1 || v2 < 0 || v2 > 1)
	{
		std::cout << "0 < v < 1 !!!" << std::endl;
		std::abort();
	}
	if (lambda1 <= 0 || lambda2 <= 0)
	{
		std::cout << " lambda > 0 !!!" << std::endl;
		std::abort();
	}

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

void EmpMainDistributionWork()
{
	int n;
	double x, v, mu, lambda;
	static int s_emp_number = 1;
	std::string name_emp = "emp_distribution";
	std::string name = "distribution";

	std::vector<double> samples;

	std::cout << "X: ";
	std::cin >> x;
	std::cout << "N: ";
	std::cin >> n;
	std::cout << "Form Parameter(v, default = 0.5): ";
	std::cin >> v;
	std::cout << "Shift Parameter(mu, default = 0): ";
	std::cin >> mu;
	std::cout << "Scale Parameter(lambda, default = 1): ";
	std::cin >> lambda;

	MainDistribution dist;

	try
	{
		dist.SetV(v);
	}
	catch (char const *exV)
	{
		std::cout << exV << std::endl;
		std::abort();
	}

	try
	{
		dist.SetLambda(lambda);
	}
	catch (char const *exLambda)
	{
		std::cout << exLambda << std::endl;
		std::abort();
	}

	dist.SetMu(mu);

	samples = EmpDistribution::samples(n, v, mu, lambda);

	std::cout << "PDF: " << EmpDistribution::pdf(x, samples) << std::endl;
	std::cout << "ER PDF: " << fabs(EmpDistribution::pdf(x, samples) - dist.pdf(x)) << std::endl;
	std::cout << "Mathematical Expectation: " << EmpDistribution::expectation(samples) << std::endl;
	std::cout << "ER Mathematical Expectation: " << fabs(EmpDistribution::expectation(samples) - dist.expectation()) << std::endl;
	std::cout << "Variance: " << EmpDistribution::variance(samples) << std::endl;
	std::cout << "ER Variance: " << fabs(EmpDistribution::variance(samples) - dist.variance()) << std::endl;
	std::cout << "Skewness: " << EmpDistribution::skewness(samples) << std::endl;
	std::cout << "ER Skewness: " << fabs(EmpDistribution::skewness(samples) - dist.skewness()) << std::endl;
	std::cout << "Excess Kurtosis: " << EmpDistribution::excessKurtosis(samples) << std::endl;
	std::cout << "ER Excess Kurtosis: " << fabs(EmpDistribution::excessKurtosis(samples) - dist.excessKurtosis()) << std::endl;

	std::string file_name_emp = emp_distributions_path + name_emp + std::to_string(s_emp_number) + ".txt";
	EmpDistribution::generateGraphPoints(samples, file_name_emp);
	std::string file_name = emp_distributions_path + name + std::to_string(s_emp_number) + ".txt";
	dist.generateGraphPoints(file_name);
	s_emp_number++;
}

void EmpMixDistributionWork()
{
	int n;
	double x, v1, mu1, lambda1, v2, mu2, lambda2, p;
	static int s_emp_number = 1;
	std::string name_emp = "emp_distribution";
	std::string name = "mix_distribution";

	std::vector<double> samples;

	std::cout << "X: ";
	std::cin >> x;
	std::cout << "N: ";
	std::cin >> n;
	std::cout << "Form Parameter(v1, default = 0.5): ";
	std::cin >> v1;
	std::cout << "Shift Parameter(mu1, default = 0): ";
	std::cin >> mu1;
	std::cout << "Scale Parameter(lambda1, default = 1): ";
	std::cin >> lambda1;
	std::cout << "Form Parameter(v2, default = 0.5): ";
	std::cin >> v2;
	std::cout << "Shift Parameter(mu2, default = 0): ";
	std::cin >> mu2;
	std::cout << "Scale Parameter(lambda2, default = 1): ";
	std::cin >> lambda2;

	std::cout << "Mix Parameter(p): ";
	std::cin >> p;

	if (p < 0 || p > 1)
	{
		std::cout << "0 < p < 1 !!!" << std::endl;
		std::abort();
	}
	else if (v1 < 0 || v1 > 1 || v2 < 0 || v2 > 1)
	{
		std::cout << "0 < v < 1 !!!" << std::endl;
		std::abort();
	}
	if (lambda1 <= 0 || lambda2 <= 0)
	{
		std::cout << " lambda > 0 !!!" << std::endl;
		std::abort();
	}

	samples = EmpDistribution::samples(n, v1, mu1, lambda1, v2, mu2, lambda2, p);

	std::cout << "PDF: " << EmpDistribution::pdf(x, samples) << std::endl;
	std::cout << "ER PDF: " << fabs(EmpDistribution::pdf(x, samples) - MixDistribution::pdf(x, v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
	std::cout << "Mathematical Expectation: " << EmpDistribution::expectation(samples) << std::endl;
	std::cout << "ER Mathematical Expectation: " << fabs(EmpDistribution::expectation(samples) - MixDistribution::expectation(v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
	std::cout << "Variance: " << EmpDistribution::variance(samples) << std::endl;
	std::cout << "ER Variance: " << fabs(EmpDistribution::variance(samples) - MixDistribution::variance(v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
	std::cout << "Skewness: " << EmpDistribution::skewness(samples) << std::endl;
	std::cout << "ER Skewness: " << fabs(EmpDistribution::skewness(samples) - MixDistribution::skewness(v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
	std::cout << "Excess Kurtosis: " << EmpDistribution::excessKurtosis(samples) << std::endl;
	std::cout << "ER Excess Kurtosis: " << fabs(EmpDistribution::excessKurtosis(samples) - MixDistribution::excessKurtosis(v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;

	std::string file_name_emp = emp_distributions_path + name_emp + std::to_string(s_emp_number) + ".txt";
	EmpDistribution::generateGraphPoints(samples, file_name_emp);
	std::string file_name = emp_distributions_path + name + std::to_string(s_emp_number) + ".txt";
	MixDistribution::generateGraphPoints(v1, mu1, lambda1, v2, mu2, lambda2, p, file_name);
	s_emp_number++;
}

void Tests()
{
	std::string logFilePath = "../tests/test_log.txt";
	std::ofstream logFile(logFilePath, std::ios::out | std::ios::trunc);

	if (!logFile)
	{
		std::cerr << "Ошибка открытия файла: " << logFilePath << std::endl;
		return;
	}

	logFile << "Test 1 (Main distribution, mu=0, lambda=1):" << std::endl;
	MainDistributionTest(distributions_path, 0.5, 0, 1, logFile);
	logFile << "==========================" << std::endl;

	logFile << "Test 2 (Main distribution, mu!=0, lambda=2):" << std::endl;
	MainDistributionTest(distributions_path, 0.2, -3, 2, logFile);
	logFile << "==========================" << std::endl;

	logFile << "Test 3 (Mix distribution, mu1=mu2!=0, lambda1=lambda2=2, v1-v2):" << std::endl;
	MixDistributionTest(mix_distributions_path, 0.5, -3, 2, 0.5, -3, 2, 0.7, logFile);
	logFile << "==========================" << std::endl;

	logFile << "Test 4 (Mix distribution, mu1!=m2, p = 0.5):" << std::endl;
	MixDistributionTest(mix_distributions_path, 1, -3, 1, 1, 2, 1, 0.5, logFile);
	logFile << "==========================" << std::endl;

	logFile << "Test 5 (Mix distribution, mu1=mu2=0, lambda1=1, lambda2=3, p = 0.5):" << std::endl;
	MixDistributionTest(mix_distributions_path, 0.2, 0, 1, 0.2, 0, 3, 0.5, logFile);
	logFile << "==========================" << std::endl;

	logFile << "Test 6 (3.3.1)" << std::endl;
	std::vector<int> N = {100, 1000, 10000, 100000};
	for (size_t i = 0; i < N.size(); ++i)
	{
		EmpDistributionTest1(emp_distributions_path, 0.4, -3, 1, N[i], logFile);
		logFile << "==========================" << std::endl;
		EmpDistributionTest1(emp_distributions_path, 0.3, -2, 1, 0.6, 2, 4, 0.8, N[i], logFile);
		logFile << "==========================" << std::endl;
	}

	logFile << "==========================" << std::endl;
	logFile.close();

	std::cout << "Все тесты пройдены. Результаты сохранены в " << logFilePath << std::endl;
}

int main()
{
	int switcher;
	bool exit = false;

	while (!exit)
	{
		std::cout << "1. Main Distribution" << std::endl;
		std::cout << "2. Mix Distribution" << std::endl;
		std::cout << "3. Empiric Main Distribution" << std::endl;
		std::cout << "4. Empiric Mix Distribution" << std::endl;
		std::cout << "5. Tests" << std::endl;
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
			EmpMainDistributionWork();
			break;
		case (4):
			EmpMixDistributionWork();
			break;
		case (5):
			Tests();
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