#include "bomberman.h"

SDL_Texture* carregaImagem(const char *imagem, SDL_Renderer *renderizador){
    SDL_Surface *img = SDL_LoadBMP(imagem);
    if(img == nullptr){
        cout << "Erro no carregamento da imagem" << SDL_GetError();
    }
    SDL_Texture *textura = SDL_CreateTextureFromSurface(renderizador, img);
    SDL_FreeSurface(img);
    return textura;
}

Personagem criaPlayer1(Personagem player1, SDL_Renderer *renderizador, SDL_Texture *personagens){
    player1.imagem = personagens;
    player1.posicao.origem = {32, 0, 32, 32};
    player1.bomba.imagem = carregaImagem("assets/bombaAzulSprite.bmp", renderizador);
    player1.bomba.posicao.origem = {0, 0, 22, 22};
    player1.bomba.valorMapa = BOMBA1;
    player1.valorMapa = PLAYER1;
    player1.fogoMapa = FOGO1;

    return player1;
}

Personagem criaPlayer2(Personagem player2, SDL_Renderer *renderizador, SDL_Texture *personagens){
    player2.imagem = personagens;
    player2.posicao.origem = {128, 0, 32, 32};
    player2.bomba.imagem = carregaImagem("assets/bombaVermSprite.bmp", renderizador);
    player2.bomba.posicao.origem = {0, 0, 22, 22};
    player2.bomba.valorMapa = BOMBA2;
    player2.valorMapa = PLAYER2;
    player2.fogoMapa = FOGO2;

    return player2;
}

void criaComponentes(SDL_Renderer *renderizador, Componentes &menuPrincipal, Componentes &instrucoes, Componentes &menuJogar, Componentes &fundo, Componentes &caixa, Componentes &parede, Componentes &fogo, Componentes &botaoHome, Componentes &botaoRestart){

    menuPrincipal.imagem = carregaImagem("assets/menu.bmp", renderizador);
    menuPrincipal.posicao.origem = {0, 0, 600, 600};
    menuPrincipal.posicao.destino = {0, 0, 600, 600};

    instrucoes.imagem = carregaImagem("assets/instrucoes.bmp", renderizador);
    instrucoes.posicao.origem = {0, 0, 600, 600};
    instrucoes.posicao.destino = {0, 0, 600, 600};

    menuJogar.imagem = carregaImagem("assets/menuJogar.bmp", renderizador);
    menuJogar.posicao.origem = {0, 0, 600, 600};
    menuJogar.posicao.destino = {0, 0, 600, 600};

    fundo.imagem = carregaImagem("assets/fundo.bmp", renderizador);
    fundo.posicao.origem = {0, 0, 600, 600};
    fundo.posicao.destino = {0, 0, 600, 600};

    caixa.imagem = carregaImagem("assets/caixa.bmp", renderizador);
    caixa.posicao.origem = {0, 0, 200, 200};

    parede.imagem = carregaImagem("assets/parede.bmp", renderizador);
    parede.posicao.origem = {0, 0, 64, 64};

    fogo.imagem = carregaImagem("assets/fogo2.bmp", renderizador);
    fogo.posicao.origem = {0, 0, 40, 40};

    botaoRestart.imagem = carregaImagem("assets/restart.bmp", renderizador);
    botaoRestart.posicao.origem = {0, 0, 106, 120};
    botaoRestart.posicao.destino = {267, 545, 30, 35};

    botaoHome.imagem = carregaImagem("assets/home.bmp", renderizador);
    botaoHome.posicao.origem = {0, 0, 106, 113};
    botaoHome.posicao.destino = {303, 545, 35, 35};
}

void criaFim(SDL_Renderer *renderizador, Componentes &empate, Componentes &player1Vence, Componentes &player2Vence){
    empate.imagem = carregaImagem("assets/empate.bmp", renderizador);
    empate.posicao.origem = {0, 0, 600, 600};
    empate.posicao.destino = {0, 0, 600, 600};

    player1Vence.imagem = carregaImagem("assets/player1Vence.bmp", renderizador);
    player1Vence.posicao.origem = {0, 0, 600, 600};
    player1Vence.posicao.destino = {0, 0, 600, 600};

    player2Vence.imagem = carregaImagem("assets/player2Vence.bmp", renderizador);
    player2Vence.posicao.origem = {0, 0, 600, 600};
    player2Vence.posicao.destino = {0, 0, 600, 600};


}

