#include "Polynome.h"
#include <stdio.h>

// ----- Create & Destroy -----
Polynome *createPolynome(int degree) {
  // Create the polynome
  Polynome *polynome = (Polynome *)malloc(sizeof(Polynome));
  if (polynome == NULL) {
    printf("Error during creating polynome 1\n");
    return NULL;
  }
  polynome->degree = degree;
  polynome->hasObviousRoot = 0;
  polynome->hasImaginaryRoot = 0;

  // Malloc coefs var
  polynome->coefs = (float *)malloc(sizeof(float) * (polynome->degree + 1));
  if (polynome->coefs == NULL) {
    free(polynome);
    printf("Error during creating polynome 2\n");
    return NULL;
  }

  // Malloc roots var
  polynome->roots = (float *)malloc(sizeof(float) * polynome->degree);
  if (polynome->roots == NULL) {
    free(polynome->coefs);
    free(polynome);
    printf("Error during creating polynome 2\n");
    return NULL;
  }

  // Malloc roots var
  polynome->imRoots = (float *)malloc(sizeof(float) * polynome->degree);
  if (polynome->imRoots == NULL) {
    free(polynome->roots);
    free(polynome->coefs);
    free(polynome);
    printf("Error during creating polynome 2\n");
    return NULL;
  }

  // Set default values
  int i = 0;
  for (i = 0; i < polynome->degree; i++) {
    polynome->coefs[i] = 0;
    polynome->roots[i] = 0;
    polynome->imRoots[i] = 0;
  }
  polynome->coefs[i] = 0;

  setRandomRoots(polynome);

  return polynome;
}

void deletePolynome(Polynome *polynome) {
  // Verify Entry
  if (polynome == NULL)
    return;

  // Free variables
  free(polynome->coefs);
  free(polynome->roots);
  free(polynome->imRoots);

  // Free the structure
  free(polynome);
}

// ----- Convert to string -----
char *toStringPoly(Polynome *polynome) {
  // Verif Entry
  if (polynome == NULL)
    return NULL;

  // temp String
  char string[1000];
  for (int i = 0; i < 1000; i++)
    string[i] = '\0';

  // Fill the string
  if (polynome->degree == 2) {
    sprintf(string, "%.1f X² + %.1f X + %.1f\n", polynome->coefs[2],
            polynome->coefs[1], polynome->coefs[0]);

  } else if (polynome->degree == 3) {
    sprintf(string, "X³ + %.1f X² + %.1f X + %.1f\n", polynome->coefs[2],
            polynome->coefs[1], polynome->coefs[0]);
  }

  // Return and Malloc the string
  return strdup(string);
}

char *toStringRoots(Polynome *polynome) {
  // Verif Entry
  if (polynome == NULL)
    return NULL;

  // temp String
  char string[1000];
  for (int i = 0; i < 1000; i++)
    string[i] = '\0';

  // Fill the string
  if (polynome->degree == 2) {
    if (polynome->hasImaginaryRoot == 0) {
      sprintf(string, "R1=%.1f, R2=%.1f\n", polynome->roots[1],
              polynome->roots[0]);
    } else {
      sprintf(string, "Imaginary Root= %0.1f + %0.1fi & %0.1f - %0.1fi\n",
              polynome->roots[0], polynome->imRoots[0], polynome->roots[0],
              polynome->imRoots[0]);
    }

  } else if (polynome->degree == 3) {
    sprintf(string, "R1=%.1f, R2=%.1f, R3=%.1f\n", polynome->roots[2],
            polynome->roots[1], polynome->roots[0]);
  }

  // Return and Malloc the string
  return strdup(string);
}

// format your roots's value in Re and Im to a str
void toStringRootAnswer(float *answer, float *answerIm, char *buffer) {
  // Verify Entry
  if (answer == NULL)
    return;

  if (*answerIm > -1000) {
    sprintf(buffer, "Answer: Obvious Root -> %.0fi + %.0f", *answerIm, *answer);
  } else if (*answer > -1000) {
    sprintf(buffer, "Answer: Obvious Root -> %.0f", *answer);
  } else {
    sprintf(buffer, "Answer: No Obvious Root");
  }
}

// ----- Render -----
void renderPolynome(Polynome *poly) {
  // Render the Polynome
  char *string = toStringPoly(poly);
  DrawText(string, 10, 10, 33, PINK);
  free(string);
}

