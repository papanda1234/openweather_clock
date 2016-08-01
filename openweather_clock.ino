/**
 * LEDのコード :  https://github.com/Makuna/NeoPixelBus
 * OLEDのコード： https://github.com/squix78/esp8266-oled-ssd1306
 * Webサーバモードのコード : http://qiita.com/exabugs/items/2f67ae363a1387c8967c
 * HTTPクライアントのコード : http://eleclog.quitsq.com/2015/11/esp8266-https.html
 * NTPのコード： https://github.com/exabugs/sketchLibraryNTP
*/

extern "C" {
  #include "user_interface.h"
}

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <FS.h>
#include <NeoPixelBus.h>
#include <NTP.h>
#include <SSD1306.h>
#include <SSD1306Ui.h>

#include "openweather_logo.h"
#include "clear_logo.h"
#include "clouds_logo.h"
#include "rain_logo.h"
#include "snow_logo.h"
#include "celsius_logo.h"

// Simple Timer LibraryがLGPL2のため
class pInterval {
  public:
    uint32_t start_;
    uint32_t ms_;
    bool flip_;
  pInterval(uint32_t ms  = 1000, bool flip = false) : ms_(ms), start_(millis()), flip_(flip) {};
  bool check() { 
      uint32_t now = millis();
      if ((now - start_) > ms_) {
        start_ = now;
        flip_ = !flip_;
        return true; 
      } else {
        return false;
      }
  }
};

// デフォルトデータ
String res_def = String("1850147,Tokyo,-4,11,1463032800,2016-05-12,15:00:00,Clear,1463043600,2016-05-12,18:00:00,Clouds,1463054400,2016-05-12,21:00:00,Rain,1463065200,2016-05-13,00:00:00,Snow,1463076000,2016-05-13,03:00:00,Clouds,1463086800,2016-05-13,06:00:00,Clear");

// メインループのウェイト(ms)
const int waitms = 200;

// ピン配置
const int IO0_PIN = 0; // IO0 pull up
const int I2C_SDA_PIN = 5; // IO5 pull up
const int I2C_SCL_PIN = 4; // IO4 pull up
const int LED_OUT_PIN = 2; // IO2 pull up

// Wi-Fi設定保存ファイル
const char* settings = "/openweather_clock_conf.txt";
const char* pmode_settings = "/pmode_settings.txt";

// サーバモードでのパスワード
const String default_pass = "esp8266pass";

// MACアドレスを文字列化したもの
String macaddr = "";

// サーバモード
char server_mode = 0;

// LED 
int PixelCount = 1;
NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PixelCount, LED_OUT_PIN);
RgbColor red(15, 0, 0);
RgbColor green(0, 15, 0);
RgbColor blue(0, 0, 15);
RgbColor white(30, 30, 30);
RgbColor gray(5, 5, 5);
RgbColor cyan(12, 12, 32);
RgbColor black(0, 0, 0);

// サーバインスタンス
ESP8266WebServer server(80);

// クライアントインスタンス
WiFiClient client;
const String api_host = "www.papa.to";
const String api_path = "/webapi/esp8266/weather.pl";
String ssid, pass, host, path, loc;
String errmes;

// 状態カウンタ
unsigned int count = 0;
int pmode = 0; // 0:Ticker, 1:PwrSave
int dmode = 0; // 0:Normal, 1:Demo
int tickerptr = -1;
int tickermax = 0;
int pushcount = 0;
int errdispcount = 0;
pInterval iv1(3000);
pInterval iv2(300000);
pInterval iv3(1000);

// OLED
const int oled_addr = 0x3C;
SSD1306 display(oled_addr, I2C_SDA_PIN, I2C_SCL_PIN);

String result[40];
int rlen = 0;

