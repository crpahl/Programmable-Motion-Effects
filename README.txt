FEATURES:

For the cube and octahedron I used so to represent the the face that was being drawn rather than the
side as this logically made more sense to me.

I also combined certain transformations by embedding multiple drawings between one glPushMatrix() 
and glPopMatrix() combination.  This allowed me to carry over certain transformations that would
be needed to draw the remaining faces anyway and allowed all the sides to move smoothly in one motion.

BUGS:

There are no known bugs