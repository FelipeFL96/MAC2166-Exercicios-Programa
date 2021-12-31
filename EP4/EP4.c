/***************************************************************/
/**                                                           **/
/**   Felipe Fernandes de Lima                   9345321      **/
/**   Exercício-Programa 04                                   **/
/**   Professor: Alan Mitchell Durham                         **/
/**   Turma: 04                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <string.h>
#define MAXLINHA 400
#define MAXCOLUNA 400
#define JANELA_MAX 50
#define MAX_NAME 256 /* tamanho maximo para nome de arquivo */

/*Funçõees para leitura/gravação*/
int le_pgm(char*, int[MAXLINHA][MAXCOLUNA], int*, int*, int*);
int grava_pgm(char*, int[MAXLINHA][MAXCOLUNA], int, int, int);
/*Funçõees de Edição*/
void negativo(int[MAXLINHA][MAXCOLUNA], int, int);
void rebatimentoVertical  (int[MAXLINHA][MAXCOLUNA], int, int);
void rebatimentoHorizontal(int[MAXLINHA][MAXCOLUNA], int, int);
void rotacao (int[MAXLINHA][MAXCOLUNA], int*, int*);
void corte   (int[MAXLINHA][MAXCOLUNA], int*, int*, int, int, int, int);
/*Funçõees de Filtro*/
void filtroMediana  (int[MAXLINHA][MAXCOLUNA], int, int, int);
void filtroMedia    (int[MAXLINHA][MAXCOLUNA], int, int, int);
void filtroErosao   (int[MAXLINHA][MAXCOLUNA], int, int, int);
void filtroDilatacao(int[MAXLINHA][MAXCOLUNA], int, int, int);
void filtroBorda1   (int[MAXLINHA][MAXCOLUNA], int, int, int, int);
void filtroBorda2   (int[MAXLINHA][MAXCOLUNA], int, int, int, int);
void filtroBorda3   (int[MAXLINHA][MAXCOLUNA], int, int, int, int);
/*Funçõees Auxiliares*/
void imprime_matriz (int[MAXLINHA][MAXCOLUNA], int, int);
void iguala_matriz  (int[MAXLINHA][MAXCOLUNA], int[MAXLINHA][MAXCOLUNA], int, int);
int acha_maior      (int[MAXLINHA][MAXCOLUNA], int, int);
int conta_posicoes  (char[MAX_NAME]);
void compara_matriz (int[MAXLINHA][MAXCOLUNA], int, int, int[MAXLINHA][MAXCOLUNA], int, int);
void janela         (int[MAXLINHA][MAXCOLUNA], int, int, int, int, int, int[MAXLINHA*MAXCOLUNA], int*);
void ordem_crescente(int [MAXLINHA*MAXCOLUNA], int);
int  mediana        (int [MAXLINHA*MAXCOLUNA], int);
int  media          (int [MAXLINHA*MAXCOLUNA], int);
int  menor_vizinho  (int [MAXLINHA*MAXCOLUNA], int);
int  maior_vizinho  (int [MAXLINHA*MAXCOLUNA], int);
void limiarizacao   (int[MAXLINHA][MAXCOLUNA], int, int, int);

