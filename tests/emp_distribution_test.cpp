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

    EmpiricalDistribution emp_dist(dist, n);

    logFile << "PDF: " << emp_dist.pdf(0) << std::endl;
    logFile << "ER PDF: " << fabs(emp_dist.pdf(0) - dist.pdf(0)) << std::endl;
    logFile << "Mathematical Expectation: " << emp_dist.expectation() << std::endl;
    logFile << "ER Mathematical Expectation: " << fabs(emp_dist.expectation() - dist.expectation()) << std::endl;
    logFile << "Variance: " << emp_dist.variance() << std::endl;
    logFile << "ER Variance: " << fabs(emp_dist.variance() - dist.variance()) << std::endl;
    logFile << "Skewness: " << emp_dist.skewness() << std::endl;
    logFile << "ER Skewness: " << fabs(emp_dist.skewness() - dist.skewness()) << std::endl;
    logFile << "Excess Kurtosis: " << emp_dist.excessKurtosis() << std::endl;
    logFile << "ER Excess Kurtosis: " << fabs(emp_dist.excessKurtosis() - dist.excessKurtosis()) << std::endl;
    logFile << "N = " << n << std::endl;

    std::string file_name_emp = emp_distributions_path + "emp_main_distribution_test" + std::to_string(s_test_emp_main_number) + ".txt";
    emp_dist.generateGraphPoints(file_name_emp);
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

    MixDistribution<MainDistribution, MainDistribution> mix_dist;
    mix_dist.SetM1(MainDistribution(v1, mu1, lambda1));
    mix_dist.SetM2(MainDistribution(v2, mu2, lambda2));

    EmpiricalDistribution emp_dist(mix_dist, n);

    logFile << "PDF: " << emp_dist.pdf(0) << std::endl;
    logFile << "ER PDF: " << fabs(emp_dist.pdf(0) - mix_dist.pdf(0)) << std::endl;
    logFile << "Mathematical Expectation: " << emp_dist.expectation() << std::endl;
    logFile << "ER Mathematical Expectation: " << fabs(emp_dist.expectation() - mix_dist.expectation()) << std::endl;
    logFile << "Variance: " << emp_dist.variance() << std::endl;
    logFile << "ER Variance: " << fabs(emp_dist.variance() - mix_dist.variance()) << std::endl;
    logFile << "Skewness: " << emp_dist.skewness() << std::endl;
    logFile << "ER Skewness: " << fabs(emp_dist.skewness() - mix_dist.skewness()) << std::endl;
    logFile << "Excess Kurtosis: " << emp_dist.excessKurtosis() << std::endl;
    logFile << "ER Excess Kurtosis: " << fabs(emp_dist.excessKurtosis() - mix_dist.excessKurtosis()) << std::endl;
    logFile << "N = " << n << std::endl;

    std::string file_name_emp = emp_distributions_path + "emp_mix_distribution_test" + std::to_string(s_test_emp_mix_number) + ".txt";
    emp_dist.generateGraphPoints(file_name_emp);
    std::string file_name = emp_distributions_path + "mix_distribution_test" + std::to_string(s_test_emp_mix_number) + ".txt";
    mix_dist.generateGraphPoints(file_name);
    s_test_emp_mix_number++;
}

