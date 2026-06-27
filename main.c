#include <raylib.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600

int main(int argc, char *argv[]) {
  time_t current_time = time(NULL);
  char *time_string = ctime(&current_time);

  printf("The current time is %s\n", time_string);

  InitWindow(WIDTH, HEIGHT, "Digital Clock!");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    int count = 6;

    Vector2 center = {WIDTH / 2, HEIGHT / 2};

    float segment_width = 200;
    float segment_thickness = 50;

    Vector2 a, b, c, d, e, f;
    a = (Vector2){center.x - segment_width / 2 - segment_thickness / 2,
                  center.y};
    b = (Vector2){center.x - segment_width / 2,
                  center.y - segment_thickness / 2};
    c = (Vector2){center.x - segment_width / 2,
                  center.y + segment_thickness / 2};
    d = (Vector2){center.x + segment_width / 2,
                  center.y - segment_thickness / 2};
    e = (Vector2){center.x + segment_width / 2,
                  center.y + segment_thickness / 2};
    f = (Vector2){center.x + segment_width / 2 + segment_thickness / 2,
                  center.y};

    Vector2 points[] = {a, b, c, d, e, f};
    DrawTriangleStrip(points, count, SKYBLUE);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
