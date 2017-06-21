# Bomberman

Esse jogo é baseado no bomberman, é um jogo de estratégia multiplayer.

## Condição de vitória

* Conseguir armar uma bomba que ao explodir irá atingir o outro player ou o outro player se auto-mutilar.

## Condição de derrota
* Ser atingido pela explosão da bomba do outro player.
* Ser atingido pela explosão de qualquer bomba.

## Personagens
Bomberman

## Características

* Gênero: Estratégia.
* Quantidade de jogadores: 2.

## O jogo

O jogo consiste em uma campo, pré-definido, em que dois jogadores se movimentam e armam bombas. O objetivo é atingir o outro player com a explosão
de bombas. O cenário é composto por blocos destrutíveis, os quais a explosão bomba pode destruir,  e indestrutíveis, os quais a explosão bomba não pode. Portanto antes de tentar atingir o adversário devem explodir esses blocos do caminho.

## Controles
### Player 1

| Tecla | Ação |
|:-----:|:----:|
| W |Move o personagem para cima|
| S |Move o personagem para baixo|
| A |Move o personagem para esquerda|
| D |Move o personagem para direita|
| Espaço |Arma a bomba|

### Player 2

| Tecla | Ação |
|:-----:|:----:|
| Seta para cima |Move o personagem para cima|
| Seta para baixo |Move o personagem para baixo|
| Seta para esquerda |Move o personagem para esquerda|
| Seta para direita |Move o personagem para direita|
| P |Arma a bomba|

## Dependências

- CMake 3.5.1
- SDL 2
- SDL\_image 2
- SDL\_ttf 2
- SDL\_mixer 2

## Como executar

```
$ git clone https://github.com/Ronyell/Bomberman.git
$ cd Bomberman
$ cmake .
$ make
$ ./bomberman
```

## Autores

### Desenvolvedor
- Ronyell Henrique dos Santos (@Ronyell)
