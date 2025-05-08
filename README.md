# bruker_pulseq
bruker method to run pulseq files on paravision


Bruker Paravision (6.0.1) method file to run pulseq files.
Copied from FLASH and added features. 

Current status: 
- Uses pulseq code to load seq files. 
- NOTE: .cpp files do not appear in the Window Explorer; may need alternative editor.

pulseq_wrapper.cpp, ExternalSequence.cpp: https://github.com/pulseq/pulseq/blob/master/src/ExternalSequence.cpp
- convert C calls to/from C++ functions
- The only change to ExternalSequence.cpp was to detect 'seq' instead of '.seq' filenames.
- NOTE: a lot of warnings during compilation.

pulseqPars.h, pulseqTypes.h, pulseqRelations.c:
- Main code to address pulseq elements and loading through PV interface.
- Setup a user dropbox to select a seq file to load from the .../exp/lists/seq directory.
- NOTE: The dynamic file gui element doesn't recognize files with symbols in the name, hence gre.seq should be converted to greseq, etc.

Makefile:
- added ExxternalSequence.cpp, md5.cpp, and pulseq_wrapper.cpp to c++ compile and linker elements.
- copies gre.seq to users .../exp/lists/seq/ directory (SEQ_DIR), creating if not existing.


TODO and implementation considerations:
- strip away all non-pulseq code (from FLASH).
- convert gradient shapes to arrays for ppg. It is likely possible to re-use gradients (trapezoidal) with identical rise/top/fall times as a single gradient array and simply scale them in the ppg.  Since we are using shaped gradients, most will need gccontol blocks in the ppg to run gradients and rf/adc simultaneously. 
- convert RF pulses to pulse files. This should be straightforward given prior efforts pulseq->ppg. Including Sint & Pint values (scalar of the pulse integral relative to a hard pulse of the same duration) will likely allow the method to use the transmit gain calibration during an update of the pulse.
- write the ppg. Here again it may be possible to assign all pulseq durations with the same value to a single ppg variable (d1, etc) to re-use them in the ppg files. We may need to consider a clever scheme to write pulseq.ppg with a timestamp or similar to avoid overwriting a running sequence with one being prepared.  Or cycling around a two digit number, or something similar. 
- 