int main(){
    char comando, nome[MAX_NAME];
    /*Variáveis da imagem*/
    int imagem[MAXLINHA][MAXCOLUNA], linhas, colunas, maiorValor, achou_pgm, prox_posicao;
    /*Variáveis para corte*/
    int xsup, ysup, xinf, yinf;
    /*Variáveis para filtros*/
    int larguraJanela, k;
    /*Variáveis para comparação*/
    char nome2[MAX_NAME];
    int imagem2[MAXLINHA][MAXCOLUNA], linhas2, colunas2, maiorValor2;

    comando = 0;
    while(comando != 's'){
        printf("Digite o nome do arquivo de entrada: ");
        scanf("%s", &nome);
        achou_pgm = le_pgm(nome, imagem, &linhas, &colunas, &maiorValor);
        if(achou_pgm == 1)
            printf("Arquivo %s.pgm carregado com sucesso.\n", nome);

        /*Preparação para alteração do nome do arquivo*/
        prox_posicao = conta_posicoes(nome);
        nome[prox_posicao] = '-';

        while((comando != 's') && (achou_pgm == 1)){
            printf("c - carga");
            printf("\nt - exibicao na tela");
            printf("\nn - negativo");
            printf("\nr - rotacao");
            printf("\nv - espelhamento vertical");
            printf("\nh - espelhamento horizontal");
            printf("\nx - corte");
            printf("\ne - filtro da erosao");
            printf("\nd - filtro da dilatacao");
            printf("\nm - filtro da mediana");
            printf("\nz - filtro da media");
            printf("\n1 - filtro de bordas 1");
            printf("\n2 - filtro de bordas 2");
            printf("\n3 - filtro de bordas 3");
            printf("\ng - gravacao");
            printf("\nC - comparacao");
            printf("\na - ajuda");
            printf("\ns - sair");

            printf("\n\nDigite um comando: ");
            scanf(" %c", &comando);

            while((comando != 's') && (comando != 'a')){
                if (comando == 'c'){
                    do{
                        printf("Digite o nome do arquivo de entrada: ");
                        scanf("%s", &nome);
                        achou_pgm = le_pgm(nome, imagem, &linhas, &colunas, &maiorValor);
                        if(achou_pgm == 1)
                            printf("Arquivo %s.pgm carregado com sucesso.\n", nome);
                    }while(achou_pgm == 0);
                    /*Preparação para alteração do nome do arquivo*/
                    prox_posicao = conta_posicoes(nome);
                    nome[prox_posicao] = '-';
                }
                else if(comando == 't'){
                    imprime_matriz(imagem, linhas, colunas);
                    printf("\n");
                }
                else if(comando == 'n'){
                    negativo(imagem, linhas, colunas);
                    printf("Operacao realizada com sucesso.");
                    /*Acrescentando a operação no nome do arquivo*/
                    prox_posicao++;
                    nome[prox_posicao] = 'n';
                }
                else if(comando == 'r'){
                    rotacao(imagem, &linhas, &colunas);
                    printf("Operacao realizada com sucesso.");
                    /*Acrescentando a operação no nome do arquivo*/
                    prox_posicao++;
                    nome[prox_posicao] = 'r';
                }
                else if(comando == 'v'){
                    rebatimentoVertical(imagem, linhas, colunas);
                    printf("Operacao realizada com sucesso.");
                    /*Acrescentando a operação no nome do arquivo*/
                    prox_posicao++;
                    nome[prox_posicao] = 'v';
                }
                else if(comando == 'h'){
                    rebatimentoHorizontal(imagem, linhas, colunas);
                    printf("Operacao realizada com sucesso.");
                    /*Acrescentando a operação no nome do arquivo*/
                    prox_posicao++;
                    nome[prox_posicao] = 'h';
                }
                else if(comando == 'x'){
                    printf("Informe x superior: ");
                    scanf("%d", &xsup);
                    printf("Informe y superior: ");
                    scanf("%d", &ysup);
                    printf("Informe x inferior: ");
                    scanf("%d", &xinf);
                    printf("Informe y inferior: ");
                    scanf("%d", &yinf);
                    /*Verificação dos pontos*/
                    if(   (xsup > (linhas - 1)) || (ysup > (colunas - 1))
                       || (xinf > (linhas - 1)) || (yinf > (colunas - 1))
                       || (xsup < 0) || (ysup < 0) || (xinf < 0) || (yinf < 0 ))
                    {
                        printf("Limites invalidos\n");
                    }
                    else{
                        corte(imagem, &linhas, &colunas, xsup, ysup, xinf, yinf);
                        /*Acrescentando a operação no nome do arquivo*/
                        prox_posicao++;
                        nome[prox_posicao] = 'x';
                    }
                }
                else if(comando == 'e'){
                    do{
                        printf("Digite o tamanho da janela: ");
                        scanf("%d", &larguraJanela);
                        if((larguraJanela < 3)||(larguraJanela > 50))
                            printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
                    }while((larguraJanela < 3)||(larguraJanela > 50));

                    filtroErosao(imagem, linhas, colunas, larguraJanela);
                    printf("Operacao realizada com sucesso.");
                    /*Acrescentando a operação no nome do arquivo*/
                    prox_posicao++;
                    nome[prox_posicao] = 'e';
                }
                else if(comando == 'd'){
                    do{
                        printf("Digite o tamanho da janela: ");
                        scanf("%d", &larguraJanela);
                        if((larguraJanela < 3)||(larguraJanela > 50))
                            printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
                    }while((larguraJanela < 3)||(larguraJanela > 50));

                    filtroDilatacao(imagem, linhas, colunas, larguraJanela);
                    printf("Operacao realizada com sucesso.");
                    /*Acrescentando a operação no nome do arquivo*/
                    prox_posicao++;
                    nome[prox_posicao] = 'd';
                }
                else if(comando == 'm'){
                    do{
                        printf("Digite o tamanho da janela: ");
                        scanf("%d", &larguraJanela);
                        if((larguraJanela < 3)||(larguraJanela > 50))
                            printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
                    }while((larguraJanela < 3)||(larguraJanela > 50));

                    filtroMediana(imagem, linhas, colunas, larguraJanela);
                    printf("Operacao realizada com sucesso.");
                    /*Acrescentando a operação no nome do arquivo*/
                    prox_posicao++;
                    nome[prox_posicao] = 'm';
                }
                else if(comando == 'z'){
                    do{
                        printf("Digite o tamanho da janela: ");
                        scanf("%d", &larguraJanela);
                        if((larguraJanela < 3)||(larguraJanela > 50))
                            printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
                    }while((larguraJanela < 3)||(larguraJanela > 50));

                    filtroMedia(imagem, linhas, colunas, larguraJanela);
                    printf("Operacao realizada com sucesso.");
                    /*Acrescentando a operação no nome do arquivo*/
                    prox_posicao++;
                    nome[prox_posicao] = 'z';
                }
                else if(comando == '1'){
                    do{
                        printf("Digite o tamanho da janela: ");
                        scanf("%d", &larguraJanela);
                        if((larguraJanela < 3)||(larguraJanela > 50))
                            printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
                    }while((larguraJanela < 3)||(larguraJanela > 50));

                    printf("informe o valor de k: ");
                    scanf("%d", &k);
                    filtroBorda1(imagem, linhas, colunas, larguraJanela, k);
                    printf("Operacao realizada com sucesso.");
                    /*Acrescentando a operação no nome do arquivo*/
                    prox_posicao++;
                    nome[prox_posicao] = '1';
                }
                else if(comando == '2'){
                    do{
                        printf("Digite o tamanho da janela: ");
                        scanf("%d", &larguraJanela);
                        if((larguraJanela < 3)||(larguraJanela > 50))
                            printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
                    }while((larguraJanela < 3)||(larguraJanela > 50));

                    printf("informe o valor de k: ");
                    scanf("%d", &k);
                    filtroBorda2(imagem, linhas, colunas, larguraJanela, k);
                    printf("Operacao realizada com sucesso.");
                    /*Acrescentando a operação no nome do arquivo*/
                    prox_posicao++;
                    nome[prox_posicao] = '2';
                }
                else if(comando == '3'){
                    do{
                        printf("Digite o tamanho da janela: ");
                        scanf("%d", &larguraJanela);
                        if((larguraJanela < 3)||(larguraJanela > 50))
                            printf("Tamanho invalido. A janela deve ser entre 3 e 50.\n");
                    }while((larguraJanela < 3)||(larguraJanela > 50));

                    printf("informe o valor de k: ");
                    scanf("%d", &k);
                    filtroBorda3(imagem, linhas, colunas, larguraJanela, k);
                    printf("Operacao realizada com sucesso.");
                    /*Acrescentando a operação no nome do arquivo*/
                    prox_posicao++;
                    nome[prox_posicao] = '3';
                }
                else if(comando == 'g'){
                    nome[prox_posicao + 1] = 0;
                    printf("%s.pgm", nome);
                    maiorValor = acha_maior(imagem, linhas, colunas);
                    grava_pgm(nome, imagem, linhas,colunas, maiorValor);
                    printf("\nArquivo %s.pgm gravado com sucesso", nome);
                }
                else if(comando == 'C'){
                    printf("Digite o nome do arquivo com a imagem a ser comparada: ");
                    scanf("%s", &nome2);
                    le_pgm(nome2, imagem2, &linhas2, &colunas2, &maiorValor2);
                    compara_matriz(imagem, linhas, colunas, imagem2, linhas2, colunas2);
                }
                else
                    printf("Comando invalido");

                /*Nova leitura de comando*/
                printf("\nDigite um comando: ");
                scanf(" %c", &comando);
            }
        }
    }
    return 0;
}

