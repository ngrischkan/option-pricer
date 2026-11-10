#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <vector>

const double S0 = 100.0;  // today's price
const double r = 0.05;    // interest rate
const double sigma = 0.2; // volatility
const double T = 1.0;     // time in years
const double K = 100.0;   // strike price

struct MCResult
{
    double price;
    double se;
};

MCResult monte_carlo_call(int N, std::mt19937 &rng)
{
    double total = 0;
    double total_sq = 0;
    std::normal_distribution<double> z_dist(0.0, 1.0);
    for (int i = 0; i < N; i++)
    {
        double price = S0 * std::exp((r - ((sigma * sigma) / 2)) * T + sigma * std::sqrt(T) * z_dist(rng));
        double payoff = std::max(price - K, 0.0);
        total += payoff;
        total_sq += payoff * payoff;
    }
    double x_bar = total / N;
    double call_price = std::exp(-r * T) * x_bar;
    double variance = (total_sq / N) - x_bar * x_bar;
    double SE = std::exp(-r * T) * std::sqrt(variance / N);
    return {call_price, SE};
}

double norm_cdf(double x)
{
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

double black_scholes_call()
{
    double d1 = (std::log(S0 / K) + (r + (sigma * sigma) / 2) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);
    double C = S0 * norm_cdf(d1) - K * std::exp(-r * T) * norm_cdf(d2);
    return C;
}

int main()
{
    std::mt19937 rng(42);
    std::vector<int> sizes = {1000, 4000, 16000, 64000, 256000, 1024000};
    double C = black_scholes_call();
    std::cout << "N\tprice\tSE\tdiff/SE" << std::endl;
    for (int N : sizes)
    {
        MCResult result = monte_carlo_call(N, rng);
        std::cout << N << "\t" << result.price << "\t" << result.se << "\t" << (result.price - C) / result.se << std::endl;
    }
    return 0;
}