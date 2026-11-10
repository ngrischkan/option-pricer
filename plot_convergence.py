import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
df = pd.read_csv("convergence.csv")
plt.loglog(df["N"], df["se"], "o-")
plt.xlabel("Number of simulations (N)")
plt.ylabel("Standard error")
plt.title("Monte Carlo convergence")
plt.loglog(df["N"], df["se"].iloc[0] * np.sqrt(1000 / df["N"]), "--", label="theory: slope -1/2")
plt.loglog(df["N"], df["se"].iloc[-1] * np.sqrt(df["N"].iloc[-1] / df["N"]), "--", label="theory: slope -1/2")
plt.legend()
plt.savefig("images/convergence.png")
plt.show()
slope, intercept = np.polyfit(np.log10(df["N"]), np.log10(df["se"]), 1)
print(slope)