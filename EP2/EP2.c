/***************************************************************/
/**                                                           **/
/**   Felipe Fernandes de Lima          9345321               **/
/**   Exercício-Programa 02                                   **/
/**   Professor: Alan Mitchell Durham                         **/
/**   Turma: 04                                               **/
/**                                                           **/
/***************************************************************/

 #include <stdio.h>

 /*Funções de obtenção*/
int obter_mantissa(int);
int obter_expoente(int);
int obter_numero_pf(int,int);
/*Funções de operação*/
int soma(int,int);
int subtracao(int,int);
int multiplicacao(int,int);
int divisao(int,int);
/*Funções auxiliares*/
int ajuste_digitos(int,int);
int normalizado(int);
int conta_digitos(int);
int modulo (int);

int main(){
    int operando1, operando2, operacao, resultado;
    printf("MAC2166 - EP2 - Calculadora para Numeros de Ponto Flutuante\n");

    operacao = 0;
    while(operacao != 6){
        printf("\nOperando 1...................: ");
        scanf("%d", &operando1);

        printf("\nOperacoes disponiveis: 1 (+), 2 (-), 3 (*), 4 (/), 5 (limpar), 6 (parar)");
        printf("\nNumero da operacao desejada..: ");
        scanf("%d", &operacao);

        while((operacao != 5) && (operacao != 6)){
            if(operacao == 1){
                printf("\nOperando 2...................: ");
                scanf("%d", &operando2);
                resultado = normalizado(soma(operando1, operando2));
            }
            if(operacao == 2){
                printf("\nOperando 2...................: ");
                scanf("%d", &operando2);
                resultado = normalizado(subtracao(operando1, operando2));
            }
            if(operacao == 3){
                printf("\nOperando 2...................: ");
                scanf("%d", &operando2);
                resultado = normalizado(multiplicacao(operando1, operando2));
            }
            if(operacao == 4){
                printf("\nOperando 2...................: ");
                scanf("%d", &operando2);
                /*Verificação de divisão por 0*/
                if(normalizado(operando2) == 0)
                    printf("\n*** ERRO: nao e' possivel dividir por zero. ***");
                else
                    resultado = normalizado(divisao(operando1, operando2));
            }
            if((operacao == 4) && (normalizado(operando2) == 0)){
                printf("\n\nOperacoes disponiveis: 1 (+), 2 (-), 3 (*), 4 (/), 5 (limpar), 6 (parar)");
                printf("\nNumero da operacao desejada..: ");
                scanf("%d", &operacao);
            }
            else{
                printf("\nResultado (e novo operando 1): %d", resultado);
                operando1 = resultado;

                printf("\n\nOperacoes disponiveis: 1 (+), 2 (-), 3 (*), 4 (/), 5 (limpar), 6 (parar)");
                printf("\nNumero da operacao desejada..: ");
                scanf("%d", &operacao);
            }
        }
    }
    printf("\nTchau!");

    return 0;
}

/*FUNÇÕES DE OBTENÇÃO*/

/*Função que recebe um numero de ponto flutuante na notação
de 9 digitos do EP2 e retorna a sua mantissa*/
int obter_mantissa(int numero_pf){
    return numero_pf/1000;
}

/*Função que recebe um numero de ponto flutuante na notação
de 9 dígitos do EP2 e retorna o seu expoente*/
int obter_expoente(int numero_pf){
    int expoente = numero_pf%100;
    numero_pf /= 100;
    int sinal = numero_pf%10;
    if(expoente < 0)
        expoente *= (-1);
    if(sinal != 0)
        expoente = 0-expoente;
    return expoente;
}

/*Função que recebe dois números: um representando a mantissa e, o outro, o
expoente, e retorna um número de ponto flutuante na notação de 9 dígitos do EP2*/
int obter_numero_pf(int mantissa,int expoente){
    int numero_pf;
    if(expoente < 0)
        numero_pf = modulo(mantissa)*1000 + 100 + modulo(expoente);
    else
        numero_pf = modulo(mantissa)*1000 + modulo(expoente);
    if(mantissa < 0)
        numero_pf *= (-1);
    return numero_pf;
}

