import matplotlib.pyplot as plt

try:
    file = open("saved_training0.txt", "r")  # Open for reading
    

    allInfo = file.readlines()
    gens = len(allInfo)

    xpoints = list(range(1,gens))
    ypoints = list(range(1,gens))

    for i in range(1,gens):
        ypoints[i-1] = float(allInfo[i])

    plt.plot(xpoints, ypoints)

    plt.show()

    file.close()
except FileNotFoundError:
    print("File not found.")
except IOError as e:
    print(f"An I/O error occurred: {e}")



