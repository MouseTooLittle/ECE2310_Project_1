#ifndef SENSOR_TOOLS_H
#define SENSOR_TOOLS_H

#include <string>
#include <memory>

namespace sensor {

constexpr int MAX_READINGS = 20;

// Determines whether value is inside the inclusive interval [low, high].
// The default interval is [0.0, 100.0] when low and high are omitted.
// Returns true when value is equal to an endpoint or lies between them;
// otherwise, returns false.
// TODO: Complete this function here. It must remain inline and must use the
// default arguments shown.
inline bool isInRange(double value, double low = 0.0, double high = 100.0) {
    if(value<= high && value>= low){
        return true;
    } else {
        return false;
    }
}

// Creates and returns an uppercase copy of name.
// The original string must not be changed.
// TODO: Implement this function in sensor_tools.cpp.
std::string cleanStationName(const std::string& name);

// Calculates and returns the arithmetic mean of the first size readings.
// Return 0.0 when size is less than or equal to zero.
// This call must count as one analysis, including the empty-array case.
// TODO: Implement this function in sensor_tools.cpp.
double average(const double readings[], int size);

// Finds the smallest and largest values among the first size readings.
// Store the results in the reference parameters minimum and maximum.
// When size is less than or equal to zero, set both results to 0.0.
// This call must count as one analysis.
// TODO: Implement this function in sensor_tools.cpp.
void findExtremes(const double readings[], int size,
                  double& minimum, double& maximum);

// Counts and returns how many of the first size readings are in the
// inclusive interval [low, high]. Use pointer arithmetic rather than [].
// Return 0 when size is less than or equal to zero.
// This call must count as one analysis.
// TODO: Implement this function in sensor_tools.cpp.
int countInRange(const double* readings, int size,
                 double low = 0.0, double high = 100.0);

// Allocates a new dynamic array containing the first size readings with
// offset added to each value. The original array must remain unchanged.
// Return nullptr when size is less than or equal to zero.
// The caller owns the returned array and must release it with delete[].
// This call must count as one analysis.
// TODO: Implement this function in sensor_tools.cpp.
double* copyWithOffset(const double* readings, int size,
                       double offset = 0.0);

// Creates a separately owned dynamic array containing the first size
// readings with offset added to each value. Return nullptr when size is
// less than or equal to zero. The unique_ptr manages cleanup automatically,
// so the caller must not use delete[] on the returned array.
// This call must count as one analysis.
// TODO: Implement this function in sensor_tools.cpp.
std::unique_ptr<double[]> copyWithOffsetRAII(const double* readings, int size,
                                              double offset = 0.0);

int getAnalysisCount();

}  // namespace sensor

#endif