/* Funçõees  PARA LEITURA/GRAVAÇÃO */

int le_pgm(char* prefixo_do_nome, int m[MAXLINHA][MAXCOLUNA], int
*linhas, int* colunas, int* maiorValor){
/* ----------------------------------------------
Le um arquivo no formato PGM.
prefixo_do_nome : prefixo do arquivo pgm
m : matriz correspondente a imagem lida
linhas : numero de linhas da matriz
colunas : numero de colunas da matriz
max_value : maior valor na matriz
---------------------------------------------- */
    FILE *arq;
    char key[128];
    int i, j, aux;
    char fname[MAX_NAME];
    /* monta o nome do arquivo */
    strcpy(fname, prefixo_do_nome);
    strcat(fname,".pgm");
    /* abre o o arquivo de entrada para leitura */
    arq = fopen(fname, "r");
    if (arq == NULL){
        printf("Erro na abertura do arquivo %s\n",fname);
        return 0;
    }
    /* le dados do cabecalho */
    aux = fscanf(arq, "%s", key);
    if (aux != 1){
        printf("Erro na letura do arquivo %s \n",fname);
        return 0;
    }
    if(strcmp(key,"P2") != 0) {
        printf("Formato desconhecido\n") ;
        fclose(arq) ;
        return 0;
    }
    aux = fscanf(arq, "%d %d %d", colunas, linhas, maiorValor) ;
    if (aux != 3) {
        printf("Formato incorreto\n") ;
        fclose(arq) ;
        return 0;
    }
    /* le a matriz (imagem) que se segue */
    for(i = 0; i < *linhas; i++) {
        for(j = 0; j < *colunas; j++) {
            fscanf(arq, "%d", &m[i][j]);
        }
    }
    fclose(arq) ; /* fecha arquivo */
    return 1;
}

