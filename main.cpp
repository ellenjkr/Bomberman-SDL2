#include "bomberman.h"

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *janela = SDL_CreateWindow("Bomberman",  SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    if(janela == nullptr){
        cout << "Erro ao criar janela" << SDL_GetError();
    }

    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    SDL_Cursor *cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    SDL_SetCursor(cursor);

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

    int mapaSinglePlayer[13][15] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                    {1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1},
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
    Bot bot;
    bot.personagem = player2;

    Componentes menuPrincipal, instrucoes, menuJogar, fundo, caixa, parede, fogo, numeros, botaoHome, botaoRestart, empate, player1Vence, player2Vence;
    criaComponentes(renderizador, menuPrincipal, instrucoes, menuJogar, fundo, caixa, parede, fogo, botaoHome, botaoRestart );
    criaFim(renderizador, empate, player1Vence, player2Vence);
    numeros.imagem = carregaImagem("assets/numeros.bmp", renderizador);

    srand(time(NULL));

    bool termina = false, abreMenuJogar = false, abreInstrucoes = false, abreMenuPrincipal = true, jogaJogo = false;
    int escolha = -1, jogo;
    int frameCounter = 0;

    while(!termina){
        if(abreMenuPrincipal == true){
            resetMultiplayer(mapa, mapaBomba, player1, player2);
            resetSinglePlayer(mapaSinglePlayer, mapaBomba, player1, bot);
            SDL_RenderCopy(renderizador, menuPrincipal.imagem, &menuPrincipal.posicao.origem, &menuPrincipal.posicao.destino);
            escolha = escolheMenuPrincipal(menuPrincipal, cursor, termina);
            if(escolha == INSTRUCOES){
                abreMenuPrincipal = false;
                abreInstrucoes = true;
            }
            else if(escolha == JOGAR){
                abreMenuPrincipal = false;
                abreMenuJogar = true;
            }
            else if(escolha == SAIR){
                termina = true;
            }
        }
        if(abreInstrucoes == true){
            SDL_RenderCopy(renderizador, instrucoes.imagem, &instrucoes.posicao.origem, &instrucoes.posicao.destino);
            carregaInstrucoes(instrucoes, abreInstrucoes, abreMenuPrincipal, cursor, termina);
        }
        if(abreMenuJogar == true){
            SDL_RenderCopy(renderizador, menuJogar.imagem, &menuJogar.posicao.origem, &menuJogar.posicao.destino);
            escolheMenuJogar(menuJogar, abreMenuPrincipal, abreMenuJogar, jogaJogo, jogo, cursor, termina);
        }
        if(jogaJogo == true){
            long int tempoAtual = SDL_GetTicks();
            if(jogo == SINGLEPLAYER){
                if(verificaFimDeJogo(player1, player2) == false){
                    imprimeMapa(fogo, caixa, parede, fundo, player1, bot.personagem, renderizador, mapaSinglePlayer, mapaBomba);
                    imprimeVidaPlayer1(player1, numeros, renderizador, personagens);
                    imprimeVidaPlayer2(bot.personagem, numeros, renderizador, personagens);
                    if(player1.vida != 0 and bot.personagem.vida != 0){
                        movimentaPlayer1(termina, player1, bot, mapaSinglePlayer, mapaBomba, abreMenuPrincipal, jogaJogo, cursor);
                        movimentaBot(mapaSinglePlayer, bot, frameCounter);
                    }
                    if(player1.bomba.plantada == true){
                        explodeBomba1(player1, bot.personagem, mapaSinglePlayer, mapaBomba, tempoAtual);
                    }
                    SDL_RenderCopy(renderizador, botaoRestart.imagem, &botaoRestart.posicao.origem, &botaoRestart.posicao.destino);
                    SDL_RenderCopy(renderizador, botaoHome.imagem, &botaoHome.posicao.origem, &botaoHome.posicao.destino);
                }
                else{
                    imprimeFimDeJogo(player1, bot.personagem, empate, player1Vence, player2Vence, renderizador, cursor, abreMenuPrincipal, jogaJogo, termina);
                }
            }
            else if(jogo == MULTIPLAYER){
                if(player1.bomba.tempoBomba == player2.bomba.tempoBomba){
                    cout << "igual" << endl;
                }
                if(verificaFimDeJogo(player1, player2) == false){
                    imprimeMapa(fogo, caixa, parede, fundo, player1, player2, renderizador, mapa, mapaBomba);
                    imprimeVidaPlayer1(player1, numeros, renderizador, personagens);
                    imprimeVidaPlayer2(player2, numeros, renderizador, personagens);
                    if(player1.vida != 0 and player2.vida != 0){
                        movimentaPlayers(termina, player1, player2, mapa, mapaBomba, abreMenuPrincipal, jogaJogo, cursor);
                    }
                    if(player1.bomba.plantada == true){
                        explodeBomba1(player1, player2, mapa, mapaBomba, tempoAtual);
                    }
                    if(player2.bomba.plantada == true){
                        explodeBomba2(player2, player1, mapa, mapaBomba, tempoAtual);
                    }
                    SDL_RenderCopy(renderizador, botaoRestart.imagem, &botaoRestart.posicao.origem, &botaoRestart.posicao.destino);
                    SDL_RenderCopy(renderizador, botaoHome.imagem, &botaoHome.posicao.origem, &botaoHome.posicao.destino);
                }
                else{
                    imprimeFimDeJogo(player1, player2, empate, player1Vence, player2Vence, renderizador, cursor, abreMenuPrincipal, jogaJogo, termina);
                }
            }
        }
        SDL_RenderPresent(renderizador);
        SDL_RenderClear(renderizador);
        SDL_Delay(1000/60);
        frameCounter++;
    }

    SDL_DestroyWindow(janela);
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyTexture(menuPrincipal.imagem);
    SDL_DestroyTexture(menuJogar.imagem);
    SDL_DestroyTexture(instrucoes.imagem);
    SDL_DestroyTexture(fundo.imagem);
    SDL_DestroyTexture(caixa.imagem);
    SDL_DestroyTexture(parede.imagem);
    SDL_DestroyTexture(numeros.imagem);
    SDL_DestroyTexture(botaoHome.imagem);
    SDL_DestroyTexture(botaoRestart.imagem);
    SDL_DestroyTexture(player1.bomba.imagem);
    SDL_DestroyTexture(player2.bomba.imagem);
    SDL_DestroyTexture(empate.imagem);
    SDL_DestroyTexture(player1Vence.imagem);
    SDL_DestroyTexture(player2Vence.imagem);
    SDL_DestroyTexture(personagens);

    SDL_Quit();

    return 0;
}
