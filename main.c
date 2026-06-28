#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600

#define OFFSET 30

#define COLOR_BG       /*(Color){ 10, 16, 10, 255 }*//*(Color){ 22, 14, 8, 255 }*/(Color){ 24, 12, 36, 255 }/*(Color){ 20, 20, 23, 255 }*/
#define COLOR_ACTIVE   /*(Color){ 0, 255, 65, 255 }*//*(Color){ 255, 140, 0, 255 }*/(Color){ 255, 0, 127, 255 }/*(Color){ 240, 240, 245, 255 }*/
#define COLOR_INACTIVE /*(Color){ 0, 45, 15, 255 }*//*(Color){ 60, 30, 5, 255 }*/(Color){ 65, 25, 75, 255 }/*(Color){ 50, 50, 55, 255 }*/

char *slice(const char *str, size_t start, size_t end) {
  char *result;
  strncpy(result, str + start, end - start);
  return result;
}

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

  drawStrip((Vector2){center.x, center.y - segment_width - OFFSET}, true,
            digit_segment[0] ? COLOR_ACTIVE : COLOR_INACTIVE);
  drawStrip((Vector2){center.x - segment_width / 2 - OFFSET / 2,
                      center.y - segment_width / 2 - OFFSET / 2},
            false, digit_segment[1] ? COLOR_ACTIVE : COLOR_INACTIVE);
  drawStrip((Vector2){center.x + segment_width / 2 + OFFSET / 2,
                      center.y - segment_width / 2 - OFFSET / 2},
            false, digit_segment[2] ? COLOR_ACTIVE : COLOR_INACTIVE);
  drawStrip((Vector2){center.x, center.y}, true,
            digit_segment[3] ? COLOR_ACTIVE : COLOR_INACTIVE);
  drawStrip((Vector2){center.x - segment_width / 2 - OFFSET / 2,
                      center.y + segment_width / 2 + OFFSET / 2},
            false, digit_segment[4] ? COLOR_ACTIVE : COLOR_INACTIVE);
  drawStrip((Vector2){center.x + segment_width / 2 + OFFSET / 2,
                      center.y + segment_width / 2 + OFFSET / 2},
            false, digit_segment[5] ? COLOR_ACTIVE : COLOR_INACTIVE);
  drawStrip((Vector2){center.x, center.y + segment_width + OFFSET}, true,
            digit_segment[6] ? COLOR_ACTIVE : COLOR_INACTIVE);
}

int main(int argc, char *argv[]) {
  InitWindow(WIDTH, HEIGHT, "Digital Clock!");

  while (!WindowShouldClose()) {
    time_t now = time(NULL); 
    struct tm *t = localtime(&now);
    int hour = t->tm_hour;
    int min = t->tm_min;
    int sec = t->tm_sec;
    
    int hour1 = hour / 10;
    int hour2 = hour % 10;
    int minute1 = min / 10;
    int minute2 = min % 10;
    int second1 = sec / 10;
    int second2 = sec % 10;
    
    BeginDrawing();
    ClearBackground(COLOR_BG);

    drawDigit((Vector2){90, HEIGHT / 2}, hour1);
    drawDigit((Vector2){200, HEIGHT / 2}, hour2);
    DrawCircle(295, HEIGHT / 2 - 50, 12, COLOR_ACTIVE);
    DrawCircle(295, HEIGHT / 2 + 50, 12, COLOR_ACTIVE);
    drawDigit((Vector2){390, HEIGHT / 2}, minute1);
    drawDigit((Vector2){500, HEIGHT / 2}, minute2);
    DrawCircle(595, HEIGHT / 2 - 50, 12, COLOR_ACTIVE);
    DrawCircle(595, HEIGHT / 2 + 50, 12, COLOR_ACTIVE);
    drawDigit((Vector2){690, HEIGHT / 2}, second1);
    drawDigit((Vector2){800, HEIGHT / 2}, second2);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
