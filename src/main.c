#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Polynome.h"

// Take the keyboards input for change your answer
void changeRootAnswer(float *answer, float *answerIm) {
  // Verify Entry
  if (answer == NULL)
    return;

  // Before change by inputs
  float temp = *answer;
  if (*answer == -171717)
    *answer = 0;

  // Change the answer by inputs
  *answer *= 10;
  if (IsKeyPressed(KEY_KP_0)) {
    *answer += 0;
  } else if (IsKeyPressed(KEY_KP_1) || IsKeyPressed(KEY_ONE)) {
    *answer += 1;
  } else if (IsKeyPressed(KEY_KP_2) || IsKeyPressed(KEY_TWO)) {
    *answer += 2;
  } else if (IsKeyPressed(KEY_KP_3) || IsKeyPressed(KEY_THREE)) {
    *answer += 3;
  } else if (IsKeyPressed(KEY_KP_4) || IsKeyPressed(KEY_FOUR)) {
    *answer += 4;
  } else if (IsKeyPressed(KEY_KP_5) || IsKeyPressed(KEY_FIVE)) {
    *answer += 5;
  } else if (IsKeyPressed(KEY_KP_6) || IsKeyPressed(KEY_SIX)) {
    *answer += 6;
  } else if (IsKeyPressed(KEY_KP_7) || IsKeyPressed(KEY_SEVEN)) {
    *answer += 7;
  } else if (IsKeyPressed(KEY_KP_8) || IsKeyPressed(KEY_EIGHT)) {
    *answer += 8;
  } else if (IsKeyPressed(KEY_KP_9) || IsKeyPressed(KEY_NINE)) {
    *answer += 9;
  } else if (IsKeyPressed(KEY_I)) {
    *answerIm = temp;
    *answer = 0;
    if (*answerIm < -1000)
      *answerIm = 1;
  } else if (IsKeyPressed(KEY_MINUS) || IsKeyPressed(KEY_KP_SUBTRACT)) {
    *answer = -temp;
  } else if (IsKeyPressed(KEY_BACKSPACE)) {
    *answer = ((int)temp) / 10 + temp - (int)temp;
  } else {
    *answer = temp;
  }

  // Limit the answer
  if (*answer < -1000 || *answer > 1000) {
    *answer = temp;
  }
}

int main() {
  srand(time(NULL));

  // Window Variables and create
  int scale = 44;
  int windowWidth = 16 * scale;
  int windowHeight = 9 * scale;
  InitWindow(windowWidth, windowHeight, ".?.?.RacineEvidente.?.?.");

  // Other variables
  int rdmDegree = rand() % 2 + 2;
  Polynome *poly = createPolynome(rdmDegree);
  int phase = -1;

  // Answer vars
  float answer = -171717;
  float answerIm = -171717;
  char str[100];

  // Score vars
  int score = 0;
  int maxScore = 0;

  // Main Loop
  while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE)) {

    // Updates Part
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
      phase = phase == 0;

      if (phase == 1) {
        // Verif answer
        if (isAnswerGood(poly, answer)) {
          score += 1;
        }
        maxScore += 1;
        printf("--> Score: %.2f\n", score * 1.0f / maxScore);
        printf("--> Regret: %d\n", maxScore - score);
      }

      // Reset Poly and answer
      if (phase == 0) {
        // Change the degree
        rdmDegree = rand() % 2 + 2;
        poly = createPolynome(rdmDegree);

        // Change randomly roots
        setRandomRoots(poly);
        answer = -171717;
        answerIm = -171717;
      }
    }
    changeRootAnswer(&answer, &answerIm);

    // Rendering Part
    BeginDrawing();
    ClearBackground(BLACK);

    if (phase == -1) {
      DrawText("Welcome", 50, 30, 33, PINK);
      DrawText("<Image>", 50, 100, 33, PINK);
      DrawText("Press To Start", 50, 200, 33, PINK);
      EndDrawing();
      continue;
    }

    // Draw your answer
    toStringRootAnswer(&answer, &answerIm, str);
    DrawText(str, 10, 100, 33, PINK);

    // Draw poly
    renderPolynome(poly);
    if (phase == 1) {
      renderRoots(poly);
    }

    EndDrawing();
  }

  // Delete all
  deletePolynome(poly);
  CloseWindow();
  return 0;
}
