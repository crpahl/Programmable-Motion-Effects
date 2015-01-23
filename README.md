# Programmable Motion Effects #

This application was created to impliment programmable motion effects as described in the paper "Programmable Motion Effects", written by Johannes Schmid, Robert W. Sumner, Huw Bowles, and Markus Gross.

A single object traveling through space and time is described in the input file. The shape of the geometric object is first described, and additional lines represent the position and time of the object in motion. Using the supplied input coordinates and times, we then generate a single time aggregate object (TAO) that aggregates the information of each individual geometric object. Using the TAO and a simple ray tracer, we use the methods as decribed in the paper to animate the object moving through space and time based on the initial values in the input file.

Additional animations can then easily be added to the object in motion in a programmable manner based on the generated information.
