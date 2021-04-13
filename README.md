# hacker symbols

NOTE: THIS IS BACKUP OF TERMINAL OUPUT VERSION

Simple terminal application which ouputs random ascii symbols to the terminal in a varity of colours and different speeds



The usage function below shows how to change run time values in the program.
```c++
#include <stdio.h>

void usage() {
    printf(
            "    COLORS: \n"
            "        -blue\n"
            "        -cyan\n"
            "        -green\n"
            "        -magenta\n"
            "        -red\n"
            "        -yellow\n"


            "    -binary / -b : DISPLAYS ONLY BINARY CHARACTERS (0, 1)\n"
            "    -frame-time / -ft : ALLOWS YOU TO DEFINE SLEEP INTERVAL BETWEEN RENDERS\n"
            "    -custom-split / -cs : ALLOWS YOU TO DEFINE SPREAD OF CHARACTERS - HIGHER = SPARSER\n"
            "    -help / help : DISPLAYS HELP\n"
    );
}
```
