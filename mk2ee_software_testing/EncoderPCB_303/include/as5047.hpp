#ifndef AS5047_H
#define AS5047_H

#define PULSE_DURATION 25 // Pulse duration SRCLK or RCLK high or low (in nanoseconds) 

typedef enum {
    AS_FLAG_PARITY = 0x8000,
    AS_FLAG_READ = 0x4000,
} As5047Flag;

typedef enum {
    AS_CMD_NOP = 0x0000,
    AS_CMD_ERROR = 0x0001 | AS_FLAG_READ,       // Reads error register of sensor and clear error flags
    AS_CMD_DIAGNOSTICS = 0x3FFD |  AS_FLAG_READ, // Reads automatic gain control and diagnostics info
    AS_CMD_MAGNITUDE = 0x3FFE | AS_FLAG_READ,
    AS_CMD_ANGLE = 0x3FFF| AS_FLAG_PARITY | AS_FLAG_READ,
} As5047Command;

// Masks for bits in the result of the AS_CMD_DIAGNOSTICS command
typedef enum {
    AS_DIAG_CORDIC_OVERFLOW = 0x0200,
    AS_DIAG_HIGH_MAGNETIC = 0x0400,
    AS_DIAG_LOW_MAGNETIC = 0x0800,
} As5047Diagnostics;

int mask(int sensor_result);
float get_angle(int sensor_result);
bool parity_check(int sensor_result);

#endif