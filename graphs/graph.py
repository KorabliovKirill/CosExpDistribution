import os
import matplotlib.pyplot as plt
import numpy as np

# Функция для обработки файлов в директории
def process_directory(directory):
    if "emp_distribution" in directory:
        files = os.listdir(directory)

        process_file_pairs(
            directory, files,
            prefix1="distribution",
            prefix2="emp_main_distribution",
            output_prefix="main_combined",
            title_prefix="Основное распределение"
        )

        process_file_pairs(
            directory, files,
            prefix1="mix_distribution",
            prefix2="emp_mix_distribution",
            output_prefix="mix_combined",
            title_prefix="Смесь распределений"
        )

    else:
        for filename in os.listdir(directory):
            filepath = os.path.join(directory, filename)
            if filename.endswith(".txt") and os.path.isfile(filepath):
                data = np.loadtxt(filepath)
                x, y = data[:, 0], data[:, 1]

                plt.figure(figsize=(10, 6))
                plt.plot(x, y, marker="o", linestyle="-", color="blue", label="График")
                plt.xlabel("X")
                plt.ylabel("Y")
                plt.title(f"График из файла {filename}")
                plt.legend()
                plt.grid()

                output_filename = os.path.join(directory, filename.replace(".txt", ".png"))
                plt.savefig(output_filename)
                plt.close()

# Вспомогательная функция для обработки пар файлов
def process_file_pairs(directory, files, prefix1, prefix2, output_prefix, title_prefix):
    files1 = [f for f in files if f.startswith(prefix1) and f.endswith(".txt")]
    files2 = [f for f in files if f.startswith(prefix2) and f.endswith(".txt")]

    for file1 in files1:
        number = file1.split(prefix1)[1].split(".")[0]
        file2 = f"{prefix2}{number}.txt"

        if file2 in files2:
            data1 = np.loadtxt(os.path.join(directory, file1))
            data2 = np.loadtxt(os.path.join(directory, file2))

            x1, y1 = data1[:, 0], data1[:, 1]
            x2, y2 = data2[:, 0], data2[:, 1]

            plt.figure(figsize=(10, 6))

            # Сначала рисуем эмпирическое распределение
            plt.plot(
                x2, y2, color="orange", label="Эмпирическое распределение", linewidth=2
            )

            # Затем рисуем теоретическое распределение поверх
            plt.plot(
                x1, y1, color="blue", label="Теоретическое распределение", linewidth=2
            )

            plt.title(f"{title_prefix}: {file1} и {file2}")
            plt.xlabel("X")
            plt.ylabel("Плотность вероятности")
            plt.legend()
            plt.grid()

            output_filename = os.path.join(directory, f"{output_prefix}_{number}.png")
            plt.savefig(output_filename)
            plt.close()

# Обходим все директории, исключая .venv
for root, dirs, files in os.walk("."):
    if ".venv" in root:
        continue
    process_directory(root)