# Atividade de Computação Gráfica - 2024.3

# Discentes
- Ana Carolina da Silva Martins
- Karl Eloy Henrique
- Francisco Yury Pinheiro Silva

# Memória matemática

Este projeto implementa um jogo de memória na qual o jogador precisa encontrar pares de cartas que representam fórmulas matemáticas. As cartas contêm operações matemáticas como adição, subtração, multiplicação, etc. 

## Vídeo de demonstração

Para ver o jogo funcionando, [clique aqui](https://youtu.be/nyBvsQ9mdGU).

## Arquivos
Consulte a pasta "codigo_fonte" deste repositório para obter os arquivos do projeto.
O programa é baseado nos seguintes arquivos:

card.cpp
card.hpp
main.cpp
window.cpp
window.hpp
Inconsolata-Medium.ttf --Arquivo de fonte de texto

card.cpp e card.hpp
Os arquivos card são responsáveis pela criação do objeto carta, que é preenchido com valores de string, com finalidade de serem comparados futuramente no funcionamento do jogo.
Possuem também as funções de retorno do status da carta (virada ou não), assim como o valor armazenado e também a função flip() que faz com que a carta mude seu estado (Virada para não virada, não virada para virada).

window.hpp e window.cpp
São os arquivos que possuem as maiores configurações, principalmente em relação ao funcionamento do programa. 

Window.hpp possui a criação das matrizes usadas para o tabuleiro. Obrigatoriamente deve ser utilizadas matrizes de tamanhos tais que o quadrado deste tamanho seja um valor par. A ideia por trás disso é fazer, por exemplo, uma matriz 4x4, com total de 16 posições distintas, onde são preenchidas com pares de cartas. Se, por exemplo, alterassemos o tamanho do tabuleiro para um tabuleiro do tipo 5x5, teríamos 25 posições, o que vai contra a ideia de pares de cartas.

Window.cpp possui o dicionário com os valores que foram utilizados para a criação dos pares de cartas, com as respectivas equações matemáticas. Após isso, é feita a população dos pares de cartas com valores distintos do dicionário. Com isso, embaralhamos as cartas e posicionamos estas no tabuleiro. O funcionamento do jogo se dá, enfim, como um jogo da memória comum. Ao selecionar uma das cartas do tabuleiro, é pedido ao jogador que seja encontrado seu respectivo par. No caso de sucesso, as duas cartas ficam viradas para cima, e o jogo aguarda a ação do jogador para encontrar novos pares. Caso não seja encontrado o par, as duas últimas cartas viradas para cima (que não compõem o par) retornam ao seu estado inicial (viradas para baixo).

main.cpp
Faz a criação da janela de aplicação, utilizando o objeto window criado em window.cpp e window.hpp, definindo também o título da janela e suas dimensões fixas. O programa por padrão vem com as dimensões definidas em 800x600 pixels. Após feita a criação, também faz o chamado da execução da janela criada, a fim de executar o jogo.

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
   emcc main.cpp -o index.html -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_FREETYPE=1
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
