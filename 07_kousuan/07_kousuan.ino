//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//---------------------------------------- Including Libraries.
#include <WiFi.h>
#include <WebServer.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Preferences.h>
#include "PageIndex.h" //--> Include the contents of the User Interface Web page, stored in the same folder as the .ino file
//----------------------------------------

// Uncomment according to your hardware type.
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
// #define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins.
#define MAX_DEVICES 4
#define CS_PIN 5
#define MAX_VALUE 20
#define SPEED_TIME  100   //--> SPEED_TIME is the speed of displaying the effect.
#define PAUSE_TIME  2000  //--> PAUSE_TIME is the time delay for switching between effects.

//----------------------------------------Variable declaration for your network credentials.
const char *ssid = "veryslow"; //--> Your wifi name
const char *password = "xxxx"; //--> Your wifi password
//----------------------------------------

// initialize variables.
// 计数器
int cnt_Text = 0;
// 最后一次的运算表达式
char lastExpression[101] = "1+1=?";
// 最新的运行状态
char lastStatus[101] = "true";

// 定义一个枚举类型
enum Operation
{
    PLUS,
    MINUS,
    MULTIPLE,
    DIVIDE,
    OPERATION_COUNT
};

// 定义一个字符串数组
const char *operationArray[OPERATION_COUNT] = {"+", "-", "*", "/"};

// 定义一个运算的范围值
const int calulate_Max_Value = MAX_VALUE;

char show_Text[101] = "";
// char Text_1[101] = "";
// char Text_2[101] = "";
// char Text_3[101] = "";
// char Text_4[101] = "";

// Initialization of "MD_Parola" library as "Display" and its settings.
MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Initialize the "Preferences" library as "preferences".
Preferences preferences;

// Server on port 80.
WebServer server(80);

//________________________________________________________________________________ handleRoot()
// This routine is executed when you open ESP32 IP Address in browser.
void handleRoot()
{
    server.send(200, "text/html", MAIN_page); // Send web page
}
//________________________________________________________________________________
void generate_Random_Expression()
{
    // 生成随机数
    int num1 = random(1, calulate_Max_Value);
    int num2 = random(1, calulate_Max_Value);
    int operation = random(0, OPERATION_COUNT);

    // 生成表达式
    sprintf(lastExpression, "%d%s%d=?", num1, operationArray[operation], num2);
}

// Subroutine to handle configs. The logic of random questions is set here.
void handleConfigs()
{
    // 1. 保存配置到flash，存储的内容：运算类型，运算范围
    // 2. 默认开始生成题目
    // 3. 循环显示生成的题目
    // 4. 点击 web 页面上的停止按钮
    // 5. 保存题目到flash
    // 6. 显示题目

    read_Status_from_Flash_Memory();


    String incoming_Configs = server.arg("triggerNext");
    Serial.println();
    Serial.println("------------Configs");
    Serial.print("Key : ");
    Serial.println(incoming_Configs);
    String symbol = server.arg("symbol");
    String maxValue = server.arg("maxValue");
    Serial.print("Symbol : ");
    Serial.println(symbol);
    Serial.print("Max Value : ");
    Serial.println(maxValue);

    if (incoming_Configs == "true")
    {
        // 生成随机表达式
        generate_Random_Expression();
        Serial.print("Expression : ");
        Serial.println(lastExpression);
        server.send(200, "text/plane", lastExpression);
        save_Text_to_Flash_Memory();
        set_Scrolling_Text_Display();
    }
}

//________________________________________________________________________________ read_Status_from_Flash_Memory()
void read_Status_from_Flash_Memory()
{
    Serial.println();
    Serial.println("------------Read status from flash memory.");

    // Read the last expression from the flash memory.
    String saved_Expression = "";
    int saved_Expression_Length;
    saved_Expression = preferences.getString("EXPRESSION", "");
    saved_Expression_Length = saved_Expression.length() + 1;
    saved_Expression.toCharArray(lastExpression, saved_Expression_Length);
    Serial.print("Expression text   : ");
    Serial.println(lastExpression);
    Serial.print("Expression length : ");
    Serial.println(strlen(lastExpression));

    Serial.println("------------");
}

