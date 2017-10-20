#include <UIPEthernet.h>
#include <utility/logging.h>
#include <SPI.h>
#include <PubSubClient.h>
#include <Servo.h>

Servo myservo;
int pos;    // variable to store the servo position
int pos2;
const int LedLuz = 9;
// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x11 };
//IPAddress server(172, 16, 0, 2);
const char* mqtt_server = "m13.cloudmqtt.com";

void callback(char* topic, byte* payload, unsigned int length) {

  String topicStr = String(topic);
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
   if (topicStr == "Portao") {
    // Switch on the LED if an 1 was received as first character

    if (payload[0] == '1') {
     // digitalWrite(LedLuz, LOW);   // Turn the LED on (Note that LOW is the voltage level
      Serial.println("Abrir Portao");
      acionaPortao(1);
      // but actually the LED is on; this is because
      // it is acive low on the ESP-01)
    } else {
    //  digitalWrite(LedLuz, HIGH);  // Turn the LED off by making the voltage HIGH
      Serial.println("Fechar Portao");
      acionaPortao(2);
    }

  }
  else {
    // Se o topico nao for Portao ele vira primeiro pra cá mas nao deve fazer nada.. para direto e ver o próximo if abaixo.
    // Serial.println("Não funcionou");
    // client.loop();
  }
  

  if (topicStr == "Luz") {
    // Switch on the LED if an 1 was received as first character

    if (payload[0] == '0') {
      digitalWrite(LedLuz, LOW);   // Turn the LED on (Note that LOW is the voltage level
      Serial.println("Desligado");
      // but actually the LED is on; this is because
      // it is acive low on the ESP-01)
    } else {
      digitalWrite(LedLuz, HIGH);  // Turn the LED off by making the voltage HIGH
      Serial.println("Ligado");
    }

  }
  else {
    Serial.println("Não funcionou");
    // client.loop();

  }
}

EthernetClient ethClient;
PubSubClient client(mqtt_server, 19927, callback, ethClient);

void setup()
{
  Serial.begin(9600);
  myservo.attach(9);
  while (!Serial) {}
  
  pinMode(LedLuz, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  if(Ethernet.begin(mac)) {
    Serial.println(Ethernet.localIP());
  } else {
    Serial.println("Falha no DHCP");
  }

  if (client.connect("alsdkjflakj", "teste", "123")) {
    Serial.println("Cheguei aqui");
    Serial.flush();
    client.publish("Luz", "1111");
    client.subscribe("Luz");
    client.setCallback(callback);
  } else {
    Serial.println("Não Cheguei aqui");
  }
}

void loop()
{
  client.loop();
  if (Serial.available() > 0) {


    posicao = Serial.parseInt();
    acionaPortao(posicao);
    delay(200);

  }
}

void acionaPortao(int direcao) {
  // Abrir Portao : direcao = 1
  
  if (direcao == 1) {
    // pos = 120;
    for (pos = 0; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);
      delay(100);
      // waits Xms for the servo to reach the position
      Serial.println("Portao Abrindo");
      Serial.flush();
    }
    Serial.println("Portao Aberto");
  }
  // Fechar Portao : direcao = 2
  else if (direcao == 2)  {
    //pos = 60;
    for (pos2 = pos; pos2 >= 0; pos2--) { // goes from 180 degrees to 0 degrees
      // tell servo to go to position in variable 'pos'
      delay(100);
      myservo.write(pos2);  // waits 15ms for the servo to reach the position
      Serial.println("Portao Fechando");
      Serial.flush();
    }
    Serial.println("Portao Fechado");
  }
}