int escolheMenuPrincipal(Componentes &menu, SDL_Cursor *cursor, bool &termina){
	int escolha = -1;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_MOUSEMOTION:{
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(x > 150 and x < 455 and y > 240 and y < 325){
                    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                    SDL_SetCursor(cursor);
                    menu.posicao.origem.x = 600;
                }
                else if(x > 150 and x < 430 and y > 350 and y < 450){
                    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                    SDL_SetCursor(cursor);
                    menu.posicao.origem.x = 1200;
                }
                else if(x > 200 and x < 390 and y > 460 and y < 555){
                    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                    SDL_SetCursor(cursor);
                    menu.posicao.origem.x = 1800;
                }
                else{
                    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                    SDL_SetCursor(cursor);
                    menu.posicao.origem.x = 0;
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:{
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(x > 150 and x < 455 and y > 240 and y < 325){
                    escolha = INSTRUCOES;
                }
                else if(x > 150 and x < 430 and y > 350 and y < 450){
                    escolha = JOGAR;
                }
                else if(x > 200 and x < 390 and y > 460 and y < 555){
                    escolha = SAIR;
                }
                break;
            }
            case SDL_QUIT:{
                termina = true;
                break;
            }
        }
    }
    return escolha;
}

void carregaInstrucoes(Componentes &instrucoes, bool &abreInstrucoes, bool &abreMenuPrincipal, SDL_Cursor *cursor, bool &termina){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_MOUSEMOTION:{
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x > 223 and x < 375 and y > 480 and y < 533){
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
                instrucoes.posicao.origem.x = 600;
            }
            else{
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                SDL_SetCursor(cursor);
                instrucoes.posicao.origem.x = 0;
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x > 223 and x < 375 and y > 480 and y < 533){
                abreInstrucoes = false;
                abreMenuPrincipal = true;
            }
            break;

        }
        case SDL_QUIT:{
            termina = true;
            break;
        }
        default:
            break;
        }
    }
}

void escolheMenuJogar(Componentes &menuJogar, bool &abreMenuPrincipal, bool &abreMenuJogar, bool &jogaJogo, int &jogo, SDL_Cursor *cursor, bool &termina){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_MOUSEMOTION:{
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x > 129 and x < 471 and y > 249 and y < 312){
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
                menuJogar.posicao.origem.x = 600;
            }
            else if(x > 161 and x < 438 and y > 360 and y < 422){
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
                menuJogar.posicao.origem.x = 1200;
            }
            else if(x > 221 and x < 376 and y > 480 and y < 533){
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
                menuJogar.posicao.origem.x = 1800;
            }
            else{
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                SDL_SetCursor(cursor);
                menuJogar.posicao.origem.x = 0;
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x > 129 and x < 471 and y > 249 and y < 312){
                abreMenuJogar = false;
                jogaJogo = true;
                jogo = SINGLEPLAYER;
            }
            else if(x > 161 and x < 438 and y > 360 and y < 422){
                jogaJogo = true;
                abreMenuJogar = false;
                jogo = MULTIPLAYER;
            }
            else if(x > 221 and x < 376 and y > 480 and y < 533){
                abreMenuJogar = false;
                abreMenuPrincipal = true;
            }
            break;

        }
        case SDL_QUIT:{
            termina = true;
            break;
        }
        default:
            break;
        }
    }
}

void resetMultiplayer(int mapa[13][15], int mapaBomba[13][15], Personagem &player1, Personagem &player2){

    int mapaOriginal[13][15] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
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

    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 15; ++j) {
            mapa[i][j] = mapaOriginal[i][j];
            mapaBomba[i][j] = 0;
        }
    }

    player1.vida = 3;
    player1.bomba.plantada = false;
    player1.bomba.quantidade = 1;
    player1.posicao.origem = {32, 0, 32, 32};

    player2.vida = 3;
    player2.bomba.plantada = false;
    player2.bomba.quantidade = 1;
    player2.posicao.origem = {128, 0, 32, 32};

}

