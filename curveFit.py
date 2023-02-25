import numpy as np
from scipy.optimize import curve_fit

# Define the power law function
def power_func(x, a, b):
    return a * np.power(x, b)

# Enter the x and y data points as arrays
x_data = np.array([128, 256, 512, 1024, 2048, 4096, 8192, 16384])
y_data_d1 = np.array([.09, .04, .023, .009, .005, .003, .0015, .0008])
y_data_d2 = np.array([0.24, 0.16, 0.128, 0.065, 0.045, 0.035, 0.025, 0.02])
y_data_d3 = np.array([0.4, 0.30, 0.25, 0.18, 0.15, 0.11, 0.095, 0.075])
y_data_d4 = np.array([0.6, 0.45, 0.35, 0.3, 0.25, 0.2, 0.175, 0.15])

# Use curve_fit to find the coefficients of the power law function that best fit the data
popt, pcov = curve_fit(power_func, x_data, y_data_d4)

# The coefficients are stored in the popt array
a = popt[0]
b = popt[1]

# Print the coefficients
print("a =", a)
print("b =", b)



