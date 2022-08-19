#include <Arduino.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_ST7735.h>

#define CS 7
#define DC 6
#define RET 10
#define SCL 2
#define SDA 3
#define BL 18

// Adafruit_ST7735 tft = Adafruit_ST7735(CS, DC, SDA, SCL, RET);

int dispLines[9][8];
int xlines[9][88];
int ylines[99][8];

int pins[] = {3, 10, 6, 7, 0, 5, 4, 18, 13};
int pinCnt = 9;
const unsigned char nums[][9] = {
    //   {0x1C,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x1C},
    //   {0x08,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08},/*"1",0*/
    // // /* (8 X 9 , MS Sans Serif )*/

    // {0x1C,0x22,0x02,0x02,0x04,0x08,0x10,0x20,0x3E},/*"2",1*/
    // // /* (8 X 9 , MS Sans Serif )*/

    // {0x1C,0x22,0x02,0x02,0x0C,0x02,0x02,0x22,0x1C},/*"3",2*/
    // // /* (8 X 9 , MS Sans Serif )*/

    // {0x04,0x0C,0x0C,0x14,0x14,0x24,0x3E,0x04,0x04},/*"4",3*/
    // // /* (8 X 9 , MS Sans Serif )*/

    // {0x3E,0x20,0x20,0x3C,0x22,0x02,0x02,0x22,0x1C},/*"5",4*/
    // // /* (8 X 9 , MS Sans Serif )*/

    // {0x1C,0x22,0x20,0x20,0x3C,0x22,0x22,0x22,0x1C},/*"6",5*/
    // // /* (8 X 9 , MS Sans Serif )*/

    // {0x3E,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x10},/*"7",6*/
    // // /* (8 X 9 , MS Sans Serif )*/

    // {0x1C,0x22,0x22,0x22,0x1C,0x22,0x22,0x22,0x1C},/*"8",7*/
    // // /* (8 X 9 , MS Sans Serif )*/

    // {0x1C,0x22,0x22,0x22,0x1E,0x02,0x02,0x22,0x1C},/*"9",8*/
    /* (8 X 9 , MS Sans Serif )*/

    {0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C}, /*"0",0*/
    /* (8 X 9 , MS Sans Serif, 加粗 )*/

    {0x18, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}, /*"1",1*/
    /* (8 X 9 , MS Sans Serif, 加粗 )*/

    {0x3C, 0x66, 0x06, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x7E}, /*"2",2*/
    /* (8 X 9 , MS Sans Serif, 加粗 )*/

    {0x3C, 0x66, 0x06, 0x06, 0x1C, 0x06, 0x06, 0x66, 0x3C}, /*"3",3*/
    /* (8 X 9 , MS Sans Serif, 加粗 )*/

    {0x0C, 0x1C, 0x1C, 0x3C, 0x3C, 0x6C, 0x7E, 0x0C, 0x0C}, /*"4",4*/
    /* (8 X 9 , MS Sans Serif, 加粗 )*/

    {0x7E, 0x60, 0x60, 0x7C, 0x66, 0x06, 0x06, 0x66, 0x3C}, /*"5",5*/
    /* (8 X 9 , MS Sans Serif, 加粗 )*/

    {0x3C, 0x66, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x3C}, /*"6",6*/
    /* (8 X 9 , MS Sans Serif, 加粗 )*/

    {0x7E, 0x06, 0x0C, 0x0C, 0x18, 0x18, 0x30, 0x30, 0x30}, /*"7",7*/
    /* (8 X 9 , MS Sans Serif, 加粗 )*/

    {0x3C, 0x66, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x66, 0x3C}, /*"8",8*/
    /* (8 X 9 , MS Sans Serif, 加粗 )*/

    {0x3C, 0x66, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x66, 0x3C}, /*"9",9*/
                                                            /* (8 X 9 , MS Sans Serif, 加粗 )*/

     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*" ", */                                                         

};

void SetAllBlock()
{
  for (int i = 0; i < pinCnt; i++)
  {
    pinMode(pins[i], INPUT);
    digitalWrite(pins[i], LOW);
  }
}

int f = 1;

void SetOneBlock(int pin)
{
  pinMode(pin, INPUT);
  digitalWrite(pin, LOW);
}
void TestOne(int curIdx)
{
  SetAllBlock();
  pinMode(pins[curIdx], OUTPUT);
  digitalWrite(pins[curIdx], HIGH);
  for (int i = 0; i < pinCnt; i++)
  {
    if (i == curIdx)
      continue;
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
    // delayMicroseconds(1440);
    SetOneBlock(pins[i]);
  }
  SetOneBlock(pins[curIdx]);
}

void lightByXY(int x, int y)
{
  // SetAllBlock();
  if (x >= y)
    x = x + 1;

  // SetAllBlock();
  int px = pins[y];
  int py = pins[x];

  pinMode(px, OUTPUT);
  pinMode(py, OUTPUT);
  digitalWrite(px, HIGH);
  digitalWrite(py, LOW);
  delayMicroseconds(80);
  SetOneBlock(px);
  SetOneBlock(py);
  // delayMicroseconds(200);
}
void displayNum(int dots[][8], int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int m = 0; m < 8; m++)
    {
      if (dots[i][m] == 1)
        lightByXY(m, i);
    }
  }
}
int *getBin(int Dec)
{
  //  Dec=128;
  static int a[8];
  for (int i = 7; i >= 0; i--)
  {
    if (pow(2, i) <= Dec)
    {
      Dec = Dec - pow(2, i);
      a[7 - i] = 1;
    }
    else
    {
      a[7 - i] = 0;
    }
  }
  return a;
};

