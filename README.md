# openweather_clock

## 概要

ESP8366,3軸ジャイロセンサー,3軸加速度センサー,気象センサー,フルカラーLED,有機ELディスプレイを統合した
[7IMUduino](http://www.papa.to/kinowiki/index.php/Products/7IMUduino) の作例として、
OpenWetherMap(http://openweathermap.org/)から3時間予報をWiFi経由でとってきて表示する時計を作りました。

## フィーチャー

- サーバモードで、WebブラウザからWiFiのSSIDや予報の地域名を設定できます
- 有機ELディスプレイに、3時間予報を最大18時間まで見やすいアイコンで表示します
- 18時間以内の降水をフルカラーLEDを青色に点灯することで示します
- 起動してからIO0長押しでパワーセーブモードに入り、1時間に1回の間欠動作になります

## インストール

USBシリアル変換アダプター用のドライバは適切なものをインストールしておいてください。

ビルドには [Arduino IDE 1.6.9](https://www.arduino.cc/en/Main/Software) が必要です。

[ESP8266のボードデータ](https://github.com/esp8266/Arduino) を参照して、
Arduino IDEのボードマネージャに[Staging version](http://arduino.esp8266.com/staging/package_esp8266com_index.json) を設定します。

ビルドには以下のArduinoライブラリが必要です。

- https://github.com/Makuna/NeoPixelBus/tree/master
- https://github.com/squix78/esp8266-oled-ssd1306/tree/2.0.2
- https://github.com/PaulStoffregen/Time.git
- https://github.com/exabugs/sketchLibraryNTP

なお、ライブラリはデフォルトでは各ホームディレクトリのArduino/librariesディレクトリに置きます。

>+libraries  
>　　+NTP
>　　+NeoPixelBus-master
>　　+Time
>　　+esp8266-oled-ssd1306-2.0.2  

openweather_clock.inoをクリックするとArduino IDEが起動します。ボードタイプは以下のように設定してください。


- FlashMode: DIO
- FlashFreq: 40MHz
- CPUFreq: 80MHz
- FlashSize: 512K
- DebugPort: Disabled
- DebugLevel: None
- ResetMethod: ck
- UploadSpeed: 115200
- SerialPort: 適切なシリアルポート
- 書き込み装置: AVR ISP

7IMUduinoのIO0ボタンを押したまま、Arduino IDEの書き込みボタンを押せばビルドされて書き込まれるはずです。

## 動作確認

予め、PC等でOpenWetherMapの地図(http://openweathermap.org/weathermap)をみてローマ字の市町村名を確認しておいてください。
割と日本人の感覚と違っていて、例えば「Yokohama」だと北海道の横浜町が出たりするので、地図で確認することをお薦めします。

- 東京都: Tokyo
- 神奈川県横浜市: Yokohama-shi
- 山口県宇部市: Ube

次に、ボードにWiFi APのSSID,パスフレーズと上記で調べたローマ字地域名を書き込みます。
この設定はopenweather_clockのサーバモードに入ることで行います。

最終的なトポロジーは以下の通りですが...

 7IMUduino --無線-- ご家庭のWiFi AP --無線--- PC

サーバモードではボード自体がWiFi APになるので以下のような接続になります。

 7IMUduino(仮AP) --無線-- PC

サーバモードに入るには7IMUduinoのRSTボタンを押して0.5秒待ってIO0ボタンを押し続けてください。
LEDが強力に白色発光するので判別できるはずです。

このとき、PCの無線サービスに7IMUduinoのMACアドレスをSSIDとした仮APが現れるので接続してください。
パスフレーズは「esp8266pass」です。
PCのWebブラウザをひらき、 http://192.168.4.1/ にアクセスすると各種設定ができます。
コンテンツ内のSendボタンを押して設定を書き込みます。「WiFi AP Accepted」と出れば書きこまれています。

RSTボタンで再起動し、ボードがクライアントモードで起動すると、1秒程度経ってLEDが白色点滅し始めます。
点滅2,3回で終了すればだいたい接続完了しています。10回以上点滅する場合はSSID等の設定を確認してください。

- WiFiに接続できない場合は有機ELに「Error」と表示しLEDは赤色点灯します
- 接続できた場合は3時間予報を最大18時間分(6枚)順繰りに表示します
- 有機ELに「Invalid query」と出た場合はサーバの問題かもしれないので1時間くらい待ってみてください
- 18時間のうち雨の降る予報が含まれていたらLEDは水色点灯します
- 全て晴れならLEDは点灯しません