void EmpDistributionTest2(std::string emp_distributions_path, double v, double mu, double lambda, int n, std::ofstream &logFile)
{
    static int s_test_emp_main_two_number = 1;

    std::vector<double> samplesOne;
    std::vector<double> samplesTwo;

    logFile << "Form Parameter(v): " << v << std::endl;
    logFile << "Shift Parameter(mu): " << mu << std::endl;
    logFile << "Scale Parameter(lambda): " << lambda << std::endl;

    MainDistribution dist;
    dist.SetV(v);
    dist.SetLambda(lambda);
    dist.SetMu(mu);

    EmpiricalDistribution emp_dist1(dist, n);
    EmpiricalDistribution emp_dist2(dist, n);

    logFile << "PDF: " << emp_dist2.pdf(0) << std::endl;
    logFile << "ER PDF: " << fabs(emp_dist2.pdf(0) - emp_dist1.pdf(0)) << std::endl;
    logFile << "Mathematical Expectation: " << emp_dist2.expectation() << std::endl;
    logFile << "ER Mathematical Expectation: " << fabs(emp_dist2.expectation() - emp_dist1.expectation()) << std::endl;
    logFile << "Variance: " << emp_dist2.variance() << std::endl;
    logFile << "ER Variance: " << fabs(emp_dist2.variance() - emp_dist1.variance()) << std::endl;
    logFile << "Skewness: " << emp_dist2.skewness() << std::endl;
    logFile << "ER Skewness: " << fabs(emp_dist2.skewness() - emp_dist1.skewness()) << std::endl;
    logFile << "Excess Kurtosis: " << emp_dist2.excessKurtosis() << std::endl;
    logFile << "ER Excess Kurtosis: " << fabs(emp_dist2.excessKurtosis() - emp_dist1.excessKurtosis()) << std::endl;
    logFile << "N = " << n << std::endl;

    std::string file_name_emp = emp_distributions_path + "emp_main_distribution_test_two" + std::to_string(s_test_emp_main_two_number) + ".txt";
    emp_dist2.generateGraphPoints(file_name_emp);
    std::string file_name = emp_distributions_path + "distribution_test_two" + std::to_string(s_test_emp_main_two_number) + ".txt";
    dist.generateGraphPoints(file_name);
    s_test_emp_main_two_number++;
}

void EmpDistributionTest2(std::string emp_distributions_path, double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p, int n, std::ofstream &logFile)
{
    static int s_test_emp_mix_two_number = 1;

    double temp;
    std::vector<double> samplesOne;
    std::vector<double> samplesTwo;

    logFile << "Form Parameter(v1): " << v1 << std::endl;
    logFile << "Shift Parameter(mu1): " << mu1 << std::endl;
    logFile << "Scale Parameter(lambda1): " << lambda1 << std::endl;
    logFile << "Form Parameter(v2): " << v2 << std::endl;
    logFile << "Shift Parameter(mu2): " << mu2 << std::endl;
    logFile << "Scale Parameter(lambda2): " << lambda2 << std::endl;
    logFile << "Mix Parameter(p): " << p << std::endl;

    MainDistribution dist1(v1, mu1, lambda1);
    MainDistribution dist2(v2, mu2, lambda2);
    MixDistribution mix_dist(dist1, dist2, p);

    EmpiricalDistribution emp_dist1(mix_dist, n);
    EmpiricalDistribution emp_dist2(mix_dist, n);

    logFile << "PDF: " << emp_dist2.pdf(0) << std::endl;
    logFile << "ER PDF: " << fabs(emp_dist2.pdf(0) - emp_dist1.pdf(0)) << std::endl;
    logFile << "Mathematical Expectation: " << emp_dist2.expectation() << std::endl;
    logFile << "ER Mathematical Expectation: " << fabs(emp_dist2.expectation() - emp_dist1.expectation()) << std::endl;
    logFile << "Variance: " << emp_dist2.variance() << std::endl;
    logFile << "ER Variance: " << fabs(emp_dist2.variance() - emp_dist1.variance()) << std::endl;
    logFile << "Skewness: " << emp_dist2.skewness() << std::endl;
    logFile << "ER Skewness: " << fabs(emp_dist2.skewness() - emp_dist1.skewness()) << std::endl;
    logFile << "Excess Kurtosis: " << emp_dist2.excessKurtosis() << std::endl;
    logFile << "ER Excess Kurtosis: " << fabs(emp_dist2.excessKurtosis() - emp_dist1.excessKurtosis()) << std::endl;
    logFile << "N = " << n << std::endl;

    std::string file_name_emp = emp_distributions_path + "emp_mix_distribution_test_two" + std::to_string(s_test_emp_mix_two_number) + ".txt";
    emp_dist2.generateGraphPoints(file_name_emp);
    std::string file_name = emp_distributions_path + "mix_distribution_test_two" + std::to_string(s_test_emp_mix_two_number) + ".txt";
    mix_dist.generateGraphPoints(file_name);
    s_test_emp_mix_two_number++;
}