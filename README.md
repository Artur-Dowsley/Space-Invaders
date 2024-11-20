# Space Invaders

Uma versão do clássico jogo **Space Invaders** desenvolvida em **C**. Controle sua nave e elimine os alienígenas!

## Requisitos do Sistema
Para executar o jogo, você precisa:

- **Sistema Operacional**:
   - Linux
   - macOS
- **Dependências**:
   - gcc instalado no sistema.

   

## Como executar o jogo

- Clone o repositorio:
```
git clone https://github.com/Artur-Dowsley/Space-Invaders.git
```

- Navegue até o diretório correto


```
cd src
```

- Compile o codigo  usando:
```
gcc -o space_invaders main.c screen.c keyboard.c timer.c -lm 
```
- Execute o programa: 
```
./space_invaders
```
## Como Jogar:
Use as seguintes teclas para controlar o jogo
- **Tecla "a":** mover para a esquerda.
- **Tecla "d":** mover para a direita.
- **Tecla "espaço":** atirar.
- **Tecla "s":** usar o ataque especial.

## Dicas:
- **Evite os tiros inimigos**, pois um único impacto destruirá sua nave.
- **Elimine todos os alienígenas** para completar o objetivo.
- Fique atento ao uso do **ataque especial**, ele pode ser um salvador em momentos críticos!


## Objetivo do jogo:
O objetivo é **eliminar todos os alienígenas no menor tempo possível**. Tente superar seu próprio tempo ou desafiar outros jogadores!

## Ranking
Ao finalizar o jogo, será solicitado que você insira seu nome. O jogo então registrará o tempo que você levou para eliminar todos os alienígenas e salvará essa informação no arquivo recordes.txt, onde poderá ser visualizada posteriormente. **Tente bater seu próprio tempo ou desafiar outros jogadores para ver quem consegue o melhor desempenho!**

## Ataque Especial

O **ataque especial** dispara **4 tiros de uma vez**, em linha reta, lado a lado.

- **Como usar**:
   - **Tecla de Ativação**: Pressione **"s"** para ativar.


