# Controle de Matriz de LEDs com Raspberry Pi Pico

## Descrição

Este projeto implementa o controle de uma matriz de LEDs WS2812B (NeoPixel) utilizando o Raspberry Pi Pico. O código exibe padrões de luz na matriz e permite ajustes interativos através de botões físicos.

## Funcionalidades

- **Exibição de padrões na matriz de LEDs**
  - Padrão pré-definido: Coração ❤️

- **Controle de brilho**
  - Aumenta o brilho ao pressionar o botão A
  - Diminui o brilho ao pressionar o botão B

- **Gerenciamento de botões físicos**
  - Detecta a interação do usuário

- **Lógica de controle otimizada**
  - Atualiza os LEDs conforme a entrada do usuário

## Hardware Necessário

- Raspberry Pi Pico
- Matriz de LEDs WS2812B (NeoPixel)
- Botões físicos (mínimo 2)
- Fonte de alimentação compatível

## Estrutura do Código

- `main.c`: Código principal contendo:
  - Inicialização dos LEDs
  - Controle de botões
  - Exibição dos padrões

### Funções principais:

- `displayPatterns()`: Exibe padrões na matriz
- `handleButtonPress()`: Gerencia os botões físicos
- `setBrightness()`: Ajusta o brilho dos LEDs
