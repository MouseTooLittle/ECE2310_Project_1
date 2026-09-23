#include "sensor_tools.h"

#include <iomanip>
#include <iostream>
#include <string>

int main() {
    std::string stationName;
    std::cout << "Station name: ";
    std::getline(std::cin, stationName);

    int size = 0;
    std::cout << "Number of readings (1-20): ";
    std::cin >> size;

    if (size < 1 || size > sensor::MAX_READINGS) {
        std::cout << "Invalid number of readings.\n";
        return 1;
    }

    double readings[sensor::MAX_READINGS];
    std::cout << "Enter " << size << " readings:\n";
    for (int i = 0; i < size; i++) {
        std::cin >> readings[i];
    }

    double offset = 0.0;
    std::cout << "Calibration offset: ";
    std::cin >> offset;

    const double mean = sensor::average(readings, size);
    double minimum;
    double maximum;
    sensor::findExtremes(readings, size, minimum, maximum);
    const int standardCount = sensor::countInRange(readings, size);
    double* adjusted = sensor::copyWithOffset(readings, size, offset);
    const double adjustedMean = sensor::average(adjusted, size);
    auto safeCopy = sensor::copyWithOffsetRAII(readings, size, offset);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nReport for "
              << sensor::cleanStationName(stationName) << '\n';
    std::cout << "Average: " << mean << '\n';
    std::cout << "Minimum: " << minimum << '\n';
    std::cout << "Maximum: " << maximum << '\n';
    std::cout << "Readings in standard range: "
              << standardCount << '\n';
    std::cout << "Adjusted average: " << adjustedMean << '\n';
    std::cout << "Analyses performed: "
              << sensor::getAnalysisCount() << '\n';

    // TODO 5: Release the raw dynamically allocated array.
    delete[] adjusted;
    // TODO 6: Set adjusted to nullptr so it does not remain dangling.
    adjusted = nullptr;
    // Do not delete safeCopy. RAII releases that array automatically.
    return 0;
}