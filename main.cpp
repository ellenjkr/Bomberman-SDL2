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

    Componentes fundo, caixa, parede, bomba, fogo;
    fundo.imagem = carregaImagem("assets/fundo.bmp", renderizador);
    fundo.posicao.origem = {0, 0, 600, 600};
    fundo.posicao.destino = {0, 0, 600, 600};

    caixa.imagem = carregaImagem("assets/caixa.bmp", renderizador);
    caixa.posicao.origem = {0, 0, 200, 200};

    parede.imagem = carregaImagem("assets/parede.bmp", renderizador);
    parede.posicao.origem = {0, 0, 64, 64};

    bomba.imagem = carregaImagem("assets/bombaAzulSprite.bmp", renderizador);
    bomba.posicao.origem = {0, 0, 22, 22};

    fogo.imagem = carregaImagem("assets/fogo2.bmp", renderizador);
    fogo.posicao.origem = {0, 0, 40, 40};

    SDL_Texture *personagens = carregaImagem("assets/personagensBMP.bmp", renderizador);
    Personagem player1;
    player1.imagem = personagens;
    player1.posicao.origem = {32, 0, 32, 32};

    Personagem bot;
    bot.imagem = personagens;
    bot.posicao.origem = {128, 0, 32, 32};
    bot.posicao.destino = {440, 520, 40, 40};

    long int tempoBomba;
    bool termina = false;

    srand(time(NULL));
    while(!termina){
        long int tempoAtual = SDL_GetTicks();
        imprimeMapa(fogo, bomba, caixa, parede, fundo, player1, bot, renderizador, mapa, mapaBomba);
        movimentaPersonagem(termina, tempoBomba, player1, mapa, mapaBomba);
        bombaAnimacao(bomba, tempoBomba, tempoAtual);
        if(explodeBomba(tempoBomba, mapa, mapaBomba, tempoAtual) == true){
            verificaVidaPlayer(mapa, mapaBomba, player1);
            if(limpaExplosao(mapaBomba, tempoBomba, tempoAtual) == true){
                player1.bomba = false;
                player1.bombas += 1;
            }
        }
        movimentaBot(mapa, bot, mapaBomba);
    }
    ///PROBLEMA COM A VIDA
    SDL_DestroyWindow(janela);
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyTexture(fundo.imagem);
    SDL_DestroyTexture(caixa.imagem);
    SDL_DestroyTexture(parede.imagem);
    SDL_DestroyTexture(bomba.imagem);
    SDL_DestroyTexture(personagens);

    SDL_Quit();

    return 0;
}
