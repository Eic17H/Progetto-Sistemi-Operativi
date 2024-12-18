#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>

typedef int Data;
#define LUNG 5

void use(Data* data, int lung);

void gen(Data* data, int lung);