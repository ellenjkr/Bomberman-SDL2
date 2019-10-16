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

struct Bomba{
    SDL_Texture *imagem;
    Posicao posicao;
    int quantidade = 1;
    bool plantada = false;
    int valorMapa;
};

struct Personagem{
    SDL_Texture *imagem;
    Posicao posicao;
    Bomba bomba;
    int vida = 3;
    int dano = 0;
    int valorMapa;
    int fogoMapa;
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
    PLAYER2,
    BOMBA1,
    BOMBA2,
    FOGO1,
    FOGO2
};

SDL_Texture* carregaImagem(const char *imagem, SDL_Renderer *renderizador);

void imprimeMapa(Componentes fogo, Componentes caixa, Componentes parede, Componentes fundo, Personagem player, Personagem bot, SDL_Renderer *renderizador, int mapa[13][15], int mapaBomba[13][15]);

void validaMovimento(int mapa[13][15], int indiceX, int indiceY, int player);

void plantaBomba(Personagem &player, int mapaBomba[13][15], long int &tempoBomba, int indiceX, int indiceY);

void movimentaPlayers(bool &termina, long int &tempoBomba, Personagem &player, long int &tempoBomba2, Personagem &player2, int mapa[13][15], int mapaBomba[13][15]);

void movimentaBot(int mapa[13][15], Personagem &bot);

void bombaAnimacao(Personagem &player, long int tempoInicio, long int tempoAtual);

void validaExplosao(Personagem &player, int mapa[13][15], int mapaBomba[13][15], int indiceX, int indiceY, int adicionalX, int adicionalY);

void explodeBomba(Personagem player, long int tempoInicio, long int tempoAtual, int mapa[13][15], int mapaBomba[13][15]);

void danoAnimacao(Personagem &player, int mapa[13][15], int mapaBomba[13][15], long int tempoAtual, long int tempoInicio);

void verificaVidaPlayer(int mapa[13][15], int mapaBomba[13][15], Personagem &player);

bool limpaExplosao(Personagem player, int mapaBomba[13][15], long int tempoInicio, long int tempoAtual);

#endif // BOMBERMAN_H
