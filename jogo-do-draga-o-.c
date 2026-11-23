#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RODADAS_FACIL 20
#define RODADAS_MEDIO 15
#define RODADAS_DIFICIL 6
#define PONTOS_INICIAIS 1000
#define VIDA_JOGADOR 40
#define VIDA_DRAGAO 60
#define POCOES_INICIAIS 2
#define CURA_POCAO 12
#define DANO_ATAQUE 10

// ---------- LEITURA SEGURA DE NUMEROS INTEIROS ----------
int lerInteiro() {
    int valor;

    while (scanf("%d", &valor) != 1) {
        printf("Entrada invalida! So sao aceitos numeros. Tente novamente: ");

        // limpa o buffer ate o fim da linha
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // descarta qualquer resto da linha (ex: "3abc" ou "2 5")
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    return valor;
}

int main() {
    srand(time(0));

    // ---------- CABECALHO: DRAGAO ASCII ART ----------
    printf("\n");
    printf("                   /|                        |\\\n");
    printf("                  ; :                        : :\n");
    printf("                  | Y,                      ,P |\n");
    printf("                  |  Yb.        __        ,dP  |\n");
    printf("                  l\\  YMMb,_ _,/  \\,_ _,dMMP  /f\n");
    printf("                   j;  `YMMP'  `--'  `YMMP'  ;j\n");
    printf("                   : \\   YP`-._    _.-'YP   / ;\n");
    printf("                    \\ `\\,  _,\\_    _/,_  ,/' /\n");
    printf("                     `,_,   \\`o>  <o'/   ,_,\n");
    printf("                         `\\            /\n");
    printf("                           |  _    _  |\n");
    printf("                           / 88b  d88 \\\n");
    printf("                           \\ `8P  Y8' /``-.\n");
    printf("                            `\\,    ,/      \\\n");
    printf("                             _`----'        \\\n");
    printf("                          _.'/ '          `, \\\n");
    printf("                        .'_,'_..._          \\ ;\n");
    printf("                      .',/.dMMMMMMb. |      /  \\\n");
    printf("                    .'./.MMMMMMMMMMM ;     /    ;\n");
    printf("                   / /.MMMMMMMMMMMMM/     /     ;\n");
    printf("                  | ;dMMMMMMMMMMMP/'   ,/'       ;\n");
    printf("                  |/dMMMMMMMMMP'     .'          |\n");
    printf("                  ;dMMMMMMMMM|     _/            |\n");
    printf("                 ;dMMMMMMMMMMb_|_| /;            ;\\,\n");
    printf("                 dMMMMMMMMMMMM`M`M`;.---..      '   `\\,\n");
    printf("                :MMMMMMMMMMMMMMMMP/'     `\\            \\\n");
    printf("               /|MMMMMMMMMMMMMMP/          \\    __      `.\n");
    printf("              / |MMMMMMMMMMMMMM|            |.-'  `-._    \\         .'\n");
    printf("             ;  ;MMMMMMMMMMMMMM|            :         `-._ `-.     /  _\n");
    printf("             |   ;MMMMMMMMMMMMM;            |             `-. `-.._.'/\n");
    printf("              \\   `\\YMMMMMMMMP/'\\           |                `~~----\n");
    printf("               `-._, ``YMMMP'_.-'\\          ;_\n");
    printf("                 |      /         `-.,_./     7\n");
    printf("                _/    `\\,            /      _\n");
    printf("             ,-' ,  ,   /         _.'      /      fsc\n");
    printf("            (_(_(__(__.'       ,-'        /\n");
    printf("                              (__(__(_('/\n");
    printf("\n");
    printf("              B E M - V I N D O   A O\n");
    printf("               DUELO CONTRA O DRAGAO!\n");
    printf("\n");
    printf("       =====================================\n\n");

    // ---------- VARIAVEIS PRINCIPAIS ----------
    long partidas = 0;
    int jogarnovamente = 1;

    while (jogarnovamente) {

        int vidajogador = VIDA_JOGADOR;
        int vidadragao = VIDA_DRAGAO;
        short pocoes = POCOES_INICIAIS;
        double pontos = PONTOS_INICIAIS;
        long totaldano = 0;
        int venceu = 0;
        int perdeu = 0;
        int opcao;
        int totalderodadas;
        int rodadasusadas = 0;
        short nivel;

        partidas++;

        printf("===== Partida %ld =====\n", partidas);

        // ---------- ESCOLHA DO NIVEL ----------
        printf("Qual o nivel de dificuldade?\n");
        printf("(1) Facil (2) Medio (3) Dificil\n\n");
        printf("Escolha: ");
        nivel = (short)lerInteiro();

        switch (nivel) {
            case 1:
                totalderodadas = RODADAS_FACIL;
                break;

            case 2:
                totalderodadas = RODADAS_MEDIO;
                break;

            default:
                totalderodadas = RODADAS_DIFICIL;
                break;
        }

        printf("\nVoce tem %d rodadas para derrotar o dragao. Boa sorte!\n\n", totalderodadas);

        // ---------- RODADAS DO JOGO ----------
        for (int i = 1; i <= totalderodadas; i++) {

            printf("-> Rodada %d de %d\n", i, totalderodadas);

            double percentual = (double)vidadragao / VIDA_DRAGAO * 100;

            printf("Voce:   [");

            for (int j = 1; j <= vidajogador / 5; j++) {
                printf("#");
            }

            printf("] %d\n", vidajogador);

            printf("Dragao: [");

            for (int j = 1; j <= vidadragao / 5; j++) {
                printf("#");
            }

            printf("] %d (%.2f%% da vida)\n", vidadragao, percentual);

            printf("Diferenca de vida entre voces: %d\n",
                   abs(vidajogador - vidadragao));

            printf("\n1 - Atacar\n");
            printf("2 - Defender\n");
            printf("3 - Usar pocao (%d restantes)\n", pocoes);
            printf("Qual e a sua acao? ");

            opcao = lerInteiro();

            // ---------- VALIDACAO DA OPCAO ----------
            if (opcao < 1) {
                printf("Opcao invalida! Escolha entre 1 e 3.\n\n");
                i--;
                continue;
            } else if (opcao > 3) {
                printf("Opcao invalida! Escolha entre 1 e 3.\n\n");
                i--;
                continue;
            }

            rodadasusadas = i;

            // ---------- DANO DO DRAGAO ----------
            int danodragao = rand() % 8 + 4;

            double furia = 1.0;

            if (percentual < 30) {
                furia = 1.5;
                printf("O dragao esta FURIOSO!\n");
            }

            danodragao = (int)(danodragao * furia);

            // ---------- DANO DO JOGADOR ----------
            int golpe = DANO_ATAQUE + rand() % 5;

            // ---------- ACAO DO JOGADOR ----------
            switch (opcao) {

                case 1:
                    vidadragao = vidadragao - golpe;
                    printf("Voce atacou e causou %d de dano!\n", golpe);
                    break;

                case 2:
                    danodragao = danodragao / 2;
                    printf("Voce levantou o escudo! O dano do dragao cai pela metade.\n");
                    break;

                case 3: {
                    int temPocao = pocoes > 0;

                    if (!temPocao) {
                        printf("Suas pocoes acabaram! Voce perdeu a vez.\n");
                    } else {
                        vidajogador = vidajogador + CURA_POCAO;
                        pocoes = pocoes - 1;

                        printf("Voce bebeu uma pocao e recuperou %d de vida!\n",
                               CURA_POCAO);
                    }

                    break;
                }
            }

            // ---------- ATAQUE DO DRAGAO ----------
            int dragaovivo = vidadragao > 0;

            if (dragaovivo) {

                vidajogador = vidajogador - danodragao;
                totaldano = totaldano + danodragao;

                double pontosperdidos = danodragao / 2.0;
                pontos = pontos - pontosperdidos;

                printf("O dragao atacou e causou %d de dano!\n", danodragao);
                printf("Voce perdeu %.2f pontos. Agora tem %.2f\n",
                       pontosperdidos, pontos);
            }

            printf("\n");

            // ---------- SEPARADOR VISUAL AO FINAL DE CADA RODADA ----------
            printf("       *****************************************\n");
            printf("       *       (  )       (  )       (  )      *\n");
            printf("       *        )(         )(         )(       *\n");
            printf("       *       (  )       (  )       (  )      *\n");
            printf("       *                                       *\n");
            printf("       *            FIM DA RODADA %02d           *\n", i);
            printf("       *                                       *\n");
            printf("       *****************************************\n");
            printf("\n");
            fflush(stdout);

            // ---------- VERIFICACAO DO RESULTADO ----------
            venceu = vidadragao <= 0;
            perdeu = vidajogador <= 0;

            if (venceu) {
                break;
            } else if (perdeu) {
                break;
            }
        }

        // ---------- RESULTADO DA PARTIDA ----------
        printf("-------- Resultado da partida --------\n");

        printf("Rodadas jogadas: %d de %d | Dano total recebido: %ld\n",
               rodadasusadas, totalderodadas, totaldano);

        if (venceu) {

            printf("\n");
            printf("       ___________\n");
            printf("      '._==_==_=_.'\n");
            printf("      .-\\:      /-.\n");
            printf("     | (|:.     |) |\n");
            printf("      '-|:.     |-'\n");
            printf("        \\::.    /\n");
            printf("         '::. .'\n");
            printf("           ) (\n");
            printf("         _.' '._\n");
            printf("        '-------'\n");

            printf("\nParabens! Voce derrotou o dragao!\n");

            double usado = (double)rodadasusadas / totalderodadas * 100;
            float estrelas = pontos / 200;

            printf("Voce usou %.2f%% das rodadas.\n", usado);

            printf("Voce fez %.2f pontos (%.1f estrelas). Ate a proxima!\n\n",
                   pontos, estrelas);

        } else if (perdeu) {

            printf("\n   \\|/ ____ \\|/\n");
            printf("   @~/ ,. \\~@\n");
            printf("   /_( \\__/ )_\\\n");
            printf("    \\__U_/\n");

            printf("\nVoce perdeu! O dragao venceu o duelo.\n");
            printf("Voce fez %.2f pontos. Tente novamente!\n\n", pontos);

        } else {

            printf("\nAs rodadas acabaram e o dragao fugiu voando...\n");
            printf("Ninguem venceu. Voce fez %.2f pontos.\n\n", pontos);
        }

        // ---------- JOGAR NOVAMENTE ----------
        int resposta;

        printf("Jogar de novo? (1) Sim (2) Nao\n");
        printf("Escolha: ");

        resposta = lerInteiro();

        jogarnovamente = resposta == 1;

        if (!jogarnovamente) {
            printf("\nVoce jogou %ld partida(s). Obrigado por jogar!\n",
                   partidas);
        } else {
            printf("\n");
        }
    }

    return 0;
}