/*FUNÇÕES DE OPERAÇÃO*/

/*Função que recebe dois numeros de ponto flutuante na notação
de 9 digitos do EP2 e retorna a sua soma na mesma notação*/
int soma(int num1, int num2){

    int mant1, mant2, exp1, exp2, soma;

/*Obtenção de dados*/
    mant1 = obter_mantissa(num1);
    exp1 = obter_expoente(num1);
    mant2 = obter_mantissa(num2);
    exp2 = obter_expoente(num2);
/*Ajuste dos expoentes para soma*/
    while(exp1 < exp2){
        exp2--;
        mant2 *= 10;
        if(conta_digitos(mant2) > 6){
            mant2 /= 10;
            exp2++;
            mant1 /= 10;
            exp1++;
        }
    }
    while(exp2 < exp1){
        exp1--;
        mant1 *= 10;
        if(conta_digitos(mant1) > 6){
            mant1 /= 10;
            exp1++;
            mant2 /= 10;
            exp2++;
        }
    }
/*Soma*/
    soma = mant1 + mant2;
    if(soma == 0){
        exp1 = 0;
    }
/*Ajuste de digitos da soma*/
    while((conta_digitos(soma) > 6) && (exp1 < 99)){
        soma /= 10;
        exp1++;
    }
    /*Verificação de Overflow*/
    if((conta_digitos(soma) > 6) && (modulo(exp1) == 99)){
        printf("\n*** AVISO: ocorreu um overflow no expoente. ***");
        if (soma < 0)
            soma = -999999;
        else
            soma = 999999;
    }
    return obter_numero_pf(soma, exp1);
}

/*Função que recebe dois numeros de ponto flutuante na notação de 9 digitos
do EP2 e retorna a subtração do primeiro pelo segundo na mesma notação*/
int subtracao(int num1, int num2){
    return soma(num1, -num2);
}

/*Função que recebe dois numeros de ponto flutuante na notação de
9 digitos do EP2 e retorna produto deles*/
int multiplicacao(int fator1, int fator2){
    int mant1, exp1, mant2, exp2, resultado, mantResultado, expResultado;

    mant1 = obter_mantissa(fator1);
    exp1 = obter_expoente(fator1);
    mant2 = obter_mantissa(fator2);
    exp2 = obter_expoente(fator2);

    resultado = 0;
    while(mant2 != 0){
    /*Operação com as mantissas e expoentes*/
        mantResultado = mant1 * (mant2%10);
        expResultado = exp1 + exp2;
    /*Verificação de underflow*/
        if(expResultado < -99){
            printf("\n*** AVISO: ocorreu um underflow no expoente. ***");
            mantResultado = 0;
            expResultado = 0;
            mant2 = 0; /*Para finalizar o loop*/
        }
     /*Verificação de overflow*/
        if((conta_digitos(mantResultado) > 6) && (expResultado == 99)){
            printf("\n*** AVISO: ocorreu um overflow no expoente. ***");
            if (mantResultado < 0)
                mantResultado = -999999;
            else
                mantResultado = 999999;
        }
    /*Resultado parcial*/
        resultado = soma(resultado, ajuste_digitos(mantResultado, expResultado));
    /*Atualização do segundo operando*/
        mant2 /= 10;
        exp2++;
    }
	int resultado_final = ajuste_digitos(obter_mantissa(resultado),obter_expoente(resultado));

    return normalizado(resultado_final);
}

