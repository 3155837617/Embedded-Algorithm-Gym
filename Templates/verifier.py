import random
with open("input.txt", "w") as f:
    f.write(" ".join([str(random.randint(0,100)) for _ in range(10)]))
print("Data generated.")
