//Librairies
//Arduino BB8

#include <SoftwareSerial.h> //Software Serial Port//Définition des paramètres pour la communication bluetooth.
#include <Servo.h> //Servo moteurs
#define RxD 7 //PIn Rx Recieve data
#define TxD 6 //PIn Tx Transmit data
#define PINLED_V 9 //define Led Verte PIN - Cette Led - Permet de voir le bon téléversement du programme et de vérifier que l'arduino est bien allumé

#define PINLED_R 13 //define Led Rouge PIN - Cette LED s'allume lorsque la communication Bluetooth est interrompu
#define LEDON() digitalWrite(PINLED, HIGH)
#define LEDOFF() digitalWrite(PINLED, LOW)
#define AVANCER 1
#define RECULER 2
#define GAUCHE 3
#define DROITE 4
#define TEST 1

void setupBlueToothConnection();
void clignoter_led(int PIN);
void motor_stop();
void commander_moteurs(int commande);
SoftwareSerial blueToothSerial(RxD,TxD);

//Useful Variables
char state='0';

int vSpeed=200; // vitesse
//int init_b=0; //Affichage bluetooth ON / OFF
int clignotant=0;

Servo motorAD;
Servo motorAG;
Servo motorG;
Servo motorD;

/*---------------------------------*/ /*Setup*/ /*---------------------------------------*/

void setup() {

// Set pins as outputs:

Serial.begin(9600); // Initialisation vitesse de communication à 9600 Bauds:

pinMode(RxD, INPUT); //Pin RX en entrée

pinMode(TxD, OUTPUT); //Pin TX en sortie

//sur cette version de code on utilise le chassis ou les robot fonctionne par paire:

// G

// ///////

// AG///////////AD

// //////

// D

motorAD.attach(5);

motorAG.attach(6);

motorG.attach(10);

motorD.attach(11);

pinMode(lights, OUTPUT);

pinMode(PINLED_V, OUTPUT);

pinMode(PINLED_R, OUTPUT);

setupBlueToothConnection(); //Appel de la fonction setupBlueToothConnection

Serial.println("Device ON / BlueTooth ON");

blueToothSerial.flush();

motor_stop();

clignoter_led(PINLED_V);

clignoter_led(PINLED_R);

}

/*---------------------------------*/ /*LooP*/ /*---------------------------------------*/

void loop(){

if( blueToothSerial.available() ){ ////Bluetooth connecté

digitalWrite(PINLED_R, LOW);

state = blueToothSerial.read(); //recoit une donnée / commande

Serial.println("Bluetooth Ready");

#if TEST

Serial.println("Bluetooth Ready");

Serial.print("state : "); //affichage commande / état

Serial.println( state );

#endif

switch (state){

case 'F' : commander_moteurs(AVANCER); break;

case 'L' : commander_moteurs(GAUCHE); break;

case 'R' : commander_moteurs(DROITE); break;

case 'B' : commander_moteurs(RECULER); break;

case 'S' :

motor_stop();

break;

default :

#if TEST

Serial.println("Erreur : ni F, L, R, B et S (commande inconnue)");

#endif

motor_stop();

break;

}

delayMicroseconds(90); //délais minimum entre chaque commande

}else{//Bluetooth déconnecté !blueToothSerial.available()

#if TEST

Serial.println("Connection LOST");

#endif

clignoter_led(PINLED_R); //Fonction bloquante de 5s

//motor_stop();

}

}

void setupBlueToothConnection()

{

blueToothSerial.begin(9600);

blueToothSerial.print("AT");

delay(400);

blueToothSerial.print("AT+DEFAULT");

delay(2000);

blueToothSerial.print("AT+NAME<__BB8__>");

delay(400);

blueToothSerial.print("AT+PIN0000");

delay(400);

blueToothSerial.print("AT+AUTH1");

delay(400);

blueToothSerial.flush();

}

void clignoter_led(int PIN){

//for( int led = 0; led < 10 ; led++){

if(clignotant==0){

digitalWrite(PIN, HIGH);

clignotant=1;

}else{

digitalWrite(PIN, LOW);

clignotant=0;

}

}

void motor_stop(){

motorAG.write(90); //STOP = moteur à 0 / 90° position neutre

motorAD.write(90);

motorG.write(90);

motorD.write(90);

delayMicroseconds(90); //délais minimum entre chaque commande

#if TEST

Serial.println("STOP -- STOP");

#endif

}

void commander_moteurs(int commande){

/*

* Position "90" (1.5ms pulse) is stop, ,

* "180" (2ms pulse) is full speed forward,

* "0" (1ms pulse) is full speed backwards.

*

*/

switch ( commande )

{

case AVANCER :

motorAG.write(180);

motorAD.write(0);

motorG.write(90);

motorD.write(90);

Serial.println("FORWARD");

delayMicroseconds(90); //delay entre chaque commande de servo moteur

//Dead band expand from 10 to 90μs

break;

case RECULER :

motorAG.write(0);

motorAD.write(180);

motorG.write(90); //STOP = moteur à 0

motorD.write(90); //STOP = moteur à 0

Serial.println("RIGHT");

delayMicroseconds(90); //delay entre chaque commande de servo moteur

//Dead band expand from 10 to 90μs

break;

case DROITE :

motorAG.write(90); //STOP = moteur à 0

motorAD.write(90);

//set 1.5ms Pulse : Stop (To solve the problem of getting a steady stop position set and drift)

motorG.write(0);

motorD.write(180);

Serial.println("RIGHT");

delayMicroseconds(90);

break;

case GAUCHE :

motorAG.write(90); //STOP = moteur à 0

motorAD.write(90);

motorG.write(180);

motorD.write(0);

Serial.println("LEFT");

delayMicroseconds(90);

break;

default:

Serial.println("- ERREUR COMMANDE -");

motor_stop();

break;

}

}
