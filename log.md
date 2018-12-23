开搞！
====
<br />
<br />
<br />

>始 2018.12.20
>----
又到了仅剩的最后两个寒假  
因为之前买的一些RGB灯没用玩想搞个音乐灯什么的  
顺便学习学习arduino，_毕竟刚节的一门课是processing_  
<br />
<br />

>2018.12.22
>----
第一次直接pin1连音频输入，pin0连Led的Din  
黄灯debug  
然后就...:   

![](https://github.com/EricHerilan/A-really-simple-music-visualizer/raw/master/img/unfinisheddemo1.gif)

是不行的，应该还要个放大器什么的，等麦克风到了先试试麦克风。  
<br />
<br />

>2018.12.23
>----
卖家给我发错货了...给我发了5个A4988，是想让我用步进电机的度数做嘛（滑稽）
暂时只能回到3.5mm输入再试试了...
用NeoPixel的库写了一段：

    #include <Adafruit_NeoPixel.h>
    #define PIN 0
    #define NUMPIXELS   10

    int ttalpix = 10; // number of pixel
    int val, pinpl, a;
    int n = 0;
    int music = 5;

    Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

    void setup() {
      strip.begin();
      for (a = 0; a < ttalpix; a++){
      strip.setPixelColor(a, 100, 55, 0);
      strip.show();
      delay(100);
      }
      for (a = 0; a < ttalpix; a++){
      strip.setPixelColor(a, 0, 0, 0);
      strip.show();
      delay(100);
      } //甚至还有个华丽的启动（不）
    }

    void loop() {
      val = analogRead(music) / 5;
      val = map(val, 0, 1024, 1, ttalpix);
      if (val == 0){
        for (a = 0; a < ttalpix; a++){
        strip.setPixelColor(a, 0, 0, 0);
        }
        strip.show();
      }else if (val >= ttalpix){
        for (a = 0; a < ttalpix; a++){
        strip.setPixelColor(a, 200, 105, 0);
        }
        strip.show();
      }else if (val > 0 && val < ttalpix){
        for (a = 0; a < val; a++){
        strip.setPixelColor(a, 200, 105, 0);
        }
      }
      delay(10);
      for (a = 0; a < ttalpix; a++){
      strip.setPixelColor(a, 0, 0, 0);
      }
      strip.show();
    }

然而没有软用，setup后面就没有然后了...
因为手头没有什么工具，甚至没有万用表，所以只能让它自己亮几个灯看看了
于是（P0输出led的信号，P1-P5是空的）：

      void loop() {
        if (analogRead(1) > 150){strip.setPixelColor(0, 0, 0, 120);}
        if (analogRead(2) > 5){strip.setPixelColor(1, 0, 0, 120);}
        if (analogRead(3) > 50){strip.setPixelColor(2, 0, 0, 120);}
        if (analogRead(4) > 10){strip.setPixelColor(3, 0, 0, 120);}
        if (analogRead(5) > 1){strip.setPixelColor(4, 0, 0, 120);}
        strip.show();
        delay(10);
        for (a = 0; a < ttalpix; a++){
        strip.setPixelColor(a, 0, 0, 0);
        }
        strip.show();
      }

然后就这样了：

![](https://github.com/EricHerilan/A-really-simple-music-visualizer/raw/master/img/mess2.gif)

这特么什么玩意儿，我都有点开始怀疑是板子的问题了，三极管的噪波有那么大嘛...。
回头再看看到底怎么直接读3.5mm输入。
<br />
<br />