int grava_pgm(char* prefixo_do_nome, int m[MAXLINHA][MAXCOLUNA], int
linhas, int colunas, int maiorValor){
/* ----------------------------------------------
Escreve um arquivo, no formato PGM.
prefixo_do_nome : prefixo do arquivo pgm
m : matriz correspondente a imagem lida
linhas : numero de linhas da matriz
colunas : numero de colunas da matriz
max_value : maior valor na matriz
---------------------------------------------- */
    FILE *arq;
    int i, j;
    char fname[MAX_NAME];
    /* monta o nome do arquivo */
    strcpy(fname, prefixo_do_nome);
    strcat(fname,".pgm");
    /*abre o o arquivo para gravacao */
    arq = fopen(fname, "w");
    if (arq == NULL){
        printf("Erro na abertura do arquivo %s\n",fname);
        return 0;
    }
    /* grava dados do cabecalho */
    fprintf(arq, "P2\n");
    fprintf(arq, "%d %d\n%d\n", colunas, linhas, maiorValor);
    /* grava a matriz (imagem) que se segue */
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            fprintf(arq, "%d ", m[i][j]);
        }
        fprintf(arq, "\n");
    }
    fclose(arq); /* fecha arquivo */
    return 1;
}

/*Funçõees DE EDIÇÃO*/
/*Função que recebe os dados de uma matriz correspondente a uma
imagem .pgm e a altera gerando o negativo da imagem*/
void negativo(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas){
    int i, j;
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            m[i][j] = 255 - m[i][j];
        }
    }
    return;
}

