#include "emp_distribution.hpp"

// Реализация методов класса EmpiricalDistribution

void EmpiricalDistribution::calculateDensity() {
  if (samples_.empty()) {
    std::cerr << "Error: No samples provided. Samples size: " << samples_.size()
              << std::endl;
    return;
  }

  // Сортируем выборку
  std::sort(samples_.begin(), samples_.end());
  min_ = samples_.front();
  max_ = samples_.back();
  double samples_len = max_ - min_;

  // Проверка диапазона
  if (samples_len <= 0) {
    std::cerr << "Error: Samples length is zero or negative!" << std::endl;
    return;
  }

  // Вычисляем количество интервалов по формуле Стёрджеса
  size_ = static_cast<size_t>(1 + std::log2(samples_.size()));

  // Инициализация вектора плотностей (fi) нулями
  density_.resize(size_, 0.0);

  // Подсчёт частот для каждого интервала
  size_t j = 0;
  for (size_t i = 0; i < size_; ++i) {
    size_t ni = 0;
    double lower_bound = min_ + (static_cast<double>(i) / size_) * samples_len;
    double upper_bound =
        min_ + (static_cast<double>(i + 1) / size_) * samples_len;

    while (j < samples_.size() && samples_[j] < upper_bound) {
      if (samples_[j] >=
          lower_bound) // Убедимся, что значение попадает в интервал
      {
        ++ni;
      }
      ++j;
    }

    // Нормализация плотности
    density_[i] =
        static_cast<double>(ni) / (samples_.size() * (samples_len / size_));
  }

  // Проверка суммарной плотности (должна быть близка к 1.0 для нормализованной
  // PDF)
  double sum_density = 0.0;
  for (double d : density_) {
    sum_density += d;
  }
}

// Конструкторы
EmpiricalDistribution::EmpiricalDistribution() : size_(0), min_(0), max_(0) {}

EmpiricalDistribution::EmpiricalDistribution(const std::vector<double> &samples,
                                             size_t size)
    : samples_(samples), size_(size) {
  min_ = *std::min_element(samples_.begin(), samples_.end());
  max_ = *std::max_element(samples_.begin(), samples_.end());
  calculateDensity();
}

EmpiricalDistribution::EmpiricalDistribution(const IDistribution &dist, int n) {
  samples_.resize(n);
  for (int i = 0; i < n; ++i) {
    samples_[i] = dist.generate();
  }
  size_ = n;
  min_ = *std::min_element(samples_.begin(), samples_.end());
  max_ = *std::max_element(samples_.begin(), samples_.end());
  calculateDensity();
}

EmpiricalDistribution::EmpiricalDistribution(
    const MixDistribution<MainDistribution, MainDistribution> &dist, int n) {
  samples_.resize(n);
  for (int i = 0; i < n; ++i) {
    samples_[i] = dist.generate();
  }
  size_ = n;
  min_ = *std::min_element(samples_.begin(), samples_.end());
  max_ = *std::max_element(samples_.begin(), samples_.end());
  calculateDensity();
}

// Конструктор копирования
EmpiricalDistribution::EmpiricalDistribution(const EmpiricalDistribution &other)
    : samples_(other.samples_), density_(other.density_), size_(other.size_),
      min_(other.min_), max_(other.max_) {}

