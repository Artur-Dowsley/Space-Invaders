# Space Invaders
Command Line Interface library, for developing CLI applications and games in C. It has functions to access keyboard, screen and manage timing tasks.

## Requirements
- This library works with the follwing OS:
   - Linux based (Ubuntu, etc)
   - MacOS
- It is necessary to have GCC installed.

## como executar o jogo

clone o repositorio:
```
https://github.com/Artur-Dowsley/Space-Invaders.git
```

va ate o diretorio correto

```
cd src
```

compile o codigo  usando:
```
gcc -o space_invaders main.c screen.c keyboard.c timer.c -lm 
```
execute o programa: 
```
./space_invaders
```

## como jogar

aperte as teclas "d" e "a" para mover para a direita e para a esquerda e utilize o espaço para atirar