void resetSinglePlayer(int mapaSinglePlayer[13][15], int mapaBomba[13][15], Personagem &player1, Bot &bot){

    int mapaSinglePlayerOriginal[13][15] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
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

    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 15; ++j) {
            mapaSinglePlayer[i][j] = mapaSinglePlayerOriginal[i][j];
            mapaBomba[i][j] = 0;
        }
    }

    player1.vida = 3;
    player1.bomba.plantada = false;
    player1.bomba.quantidade = 1;
    player1.posicao.origem = {32, 0, 32, 32};

    bot.personagem.vida = 3;
    bot.personagem.bomba.plantada = false;
    bot.personagem.bomba.quantidade = 1;
    bot.personagem.posicao.origem = {128, 0, 32, 32};
    bot.personagem.vida = 3;
}

void imprimeMapa(Componentes fogo, Componentes caixa, Componentes parede, Componentes fundo, Personagem player1, Personagem player2, SDL_Renderer *renderizador, int mapa[13][15], int mapaBomba[13][15]){
    SDL_RenderCopy(renderizador, fundo.imagem, &fundo.posicao.origem, &fundo.posicao.destino);
    int posicaoY;
    int posicaoX;
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 15; ++j) {
            posicaoY = i * 40;
            posicaoX = j * 40;
            if(mapa[i][j] == PAREDE ){
                parede.posicao.destino = {posicaoX, posicaoY, 40, 40};
                SDL_RenderCopy(renderizador, parede.imagem, &parede.posicao.origem, &parede.posicao.destino);
            }
            else if(mapa[i][j] == CAIXA){
                caixa.posicao.destino = {posicaoX, posicaoY, 40, 40};
                SDL_RenderCopy(renderizador, caixa.imagem, &caixa.posicao.origem, &caixa.posicao.destino);
            }
            else if(mapa[i][j] == PLAYER1){
                player1.posicao.destino.x = posicaoX;
                player1.posicao.destino.y = posicaoY;
                if(mapaBomba[i][j] != FOGO1 and mapaBomba[i][j] != FOGO2){
                    player1.posicao.destino.h = 40;
                    player1.posicao.destino.w = 40;
                }
                else{
                    fogo.posicao.destino = {posicaoX, posicaoY, 40, 40};
                    SDL_RenderCopy(renderizador, fogo.imagem, &fogo.posicao.origem, &fogo.posicao.destino);
                }
                SDL_RenderCopy(renderizador, player1.imagem, &player1.posicao.origem, &player1.posicao.destino);
            }
            else if(mapa[i][j] == PLAYER2){
                player2.posicao.destino.x = posicaoX;
                player2.posicao.destino.y = posicaoY;
                if(mapaBomba[i][j] != FOGO1 and mapaBomba[i][j] != FOGO2){
                    player2.posicao.destino.h = 40;
                    player2.posicao.destino.w = 40;
                }
                else{
                    fogo.posicao.destino = {posicaoX, posicaoY, 40, 40};
                    SDL_RenderCopy(renderizador, fogo.imagem, &fogo.posicao.origem, &fogo.posicao.destino);
                }
                SDL_RenderCopy(renderizador, player2.imagem, &player2.posicao.origem, &player2.posicao.destino);
            }
            else if(mapaBomba[i][j] == BOMBA1){
                player1.bomba.posicao.destino = {posicaoX, posicaoY, 40, 40};
                SDL_RenderCopy(renderizador, player1.bomba.imagem, &player1.bomba.posicao.origem, &player1.bomba.posicao.destino);
            }
            else if(mapaBomba[i][j] == BOMBA2){
                player2.bomba.posicao.destino = {posicaoX, posicaoY, 40, 40};
                SDL_RenderCopy(renderizador, player2.bomba.imagem, &player2.bomba.posicao.origem, &player2.bomba.posicao.destino);
            }
            else if(mapaBomba[i][j] == FOGO1 or mapaBomba[i][j] == FOGO2){
                fogo.posicao.destino = {posicaoX, posicaoY, 40, 40};
                SDL_RenderCopy(renderizador, fogo.imagem, &fogo.posicao.origem, &fogo.posicao.destino);
            }
        }
    }
}

