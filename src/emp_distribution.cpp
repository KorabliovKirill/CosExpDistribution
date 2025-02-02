#include "emp_distribution.hpp"
#include <algorithm>

namespace EmpDistribution
{
    double pdf(double x, std::vector<double> &samples)
    {
        double samples_max = *std::max_element(samples.begin(), samples.end());
        double samples_min = *std::min_element(samples.begin(), samples.end());

        if (x < samples_min || x > samples_max)
            return 0;

        double samples_len = samples_max - samples_min;
        int k = (int)log2(samples.size()) + 1;

        sort(samples.begin(), samples.end());

        int ni = 0;
        for (int i = 0; i < k; i++)
        {
            if (samples_min + ((double)i / (double)k) * samples_len <= x && samples_min + ((double)(i + 1) / (double)k) * samples_len > x)
            { // проверка на попадание в промежуток Xi
                int j = 0;
                while (samples[j] < samples_min + ((double)i / (double)k) * samples_len)
                { // поиск номера первого элемента выборки, входящего в Xi
                    j++;
                }
                ni = 0;
                for (int j = 0; j < samples.size(); j++)
                {
                    if (samples[j] >= samples_min + (double)i / k * samples_len &&
                        samples[j] < samples_min + (double)(i + 1) / k * samples_len)
                    {
                        ni++;
                    }
                }
                return (double)ni / (samples.size() * samples_len / (double)k);
            }
        }

        return 0;
    }

    double expectation(std::vector<double> &samples)
    {
        double sum = 0;
        for (int i = 0; i < samples.size(); i++)
        {
            sum += samples[i];
        }
        return sum / (double)samples.size();
    }

    double variance(std::vector<double> &samples)
    {
        double sum = 0;
        double exp_val = expectation(samples);
        for (int i = 0; i < samples.size(); i++)
        {
            sum += (samples[i] - exp_val) * (samples[i] - exp_val);
        }
        return sum / (double)samples.size();
    }

    double skewness(std::vector<double> &samples)
    {
        double sum = 0;
        double exp_val = expectation(samples);
        for (int i = 0; i < samples.size(); i++)
        {
            sum += (samples[i] - exp_val) * (samples[i] - exp_val) * (samples[i] - exp_val);
        }
        return sum / ((double)samples.size() * pow(variance(samples), 1.5));
    }

    double excessKurtosis(std::vector<double> &samples)
    {
        double sum = 0;
        double exp_val = expectation(samples);
        for (int i = 0; i < samples.size(); i++)
        {
            sum += (samples[i] - exp_val) * (samples[i] - exp_val) * (samples[i] - exp_val) * (samples[i] - exp_val);
        }
        return sum / ((double)samples.size() * pow(variance(samples), 2));
    }

    std::vector<double> generate(int n, std::vector<double> &samples)
    {
        if (samples.empty()) // Проверка на пустой вектор
            throw std::invalid_argument("Samples vector is empty!");

        // Сортируем выборку, находим минимальное и максимальное значения
        std::sort(samples.begin(), samples.end());
        double samples_min = samples.front();
        double samples_max = samples.back();
        double samples_len = samples_max - samples_min;

        // Количество интервалов для деления диапазона
        int k = static_cast<int>(std::log2(samples.size())) + 1;
        std::vector<double> pi(k);

        // Подсчет вероятности для каждого интервала
        int ni = 0;
        int j = 0;
        for (int i = 0; i < k; ++i)
        {
            ni = 0;
            double upper_bound = samples_min + (static_cast<double>(i + 1) / k) * samples_len;
            while (j < samples.size() && samples[j] < upper_bound)
            {
                ++ni;
                ++j;
            }
            pi[i] = static_cast<double>(ni) / samples.size(); // Частота значений в интервале
        }

        // Настроим генератор случайных чисел
        std::mt19937 generator(std::random_device{}());           // Генератор случайных чисел
        std::uniform_real_distribution<double> uniform(0.0, 1.0); // Равномерное распределение на [0, 1)

        // Генерация случайных значений
        std::vector<double> result;
        result.reserve(n);

        for (int j = 0; j < n; ++j)
        {
            double r1 = 0.0;
            double r2 = 0.0;

            // Генерация случайных чисел для выбора интервала
            r1 = uniform(generator);
            r2 = uniform(generator);

            // Нахождение интервала, в который попадает случайное число
            double p = 0;
            int i_cur = 0;
            for (int i = 0; i < k; ++i)
            {
                if (p < r1 && r1 < p + pi[i])
                {
                    i_cur = i;
                    break;
                }
                p += pi[i];
            }

            // Генерация значения внутри выбранного интервала
            double random_value = (samples_len / k) * (i_cur + r2) + samples_min;
            result.push_back(random_value);
        }

        return result;
    }

