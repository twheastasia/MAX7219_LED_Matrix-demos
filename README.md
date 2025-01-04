原版视频： https://www.youtube.com/watch?v=dLHldxZ8Dc0

# 通用步骤
ARDUINO IDE + ESP32 + MAX7219 LED Matrix 32x8 Module.

### Arduino libraries used :
MD_MAX72XX (V3.5.1).
MD_Parola (V3.7.3).

### Hardware used :
Nodemcu-32
MAX7219 LED Matrix 32x8 FC-16 Module.

### Connection :
```plaintext
CS_PIN 5
CLK_PIN 18
DIN_PIN 23
```

# demo 解析
1. 分钟数和秒数的倒计时
2. 滚动特效
5. Station Mode，控制LED Matrix显示的内容
6. AP Mode，控制LED Matrix显示的内容 