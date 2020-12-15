# CourseProject for st19

# ManBearPig. An attempt at providing Full Text Search to mandoc
The goal of this project would be to attempt an implementation of a trigram based full text search database
for the mandoc project (https://mandoc.bsd.lv/)

# Background
UNIX system provide their documentation to the user through a set of tools collectively referred to
as the Manual Page system. The well known man(1) command exists today on all UNIX systems but even
on other platforms like MacOSX and android. Searching efficiently keywords and semantics has been
of paramount importance for the user to quickly get to the relevant manual page and the command
apropos(1) traditionally served that purpose, meaning doing database lookups. 
The database are built with the makewhatis(1) tool.

# Project proposal
We will investigate the C source code of the mandoc project, targeted on the modules of searching
and database building. We will understand how it works and how to extract manual page text
using the mdoc library functions. Then we shall create a simplified trigram database of an 
an inverted index with the goal to connect it to the search capabilities.

# Final report and code
You can read the final report in the pdf , and see the provided final-presentation.mp4 
To compile the mandoc source code you can fetch it from https://mandoc.bsd.lv/ and compile
it at the same directory level as this project.

# members
st19 / solo project 
