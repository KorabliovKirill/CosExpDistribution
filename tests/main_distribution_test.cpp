#include "main_distribution_test.hpp"

void MainDistributionTest(std::string distributions_path, double v, double mu, double lambda, std::ofstream &logFile)
{
    static int s_test_number = 1;

    logFile << "Form Parameter(v): " << v << std::endl;
    logFile << "Shift Parameter(mu): " << mu << std::endl;
    logFile << "Scale Parameter(lambda): " << lambda << std::endl;

    MainDistribution dist;
    dist.SetV(v);
    dist.SetMu(mu);
    dist.SetLambda(lambda);
    logFile << "Mathematical Expectation: " << dist.expectation() << std::endl;
    logFile << "Variance: " << dist.variance() << std::endl;
    logFile << "Excess Kurtosis: " << dist.excessKurtosis() << std::endl;
    logFile << "P: " << dist.GetP() << std::endl;
    logFile << "PDF at x=0: " << dist.pdf(0) << std::endl;

    std::string file_name = distributions_path + "distribution_test" + std::to_string(s_test_number) + ".txt";
    dist.generateGraphPoints(file_name);
    s_test_number++;
}