void validaMovimento(int mapa[13][15], int indiceX, int indiceY, int adicionalX, int adicionalY, int player){
    if(mapa[indiceX + adicionalX][indiceY + adicionalY] == VAZIO){
        mapa[indiceX + adicionalX][indiceY + adicionalY] = player;
        mapa[indiceX][indiceY] = VAZIO;
    }
}

void plantaBomba(Personagem &player, int mapaBomba[13][15], int indiceX, int indiceY){
    if(player.bomba.quantidade != 0 and player.bomba.plantada == false){
        player.bomba.plantada = true;
        mapaBomba[indiceX][indiceY] = player.bomba.valorMapa;
        player.bomba.quantidade -= 1;
        player.bomba.tempoBomba = SDL_GetTicks();
    }
}

void movimentaPlayers(bool &termina, Personagem &player, Personagem &player2, int mapa[13][15], int mapaBomba[13][15], bool &abreMenuPrincipal, bool &jogaJogo, SDL_Cursor *cursor){
    SDL_Event evento;
    int indiceX = 0;
    int indiceY = 0;
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 15; ++j) {
            if(mapa[i][j] == PLAYER1){
                indiceX = i;
                indiceY = j;
            }
        }
    }
    int indiceX2 = 0;
    int indiceY2 = 0;
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 15; ++j) {
            if(mapa[i][j] == PLAYER2){
                indiceX2 = i;
                indiceY2 = j;
            }
        }
    }
    while(SDL_PollEvent(&evento)){
        if(evento.type == SDL_QUIT){
            termina = true;
        }
        if(evento.type == SDL_MOUSEMOTION){
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x > 303 and x < 338 and y > 545 and y < 580){
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
            }
            else if(x > 267 and x < 297 and y > 545 and y < 580){
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
            }
            else{
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                SDL_SetCursor(cursor);
            }
        }
        if(evento.type == SDL_MOUSEBUTTONDOWN){
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x > 303 and x < 338 and y > 545 and y < 580){
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
                jogaJogo = false;
                abreMenuPrincipal = true;
            }
            else if(x > 267 and x < 297 and y > 545 and y < 580){
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
                resetMultiplayer(mapa, mapaBomba, player, player2);
            }
        }
        else if(evento.type == SDL_KEYUP){
            if(evento.key.keysym.sym == SDLK_SPACE){
                plantaBomba(player, mapaBomba, indiceX, indiceY);
            }
            if(evento.key.keysym.sym == SDLK_s){
                player.posicao.origem = {32, 0, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, 1, 0, PLAYER1);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_w){
                player.posicao.origem = {32, 96, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, -1, 0, PLAYER1);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_a){
                player.posicao.origem = {32, 32, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, 0, -1, PLAYER1);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_d){
                player.posicao.origem = {32, 64, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, 0, 1, PLAYER1);
                break;
            }
            if(evento.key.keysym.sym == SDLK_KP_4){
                plantaBomba(player2, mapaBomba, indiceX2, indiceY2);
            }
            if(evento.key.keysym.sym == SDLK_KP_2){
                player2.posicao.origem = {128, 0, 32, 32};
                validaMovimento(mapa, indiceX2, indiceY2, 1, 0, PLAYER2);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_KP_5){
                player2.posicao.origem = {128, 96, 32, 32};
                validaMovimento(mapa, indiceX2, indiceY2, -1, 0, PLAYER2);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_KP_1){
                player2.posicao.origem = {128, 32, 32, 32};
                validaMovimento(mapa, indiceX2, indiceY2, 0, -1, PLAYER2);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_KP_3){
                player2.posicao.origem = {128, 64, 32, 32};
                validaMovimento(mapa, indiceX2, indiceY2, 0, 1, PLAYER2);
                break;
            }
        }
    }
}

