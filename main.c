#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600

#define OFFSET 30

float segment_width = 50;
float segment_thickness = 25;

int digits[10][7] = {{1, 1, 1, 0, 1, 1, 1}, {0, 0, 1, 0, 0, 1, 0},
                     {1, 0, 1, 1, 1, 0, 1}, {1, 0, 1, 1, 0, 1, 1},
                     {0, 1, 1, 1, 0, 1, 0}, {1, 1, 0, 1, 0, 1, 1},
                     {1, 1, 0, 1, 1, 1, 1}, {1, 0, 1, 0, 0, 1, 0},
                     {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 0, 1, 1}};

void drawStrip(Vector2 center, bool horizontal, Color color) {
  int count = 6;

  Vector2 a, b, c, d, e, f;

  if (horizontal) {
    a = (Vector2){center.x - segment_width / 2 - segment_thickness / 2,
                  center.y};
    b = (Vector2){center.x - segment_width / 2,
                  center.y + segment_thickness / 2};
    c = (Vector2){center.x - segment_width / 2,
                  center.y - segment_thickness / 2};
    d = (Vector2){center.x + segment_width / 2,
                  center.y + segment_thickness / 2};
    e = (Vector2){center.x + segment_width / 2,
                  center.y - segment_thickness / 2};
    f = (Vector2){center.x + segment_width / 2 + segment_thickness / 2,
                  center.y};
  } else {
    a = (Vector2){center.x,
                  center.y - segment_width / 2 - segment_thickness / 2};
    b = (Vector2){center.x - segment_thickness / 2,
                  center.y - segment_width / 2};
    c = (Vector2){center.x + segment_thickness / 2,
                  center.y - segment_width / 2};
    d = (Vector2){center.x - segment_thickness / 2,
                  center.y + segment_width / 2};
    e = (Vector2){center.x + segment_thickness / 2,
                  center.y + segment_width / 2};
    f = (Vector2){center.x,
                  center.y + segment_width / 2 + segment_thickness / 2};
  }
  Vector2 points[] = {a, b, c, d, e, f};

  DrawTriangleStrip(points, count, color);
}

void drawDigit(Vector2 center, int digit) {
  // Find the Digit to Draw
  int *digit_segment = &digits[digit][0];

  drawStrip((Vector2){center.x, center.y - segment_width - OFFSET},
  true, digit_segment[0] ? WHITE : GRAY);
  drawStrip((Vector2){center.x - segment_width / 2 - OFFSET/2, center.y - segment_width / 2 - OFFSET / 2},
  false, digit_segment[1] ? WHITE : GRAY);
  drawStrip((Vector2){center.x + segment_width / 2 + OFFSET/2, center.y - segment_width / 2 - OFFSET / 2},
  false, digit_segment[2] ? WHITE : GRAY);
  drawStrip((Vector2){center.x, center.y},
  true, digit_segment[3] ? WHITE : GRAY);
  drawStrip((Vector2){center.x - segment_width / 2 - OFFSET/2, center.y + segment_width / 2 + OFFSET/2},
  false, digit_segment[4] ? WHITE : GRAY);
  drawStrip((Vector2){center.x + segment_width / 2 + OFFSET/2, center.y + segment_width / 2 + OFFSET/2},
  false, digit_segment[5] ? WHITE : GRAY);
  drawStrip((Vector2){center.x, center.y + segment_width + OFFSET},
  true, digit_segment[6] ? WHITE : GRAY);
}

int main(int argc, char *argv[]) {
  time_t current_time = time(NULL);
  char *time_string = ctime(&current_time);

  printf("The current time is %s\n", time_string);

  InitWindow(WIDTH, HEIGHT, "Digital Clock!");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    drawDigit((Vector2){90, HEIGHT / 2}, 0);
    drawDigit((Vector2){200, HEIGHT / 2}, 1);
    drawDigit((Vector2){390, HEIGHT / 2}, 2);
    drawDigit((Vector2){500, HEIGHT / 2}, 3);
    drawDigit((Vector2){690, HEIGHT / 2}, 4);
    drawDigit((Vector2){800, HEIGHT / 2}, 5);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
