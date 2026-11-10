#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>

const double S0 = 100.0;  // today's price
const double r = 0.05;    // interest rate
const double sigma = 0.2; // volatility
const double T = 1.0;     // time in years
const double K = 100.0; // strike price

int main()
{
    std::mt19937 rng(42);
    std::normal_distribution<double> z_dist(0.0, 1.0);
    double total = 0;
    for (int i = 0; i < 100000; i++)
    {
        double price = S0 * std::exp((r - ((sigma * sigma) / 2)) * T + sigma * std::sqrt(T) * z_dist(rng));
        total += std::max(price - K, 0.0);
    }
    double avg_payoff = total / 100000;
    double call_price = std::exp(-r * T) * avg_payoff;
    std::cout << call_price << std::endl;
    return 0;
}