/*Função que recebe dois numeros de ponto flutuante na notação de
9 digitos de EP2 e retorna o resultado da divisão entre eles*/
int divisao(int dividendo, int divisor){
    int mant1, mant2, exp1, exp2; /*Variáveis de Obtenção*/
    int exp_quociente, quociente, quociente_pf, resto, resultado; /*Varáveis de Operação*/
    int mantRes_final, expRes_final, Res_final; /*Varáveis de resultado*/
/*Obtenção de dados*/
    dividendo = normalizado(dividendo);
    divisor = normalizado(divisor);
    mant1 = obter_mantissa(dividendo);
    exp1  = obter_expoente(dividendo);
    mant2 = obter_mantissa(divisor);
    exp2  = obter_expoente(divisor);
/*Operação*/
    /*Inicializações para Operação*/
    exp_quociente = 0;
    resultado = 0;
    /*Primeira divisão*/
    quociente = mant1/mant2;
    resto = mant1 % mant2;
    quociente_pf = obter_numero_pf(quociente, exp_quociente);
    resultado = soma(resultado, quociente_pf);
    /*Próximas possíveis divisões*/
    while((resto != 0) && (conta_digitos(obter_mantissa(resultado)) < 6)){
        /* Atualizações */
        resto *= 10;
        exp_quociente--;
        /* Operação */
        quociente = resto/mant2;
        resto = resto%mant2;
        /* Composição de resultado */
        quociente_pf = obter_numero_pf(quociente, exp_quociente);
        resultado = soma(resultado, quociente_pf);
    }
/*Resultado*/
    mantRes_final = obter_mantissa(resultado);
    expRes_final = obter_expoente(resultado) + exp1 - exp2;
    /*Correção de expoentes de 0*/
    if(mantRes_final == 0)
        expRes_final = 0;
    /*Verificação de underflow*/
		if(expRes_final < -99){
			printf("\n*** AVISO: ocorreu um underflow no expoente. ***");
			mantRes_final = 0;
			expRes_final = 0;
		}
	 /*Verificação de overflow*/
		if(expRes_final > 99){
			printf("\n*** AVISO: ocorreu um overflow no expoente. ***");
			if (mantRes_final < 0)
				mantRes_final = -999999;
			else
				mantRes_final = 999999;
		}
    Res_final = obter_numero_pf(mantRes_final, expRes_final);

    return Res_final;
}

/*FUNÇÕES AUXILIARES*/

/*Função que recebe a mantissa e o expoente de um número e devolve um numero na
notação de pto flutuante do EP2 limitando o número de algarismos significativos*/
int ajuste_digitos(int mantissa, int expoente){

/*Ajuste de número de digitos/expoente*/
    while((conta_digitos(mantissa) > 6) && (expoente < 99)){
        mantissa /= 10;
        expoente++;
    }
    return obter_numero_pf(mantissa, expoente);
}

/*Função que recebe um inteiro no formato de 9 digitos do EP2 e o
retorna normalizado, conforme a definição contida no enunciado do EP2*/
int normalizado(int numero){
    int mantissa, expoente, cresce_exp, exp_final, sinal, normalizado;
    mantissa = obter_mantissa(numero);
    expoente = obter_expoente(numero);
    if (mantissa == 0){
        normalizado = 0;
    }
    if(mantissa != 0){
        for(cresce_exp = 0;(mantissa%10 == 0) && (expoente+cresce_exp < 99);cresce_exp++){
            mantissa /= 10;
        }
        exp_final = expoente + cresce_exp;
        if(exp_final < 0)
            normalizado = modulo(mantissa*1000) + 100 + modulo(exp_final);
        else
            normalizado = modulo(mantissa*1000) + modulo(exp_final);
        if(numero < 0)
            normalizado *= (-1);
    }
    return normalizado;
}

/*Função que recebe um inteiro e retorna a quantidade de digitos dele*/
int conta_digitos(int numero){
    int contador;
    for(contador = 0; numero != 0; contador++){
        numero /= 10;
    }
    return contador;
}

/*Função que recebe um inteiro e retorna seu módulo*/
int modulo(int numero){
    if(numero < 0)
        numero = 0 - numero;
    return numero;
}
