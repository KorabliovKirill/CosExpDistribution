#include "emp_distribution_test.hpp"

void EmpDistributionTest1(std::string emp_distributions_path, double v, double mu, double lambda, int n)
{
    static int s_test_emp_main_number = 1;

    std::vector<double> samples;

    MainDistribution dist(v, mu, lambda);

    samples = EmpDistribution::samples(n, v, mu, lambda);

    std::cout << "PDF: " << EmpDistribution::pdf(0, samples) << std::endl;
    std::cout << "ER PDF: " << fabs(EmpDistribution::pdf(0, samples) - dist.pdf(0)) << std::endl;
    std::cout << "Mathematical Expectation: " << EmpDistribution::expectation(samples) << std::endl;
    std::cout << "ER Mathematical Expectation: " << fabs(EmpDistribution::expectation(samples) - dist.expectation()) << std::endl;
    std::cout << "Variance: " << EmpDistribution::variance(samples) << std::endl;
    std::cout << "ER Variance: " << fabs(EmpDistribution::variance(samples) - dist.variance()) << std::endl;
    std::cout << "Skewness: " << EmpDistribution::skewness(samples) << std::endl;
    std::cout << "ER Skewness: " << fabs(EmpDistribution::skewness(samples) - dist.skewness()) << std::endl;
    std::cout << "Excess Kurtosis: " << EmpDistribution::excessKurtosis(samples) << std::endl;
    std::cout << "ER Excess Kurtosis: " << fabs(EmpDistribution::excessKurtosis(samples) - dist.skewness()) << std::endl;
    std::cout << "N = " << n << std::endl;

    std::string file_name_emp = emp_distributions_path + "emp_main_distribution_test" + std::to_string(s_test_emp_main_number) + ".txt";
    EmpDistribution::generateGraphPoints(samples, file_name_emp);
    std::string file_name = emp_distributions_path + "distribution_test" + std::to_string(s_test_emp_main_number) + ".txt";
    dist.generateGraphPoints(file_name);
    s_test_emp_main_number++;
}

void EmpDistributionTest1(std::string emp_distributions_path, double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p, int n)
{
    static int s_test_emp_mix_number = 1;

    double temp;
    std::vector<double> samples;

    std::cout << "Form Parameter(v1): " << v1 << std::endl;
    std::cout << "Shift Parameter(mu1): " << mu1 << std::endl;
    std::cout << "Scale Parameter(lambda1): " << lambda1 << std::endl;
    std::cout << "Form Parameter(v2): " << v2 << std::endl;
    std::cout << "Shift Parameter(mu2): " << mu2 << std::endl;
    std::cout << "Scale Parameter(lambda2): " << lambda2 << std::endl;
    std::cout << "Mix Parameter(p): " << p << std::endl;

    samples = EmpDistribution::samples(n, v1, mu1, lambda1, v2, mu2, lambda2, p);

    std::cout << "PDF: " << EmpDistribution::pdf(0, samples) << std::endl;
    std::cout << "ER PDF: " << fabs(EmpDistribution::pdf(0, samples) - MixDistribution::pdf(0, v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
    std::cout << "Mathematical Expectation: " << EmpDistribution::expectation(samples) << std::endl;
    std::cout << "ER Mathematical Expectation: " << fabs(EmpDistribution::expectation(samples) - MixDistribution::expectation(v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
    std::cout << "Variance: " << EmpDistribution::variance(samples) << std::endl;
    std::cout << "ER Variance: " << fabs(EmpDistribution::variance(samples) - MixDistribution::variance(v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
    std::cout << "Skewness: " << EmpDistribution::skewness(samples) << std::endl;
    std::cout << "ER Skewness: " << fabs(EmpDistribution::skewness(samples) - MixDistribution::skewness(v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
    std::cout << "Excess Kurtosis: " << EmpDistribution::excessKurtosis(samples) << std::endl;
    std::cout << "ER Excess Kurtosis: " << fabs(EmpDistribution::excessKurtosis(samples) - MixDistribution::excessKurtosis(v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
    std::cout << "N = " << n << std::endl;

    std::string file_name_emp = emp_distributions_path + "emp_mix_distribution_test" + std::to_string(s_test_emp_mix_number) + ".txt";
    EmpDistribution::generateGraphPoints(samples, file_name_emp);
    std::string file_name = emp_distributions_path + "mix_distribution_test" + std::to_string(s_test_emp_mix_number) + ".txt";
    MixDistribution::generateGraphPoints(v1, mu1, lambda1, v2, mu2, lambda2, p, file_name);
    s_test_emp_mix_number++;
}