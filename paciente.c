#include "geral.h"

// adiciona pacientes novos
void adicionar_paciente(pacientes **paciente, int *p, int *idpaciente, int *capacidade_pacientes){
    pacientes a;
    
    int maior_id = 0;
        for (int i = 0; i < *p; i++) {
            if ((*paciente)[i].id > maior_id) {
                maior_id = (*paciente)[i].id;
            }
        }
        a.id = maior_id + 1;
        (*idpaciente) = a.id + 1;

    // adiciona ID (definido como 1 no main e eh incrementado a cada paciente novo)
    printf("Iniciando o programa de cadastro de pacientes...\n");
    
    // leitura do nome
    do {
        printf("\nadicione o nome do(a) paciente: ");
        scanf(" %63[^\n]", a.nome);
    } while (!validar_nome(a.nome));

    // leitura do contato (sera considerado email se possuir @ e numero se so possuir numero)
    do {
        printf("\nadicione o contato do(a) paciente (email ou telefone(apenas numeros)): ");
        scanf(" %63[^\n]", a.contato);
        getchar();
    } while (!validar_contato(a.contato));

    // realoca memoria se necessario 
    if (*p >= *capacidade_pacientes) {
        *capacidade_pacientes += 10;
        *paciente = (pacientes*)realloc(*paciente, *capacidade_pacientes * sizeof(pacientes));
        
        if (*paciente == NULL) {
            printf("Erro ao realocar memoria para pacientes.\n");
            return;
        }
    }

    (*paciente)[*p] = a;
    (*p)++;
    (*idpaciente)++;
}

// lista os pacientes cadastrados
void listarpacientes(pacientes *x, int n) {
    if (n == 0) {
        printf("Nao existe nenhum paciente cadastrado no sistema!\n");
        return;
    }
    // usa o for para passar por todos os espaços que etiverem atras do numero total de cadastros
    for(int i = 0; i < n; i++) {
        printf("---LISTA DO PACIENTE---\n");
        printf("ID: %d\n", x[i].id);
        printf("Nome: %s\n", x[i].nome);
        printf("Contato: %s\n", x[i].contato);
        printf("-------------------------------\n");
    }
}

// busca id especifico (passando pelo vetor de pacinetes comparando o id esoclhido com os resgitrados)
pacientes* buscaidp(pacientes *a, int t, int b) {
    if (t == 0) {
        printf("nao existe nenhum paciente cadastrado no sstema!");
        return NULL;
    }
    for (int j = 0; j < t; j++) {
        if (a[j].id == b) {
            return &a[j];
        }
    }
    return NULL;
}

// atualiza o paciente (podendo atualizar somente o nome e contato)
void atualizarpacientes(pacientes *p, int t) {
    int idbusca;
    int escolha;

    if (t == 0) {
        printf("Nao existe nenhum pacientes cadastrado no sistema!\n");
        return;
    }
    printf("Digite o id do paciente que voce deseja atualizar as informacoes: \n");
    idbusca=apenas_numeros();

    pacientes *aux = buscaidp(p, t, idbusca);
    if (aux != NULL) {
        printf("--- PACIENTE ENCONTRADO ---\n");
        printf("ID: %d\n", aux->id);
        printf("Nome: %s\n", aux->nome);
        printf("Contato: %s\n", aux->contato);
        printf("\nO que voce deseja atualizar?\n1 - Nome\n2 - Contato\n");
        printf("Digite sua escolha:\n ");
        do{
            escolha = apenas_numeros();
            if (escolha < 1 || escolha > 2){
                printf("ESCOLHA INVALIDA! tente novamente (entre 1 e 2)");
            }
        } while (escolha < 1 || escolha > 2);

        switch (escolha) {
            case 1:
                printf("Digite o novo nome.\n");
                scanf(" %63[^\n]", aux->nome);
                printf("Atualizacao feita com sucesso!\n");
                getchar();
                break;
            case 2:
                printf("Digite o novo contato.\n");
                scanf(" %63[^\n]", aux->contato);
                printf("Atualizacao feita com sucesso!\n");
                getchar();
                break;
            default:
                break;
        }
    } else {
        printf("\nPaciente com ID %d nao encontrado.\n", idbusca);
    }
}

// Remove um paciente do array pelo ID informado.
// Se o ID for encontrado, os elementos posteriores são deslocados para preencher o espaço
// e a memória do array é realocada para liberar o espaço do paciente removido
void remover_paciente(pacientes **paciente, int *num_pacientes) {
    int id_busca;
    int i;
    int encontrado = -1;

    if ((*num_pacientes) == 0) {
        printf("Nao existe nenhum pacientes cadastrado no sistema!\n");
        return;
    }

    printf("Digite o ID do paciente que sera removido: ");
    id_busca=apenas_numeros();

    for (int i=0; i < *num_pacientes; i++) {
        if ((*paciente)[i].id == id_busca) {
            encontrado = i;
            break;
        }
    }

    if (encontrado !=-1) {
        for (i=encontrado; i < (*num_pacientes)-1; i++) {
            (*paciente)[i] = (*paciente)[i+1];
        }
        (*num_pacientes)--;

        printf("Paciente removido com sucesso!\n");
    } else {
        printf("Paciente com o ID %d nao encontrado.\n", id_busca);
    }
}

// ordena pacientes por ordem alfabetica
int compararpacientes(const void *a, const void *b) {
    pacientes *pa = (pacientes *)a;
    pacientes *pb = (pacientes *)b;
    return strcmp(pa->nome, pb->nome);
}

// ordena pacientes por ordem de ID
int ordenar_id_paciente(const void *a, const void *b) {
    pacientes *pa = (pacientes *)a;
    pacientes *pb = (pacientes *)b;
    return pa->id-pb->id;
}

void ordenar_paciente_ID(pacientes *p, int n) {
    if (n == 0) {
        printf("Nao existe nenhum pacientes cadastrado no sistema!\n");
        return;
    }
    qsort(p, n, sizeof(pacientes), ordenar_medico_id);
}

void ordenarpacientes(pacientes *x, int n) {
    if (n == 0) {
        printf("Nao existe nenhum pacientes cadastrado no sistema!\n");
        return;
    }
    qsort(x, n, sizeof(pacientes), compararpacientes);
}

