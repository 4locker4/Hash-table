import matplotlib.pyplot as plt

lengths = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
counts  = [3, 12, 45, 108, 240, 300, 360, 300, 180, 108, 72, 36, 24, 12, 6, 3, 3]

plt.figure (figsize=(10, 6))
plt.bar (lengths, counts, color='skyblue')
plt.xlabel ('Длина слова')
plt.ylabel ('Количество слов')
plt.title ('Распределение длин слов')
plt.xticks (lengths)
plt.grid (axis='y', linestyle='--', alpha=0.7)
plt.show ()