#pragma once

#include "distribution.hpp"

template <typename Distribution1, typename Distribution2>
class MixDistribution : public IDistribution, public IPersistent
{
private:
    Distribution1 M1;
    Distribution2 M2;
    double p;
    mutable std::mt19937 generator;
    mutable std::uniform_real_distribution<double> uniform;

public:
    MixDistribution() : M1(), M2(), p(0.5) {}

    MixDistribution(const Distribution1 &M1, const Distribution2 &M2, double p) : M1(M1), M2(M2), p((p >= 0 && p <= 1) ? p : throw std::invalid_argument("p должно быть в диапазоне [0,1]")) {}

    MixDistribution(FILE *file)
    {
        if (!file)
        {
            throw std::runtime_error("Ошибка: не удалось открыть файл");
        }
        double v1, mu1, lambda1, v2, mu2, lambda2;
        if (fscanf(file, "%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf", &v1, &mu1, &lambda1, &v2, &mu2, &lambda2, &p) != 7)
        {
            throw std::runtime_error("Ошибка: неверный формат данных в файле");
        }
        M1 = Distribution1(v1, mu1, lambda1);
        M2 = Distribution2(v2, mu2, lambda2);
    }

    MixDistribution(std::string path)
    {
        std::ifstream file(path);
        if (!file)
        {
            throw std::runtime_error("Ошибка: не удалось открыть файл");
        }
        double v1, mu1, lambda1, v2, mu2, lambda2;
        if (!(file >> v1 >> mu1 >> lambda1 >> v2 >> mu2 >> lambda2 >> p))
        {
            throw std::runtime_error("Ошибка: неверный формат данных в файле");
        }
        M1 = Distribution1(v1, mu1, lambda1);
        M2 = Distribution2(v2, mu2, lambda2);
        file.close();
    }

    ~MixDistribution() {}

    double pdf(double x) const override
    {
        return (1 - p) * M1.pdf(x) + p * M2.pdf(x);
    }

    double expectation() const override
    {
        return (1 - p) * M1.expectation() + p * M2.expectation();
    }

    double variance() const override
    {
        double term1 = (1 - p) * (pow(M1.expectation(), 2) + M1.variance());
        double term2 = p * (pow(M2.expectation(), 2) + M2.variance());
        return term1 + term2 - pow(expectation(), 2);
    }

    double skewness() const override
    {
        double M1_exp = M1.expectation();
        double M2_exp = M2.expectation();
        double mix_exp = expectation();
        double M1_var = M1.variance();
        double M2_var = M2.variance();

        double term1 = (1 - p) * (pow((M1_exp - mix_exp), 3) + 3 * (M1_exp - mix_exp) * M1_var + pow(M1_var, 1.5) * M1.skewness());
        double term2 = p * (pow((M2_exp - mix_exp), 3) + 3 * (M2_exp - mix_exp) * M2_var + pow(M2_var, 1.5) * M2.skewness());

        return (1 / pow(variance(), 1.5)) * (term1 + term2);
    }

    double excessKurtosis() const override
    {
        double M1_exp = M1.expectation();
        double M2_exp = M2.expectation();
        double mix_exp = expectation();
        double M1_var = M1.variance();
        double M2_var = M2.variance();

        double term1 = (1 - p) * (pow((M1_exp - mix_exp), 4) + 6 * (M1_exp - mix_exp) * pow(M1_var, (3 / 2)) * M1.skewness() + pow(M1_var, 2) * (M1.excessKurtosis() + 3));
        double term2 = p * (pow((M2_exp - mix_exp), 4) + 6 * (M2_exp - mix_exp) * pow(M2_var, (3 / 2)) * M2.skewness() + pow(M2_var, 2) * (M2.excessKurtosis() + 3));

        return (term1 + term2) / pow(variance(), 2) - 3;
    }

    double generate() const
    {
        return (p < uniform(generator)) ? M1.generate() : M2.generate();
    }

    const Distribution1 &GetM1() const { return M1; }
    const Distribution2 &GetM2() const { return M2; }
    double GetP() const { return p; }
    void SetP(double p)
    {
        if (p < 0 || p > 1)
        {
            throw std::invalid_argument("p должно быть в диапазоне [0,1]");
        }
        this->p = p;
    }
    void SetM1(const Distribution1 &M1)
    {
        this->M1 = M1;
    }
    void SetM2(const Distribution2 &M2)
    {
        this->M2 = M2;
    }

    void generateGraphPoints(std::string filename)
    {
        std::ofstream file(filename);
        if (!file)
        {
            std::cerr << "Error: Unable to open file." << std::endl;
            return;
        }

        double minX = -10;
        double maxX = 10;
        int numPoints = 1000;
        double step = (maxX - minX) / (numPoints - 1);

        for (int i = 0; i < numPoints; ++i)
        {
            double x = minX + i * step;
            double y = pdf(x);
            file << x << " " << y << "\n";
        }
        file.close();
    }

    void save_params(std::string filename) const override
    { // сохранение атрибутов в файл
        std::ofstream file(filename);
        if (!file)
        {
            throw std::runtime_error("Unable to open file for saving parameters.");
        }
        file << M1.GetV() << "\n"
             << M1.GetMu() << "\n"
             << M1.GetLambda() << "\n"
             << M2.GetV() << "\n"
             << M2.GetMu() << "\n"
             << M2.GetLambda() << "\n"
             << p << "\n";
        file.close();
    }

    void load_params(std::string filename) override
    { // загрузка атрибутов из файла
        std::ifstream file(filename);
        if (!file)
        {
            throw std::runtime_error("Unable to open file for loading parameters.");
        }
        double v1, mu1, lambda1, v2, mu2, lambda2;
        file >> v1 >> mu1 >> lambda1 >> v2 >> mu2 >> lambda2 >> p;
        M1 = Distribution1(v1, mu1, lambda1);
        M2 = Distribution2(v2, mu2, lambda2);
        file.close();
    }
};