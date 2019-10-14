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

void imprimeMapa(Componentes fogo, Componentes bomba, Componentes caixa, Componentes parede, Componentes fundo, Personagem player, Personagem bot, SDL_Renderer *renderizador, int mapa[13][15], int mapaBomba[13][15]){
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
                player.posicao.destino = {posicaoX, posicaoY, 40, 40};
                SDL_RenderCopy(renderizador, player.imagem, &player.posicao.origem, &player.posicao.destino);
            }
            else if(mapa[i][j] == BOT){
                bot.posicao.destino = {posicaoX, posicaoY, 40, 40};
                SDL_RenderCopy(renderizador, bot.imagem, &bot.posicao.origem, &bot.posicao.destino);
            }
            else if(mapaBomba[i][j] == BOMBA){
                bomba.posicao.destino = {posicaoX, posicaoY, 40, 40};
                SDL_RenderCopy(renderizador, bomba.imagem, &bomba.posicao.origem, &bomba.posicao.destino);
            }
            else if(mapaBomba[i][j] == FOGO){
                fogo.posicao.destino = {posicaoX, posicaoY, 40, 40};
                SDL_RenderCopy(renderizador, fogo.imagem, &fogo.posicao.origem, &fogo.posicao.destino);
            }
        }
    }
    SDL_RenderPresent(renderizador);
    SDL_RenderClear(renderizador);
    SDL_Delay(1000/40);
}

void validaMovimento(int mapa[13][15], int indiceX, int indiceY, int adicionalX, int adicionalY){
    if(mapa[indiceX + adicionalX][indiceY + adicionalY] == VAZIO){
        mapa[indiceX + adicionalX][indiceY + adicionalY] = PLAYER1;
        mapa[indiceX][indiceY] = VAZIO;
    }
}

void plantaBomba(Personagem &player, int mapaBomba[13][15], long int &tempoBomba, int indiceX, int indiceY){
    if(player.bombas != 0 and player.bomba == false){
        player.bomba = true;
        mapaBomba[indiceX][indiceY] = BOMBA;
        player.bombas -= 1;
        tempoBomba = SDL_GetTicks();
    }
}

void movimentaPersonagem(bool &termina, long int &tempoBomba, Personagem &player, int mapa[13][15], int mapaBomba[13][15]){
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
        else if(evento.type == SDL_KEYDOWN){
            if(evento.key.keysym.sym == SDLK_SPACE){
                plantaBomba(player, mapaBomba, tempoBomba, indiceX, indiceY);
            }
            if(evento.key.keysym.sym == SDLK_s){
                player.posicao.origem = {32, 0, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, 1, 0);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_w){
                player.posicao.origem = {32, 96, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, -1, 0);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_a){
                player.posicao.origem = {32, 32, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, 0, -1);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_d){
                player.posicao.origem = {32, 64, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, 0, 1);
                break;
            }
        }
    }
}

void movimentaBot(int mapa[13][15], Personagem &bot, int mapaBomba[13][15]){
    int direcao = rand()%4;
    int passos = rand() % 15 + 3;
    cout << direcao << endl;
    int cont = 1;
    while(cont < passos){
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 15; ++j) {
                if(mapa[i][j] == BOT){
                    if(direcao == 0){ // DIREITA
                        if(mapa[i][j+1] == VAZIO){
                            bot.posicao.origem = {128, 0, 32, 32};
                            mapa[i][j+1] = BOT;
                            mapa[i][j] = VAZIO;
                        }
                    }
                    else if(direcao == 1){ // ESQUERDA
                        if(mapa[i][j-1] == VAZIO){
                            bot.posicao.origem = {128, 32, 32, 32};
                            mapa[i][j-1] = BOT;
                            mapa[i][j] = VAZIO;
                        }
                    }
                    else if(direcao == 2){ // CIMA
                        if(mapa[i-1][j] == VAZIO){
                            bot.posicao.origem = {128, 96, 32, 32};
                            mapa[i-1][j] = BOT;
                            mapa[i][j] = VAZIO;
                        }
                    }
                    else if(direcao == 3){ // BAIXO
                        if(mapa[i+1][j] == VAZIO){
                            bot.posicao.origem = {128, 64, 32, 32};
                            mapa[i+1][j] = BOT;
                            mapa[i][j] = VAZIO;
                        }
                    }
                }
            }
        }
        cont++;
    }
}

void bombaAnimacao(Componentes &bomba, long int tempoInicio, long int tempoAtual){
    if(tempoAtual - tempoInicio == 100 ){
        bomba.posicao.origem = {22, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 200){
        bomba.posicao.origem = {44, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 300 ){
        bomba.posicao.origem = {66, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 400 ){
        bomba.posicao.origem = {88, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 500 ){
        bomba.posicao.origem = {110, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 700 ){
        bomba.posicao.origem = {132, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 800 ){
        bomba.posicao.origem = {154, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 900 ){
        bomba.posicao.origem = {176, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 1000 ){
        bomba.posicao.origem = {198, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 1100 ){
        bomba.posicao.origem = {220, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 1200 ){
        bomba.posicao.origem = {198, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 1300 ){
        bomba.posicao.origem = {220, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 1400 ){
        bomba.posicao.origem = {198, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 1500 ){
        bomba.posicao.origem = {220, 0, 22, 22};
    }
}

void validaExplosao(int mapa[13][15], int mapaBomba[13][15], int indiceX, int indiceY, int adicionalX, int adicionalY){
    int cont = 1;
    while(cont < 3){
        if(mapa[indiceX + adicionalX * cont][indiceY + adicionalY * cont] != PAREDE){
            mapaBomba[indiceX + adicionalX * cont][indiceY + adicionalY * cont] = FOGO;
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

bool explodeBomba(long int tempoInicio, int mapa[13][15], int mapaBomba[13][15], long int tempoAtual){
    if(tempoAtual - tempoInicio > 1500 ){ // milisegundos
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 15; ++j) {
                if(mapaBomba[i][j] == BOMBA){
                    mapaBomba[i][j] = FOGO;
                    validaExplosao(mapa, mapaBomba, i, j, 0, 1); // DIREITA
                    validaExplosao(mapa, mapaBomba, i, j, 0, -1); // ESQUERDA
                    validaExplosao(mapa, mapaBomba, i, j, -1, 0); // EM CIMA
                    validaExplosao(mapa, mapaBomba, i, j, +1, 0); // EMBAIXO
                }
            }
        }
        return true;
    }
    else{
        return false;
    }
}

void verificaVidaPlayer(int mapa[13][15], int mapaBomba[13][15], Personagem &player){
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 15; ++j) {
            if(mapa[i][j] == PLAYER1 and mapaBomba[i][j] == FOGO){
                if(player.vida == 1){
                    mapa[i][j] = VAZIO;
                }
                else{
                    player.vida -= 1;
                }
            }
        }
    }
    //cout << player1.vida << endl;
    /*if(mapa[i][j] == PLAYER1 and player1.vida == 0){
        mapa[i][j] = VAZIO;
    }*/
    //cout << "TESTE" << endl;
}

bool limpaExplosao(int mapaBomba[13][15], long int tempoInicio, long int tempoAtual){
    if(tempoAtual - tempoInicio > 2500){
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 15; ++j) {

                if(mapaBomba[i][j] == FOGO){
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
