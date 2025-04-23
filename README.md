# Leitor LDR arduino

Este projeto utiliza um Arduino, um sensor LDR, um display LCD, LEDs coloridos e um buzzer para monitorar a luminosidade de um ambiente e sinalizar três níveis de iluminação ideais para uma vinheria. O sistema exibe informações em tempo real no LCD e aciona LEDs (vermelho, amarelo e verde) e um buzzer conforme o nível de luz.

## Componentes

- **Arduino Uno (ou compatível)**
- **Sensor LDR** (Light Dependent Resistor)
- **Display LCD 16x2** com interface paralela e backlight
- **LEDs**: 1 verde, 1 amarelo, 1 vermelho
- **Buzzer** piezoelétrico
- **Resistores**: 5x 220 Ω (para LEDs e sensor)
- **Cabos jumper**
- **Protoboard**

## Diagrama de Ligação

| Componente       | Pino Arduino   |
|------------------|----------------|
| LDR              | A0             |
| LED Verde        | 12             |
| LED Amarelo      | 11             |
| LED Vermelho     | 10             |
| Buzzer           | 9              |
| LCD RS           | 7              |
| LCD Enable (E)   | 6              |
| LCD D4           | 5              |
| LCD D5           | 4              |
| LCD D6           | 3              |
| LCD D7           | 2              |
| LCD Backlight    | 1              |

> **Obs.** Conecte resistores de 220 Ω em série com cada LED e no sensor conforme necessário.

## Uso

1. Abra o sketch `leitor_ldr.ino` na IDE do Arduino.
2. Faça o upload para o Arduino.
3. Após o reset, o LCD exibirá uma animação de boas-vindas com o nome da vinheria.
4. O sistema começará a ler o LDR e indicará no LCD a porcentagem de luminosidade.
5. LEDs e buzzer:  
   - **Luz alta (>80%)**: LED vermelho aceso e alarme sonoro.  
   - **Em alerta (70–80%)**: LED amarelo aceso.  
   - **Penumbra ideal (<70%)**: LED verde aceso.

## Calibração

Os valores de mapeamento da LDR podem variar conforme o sensor e o ambiente:

```cpp
// Exemplo de calibração
int luz = analogRead(A0);
// Mapeia 511–1016 para 100–0%
int nivelLuz = map(luz, 511, 1016, 100, 0);
```

Ajuste `511` e `1016` para os valores mínimo e máximo obtidos em seu ambiente.
**Obs.** Lembre-se que, no caso desse leitor, valores MAIORES representam MENOR luminosidade.

## Estrutura do Código

- **setup()**: Configura pinos, inicializa LCD, cria caracteres personalizados e exibe tela de boas-vindas.
- **loop()**: Lê valor da LDR, calcula porcentagem de luminosidade, atualiza o LCD e aciona LEDs/buzzer conforme o nível.

## Simulação do Código
Simule esse projeto em https://wokwi.com/projects/428549570699854849
