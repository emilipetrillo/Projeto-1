
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int pos2;
const int pinLed = 8;
const int btn = 2;
int pressionadoAnterior;
int ligado;
int btnState;



void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.println("Iniciando");
  pinMode(pinLed, OUTPUT);
  pinMode(btn, INPUT);
}

void loop() {
  btnState = digitalRead(btn);
  if(btnState == 1){
    Led();
    //ligarLampada(btnState);
    abrir();
  } 
}


void Led() {
  //int btnState = digitalRead(btn);
  Serial.print("btnStatus: ");
  Serial.println(btnState);
  if (btnState && (pressionadoAnterior == LOW)) {
    ligado = 1 - ligado;
    ligarLampada(ligado);
  }
  Serial.print("btnStatus: ");
  Serial.println(btnState);
  pressionadoAnterior = btnState;
}

void ligarLampada(int sim) {
  digitalWrite(pinLed, sim);
  Serial.print("ligarLampada: ");
  Serial.println(sim);
  // reportar o estado do led via MQTT
}

void abrirPortao(int sim) {
  Serial.println("Abrindo portão e sim = 1");
  abrir();

}
// abre o portao via servo
//abrir();
// enviar mensagem mqtt


void abrir() {
  Serial.println("Abrindo portão");
  delay(1000);
    for (pos = 0; pos <= 180; pos++) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      //Serial.println(pos);
      delay(50);                       // waits 15ms for the servo to reach the position
    }
    Serial.println("Portão aberto");
    Led();
}

void fechar() {
  Serial.println("Fechando...");
  Serial.println(pos);
  for (pos2 = pos; pos2 >= 0; pos2--) {
    myservo.write(pos2);              // tell servo to go to position in variable 'pos'
    delay(50);
  }
  Serial.println(pos2);
}



