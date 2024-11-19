# Space Invaders

## Requisitos
- Precisa estar utilizando algum desses sistemas operacionais:
   - Linux
   - MacOS
- Precisa ter o gcc instalado.

## Como executar o jogo

- Clone o repositorio:
```
https://github.com/Artur-Dowsley/Space-Invaders.git
```

- Va ate o diretorio correto

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


## Como jogar

Aperte as teclas "d" e "a" para mover para a direita e para a esquerda ,aperte "s" para usar o especial e utilize o espaço para atirar.
Se for atingido por um tiro inimigo, você será destruído


## Objetivo

Eliminar todos os aliens e evitar ser atingido.
