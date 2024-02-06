#ifndef _CRYPT_H_   // ou:  #if ! defined _CRYPT_H_
#define _CRYPT_H_

/**
 * Crypte une chaîne de caractères avec ROT13
 * PRE: s : chaîne à crypter
 * RES: renvoie une nouvelle chaîne contenant la chaîne s cryptée en ROT13; 
 *      la chaîne ayant été allouée dynamiquement, elle doit être libérée
 */
char* encrypt (char * s);

/**
 * Décrypte une chaîne de caractères cryptée avec la fonction crypt()
 * PRE: s : chaîne à décrypter
 * RES: renvoie une nouvelle chaîne contenant la chaîne s décryptée en ROT13;
 *      la chaîne ayant été allouée dynamiquement, elle doit être libérée
 */
char* decrypt (char * s);

#endif   // _CRYPT_H_