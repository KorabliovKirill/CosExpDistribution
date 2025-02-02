import os
import matplotlib.pyplot as plt
import numpy as np

# Функция для обработки файлов в директории
def process_directory(directory):
    # Для директории emp_distribution обрабатываем пары файлов
    if "emp_distribution" in directory:
        # Получаем все файлы в директории
        files = os.listdir(directory)
        # Фильтруем файлы по заданным условиям
        distribution_files = [f for f in files if f.startswith("distribution") and f.endswith(".txt")]
        emp_distribution_files = [f for f in files if f.startswith("emp_distribution") and f.endswith(".txt")]

        # Перебираем пары файлов
        for distribution_file in distribution_files:
            number = distribution_file.split("distribution")[1].split(".")[0]
            emp_file = f"emp_distribution{number}.txt"

            if emp_file in emp_distribution_files:
                # Чтение данных из файлов
                data1 = np.loadtxt(os.path.join(directory, distribution_file))
                data2 = np.loadtxt(os.path.join(directory, emp_file))

                x1, y1 = data1[:, 0], data1[:, 1]
                x2, y2 = data2[:, 0], data2[:, 1]

                # Построение графиков
                plt.figure(figsize=(10, 6))

                # Теоретическое распределение
                plt.plot(
                    x1, y1, color="blue", label="Теоретическое распределение", linewidth=2
                )

                # Эмпирическое распределение (ступенчатый график)
                plt.step(
                    x2, y2, where="mid", color="orange", label="Эмпирическое распределение", linewidth=2
                )

                # Настройка графика
                plt.title(f"Наложенные графики: {distribution_file} и {emp_file}")
                plt.xlabel("X")
                plt.ylabel("Плотность вероятности")
                plt.legend()
                plt.grid()

                # Сохранение графика
                output_filename = os.path.join(directory, f"combined_{number}.png")
                plt.savefig(output_filename)
                plt.close()

    else:
        # Для остальных директорий обрабатываем одиночные файлы
        for filename in os.listdir(directory):
            filepath = os.path.join(directory, filename)
            if filename.endswith(".txt") and os.path.isfile(filepath):  # Фильтруем только текстовые файлы
                data = np.loadtxt(filepath)
                x, y = data[:, 0], data[:, 1]

                # Построение графика
                plt.figure(figsize=(10, 6))
                plt.plot(x, y, marker="o", linestyle="-", color="blue", label="График")
                plt.xlabel("X")
                plt.ylabel("Y")
                plt.title(f"График из файла {filename}")
                plt.legend()
                plt.grid()

                # Сохранение графика
                output_filename = os.path.join(directory, filename.replace(".txt", ".png"))
                plt.savefig(output_filename)
                plt.close()

# Обходим все директории, исключая .venv
for root, dirs, files in os.walk("."):
    if ".venv" in root:
        continue
    process_directory(root)
