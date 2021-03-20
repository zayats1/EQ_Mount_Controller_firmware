#ifndef MAP_CONSTRAIN_H
#define MAP_CONSTRAIN_H

// Google braces style

#if defined __cplusplus
extern "C" {
#endif

/*
Map function scales input range of values to predicted range of values.
*/

double map(double value, double min_val, double max_val, double new_min_val,
           double new_max_val);

/*
Constrain function constrains value in setted range of values.
*/

double constrain(double value, double min_value, double max_value);

#ifdef __cplusplus
}
#endif

#endif // #define MAP_CONSTRAIN_H