// Оператор присваивания
EmpiricalDistribution &
EmpiricalDistribution::operator=(const EmpiricalDistribution &other) {
  if (this != &other) {
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
double EmpiricalDistribution::pdf(double x) const {
  if (x < min_ || x > max_)
    return 0.0;
  double binWidth = (max_ - min_) / size_;
  int bin = static_cast<int>((x - min_) / binWidth);
  return density_[bin];
}

double EmpiricalDistribution::expectation() const {
  double sum = 0.0;
  for (double sample : samples_) {
    sum += sample;
  }
  return sum / samples_.size();
}

double EmpiricalDistribution::variance() const {
  double mean = expectation();
  double sum = 0.0;
  for (double sample : samples_) {
    sum += (sample - mean) * (sample - mean);
  }
  return sum / samples_.size();
}

double EmpiricalDistribution::skewness() const {
  double mean = expectation();
  double stdDev = std::sqrt(variance());
  double sum = 0.0;
  for (double sample : samples_) {
    sum += std::pow((sample - mean) / stdDev, 3);
  }
  return sum / samples_.size();
}

double EmpiricalDistribution::excessKurtosis() const {
  double mean = expectation();
  double stdDev = std::sqrt(variance());
  double sum = 0.0;
  for (double sample : samples_) {
    sum += std::pow((sample - mean) / stdDev, 4);
  }
  return (sum / samples_.size()) - 3;
}

void EmpiricalDistribution::generateGraphPoints(
    const std::string &filename) const {
  if (samples_.empty()) {
    std::cerr << "Error: samples vector is empty!\n";
    return;
  }

  // Константы для построения графика
  const int N = 1000; // Количество точек
  double x1 = -10;    // Минимальное значение
  double x2 = 10;     // Максимальное значение
  double dx = (x2 - x1) / (double)(N - 1); // Шаг изменения x

  std::ofstream file(filename);
  if (!file) {
    std::cerr << "Error: Unable to open file " << filename << " for writing.\n";
    return;
  }

  std::cout << "Generating graph data: " << filename << std::endl;

  // Сортируем выборку и вычисляем диапазон
  std::vector<double> sorted_samples = samples_;
  std::sort(sorted_samples.begin(), sorted_samples.end());
  double samples_min = sorted_samples.front();
  double samples_max = sorted_samples.back();
  double samples_len = samples_max - samples_min;

  // Проверка диапазона
  if (samples_len <= 0) {
    std::cerr
        << "Error: Samples length is zero or negative in generateGraphPoints!"
        << std::endl;
    file.close();
    return;
  }

  // Определяем количество интервалов (используем size_, вычисленное в
  // calculateDensity)
  size_t k = size_;

  // Генерация значений для построения графика
  size_t bin_index = 0;
  for (int i = 0; i < N; ++i) {
    double x = x1 + i * dx;

    // Если x вне диапазона выборки, плотность = 0
    if (x < samples_min || x > samples_max) {
      file << x << '\t' << 0.0 << std::endl;
    } else {
      // Найдём соответствующий интервал
      while (bin_index < k - 1 &&
             x >= samples_min + ((double)(bin_index + 1) / k) * samples_len) {
        bin_index++;
      }
      double density = density_[bin_index]; // Используем плотности из density_

      file << x << '\t' << density << std::endl;
    }
  }

  file.close();
  std::cout << "Graph data saved successfully to " << filename << std::endl;
}

// Реализация метода для генерации одного случайного числа
double EmpiricalDistribution::generate() const {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, size_ - 1);
  return samples_[dis(gen)];
}

// Реализация метода для генерации n случайных чисел
std::vector<double> EmpiricalDistribution::generate(int n) const {
  std::vector<double> result(n);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, size_ - 1);
  for (int i = 0; i < n; ++i) {
    result[i] = samples_[dis(gen)];
  }
  return result;
}

// сохранение атрибутов в файл
void EmpiricalDistribution::save_params(std::string filename) const {
  std::ofstream file(filename);
  if (!file) {
    throw std::runtime_error("Unable to open file for saving parameters.");
  }
  for (const auto &sample : samples_) {
    file << sample << "\n";
  }
  file.close();
}

void EmpiricalDistribution::load_params(std::string filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("Unable to open file for loading parameters.");
  }
  samples_.clear();
  double sample;
  while (file >> sample) {
    samples_.push_back(sample);
  }
  size_ = samples_.size();
  min_ = *std::min_element(samples_.begin(), samples_.end());
  max_ = *std::max_element(samples_.begin(), samples_.end());
  calculateDensity();
  file.close();
}