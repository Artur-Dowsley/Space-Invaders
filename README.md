# Space Invaders

## Requesitos
- precisa estar utilizando algum desses sistemas operacionais:
   - Linux
   - MacOS
- precisa ter o gcc instalado.

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

Aperte as teclas "d" e "a" para mover para a direita e para a esquerda e utilize o espaço para atirar
se for atingido por um tiro inimigo sera destruido


## Objetivo

Eliminar todas as naves inimigas e evitar ser destruido