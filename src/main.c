#include "raylib.h"

#include <stdlib.h>
#include <time.h>

#include "Polynome.h"

int main() {
  srand(time(NULL));

  // Window Variables and create
  int scale = 44;
  int windowWidth = 16 * scale;
  int windowHeight = 9 * scale;
  InitWindow(windowWidth, windowHeight, ".?.?.RacineEvidente.?.?.");

  // Other variables
  Polynome *poly = createPolynome(3);
  int phase = 0;

  // Main Loop
  while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE)) {

    // Updates Part
    if (IsKeyPressed(KEY_SPACE)) {
      phase = phase == 0;
      if (phase == 0)
        setRandomRoots(poly);
    }

    // Rendering Part
    BeginDrawing();
    ClearBackground(BLACK);

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
