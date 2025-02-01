#include "distribution.hpp"

int main() {
	double v = 1;
	MainDistribution dist(v, 0, 1);
	std::cout << "Variance: " << dist.variance() << std::endl;
	std::cout << "Excess Kurtosis: " << dist.excessKurtosis() << std::endl;
	std::cout << "P: " << dist.GetP() << std::endl;
	std::cout << "PDF at x=0: " << dist.pdf(0) << std::endl;
	std::cout << "Random sample: " << dist.generate() << std::endl;
}