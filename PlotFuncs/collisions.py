import matplotlib.pyplot as plt

with open('Text/CollisionsCRC32.txt', 'r') as file:
    data = [int(line.strip()) for line in file]

line_numbers = range(1, len(data) + 1)

plt.figure(figsize=(15, 6))
plt.bar(line_numbers, data, color='skyblue', width=0.8)
plt.xlabel('Ячейка таблицы')
plt.ylabel('Количество элементов')
plt.grid(axis='y', linestyle='--', alpha=0.7)

plt.show()