#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

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
    long int tempoBomba;
    int valorMapa;
};

struct Personagem{
    SDL_Texture *imagem;
    Posicao posicao;
    Bomba bomba;
    int vida = 3;
    bool danoBomba1 = false;
    bool danoBomba2 = false;
    int valorMapa;
    int fogoMapa;
};

struct Bot{
    Personagem personagem;
    int direcao;
    int quantidadePassos = 0;
    int passosAndados = 0;
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

enum Jogo{
    SINGLEPLAYER,
    MULTIPLAYER
};

enum Menu{
    INSTRUCOES,
    JOGAR,
    SAIR
};

SDL_Texture* carregaImagem(const char *imagem, SDL_Renderer *renderizador);

Personagem criaPlayer1(Personagem player1, SDL_Renderer *renderizador, SDL_Texture *personagens);

Personagem criaPlayer2(Personagem player2, SDL_Renderer *renderizador, SDL_Texture *personagens);

void criaComponentes(SDL_Renderer *renderizador, Componentes &menuPrincipal, Componentes &instrucoes, Componentes &menuJogar, Componentes &fundo, Componentes &caixa, Componentes &parede, Componentes &fogo, Componentes &botaoHome, Componentes &botaoRestart);

void criaFim(SDL_Renderer *renderizador, Componentes &empate, Componentes &player1Vence, Componentes &player2Vence);

int escolheMenuPrincipal(Componentes &menu, SDL_Cursor *cursor, bool &termina);

void carregaInstrucoes(Componentes &instrucoes, bool &abreInstrucoes, bool &abreMenuPrincipal, SDL_Cursor *cursor, bool &termina);

void escolheMenuJogar(Componentes &menuJogar, bool &abreMenuPrincipal, bool &abreMenuJogar, bool &jogaJogo, int &jogo, SDL_Cursor *cursor, bool &termina);

void resetMultiplayer(int mapa[13][15], int mapaBomba[13][15], Personagem &player1, Personagem &player2);

void resetSinglePlayer(int mapaSinglePlayer[13][15], int mapaBomb[13][15], Personagem &player1, Bot &bot);

void imprimeMapa(Componentes fogo, Componentes caixa, Componentes parede, Componentes fundo, Personagem player, Personagem bot, SDL_Renderer *renderizador, int mapa[13][15], int mapaBomba[13][15]);

void validaMovimento(int mapa[13][15], int indiceX, int indiceY, int player);

void plantaBomba(Personagem &player, int mapaBomba[13][15], int indiceX, int indiceY);

void movimentaPlayers(bool &termina, Personagem &player, Personagem &player2, int mapa[13][15], int mapaBomba[13][15], bool &abreMenuPrincipal, bool &jogaJogo, SDL_Cursor *cursor);

void movimentaPlayer1(bool &termina, Personagem &player, Bot &bot, int mapa[13][15], int mapaBomba[13][15], bool &abreMenuPrincipal, bool &jogaJogo, SDL_Cursor *cursor);

void movimentaBot(int mapa[13][15], Bot &bot, int frameCounter);

void bombaAnimacao(Personagem &player, long int tempoAtual);

void validaExplosao(Personagem &player, int mapa[13][15], int mapaBomba[13][15], int indiceX, int indiceY, int adicionalX, int adicionalY);

void bombaExplosao(Personagem player, long int tempoAtual, int mapa[13][15], int mapaBomba[13][15]);

void danoAnimacao(Personagem &player, int mapa[13][15], int mapaBomba[13][15], long int tempoBomba, long int tempoAtual);

void verificaVidaPlayer(int mapa[13][15], int mapaBomba[13][15], Personagem &player, int valorFogo, bool &dano);

void imprimeVidaPlayer1(Personagem player1, Componentes numeros, SDL_Renderer *renderizador, SDL_Texture *personagens);

void imprimeVidaPlayer2(Personagem player2, Componentes numeros, SDL_Renderer *renderizador, SDL_Texture *personagens);

bool limpaExplosao(Personagem player, int mapaBomba[13][15], long int tempoAtual);

void explodeBomba1(Personagem &playerPrincipal, Personagem &playerSecundario, int mapa[13][15], int mapaBomba[13][15], long int tempoAtual);

void explodeBomba2(Personagem &playerPrincipal, Personagem &playerSecundario, int mapa[13][15], int mapaBomba[13][15], long int tempoAtual);

bool verificaFimDeJogo(Personagem &player1, Personagem &player2);

void imprimeFimDeJogo(Personagem &player1, Personagem &player2, Componentes &empate, Componentes &player1Vence, Componentes &player2Vence, SDL_Renderer *renderizador, SDL_Cursor *cursor, bool &abreMenuPrincipal, bool &jogaJogo, bool &termina);


#endif // BOMBERMAN_H
