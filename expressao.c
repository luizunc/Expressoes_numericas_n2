#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "expressao.h"

#define MAX 512
//
// Função auxiliar para verificar precedência dos operadores
//
int precedencia(char op) {
    switch(op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/':
        case '%': return 2;
        case '^': return 3;
        default: return 0;
    }
}
//
// Função para converter infixa para pós-fixa
//
char *getFormaPosFixa(char *Str) {
    static char saida[MAX];
    char pilha[MAX];
    int topo = -1, j = 0;
    int i = 0;
    memset(saida, 0, sizeof(saida));
    while (Str[i] != '\0') {
        if (Str[i] == ' ') { i++; continue; }
        if ((Str[i] >= '0' && Str[i] <= '9') || Str[i] == '.') {
            //
            // Número: copiar para saída
            //
            while ((Str[i] >= '0' && Str[i] <= '9') || Str[i] == '.') {
                saida[j++] = Str[i++];
            }
            saida[j++] = ' ';
            continue;
        }
        if (Str[i] == '(') {
            pilha[++topo] = Str[i];
        } else if (Str[i] == ')') {
            while (topo >= 0 && pilha[topo] != '(') {
                saida[j++] = pilha[topo--];
                saida[j++] = ' ';
            }
            if (topo >= 0 && pilha[topo] == '(') topo--;
        } else if (strchr("+-*/%^", Str[i])) {
            while (topo >= 0 && precedencia(pilha[topo]) >= precedencia(Str[i])) {
                saida[j++] = pilha[topo--];
                saida[j++] = ' ';
            }
            pilha[++topo] = Str[i];
        }
        //
        // TODO: Funções matemáticas (sen, cos, etc)
        //
        i++;
    }
    while (topo >= 0) {
        if (pilha[topo] != '(')
            saida[j++] = pilha[topo];
        topo--;
        saida[j++] = ' ';
    }
    saida[j] = '\0';
    return saida;
}
//
// Função para converter pós-fixa para infixa
//
char *getFormaInFixa(char *Str) {
    static char saida[MAX * 2];
    char *pilha[MAX];
    int topo = -1;
    char token[64];
    int i = 0, j = 0;
    while (Str[i] != '\0') {
        if (Str[i] == ' ') { i++; continue; }
        //
        // Se for número
        //
        if ((Str[i] >= '0' && Str[i] <= '9') || Str[i] == '.') {
            j = 0;
            while ((Str[i] >= '0' && Str[i] <= '9') || Str[i] == '.') {
                token[j++] = Str[i++];
            }
            token[j] = '\0';
            pilha[++topo] = strdup(token);
            continue;
        }
        //
        // Operadores binários
        //
        if (strchr("+-*/%^", Str[i])) {
            if (topo < 1) return NULL;
            char *b = pilha[topo--];
            char *a = pilha[topo--];
            char *expr = malloc(strlen(a) + strlen(b) + 8);
            sprintf(expr, "(%s %c %s)", a, Str[i], b);
            free(a); free(b);
            pilha[++topo] = expr;
            i++;
            continue;
        }
        //
        // Funções de um operando
        //
        if (strncmp(&Str[i], "sen", 3) == 0) {
            if (topo < 0) return NULL;
            char *a = pilha[topo--];
            char *expr = malloc(strlen(a) + 8);
            sprintf(expr, "sen(%s)", a);
            free(a);
            pilha[++topo] = expr;
            i += 3;
            continue;
        }
        if (strncmp(&Str[i], "cos", 3) == 0) {
            if (topo < 0) return NULL;
            char *a = pilha[topo--];
            char *expr = malloc(strlen(a) + 8);
            sprintf(expr, "cos(%s)", a);
            free(a);
            pilha[++topo] = expr;
            i += 3;
            continue;
        }
        if (strncmp(&Str[i], "tg", 2) == 0) {
            if (topo < 0) return NULL;
            char *a = pilha[topo--];
            char *expr = malloc(strlen(a) + 8);
            sprintf(expr, "tg(%s)", a);
            free(a);
            pilha[++topo] = expr;
            i += 2;
            continue;
        }
        if (strncmp(&Str[i], "log", 3) == 0) {
            if (topo < 0) return NULL;
            char *a = pilha[topo--];
            char *expr = malloc(strlen(a) + 8);
            sprintf(expr, "log(%s)", a);
            free(a);
            pilha[++topo] = expr;
            i += 3;
            continue;
        }
        if (strncmp(&Str[i], "raiz", 4) == 0) {
            if (topo < 0) return NULL;
            char *a = pilha[topo--];
            char *expr = malloc(strlen(a) + 8);
            sprintf(expr, "raiz(%s)", a);
            free(a);
            pilha[++topo] = expr;
            i += 4;
            continue;
        }
        i++;
    }
    if (topo == 0) {
        strncpy(saida, pilha[0], MAX * 2);
        free(pilha[0]);
        return saida;
    }
    return NULL;
}
//
// Função para avaliar expressão pós-fixa
//
float getValorPosFixa(char *StrPosFixa) {
    float pilha[MAX];
    int topo = -1;
    char token[64];
    int i = 0, j = 0;
    while (StrPosFixa[i] != '\0') {
        if (StrPosFixa[i] == ' ') { i++; continue; }
        //
        // Se for número
        //
        if ((StrPosFixa[i] >= '0' && StrPosFixa[i] <= '9') || StrPosFixa[i] == '.') {
            j = 0;
            while ((StrPosFixa[i] >= '0' && StrPosFixa[i] <= '9') || StrPosFixa[i] == '.') {
                token[j++] = StrPosFixa[i++];
            }
            token[j] = '\0';
            pilha[++topo] = atof(token);
            continue;
        }
        //
        // Se for operador
        //
        if (strchr("+-*/%^", StrPosFixa[i])) {
            if (topo < 1) return 0.0; // erro: operandos insuficientes
            float b = pilha[topo--];
            float a = pilha[topo--];
            switch (StrPosFixa[i]) {
                case '+': pilha[++topo] = a + b; break;
                case '-': pilha[++topo] = a - b; break;
                case '*': pilha[++topo] = a * b; break;
                case '/': pilha[++topo] = a / b; break;
                case '%': pilha[++topo] = fmod(a, b); break;
                case '^': pilha[++topo] = pow(a, b); break;
            }
            i++;
            continue;
        }
        //
        // Funções matemáticas
        //
        if (strncmp(&StrPosFixa[i], "sen", 3) == 0) {
            if (topo < 0) return 0.0;
            float a = pilha[topo--];
            pilha[++topo] = sin(a * M_PI / 180.0); // graus para radianos
            i += 3;
            continue;
        }
        if (strncmp(&StrPosFixa[i], "cos", 3) == 0) {
            if (topo < 0) return 0.0;
            float a = pilha[topo--];
            pilha[++topo] = cos(a * M_PI / 180.0);
            i += 3;
            continue;
        }
        if (strncmp(&StrPosFixa[i], "tg", 2) == 0) {
            if (topo < 0) return 0.0;
            float a = pilha[topo--];
            pilha[++topo] = tan(a * M_PI / 180.0);
            i += 2;
            continue;
        }
        if (strncmp(&StrPosFixa[i], "log", 3) == 0) {
            if (topo < 0) return 0.0;
            float a = pilha[topo--];
            pilha[++topo] = log10(a);
            i += 3;
            continue;
        }
        if (strncmp(&StrPosFixa[i], "raiz", 4) == 0) {
            if (topo < 0) return 0.0;
            float a = pilha[topo--];
            pilha[++topo] = sqrt(a);
            i += 4;
            continue;
        }
        //
        // Se não reconhecido, avança
        //
        i++;
    }
    if (topo == 0) return pilha[0];
    return 0.0; // Log: caso de erro
}
//
// Função para avaliar expressão infixa
//
float getValorInFixa(char *StrInFixa) {
    char *posfixa = getFormaPosFixa(StrInFixa);
    return getValorPosFixa(posfixa);
} 