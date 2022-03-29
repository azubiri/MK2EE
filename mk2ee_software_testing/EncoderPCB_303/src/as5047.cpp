#include "as5047.hpp"

int mask(int sensor_result)
{
    return sensor_result & 0x3FFF; // return lowest 14-bits
}

float degrees(int sensor_result)
{
    float conversor, angle;
    conversor = 360.0 / 16384.0;
    angle = mask(sensor_result);
    return angle * conversor;
}

bool parity_check(int sensor_result)
{
    // Use the LSb of result to keep track of parity (0 = even, 1 = odd)
    int result = sensor_result;
    
    for(int i = 1; i <= 15; ++i) {
        sensor_result >>= 1;
        // pc.printf("Sensor result: 0x%04X\n", sensor_result);
        result ^= sensor_result;
        // pc.printf("Result: 0x%04X\n", result);
    }
    // Parity should be even
    return (result & 0x0001) == 0;
}