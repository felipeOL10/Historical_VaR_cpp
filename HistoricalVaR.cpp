#include <iostream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include "rapidcsv.h"

using namespace std;

// Function to calculate historical VaR
double calculateHistoricalVaR(vector<double>& closePrices, double confidenceLevel) {
    // Sort close prices in ascending order
    vector<double> sortedPrices = closePrices;
    sort(sortedPrices.begin(), sortedPrices.end());

    // Calculate the index corresponding to the confidence level
    int index = static_cast<int>(sortedPrices.size() * (1 - confidenceLevel));

    // Return the historical VaR
    return sortedPrices[index];
}

int main() {

    filesystem::path currentPath = filesystem::current_path();

    cout << currentPath << endl;

    rapidcsv::Document doc("TSLA.csv");
    vector<double> closePrices = doc.GetColumn<double>("Close");

    vector<double> returns;
    for (size_t i = 1; i < closePrices.size(); ++i) {
        double ret = (closePrices[i] - closePrices[i - 1]) / closePrices[i - 1];
        returns.push_back(ret);
        }

    // Specify the confidence level (e.g., 0.95 for 95% confidence)
    double confidenceLevel = 0.95;

    // Calculate the historical VaR
    double var = calculateHistoricalVaR(closePrices, confidenceLevel);

    // Output the result
    std::cout << "Historical VaR at " << confidenceLevel << ": " << var << std::endl;

    return 0;
}