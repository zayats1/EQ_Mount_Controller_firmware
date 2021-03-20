#include "map_constrain.h"

double map(double value, double min_val, double max_val, double new_min_val,
           double new_max_val) {
  return (value - min_val) * (new_max_val - new_min_val) / (max_val - min_val) +
         new_min_val;
}

double constrain(double value, double min_value, double max_value) {
  if (value < min_value) {
    return min_value;
  } else if (value > max_value) {
    return max_value;
  } else {
    return value;
  }
}