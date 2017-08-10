#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double total_error;
  double best_error;

  /*
  * Count number ob past steps
  */
  int past_steps;
  int optimization_index;
  bool optimization_first_run;
  /*
  * Coefficients
  */ 
  double params[3];

  /*
   * Coefficient change params
   */
  double d_params[3];

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init();

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the steering angle based previously updated cross track error
  */
  double GetSteeringAngle();

  /*
   * Optimize parameters in a twiddle fashion
   */
  void TwiddleParameters();
};

#endif /* PID_H */
