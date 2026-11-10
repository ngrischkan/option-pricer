import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("final_prices.csv")
plt.hist(df["price"], bins=100)
plt.axvline(100, color="black", linestyle="--", label="strike")
plt.xlabel("Final stock price")
plt.ylabel("Number of simulations")
plt.title("Distribution of 100,000 final prices")
plt.legend()
plt.savefig("images/final_prices.png")
plt.show()
print((df["price"] > 100).mean())