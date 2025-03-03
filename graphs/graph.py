import os
import matplotlib.pyplot as plt
import numpy as np

# Функция для обработки файлов в директории
def process_directory(directory):
    # Для директории emp_distribution обрабатываем пары файлов
    if "emp_distribution" in directory:
        # Получаем все файлы в директории
        files = os.listdir(directory)
        print(f"Обработка директории: {directory}")
        print(f"Найденные файлы: {files}")

        # Обрабатываем пары для основных распределений
        process_file_pairs(
            directory, files,
            prefix1="distribution",
            prefix2="emp_main_distribution",
            output_prefix="main_combined",
            title_prefix="Основное распределение"
        )

        # Обрабатываем пары для смеси распределений
        process_file_pairs(
            directory, files,
            prefix1="mix_distribution",
            prefix2="emp_mix_distribution",
            output_prefix="mix_combined",
            title_prefix="Смесь распределений"
        )

    else:
        # Для остальных директорий обрабатываем одиночные файлы
        for filename in os.listdir(directory):
            filepath = os.path.join(directory, filename)
            if filename.endswith(".txt") and os.path.isfile(filepath):  # Фильтруем только текстовые файлы
                try:
                    data = np.loadtxt(filepath, delimiter=" ")
                    x, y = data[:, 0], data[:, 1]

                    if len(x) == 0 or len(y) == 0:
                        print(f"Нет данных для построения графика из {filename}")
                        continue

                    # Построение графика
                    plt.figure(figsize=(10, 6))
                    plt.plot(x, y, marker="o", linestyle="-", color="blue", label="График")
                    plt.xlabel("X")
                    plt.ylabel("Y")
                    plt.title(f"График из файла {filename}")
                    plt.legend()
                    plt.grid()

                    # Сохранение графика
                    os.makedirs(directory, exist_ok=True)  # Создаём директорию, если её нет
                    output_filename = os.path.join(directory, filename.replace(".txt", ".png"))
                    plt.savefig(output_filename)
                    plt.show()  # Показываем график на экране (можно убрать, если не нужно)
                    plt.close()

                except Exception as e:
                    print(f"Ошибка при обработке файла {filename}: {e}")

def process_file_pairs(directory, files, prefix1, prefix2, output_prefix, title_prefix):
    """
    Обрабатывает пары файлов, строит наложенные графики (ступенчатая линия для эмпирического и линия с крестиками для теоретического) и сохраняет их.

    :param directory: Директория для обработки.
    :param files: Список файлов в директории.
    :param prefix1: Префикс первого файла в паре (теоретическое).
    :param prefix2: Префикс второго файла в паре (эмпирическое).
    :param output_prefix: Префикс для сохранения графиков.
    :param title_prefix: Префикс для заголовков графиков.
    """
    # Фильтруем файлы по указанным префиксам
    files1 = [f for f in files if f.startswith(prefix1) and f.endswith(".txt")]
    files2 = [f for f in files if f.startswith(prefix2) and f.endswith(".txt")]

    # Перебираем пары файлов
    for file1 in files1:
        # Ищем соответствующий файл второго типа
        number = file1.split(prefix1)[1].split(".")[0]
        file2 = f"{prefix2}{number}.txt"

        if file2 in files2:
            # Чтение данных из файлов
            data1 = np.loadtxt(os.path.join(directory, file1))
            data2 = np.loadtxt(os.path.join(directory, file2))

            x1, y1 = data1[:, 0], data1[:, 1]
            x2, y2 = data2[:, 0], data2[:, 1]

            # Построение графиков
            plt.figure(figsize=(10, 6))

            # Теоретическое распределение (синяя линия с крестиками)
            plt.plot(
                x1, y1, color="blue", label="Теоретическое распределение", 
                linewidth=0.5, marker='o', markersize=10, markeredgewidth=2
            )

            # Эмпирическое распределение (ступенчатая оранжевая линия)
            plt.step(
                x2, y2, where="mid", color="orange", label="Эмпирическое распределение", linewidth=2
            )

            # Настройка графика
            plt.title(f"{title_prefix}: {file1} и {file2}")
            plt.xlabel("X")
            plt.ylabel("Плотность вероятности")
            plt.legend()
            plt.grid(True, linestyle='--', alpha=0.7)

            # Сохранение графика
            os.makedirs(directory, exist_ok=True)  # Создаём директорию, если её нет
            output_filename = os.path.join(directory, f"{output_prefix}_{number}.png")
            plt.savefig(output_filename)
            plt.close()

# Остальная часть скрипта остаётся прежней
for root, dirs, files in os.walk("."):
    if ".venv" in root:
        continue
    process_directory(root)