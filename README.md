High-Performance-Computing
==========================

Working with different forms of HPC in a practical setting

1. Matrix-Multiplication-Speedup
-----------------------------
Using different optimizations to speed up the standard matrix multiplication. The boost matrix multiplication function is used to compare the speed up of this implementation.

Analysis avilible with graph representation of a log Y graph to show the magnitudes of speed up over boost's implementation

2. CSV-Vector-Parser
-----------------
Simple CSV parser for parsing feature vectors in the form of [filename:vector of floats]. Used in many of the Vector distance calulators to parse the data files into datastructures for fast searching

3. IPC-Vector-Distance-Calculator
------------------------------
Calculates the L2 norm of a vector against a database of vectors using multiple forked processes with shared memory access and returns the top K closest matches.

4. Threaded-Vector-Distance-Calculator
-----------------------------------
Calculates the L2 norm of a vector against a database of vectors using C++ threads for parallelization and returns the top K closest matches.