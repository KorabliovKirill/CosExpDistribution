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

    MainDistribution dist1(v1, mu1, lambda1);
    MainDistribution dist2(v2, mu2, lambda2);

    MixDistribution mix_dist(dist1, dist2, p);

    logFile << "Mathematical Expectation: " << mix_dist.expectation() << std::endl;
    logFile << "Variance: " << mix_dist.variance() << std::endl;
    logFile << "Excess Kurtosis: " << mix_dist.excessKurtosis() << std::endl;
    logFile << "Skewness: " << mix_dist.skewness() << std::endl;
    logFile << "PDF: " << mix_dist.pdf(0) << std::endl;

    std::string file_name = mix_distributions_path + "mix_distribution_test" + std::to_string(s_test_mix_number) + ".txt";
    mix_dist.generateGraphPoints(file_name);
    s_test_mix_number++;
}