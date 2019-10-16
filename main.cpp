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

    Componentes fundo, caixa, parede, fogo;
    fundo.imagem = carregaImagem("assets/fundo.bmp", renderizador);
    fundo.posicao.origem = {0, 0, 600, 600};
    fundo.posicao.destino = {0, 0, 600, 600};

    caixa.imagem = carregaImagem("assets/caixa.bmp", renderizador);
    caixa.posicao.origem = {0, 0, 200, 200};

    parede.imagem = carregaImagem("assets/parede.bmp", renderizador);
    parede.posicao.origem = {0, 0, 64, 64};

    fogo.imagem = carregaImagem("assets/fogo2.bmp", renderizador);
    fogo.posicao.origem = {0, 0, 40, 40};

    SDL_Texture *personagens = carregaImagem("assets/personagensBMP.bmp", renderizador);
    Personagem player1;
    player1.imagem = personagens;
    player1.posicao.origem = {32, 0, 32, 32};
    player1.bomba.imagem = carregaImagem("assets/bombaAzulSprite.bmp", renderizador);
    player1.bomba.posicao.origem = {0, 0, 22, 22};
    player1.bomba.valorMapa = BOMBA1;
    player1.valorMapa = PLAYER1;
    player1.fogoMapa = FOGO1;

    Personagem player2;
    player2.imagem = personagens;
    player2.posicao.origem = {128, 0, 32, 32};
    //player2.posicao.destino = {440, 520, 40, 40};
    player2.bomba.imagem = carregaImagem("assets/bombaVermSprite.bmp", renderizador);
    player2.bomba.posicao.origem = {0, 0, 22, 22};
    player2.bomba.valorMapa = BOMBA2;
    player2.valorMapa = PLAYER2;
    player2.fogoMapa = FOGO2;

    long int tempoBomba;
    long int tempoBomba2;
    bool termina = false;

    srand(time(NULL));
    while(!termina){
        long int tempoAtual = SDL_GetTicks();
        imprimeMapa(fogo, caixa, parede, fundo, player1, player2, renderizador, mapa, mapaBomba);
        movimentaPlayers(termina, tempoBomba, player1, tempoBomba2, player2, mapa, mapaBomba);
        if(player1.bomba.plantada == true){
            bombaAnimacao(player1, tempoBomba, tempoAtual);
            explodeBomba(player1, tempoBomba, tempoAtual, mapa, mapaBomba);
            danoAnimacao(player1, mapa, mapaBomba, tempoAtual, tempoBomba);
            danoAnimacao(player2, mapa, mapaBomba, tempoAtual, tempoBomba);
            verificaVidaPlayer(mapa, mapaBomba, player1);
            verificaVidaPlayer(mapa, mapaBomba, player2);
            if(limpaExplosao(player1, mapaBomba, tempoBomba, tempoAtual) == true){
                player1.dano = 0;
                player2.dano = 0;
                player1.bomba.plantada = false;
                player1.bomba.quantidade += 1;
            }
        }
        if(player2.bomba.plantada == true){
            bombaAnimacao(player2, tempoBomba2, tempoAtual);
            explodeBomba(player2, tempoBomba2, tempoAtual, mapa, mapaBomba);
            danoAnimacao(player1, mapa, mapaBomba, tempoAtual, tempoBomba2);
            danoAnimacao(player2, mapa, mapaBomba, tempoAtual, tempoBomba2);
            verificaVidaPlayer(mapa, mapaBomba, player2);
            verificaVidaPlayer(mapa, mapaBomba, player1);
            if(limpaExplosao(player2, mapaBomba, tempoBomba2, tempoAtual) == true){
                player2.dano = 0;
                player1.dano = 0;
                player2.bomba.plantada = false;
                player2.bomba.quantidade += 1;
            }
        }
        //movimentaBot(mapa, player2);
    }
    ///PROBLEMA QUANDO SEGURA TECLAS DIFERENTES, UMA DE CADA PERSONAGEM
    ///PROBLEMA MOVIMENTAÇÃO BOT
    SDL_DestroyWindow(janela);
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyTexture(fundo.imagem);
    SDL_DestroyTexture(caixa.imagem);
    SDL_DestroyTexture(parede.imagem);
    SDL_DestroyTexture(player1.bomba.imagem);
    SDL_DestroyTexture(personagens);

    SDL_Quit();

    return 0;
}