void renderRoots(Polynome *poly) {
  // Render roots
  char *string = toStringRoots(poly);
  DrawText(string, 10, 52, 33, PINK);
  free(string);
}

// ----- Change polynome -----
void setRandomRoots(Polynome *polynome) {
  // Verify entry
  if (polynome == NULL)
    return;

  // Random Roots
  for (int i = 0; i < polynome->degree; i++) {
    polynome->roots[i] = (rand() % (30 * 10)) / 10. - 15;
    polynome->imRoots[i] = 0;
  }

  // Evident Roots

  int numEvidentRoot = rand() % 4 - 1;
  int rdm = rand() % 2;
  if (polynome->degree == 2 && rdm == 0 && numEvidentRoot > 0) {
    // ---- IMAGINARY ROOTS ----
    polynome->hasImaginaryRoot = 1;
    for (int i = 0; i < polynome->degree; i++) {
      polynome->imRoots[i] = (rand() % (30 * 10)) / 10. - 15;
    }
    if (rand() % 2 == 0) {
      // 1 + j
      polynome->roots[0] = 1;
      polynome->imRoots[0] = 1;
    } else {
      // j
      polynome->roots[0] = 0;
      polynome->imRoots[0] = 1;
    }

  } else {
    // ---- REAL ROOTS ----
    polynome->hasImaginaryRoot = 0;
    for (int i = 0; i < numEvidentRoot; i++) {
      int newRoot = rand() % 5 - 2;
      polynome->roots[i] = newRoot;
    }
  }

  if (numEvidentRoot > 0)
    polynome->hasObviousRoot = 1;
  else
    polynome->hasObviousRoot = 0;

  // Console informations
  printf("numEvidentRoot: %d\n", numEvidentRoot);
  printf("The roots are settled\n");
  setRandomCoefsForRoots(polynome);
}

void setRandomCoefsForRoots(Polynome *polynome) {
  // Verify entry
  if (polynome == NULL)
    return;

  if (polynome->degree == 2) {
    if (polynome->hasImaginaryRoot == 0) {
      // ---- REAL ROOTS ----
      // X² - (R1*R2)*X + R1*R2
      polynome->coefs[2] = 1;
      polynome->coefs[1] = -(polynome->roots[1] + polynome->roots[0]);
      polynome->coefs[0] = polynome->roots[1] * polynome->roots[0];
    } else {
      // ---- IMAGINARY ROOTS ----
      // a*X² + b*X + c
      if (polynome->roots[0] == 0 && polynome->imRoots[0] == 1) {
        // j
        polynome->coefs[0] = rand() % 100 - 50;
        polynome->coefs[1] = polynome->coefs[0];
        polynome->coefs[2] = 0;

      } else if (polynome->roots[0] == 1 && polynome->imRoots[0] == 1) {
        // 1 + j && 1 - j
        polynome->coefs[0] = rand() % 100 - 50;
        polynome->coefs[1] = -polynome->coefs[0];
        polynome->coefs[2] = polynome->coefs[0] / 2;
      }
    }
  } else if (polynome->degree == 3) {
    // X³ - (R2+R1+R0)*X² - (R1*R2 + R0*R2 + R1*R0)*X + R1*R2*R0
    polynome->coefs[3] = 1;
    polynome->coefs[2] =
        -(polynome->roots[2] + polynome->roots[1] + polynome->roots[0]);
    polynome->coefs[1] =
        polynome->roots[2] * (polynome->roots[1] + polynome->roots[0]) +
        polynome->roots[1] * polynome->roots[0];
    polynome->coefs[0] =
        -polynome->roots[2] * polynome->roots[1] * polynome->roots[0];
  }
  printf("The coefs are settled\n");
}

// Comp
int isAnswerGood(Polynome *polynome, float answer) {
  // Verify entry
  if (polynome == NULL)
    return -1;

  // No obvious Root
  if (polynome->hasObviousRoot == 0) {
    if (answer == -171717)
      return 1;
    return 0;
  }

  if (polynome->hasImaginaryRoot == 1) {
    printf("------ Have Im roots ------\n");
    // TODO
  }

  // Have Obvious Root
  for (int i = 0; i < polynome->degree; i++) {
    if (answer == polynome->roots[i])
      return 1;
  }

  return 0;
}
