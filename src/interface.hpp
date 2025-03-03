#pragma once
#include <string>

#define interface struct

interface IDistribution { // интерфейс распределения
  virtual double pdf(double x)
      const = 0; // функция для вычисления плотности распределения
  virtual double expectation() const = 0; // математическое ожидание
  virtual double variance() const = 0; // дисперсия
  virtual double skewness() const = 0; // коэффициент асимметрии
  virtual double excessKurtosis() const = 0; // коэффициент эксцесса
  virtual double generate()
      const = 0; // функция для моделирования случайной величины
};

interface IPersistent { // интерфейс персистентного объекта
  virtual void save_params(std::string filename)
      const = 0; // сохранение параметров в файл
  virtual void load_params(
      std::string filename) = 0; // загрузка параметров из файла
};