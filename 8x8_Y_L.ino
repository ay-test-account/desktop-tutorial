float k = 0;
char row[8]    = {38, 40, 42, 44, 46, 48, 50, 52};
char column[8] = {39, 41, 43, 45, 47, 49, 51, 53};

int Screen[64] = {0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0
                 };
void cls_Led() {
  for (int i = 0; i < 8 ; i++) {
    digitalWrite (column[i], LOW);
    digitalWrite (row[i], HIGH);
  }
}
void one_led(int x, int y) {
  cls_Led();
  digitalWrite (column[x], HIGH);
  digitalWrite (row[y], LOW);
  delay (1);
}

void setup() {
  int i = 38;
  while (i < 54) {
    pinMode (i, OUTPUT);
    i++;
  }
  pinMode (A1, INPUT);
  pinMode (A2, INPUT);
  pinMode (A3, INPUT);
  pinMode (A4, INPUT);
  Serial.begin(9600);
  cls_Led();
}
void draw_old(int n) {
  for (int i = 0; i < n; i++) {
    for (int i = 0; i < 64; i++) {
      if (Screen[i] == 1) {
        one_led(i % 8, i / 8);
      }
    }
  }
}
void draw(int n) {
  for (int t = 0; t < n; t++) {
    for (int y = 0; y < 8; y++) {
      digitalWrite(row[y], LOW);
      for (int x = 0; x < 8; x++) {
        if (Screen[y * 8 + x] == 1) {
          digitalWrite (column [x], HIGH);
        }
        if (Screen[y * 8 + x] == 2) {
          digitalWrite (column [x], HIGH);
          digitalWrite (column [x], LOW);
        }
      }
      delay(1);
      for (int x = 0; x < 8; x++) {
        digitalWrite (column [x], LOW);
      }
      digitalWrite(row[y], HIGH);
    }
  }
}

void loop() {
  for (int i = 0; i < 64; i++) {
    Screen [i] = 0;
  }
  for (int x = 0; x < 8; x++) {
    int y = k * x;
    Screen [y * 8 + x] = 1;
    if (y > 7) {
      break;
    }
  }
  draw_old(25);
  //draw(25);

  k = k + 0.1;
  if (k == 2.3) {
    k = 0;
  }
}
