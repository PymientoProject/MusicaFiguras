/*
  Código para saber que identificador NFC hay en cada posicion de forma continua
 */

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 6    
#define RST_PIN 9    //

#define SS_PIN2 7
#define RST_PIN2 10  //

#define SS_PIN3 5
#define RST_PIN3 8

#define SS_PIN4 4
#define RST_PIN4 3  //

#define SS_PIN5 A0
#define RST_PIN5 A1

#define SS_PIN6 A2    //
#define RST_PIN6 A3
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522 rfid2(SS_PIN2, RST_PIN2); // Instance of the class
MFRC522 rfid3(SS_PIN3, RST_PIN3); // Instance of the class
MFRC522 rfid4(SS_PIN4, RST_PIN4); // Instance of the class
MFRC522 rfid5(SS_PIN5, RST_PIN5); // Instance of the class
MFRC522 rfid6(SS_PIN6, RST_PIN6); // Instance of the class


MFRC522::MIFARE_Key key; 
MFRC522::PICC_Type piccType;

// Init array that will store new NUID 
byte nuidPICC[3];







/*
byte a[4] = {131, 43, 239, 117};
byte b[4] = {229, 211, 125, 99};
byte c[4] = {22, 77, 173, 88};
byte d[4] = {181, 54, 120, 99};
byte e[4] = {229, 79, 145, 100};
*/
/*
byte a[4] = {69, 42, 174, 107};
byte b[4] = {05, 193, 44, 119};
byte c[4] = {53, 07, 04, 109};
byte d[4] = {213, 22, 34, 119};
byte e[4] = {101, 137, 38, 119};
byte f[4] = {21, 248, 64, 119};
*/

byte a[4] = {04, 174, 76, 114};
byte b[4] = {04, 47, 101, 114};
byte c[4] = {04, 237, 101, 114};
byte d[4] = {04, 232, 101, 114};
byte e[4] = {04, 242, 76, 114};
byte f[4] = {04, 231, 101, 114};
byte g[4] = {04, 193, 101, 114};
byte h[4] = {04, 33, 76, 114};
byte j[4] = {04, 248, 76, 114};
byte k[4] = {04, 32, 76, 114};



int currentId;
int currentId2;
int currentId3;
int currentId4;
int currentId5;
int currentId6;

int lastId;
int lastId2;
int lastId3;
int lastId4;
int lastId5;
int lastId6;

void setup() { 

  delay(5000);
  
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}
 
void loop() {
  currentId = readModule(rfid);
  if(currentId != lastId){
    Serial.println("0" + String(currentId));
  }
  
  currentId2 = readModule(rfid2);
  if(currentId2 != lastId2){
    Serial.println("1" + String(currentId2));
  }

  currentId3 = readModule(rfid3);
  if(currentId3 != lastId3){
    Serial.println("2" + String(currentId3));
  }

  currentId4 = readModule(rfid4);
  if(currentId4 != lastId4){
    Serial.println("3" + String(currentId4));
  }

  currentId5 = readModule(rfid5);
  if(currentId5 != lastId5){
    Serial.println("4" + String(currentId5));
  }
  
  currentId6 = readModule(rfid6);
  if(currentId6 != lastId6){
    Serial.println("5" + String(currentId6));
  }
  
  lastId = currentId;
  lastId2 = currentId2;
  lastId3 = currentId3;
  lastId4 = currentId4;
  lastId5 = currentId5;
  lastId6 = currentId6;

  delay(10);
}

int readModule(MFRC522 module){
  module.PCD_Init(); // Init MFRC522
 
  // Look for new cards
  if (!module.PICC_IsNewCardPresent()){
    // Halt PICC
    module.PICC_HaltA();

    // Stop encryption on PCD
    module.PCD_StopCrypto1();
    return 0;
  }

   // Verify if the NUID has been readed
  if (!module.PICC_ReadCardSerial()){
    // Halt PICC
    module.PICC_HaltA();

    // Stop encryption on PCD
    module.PCD_StopCrypto1();
    return 0;
  }
    
  piccType = module.PICC_GetType(rfid.uid.sak);
   
  if(a[0] == module.uid.uidByte[0] &&
    a[1] == module.uid.uidByte[1] &&
    a[2] == module.uid.uidByte[2] &&
    a[3] == module.uid.uidByte[3]){
    // Halt PICC
    module.PICC_HaltA();

    // Stop encryption on PCD
    module.PCD_StopCrypto1();

    return 1;
  }

  if(b[0] == module.uid.uidByte[0] &&
    b[1] == module.uid.uidByte[1] &&
    b[2] == module.uid.uidByte[2] &&
    b[3] == module.uid.uidByte[3]){

    // Halt PICC
    module.PICC_HaltA();

    // Stop encryption on PCD
    module.PCD_StopCrypto1();

    return 2;
    
  }

  if(c[0] == module.uid.uidByte[0] &&
    c[1] == module.uid.uidByte[1] &&
    c[2] == module.uid.uidByte[2] &&
    c[3] == module.uid.uidByte[3]){

    // Halt PICC
    module.PICC_HaltA();

    // Stop encryption on PCD
    module.PCD_StopCrypto1();

    return 3;
    
  }

  if(d[0] == module.uid.uidByte[0] &&
    d[1] == module.uid.uidByte[1] &&
    d[2] == module.uid.uidByte[2] &&
    d[3] == module.uid.uidByte[3]){

    // Halt PICC
    module.PICC_HaltA();

    // Stop encryption on PCD
    module.PCD_StopCrypto1();

    return 4;
    
  }

  if(e[0] == module.uid.uidByte[0] &&
    e[1] == module.uid.uidByte[1] &&
    e[2] == module.uid.uidByte[2] &&
    e[3] == module.uid.uidByte[3]){

    // Halt PICC
    module.PICC_HaltA();

    // Stop encryption on PCD
    module.PCD_StopCrypto1();

    return 5;
    
  }

  if(f[0] == module.uid.uidByte[0] &&
    f[1] == module.uid.uidByte[1] &&
    f[2] == module.uid.uidByte[2] &&
    f[3] == module.uid.uidByte[3]){

    // Halt PICC
    module.PICC_HaltA();

    // Stop encryption on PCD
    module.PCD_StopCrypto1();

    return 6;
    
  }
  
  if(g[0] == module.uid.uidByte[0] &&
    g[1] == module.uid.uidByte[1] &&
    g[2] == module.uid.uidByte[2] &&
    g[3] == module.uid.uidByte[3]){

    // Halt PICC
    module.PICC_HaltA();

    // Stop encryption on PCD
    module.PCD_StopCrypto1();

    return 7;
    
  }
  
  if(h[0] == module.uid.uidByte[0] &&
    h[1] == module.uid.uidByte[1] &&
    h[2] == module.uid.uidByte[2] &&
    h[3] == module.uid.uidByte[3]){

    // Halt PICC
    module.PICC_HaltA();

    // Stop encryption on PCD
    module.PCD_StopCrypto1();

    return 8;
    
  }

    
  // Halt PICC
  module.PICC_HaltA();

  // Stop encryption on PCD
  module.PCD_StopCrypto1();
}