/*Função que recebe os dados de uma matriz e a altera invertendo as
posições de seus pontos em relação a um eixo vertical*/
void rebatimentoVertical(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas){
    int aux[linhas][colunas], i, j;
    /* Montagem da Matriz Auxiliar */
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            aux[i][j] = m[i][j];
        }
    }
    /* Rebatimento Vertical */
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            m[i][j] = aux[i][(colunas - 1) - j];
        }
    }
    return;
}

/*Função que recebe os dados de uma matriz e a altera invertendo as
posições de seus pontos em relação a um eixo horizontal*/
void rebatimentoHorizontal(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas){
    int aux[linhas][colunas], i, j;
    /* Montagem da Matriz Auxiliar */
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            aux[i][j] = m[i][j];
        }
    }
    /* Rebatimento Horizontal */
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            m[i][j] = aux[(linhas - 1) - i][j];
        }
    }
    return;
}

/*Função que recebe os dados de uma matriz e a altera de modo que suas
entradas mudem de posição girando 90° em torno de um eixo em seu centro*/
void rotacao(int m[MAXLINHA][MAXCOLUNA], int* linhas, int* colunas){
    int i, j, m_transposta[*colunas][*linhas], aux;
    /*Transposição da Matriz*/
    aux = *linhas;
    *linhas = *colunas;
    *colunas = aux;
    for(i = 0; i < (*linhas); i++){
        for(j = 0; j < (*colunas); j++){
            m_transposta[i][j] = m[j][i];
        }
    }
    for(i = 0; i < (*linhas); i++){
        for(j = 0; j < (*colunas); j++){
            m[i][j] = m_transposta[i][j];
        }
    }
    /*Rebatimento Vertical da Matriz*/
    rebatimentoVertical(m, *linhas, *colunas);
    return;
}

/*Função que recebe os dados de uma matriz e dois de seus pontos, um
superior e um inferior, como parâmetros para dimensionar seu corte.
A matriz recebida é alterada tornando-se o resultado do corte*/
void corte(int m[MAXLINHA][MAXCOLUNA], int* linhas,
            int* colunas, int xsup, int ysup, int xinf, int yinf)
{
    int i, j, lin_m_corte, col_m_corte, m_cortada[MAXLINHA][MAXCOLUNA];

    /*Corte*/
    lin_m_corte = 0;
    col_m_corte = 0;
    for(i = xsup; i <= xinf; i++){
        col_m_corte = 0;
        for(j = ysup; j<= yinf; j++){
            m_cortada[lin_m_corte][col_m_corte] = m[i][j];
            col_m_corte++;
        }
        lin_m_corte++;
    }
    /*Montagem da nova matriz m*/
    *linhas = lin_m_corte;
    *colunas = col_m_corte;
    for(i = 0; i < (*linhas); i++){
        for(j = 0; j < (*colunas); j++){
            m[i][j] = m_cortada[i][j];
        }
    }
    printf("Operacao realizada com sucesso.");
    return;
}

/*Funçõees DE FILTRO*/

/*Função que recebe os dados de uma matriz, e um tamanho de janela, e a altera
dando a cada posição o valor da mediana das posições na janela ao redor dela*/
void filtroMediana(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas,
                   int larguraJanela)
{
    int i, j, aux[MAXLINHA][MAXCOLUNA], vizinhanca[JANELA_MAX*JANELA_MAX], qtde_elem;
    /*Reservando os valores de m em aux*/
    iguala_matriz(m, aux, linhas, colunas);

    /*Implementação do filtro*/
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            janela(aux, linhas, colunas, i, j, larguraJanela, vizinhanca, &qtde_elem);
            m[i][j] = mediana(vizinhanca, qtde_elem);
        }
    }
    return;
}

