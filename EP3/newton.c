/***************************************************************/
/**                                                           **/
/**   Felipe Fernandes de Lima                   9345321      **/
/**   Exercício-Programa 03                                   **/
/**   Professor: Alan Mitchell Durham                         **/
/**   Turma: 04                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>

/*Funções utilizadas*/
int newton(double *x_real, double *x_imag, int max_iter, double eps);
void potencia(double *ret_real, double *ret_imag, double x_real, double x_imag, int k);
void multiplica(double *ret_real, double *ret_imag, double x_real, double x_imag, double y_real, double y_imag);
void divide(double *ret_real, double *ret_imag, double x_real, double x_imag, double y_real, double y_imag);
double modulo(double numero);

/*Incluindo a função calcula(), contida em polinomio.c*/
#include "polinomio.c"

int main(){
    double x_real, x_imag, y_real, y_imag, ret_real, ret_imag;
    double l, u, eps, delta;
    int N, max_iter, r, s, achou_resposta;
    /*Entradas*/
    printf("Digite o valor de l       : ");
    scanf("%lf", &l);
    printf("Digite o valor de u       : ");
    scanf("%lf", &u);
    printf("Digite o valor de N       : ");
    scanf("%d", &N);
    printf("Digite o valor de max_iter: ");
    scanf("%d", &max_iter);
    printf("Digite o valor de epsilon : ");
    scanf("%lf", &eps);

    /*Preparação para o arquivo saida.txt*/
    FILE *out;
    out = fopen("saida.txt", "w");
    if(!out){
        printf("Nao consegui abrir o arquivo para gravacao!\n");
        return 0;
    }
    fprintf(out, "%d", N);

    /*Determinação dos pontos Xrs a serem testados*/
    delta = (u-l)/N;
    for(r = 0; r <= N; r++){
        fprintf(out, "\n");
        for(s = 0; s <= N; s++){
            x_real = l + r*delta;
            x_imag = l + s*delta;
            /*Aplicação do Método de Newton*/
            achou_resposta = newton(&x_real, &x_imag, max_iter, eps);
            if(achou_resposta){
                fprintf(out, "%.10g %.10g ", x_real, x_imag);
            }
            else{
                fprintf(out, "N ");
            }
        }
    }
    return 0;
}

/*Função que calcula, através do Método de Newton, aproximações para raízes
complexas de um polinômio e coloca o seu valor em variáveis de um complexo*/
int newton(double *x_real, double *x_imag, int max_iter, double eps){
    double p_real, p_imag, d_real, d_imag, pDIVd_real, pDIVd_imag;
    int achou_raiz = 0;
    for(; max_iter > 0; max_iter--){
        calcula(*x_real, *x_imag, &p_real, &p_imag, &d_real, &d_imag);
        if((modulo(p_real) <= eps) && (modulo(p_imag) <= eps)){
            achou_raiz = 1;
            break;
        }
        if((modulo(d_real) <= eps) && (modulo(d_imag) <= eps)){
            break;
        }
        divide(&pDIVd_real, &pDIVd_imag, p_real, p_imag, d_real, d_imag);
        /*Cálculo do próximo x*/
        *x_real = *x_real - pDIVd_real;
        *x_imag = *x_imag - pDIVd_imag;
    }
    return achou_raiz;
}

/*Função que recebe um numero complexo(em duas variáveis)e um expoente k
  coloca o valor do complexo elevado a k em variaveis de outro complexo*/
void potencia(double *ret_real, double *ret_imag, double x_real, double x_imag, int k){
    *ret_real = 1;
    *ret_imag = 0;
    for(; k > 0; k--){
        multiplica(&*ret_real, &*ret_imag, x_real, x_imag, *ret_real, *ret_imag);
    }
    return;
}

/*Função que recebe dois numeros complexos(em quatro variáveis)
  e coloca o produto deles em variáveis de outro complexo*/
void multiplica(double *ret_real, double *ret_imag, double x_real, double x_imag, double y_real, double y_imag){
    *ret_real = (x_real * y_real) - (x_imag * y_imag);
    *ret_imag = (x_real * y_imag) + (x_imag * y_real);
    return;
}

/*Função que recebe dois numeros complexos(em quatro variáveis)e coloca
o resultado da a divisão entre eles em variáveis de outro complexo*/
void divide(double *ret_real, double *ret_imag, double x_real, double x_imag, double y_real, double y_imag){
    double numerador_real, numerador_imag, denominador;
    numerador_real = (x_real * y_real) - (x_imag * (-y_imag));
    numerador_imag = (x_real * (-y_imag)) + (x_imag * y_real);
    denominador = (y_real * y_real) + (y_imag * y_imag);
    *ret_real = numerador_real/denominador;
    *ret_imag = numerador_imag/denominador;
    return;
}

/*Função que recebe um número real e retorna seu valor em módulo*/
double modulo(double numero){
    if(numero < 0)
        numero *= (-1);
    return numero;
}
