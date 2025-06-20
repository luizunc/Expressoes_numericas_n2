# Avaliador de Expressões Numéricas

## Descrição

Este projeto implementa um avaliador de expressões numéricas em linguagem C, capaz de converter e avaliar expressões matemáticas entre as notações infixa e pós-fixa. O sistema utiliza o TAD Pilha como estrutura fundamental e suporta operações matemáticas básicas e funções especiais.

## Funcionalidades

### Conversões
- **Infixa → Pós-fixa**: Converte expressões da notação infixa para pós-fixa
- **Pós-fixa → Infixa**: Converte expressões da notação pós-fixa para infixa

### Operações Suportadas
- **Operadores binários**: `+`, `-`, `*`, `/`, `%`, `^` (potenciação)
- **Funções matemáticas**:
  - `sen(x)` - Seno (ângulo em graus)
  - `cos(x)` - Cosseno (ângulo em graus)
  - `tg(x)` - Tangente (ângulo em graus)
  - `log(x)` - Logaritmo de base 10
  - `raiz(x)` - Raiz quadrada

### Avaliação
- **Avaliação de expressões pós-fixas**: Calcula o valor de expressões na notação pós-fixa
- **Avaliação de expressões infixas**: Calcula o valor de expressões na notação infixa

## Estrutura do Projeto

```
projeto/
├── expressao.h      # Cabeçalho com definições e protótipos
├── expressao.c      # Implementação das funções principais
├── main.c          # Interface do usuário e menu
└── README.md       # Este arquivo
```

## Compilação

Para compilar o projeto, use o comando:

```bash
gcc expressao.c main.c -o expressao.exe
```

**Requisitos:**
- Compilador GCC
- Biblioteca matemática (incluída automaticamente)

## Como Usar

1. **Compile o projeto** usando o comando acima
2. **Execute o programa**:
   ```bash
   ./expressao.exe
   ```
3. **Escolha uma opção** no menu:
   - `1` - Converter infixa para pós-fixa
   - `2` - Converter pós-fixa para infixa
   - `3` - Avaliar expressão pós-fixa
   - `4` - Avaliar expressão infixa
   - `0` - Sair

## Exemplos de Uso

### Conversão Infixa → Pós-fixa
```
Digite a expressao infixa: (3 + 4) * 5
Pos-fixa: 3 4 + 5 *
```

### Avaliação Pós-fixa
```
Digite a expressao pos-fixa: 3 4 + 5 *
Valor: 35.00
```

### Funções Matemáticas
```
Digite a expressao pos-fixa: 45 sen
Valor: 0.71

Digite a expressao pos-fixa: 100 log
Valor: 2.00
```

## Testes Realizados

O projeto foi testado com diversos casos, incluindo:

1. **Operações básicas**: `3 4 + 5 *` → 35
2. **Funções trigonométricas**: `45 sen` → 0.7071
3. **Expressões complexas**: `2 3 + log 5 /` → 0.14
4. **Combinações**: `45 60 + 30 cos *` → 90.93

## Algoritmos Implementados

### Conversão Infixa → Pós-fixa
Utiliza o **Algoritmo de Shunting Yard** para converter expressões infixas em pós-fixas, respeitando a precedência dos operadores.

### Avaliação Pós-fixa
Utiliza uma **pilha de operandos** para avaliar expressões pós-fixas, processando cada token sequencialmente.

### Conversão Pós-fixa → Infixa
Utiliza uma **pilha de strings** para reconstruir a expressão infixa com parênteses apropriados.

## Tratamento de Erros

O sistema inclui verificações básicas para:
- Operandos insuficientes
- Expressões mal formadas
- Entradas inválidas

## Autor

[Luiz Eduardo dos Anjos de Jesus] - Universidade Católica de Brasília

## Licença

Este projeto foi desenvolvido para fins educacionais como parte do curso de Estrutura de Dados.
