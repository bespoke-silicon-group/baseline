# Q-learning

This example runs the Q-learning algorithm. The goal in this problem is to 
predict the state value based on a feature list. The state value is calculated 
by performing a dot product between the feature vector and the weight vector. 

Training is done on a list of feature vectors and corresponding state values.
At every step, the error is calculated as the difference between prediction and 
the given state value. Then, the list of weights are updated based on the given 
error in the following way:

Error = Sum(W[i] . F[i]) - V
W_new[i] = W[i] + alpha . error . feature [i]


The kernel code is located in the subdirectories of [kernel](kernel). The actual
sum of absolute differences code is in the header file
[kernel/include/sum_abs_diff.hpp](kernel/include/sum_abs_diff.hpp). 

# Makefile Targets

For a list of all Makefile targets, run `make help`.

## Versions

There are several different versions of this kernel. Each is a subdirectory in
the [kernel](kernel) directory.

### Version 0