/*Função que recebe os dados de uma matriz, e um tamanho de janela, e a altera
dando a cada posição o valor da média das posições na janela ao redor dela*/
void filtroMedia(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas,
                 int larguraJanela)
{
    int i, j, aux[MAXLINHA][MAXCOLUNA], vizinhanca[JANELA_MAX*JANELA_MAX], qtde_elem;
    /*Guardando os valores de m em aux*/
    iguala_matriz(m, aux, linhas, colunas);

    /*Implementação do filtro*/
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            janela(aux, linhas, colunas, i, j, larguraJanela, vizinhanca, &qtde_elem);
            m[i][j] = media(vizinhanca, qtde_elem);
        }
    }
    return;
}

/*Função que recebe os dados de uma matriz, e um tamanho de janela, e a altera
dando a cada posição o valor mínimo entre as posições na janela ao redor dela*/
void filtroErosao(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas,
                   int larguraJanela)
{
    int i, j, aux[MAXLINHA][MAXCOLUNA], vizinhanca[JANELA_MAX*JANELA_MAX], qtde_elem;
    /*Guardando os valores de m em aux*/
    iguala_matriz(m, aux, linhas, colunas);

    /*Implementação do filtro*/
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            janela(aux, linhas, colunas, i, j, larguraJanela, vizinhanca, &qtde_elem);
            m[i][j] = menor_vizinho(vizinhanca, qtde_elem);
        }
    }
    return;
}

/*Função que recebe os dados de uma matriz, e um tamanho de janela, e a altera
dando a cada posição o valor máximo entre as posições na janela ao redor dela*/
void filtroDilatacao(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas,
                     int larguraJanela)
{
    int i, j, aux[MAXLINHA][MAXCOLUNA], vizinhanca[JANELA_MAX*JANELA_MAX], qtde_elem;
    /*Guardando os valores m em aux*/
    iguala_matriz(m, aux, linhas, colunas);

    /*Implementação do filtro*/
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            janela(aux, linhas, colunas, i, j, larguraJanela, vizinhanca, &qtde_elem);
            m[i][j] = maior_vizinho(vizinhanca, qtde_elem);
        }
    }
    return;
}

/*Função que recebe os dados de uma matriz e implementa o filtro de borda 1
conforme especificado no enunciado do EP4*/
void filtroBorda1(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas,
                   int larguraJanela, int k)
{
    int i, j, aux[MAXCOLUNA][MAXCOLUNA], vizinhanca[JANELA_MAX*JANELA_MAX], qtde_elem;
    /*Guardando os valores  de m em aux*/
    iguala_matriz(m, aux, linhas, colunas);
    /*Implementação do filtro*/
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            janela(aux, linhas, colunas, i, j, larguraJanela, vizinhanca, &qtde_elem);
            m[i][j] =  maior_vizinho(vizinhanca, qtde_elem) - menor_vizinho(vizinhanca, qtde_elem);
        }
    }
    /*Limiarização do resultado*/
    limiarizacao(m, linhas, colunas, k);
    return;
}

/*Função que recebe os dados de uma matriz e implementa o filtro de borda 2
conforme especificado no enunciado do EP4*/
void filtroBorda2(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas,
                   int larguraJanela, int k)
{
    int i, j, aux[MAXLINHA][MAXCOLUNA], vizinhanca[JANELA_MAX*JANELA_MAX], qtde_elem;
    /*Guardando os valores de m em aux*/
    iguala_matriz(m, aux, linhas, colunas);
    /*Implementação do filtro*/
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            janela(aux, linhas, colunas, i, j, larguraJanela, vizinhanca, &qtde_elem);
            m[i][j] = m[i][j] - menor_vizinho(vizinhanca, qtde_elem);
        }
    }
    /*Limiarização do resultado*/
    limiarizacao(m, linhas, colunas, k);
    return;
}

