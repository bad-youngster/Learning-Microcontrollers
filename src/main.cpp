#include <Arduino.h>

// 第4课：交通灯
// 红灯 → 绿灯 → 黄灯 → 循环

const int RED_PIN    = 9;
const int YELLOW_PIN = 10;
const int GREEN_PIN  = 11;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void loop() {
  // 红灯亮 3 秒
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  delay(3000);

  // 绿灯亮 3 秒
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  delay(3000);

  // 黄灯亮 1 秒
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  delay(1000);
}