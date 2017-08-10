## CarND PID-Control Project
[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

Overview
---
This project is part of the Udacity Self-Driving Car Engineer Nanodegree program Term 2. 

If you are looking for instructions how to build and setup the project environment, please see the [INSTRUCTIONS.md](./INSTRUCTIONS.md) for more details.


### Project Goals
The goals/steps of this project are the following:
* Implement a PID controller in order to steer a vehicle around a simulated track
* Tune the PID controller hyperparameters either manually or algorithmically to minimize the cross track error
* Discuss the effects of the P, I, D components in their implementation


### Results
Final Parameters:

- P-Component: **0.33**
- D-Component: **2.1**
- I-Component: **0.00015**

### Reflection

#### Effects of each component P, I, D in the implementation

- **P**: The proportional part makes the system minimize the Cross-Track Error which is the distance between the car and the middle of the road. The further away from the
center line, the more it will steer in the direction of the center.This makes the system to constantly overshoot left and right of the middle of the road. 

- **D**: The derivative takes into account the difference between the current and previous error in an attempt to slow down as the system reaches the minimum error. 
This allows the system to stabilize as it approaches the center effectively reducing the overshooting issue described before.

- **I**: The integral is the cumulative error and it usually correct for small drifts and issues the vehicle may have. 
As our simulator might have no drift at all, this parameter can be (and is) set to almost zero in this particular example.


#### Hyperparameter optimization
Most of the time I manually tuned the hyperparameters. Starting with educated guesses of all three parameters and then
tuning them one at a time. I also tried to optimize the parameters with Twiddle but I found it very hard for the
algorithm to figure out an optimal solution. Mostly due to the fact, that the over all error after some timesteps depends
heavily on where the car is on the track. One might need an easier way to calculate the overall error after a parameter change than to run the simulator which is very slow.