#ifdef  ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <stdio.h>
#include <stdlib.h>

char str[] = "";
String message ="";
float temperature, humidity;
int gas;
const char* ssid     = "C206 2.4 Ghz";
const char* password = "Spkt2022";
const char* serverName = "https://vinhcaodatabase.com/thuctapnhung/post-esp-data.php";


String apiKeyValue = "nhom3ttnhung";
String sensorName = "DHT11 - MQ2";
String sensorLocation = "DHSPKT";
float nhietdo, doam;
int khigas;
void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Ket noi Wifi Thanh Cong!!!");
  Serial.print("IP:");
  Serial.println(WiFi.localIP());

  while(!Serial){}
}

void loop() {
    if(Serial.available()>0){
          message = Serial.readStringUntil('\n');
          Serial.println(message);
            message.toCharArray(str, 20);
        // char str[] = "t34.0h46.0g0";


        // Tách chuỗi
        float temperature = strtof(str + 1, NULL);
        float humidity = strtof(strchr(str, 'h') + 1, NULL);
        int gas = strtof(strchr(str, 'g') + 1, NULL);

        nhietdo = temperature;
        doam = humidity;
        khigas = gas;
        // In kết quả
        Serial.printf("Temperature: %.1f\n", temperature);
        Serial.printf("Humidity: %.1f\n", humidity);
        Serial.printf("Gas: %d\n", gas);
  //Check WiFi connection status
      if(WiFi.status()== WL_CONNECTED){
        WiFiClientSecure *client = new WiFiClientSecure;
        client->setInsecure(); //don't use SSL certificate
        HTTPClient https;
      
    
        https.begin(*client, serverName);


        https.addHeader("Content-Type", "application/x-www-form-urlencoded");
      
        String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                            + "&location=" + sensorLocation + "&value1=" + nhietdo
                            + "&value2=" + doam + "&value3=" + khigas + "";
        Serial.print("httpRequestData: ");
        Serial.println(httpRequestData);
      

      // Send HTTP POST request
      int httpResponseCode = https.POST(httpRequestData);
      
      
        if (httpResponseCode>0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
        }
        else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
        }

      https.end();
    }
    else {
      Serial.println("Mat ket noi WIFI");
    }
  }
  delay(500);  
}

