import random

m = 1000
n = 3000

with open("input.txt", "w") as file:
    file.write(f"{m} {n}\n")
    for _ in range(m):
        row = " ".join(str(random.randint(1, 10)) for _ in range(n))
        file.write(row + "\n")