    std::vector<double> samples(int n, double v, double mu, double lambda)
    {
        if (n <= 0)
        {
            throw std::invalid_argument("Sample size n must be greater than 0.");
        }

        MainDistribution dist(v, mu, lambda);

        std::vector<double> samples;
        samples.reserve(n); // Резервируем память заранее для улучшения производительности

        // Генерация случайных значений
        for (int i = 0; i < n; ++i)
        {
            double sample_value = dist.generate();
            samples.push_back(sample_value);
        }

        return samples;
    }

    std::vector<double> samples(int n, double v1, double mu1, double lambda1, double v2, double mu2, double lambda2, double p)
    {
        if (n <= 0)
        {
            throw std::invalid_argument("Sample size n must be greater than 0.");
        }

        std::vector<double> samples;
        samples.reserve(n); // Резервируем память заранее

        // Генерация случайных значений для смеси распределений
        for (int i = 0; i < n; ++i)
        {
            double sample_value = MixDistribution::generate(v1, mu1, lambda1, v2, mu2, lambda2, p);
            samples.push_back(sample_value);
        }

        return samples;
    }

    std::vector<double> samples(int n, std::vector<double> &samples)
    {
        if (n <= 0)
        {
            throw std::invalid_argument("Sample size n must be greater than 0.");
        }

        // Генерация выборки на основе эмпирического распределения
        return generate(n, samples);
    }

    void generateGraphPoints(std::vector<double> &samples, std::string filename)
    {
        if (samples.empty())
        {
            std::cerr << "Error: samples vector is empty!\n";
            return;
        }

        // Константы для построения графика
        const int N = 1000;                      // Количество точек
        double x1 = -10;                         // Минимальное значение из выборки
        double x2 = 10;                          // Максимальное значение
        double dx = (x2 - x1) / (double)(N - 1); // Шаг изменения x

        std::ofstream file(filename);
        if (!file)
        {
            std::cerr << "Error: Unable to open file " << filename << " for writing.\n";
            return;
        }

        std::cout << "Generating graph data: " << filename << std::endl;

        // Сортируем выборку
        std::sort(samples.begin(), samples.end());
        double samples_min = samples.front();
        double samples_max = samples.back();
        double samples_len = samples_max - samples_min;

        // Определяем количество интервалов k
        int k = (int)std::log2(samples.size()) + 1;
        std::vector<double> fi(k, 0.0);

        // Подсчёт частот fi[i]
        int ni = 0;
        int j = 0;
        for (int i = 0; i < k; i++)
        {
            ni = 0;
            double upper_bound = samples_min + ((double)(i + 1) / k) * samples_len;
            while (j < samples.size() && samples[j] < upper_bound)
            {
                ni++;
                j++;
            }
            fi[i] = (double)ni / (samples.size() * (samples_len / (double)k));
        }

        // Генерация значений для построения графика
        int bin_index = 0;
        for (int i = 0; i < N; i++)
        {
            double x = x1 + i * dx;

            // Если x вне диапазона выборки, плотность = 0
            if (x < samples_min || x > samples_max)
            {
                file << x << '\t' << 0.0 << std::endl;
            }
            else
            {
                // Найдём соответствующий интервал
                while (bin_index < k - 1 && x >= samples_min + ((double)(bin_index + 1) / k) * samples_len)
                {
                    bin_index++;
                }
                file << x << '\t' << fi[bin_index] << std::endl;
            }
        }

        file.close();
        std::cout << "Graph data saved successfully to " << filename << std::endl;
    }
}