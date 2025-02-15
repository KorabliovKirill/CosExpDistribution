#include "mix_distribution.hpp"

template <class Distribution1, class Distribution2>
MixDistribution<Distribution1, Distribution2>::MixDistribution() : M1(), M2(), p(0.5) {}

template <class Distribution1, class Distribution2>
MixDistribution<Distribution1, Distribution2>::MixDistribution(const Distribution1 &M1, const Distribution2 &M2, double p)
    : M1(M1), M2(M2), p((p >= 0 && p <= 1) ? p : throw std::invalid_argument("p должно быть в диапазоне [0,1]")) {}

template <class Distribution1, class Distribution2>
MixDistribution<Distribution1, Distribution2>::MixDistribution(FILE *file)
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

template <class Distribution1, class Distribution2>
MixDistribution<Distribution1, Distribution2>::MixDistribution(std::string path)
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

template <class Distribution1, class Distribution2>
MixDistribution<Distribution1, Distribution2>::~MixDistribution()
{
}

// Геттеры
template <class Distribution1, class Distribution2>
const Distribution1 &MixDistribution<Distribution1, Distribution2>::GetM1() const { return M1; }
template <class Distribution1, class Distribution2>
const Distribution2 &MixDistribution<Distribution1, Distribution2>::GetM2() const { return M2; }
template <class Distribution1, class Distribution2>
double MixDistribution<Distribution1, Distribution2>::GetP() const { return p; }

// Сеттер для p
template <class Distribution1, class Distribution2>
void MixDistribution<Distribution1, Distribution2>::SetP(double p)
{
    if (p < 0 || p > 1)
    {
        throw std::invalid_argument("p должно быть в диапазоне [0,1]");
    }
    this->p = p;
}

template <class Distribution1, class Distribution2>
void MixDistribution<Distribution1, Distribution2>::SetM1(const Distribution1 &M1)
{
    this->M1 = M1;
}

template <class Distribution1, class Distribution2>
void MixDistribution<Distribution1, Distribution2>::SetM2(const Distribution2 &M2)
{
    this->M2 = M2;
}

template <class Distribution1, class Distribution2>
double MixDistribution<Distribution1, Distribution2>::pdf(double x) const
{
    return (1 - p) * M1.pdf(x) + p * M2.pdf(x);
}

template <class Distribution1, class Distribution2>
double MixDistribution<Distribution1, Distribution2>::expectation() const
{
    return (1 - p) * M1.expectation() + p * M2.expectation();
}

template <class Distribution1, class Distribution2>
double MixDistribution<Distribution1, Distribution2>::variance() const
{
    double term1 = (1 - p) * (pow(M1.expectation(), 2) + M1.variance());
    double term2 = p * (pow(M2.expectation(), 2) + M2.variance());
    return term1 + term2 - pow(expectation(), 2);
}

template <class Distribution1, class Distribution2>
double MixDistribution<Distribution1, Distribution2>::skewness() const
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

template <class Distribution1, class Distribution2>
double MixDistribution<Distribution1, Distribution2>::excessKurtosis() const
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

template <class Distribution1, class Distribution2>
double MixDistribution<Distribution1, Distribution2>::generate() const
{
    return (p < uniform(generator)) ? M1.generate() : M2.generate();
}

template <class Distribution1, class Distribution2>
void MixDistribution<Distribution1, Distribution2>::generateGraphPoints(std::string filename)
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

template <class Distribution1, class Distribution2>
void MixDistribution<Distribution1, Distribution2>::save_params(std::string filename) const
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

template <class Distribution1, class Distribution2>
void MixDistribution<Distribution1, Distribution2>::load_params(std::string filename)
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