void movimentaPlayer1(bool &termina, Personagem &player, Bot &bot, int mapa[13][15], int mapaBomba[13][15], bool &abreMenuPrincipal, bool &jogaJogo, SDL_Cursor *cursor){
    SDL_Event evento;
    int indiceX = 0;
    int indiceY = 0;
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 15; ++j) {
            if(mapa[i][j] == PLAYER1){
                indiceX = i;
                indiceY = j;
            }
        }
    }
    while(SDL_PollEvent(&evento)){
        if(evento.type == SDL_QUIT){
            termina = true;
        }
        if(evento.type == SDL_MOUSEMOTION){
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x > 303 and x < 338 and y > 545 and y < 580){
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
            }
            else if(x > 267 and x < 297 and y > 545 and y < 580){
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
            }
            else{
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                SDL_SetCursor(cursor);
            }
        }
        if(evento.type == SDL_MOUSEBUTTONDOWN){
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x > 303 and x < 338 and y > 545 and y < 580){
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
                jogaJogo = false;
                abreMenuPrincipal = true;
            }
            else if(x > 267 and x < 297 and y > 545 and y < 580){
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
                resetSinglePlayer(mapa, mapaBomba, player, bot);
            }
            else{
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                SDL_SetCursor(cursor);
            }
        }
        else if(evento.type == SDL_KEYUP){
            if(evento.key.keysym.sym == SDLK_SPACE){
                plantaBomba(player, mapaBomba, indiceX, indiceY);
            }
            if(evento.key.keysym.sym == SDLK_s){
                player.posicao.origem = {32, 0, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, 1, 0, PLAYER1);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_w){
                player.posicao.origem = {32, 96, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, -1, 0, PLAYER1);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_a){
                player.posicao.origem = {32, 32, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, 0, -1, PLAYER1);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_d){
                player.posicao.origem = {32, 64, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, 0, 1, PLAYER1);
                break;
            }
        }
    }
}

void movimentaBot(int mapa[13][15], Bot &bot, int frameCounter){
    if(bot.quantidadePassos == 0){
        bot.direcao = rand()%4;
        bot.quantidadePassos = rand() % 5;
    }
    int indiceX;
    int indiceY;
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 15; ++j) {
            if(mapa[i][j] == PLAYER2){
                indiceX = i;
                indiceY = j;
            }
        }
    }
    if(frameCounter % 10 == 0){
        if(bot.direcao == 0){ // DIREITA
            if(mapa[indiceX][indiceY+1] == VAZIO){
                validaMovimento(mapa, indiceX, indiceY, 0, 1, PLAYER2);
                bot.personagem.posicao.origem = {128, 64, 32, 32};
                bot.passosAndados++;
            }
            else{
                bot.passosAndados = 0;
                bot.quantidadePassos = 0;
            }
        }
        else if(bot.direcao == 1){ // ESQUERDA
            if(mapa[indiceX][indiceY-1] == VAZIO){
                validaMovimento(mapa, indiceX, indiceY, 0, -1, PLAYER2);
                bot.personagem.posicao.origem = {128, 32, 32, 32};
                bot.passosAndados++;
            }
            else{
                bot.passosAndados = 0;
                bot.quantidadePassos = 0;
            }
        }
        else if(bot.direcao == 2){ // CIMA
            if(mapa[indiceX-1][indiceY] == VAZIO){
                validaMovimento(mapa, indiceX, indiceY, -1, 0, PLAYER2);
                bot.personagem.posicao.origem = {128, 96, 32, 32};
                bot.passosAndados++;
            }
            else{
                bot.passosAndados = 0;
                bot.quantidadePassos = 0;
            }
        }
        else if(bot.direcao == 3){ // BAIXO
            if(mapa[indiceX+1][indiceY] == VAZIO){
                validaMovimento(mapa, indiceX, indiceY, 1, 0, PLAYER2);
                bot.personagem.posicao.origem = {128, 0, 32, 32};
                bot.passosAndados++;
            }
            else{
                bot.passosAndados = 0;
                bot.quantidadePassos = 0;
            }

        }
    }
    if(bot.passosAndados == bot.quantidadePassos){
        bot.passosAndados = 0;
        bot.quantidadePassos = 0;
    }
}

