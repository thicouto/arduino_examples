//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//  Arquivo:   card_nano_serial
//  Autor:     Thiago Couto
//  Descricao: Leitura de cartao RFID e envio pela serial RX | TX.

//  O leitor RFID tem 8 pinos que seguem a seguinte sequência de ligação. Atenção à tensão de alimentação, que neste caso é de 3.3 volts
//  Pino SDA ligado na porta 10 do Arduino
//  Pino SCK ligado na porta 13 do Arduino
//  Pino MOSI ligado na porta 11 do Arduino
//  Pino MISO ligado na porta 12 do Arduino
//  Pino NC – Não conectado
//  Pino GND  ligado no pino GND do Arduino
//  Pino RST ligado na porta 9 do Arduinoq
//  Pino 3.3 – ligado ao pino 3.3 V do Arduino

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int         baud_rate = 9600;
char        st[20];
const char  nl = '\n';
char        Buffer[256];
const int   buzzer = 7;
String      program_arduino  = "";

void setup() 
{

  Serial.begin(baud_rate);
  
  while (!Serial) {
    ;                   // Aguarda a serial
  }
  
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
  
  SPI.begin();          // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522

}
 
void loop() 
{
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  conteudo.toUpperCase();

  Serial.println(conteudo);

  digitalWrite(buzzer, HIGH);
  delay(50);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(50);
  digitalWrite(buzzer, LOW);
  delay(50);

  delay(2000);
  
}
