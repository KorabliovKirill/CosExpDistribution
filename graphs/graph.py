import matplotlib.pyplot as plt
import os

# Функция для обработки файлов в директории
def process_directory(directory):
    for filename in os.listdir(directory):
        filepath = os.path.join(directory, filename)
        if filename.endswith(".txt") and os.path.isfile(filepath):  # Фильтруем только текстовые файлы
            x_values = []
            y_values = []
            
            with open(filepath, "r") as file:
                for line in file:
                    x, y = map(float, line.split())  # Разделяем строку по пробелу и конвертируем в числа
                    x_values.append(x)
                    y_values.append(y)
            
            # Строим график
            plt.figure(figsize=(8, 6))
            plt.plot(x_values, y_values, marker="o", linestyle="-", color="b", label="График")
            plt.xlabel("X")
            plt.ylabel("Y")
            plt.title(f"График из файла {filename}")
            plt.legend()
            plt.grid()
            
            # Сохраняем график в той же директории
            output_filename = os.path.join(directory, filename.replace(".txt", ".png"))
            plt.savefig(output_filename)
            plt.close()

# Обходим все директории кроме .venv
for root, dirs, files in os.walk("."):
    if ".venv" in root:
        continue
    process_directory(root)