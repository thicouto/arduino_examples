//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//  Arquivo:   card_nano_serial
//  Autor:     Thiago Couto
//  Descricao: Leitura de cartao RFID e envio pela serial RX | TX.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

#define SCK  (13)
#define MOSI (11)
#define SS   (10)
#define MISO (12)

char        st[20];
const char  nl = '\n';
char        Buffer[256];
const int   buzzer = 7;
String      program_arduino  = "";

Adafruit_PN532 nfc(SCK, MISO, MOSI, SS);

void setup(void) {
  Serial.begin(9600);
  while (!Serial) delay(10);

  pinMode(buzzer,OUTPUT);

  while (program_arduino  == "") {
    
    int ByteCount = Serial.readBytesUntil(nl,Buffer,sizeof(Buffer));
    program_arduino = String(Buffer);
    memset(Buffer,0,sizeof(Buffer));

    if (program_arduino == "OK") {
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      delay(50);
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      delay(50);
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      delay(50);
    }
  }

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    while (1);
  }
  nfc.SAMConfig();
}

void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  if (success) {
    nfc.PrintHex(uid, uidLength);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(50);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(50);
    delay(3000);
  }
}
