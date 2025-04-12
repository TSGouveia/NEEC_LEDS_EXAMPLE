#include <FastLED.h>    // Core FastLED library
#include <LEDMatrix.h>  // Matrix layout helper (optional but helpful)

// --- Configurações da Matriz (VERIFIQUE AS SUAS CONFIGURAÇÕES!) ---
#define LED_PIN        10         // Pino de dados onde a matriz está conectada
#define COLOR_ORDER    RGB        // Ordem das cores (RGB, GRB, BRG etc.) - VERIFIQUE A SUA MATRIZ!
#define CHIPSET        WS2812B    // Tipo de LED (WS2811, WS2812B, APA102 etc.)

#define MATRIX_WIDTH   32         // Largura da sua matriz em pixels
#define MATRIX_HEIGHT  18         // Altura da sua matriz em pixels
#define NUM_PIXELS     (MATRIX_WIDTH * MATRIX_HEIGHT) // Total de LEDs (576)

// Tipo de layout da matriz - VERIFIQUE SE ESTÁ CORRETO PARA A SUA FIAÇÃO!
#define MATRIX_TYPE    HORIZONTAL_ZIGZAG_MATRIX

// --- Configurações de Exibição ---
#define BRIGHTNESS     96 // Brilho (0-255) - Ajuste conforme necessário

// --- Objeto da Matriz ---
// Usa o cLEDMatrix para mapear coordenadas (x,y) para o índice linear do LED.
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

void setup() {
  delay(1000); // Pequena pausa para estabilização na inicialização

  // Inicializa FastLED
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], NUM_PIXELS); // Use leds[0] com cLEDMatrix
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(true); // Começa com a matriz apagada (preto)

  // --- Desenha as Colunas Estáticas de Arco-Íris ---
  // Este loop calcula e define a cor para cada pixel UMA VEZ.
  for (int x = 0; x < MATRIX_WIDTH; x++) {
    // Calcula a Matiz (Hue) com base APENAS na posição da coluna (x)
    // Mapeia x (0 a MATRIX_WIDTH-1) para hue (0 a 255)
    // (x * 255) / MATRIX_WIDTH distribui as cores pelo espectro
    uint8_t hue = (x * 255) / MATRIX_WIDTH;

    // Define a cor para esta coluna usando CHSV (Hue, Saturation, Value)
    // Saturação e Valor (Brilho) no máximo para cores vivas
    CHSV columnColor = CHSV(hue, 255, 255);

    // Aplica esta mesma cor a TODOS os pixels nesta coluna (y)
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
      // Usa o objeto leds(x,y) para definir o pixel na coordenada correta,
      // independentemente da fiação (graças a MATRIX_TYPE e cLEDMatrix)
      leds(x, y) = columnColor;
    }
  }

  // Atualiza a matriz física UMA VEZ com a imagem estática que acabamos de criar
  FastLED.show();
}

void loop() {
  // NADA A FAZER NO LOOP!
  // A imagem é estática e foi definida no setup().
  // FastLED manterá os LEDs no estado definido pela última chamada a FastLED.show().
  // Um delay pode ser adicionado se você quiser que o microcontrolador
  // gaste menos ciclos, mas não é funcionalmente necessário.
  // delay(100);
}