void bombaAnimacao(Personagem &player, long int tempoAtual){
    if(tempoAtual - player.bomba.tempoBomba == 100 ){
        player.bomba.posicao.origem = {22, 0, 22, 22};
    }
    else if(tempoAtual - player.bomba.tempoBomba < 200){
        player.bomba.posicao.origem = {44, 0, 22, 22};
    }
    else if(tempoAtual - player.bomba.tempoBomba < 300 ){
        player.bomba.posicao.origem = {66, 0, 22, 22};
    }
    else if(tempoAtual - player.bomba.tempoBomba < 400 ){
        player.bomba.posicao.origem = {88, 0, 22, 22};
    }
    else if(tempoAtual - player.bomba.tempoBomba < 500 ){
        player.bomba.posicao.origem = {110, 0, 22, 22};
    }
    else if(tempoAtual - player.bomba.tempoBomba < 700 ){
        player.bomba.posicao.origem = {132, 0, 22, 22};
    }
    else if(tempoAtual - player.bomba.tempoBomba < 800 ){
        player.bomba.posicao.origem = {154, 0, 22, 22};
    }
    else if(tempoAtual - player.bomba.tempoBomba < 900 ){
        player.bomba.posicao.origem = {176, 0, 22, 22};
    }
    else if(tempoAtual - player.bomba.tempoBomba < 1000 ){
        player.bomba.posicao.origem = {198, 0, 22, 22};
    }
    else if(tempoAtual - player.bomba.tempoBomba < 1100 ){
        player.bomba.posicao.origem = {220, 0, 22, 22};
    }
    else if(tempoAtual - player.bomba.tempoBomba < 1200 ){
        player.bomba.posicao.origem = {198, 0, 22, 22};
    }
    else if(tempoAtual - player.bomba.tempoBomba < 1300 ){
        player.bomba.posicao.origem = {220, 0, 22, 22};
    }
    else if(tempoAtual - player.bomba.tempoBomba < 1400 ){
        player.bomba.posicao.origem = {198, 0, 22, 22};
    }
    else if(tempoAtual - player.bomba.tempoBomba < 1500 ){
        player.bomba.posicao.origem = {220, 0, 22, 22};
    }
}

void validaExplosao(Personagem &player, int mapa[13][15], int mapaBomba[13][15], int indiceX, int indiceY, int adicionalX, int adicionalY){
    int cont = 1;
    while(cont < 3){
        if(mapa[indiceX + adicionalX * cont][indiceY + adicionalY * cont] != PAREDE and mapaBomba[indiceX + adicionalX * cont][indiceY + adicionalY * cont] == VAZIO){
            mapaBomba[indiceX + adicionalX * cont][indiceY + adicionalY * cont] = player.fogoMapa;
            if(mapa[indiceX + adicionalX * cont][indiceY + adicionalY * cont] == CAIXA){
                mapa[indiceX + adicionalX * cont][indiceY + adicionalY * cont] = VAZIO;
                break;
            }
        }
        else{
            break;
        }
        cont++;
    }
}

void bombaExplosao(Personagem player, long int tempoAtual, int mapa[13][15], int mapaBomba[13][15]){
    if(tempoAtual - player.bomba.tempoBomba > 1500 ){ // milisegundos
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 15; ++j) {
                if(mapaBomba[i][j] == player.bomba.valorMapa){
                    mapaBomba[i][j] = player.fogoMapa;
                    validaExplosao(player, mapa, mapaBomba, i, j, 0, 1); // DIREITA
                    validaExplosao(player, mapa, mapaBomba, i, j, 0, -1); // ESQUERDA
                    validaExplosao(player, mapa, mapaBomba, i, j, -1, 0); // EM CIMA
                    validaExplosao(player, mapa, mapaBomba, i, j, +1, 0); // EMBAIXO
                }
            }
        }
    }
}

