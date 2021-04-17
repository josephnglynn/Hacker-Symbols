# hacker symbols
A simple opengl application with renders random ascii symbols to the window in a variety of colours, speeds, fonts and spread.

The usage function below shows how to change run time values in the program.
```c++
#include <stdio.h>

void usage() {
    printf(
            "    -color : sets textColor based on three floats for rgb color following the flag. 0 <= values <= 1\n"
            "    -colorRGB : sets textColor based on three floats as rgb colors : 0 <= values <= 255\n"
            "    -bg : sets background color based on three floats for rgb color following the flag. 0 <= values <= 1\n"
            "    -bgRGB : sets background color based on three floats for rgb color following the flag. 0 <= values <= 255\n"
            "    -binary / -b : DISPLAYS ONLY BINARY CHARACTERS (0, 1)\n"
            "    -fontSize / -fs : Sets the height of the font\n"
            "    -fontPath / -fp : Set the font to use from the path to said font\n"
            "    -change / -c : ALLOW YOU TO DEFINE THE SPEED OF CHARACTERS\n"
            "    -custom-split / -cs : ALLOWS YOU TO DEFINE SPREAD OF CHARACTERS - HIGHER = SPARSER\n"
            "    -help / help : DISPLAYS HELP\n"
    );
}
```

## Previous Version
The old terminal based version:
> Simple terminal application which outputs random ascii symbols to the terminal in a varity of colours and different speeds

Can be found on the [terminal branch](https://github.com/josephnglynn/Hacker-Symbols/tree/terminal-output)