#ifndef driveFunctions_H
#define driveFunctions_H

#include "main.h"

extern double signum(double num);
extern double bothBind(double num, double upper, double lower);
extern double maxBind(double num, double upper);
extern double minBind(double num, double lower);
extern void maxCurrent(double current);
extern void move();

#endif