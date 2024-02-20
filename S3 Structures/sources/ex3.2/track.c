#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "track.h"


Track* initTrack (char* artiste, char* titre, int duree) {
    Track *track = (Track*) malloc(sizeof(Track));
    if (track == NULL) { return NULL; }


    strncpy(track->artiste, artiste, ARTISTE_LENGTH);

    strncpy(track->titre, titre, TITLE_LENGTH);
    
    track->duree = duree;

    return track;
}

int compareTrack (Track* t1, Track* t2) {
    if (strcmp(t1->artiste, t2->artiste) == 0) {
        if (strcmp(t1->titre, t2->titre) == 0) {
            if (t1->duree == t2->duree) {
                return 0;
            }
        }
        return strcmp(t1->titre, t2->titre);
    }
    return strcmp(t1->artiste, t2->artiste);
}

void printTrack (Track *t) {
    printf("%s - %s - %d", t->artiste, t->titre, t->duree);
}

