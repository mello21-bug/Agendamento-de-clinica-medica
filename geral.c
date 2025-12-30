#include "geral.h" 

// Função limpar_buffer: lê caracteres do buffer de entrada até encontrar uma nova linha '\n' ou EOF.
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// Verifica se o nome digitado é nulo ou vazio; se sim, imprime erro e retorna 0 (inválido).
int validar_nome(const char *n) {
    if (n==NULL || strlen(n)==0) {
        printf("Erro: O campo nome e obrigatorio!\n");
        return 0;
    }
    for (int i=0; n[i] != '\0'; i++) {
        if (!isalpha(n[i]) && n[i] !=' ') {
            printf("Erro: O nome so pode conter letras e espacos.\n");
            return 0;
            // Percorre cada caractere do nome e verifica se não é letra ou espaço.
           // Se encontrar algum caractere inválido, imprime erro e retorna 0.
        }
    }
    return 1;
    // Se passou por todas as verificações, retorna 1 (válido).
}

int validar_horario(Horario horario, int minh, int maxh) {

    if (horario.hora < minh || horario.hora > maxh) {
        printf("Horario invalido! A hora deve estar entre %dh a %dh.\n", minh, maxh);
        return 0;
        // Verifica se a hora está dentro do intervalo permitido (minh a maxh). Caso contrário, imprime erro e retorna 0.
    }
    if (horario.minuto <0 || horario.minuto > 59) {
        printf("Horario invalido! A hora deve estar entre 0 a 59.\n");
        return 0;
        // Verifica se os minutos estão entre 0 e 59. Caso contrário, imprime erro e retorna 0.
    }
    return 1;
    // Se passou nas duas verificações, retorna 1 (válido).
}

int validar_interalo_horario(Horario horainic, Horario horafim) {
    int total_min_inic = horainic.hora*60 + horainic.minuto;
    int total_min_fim = horafim.hora*60 + horafim.minuto;
     // Converte os horários inicial e final para minutos totais para facilitar a comparação.

    if (total_min_inic>=total_min_fim) {
        printf("Erro: Horario invalido! O horario de inicio deve ser anterior ao de fim.\n");
        return 0;
        // Verifica se o horário inicial é maior ou igual ao final. Se sim, imprime erro e retorna 0.
    }
    return 1;
    // Se o intervalo está correto, retorna 1 (válido).
}

int validar_contato(const char *contato) {
    if (contato == NULL || strlen(contato) == 0) {
        printf("Erro: O campo de contato e obrigatorio!\n");
        return 0;
        // Verifica se o contato é nulo ou vazio. Caso sim, imprime erro e retorna 0.
    }
    if (strchr(contato, '@') != NULL) {
        if (strchr(contato, '.')) {
            return 1;
        } else {
            printf("Erro: formato do email errado, esta faltando '.'.\n");
            return 0;
            // Se contém '@', considera que é um email. Verifica se também contém '.'.
           // Se faltar o ponto, retorna erro.
        }

    } else {
        for (int i=0; contato[i] != '\0'; i++) {
            if (!isdigit(contato[i])) { 
                printf("Erro: formato do contato invalido, digite o seu contato novamente!\n");
                return 0;
                // Se não contém '@', considera que é um número de telefone.
               // Verifica se todos os caracteres são dígitos; se algum não for, retorna erro.
            }
        }
    }
    return 1;
}

int apenas_numeros() {
    char entrada[100];
    int n = 0;
    bool entrada_valida = false;
     
    while (!entrada_valida) {
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Erro de leitura.\n");
            continue;
        }

        // Remove \n se existir
        entrada[strcspn(entrada, "\n")] = '\0';

        if (strlen(entrada) == 0) {
            printf("Entrada invalida. Por favor, digite um numero: ");
            continue;
        }

        // Verifica se todos são dígitos
        bool todos_digitos = true;
        for (int i = 0; entrada[i] != '\0'; i++) {
            if (!isdigit((unsigned char)entrada[i])) {
                todos_digitos = false;
                break;
            }
        }

        if (todos_digitos) {
            n = atoi(entrada);
            entrada_valida = true;
        } else {
            printf("Entrada invalida. Por favor, digite um numero: ");
            // Se todos os caracteres forem dígitos, converte a string para inteiro e sai do loop.
          // Caso contrário, solicita novamente.
        }
    }
    return n;
   // Retorna o número válido digitado pelo usuário.
}

Horario somar_minutos(Horario h, int minutos) {
    h.minuto += minutos;
    h.hora += h.minuto / 60;
    h.minuto %= 60;
    return h;
     // Função que soma minutos a um horário.
    // Primeiro soma os minutos, depois ajusta as horas caso ultrapasse 60.
   // garante que minutos fiquem entre 0 e 59 usando módulo.
}
