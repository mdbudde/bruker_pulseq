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

See discussions for additional needs and developments.
