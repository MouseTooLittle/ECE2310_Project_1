#include "sensor_tools.h"

#include <iomanip>
#include <iostream>
#include <string>

int main() {
    std::string stationName;
    std::cout << "Station name: ";
    // TODO 1: Read the complete station name using std::getline.

    int size = 0;
    std::cout << "Number of readings (1-20): ";
    // TODO 2: Read the number of readings.

    if (size < 1 || size > sensor::MAX_READINGS) {
        std::cout << "Invalid number of readings.\n";
        return 1;
    }

    double readings[sensor::MAX_READINGS];
    std::cout << "Enter " << size << " readings:\n";
    // TODO 3: Use a loop to read size values into readings.

    double offset = 0.0;
    std::cout << "Calibration offset: ";
    // TODO 4: Read the calibration offset.

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

    // TODO 6: Set adjusted to nullptr so it does not remain dangling.

    // Do not delete safeCopy. RAII releases that array automatically.
    return 0;
}
