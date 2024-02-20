#include <stdlib.h>
#include <stdio.h>

#include "playlist.h"


Playlist* initPlaylist () {
    Playlist* playlist = (Playlist*) malloc(sizeof(Playlist));
    if (playlist == NULL) { return NULL; }
    playlist->queue = NULL;
    playlist->tete = playlist->queue;
    return playlist;
}


bool addTrack (Playlist* p, Track* t) {
    Noeud *n = (Noeud*) malloc(sizeof(Noeud));
    if (n == NULL) { return false; }

    n->track = t;
    n->suivant = NULL;

    if (p->tete == NULL) {
        p->tete = n;
        p->queue = n;
    } else {
        p->queue->suivant = n;
        p->queue = n;
    }
    
    return true;
}


Playlist* destructiveMerge (Playlist* p1, Playlist* p2) {
    Playlist *mergedPlaylist = (Playlist*) malloc(sizeof(Playlist));
    if (mergedPlaylist == NULL) { return NULL; }

    while (p1->tete != NULL && p2->tete != NULL) {

        int cmp = compareTrack(p1->tete->track, p2->tete->track);

        
        if (cmp < 0) { // t1 < t2
            Noeud *suivant = p1->tete->suivant;
            addTrack(mergedPlaylist, p1->tete->track);
            p1->tete = suivant;
        
        } else if (cmp > 0) { // t1 == t2
            Noeud *suivant = p2->tete->suivant;
            addTrack(mergedPlaylist, p2->tete->track);
            p2->tete = suivant;
        
        } else { // t1 > t2
            Noeud *suivant = p1->tete->suivant;
            addTrack(mergedPlaylist, p1->tete->track);
            p1->tete = suivant;

            Noeud *toDelete = p2->tete;
            p2->tete = p2->tete->suivant;
            free(toDelete->track);
            free(toDelete);
        }
    }

    if (p1->tete != NULL) {
        mergedPlaylist->queue->suivant = p1->tete;
        mergedPlaylist->queue = p1->queue;
        p1->tete = NULL;
    }

    if (p2->tete != NULL) {
        mergedPlaylist->queue->suivant = p2->tete;
        mergedPlaylist->queue = p1->queue;
        p2->tete = NULL;
    }

    p1->queue = NULL;
    p2->queue = NULL;
    
    return mergedPlaylist;
}


/** 
 * Affiche le contenu d'une playlist
 * PRE: p: pointeur non null vers la playtlist
 * POST: affiche le contenu de la playlist
 */
void printPlaylist (Playlist* p) {
    Noeud *bal = p->tete;
    int trackCnt = 0;
    while (bal != NULL) {
        printf("%d ", ++trackCnt);
        printTrack(bal->track);
        printf("\n");
        bal = bal->suivant;
    }
    if (trackCnt == 0)
        printf("/\n");
}

