#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
    kp = kp_;
    ki = ki_;
    kd = kd_;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
    double cte_sum = 0.0;
    // Calculate propositional error
    p_error = kp*cte;
    // Calculate Intregral error
    cte_sum+=cte;
    i_error = ki*cte_sum;
    // Calculate derivative error
    double prev_cte = cte;
    diff_cte = cte-prev_cte;
    d_error = kd*diff_cte;
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  return p_error+ i_error+ d_error;  // TODO: Add your total error calc here!
}
