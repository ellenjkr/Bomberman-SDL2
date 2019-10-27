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

void criaComponentes(SDL_Renderer *renderizador, Componentes &fundo, Componentes &caixa, Componentes &parede, Componentes &fogo, Componentes &botaoHome, Componentes &botaoRestart){
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

void movimentaPlayers(bool &termina, Personagem &player, Personagem &player2, int mapa[13][15], int mapaBomba[13][15]){
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

void movimentaBot(int mapa[13][15], Personagem &bot){
    int direcao = rand()%4;
    int passos = rand() % 15 + 3;
    int cont = 1;
    while(cont < passos){
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 15; ++j) {
                if(mapa[i][j] == PLAYER2){
                    if(direcao == 0){ // DIREITA
                        validaMovimento(mapa, i, j, 0, 1, PLAYER2);
                        bot.posicao.origem = {128, 0, 32, 32};
                    }
                    else if(direcao == 1){ // ESQUERDA
                        validaMovimento(mapa, i, j, 0, -1, PLAYER2);
                        bot.posicao.origem = {128, 32, 32, 32};
                    }
                    else if(direcao == 2){ // CIMA
                        validaMovimento(mapa, i, j, -1, 0, PLAYER2);
                        bot.posicao.origem = {128, 96, 32, 32};
                    }
                    else if(direcao == 3){ // BAIXO
                        validaMovimento(mapa, i, j, 1, 0, PLAYER2);
                        bot.posicao.origem = {128, 64, 32, 32};
                    }
                }
            }
        }
        cont++;
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
