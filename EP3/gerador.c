/***************************************************************/
/**                                                           **/
/**   Felipe Fernandes de Lima                   9345321      **/
/**   Exercício-Programa 03                                   **/
/**   Professor: Alan Mitchell Durham                         **/
/**   Turma: 04                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>


int main(){
    double coef_real = 0, coef_imag = 0; /*Variáveis para armazenar os coeficientes*/
    int grau, contador;

    /*Iniciando operacoes de leitura e escrita em arquivos*/
    FILE *in, *out;

    in = fopen("polinomio.txt", "r");

    if(!in){
        printf("Nao consegui abrir o arquivo para leitura!\n");
        return 0;
    }

    out = fopen("polinomio.c", "w");

    if(!out){
        printf("Nao consegui abrir o arquivo para gravacao!\n");
        return 0;
    }

    /*Geração de polinomio.c*/
    fscanf(in, "%d", &grau);

    fprintf(out, "#include <stdio.h>\n\n");
    fprintf(out, "void calcula(double x_real, double x_imag, double *p_real,\n");
    fprintf(out, "             double *p_imag, double *d_real, double *d_imag)\n");
    fprintf(out, "{\n");
    fprintf(out, "    double a,b;\n\n");
    fprintf(out, "    *p_real = *p_imag = 0;\n");
    fprintf(out, "    *d_real = *d_imag = 0;\n\n");
    fprintf(out, "/*Calculando o valor de p(x) e d(x)*/\n");

    for(; grau >= 0; grau--){
        fscanf(in, "%lf %lf", &coef_real, &coef_imag);

        if((coef_real)||(coef_imag)){
            /*Imprime no programa calculador para p(x)*/
            fprintf(out, "    potencia(&a, &b, x_real, x_imag, %d);\n", grau);
            fprintf(out, "    multiplica(&a, &b, a, b, %.10g, %.10g);\n", coef_real, coef_imag);
            fprintf(out, "    *p_real += a;\n");
            fprintf(out, "    *p_imag += b;\n\n");
            /*Imprime no programa calculador para d(x) = p'(x)*/
            if((grau-1) >= 0){
                fprintf(out, "    potencia(&a, &b, x_real, x_imag, %d);\n", grau-1);
                fprintf(out, "    multiplica(&a, &b, a, b, %.10g, %.10g);\n", coef_real*grau, coef_imag*grau);
                fprintf(out, "    *d_real += a;\n");
                fprintf(out, "    *d_imag += b;\n\n");
            }
        }

    }

    fprintf(out, "}");

    /*Encerrando leitura em arquivos*/
    fclose(in);
    fclose(out);

    return 0;
}
