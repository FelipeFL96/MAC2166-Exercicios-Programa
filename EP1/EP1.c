/******************************************/
/**                                      **/
/**  Felipe Fernandes de Lima    9345321 **/
/**  Exercício-Programa 01               **/
/**  Professor: Alan Mitchell Durham     **/
/**  Turma: 04                           **/
/**                                      **/
/******************************************/

#include <stdio.h>

int main(){
    int numero, posicao_virgula, algarismo, fator, soma, numDigitos;
    printf("MAC2166 - EP1 - Usando Inteiros para Representar Reais");
    printf("\n\nDigite os algarismos do numero:................: ");
    scanf("%d", &numero);
    printf("Digite a posicao do separador de casas decimais: ");
    scanf("%d", &posicao_virgula);

/*Para o caso de posicao_virgula = 0*/
    if(posicao_virgula==0){
        printf("O numero correspondente na notacao decimal e...: %d\n\n", numero);
        return 0;
    }

/*Contagem do n�mero de algarismos da entrada*/
    fator = 1;
    soma = 0;
    numDigitos = 0;
    while(numero > 0){
        algarismo = numero % 10;
        soma += algarismo*fator;

        numDigitos += 1;
        fator *= 10;
        numero /= 10;
    }

    /*Reinicializa��o de vari�veis*/
    fator = 1;
    numero = soma;

/*Resposta quando v�rgula volta menos ou at� o tamanho do n�mero*/
    if(numDigitos >= posicao_virgula){

        int decimal, contador;
        decimal = 0;
        contador = 0;

        while(contador < posicao_virgula){
            algarismo = numero % 10;
            decimal = decimal + fator*algarismo;
            contador += 1;

            fator *= 10;
            numero /= 10;
        }

        printf("O numero correspondente na notacao decimal e...: %d,", numero);

        /*Teste de casas de decimal para evitar falta de zeros*/
        int teste_decimal = decimal;
        int digitos_decimal = 0;
        int cont_zeros = 0;
        while(teste_decimal > 0){
            digitos_decimal++;
            teste_decimal/=10;
        };
        if(posicao_virgula-digitos_decimal != 0){
            while(cont_zeros < posicao_virgula-digitos_decimal){
                printf("0");
                cont_zeros++;
            }
            if(decimal!=0){
                printf("%d", decimal);/*impressão de decimal após zeros, caso decimal != zero*/
            }
        }
        else{
            printf("%d", decimal);/*impressão normal de decimal quando não faltarem zeros*/
        }
    }



/*Resposta quando a vírgula volta mais que o número*/
    else{

        int contador2 = 0;

        printf("O numero correspondente na notacao decimal e...: ");
        printf("0,");

        while(contador2 < posicao_virgula-numDigitos){
            printf("0");
            contador2 += 1;
        }
        if(numero!=0){
                printf("%d", numero);
        }
    }

    printf("\n");
    return 0;
}
