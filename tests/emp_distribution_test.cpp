#include "emp_distribution_test.hpp"

void EmpDistributionTest1(std::string emp_distributions_path, double v, double mu, double lambda, int n, std::ofstream &logFile)
{
    static int s_test_emp_main_number = 1;

    std::vector<double> samples;

    logFile << "Form Parameter(v): " << v << std::endl;
    logFile << "Shift Parameter(mu): " << mu << std::endl;
    logFile << "Scale Parameter(lambda): " << lambda << std::endl;

    MainDistribution dist;
    dist.SetV(v);
    dist.SetLambda(lambda);
    dist.SetMu(mu);

    samples = EmpDistribution::samples(n, v, mu, lambda);

    logFile << "PDF: " << EmpDistribution::pdf(0, samples) << std::endl;
    logFile << "ER PDF: " << fabs(EmpDistribution::pdf(0, samples) - dist.pdf(0)) << std::endl;
    logFile << "Mathematical Expectation: " << EmpDistribution::expectation(samples) << std::endl;
    logFile << "ER Mathematical Expectation: " << fabs(EmpDistribution::expectation(samples) - dist.expectation()) << std::endl;
    logFile << "Variance: " << EmpDistribution::variance(samples) << std::endl;
    logFile << "ER Variance: " << fabs(EmpDistribution::variance(samples) - dist.variance()) << std::endl;
    logFile << "Skewness: " << EmpDistribution::skewness(samples) << std::endl;
    logFile << "ER Skewness: " << fabs(EmpDistribution::skewness(samples) - dist.skewness()) << std::endl;
    logFile << "Excess Kurtosis: " << EmpDistribution::excessKurtosis(samples) << std::endl;
    logFile << "ER Excess Kurtosis: " << fabs(EmpDistribution::excessKurtosis(samples) - dist.skewness()) << std::endl;
    logFile << "N = " << n << std::endl;

    std::string file_name_emp = emp_distributions_path + "emp_main_distribution_test" + std::to_string(s_test_emp_main_number) + ".txt";
    EmpDistribution::generateGraphPoints(samples, file_name_emp);
    std::string file_name = emp_distributions_path + "distribution_test" + std::to_string(s_test_emp_main_number) + ".txt";
    dist.generateGraphPoints(file_name);
    s_test_emp_main_number++;
}

void EmpDistributionTest1(std::string emp_distributions_path, double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p, int n, std::ofstream &logFile)
{
    static int s_test_emp_mix_number = 1;

    double temp;
    std::vector<double> samples;

    logFile << "Form Parameter(v1): " << v1 << std::endl;
    logFile << "Shift Parameter(mu1): " << mu1 << std::endl;
    logFile << "Scale Parameter(lambda1): " << lambda1 << std::endl;
    logFile << "Form Parameter(v2): " << v2 << std::endl;
    logFile << "Shift Parameter(mu2): " << mu2 << std::endl;
    logFile << "Scale Parameter(lambda2): " << lambda2 << std::endl;
    logFile << "Mix Parameter(p): " << p << std::endl;

    samples = EmpDistribution::samples(n, v1, mu1, lambda1, v2, mu2, lambda2, p);

    logFile << "PDF: " << EmpDistribution::pdf(0, samples) << std::endl;
    logFile << "ER PDF: " << fabs(EmpDistribution::pdf(0, samples) - MixDistribution::pdf(0, v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
    logFile << "Mathematical Expectation: " << EmpDistribution::expectation(samples) << std::endl;
    logFile << "ER Mathematical Expectation: " << fabs(EmpDistribution::expectation(samples) - MixDistribution::expectation(v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
    logFile << "Variance: " << EmpDistribution::variance(samples) << std::endl;
    logFile << "ER Variance: " << fabs(EmpDistribution::variance(samples) - MixDistribution::variance(v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
    logFile << "Skewness: " << EmpDistribution::skewness(samples) << std::endl;
    logFile << "ER Skewness: " << fabs(EmpDistribution::skewness(samples) - MixDistribution::skewness(v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
    logFile << "Excess Kurtosis: " << EmpDistribution::excessKurtosis(samples) << std::endl;
    logFile << "ER Excess Kurtosis: " << fabs(EmpDistribution::excessKurtosis(samples) - MixDistribution::excessKurtosis(v1, mu1, lambda1, v2, mu2, lambda2, p)) << std::endl;
    logFile << "N = " << n << std::endl;

    std::string file_name_emp = emp_distributions_path + "emp_mix_distribution_test" + std::to_string(s_test_emp_mix_number) + ".txt";
    EmpDistribution::generateGraphPoints(samples, file_name_emp);
    std::string file_name = emp_distributions_path + "mix_distribution_test" + std::to_string(s_test_emp_mix_number) + ".txt";
    MixDistribution::generateGraphPoints(v1, mu1, lambda1, v2, mu2, lambda2, p, file_name);
    s_test_emp_mix_number++;
}