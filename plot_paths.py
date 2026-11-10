import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("paths.csv")
for path_id, group in df.groupby("path"):
    plt.plot(group["step"], group["price"], linewidth=0.8)
plt.axhline(100, color="black", linestyle="--")   # the strike
plt.xlabel("Trading day")
plt.ylabel("Stock price")
plt.title("50 simulated price paths")
plt.savefig("images/paths.png")
plt.show()