#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11, 13); //创建对象

int ThermistorPin = A0;
int Vo;
double R1 = 10000;
double logR2, R2, T, Tc, Tf;
double c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup(void) {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop(void) {
  int value = map(analogRead(A2), 0, 1023, 80, 250);
  //  Serial.println(value);

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0) / 5.0 + 32.0;
  Serial.println(Tc);
  u8g.firstPage();  //表示图像循环的开始
  do {
    u8g.setFont(u8g_font_fub30);//设置字体和自号
    u8g.setPrintPos(5, 55); //显示的位置
    u8g.print(String(int(Tc)) + "C");
    u8g.setFont(u8g_font_fub11);
    u8g.setPrintPos(85, 13);
    u8g.print(String(value) + "C");
    u8g.setFont(u8g_font_fub11);
    u8g.setPrintPos(5, 13);
    u8g.print("Temp:");
  } while ( u8g.nextPage() ); //u8g.nextPage() 表示图像循环的结束

  if (Tc < value-8) {
    digitalWrite(2, HIGH);
    digitalWrite(A1, 1);
  }
  else if (Tc > value+8) {
    digitalWrite(2, LOW);
    digitalWrite(A1, 0);
  }
  delay(100);

}
