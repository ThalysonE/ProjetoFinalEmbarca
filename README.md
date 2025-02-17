Controle de Matriz de LEDs com Raspberry Pi Pico

Descrição

Este projeto implementa o controle de uma matriz de LEDs WS2812B (NeoPixel) utilizando o Raspberry Pi Pico. O código exibe padrões de luz na matriz e permite ajustes interativos através de botões físicos.

Funcionalidades

Exibição de padrões na matriz de LEDs

Padrão pré-definido: Coração ❤️

Controle de brilho

Aumenta o brilho ao pressionar o botão A

Diminui o brilho ao pressionar o botão B

Gerenciamento de botões físicos

Detecta a interação do usuário

Lógica de controle otimizada

Atualiza os LEDs conforme a entrada do usuário

Hardware Necessário

Raspberry Pi Pico

Matriz de LEDs WS2812B (NeoPixel)

Botões físicos (mínimo 2)

Fonte de alimentação compatível

Como Compilar e Executar

1. Configurar o ambiente

Certifique-se de que o SDK do Raspberry Pi Pico está instalado e configurado corretamente.

2. Compilar o código

mkdir build
cd build
cmake ..
make -j$(nproc)

Isso gerará um arquivo .uf2 dentro da pasta build.

3. Carregar no Raspberry Pi Pico

Conecte o Raspberry Pi Pico ao PC segurando o botão BOOTSEL

O Pico aparecerá como um dispositivo de armazenamento USB

Arraste e solte o arquivo .uf2 gerado para dentro do dispositivo

O código será carregado e iniciará automaticamente

Estrutura do Código

main.c: Código principal contendo:

Inicialização dos LEDs

Controle de botões

Exibição dos padrões

Funções principais:

displayPatterns(): Exibe padrões na matriz

handleButtonPress(): Gerencia os botões físicos

setBrightness(): Ajusta o brilho dos LEDs

Autor

Este projeto foi desenvolvido para facilitar o uso do Raspberry Pi Pico em aplicações interativas com LEDs e botões. Sinta-se à vontade para contribuir!