int parse_csv_with_led(String res)
{
  rlen = 0;
  int rains = 0;
  Serial.println(res);           
  do {
    int i = res.indexOf(',');
    if (i > 0) {
      result[rlen] = res.substring(0, i);
      result[rlen].trim();
      if (result[rlen].equals("Rain")) {
        rains++;
      }
      if (result[rlen].equals("Snow")) {
        rains++;
      }
      res = res.substring(i + 1);
        rlen++;
        if (rlen >= 40) {
          break;              
        }
    } else {
        result[rlen] = res;
        result[rlen].trim();
        rlen++;
        res = "";
        break;
    }
  } while (res.length() > 0);
  RgbColor color((rains * 1)%256, (rains * 1)%256, (rains * 8)%256);
  strip.SetPixelColor(0, color);
  strip.Show();  
  return rlen;         
}

/**
 * WiFi設定画面(サーバーモード)
 */
void handleRootGet() {
  String html = "";
  html += "<html lang=\"ja\"><head><meta charset=\"utf-8\" /><meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\" /><title>WiFi AP Config</title></head><body>";
  html += "<h1>WiFi AP Config</h1>";
  html += "<form method='post'>";
  html += "  <input type='text' name='ssid' placeholder='ssid' value='" + ssid + "'><br>";
  html += "  <input type='text' name='pass' placeholder='pass' value='" + pass + "'><br>";
  html += "  <input type='text' name='api' placeholder='api' value='" + host + path + "'><br>";
  html += "  <input type='text' name='loc' placeholder='Zip, Location...' value='" + loc + "'><br>";
  html += "  <input type='checkbox' name='dmode' value='1' />demo mode<br><br>";
  
  html += "  <input type='submit'><br>";
  html += "</form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

/**
 * SSID書き込み画面(サーバーモード)
 */
void handleRootPost() {
  Serial.println("POST");
  String ssid = server.arg("ssid");
  String pass = server.arg("pass");
  String api = server.arg("api");
  String loc = server.arg("loc");
  String dmode_str = server.arg("dmode");
  Serial.println(ssid + pass + api + loc + dmode_str);

  File f = SPIFFS.open(settings, "w");
  f.println(ssid);
  f.println(pass);
  f.println(api);  
  f.println(loc);
  f.println(dmode_str);
  f.close();

  String html = "";
  html += "<html lang=\"ja\"><head><meta charset=\"utf-8\" /><meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\" /><title>WiFi AP Accepted</title></head><body>";
  html += "<h1>" + macaddr + "</h1>";
  html += ssid + "<br>";
  html += pass + "<br>";
  html += api + "<br>";
  html += loc + "<br>";
  html += dmode_str + "<br>";
  html += "</body></html>";
  Serial.println("POSTOK");
  server.send(200, "text/html", html);
}

/**
 * ホスト名ロード(クライアントモード) 
 */
void setup_host_and_path(String &ssid, String &pass, String &host, String &path) {
  File f = SPIFFS.open(settings, "r");
  ssid = f.readStringUntil('\n');
  pass = f.readStringUntil('\n');
  String api = f.readStringUntil('\n');
  loc = f.readStringUntil('\n');
  String dmode_str = f.readStringUntil('\n');
  f.close();

  ssid.trim();
  pass.trim();
  api.trim();
  loc.trim();
  dmode_str.trim();
  dmode = dmode_str.toInt() + 0;

  host = api_host;
  path = api_path;
  if (api.length() >= 11) {
    int i = api.indexOf("/");
    if (i >= 8) {
      host = api.substring(0, i);
      path = api.substring(i);
    }
  }
}

/**
 * WiFi接続試行(クライアントモード)
 */
boolean wifi_connect(String ssid, String pass) {
  Serial.println("SSID: " + ssid);
  Serial.println("PASS: " + pass);
  WiFi.begin(ssid.c_str(), pass.c_str());

  char timeout = 30;
  for (; timeout > 0; timeout--) {
    strip.SetPixelColor(0, gray);
    strip.Show();
    delay(100);
    if (WiFi.status() == WL_CONNECTED) {
      strip.SetPixelColor(0, cyan);
      strip.Show();
      delay(100);
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      strip.SetPixelColor(0, black);
      strip.Show();
      return true;    
    }
    Serial.print(".");
    strip.SetPixelColor(0, black);
    strip.Show();
    delay(100);
  }
  return false;
}

/**
 * HTTP POST実行(クライアントモード) 
 */
String http_post(String host, String path, String data) {
  Serial.println("HOST: " + host);
  Serial.println("PATH: " + path);
  if (client.connect(host.c_str(), 80)) {
    client.println("POST " + path + " HTTP/1.1");
    client.println("Host: " + (String)host);
    client.println("User-Agent: ESP8266/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
    int tcount = 100;
    while (!client.available()) {
      delay(50);
      tcount--;
      if (tcount < 0) {
        Serial.println("recv error");
        return "ERROR";
      }
    }
    String response = client.readString();
    int bodypos =  response.indexOf("\r\n\r\n") + 4;
    return response.substring(bodypos);
  }
  else {
    return "ERROR";
  }
}

/**
 * モードセーブ
 */
void save_pmode(int n)
{
  File f = SPIFFS.open(pmode_settings, "w");
  f.println(String(n));
  f.close();
  pmode = n;
}

/**
 * 初期化(サーバモード)
 */
void setup_server() {
  Serial.println("SSID: " + macaddr);
  Serial.println("PASS: " + default_pass);

  server_mode = 1;
  strip.SetPixelColor(0, white);
  strip.Show();

  // モード強制初期化
  save_pmode(0);
    
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(macaddr.c_str(), default_pass.c_str());

  server.on("/", HTTP_GET, handleRootGet);
  server.on("/", HTTP_POST, handleRootPost);
  server.begin();
  Serial.println("HTTP server started.");
}

/**
 * OTA初期化
 */
void setup_ota(String macaddr)
{
  ArduinoOTA.setHostname(macaddr.c_str());
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  MDNS.begin(macaddr.c_str());  
}

/**
 * 初期化(クライアントモード) 
 */
void setup_client() {
  count = 0;

  // モード読み込み
  File f = SPIFFS.open(pmode_settings, "r");
  String pmode_str = f.readStringUntil('\n');
  Serial.println("PMODE:" + pmode_str);
  pmode = pmode_str.toInt();
  f.close();

  if (pmode == 0) {
    for (int x = 128; x >= -512; x -= 8) {
      display.clear(); 
      display.drawXbm(x, -1, openweather_logo_width, openweather_logo_height, (const char*)openweather_logo_bits);
      display.display();
    }    
  }
  delay(800);

  if (dmode == 1) {
    parse_csv_with_led(res_def);          
  } else if (wifi_connect(ssid, pass)) {
    Serial.println("NTP Starting...");
    ntp_begin(2390);
    String data = "q=" + loc + "&mac=" + macaddr;
    String res = http_post(host, path, data);
    if (res.startsWith("ERROR")) {
      errmes = res;
      rlen = 0;
    } else {
      parse_csv_with_led(res);
    }
  }
}   

void power_down(unsigned long sec)
{
  Serial.println("PwrSave...");            
  display.displayOff();
  ESP.deepSleep(sec*1000*1000, WAKE_RF_DEFAULT);
  delay(1000);
}

/* セットアップ */
void setup() {
  //シリアル初期化
  Serial.begin(115200);
  Serial.println();
  // LED初期化
  strip.Begin();
  // OLED初期化
  display.init();
  display.flipScreenVertically();
  display.displayOn();
  display.clear();
  // デジタルI/O初期化
  pinMode(IO0_PIN, INPUT);
  // ファイルシステム初期化
  SPIFFS.begin();
  setup_host_and_path(ssid, pass, host, path);
  // 1秒以内にMODEを切り替えることにする(IO0押下)
  delay(1000);
  
  // Macアドレスを文字列に
  byte mac[6];
  WiFi.macAddress(mac);
  macaddr = "";
  for (int i = 0; i < 6; i++) {
    macaddr += String(mac[i], HEX);
  }
  
  if (digitalRead(IO0_PIN) == 0) {
    // サーバモード初期化
    setup_server();
  } else {
    // クライアントモード初期化
    setup_client();
  }
}

/* メインループ */
void loop() {
  char s[20];
  if (server_mode) {
    server.handleClient();
    if (iv1.check()) {
      count++;
      display.clear();
      display.setFont(ArialMT_Plain_16);
      display.setTextAlignment(TEXT_ALIGN_LEFT);      
      if ((count % 2) == 0) {
        display.drawString(20, 16, "*AP Config*");
      } else {
        display.drawString(20, 16, "192.168.4.1");        
      }
      display.drawString(12, 35, macaddr);
      display.setFont(ArialMT_Plain_10);
      display.drawString(4, 50, "<<PASS>>"+default_pass);
      display.display();
    }
  } else {
    ArduinoOTA.handle();
    if (iv1.check()) {
      count++;
      time_t t = now();
      t = localtime(t, 9);
      display.clear();
      sprintf(s, "%02d:%02d", hour(t), minute(t));
      display.setFont(ArialMT_Plain_10);
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.drawString(99, 54, s);
            
      if (rlen >= 8) {
        errdispcount = 0;
         
        tickermax = (rlen - 4) / 4;
        tickerptr++;
        if (tickerptr >= tickermax) {
          tickerptr = 0;
          if (pmode == 1) {
            power_down(3600);            
          }
        }     
        display.setFont(ArialMT_Plain_10);
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawString(0, 54, "L:"+result[2]);
        display.drawXbm(28, 54, celsius_width, celsius_height, (const char*)celsius_bits);          
        display.drawString(45, 54, "H:"+result[3]);
        display.drawXbm(72, 54, celsius_width, celsius_height, (const char*)celsius_bits);          

        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.setFont(ArialMT_Plain_16);
        if (display.getStringWidth(result[1]) <= 68) {
          display.drawString(0, 8, result[1]);
        } else {
          display.drawString(0, -4, result[1].substring(0, 6));
          display.drawString(16, 12, result[1].substring(6));
        }

        display.setFont(ArialMT_Plain_10);
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawString(8, 27, result[5+tickerptr*4]);
        display.drawString(8, 40, result[6+tickerptr*4]);
        String main_stat = result[7+tickerptr*4];
        if (main_stat.equals("Clear")) {
          display.drawXbm(72, -8, clear_width, clear_height, (const char*)clear_bits);          
        } else if (main_stat.equals("Rain")) {
          display.drawXbm(72, -8, rain_width, rain_height, (const char*)rain_bits);                    
        } else if (main_stat.equals("Clouds")) {
          display.drawXbm(72, -8, clouds_width, clouds_height, (const char*)clouds_bits);                              
        } else if (main_stat.equals("Snow")) {          
          display.drawXbm(72, -8, snow_width, snow_height, (const char*)snow_bits);                              
        }        
      } else {
        strip.SetPixelColor(0, red);
        strip.Show();  

        display.setFont(ArialMT_Plain_16);
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        errmes.trim();
        display.drawString(0, 16, errmes.substring(0, 6));
        display.drawString(16, 32, errmes.substring(6));
        errdispcount++;
        if (pmode == 1 && errdispcount >= 25) {
          power_down(3600);
        }
      }
      display.display();
    }
    if (iv2.check()) {
        //天気
        if (dmode == 1) {
          parse_csv_with_led(res_def);          
        } else if (wifi_connect(ssid, pass)) {
          String data = "q=" + loc + "&mac=" + macaddr;
          String res = http_post(host, path, data); 
          if (res.startsWith("ERROR")) {
            errmes = res;
            rlen = 0;
          } else {
            parse_csv_with_led(res);
          }
        }
    }
    if (iv3.check()) {
      //ボタン
      if (digitalRead(IO0_PIN) == 0) {
        pushcount++;
        if (pushcount >= 3) {
          pushcount = 0;
          strip.SetPixelColor(0, gray);
          strip.Show();
          display.clear();
          display.setTextAlignment(TEXT_ALIGN_LEFT);
          display.setFont(ArialMT_Plain_16);
          if (pmode == 0) {
            //パワーセーブ
            save_pmode(1);
            display.drawString(32, 48, "PwrSave");
          } else {
            //ティッカー
            save_pmode(0);
            display.drawString(32, 48, "Ticker");          
          }
          display.display();
          delay(2000);
          strip.SetPixelColor(0, black);
          strip.Show();
        }
      } else {
         pushcount = 0;        
      }
    }
    delay(waitms);
  }
  ESP.wdtFeed();
}
