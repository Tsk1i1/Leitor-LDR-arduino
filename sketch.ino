//Biblioteca LCD
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2, 1);

// Declarando nomes para as portas do arduino.
int Lerluz = A0;
int LuzVerde = 12;
int LuzAmarela = 11;
int LuzVermelha = 10;
int buzzer = 9;

// Criando caracteres diferentes para o LCD
byte garrafa[8] = {
  B00100,
  B00100,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
};
byte taca[8] = {
  B00000,
  B00000,
  B10100,
  B10100,
  B11100,
  B01000,
  B11100,
};


void setup() {
// Declarando saídas e entradas do arduino.
  pinMode(Lerluz, INPUT);
  pinMode(LuzVerde, OUTPUT);
  pinMode(LuzAmarela, OUTPUT);
  pinMode(LuzVermelha, OUTPUT);
  pinMode(buzzer, OUTPUT);
// Preparando LCD para mensagens
  lcd.createChar(3, garrafa);
  lcd.createChar(4, taca);
  lcd.begin(16, 2);
  for (int i = 0; i < 6; i++) {
    lcd.print("    Vinheria");
    lcd.setCursor(0,2);
    lcd.print("    Agnello \x03\x04");
    delay(500);
    lcd.clear();
    delay(500);
  }
  lcd.print("Seja bem-vindo!");
  delay(2000);
  lcd.clear();
}

void loop() {
  int luz = analogRead(Lerluz); // Obter leitura da luminosidade do ambiente.
  int nivelLuz = map(luz, 511, 1016, 100, 0);
    // Valores relativos: 1016 = 0% escuridao total e 511 = 100% = ambiente iluminado.
    // luminosidade de 60 a 100 lux = ambiente bem iluminado
    // luminosidade entre 40 e 60 lux
    // luminosidade menor que 40 lux = ambiente com penumbra ideal para os vinhos
  lcd.setCursor(0,0);
  lcd.print("Luz:");
  lcd.print(nivelLuz);
  lcd.println("%");
  lcd.setCursor(0,2);

  if (nivelLuz >= 80){ 
    // Acima de 55 Lux ligar o led vermelho e alarme.
    digitalWrite (LuzVerde, LOW);
    digitalWrite (LuzAmarela, LOW);
    digitalWrite (LuzVermelha, HIGH);
    digitalWrite (buzzer, HIGH);
    lcd.print("Luz alta!");
    delay(3000);
    digitalWrite (LuzVermelha, LOW);
    digitalWrite (buzzer, LOW);
  }
  if (nivelLuz >= 70 && nivelLuz < 80) {
    // Em alerta. Entre 42 e 55 Lux ligar a luz amarela.
    digitalWrite (LuzVerde, LOW);
    digitalWrite (LuzAmarela, HIGH);
    digitalWrite (LuzVermelha, LOW);
    lcd.print("Em Alerta");
    delay(3000);
  }
  if (nivelLuz < 70){ 
    // Em penumbra ideal. Abaixo de 42 lux ligar a luz verde.
    digitalWrite (LuzVerde, HIGH);
    digitalWrite (LuzAmarela, LOW);
    digitalWrite (LuzVermelha, LOW);
    lcd.print("Penumbra ideal");
    delay(3000);
  }
  delay(2000);
  lcd.clear();
}
// 3 leds coloridos: verde,amarelo e vermelho.
// 1 LDR, 1 Buzzer, 5 Resitores de 220, 1 LCD