# CourseProject for st19

# ManBearPig. A study on how modern UNIX sytem search their manual pages.
The goal of this project would be to create a report and possibly code improvements
for the mandoc project (https://mandoc.bsd.lv/) and more specifically for its textual 
search features.

# Background
UNIX system provide their documentation to the user through a set of tools collectively referred to
as the Manual Page system. The well known man(1) command exists today on all UNIX systems but even
on other platforms like MacOSX and android. Searching efficiently keywords and semantics has been
of paramount importance for the user to quickly get to the relevant manual page and the command
apropos(1) traditionally served that purpose, meaning doing database lookups. 
The database are built with the makewhatis(1) tool.

# Project proposal
We will investigate the C source code of the mandoc project, targeted on the modules of searching
and database building. We will understand how it works and them potentially propose improvements
or patches based on modern techniques learned from CS410: Text Information Systems @ UIUC course.

# members
st19 / solo project 
