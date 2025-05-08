# bruker_pulseq
bruker method to run pulseq files on paravision (6.0.1)


Bruker Paravision (6.0.1) method file to run pulseq files.
Copied from FLASH and added features. 

Current status: 
- Uses pulseq code (ExternalSequence.cpp) to load seq files.
- NOTE: The dynamic file gui element doesn't recognize files with symbols in the name, hence gre.seq should be converted to greseq, etc.
- NOTE: a lot of warnings during compilation.
- NOTE: .cpp files do not appear in the Window Explorer; may need alternative editor.
- The only change to ExternalSequence.cpp was to confirm 'seq' instead of '.seq' filenames.

pulseq_wrapper.cpp:
- convert C calls to/from C++ functions. 

pulseqPars.h, pulseqTypes.h, pulseqRelations.c:
- Main code to address pulseq elements and loading through PV interface.

Makefile:
- added ExxternalSequence.cpp, md5.cpp, and pulseq_wrapper.cpp to c++ compile and linker elements.
- copies gre.seq to users .../exp/lists/seq/ directory (SEQ_DIR), creating if not existing.


TODO:
- strip away all non-pulseq code (from FLASH).
- 
