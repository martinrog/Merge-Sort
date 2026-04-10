import matplotlib.pyplot as plt

threads = [1, 2, 4, 8]
times = [0.0097638, 0.0056115, 0.003744, 0.0041862]


plt.figure()

plt.plot(threads, times, marker='o')

plt.title("Runtime van parallel merge sort")
plt.xlabel("Aantal threads")
plt.ylabel("Tijd (seconden)")


# plt.xticks(threads)

plt.grid()

plt.savefig("runtime_plot.png")