/*Função que recebe os dados de uma matriz e implementa o filtro de borda 3
conforme especificado no enunciado do EP4*/
void filtroBorda3(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas,
                   int larguraJanela, int k)
{
    int i, j, aux[MAXLINHA][MAXCOLUNA], vizinhanca[JANELA_MAX*JANELA_MAX], qtde_elem;
    /*Guardando os valores de m em aux*/
    iguala_matriz(m, aux, linhas, colunas);
    /*Implementação do filtro*/
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            janela(aux, linhas, colunas, i, j, larguraJanela, vizinhanca, &qtde_elem);
            m[i][j] = maior_vizinho(vizinhanca, qtde_elem) - m[i][j];
        }
    }
    /*Limiarização do resultado*/
    limiarizacao(m, linhas, colunas, k);
    return;
}

/*Funçõees AUXILIARES*/

/*Operações com Matrizes e Vetores*/

/*Função que recebe os dados de uma matriz e a imprime na tela*/
void imprime_matriz(int matriz[MAXLINHA][MAXCOLUNA], int linhas, int colunas){
    int i, j;
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            printf("%3d ", matriz[i][j]);
        }
        printf("\n");
    }
    return;
}

/*Função que recebe os dados de duas matrizes de mesmas dimensões e
altera a segunda igualando suas entradas às da primeira*/
void iguala_matriz(int m1[MAXLINHA][MAXCOLUNA], int m2[MAXLINHA][MAXCOLUNA],
                   int linhas, int colunas)
{
    int i, j;
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            m2[i][j] = m1[i][j];
        }
    }
    return;
}

/*Função que recebe os dados de uma matriz e devolve o maior
valor entre suas entradas*/
int acha_maior(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas){
    int i, j, maior;
    maior = 0;
    for(i = 0; i < linhas; i ++){
        for(j = 0; j < colunas; j++){
            if(m[i][j] > maior)
                maior = m[i][j];
        }
    }
    return maior;
}

/*Função que recebe um vetor do tipo char (string) e devolve o
número de posições preenchidas nele*/
int conta_posicoes(char nome[MAX_NAME]){
    int tam_nome, posicao;
    tam_nome = 0;
    for(posicao = 0; nome[posicao] != '\0'; posicao++){
        tam_nome++;
    }
    return tam_nome;
}

/*Função que recebe os dados de duas matrizes e responde se são
iguais ou diferentes em suas dimensões ou entradas*/
void compara_matriz(int m1[MAXLINHA][MAXCOLUNA], int linhas1, int colunas1,
               int m2[MAXLINHA][MAXCOLUNA], int linhas2, int colunas2)
{
    int i, j, x, y, achou_diferente;
    /*Comparação das dimensões de m1 e m2*/
    if((linhas1 != linhas2) || (colunas1 != colunas2)){
        printf("As matrizes tem dimensoes diferentes");
        return;
    }
    /*Comparação das entradas de m1 e m2*/
    achou_diferente = 0;
    for(i = 0; (i < linhas1) && (!achou_diferente); i++){
        for(j = 0; (j < colunas1) && (!achou_diferente); j++){
            if(m1[i][j] != m2[i][j]){
                achou_diferente = 1;
                x = i;
                y = j;
            }
        }
    }
    if(achou_diferente)
        printf("As matrizes tem valores diferentes na posicao %d, %d", x, y);
    else
        printf("As matrizes sao iguais");
    return;
}

/*Funçõees para filtros*/

