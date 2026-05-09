#include <Arduino.h>
#include "communicate.hpp"
#include "screen.hpp"
#include "touch.hpp"

// 一个绘图的触摸回调函数，简单地在触摸位置画一个红色圆点
void draw_touch_cb(int x, int y) {
    tft.fillCircle(x, y, 3, TFT_RED);
}

void setup() {
  i2c_pullup();
  serial_start();
  screen_init();
  touch_init();
  smooth_off();
  // 设置触摸回调函数，这样每次触摸屏幕时都会调用 draw_touch_cb 来在屏幕上绘制一个红点
  set_touch_cb(draw_touch_cb);
  
  // 根据触摸芯片是否被找到决定启动哪个界面
  if (touch_dev._touch_init_done) {
    tft.fillScreen(TFT_WHITE);
  } else {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(2);
    tft.drawString("TOUCH SCREEN NOT FOUND !", tft.width() / 2, tft.height() / 2);
  }
  smooth_on();
}

void loop() {
  serial_loop();
  touch_loop();
}