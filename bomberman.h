#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Posicao{
    SDL_Rect origem;
    SDL_Rect destino;
};

struct Personagem{
    SDL_Texture *imagem;
    Posicao posicao;
    int bombas = 1;
    bool bomba = false;
    int vida = 3;
};

struct Componentes{
    SDL_Texture *imagem;
    Posicao posicao;
};

enum Itens{
    VAZIO,
    PAREDE,
    CAIXA,
    PLAYER1,
    BOT,
    BOMBA,
    FOGO
};

SDL_Texture* carregaImagem(const char *imagem, SDL_Renderer *renderizador);

void imprimeMapa(Componentes fogo, Componentes bomba, Componentes caixa, Componentes parede, Componentes fundo, Personagem player, Personagem bot, SDL_Renderer *renderizador, int mapa[13][15], int mapaBomba[13][15]);

void validaMovimento(int mapa[13][15], int indiceX, int indiceY);

void plantaBomba(Personagem &player, int mapaBomba[13][15], long int &tempoBomba, int indiceX, int indiceY);

void movimentaPersonagem(bool &termina, long int &tempoBomba, Personagem &player, int mapa[13][15], int mapaBomba[13][15]);

void movimentaBot(int mapa[13][15], Personagem &bot, int mapaBomba[13][15]);

void bombaAnimacao(Componentes &bomba, long int tempoInicio, long int tempoAtual);

void validaExplosao(int mapa[13][15], int mapaBomba[13][15], int indiceX, int indiceY, int adicionalX, int adicionalY);

bool explodeBomba(long int tempoInicio, int mapa[13][15], int mapaBomba[13][15], long int tempoAtual);

void verificaVidaPlayer(int mapa[13][15], int mapaBomba[13][15], Personagem &player);

bool limpaExplosao(int mapaBomba[13][15], long int tempoInicio, long int tempoAtual);

#endif // BOMBERMAN_H
