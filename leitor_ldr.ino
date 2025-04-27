//Biblioteca LCD
#include <LiquidCrystal.h>

// Inicializa o display LCD: (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Declara as portas do Arduino
int Lerluz = A0;
int LuzVerde = 12;
int LuzAmarela = 11;
int LuzVermelha = 10;
int buzzer = 9;

// Criando caracteres personalizados para o LCD
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
  
// Configurando LCD para mensagens
  lcd.createChar(3, garrafa); // Armazena o caractere da garrafa no índice 3
  lcd.createChar(4, taca); // Armazena o caractere da taça no índice 4
  lcd.begin(16, 2); // Define o LCD como 16 colunas e 2 linhas

// Tela de boas-vindas animada
  for (int i = 0; i < 6; i++) {
    lcd.print("    Vinheria"); // Exibe texto centralizado
    lcd.setCursor(0,2); // Move para a segunda linha
    lcd.print("    Agnello \x03\x04"); // Exibe Nome da vinheria juntamente dos caracteres personalizados de garrafa e taça
    delay(500);
    lcd.clear(); // Limpa display
    delay(500);
  }
  lcd.print("Seja bem-vindo!"); // Mensagem final de boas-vindas
  delay(2000);
  lcd.clear();
}

void loop() {
  int luz = analogRead(Lerluz);  //Leitura do valor analógico da LDR
  // Mapeia o valor bruto em porcentagem de Luminosidade: 
  // luz = 511 -> 100% iluminado (0% escuridão) Valor relativo a 100 lux (luminosidade de um quarto)
  // luz = 1016 -> 0% iluminado (100% escuridão).
  int nivelLuz = map(luz, 511, 1016, 100, 0);
    // luminosidade de 60 a 100 lux = ambiente bem iluminado
    // luminosidade entre 40 e 60 lux
    // luminosidade menor que 40 lux = ambiente com penumbra ideal para os vinhos
  // Exibe no LCD o nível de luz.
  lcd.setCursor(0,0);
  lcd.print("Luz:");
  lcd.print(nivelLuz);
  lcd.println("%");
  lcd.setCursor(0,1); // Segunda linha do display.

  // Condicional para diferentes níveis de iluminação.
  if (nivelLuz >= 80){ 
    // Ambiente muito iluminado (>80%) -> LED vermelho e buzzer (Acima de 55 Lux) .
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
    // Alerta (70-80% iluminação) -> LED amarelo (Entre 42 e 55).
    digitalWrite (LuzVerde, LOW);
    digitalWrite (LuzAmarela, HIGH);
    digitalWrite (LuzVermelha, LOW);
    lcd.print("Em Alerta");
    delay(3000);
  }
  if (nivelLuz < 70){ 
    // Penumbra ideal (<70% iluminação) -> LED verde (Abaixo de 42 lux) 
    digitalWrite (LuzVerde, HIGH);
    digitalWrite (LuzAmarela, LOW);
    digitalWrite (LuzVermelha, LOW);
    lcd.print("Penumbra ideal");
    delay(3000);
  }
  delay(2000); // Pausa antes da próxima leitura
  lcd.clear(); // Limpa display para atualização
}
// 3 leds coloridos: verde,amarelo e vermelho.
// 1 LDR, 1 Buzzer, 5 Resitores de 220, 1 LCD
