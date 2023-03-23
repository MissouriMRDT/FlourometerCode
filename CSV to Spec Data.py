import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.signal import argrelextrema, argrelmax

#MOLECULE NAME

plt.rcParams["figure.figsize"] = [7.50, 3.50]
plt.rcParams["figure.autolayout"] = True

#read data into dataframe
df = pd.read_csv('CSVFILENAME')

#convert csv data into arrays
Wavelengths = df.iloc[:,0].to_numpy()
Intensity_data = df.iloc[:,1].to_numpy()

#pick out maximum value
Max_I = np.amax(Intensity_data)

#normalize intensity
Norm_Int = Intensity_data / Max_I

plt.plot(Wavelengths, Norm_Int, linewidth=0.8)

#plotting
plt.title('Spectral Data')
plt.xlabel('Wavelength')
plt.ylabel('Intensity (Normalized)')

plt.grid()
plt.show()

#defining max and min of numbers
relmaxraw = argrelextrema(Norm_Int, np.greater, 0, 3)
relminraw = argrelextrema(Norm_Int, np.less, 0, 3)

#picking out the values from the bullshit
relmaxind = relmaxraw[0]
relminind = relminraw[0]

#printing max and min values
max_index=np.where(Intensity_data == Max_I)[0][0]

#printing the useful numbers
for x in relmaxind:
    if x == max_index:
        continue
    print("Relative Peak at " + str(Wavelengths[x]) + "nm")

for x in relminind:
    print("Relative dip at " + str(Wavelengths[x]) + "nm")

print(" ")
    
print("Peak Wavelength " + str(Wavelengths[max_index]) + "nm")