//________________________________________________________________________________ save_Text_to_Flash_Memory()
void save_Text_to_Flash_Memory()
{
    Serial.println();
    Serial.println("Save text to flash memory.");

    preferences.putString("EXPRESSION", lastExpression);
}
//________________________________________________________________________________

//________________________________________________________________________________ set_Scrolling_Text_Display()
void set_Scrolling_Text_Display()
{
    Serial.println();
    Serial.println("Set Scrolling Text Display.");

    Display.begin();
    delay(500);
    Display.setIntensity(0);
    Display.setInvert(false);
    // Display.displayScroll(show_Text, PA_RIGHT, PA_SCROLL_LEFT, 75);
    Display.displayText(show_Text, PA_CENTER, SPEED_TIME, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);
}
//________________________________________________________________________________

//________________________________________________________________________________ Scrolling_Text()
void Scrolling_Text()
{
    if (Display.displayAnimate())
    {
        strcpy(show_Text, lastExpression);

        Serial.println();
        Serial.print("Scroll Text_");
        Serial.print(cnt_Text);
        Serial.println(".");

        delay(2000);
        Display.displayReset();
    }
}
//________________________________________________________________________________

//________________________________________________________________________________ VOID SETUP()
void setup()
{
    // put your setup code here, to run once:

    Serial.begin(115200);
    Serial.println();
    delay(2000);

    preferences.begin("kousuan", false);

    delay(500);

    read_Status_from_Flash_Memory();

    delay(500);

    // Calls the "set_Scrolling_Text_Display()" subroutine.
    set_Scrolling_Text_Display();

    delay(500);

    //----------------------------------------Set Wifi to STA mode.
    Serial.println();
    Serial.println("-------------");
    Serial.println("WIFI mode : STA");
    WiFi.mode(WIFI_STA);
    Serial.println("-------------");
    //----------------------------------------

    //----------------------------------------Connect to Wi-Fi (STA).
    Serial.println();
    Serial.println("------------");
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    //:::::::::::::::::: The process of connecting ESP32 with WiFi Hotspot / WiFi Router.
    // The process timeout of connecting ESP32 with WiFi Hotspot / WiFi Router is 20 seconds.
    // If within 20 seconds the ESP32 has not been successfully connected to WiFi, the ESP32 will restart.
    // I made this condition because on my ESP32, there are times when it seems like it can't connect to WiFi, so it needs to be restarted to be able to connect to WiFi.

    int connecting_process_timed_out = 20; //--> 20 = 20 seconds.
    connecting_process_timed_out = connecting_process_timed_out * 2;
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
        if (connecting_process_timed_out > 0)
            connecting_process_timed_out--;
        if (connecting_process_timed_out == 0)
        {
            Serial.println();
            Serial.println("Failed to connect to WiFi. The ESP32 will be restarted.");
            Serial.println("------------");
            delay(1000);
            ESP.restart();
        }
    }

    Serial.println();
    Serial.println("WiFi connected");
    Serial.print("Successfully connected to : ");
    Serial.println(ssid);
    Serial.println("------------");
    //::::::::::::::::::
    //----------------------------------------

    delay(1000);

    //---------------------------------------- Setting the server.
    // TODO
    server.on("/", handleRoot);
    // server.on("/settings", handleSettings);
    server.on("/configs", handleConfigs);
    //----------------------------------------

    //---------------------------------------- Start server.
    server.begin();
    Serial.println();
    Serial.println("HTTP server started");
    //----------------------------------------

    delay(500);

    // Open the IP address in your browser to open the interface page.
    // Make sure that your computer / mobile device and ESP32 are connected to the same WiFi network.
    Serial.println();
    Serial.print("IP address : ");
    Serial.println(WiFi.localIP());
    Serial.println("Open the IP address in your browser to open the interface page.");
    Serial.println("Make sure that your computer / mobile device and");
    Serial.println("ESP32 are connected to the same WiFi network.");

    delay(500);

    // Call the "set_Scrolling_Text_Display()" subroutine again.
    set_Scrolling_Text_Display();

    delay(500);
}
//________________________________________________________________________________

//________________________________________________________________________________ VOID LOOP()
void loop()
{
    // put your main code here, to run repeatedly:

    // Handle client requests.
    server.handleClient();

    Scrolling_Text();
}
//________________________________________________________________________________
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