void danoAnimacao(Personagem &player, int mapa[13][15], int mapaBomba[13][15], long int tempoBomba, long int tempoAtual){
    if(tempoAtual - tempoBomba < 2500){
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 15; ++j) {
                if(mapa[i][j] == player.valorMapa and (mapaBomba[i][j] == FOGO1 or mapaBomba[i][j] == FOGO2)){
                    if(tempoAtual - tempoBomba < 1600){
                        player.posicao.destino.h = 0;
                        player.posicao.destino.w = 0;
                    }
                    else if(tempoAtual - tempoBomba < 1700){
                        player.posicao.destino.h = 40;
                        player.posicao.destino.w = 40;
                    }
                    else if(tempoAtual - tempoBomba < 1800){
                        player.posicao.destino.h = 0;
                        player.posicao.destino.w = 0;
                    }
                    else if(tempoAtual - tempoBomba < 1900){
                        player.posicao.destino.h = 40;
                        player.posicao.destino.w = 40;
                    }
                    else if(tempoAtual - tempoBomba < 2000){
                        player.posicao.destino.h = 0;
                        player.posicao.destino.w = 0;
                    }
                    else if(tempoAtual - tempoBomba < 2100){
                        player.posicao.destino.h = 40;
                        player.posicao.destino.w = 40;
                    }
                    else if(tempoAtual - tempoBomba < 2200){
                        player.posicao.destino.h = 0;
                        player.posicao.destino.w = 0;
                    }
                    else if(tempoAtual - tempoBomba < 2300){
                        player.posicao.destino.h = 40;
                        player.posicao.destino.w = 40;
                    }
                    else if(tempoAtual - tempoBomba < 2400){
                        player.posicao.destino.h = 0;
                        player.posicao.destino.w = 0;
                    }
                    else if(tempoAtual - tempoBomba < 2500){
                        player.posicao.destino.h = 40;
                        player.posicao.destino.w = 40;
                    }
                }
            }
        }
    }
}

void verificaVidaPlayer(int mapa[13][15], int mapaBomba[13][15], Personagem &player, int valorFogo, bool &dano){
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 15; ++j) {
            if(mapa[i][j] == player.valorMapa and mapaBomba[i][j] == valorFogo){
                player.vida -= 1;
                dano = true;
                if(player.vida == 0){
                    mapa[i][j] = VAZIO;
                }
            }
        }
    }
}

void imprimeVidaPlayer1(Personagem player1, Componentes numeros, SDL_Renderer *renderizador, SDL_Texture *personagens){
    int aux = 1356 - 339 * (player1.vida + 1);
    numeros.posicao.origem = {aux, 0, 339, 480};
    numeros.posicao.destino = {80, 540, 20, 40};
    SDL_RenderCopy(renderizador, numeros.imagem, &numeros.posicao.origem, &numeros.posicao.destino);

    SDL_Rect origem = {32, 0, 32, 32};
    SDL_Rect destino = {40, 545, 35, 35};
    SDL_RenderCopy(renderizador, personagens, &origem, &destino);
}

void imprimeVidaPlayer2(Personagem player2, Componentes numeros, SDL_Renderer *renderizador, SDL_Texture *personagens){
    int aux = 1356 - 339 * (player2.vida + 1);
    numeros.posicao.origem = {aux, 0, 339, 480};
    numeros.posicao.destino = {500, 540, 20, 40};
    SDL_RenderCopy(renderizador, numeros.imagem, &numeros.posicao.origem, &numeros.posicao.destino);

    SDL_Rect origem = {128, 0, 32, 32};
    SDL_Rect destino = {525, 545, 35, 35};
    SDL_RenderCopy(renderizador, personagens, &origem, &destino);
}

bool limpaExplosao(Personagem player, int mapaBomba[13][15], long int tempoAtual){
    if(tempoAtual - player.bomba.tempoBomba > 2500){
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 15; ++j) {

                if(mapaBomba[i][j] == player.fogoMapa){
                    mapaBomba[i][j] = VAZIO;
                }
            }
        }
        return true;
    }
    else{
        return false;
    }
}

