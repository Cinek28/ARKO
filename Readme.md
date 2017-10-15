Platform:
=========
Linux

Dependencies:
==============
*Allegro5 graphic library

About:
=======

Program for representing affinite transformations: rotation and transposition. Function for those operations are written in Assembler.

How to use:
After executing: "./Affinite <picture_name>", you can change the position with up,down,left,right direction keys and rotation with 'z' and 'x'. To exit program simply click Esc or mouseclick X.


Running:
========
```
1. Use "make" to compile and link.
2. Use "make clean"
3. Use "chmod +x Affinite"
4. Run ./Affinite <picture_name>
```
**Warning:** Picture must be set in same folder. Additionally program uses Allegro5 libraries, so to work properly one has to install allegro package and link them to project (already linked using makefile)



