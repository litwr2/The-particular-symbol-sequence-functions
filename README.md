# The particular symbol sequence utilities

We have a set of rules describing a symbolic sequence:

1) after A1 follows A2, after A2 - A3, ..., after A8 - A9, after A9 - B1, after B1 - B2, ..., after Z9 - A1-A1, after A1-A1 - A1-A2, ..., after A1-Z9 - A2-A1, ...;

2) symbols D, F, G, J, M, Q, V, 0 (digit) are forbidden to use in the sequence;

3) max length of the sequence is 10 pairs of letter and digit.

We need a function which gives the next symbolic sequence for the given sequence.  The order fuction, its inverse function, and the sequence grammar checker function will be also useful.  For example, order("A1") = 0, order("A1-A1") = 171, inverse(172) = "A1-A2", check("A8") = true, check("D0") = false.

The code is C++03 compliant.
