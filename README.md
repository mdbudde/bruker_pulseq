# bruker_pulseq
bruker method to run pulseq files on paravision


Bruker Paravision (6.0.1) method file to run pulseq files.
This repo is simply code to load in the seq file using c.
A different private repo (w Bruker code) will be used to integrate into the method once this one is (mostly) complete.

In a linix/mac, simply type:
```
make
./loadseqtest
```
to run the code

The goal is to convert the functions here into c code:
ExternalSequence.cpp: https://github.com/pulseq/pulseq/blob/master/src/ExternalSequence.cpp
Why?
The first implementation to wrap all c++ functions to make them c accessible was difficult and messy.
With ai tools, rewriting the code in c should be easy enough to rebuild, and c is more familiar to the majority of paravision programmers (us).

In the PulseqInterpreter.c file, the structures will be converted to paravision variables that are fully accessible in all parts of the code.
I have done this for a load instructions from a similarly-formatted file (diffusion weighted directions and artbitary waveforms) and works quite well.

email me (mdbudde@mcw.edu) with any questions or access to the private repo. 
