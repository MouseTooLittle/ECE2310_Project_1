#include "sensor_tools.h"

#include <cctype>

namespace sensor {

namespace {
int analysisCount = 0;  // Visible only inside this source file.
}

// Return an uppercase copy of name without modifying the original string.
std::string cleanStationName(const std::string& name) {
    std::string cleanName;
    for (size_t i = 0;i<name.length();i++){
        cleanName += toupper(name[i]); 
    }
    return cleanName;
}

// Return the mean of the first size readings, or 0.0 when size <= 0.
double average(const double readings[], int size) {
    analysisCount++;
    double sum = 0.0;
    if (size > 0){
        for (int i = 0; i < size; i++){
            sum += readings[i];
        }
    } else {
        return 0.0;
    }
    return (sum/size);
}

// Place the smallest and largest readings into the two reference parameters.
// Set both results to 0.0 when size <= 0.
void findExtremes(const double readings[], int size, double& minimum, double& maximum) {
    analysisCount++;
    if (size > 0) {
        minimum = maximum = readings[0];
        for (int i = 0; i < size; i++){
            if (readings[i] < minimum){
                minimum = readings[i];
            }
            if (readings[i] > maximum){
                maximum = readings[i];
            }
        } 
    } else {
        minimum = 0.0;
        maximum = 0.0;
    }
}

// Count values in the inclusive interval [low, high] using pointer arithmetic.
int countInRange(const double* readings, int size, double low, double high) {
    analysisCount++;
    int count = 0;
    for (int i = 0; i < size; i++) {
        if(*(readings + i) <= high && *(readings + i) >= low){
            count++;
        }
    }
    return count;
}

// Return a new caller-owned array with offset added to every reading.
// Return nullptr when size <= 0; the caller will clean up with delete[].
double* copyWithOffset(const double* readings, int size, double offset) {
    analysisCount++;
    if (size > 0) {
        double* copyReadings = new double[size];
        for (int i = 0; i < size; i++) {
            copyReadings[i] = readings[i] + offset;
        }
        return copyReadings;
    } else {
        return nullptr;
    }
}

// Return an automatically managed array with offset added to every reading.
// Return nullptr when size <= 0; do not manually delete the returned array.
std::unique_ptr<double[]> copyWithOffsetRAII(const double* readings, int size, double offset) {
    analysisCount++;
    if (size > 0) {
        std::unique_ptr<double[]> copyRAII = std::make_unique<double[]>(size);
        for (int i = 0; i < size; i++) {
            copyRAII[i] = readings[i] + offset;
        }
        return copyRAII;
    } else {
        return nullptr;
    }
}

int getAnalysisCount() {
    return analysisCount;
}

}  // namespace sensor
