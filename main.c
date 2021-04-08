#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>


//COMPILE AND RUN : clang main.c ./a.out

#define getWidth() currentWindowDimensions.ws_col - 1

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


bool binary = false;

enum Color {
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    COLOR_DEFAULT
};

struct winsize currentWindowDimensions;

double frameTimes = 0;

int getMiddle = RAND_MAX / 2;

int customSplit = RAND_MAX / 2;

void setWindowDimensions() {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &currentWindowDimensions);
}

void onExit() {
    printf("\n");
    printf(ANSI_COLOR_RESET);
}

void signalHandler() {
    exit(0);
}

void init() {

    //SETUP RANDOM NUMBER GENERATOR SEED
    printf("INITIALIZING RANDOM NUMBER GENERATOR\n");
    srand(time(NULL));

    //SETTING UP FRAME TIMES
    if (frameTimes == 0) {
        printf("SETTING UP FRAME TIMES\n");
        frameTimes = 16.6 * 1000;
    }


    //MAKING SURE TERMINAL IS RESET AT END OF PROGRAM
    printf("SETTING SIGNAL EVENT HANDLERS\n");
    atexit(onExit);
    signal(SIGINT, signalHandler);
    signal(SIGQUIT, signalHandler);
    signal(SIGTSTP, signalHandler);

    //JUST COS IT LOOKS NICE IN TERMINAL OUTPUT
    printf("SETTING COLORS\n");
    printf("SETTING RENDER TYPE\n");

    //INIT FINISHED
    printf("FINISHED SETUP PHASE\n");
}


void binaryOutput() {
    for (;;) {
        setWindowDimensions();
        for (int i = 0; i < getWidth(); i++) {
            //DRAW IF BIGGER
            if (random() < customSplit) {
                if (random() > getMiddle) {
                    printf("0");
                } else {
                    printf("1");
                }
            } else {
                printf(" ");
            }
        }
        printf("\n");

        usleep(frameTimes);
    }
}

void nonBinaryOutput() {
    for (;;) {
        setWindowDimensions();
        for (int i = 0; i < getWidth(); i++) {
            //DRAW IF BIGGER
            if (random() < customSplit) {
                printf("%c", (int) (32 + random() % 94));
            } else {
                printf(" ");
            }
        }
        printf("\n");

        usleep(frameTimes);
    }
}



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


int main(int argc, char *argv[]) {
    printf("STARTING UP...\n");

    enum Color color = COLOR_DEFAULT;

    for (int i = 0; i < argc; i++) {

        if (argv[i] == NULL) {
            break;
        }

        if (strcmp(argv[i], "-binary") == 0 || strcmp(argv[i], "-b") == 0) {
            binary = true;
        }

        if (strcmp(argv[i], "-green") == 0) {
            color = GREEN;
        }

        if (strcmp(argv[i], "-red") == 0) {
            color = RED;
        }

        if (strcmp(argv[i], "-blue") == 0) {
            color = BLUE;
        }

        if (strcmp(argv[i], "-yellow") == 0) {
            color = YELLOW;
        }

        if (strcmp(argv[i], "-magenta") == 0) {
            color = MAGENTA;
        }

        if (strcmp(argv[i], "-cyan") == 0) {
            color = CYAN;
        }

        if (strcmp(argv[i], "-custom-split") == 0 || strcmp(argv[i], "-cs") == 0) {
            customSplit = RAND_MAX / atoi(argv[i + 1]);
            i++;
        }

        if (strcmp(argv[i], "-frame-time") == 0 || strcmp(argv[i], "-ft") == 0) {
            double ft = atof(argv[i + 1]);
            printf("SETTING FRAME TIME: %f\n", ft);
            frameTimes = ft * 1000;
            i++;
        }


        if (strcmp(argv[i], "-help") == 0 || strcmp(argv[i], "help") == 0) {
            usage();
            return 0;
        }
    }

    init();

    switch (color) {
        case RED:
            printf(ANSI_COLOR_RED);
            break;
        case GREEN:
            printf(ANSI_COLOR_GREEN);
            break;
        case YELLOW:
            printf(ANSI_COLOR_YELLOW);
            break;
        case BLUE:
            printf(ANSI_COLOR_BLUE);
            break;
        case MAGENTA:
            printf(ANSI_COLOR_MAGENTA);
            break;
        case CYAN:
            printf(ANSI_COLOR_CYAN);
            break;
        case COLOR_DEFAULT:
            printf("NO COLOR SELECTED\n");
            printf(ANSI_COLOR_RESET);
            break;
        default:
            printf("NO COLOR SELECTED\n");
            break;
    }


    printf("BEGINING OUTPUT\n");
    if (binary) {
        binaryOutput();
    } else {
        nonBinaryOutput();
    }
}
