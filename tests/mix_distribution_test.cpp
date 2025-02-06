#include "mix_distribution_test.hpp"

void MixDistributionTest(std::string mix_distributions_path, double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p, std::ofstream &logFile)
{
    static int s_test_mix_number = 1;

    logFile << "Form Parameter(v1): " << v1 << std::endl;
    logFile << "Shift Parameter(mu1): " << mu1 << std::endl;
    logFile << "Scale Parameter(lambda1): " << lambda1 << std::endl;
    logFile << "Form Parameter(v2): " << v2 << std::endl;
    logFile << "Shift Parameter(mu2): " << mu2 << std::endl;
    logFile << "Scale Parameter(lambda2): " << lambda2 << std::endl;
    logFile << "Mix Parameter(p): " << p << std::endl;

    logFile << "Mathematical Expectation: " << MixDistribution::expectation(v1, mu1, lambda1, v2, mu2, lambda2, p) << std::endl;
    logFile << "Variance: " << MixDistribution::variance(v1, mu1, lambda1, v2, mu2, lambda2, p) << std::endl;
    logFile << "Excess Kurtosis: " << MixDistribution::excessKurtosis(v1, mu1, lambda1, v2, mu2, lambda2, p) << std::endl;
    logFile << "Skewness: " << MixDistribution::skewness(v1, mu1, lambda1, v2, mu2, lambda2, p) << std::endl;
    logFile << "PDF: " << MixDistribution::pdf(0, v1, mu1, lambda1, v2, mu2, lambda2, p) << std::endl;

    std::string file_name = mix_distributions_path + "mix_distribution_test" + std::to_string(s_test_mix_number) + ".txt";
    MixDistribution::generateGraphPoints(v1, mu1, lambda1, v2, mu2, lambda2, p, file_name);
    s_test_mix_number++;
}