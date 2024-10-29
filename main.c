#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Nave
{
    char nome[25];
    int ataque;
    int defesa;
    int energia;
    int velocidade;
};

struct Nave naves[4] = {
        {"Astro", 18, 15, 120, 50},
        {"Apollo", 25, 10, 100, 40},
        {"Sombra", 18, 15, 150, 48},
        {"Umbra", 19, 15, 105, 45}
        };


void ataque(struct Nave *nave1, struct Nave *nave2, int acao);
int P1(void);
int P2(void);
void status(struct Nave nave1, struct Nave nave2);
int velocidade(struct Nave nave1, struct Nave nave2);
int vitoria(struct Nave nave1, struct Nave nave2);
int main(void)
{
    srand(time(0));
    int escolha; //Armazena a escolha da nave
    int acaoJogador; //Armazena qual ação o jogador tera
    int acaoComputador; //Armazena a ação do computador;
    int turno;

    struct Nave jogador;
    struct Nave computador;
    
    
    printf("| %-10s | %-5s | %-5s | %-5s| %-5s\n", "Nome", "Ataque", "Defesa", "Velocidade","Energia");
    printf("----------------------------------------------\n");
    for (int i = 0; i < 4; i++) {
        printf("| %-10s | %-6d | %-6d | %-5d\n",naves[i].nome, naves[i].ataque, naves[i].defesa, naves[i].velocidade ,naves[i].energia);
        
    }
    do {
        printf("Escolha sua nave: \n");
        printf("1. Astro\n2. Apollo\n3. Sombra\n4. Umbra\n(Aperte 5 para sair)\n");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            jogador = naves[0];
            break;
        case 2:
            jogador = naves[1];
            break;
        case 3:
            jogador = naves[2];
            break;
        case 4:
            jogador = naves[3];
            break;
        case 5:
            printf("Encerrando programa...\n");
            return 0;
            break;
        
        default:
            printf("opcao invalida!\n");
            break;
        }
        
        //Seleciona uma da opções aleatoriamente e previne matchup espelhadas
        int index = rand() % 4;
        while (index == escolha - 1) {
            index = rand() % 4;
        }
        computador = naves[index];
        system("cls");

        //Inicio da batalha
        do
        {
            status(jogador, computador);
            acaoJogador = P1();
            acaoComputador = P2();
            if(acaoJogador && acaoComputador == 2) {
                    printf("Ninguem atacou nesse turno!\n");
                    continue;
                }
            turno = velocidade(jogador, computador);
            if (turno == 0) {
                if (acaoJogador == 1) 
                    ataque(&jogador, &computador, acaoComputador);
                if (acaoJogador == 2)
                    ataque(&computador, &jogador, acaoJogador);
            }
            else {
                if (acaoComputador == 1)
                    ataque(&computador, &jogador, acaoJogador);
                if (acaoComputador == 2)
                    ataque(&jogador, &computador, acaoComputador);
            }
            if (vitoria(jogador, computador) == 0) {
                status(jogador, computador);
                printf("Voce venceu!\n");
                return 0;
            }
            if (vitoria(jogador, computador) == 1) {
                status(jogador, computador);
                printf("Voce Perdeu, mais sorte da proxima vez!\n");
                return 0;
            }
            

        } while (jogador.energia != 0 && computador.energia != 0 );
    } while(escolha != 5);
    return 0;
}

int P1(void) {
    int acaoV; //acaoV para identifica e nao confundir a variavel com a função
    do {
        printf("1. Atacar\n");
        printf("2. Defender\n");
        scanf("%d", &acaoV);
        switch (acaoV)
        {
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        
        default:
            printf("Opcao invalida\n");
            break;
        }
    } while(acaoV != 1 || acaoV != 2);  
}

int P2(void) {
    return rand() % 2;
}

void ataque(struct Nave *nave1, struct Nave *nave2, int acao) {
    int dano;
    if (acao == 1) { //Ataca normalmente
        nave2->energia -= nave1->ataque;
        nave2->velocidade -= 2;
        printf("%s ataca %s causando %d de dano.\n", nave1->nome, nave2->nome, nave1->ataque);
        return;
    }
    else {
        dano = nave1->ataque - nave2->defesa;
        nave2->velocidade - 1;
        if (dano < 0)
            dano = 0;
        nave2->energia -= dano;
        if (nave2->energia < 0)
            nave2->energia = 0;
        printf("%s ataca %s causando %d de dano.\n", nave1->nome, nave2->nome, dano);
    }
}

int velocidade(struct Nave nave1, struct Nave nave2) {
    if(nave1.velocidade > nave2.velocidade)
        return 0;
    else if (nave1.velocidade <  nave2.velocidade)
        return 1;
    else 
        return 0;
}
void status(struct Nave nave1, struct Nave nave2) {
    printf("Energia Jogador '%s': %d\n",nave1.nome, nave1.energia);
    printf("Energia Computador '%s': %d\n",nave2.nome, nave2.energia);
}

int vitoria(struct Nave nave1, struct Nave nave2) {
    if (nave1.energia == 0) {
        return 1;
    }
    if (nave2.energia == 0) {
        return 0;
    }
    return -1;
}