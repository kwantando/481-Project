# 481-Project
MelodiMemori is a cross-platform gaming device, designed to help recovering patients in the ICU.
To run this on your local device, follow the following steps:


Windows:
Compile and run the included Visual Studio solution. You need to make sure that you have /Source set as your working directory. Before the game can be ran, the proejct needs to be linked against the DLLs of SFML. Follow the tutorial here (http://www.sfml-dev.org/tutorials/2.0/start-vc.php) to do so.


Mac OSX and 64-bit Linux:
Run "Make" in the Source directory from the terminal.
Type the following in your terminal, or run from your file manager:
./melodimemori
This runs the program.



The program is to be run with a Makey Makey and Galileo; the game board provides both, and simply needs both USBs connected to the laptop to run effectively; the user can navigate the menu with the arrow keys, and then use the board to interface with the game as it begins.


Note that these should be plugged in prior to the executable launching.


Finally, there is currently a bug with Apple's OpenAL implementation that can cause segfaults to rarely occur, when 16-bit .wavs are run. Our program has multiple workarounds to this bug in place, until Apple has resolved the issue, but it something to be aware of. There's more info on this issue here: https://github.com/LaurentGomila/SFML/issues/541


The code for the project is all available under the Source directory. 
