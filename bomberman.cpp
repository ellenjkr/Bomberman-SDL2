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
                player1.posicao.destino = {posicaoX, posicaoY, 40, 40};
                SDL_RenderCopy(renderizador, player1.imagem, &player1.posicao.origem, &player1.posicao.destino);
            }
            else if(mapa[i][j] == PLAYER2){
                player2.posicao.destino = {posicaoX, posicaoY, 40, 40};
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

void validaMovimento(int mapa[13][15], int indiceX, int indiceY, int adicionalX, int adicionalY, int player){
    if(mapa[indiceX + adicionalX][indiceY + adicionalY] == VAZIO){
        mapa[indiceX + adicionalX][indiceY + adicionalY] = player;
        mapa[indiceX][indiceY] = VAZIO;
    }
}

void plantaBomba(Personagem &player, int mapaBomba[13][15], long int &tempoBomba, int indiceX, int indiceY){
    if(player.bomba.quantidade != 0 and player.bomba.plantada == false){
        player.bomba.plantada = true;
        mapaBomba[indiceX][indiceY] = player.bomba.valorMapa;
        player.bomba.quantidade -= 1;
        tempoBomba = SDL_GetTicks();
    }
}

void movimentaPlayers(bool &termina, long int &tempoBomba, Personagem &player, long int &tempoBomba2, Personagem &player2, int mapa[13][15], int mapaBomba[13][15]){
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
        else if(evento.type == SDL_KEYDOWN){
            if(evento.key.keysym.sym == SDLK_SPACE){
                plantaBomba(player, mapaBomba, tempoBomba, indiceX, indiceY);
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
                plantaBomba(player2, mapaBomba, tempoBomba2, indiceX2, indiceY2);
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

void movimentaPlayer2(bool &termina, long int &tempoBomba2, Personagem &player2, int mapa[13][15], int mapaBomba[13][15]){
    SDL_Event evento;
    int indiceX = 0;
    int indiceY = 0;
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 15; ++j) {
            if(mapa[i][j] == PLAYER2){
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
            if(evento.key.keysym.sym == SDLK_KP_4){
                plantaBomba(player2, mapaBomba, tempoBomba2, indiceX, indiceY);
            }
            if(evento.key.keysym.sym == SDLK_KP_2){
                player2.posicao.origem = {128, 0, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, 1, 0, PLAYER2);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_KP_5){
                player2.posicao.origem = {128, 96, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, -1, 0, PLAYER2);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_KP_1){
                player2.posicao.origem = {128, 32, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, 0, -1, PLAYER2);
                break;
            }
            else if(evento.key.keysym.sym == SDLK_KP_3){
                player2.posicao.origem = {128, 64, 32, 32};
                validaMovimento(mapa, indiceX, indiceY, 0, 1, PLAYER2);
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

void bombaAnimacao(Personagem &player, long int tempoInicio, long int tempoAtual){
    if(tempoAtual - tempoInicio == 100 ){
        player.bomba.posicao.origem = {22, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 200){
        player.bomba.posicao.origem = {44, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 300 ){
        player.bomba.posicao.origem = {66, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 400 ){
        player.bomba.posicao.origem = {88, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 500 ){
        player.bomba.posicao.origem = {110, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 700 ){
        player.bomba.posicao.origem = {132, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 800 ){
        player.bomba.posicao.origem = {154, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 900 ){
        player.bomba.posicao.origem = {176, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 1000 ){
        player.bomba.posicao.origem = {198, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 1100 ){
        player.bomba.posicao.origem = {220, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 1200 ){
        player.bomba.posicao.origem = {198, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 1300 ){
        player.bomba.posicao.origem = {220, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 1400 ){
        player.bomba.posicao.origem = {198, 0, 22, 22};
    }
    else if(tempoAtual - tempoInicio < 1500 ){
        player.bomba.posicao.origem = {220, 0, 22, 22};
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

void explodeBomba(Personagem player, long int tempoInicio, long int tempoAtual, int mapa[13][15], int mapaBomba[13][15]){
    if(tempoAtual - tempoInicio > 1500 ){ // milisegundos
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 15; ++j) {
                if(mapaBomba[i][j] == player.bomba.valorMapa){
                    mapaBomba[i][j] = FOGO;
                    validaExplosao(mapa, mapaBomba, i, j, 0, 1); // DIREITA
                    validaExplosao(mapa, mapaBomba, i, j, 0, -1); // ESQUERDA
                    validaExplosao(mapa, mapaBomba, i, j, -1, 0); // EM CIMA
                    validaExplosao(mapa, mapaBomba, i, j, +1, 0); // EMBAIXO
                }
            }
        }
    }
}

void verificaVidaPlayer(int mapa[13][15], int mapaBomba[13][15], Personagem &player){
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 15; ++j) {
            if(mapa[i][j] == player.valorMapa and mapaBomba[i][j] == FOGO){
                if(player.vida == 0){
                    mapa[i][j] = VAZIO;
                }
                else{
                    player.dano += 1;
                }
            }
        }
    }
    if(player.dano == 1){
        player.vida -= 1;
    }
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
