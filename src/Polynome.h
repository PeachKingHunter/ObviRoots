#ifndef Polynome_H
#define Polynome_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raygui.h"

typedef struct {
  int degree;
  float *coefs;
  float *roots;
} Polynome;

// Create & Destroy
Polynome *createPolynome(int degree);
void deletePolynome(Polynome *polynome);

// Convert to string
char *toStringPoly(Polynome *polynome);
char *toStringRoots(Polynome *polynome);

// Render
void renderPolynome(Polynome *poly);
void renderRoots(Polynome *poly);

// Change polynome
void setRandomRoots(Polynome *polynome);
void setRandomCoefsForRoots(Polynome *polynome);

#endif
