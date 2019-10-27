#include "bomberman.h"

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *janela = SDL_CreateWindow("Bomberman",  SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    if(janela == nullptr){
        cout << "Erro ao criar janela" << SDL_GetError();
    }

    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    int mapa[13][15] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 3, 0, 0, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 1},
                        {1, 0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1},
                        {1, 0, 2, 0, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 1},
                        {1, 0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                        {1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 1},
                        {1, 2, 1, 2 ,1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1},
                        {1, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                        {1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 2, 1},
                        {1, 0, 2, 0, 2, 2, 0, 2, 0, 2, 0, 0, 0, 0, 1},
                        {1, 0, 1, 2, 1, 0, 1, 0, 1, 2, 1, 2, 1, 0, 1},
                        {1, 0, 0, 0, 2, 2, 2, 2, 0, 2, 2, 0, 0, 4, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    int mapaBomba[13][15] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    SDL_Texture *personagens = carregaImagem("assets/personagensBMP.bmp", renderizador);
    Personagem player1, player2;
    player1 = criaPlayer1(player1, renderizador, personagens);
    player2 = criaPlayer2(player2, renderizador, personagens);
    //player2.posicao.destino = {440, 520, 40, 40};
    Componentes fundo, caixa, parede, fogo, numeros, botaoHome, botaoRestart;
    criaComponentes(renderizador, fundo, caixa, parede, fogo, botaoHome, botaoRestart);
    numeros.imagem = carregaImagem("assets/numeros.bmp", renderizador);

    srand(time(NULL));

    bool termina = false;

    while(!termina){
        long int tempoAtual = SDL_GetTicks();
        imprimeMapa(fogo, caixa, parede, fundo, player1, player2, renderizador, mapa, mapaBomba);
        imprimeVidaPlayer1(player1, numeros, renderizador, personagens);
        imprimeVidaPlayer2(player2, numeros, renderizador, personagens);
        movimentaPlayers(termina, player1, player2, mapa, mapaBomba);
        if(player1.bomba.plantada == true){
            explodeBomba1(player1, player2, mapa, mapaBomba, tempoAtual);

        }
        if(player2.bomba.plantada == true){
            explodeBomba2(player2, player1, mapa, mapaBomba, tempoAtual);
        }
        //movimentaBot(mapa, player2);
        SDL_RenderCopy(renderizador, botaoRestart.imagem, &botaoRestart.posicao.origem, &botaoRestart.posicao.destino);
        SDL_RenderCopy(renderizador, botaoHome.imagem, &botaoHome.posicao.origem, &botaoHome.posicao.destino);
        SDL_RenderPresent(renderizador);
        SDL_RenderClear(renderizador);
        SDL_Delay(1000/60);
    }

    /// Menu
    /// Submenu
    /// Instruções
    /// Bot
    /// Fim de jogo
    /// Menu interno
    /// Bomba explode outra bomba

    /// PROBLEMA MOVIMENTAÇÃO BOT

    SDL_DestroyWindow(janela);
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyTexture(fundo.imagem);
    SDL_DestroyTexture(caixa.imagem);
    SDL_DestroyTexture(parede.imagem);
    SDL_DestroyTexture(numeros.imagem);
    SDL_DestroyTexture(botaoHome.imagem);
    SDL_DestroyTexture(botaoRestart.imagem);
    SDL_DestroyTexture(player1.bomba.imagem);
    SDL_DestroyTexture(player2.bomba.imagem);
    SDL_DestroyTexture(personagens);

    SDL_Quit();

    return 0;
}
