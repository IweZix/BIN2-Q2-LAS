#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>

#include "utils_v1.h"

#define MAX_XY  5

//***************************************************************************
// USER INTERFACE
//***************************************************************************

/**
 * Displays the game board
 * PRE: board of dimensions nl x nc
 *      i,j: indices of a board element where i<nl && j<nc
 * POST: the board has been displayed (upper left corner
 *       on position (4,0)), indicating an 'X' on (i,j)
 */
void printBoard (int nl, int nc, int i, int j) {
    colorOn(1,PURPLE_TEXT);
    printf("\n    ");
    for (int c=0; c<nc; c++)
        printf("%3i", c);
    printf("\n     ");
    for (int c=0; c<nc; c++)
        printf("---");
    printf("\n");
    for (int l=nl-1; l>=0; l--) {
        printf("%3i |", l);
        colorOn(1,CYAN_TEXT);
        for (int c=0; c<nc; c++) {
            if (l==i && c==j) {
                colorOn(1,YELLOW_TEXT);
                printf(" %c ", 'X');
                colorOn(1,CYAN_TEXT);
            }
            else {
                printf("   ");
            }
        }
        colorOn(1,PURPLE_TEXT);
        printf("| %i\n", l);
    }
    printf("     ");
    for (int c=0; c<nc; c++)
        printf("---");
    printf("\n    ");
    for (int c=0; c<nc; c++)
        printf("%3i", c);
    printf("\n\n");
    colorOff();
}

//***************************************************************************
// CHILD CODE
//***************************************************************************




//***************************************************************************
// PARENT CODE
//***************************************************************************



