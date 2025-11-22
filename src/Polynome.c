#include "Polynome.h"

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

  // Set default values
  int i = 0;
  for (i = 0; i < polynome->degree; i++) {
    polynome->coefs[i] = 0;
    polynome->roots[i] = 0;
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
    sprintf(string, "X² + %.1f X + %.1f\n", polynome->coefs[1],
            polynome->coefs[0]);

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
    sprintf(string, "R1=%.1f, R2=%.1f\n", polynome->roots[1],
            polynome->roots[0]);

  } else if (polynome->degree == 3) {
    sprintf(string, "R1=%.1f, R2=%.1f, R3=%.1f\n", polynome->roots[2],
            polynome->roots[1], polynome->roots[0]);
  }

  // Return and Malloc the string
  return strdup(string);
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
  }

  // Evident Roots
  int numEvidentRoot = rand() % 4 - 1;
  for (int i = 0; i < numEvidentRoot; i++) {
    int newRoot = rand() % 5 - 2;
    polynome->roots[i] = newRoot;
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
    // X² - (R1*R2)*X + R1*R2
    polynome->coefs[2] = 1;
    polynome->coefs[1] = -(polynome->roots[1] + polynome->roots[0]);
    polynome->coefs[0] = polynome->roots[1] * polynome->roots[0];

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

  // Have Obvious Root
  for (int i=0; i< polynome->degree; i++) {
    if (answer == polynome->roots[i]) 
      return 1;
  }

  return 0;
}