void explodeBomba1(Personagem &player1, Personagem &player2, int mapa[13][15], int mapaBomba[13][15], long int tempoAtual){
    bombaAnimacao(player1, tempoAtual);
    bombaExplosao(player1, tempoAtual, mapa, mapaBomba);
    danoAnimacao(player1, mapa, mapaBomba, player1.bomba.tempoBomba, tempoAtual);
    danoAnimacao(player2, mapa, mapaBomba, player1.bomba.tempoBomba, tempoAtual);
    if(player1.danoBomba1 == false){
        verificaVidaPlayer(mapa, mapaBomba, player1, player1.fogoMapa, player1.danoBomba1);
    }
    if(player2.danoBomba1 == false){
        verificaVidaPlayer(mapa, mapaBomba, player2, player1.fogoMapa, player2.danoBomba1);
    }
    if(limpaExplosao(player1, mapaBomba, tempoAtual) == true){
        player1.danoBomba1 = false;
        player2.danoBomba1 = false;
        player1.bomba.plantada = false;
        player1.bomba.quantidade += 1;
    }
}

void explodeBomba2(Personagem &player2, Personagem &player1, int mapa[13][15], int mapaBomba[13][15], long int tempoAtual){
    bombaAnimacao(player2, tempoAtual);
    bombaExplosao(player2, tempoAtual, mapa, mapaBomba);
    danoAnimacao(player2, mapa, mapaBomba, player2.bomba.tempoBomba, tempoAtual);
    danoAnimacao(player1, mapa, mapaBomba, player2.bomba.tempoBomba, tempoAtual);
    if(player2.danoBomba2 == false){
        verificaVidaPlayer(mapa, mapaBomba, player2, player2.fogoMapa, player2.danoBomba2);
    }
    if(player1.danoBomba2 == false){
        verificaVidaPlayer(mapa, mapaBomba, player1, player2.fogoMapa, player1.danoBomba2);
    }
    if(limpaExplosao(player2, mapaBomba, tempoAtual) == true){
        player2.danoBomba2 = false;
        player1.danoBomba2 = false;
        player2.bomba.plantada = false;
        player2.bomba.quantidade += 1;
    }
}

bool verificaFimDeJogo(Personagem &player1, Personagem &player2){
    if(player1.vida == 0 or player2.vida == 0){
        return true;
    }
    return false;
}

void imprimeFimDeJogo(Personagem &player1, Personagem &player2, Componentes &empate, Componentes &player1Vence, Componentes &player2Vence, SDL_Renderer *renderizador, SDL_Cursor *cursor, bool &abreMenuPrincipal, bool &jogaJogo, bool &termina){
    if(player1.vida == 0 and player2.vida == 0){
        SDL_RenderCopy(renderizador, empate.imagem, &empate.posicao.origem, &empate.posicao.destino);
    }
    else if(player1.vida == 0){
        SDL_RenderCopy(renderizador, player2Vence.imagem, &player1Vence.posicao.origem, &player1Vence.posicao.destino);
    }
    else if(player2.vida == 0){
        SDL_RenderCopy(renderizador, player1Vence.imagem, &player2Vence.posicao.origem, &player2Vence.posicao.destino);
    }
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_MOUSEMOTION:{
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x > 223 and x < 375 and y > 480 and y < 533){
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
                empate.posicao.origem.x = 600;
                player1Vence.posicao.origem.x = 600;
                player2Vence.posicao.origem.x = 600;
            }
            else{
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                SDL_SetCursor(cursor);
                empate.posicao.origem.x = 0;
                player1Vence.posicao.origem.x = 0;
                player2Vence.posicao.origem.x = 0;
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x > 178 and x < 421 and y > 473 and y < 515){
                jogaJogo = false;
                abreMenuPrincipal = true;
            }
            break;

        }
        case SDL_QUIT:{
            termina = true;
            break;
        }
        default:
            break;
        }
    }
}
