//Por Rafael Pontes

#include <WiFi.h>

//Definição dos pinos de controle do motor
#define M1 13 // Pino_Velocidade 1º Motor ( 0 a 255)_ Porta ATV_A ponte H;
#define M2 27 //Pino_Velocidade 2º Motor ( 0 a 255) _ Porta ATV_B ponte H;
#define dir1 14 //Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
#define dir2 26 //Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;
#define ledAzul 25
const int reD = 0;
const int frenteD = 1;
const int reE = 2;
const int frenteE = 3; 

const char* ssid     = "wifiName";
const char* password = "password";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);

    pinMode(ledAzul,OUTPUT);
    digitalWrite(ledAzul,LOW);
    
    ledcAttachPin(M1,reD);
    ledcSetup(reD,4000,8);
    ledcAttachPin(dir1,frenteD);
    ledcSetup(frenteD,4000,8);
    ledcAttachPin(M2,reE);
    ledcSetup(reE,4000,8);
    ledcAttachPin(dir2,frenteE);
    ledcSetup(frenteE,4000,8); 

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(ledAzul,HIGH);
        delay(250);
        Serial.print(".");
        digitalWrite(ledAzul,LOW);
        delay(250);
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(ledAzul,HIGH);
    server.begin();

}

int value = 0;
int vel_max = 255;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        digitalWrite(ledAzul,HIGH);
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // Criando uma página HTML para servir de controle remoto :
            client.print("<div style=\"text-align:center;margin-top:100px;padding:20px;font-size:120px;text-decoration:none;text-align:center\">");
            client.print("<p><a href=\"/F\" style=\"border:1px solid black;padding: 20px;background-color:greenyellow;border-radius: 30px;text-decoration:none;text-align:center;color:white \"> ^ </a> </p>");
            client.print("<p style=\" padding: 70px\"><a href=\"/E\" style=\" padding:20px; border:1px solid black;background-color:greenyellow;border-radius: 30px;text-decoration:none;text-align:center;color:white \"> <</a> <a href=\"/P\" style=\"padding:20px; margin: 120px;border:1px solid black;background-color:greenyellow;border-radius: 30px;text-decoration:none;text-align:center;color:white;padding:10px \">O</a> <a href=\"/D\" style=\"padding:20px; border:1px solid black;background-color:greenyellow;border-radius: 30px;text-decoration:none;text-align:center;color:white\"> > </a></p>");
            client.print("<p><a href=\"/T\"style=\"padding:20px; border:1px solid black;background-color:greenyellow;border-radius: 30px;text-decoration:none;text-align:center;color:white \"> v </a> </p>");      
             client.print("</div>");
            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /F","GET /D","GET /E","GET /P" or "GET /T":
        if (currentLine.endsWith("GET /F")) {
          ledcWrite(reD,0);
          ledcWrite(frenteD,vel_max);
          ledcWrite(reE,0);
          ledcWrite(frenteE,vel_max);          
        }
        if (currentLine.endsWith("GET /T")) {
          ledcWrite(reD,vel_max);
          ledcWrite(frenteD,0);
          ledcWrite(reE,vel_max);
          ledcWrite(frenteE,0);                
        }
        if (currentLine.endsWith("GET /D")){
          ledcWrite(reD,vel_max);
          ledcWrite(frenteD,0);
          ledcWrite(reE,0);
          ledcWrite(frenteE,vel_max); 
          delay(400);
          ledcWrite(reD,0);
          ledcWrite(frenteD,0);
          ledcWrite(reE,0);
          ledcWrite(frenteE,0);
          }
        if (currentLine.endsWith("GET /E")){
          ledcWrite(reD,0);
          ledcWrite(frenteD,vel_max);
          ledcWrite(reE,vel_max);
          ledcWrite(frenteE,0); 
          delay(400);
          ledcWrite(reD,0);
          ledcWrite(frenteD,0);
          ledcWrite(reE,0);
          ledcWrite(frenteE,0);
          }
        if (currentLine.endsWith("GET /P")) {
          ledcWrite(reD,0);
          ledcWrite(frenteD,0);
          ledcWrite(reE,0);
          ledcWrite(frenteE,0);          
        }

      }
    }
  }
}
