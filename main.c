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

    int count = 4;
    Vector2 a, b, c, d;
    a = (Vector2){50, 50};
    b = (Vector2){100, 100};
    c = (Vector2){80, 20};
    d = (Vector2){200, 30};
    Vector2 points[] = {a, b, c, d};
    DrawTriangleStrip(points, count, SKYBLUE);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
