#include "main_distribution_test.hpp"

void MainDistributionTest(std::string distributions_path, double v, double mu, double lambda)
{
    static int s_test_number = 1;

    std::cout << "Form Parameter(v): " << v << std::endl;
    std::cout << "Shift Parameter(mu): " << mu << std::endl;
    std::cout << "Scale Parameter(lambda): " << lambda << std::endl;

    MainDistribution dist(v, mu, lambda);
    std::cout << "Mathematical Expectation: " << dist.expectation() << std::endl;
    std::cout << "Variance: " << dist.variance() << std::endl;
    std::cout << "Excess Kurtosis: " << dist.excessKurtosis() << std::endl;
    std::cout << "P: " << dist.GetP() << std::endl;
    std::cout << "PDF at x=0: " << dist.pdf(0) << std::endl;
    std::cout << "Random sample: " << dist.generate() << std::endl;

    std::string file_name = distributions_path + "distribution_test" + std::to_string(s_test_number) + ".txt";
    dist.generateGraphPoints(file_name);
    s_test_number++;
}