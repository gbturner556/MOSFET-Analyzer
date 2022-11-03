import matplotlib.pyplot as plt
import os
import sys
import pandas as pd
import numpy as np

# if we have no CL arguments just quit
if len(sys.argv) == 1:
    sys.exit()
# if we only have one argument lets assume its the
# data_dir and give the name a default name
elif len(sys.argv) == 2:
    fet_name = "MOSFET Device"
    data_dir = sys.argv[1]
# otherwise assume the argument 1 is the name
# and argument 2 is the data_dir
else:
    fet_name = sys.argv[1]
    data_dir = sys.argv[2]

ax = plt.subplot(111)
plt.title(fet_name + " Characteristic Curves")
plt.ylabel("I_dd [A]")
plt.xlabel("V_dd [V]")
labels = []



# go through all the files in the directory
for filename in os.listdir(data_dir):

    # merge the filename and directory name to get the path
    # grabbed this from g4g
    # https://www.geeksforgeeks.org/how-to-iterate-over-files-in-directory-using-python/
    csv_path = os.path.join(data_dir, filename)

    # extract the extension
    # grabbed this from stack overflow
    # https://stackoverflow.com/questions/5899497/how-can-i-check-the-extension-of-a-file
    ext = os.path.splitext(csv_path)[-1].lower()

    # if the file is not a csv skip it
    if ext != ".csv":
        continue

    # extract the csv to a dataframe
    df = pd.read_csv(csv_path, sep=",", header=0)

    # convert to a normal 2-D array
    # we should be able to do all this in df but pandas is being difficult
    curve_data = df.to_numpy()

    # extract the gate voltage and add it to labels
    labels.append("V_gs = " + str(curve_data[0, 2]))

    # extract the drain voltage data
    v_ds = curve_data[:, 0]

    # extract the drain current data
    i_dd = curve_data[:, 1]

    # plot v_ds vs i_dd
    ax.plot(v_ds, i_dd)

    # add labels to legend
    ax.legend(labels)

# show the plot
plt.show()

# for debugging
# print("V_gs: ", labels)
# print("V_ds: ", v_ds)
# print("V_ds: ", i_dd)