String getNumStr(int idx)
{
  String r = "";
  for (int n = 0; n < 9; n++)
  {
    int *lines = getBin(nums[idx][n]);
    for (int d = 0; d < 8; d++)
    {
      // Serial.print(lines[d]);
      r += (String)lines[d];
      if (lines[d] == 1)
        lightByXY(d, n);
      // delayMicroseconds(14000);
    }
    r += "\r\n";
  }
  // Serial.println(r);
  //  Serial.println("");
  return r;
}

void getLeftToRightNumStr(const unsigned char str[][9], int asize)
{
  String r = "";
  // int ka[9][8 * asize];
  for (int i = 0; i < asize; i++)
  {
    for (int m = 0; m < 9; m++)
    {
      int *ls = getBin(str[i][m]);
      for (int d = 0; d < 8; d++)
      {
        xlines[m][8 * i + d] = ls[d];
        r += (String)ls[d];
      }
    }
  }
}
int inc = 0;

void moveRight()
{
  for (int i = 0; i < 10; i++)
  {
    for (int d = 0; d < 8; d++)
    {
      int p = d + inc;
      if (p < 88)
      {
        dispLines[i][d] = xlines[i][p];
      }
      else if (p < 95)
      {
        dispLines[i][d] = 0;
      }
      else
      {
        inc = 0;
      }
    }
  }
}

void moveLeft()
{
  for (int i = 0; i < 10; i++)
  {
    for (int d = 7; d >=0; d--)
    {
      int p = 88-d-inc;
      if (p <= 88&&p>=0)
      {
        dispLines[i][7-d] = xlines[i][p];
        //  dispLines[i][d] = xlines[i][p];
      }
      //  else if (p <=0 &&p>-7)
      // {
      //   dispLines[i][d] = 0;
      // }
      else
      {
        inc = 0;
      }
    }
  }
}
void getRightToLeftNumStr(const unsigned char str[][9], int asize)
{
  // int ka[9][8 * asize];
  // for (int i = 0; i < asize; i++)
  for (int i = asize - 1; i >= 0; i--)
  {
    for (int m = 0; m < 9; m++)
    {
      int *ls = getBin(str[i][m]);
      for (int d = 7; d >= 0; d--)
      {
        xlines[m][8 * (asize - 1 - i) + d] = ls[d];
      }
    }
  }
}
void getTopToBottomNumStr(const unsigned char str[][9], int asize)
{
  // int ka[9 * asize][8];
  for (int i = 0; i < asize; i++)
  {
    for (int m = 0; m < 9; m++)
    {
      int *ls = getBin(str[i][m]);
      for (int d = 0; d < 8; d++)
      {
        ylines[9 * i + m][d] = ls[d];
      }
    }
  }
}

void getBottomToTopNumStr(const unsigned char str[][9], int asize)
{
  // int ka[9 * asize][8];
  for (int i = 0; i < asize; i++)
  {
    for (int m = 0; m < 9; m++)
    {
      int *ls = getBin(str[i][m]);
      for (int d = 7; d >= 0; d--)
      {
        ylines[9 * (asize - 1 - i) + m][d] = ls[d];
      }
    }
  }
  int i2 = 0;
  int i3 = 1;
  for (int i = 0; i < 9 * asize; i++)
  {
    if (i < 9)
      i2 = i;
    else
    {
      i2 = i - i3;
      i3 = i3 + 1;
    }
    // i2=i/9;
    for (int cc = 0; cc < 200; cc++)
    {
      for (int c = 0; c < 8; c++)
      {
        if (ylines[i][c] == 1)
        {
          lightByXY(c, i2);
          // delayMicroseconds(100);
        }
      }
      // Serial.print(ka[i][c]);
      // Serial.print(" ");
    }

    // Serial.println("");
  }
}

void setup()
{
  // put your setup code here, to run once:
  // tft.initR(INITR_BLACKTAB);
  // tft.fillScreen(ST7735_BLACK);
  // tft.setTextColor(ST7735_YELLOW);
  // tft.setTextSize(1);
  // //  tft.setCursor(10,10);
  // tft.println("  All come for this.Thi is Hello!");
  // tft.println("i am sean pu.welcome to this tft world!");
  // pinMode(18, OUTPUT);
  // digitalWrite(18, HIGH);
  // Serial.begin(115200);
  // pinMode(4, OUTPUT);
  // pinMode(5, OUTPUT);
  SetAllBlock();
  Serial.begin(115200);
  // getLeftToRightNumStr(nums, 10);
  getRightToLeftNumStr(nums, 11);//9876543210
}
void loop()
{
  // getMoveNumStr(nums,10);
  // int a1 [3] [2]={{1,2},{1,333},{5,2}};
  // moveLeft();
  moveRight();
  for (int i = 0; i < 100; i++)
  {
    displayNum(dispLines, 9);
  }

  inc += 1;
  // if (inc >= 80)
  //   inc = 0;
  //  delay(10);
  // delay(1000);
  // for (int d = 0; d < 10; d++)
  // {
  //   for (int cc = 0; cc < 80; cc++)
  //   {
  //     getNumStr(d);
  //   }
  // }
  // delay(1000);
  // delay(1000);
  // getNumStr(1);
  // delay(1000);
  // getNumStr(2);
  // delay(1000);
  return;
  // tft.setTextColor(ST7735_GREEN);
  // tft.print(i);
  //   delay(100);
  // put your main code here, to run repeatedly:
  f = f + 1;
  // digitalWrite(4, LOW);
  // digitalWrite(5, HIGH);
  // delayMicroseconds(100);
  // digitalWrite(5, LOW);
  // CloseAll(12);
  //  TestOne(0);
  //  TestOne(1);
  //   TestOne(2);
  //    TestOne(3);
  //     TestOne(4);

  //   TestOne(8);
}
