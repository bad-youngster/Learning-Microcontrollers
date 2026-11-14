#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 定义 OLED 屏幕宽度和高度（像素）
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 // 如果没有复位引脚设为 -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 引脚定义
const int PIN_RED = 9;
const int PIN_YELLOW = 10;
const int PIN_GREEN = 11;
const int PIN_BUTTON = 2; 
const int PIN_LDR = A0;   

const int LIGHT_THRESHOLD = 200; 
bool pedestrianRequested = false;

// 封装一个在 OLED 上刷新显示信息的函数
void updateDisplay(String statusText, int countdown, int lightVal) {
  display.clearDisplay(); // 清屏
  
  // 第一行：系统标题
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Smart Traffic Light");

  // 第二行：当前光照
  display.setCursor(0, 12);
  display.print("LDR: ");
  display.print(lightVal);

  // 分隔线
  display.drawLine(0, 22, 128, 22, SSD1306_WHITE);

  // 第三行：状态显示
  display.setCursor(0, 30);
  display.print("Status: ");
  display.println(statusText);

  // 第四行：大号字体显示倒计时数字
  display.setTextSize(2);
  display.setCursor(0, 48);
  display.print("Time:");
  display.print(countdown);
  display.print("s");

  display.display(); // 将缓冲区内容渲染到屏幕上
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // 初始化 OLED 屏幕 (地址通常为 0x3C)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 分配屏幕失败！"));
    for(;;); // 停在这里
  }
  
  display.clearDisplay();
  display.display();
  Serial.println("OLED 初始化成功，系统启动！");
}

void loop() {
  int lightVal = analogRead(PIN_LDR);
  
  // 1. 夜间模式判断
  if (lightVal < LIGHT_THRESHOLD) {
    digitalWrite(PIN_RED, LOW);
    digitalWrite(PIN_GREEN, LOW);
    digitalWrite(PIN_YELLOW, HIGH);

    Serial.println(lightVal);
    
    // OLED 显示夜间模式
    updateDisplay("Night Flash", 0, lightVal);
    delay(500);
    digitalWrite(PIN_YELLOW, LOW);
    delay(500);
    return;
  }

  // 2. 白天模式：绿灯阶段 (3秒倒计时)
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_YELLOW, LOW);
  digitalWrite(PIN_RED, LOW);

  Serial.println(lightVal);

  for (int i = 3; i > 0; i--) {
    if (digitalRead(PIN_BUTTON) == LOW) {
      pedestrianRequested = true;
    }
    updateDisplay("GREEN GO", i, lightVal);
    delay(1000); // 每秒更新倒计时
  }

  // 3. 黄灯过渡阶段 (1.5秒，简化为 2 秒倒计时)
  digitalWrite(PIN_GREEN, LOW);
  for (int i = 2; i > 0; i--) {
    digitalWrite(PIN_YELLOW, HIGH);
    updateDisplay("YELLOW WARN", i, lightVal);
    delay(500);
    digitalWrite(PIN_YELLOW, LOW);
    delay(500);
  }

  // 4. 红灯阶段 (根据是否有行人请求决定时长：5秒或2秒)
  digitalWrite(PIN_RED, HIGH);
  int redTime = pedestrianRequested ? 5 : 2;

  for (int i = redTime; i > 0; i--) {
    updateDisplay(pedestrianRequested ? "PEDESTRIAN" : "RED STOP", i, lightVal);
    delay(1000);
  }
  
  if (pedestrianRequested) {
    pedestrianRequested = false; // 重置按键标志
  }
  digitalWrite(PIN_RED, LOW);
}