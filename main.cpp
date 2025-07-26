#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define screen_width 128
#define screen_hight 64

const int buttonpin[] = {13, 12, 14, 27};
int maze[21][41];
int ox = 17, oy = 1;
int path_close = 0;
int game_over = 1;
int x = 19, y = 0;
int xd = 4, yd = 59;
String words = "You Solve Maze";

Adafruit_SSD1306 display(screen_width, screen_hight, &Wire, -1);

void after_match();
void drawPlayer(int px, int py, int color) {
  display.fillRect(3 * py + 1, 3 * px + 1, 3, 3, color);
}

void handlePlayerMove(int dx, int dy) {
  int newX = x + dx;
  int newY = y + dy;

  if (newX < 0 || newX > 20 || newY < 0 || newY > 40) return;

  int cell = maze[newX][newY];
  if (cell == 2) {
    drawPlayer(x, y, BLACK);
    x = newX;
    y = newY;
    drawPlayer(x, y, WHITE);
    delay(150);
  } else if (cell == -2) {
    after_match();
  }
}


void setup() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.print(F("failed"));
    for (;;);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(buttonpin[i], INPUT_PULLUP);
  }

  for (int i = 0; i < 21; i++) {
    for (int j = 0; j < 41; j++) {
      maze[i][j] = (i % 2 == 0 || j % 2 == 0) ? 1 : 0;
    }
  }

  maze[ox][oy] = 2;
  maze[x][y] = -1;
  maze[x][40 - y] = -2;
}

void loop() {
  int directions[4];
  int count = 0;

  if (ox >= 3 && maze[ox - 2][oy] == 0) directions[count++] = 0;
  if (ox <= 17 && maze[ox + 2][oy] == 0) directions[count++] = 1;
  if (oy >= 3 && maze[ox][oy - 2] == 0) directions[count++] = 2;
  if (oy <= 37 && maze[ox][oy + 2] == 0) directions[count++] = 3;

  if (count > 0) {
    int d = directions[esp_random() % count];
    if (d == 0) {
      maze[ox - 1][oy] = 2;
      maze[ox - 2][oy] = 2;
      ox -= 2;
    } else if (d == 1) {
      maze[ox + 1][oy] = 2;
      maze[ox + 2][oy] = 2;
      ox += 2;
    } else if (d == 2) {
      maze[ox][oy - 1] = 2;
      maze[ox][oy - 2] = 2;
      oy -= 2;
    } else if (d == 3) {
      maze[ox][oy + 1] = 2;
      maze[ox][oy + 2] = 2;
      oy += 2;
    }
  } else {
    bool found = false;
    for (int j = 1; j < 40 && !found; j += 2) {
      for (int i = 1; i < 20 && !found; i += 2) {
        if (maze[i][j] == 2 &&
            ((i >= 3 && maze[i - 2][j] == 0) ||
             (i <= 17 && maze[i + 2][j] == 0) ||
             (j >= 3 && maze[i][j - 2] == 0) ||
             (j <= 37 && maze[i][j + 2] == 0))) {
          ox = i;
          oy = j;
          found = true;
        }
      }
    }

    if (!found) {
      display.clearDisplay();
      display.fillRect(2, 2, 121, 61, WHITE);
      for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 41; j++) {
          if (maze[i][j] == 2 || maze[i][j] == -2 || maze[i][j] == -1) {
            display.fillRect(3 * j, 3 * i, 5, 5, BLACK);
          }
        }
      }

      drawPlayer(x, y, WHITE);
      display.display();

      while (game_over == 1) {
        if (digitalRead(buttonpin[2]) == LOW) handlePlayerMove(-1, 0); // Up
        else if (digitalRead(buttonpin[3]) == LOW) handlePlayerMove(1, 0);  // Down
        else if (digitalRead(buttonpin[0]) == LOW) handlePlayerMove(0, -1); // Left
        else if (digitalRead(buttonpin[1]) == LOW) handlePlayerMove(0, 1);  // Right

        display.display();
      }
    }
  }
}

void after_match() {
  game_over = 1;
  display.clearDisplay();
  display.display();
  int16_t x1, y1;
  uint16_t width, hight;
  display.getTextBounds(words, 0, 0, &x1, &y1, &width, &hight);
  int x2 = (screen_width - width) / 2;
  int y2 = (screen_hight - hight) / 2;
  display.setCursor(x2, y2);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print(words);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();

  for (int i = 0; i < 21; i++) {
    for (int j = 0; j < 41; j++) {
      maze[i][j] = (i % 2 == 0 || j % 2 == 0) ? 1 : 0;
    }
  }

  ox = 17;
  oy = 1;
  maze[ox][oy] = 2;
  path_close = 0;
  x = 19;
  y = 0;
  xd = 3 * y + 1;
  yd = 3 * x + 1;
  maze[x][y] = -1;
  maze[x][40 - y] = -2;
}