/*Função que recebe uma matriz e encontra, para um de seus pontos,
os elementos de uma janela de tamanho determinado ao redor desse ponto,
reunindo-os em um vetor e altera uma variável com o tamanho do vetor*/
void janela (int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, /*Dados da matriz de entrada*/
        int x, int y, int janela,                                 /*Dados da Janela*/
        int jan_elementos[JANELA_MAX*JANELA_MAX], int* jan_tamanho)  /*Dados para saída*/
{
    int i, j, pos_v, jan_xsup, jan_ysup, x_janela, y_janela;
    x_janela = janela;/*Tamanho da janela em x*/
    y_janela = janela;/*Tamanho da janela em y*/

    /*Determinação do ponto inicial da janela*/
    jan_xsup = x - (janela - 1)/2;
    jan_ysup = y - (janela - 1)/2;
    /*Limites de tamanho da janela*/
    while(jan_xsup < 0){
        jan_xsup++;
        x_janela--;
    }
    while((jan_xsup + x_janela) > (linhas)){
        x_janela--;
    }
    while(jan_ysup < 0){
        jan_ysup++;
        y_janela--;
    }
    while((jan_ysup + y_janela) > (colunas)){
        y_janela--;
    }
    /*Preenchendo o vetor de elementos da janela*/
    pos_v = 0;
    for(i = jan_xsup; i < (jan_xsup + x_janela); i++){
        for(j = jan_ysup; j < (jan_ysup + y_janela); j++){
            jan_elementos[pos_v] = m[i][j];
            pos_v++;
        }
    }
    *jan_tamanho = pos_v;
    return;
}

/*Função que recebe um vetor e põe seus elementos em ordem crescente*/
void ordem_crescente(int elementos[JANELA_MAX*JANELA_MAX], int qtde_elementos){
    int pos1, pos2, aux;
    for(pos1 = 0; pos1 < qtde_elementos; pos1++){
        for(pos2 = 0; pos2 < qtde_elementos; pos2++){
            if(elementos[pos1] < elementos[pos2]){
                aux = elementos[pos1];
                elementos[pos1] = elementos[pos2];
                elementos[pos2] = aux;
            }
        }
    }
    return;
}

/*Função que recebe um vetor com uma determinada quantidade de
elementos e devolve a mediana entre esses elementos*/
int mediana(int elementos[JANELA_MAX*JANELA_MAX], int qtde_elementos){
    int mediana;
    ordem_crescente(elementos, qtde_elementos);
    mediana = elementos[qtde_elementos/2];
    return mediana;
}

/*Função que recebe um vetor com uma determinada quantidades de
elementos e devolve a média entre esses elementos*/
int media(int elementos[JANELA_MAX*JANELA_MAX], int qtde_elementos){
    int posicao, soma, media;
    soma = 0;
    for(posicao = 0; posicao < qtde_elementos; posicao++)
        soma += elementos[posicao];
    media = soma/qtde_elementos;
    return media;
}

/*Função que recebe um vetor com uma determinada quantidades de
elementos e devolve o menor entre esses elementos*/
int menor_vizinho(int vizinhanca[JANELA_MAX*JANELA_MAX], int qtde_elementos){
    int min, posicao;
    min = 255;
    for(posicao = 0; posicao < qtde_elementos; posicao++){
        if(vizinhanca[posicao] < min)
            min = vizinhanca[posicao];
    }
    return min;
}

/*Função que recebe um vetor com uma determinada quantidades de
elementos e devolve o maior entre esses elementos*/
int maior_vizinho(int vizinhanca[JANELA_MAX*JANELA_MAX], int qtde_elementos){
    int max, posicao;
    max = 0;
    for(posicao = 0; posicao < qtde_elementos; posicao++){
        if(vizinhanca[posicao] > max)
            max = vizinhanca[posicao];
    }
    return max;
}

/*Função que recebe os dados de uma matriz e um valor k e limiariza a
matriz, alterando suas entradas de acordo com k*/
void limiarizacao(int m[MAXLINHA][MAXCOLUNA], int linhas, int colunas, int k){
    int i, j;
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            if(m[i][j] >= k)
                m[i][j] = 255;
            else
                m[i][j] = 0;
        }
    }
    return;
}
