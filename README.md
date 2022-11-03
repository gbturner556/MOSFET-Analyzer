# MOSFET Analyzer
Author: Gavin Turner <gbturner556@gmail.com>

## Summary
I'm an electrical engineering major with a minor in computer science. 
Programming and computer science concepts are used heavily in the EE field especially 
for simulation software. One of the most widely used categories of software in the 
EE field is **SPICE** (**S**imulation **P**rogram with **I**ntegrated **C**ircuit 
**E**mphasis). Typical SPICE applications allow you to simulate complex circuits before
spending the large amount of resources required to make an integrated circuit. Many 
SPICE programs use complex mathematical models that would be tedious to compute by hand
to replicate the imperfections of typical devices. I decided for this module I would make
a rudimentary SPICE program. This program does not allow you to model full circuits but
does allow you to model the characteristics of a MOSFET (arguably one of the most important
electrical devices). 

For more information regarding MOSFETs and there function see the following link
<https://en.wikipedia.org/wiki/MOSFET>

## Software Requirements
This program requires the following software:

- Python 3
  - Pandas package
  - sys package
  - matplotlib package
- C++ 17
- Windows OS

## Running the Program
The program will run starting from C++. The program will prompt the user with 3 options:
(a) Characterize a new MOSFET, (b) Plot existing MOSFET data, and (c) Exit.

##### Option (a):
After selecting this option the program will prompt you for a name for the device.
This name is merely used to label the directory where the data is stored. If you enter 
the name of an existing directory it will be overwritten.
Next the program will prompt the user with various parameters needed
to define a MOSFET. If you enter nothing or something other than a double the program
will leave parameter as its default value. After entering all parameters the program
will automatically plot the characteristic curves of the device

#### Option (b):
This option will prompt the user for the name of the existing data directory. If the provided
name does not exist or is not a directory, the program will notify the user and exit to the main 
menu. If the provided name is a valid directory it will automatically plot the characteristic 
curves from the data given.

#### Option (c):
Selecting this option immediately exits the program. The program runs on an infinite loop
so that multiple MOSFET can be characterized in a single session. To exit the program this
option must be selected from the main menu.

#### Example of Default Characteristic Curves

![Default MOSFET](../../Users/gbtur/Downloads/Figure_1.png)
## Known Bugs
There are currently no known bugs

## Future Work
Currently, the program does not allow the user to change the increments and ranges of vdd 
and vgs. The NFET class does all for this through getters and setters so this addition is
not far from reach. 

This program also only models a single device. It is unrealistic to see this program modeling
entire circuits, but the addition of other basic electrical devices is conceivable.

## Citations
The following are resources obtained outside of class material for this program. These 
citations are also listed in the comments of the program near their application 

[https://manytools.org/hacker-tools/ascii-banner/](https://manytools.org/hacker-tools/ascii-banner/)
was used to generate ASCII art for the title screen

[https://www.geeksforgeeks.org/how-to-iterate-over-files-in-directory-using-python/](https://www.geeksforgeeks.org/how-to-iterate-over-files-in-directory-using-python/)
was used to iterate through all files in a directory

[https://stackoverflow.com/questions/5899497/how-can-i-check-the-extension-of-a-file](https://stackoverflow.com/questions/5899497/how-can-i-check-the-extension-of-a-file)
was used to extract the extension of a file


## Demonstration Video:
<https://uvmoffice-my.sharepoint.com/:v:/g/personal/gbturner_uvm_edu/EcR4NYAhnvtCs_V2d1nWiPYBm9Otoiv3dXr18Ipjv14lyw>
