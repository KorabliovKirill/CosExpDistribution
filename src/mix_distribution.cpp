#include "mix_distribution.hpp"

namespace MixDistribution
{
    double pdf(double x, double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p)
    {
        MainDistribution dist1(v1, mu1, lambda1);
        MainDistribution dist2(v2, mu2, lambda2);

        return (1 - p) * dist1.pdf(x) + p * dist2.pdf(x);
    }

    double expectation(double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p)
    {
        MainDistribution dist1(v1, mu1, lambda1);
        MainDistribution dist2(v2, mu2, lambda2);

        return (1 - p) * dist1.expectation() + p * dist2.expectation();
    }

    double variance(double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p)
    {
        MainDistribution dist1(v1, mu1, lambda1);
        MainDistribution dist2(v2, mu2, lambda2);

        double term1 = (1 - p) * (pow(dist1.expectation(), 2) + dist1.variance());
        double term2 = p * (pow(dist2.expectation(), 2) + dist2.variance());
        return term1 + term2 - pow(expectation(v1, mu1, lambda1, v2, mu2, lambda2, p), 2);
    }

    double skewness(double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p)
    {
        MainDistribution dist1(v1, mu1, lambda1);
        MainDistribution dist2(v2, mu2, lambda2);

        double M1 = dist1.expectation();
        double M2 = dist2.expectation();
        double M = expectation(v1, mu1, lambda1, v2, mu2, lambda2, p);
        double D1 = dist1.variance();
        double D2 = dist2.variance();

        double term1 = (1 - p) * (pow((M1 - M), 3) + 3 * (M1 - M) * D1 + pow(D1, 1.5) * dist1.skewness());
        double term2 = p * (pow((M2 - M), 3) + 3 * (M2 - M) * D2 + pow(D2, 1.5) * dist2.skewness());

        return (1 / pow(variance(v1, mu1, lambda1, v2, mu2, lambda2, p), 1.5)) * (term1 + term2);
    }

    double excessKurtosis(double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p)
    {
        MainDistribution dist1(v1, mu1, lambda1);
        MainDistribution dist2(v2, mu2, lambda2);

        double M1 = dist1.expectation();
        double M2 = dist2.expectation();
        double M = expectation(v1, mu1, lambda1, v2, mu2, lambda2, p);
        double D1 = dist1.variance();
        double D2 = dist2.variance();

        double term1 = (1 - p) * (pow((M1 - M), 4) + 6 * (M1 - M) * pow(D1, (3 / 2)) * dist1.skewness() + pow(D1, 2) * (dist1.excessKurtosis() + 3));
        double term2 = p * (pow((M2 - M), 4) + 6 * (M2 - M) * pow(D2, (3 / 2)) * dist2.skewness() + pow(D2, 2) * (dist2.excessKurtosis() + 3));

        return (term1 + term2) / pow(variance(v1, mu1, lambda1, v2, mu2, lambda2, p), 2) - 3;
    }

    double generate(double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p)
    {
        std::uniform_real_distribution<double> uniform(0.0, 1.0);
        std::mt19937 generator(std::random_device{}());
        MainDistribution dist1(v1, mu1, lambda1);
        MainDistribution dist2(v2, mu2, lambda2);

        double r = uniform(generator);
        return (p < r) ? dist1.generate() : dist2.generate();
    }

    void generateGraphPoints(double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p, std::string filename)
    {
        std::ofstream file(filename);
        if (!file)
        {
            std::cerr << "Error: Unable to open file." << std::endl;
            return;
        }

        double minX = -10;
        double maxX = 10;
        double numPoints = 1000;
        double step = (maxX - minX) / (numPoints - 1);

        for (int i = 0; i < numPoints; ++i)
        {
            double x = minX + i * step;
            double y = pdf(x, v1, mu1, lambda1, v2, mu2, lambda2, p);
            file << x << " " << y << "\n";
        }
        file.close();
    }
}