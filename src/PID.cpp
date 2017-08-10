#include <iostream>
#include "PID.h"


PID::PID() {}

PID::~PID() {}

void PID::Init() {
  params[0] = 0.33;    // P
  params[1] = 2.1;     // D
  params[2] = 0.00015;  // I

  p_error = 0.0;
  i_error = 0.0;
  d_error = 0.0;

  best_error  = 0.0;
  total_error = 0.0;
  past_steps  = 0;

  d_params[0] = 0.1;
  d_params[1] = 0.2;
  d_params[2] = 0.0005;

  optimization_index = 0;
  optimization_first_run = true;
}

void PID::UpdateError(double cte) {
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;

  total_error += d_error + p_error + i_error;

  past_steps += 1;

  if (past_steps >= 500) {
    TwiddleParameters();
    past_steps = 0;
  }
}

double PID::GetSteeringAngle() {
  return -params[0] * p_error - params[1] * d_error - params[2] * i_error;
}

void PID::TwiddleParameters() {
  // Run parameter optimization only if the sum of changes is higher
  // than the the tolerance value
  if (d_params[0] + d_params[1] + d_params[3] > 0.00001) {
    if (optimization_first_run) {
      if (total_error < best_error) {
        best_error = total_error;
        d_params[optimization_index] *= 1.1;
        params[optimization_index] += d_params[optimization_index];
      }
      else {
        params[optimization_index] -= 2 * d_params[optimization_index];
      }

      optimization_first_run = false;
    }
    else {
      if (total_error < best_error) {
        best_error = total_error;
        d_params[optimization_index] *= 1.1;
      }
      else {
        params[optimization_index] += d_params[optimization_index];
        d_params[optimization_index] *= 0.9;
      }

      optimization_first_run = true;
      optimization_index = (optimization_index + 1) % 3;
    }

    total_error = 0.0;

    std::cout << "Parameters: [0]-" << params[0] << "  [1]-" << params[1] << "  [2]-" << params[2] << std::endl;
  }
}