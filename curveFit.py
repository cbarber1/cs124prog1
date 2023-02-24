import numpy as np
from scipy.optimize import curve_fit

# Define the power law function
def power_func(x, a, b):
    return a * np.power(x, b)

# Enter the x and y data points as arrays
x_data = np.array([128, 256, 512, 1024, 2048, 4096, 8192, 16384])
y_data = np.array([.09, .04, .023, .009, .005, .003, .0015, .0008])

# Use curve_fit to find the coefficients of the power law function that best fit the data
popt, pcov = curve_fit(power_func, x_data, y_data)

# The coefficients are stored in the popt array
a = popt[0]
b = popt[1]

# Print the coefficients
print("a =", a)
print("b =", b)



