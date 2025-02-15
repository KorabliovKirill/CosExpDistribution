#include "emp_distribution.hpp"

// Реализация методов класса EmpiricalDistribution

void EmpiricalDistribution::calculateDensity()
{
    // Вычисляем оптимальное число интервалов по формуле Стёрджеса
    if (size_ == 0)
    { // Если размер не задан, вычисляем автоматически
        size_ = static_cast<size_t>(1 + std::log2(samples_.size()));
    }

    // Инициализация массива плотности нулями
    density_.resize(size_, 0.0);

    // Вычисление ширины интервала
    double binWidth = (max_ - min_) / size_;

    // Подсчет количества значений в каждом интервале
    for (double sample : samples_)
    {
        int bin = static_cast<int>((sample - min_) / binWidth);
        if (bin >= 0 && bin < size_)
        {
            density_[bin]++;
        }
    }

    // Нормализация плотности
    for (double &d : density_)
    {
        d /= (samples_.size() * binWidth);
    }
}

// Конструкторы
EmpiricalDistribution::EmpiricalDistribution() : size_(0), min_(0), max_(0) {}

EmpiricalDistribution::EmpiricalDistribution(const std::vector<double> &samples, size_t size)
    : samples_(samples), size_(size)
{
    min_ = *std::min_element(samples_.begin(), samples_.end());
    max_ = *std::max_element(samples_.begin(), samples_.end());
    calculateDensity();
}

EmpiricalDistribution::EmpiricalDistribution(const IDistribution &dist, int n)
{
    samples_.resize(n);
    for (int i = 0; i < n; ++i)
    {
        samples_[i] = dist.generate();
    }
    size_ = n;
    min_ = *std::min_element(samples_.begin(), samples_.end());
    max_ = *std::max_element(samples_.begin(), samples_.end());
    calculateDensity();
}

EmpiricalDistribution::EmpiricalDistribution(const MixDistribution<MainDistribution, MainDistribution> &dist, int n)
{
    samples_.resize(n);
    for (int i = 0; i < n; ++i)
    {
        samples_[i] = dist.generate();
    }
    size_ = n;
    min_ = *std::min_element(samples_.begin(), samples_.end());
    max_ = *std::max_element(samples_.begin(), samples_.end());
    calculateDensity();
}

// Конструктор копирования
EmpiricalDistribution::EmpiricalDistribution(const EmpiricalDistribution &other)
    : samples_(other.samples_), density_(other.density_), size_(other.size_), min_(other.min_), max_(other.max_) {}

// Оператор присваивания
EmpiricalDistribution &EmpiricalDistribution::operator=(const EmpiricalDistribution &other)
{
    if (this != &other)
    {
        samples_ = other.samples_;
        density_ = other.density_;
        size_ = other.size_;
        min_ = other.min_;
        max_ = other.max_;
    }
    return *this;
}

// Деструктор
EmpiricalDistribution::~EmpiricalDistribution() {}

// Методы
double EmpiricalDistribution::pdf(double x) const
{
    if (x < min_ || x > max_)
        return 0.0;
    double binWidth = (max_ - min_) / size_;
    int bin = static_cast<int>((x - min_) / binWidth);
    return density_[bin];
}

double EmpiricalDistribution::expectation() const
{
    double sum = 0.0;
    for (double sample : samples_)
    {
        sum += sample;
    }
    return sum / samples_.size();
}

double EmpiricalDistribution::variance() const
{
    double mean = expectation();
    double sum = 0.0;
    for (double sample : samples_)
    {
        sum += (sample - mean) * (sample - mean);
    }
    return sum / samples_.size();
}

double EmpiricalDistribution::skewness() const
{
    double mean = expectation();
    double stdDev = std::sqrt(variance());
    double sum = 0.0;
    for (double sample : samples_)
    {
        sum += std::pow((sample - mean) / stdDev, 3);
    }
    return sum / samples_.size();
}

double EmpiricalDistribution::excessKurtosis() const
{
    double mean = expectation();
    double stdDev = std::sqrt(variance());
    double sum = 0.0;
    for (double sample : samples_)
    {
        sum += std::pow((sample - mean) / stdDev, 4);
    }
    return (sum / samples_.size()) - 3;
}

void EmpiricalDistribution::generateGraphPoints(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file)
    {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    double numPoints = 1000;

    double step = (max_ - min_) / (numPoints - 1);
    for (int i = 0; i < numPoints; ++i)
    {
        double x = min_ + i * step;
        file << x << " " << pdf(x) << "\n";
    }
    file.close();
}

// Реализация метода для генерации одного случайного числа
double EmpiricalDistribution::generate() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size_ - 1);
    return samples_[dis(gen)];
}

// Реализация метода для генерации n случайных чисел
std::vector<double> EmpiricalDistribution::generate(int n) const
{
    std::vector<double> result(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size_ - 1);
    for (int i = 0; i < n; ++i)
    {
        result[i] = samples_[dis(gen)];
    }
    return result;
}

// сохранение атрибутов в файл
void EmpiricalDistribution::save_params(std::string filename) const
{
    std::ofstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Unable to open file for saving parameters.");
    }
    for (const auto &sample : samples_)
    {
        file << sample << "\n";
    }
    file.close();
}

void EmpiricalDistribution::load_params(std::string filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Unable to open file for loading parameters.");
    }
    samples_.clear();
    double sample;
    while (file >> sample)
    {
        samples_.push_back(sample);
    }
    size_ = samples_.size();
    min_ = *std::min_element(samples_.begin(), samples_.end());
    max_ = *std::max_element(samples_.begin(), samples_.end());
    calculateDensity();
    file.close();
}