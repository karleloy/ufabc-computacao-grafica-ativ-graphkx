# Atividade de Computação Gráfica - 2024.3

# Discentes
- Ana Carolina da Silva Martins
- Karl Eloy Henrique
- Francisco Yury Pinheiro

# Memória matemática

Este projeto implementa um jogo de memória na qual o jogador precisa encontrar pares de cartas que representam fórmulas matemáticas. As cartas contêm operações matemáticas como adição, subtração, multiplicação, etc. 

## Estrutura do Código

O código está estruturado em três funções principais:

1. **restartGame**: Reinicia o jogo, embaralhando as cartas e distribuindo-as aleatoriamente no tabuleiro.

2. **onCreate**: Carrega a fonte personalizada usada nas cartas e inicia o jogo.

3. **onPaintUI**: Desenha a interface gráfica do jogo usando a biblioteca ImGui, onde:
   - Exibe mensagens sobre o estado do jogo;
   - Renderiza o tabuleiro com as cartas;
   - Implementa as interações do jogador com as cartas e o botão de reiniciar o jogo.

4. **checkEndCondition**: Verifica se o jogador acertou um par de cartas ou se completou o jogo, determinando o estado final.

### Dependências

- `ImGui`: Usada para renderizar a interface gráfica do usuário.
- `fmt` e `gsl`: Bibliotecas para manipulação de strings e segurança em tipos.
- `window.hpp` e `card.hpp`: Definem as classes e métodos relacionados à janela e às cartas do jogo.

## Como gerar o WebAssembly

Para rodar o jogo no navegador usando WebAssembly, será necessário compilar o arquivo `.cpp` usando o [Emscripten SDK](https://emscripten.org/). Para isso, siga as instruções abaixo ou consulte a documentação da ferramenta.

### Passo 1: Instalar o Emscripten

1. Faça o download e instale o Emscripten SDK:
   ```bash
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   ./emsdk install latest
   ./emsdk activate latest
   source ./emsdk_env.sh  # Ativa o Emscripten no terminal atual
   ```

### Passo 2: Compilar o arquivo para WebAssembly

1. No terminal, navegue até o diretório onde está o arquivo `.cpp`.
2. Use o comando `emcc` para compilar:

   ```bash
   emcc window.cpp -o index.html -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_FREETYPE=1
   ```

   Este comando gerará três arquivos:
   - `index.html`: A página web que carrega o WebAssembly.
   - `index.js`: Arquivo JavaScript que facilita a integração com o `.wasm`.
   - `index.wasm`: O arquivo WebAssembly.

### Passo 3: Executar o código no navegador

1. Para executar o código WebAssembly localmente, execute o comando a seguir para iniciar um servidor local:
   ```bash
   emrun --no_browser --port 8080 .
   ```

2. Abra um navegador e acesse `http://localhost:8080/index.html` para ver o jogo em execução.
