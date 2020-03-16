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

The list of feature vectors is represented as a feature matrix, with each row
being a new feature vector observation.
Treat every row of the feature matrix as a new feature observation 
With the corresponding value of value[y] 
For every new feature observation, the prediction value is calculated 
by performing a dot product of the row y of the feature matrix, and 
the weight vector. 
Each tile performes its share of the dot product and stores it in 
a shared array.
A sum reduction is performed among the values in the shared array to 
calcualte the value of the prediction
The error is calculated as the difference between the prediction and 
the actual value. 
Each weight in the weight vector is then updated as below:
weight[x] += ALPHA * error * feature[y][x]
The process repeats for all rows in the feature matrix.


The kernel code is located in the subdirectories of [kernel](kernel). The actual
sum of absolute differences code is in the header file
[kernel/include/sum_abs_diff.hpp](kernel/include/sum_abs_diff.hpp). 

# Makefile Targets

For a list of all Makefile targets, run `make help`.

## Versions

There are several different versions of this kernel. Each is a subdirectory in
the [kernel](kernel) directory.

### Version 0


