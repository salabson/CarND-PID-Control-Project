#include "PID.h"
#include <iostream>
#include <cmath>
/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;
    p_error=0.0;
    i_error=0.0;
    d_error=0.0;
 
    // Resize twiddle 
    p.resize(3);
    dp.resize(3);
    
    // Initialize twiddle dp values
    dp[0] = 1.0;
    dp[1] = 1.0;
    dp[2] = 1.0;

    iter+=1;
    }

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
    // Calculate derivative error
    d_error = cte-p_error;
    
    // Calculate propotional error
    p_error = cte;

    // Calculate Intregral error
    i_error += cte;

}




double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  return -Kp*p_error+ -Ki*i_error+ -Kd*d_error;  // TODO: Add your total error calc here!
}

double PID::TotalError(double p_gain, double i_gain, double d_gain){
   return -p_gain*p_error -i_gain*i_error+ -d_gain*d_error; 
}

void PID::Twiddle(double tol){
   double best_err= Kp;
   double err;

   p[0]=Kp;
   p[1]=Ki;
   p[2]=Kd;

   // Twiddle
   while((dp[0]+dp[1]+dp[2]) > tol){
      for(int i=0; i<p.size(); i++){
         p[i]+=dp[i];
         err = std::abs(TotalError(p[0], p[1], p[2]));
         if(err < best_err){
           best_err = err;
           dp[i]*=1.1;
         } 
         else{
           p[i]-=2*dp[i];
           err = std::abs(TotalError(p[0], p[1], p[2]));
           if(err < best_err){
           best_err = err;
           dp[i]*=1.1;
           }else{
            p[i]+=dp[i];
            dp[i]*=0.9;
           }

      }

   }
}

  Kp = p[0];
  Ki = p[1];
  Kd = p[2];

}
