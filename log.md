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

是不行的，或许等麦克风到了先试试麦克风？
但其实是可以的，可以看看这个[VU METER (Music Visualizer) #1 With Arduino](https://www.instructables.com/id/UV-METER-Music-Visualizer-1-With-Arduino/)
然后我才意识到直接google：arduino巴拉巴拉music visualizer的东西似乎没太大帮助（~~因为看不懂..~~），倒是直接搜EQ倒还有不少是基础的东西。
库的话就用[NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)了
<br />
<br />

>2018.12.23
>----
卖家给我发错货了...给我发了5个A4988，是想让我用步进电机的读数做嘛（滑稽）
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

>2018.12.24
>----
我发现的确是板子好像有点问题（~~依稀记得很久以前好像冒过烟...~~）
换了一块就只有`p1`和`p3`有读数了，然后把音频从`p4`输入,就发现好像怪怪的（~~应该是因为我没有看说明书~~）  
如图针脚插线：

![](https://github.com/EricHerilan/A-really-simple-music-visualizer/raw/master/img/mess5.jpg)

`p4`插的是电脑音频左右声道，接地也接了，但是信号确出现在`p2`上了...

![](https://github.com/EricHerilan/A-really-simple-music-visualizer/raw/master/img/mess3.gif)

不管了，反正能用就是了，至于会不会烧坏嘛...让时间去证明把，反正到现在为止好像都没有冒过烟。  
现在就先试试放首歌看看，手机的音频信号相对弱一点，所以就拔掉电阻了：

![](https://github.com/EricHerilan/A-really-simple-music-visualizer/raw/master/img/mess4.gif)

似乎是可以了，就是东西还没写完整，完整的在[tool](https://github.com/EricHerilan/A-really-simple-music-visualizer/raw/master/tools)目录下面  
里面现在有一个上面的`input_debug`和这个`onebar_EQ_test`  
现在把单条的EQ放的大一点的列阵上看看效果：

![](https://github.com/EricHerilan/A-really-simple-music-visualizer/raw/master/img/mess6.gif)

~~我觉得海星~~，当然这只是第一步，之后还要换麦克风试试，以及最终的视觉效果，当然不可能只是简简单单的EQ条（~~其实也想不出什么好的~~）
<br />
<br />

>2018.12.26
>----
麦克风传感器终于到了，以及attiny88带usb
![](https://github.com/EricHerilan/A-really-simple-music-visualizer/raw/master/img/mess7.jpg)<br />
但是又有一堆问题堆在了本小白面前：输入信号...  
如果处理不好的话估计什么效果都别想做了。  
然而现实就是：直接输入信号估计是行不通了，如下attiny88，A0直接输入音频信号
![](https://github.com/EricHerilan/A-really-simple-music-visualizer/raw/master/img/mess8.gif)<br />
暂且没法直接用了，然后又去网上草草翻了一下资料，现在还在研究[Devon Crawford的一个视频](https://www.youtube.com/watch?v=lU1GVVU9gLU),里面提到了一个电压频率转换器——LM331N（我也不知道干嘛用的）具体还需要多看点实例，是时候去趟学校图书馆了（我个视传的居然回去图书馆4西楼也是绝了），又是一小笔开销。
然后看到有不少用SparkFun Spectrum Shield或者一种现成的板子：nootropic Lumazoid Music Visualizer，当然出于成本和学习的目的这些100%是不会考虑在内的。
不过从EQ条那几个例子来看，输入还需要有不同的频率，这样最终的参数也会更多的点，也会有更多可能性（~~可能~~）  
~~问题是我也不知道怎么区分频率~~。
啊啊啊，不管了，都要寒假了，R6启动！
<br />
<br />

>2018.12.27
>----
还得多看看arduino的[Reference](https://www.arduino.cc/reference/en/#functions)  
我才知道不是所有的pin能`analogRead()`而且在arduino的[Reference](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)里也写得明明白白...（~~果然是不看说明书的后果~~）  
嘛，看来之前都是瞎搞搞的，而且之前85能读频率估计也是巧合，看来频率转电压这一步看来是必要的了，似乎还要用到示波器...  
看来下一个亟待解决的问题就是**F转V**了
<br />
<br />

>2019.1.1
>----
新年了，寒假要鸽了，因为东西都放学校了...  
这两天倒是搞了个不怎么相干的东西——物理按键说话（push to talk key）  
因为现在语音搞了个soundbord（放那种搞笑声音片段用的那种）所以又两个音源输入了，但电脑上耳机孔就一个，而且就算有两个要让游戏一起读取两个audio in太麻烦了，就搞了这么个偷懒的东西lul  
![](https://github.com/EricHerilan/A-really-simple-music-visualizer/raw/master/img/mess9.jpg)<br />
当然这个电路也是乱接的毕竟~~怎么能响怎么搞~~。
最近还在看[greatscottlab](https://www.youtube.com/user/greatscottlab)做的一些挺有趣的东西，当然人家比起我不知道硬核到哪里去了。  
不过倒是有不少东西能让我让我节省不少时间，比如~~去~~前年这位大佬[diy过一个麦克风](https://www.youtube.com/watch?v=ts-JqEVzvDo)，里面还告诉你这么做个amp（美滋滋）。
其实我对这些原件都不了解，~~甚至不知道三极管、电容啥的干嘛用~~...
毕竟随便玩玩嘛~  
不过现在倒是要重新考虑下最后到底要呈现出怎么样效果了，毕竟attiny的容量小，或许之后会换个mega吧，多余的attiny还能diy个键盘啥的。  
倒是物理这边发生了件搞笑的事情，应为之前麦克风卖家给我发错货了，然后换货到卖家手上了后说立刻给我发，结果一个礼拜过去说忘记给我发货了，我就直接要求退款了，结果第二天收到了换货的包裹...现在手上有一把麦克风了，我在想要不要搞个多声道什么的。  
当然是有生之年系列了。
<br />
<br />
