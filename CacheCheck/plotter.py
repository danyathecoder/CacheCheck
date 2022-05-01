import matplotlib.pyplot as plt
import numpy as np
 
with open("data.txt", "r") as f:
	x = f.readlines()
	x = [int(i.strip()) for i in x]

y = list(range(1, 21))

# plotting the points
plt.plot(y, x)
# show points
plt.scatter(y, x)
# naming the x axis
plt.xlabel('x - amount of ways')
# naming the y axis
plt.ylabel('y - ticks')
 
# giving a title to my graph
plt.title('Experemental determination of cache\'s degree of associativity')
major_ticks = np.arange(y[0], int(len(y)), 1)
plt.yticks(major_ticks)
plt.grid(True)
plt.show()