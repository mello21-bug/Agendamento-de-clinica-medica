#include "geral.h"

void adicionar_medico(medicos **medico, int *m, int *idmedico, int *capacidade_medicos){
    medicos a;
    int turno;
    // A variável a do tipo medicos para armazenar o médico que será adicionado.
    // A variável turno para escolher o turno de trabalho do médico.

    a.inicioManha.hora = -1;
    a.inicioManha.minuto = -1;
    a.fimManha.hora = -1;
    a.fimManha.minuto = -1;
    a.inicioTarde.hora = -1;
    a.inicioTarde.minuto = -1;
    a.fimTarde.hora = -1;
    a.fimTarde.minuto = -1;
    // Inicializar todos os horários com valor inválido (-1) para indicar que ainda não foram preenchidos.


    printf("Iniciando o programa de cadastro de medicos...\n");
    a.id=*idmedico;
    (*idmedico)++;
    // Atribui um ID ao médico e incrementa o contador de IDs.
    
    do {
        printf("\nadicione o nome do(a) medico(a): ");
        scanf(" %63[^\n]", a.nome);
        limpar_buffer();

    } while (!validar_nome(a.nome));
    // Solicita o nome do médico até que seja válido (apenas letras e espaços, não vazio).

    do {
        printf("\nadicione a especialidade do(a) medico(a):\n0-Clinico geral\n1-Pediatra\n2-Dermatologista\n3-Cardiologista\n4-Psicologo\n");
        a.especialidade = apenas_numeros();

        if (a.especialidade < 0 && a.especialidade > 4) {
            printf("Resposta invalida, tente novamente!\n");
        }
    } while (a.especialidade < 0 || a.especialidade > 4);
    // Solicita a especialidade do médico até que esteja dentro do intervalo válido (0 a 4).
    
       do {
        printf("\nQual o turno de trabalho?\n1-manha e tarde.\n2-manha.\n3-tarde.\n");
         turno = apenas_numeros();

        switch (turno){
            case 1:
                // Ambos os turnos
                do {
                    do {
                        printf("Digite o horario de inicio da manha (HH MM): ");
                        scanf("%d %d", &a.inicioManha.hora, &a.inicioManha.minuto);
                    } while (!validar_horario(a.inicioManha, 6, 12));
                    do {
                        printf("Digite o horario de fim da manha (HH MM): ");
                        scanf("%d %d", &a.fimManha.hora, &a.fimManha.minuto);
                    } while (!validar_horario(a.fimManha, 6, 12));

                } while (!validar_interalo_horario(a.inicioManha, a.fimManha));
                // Solicita e valida os horários da manhã, garantindo que inicio < fim e horas entre 6 e 12.

                do {
                    do {
                        printf("Digite o horario de inicio da tarde (HH MM): ");
                        scanf("%d %d", &a.inicioTarde.hora, &a.inicioTarde.minuto);
                    } while (!validar_horario(a.inicioTarde, 14, 18));
                    do {
                        printf("Digite o horario de fim da tarde (HH MM): ");
                        scanf("%d %d", &a.fimTarde.hora, &a.fimTarde.minuto);
                    } while (!validar_horario(a.fimTarde, 14, 18));
                } while (!validar_interalo_horario(a.inicioTarde, a.fimTarde));
                getchar();
                // Solicita e valida os horários da tarde, horas entre 14 e 18, inicio < fim.
                break;
            case 2:
                // Somente Manha
                do {
                    do {
                        printf("Digite o horario de inicio da manha (HH MM): ");
                        scanf("%d %d", &a.inicioManha.hora, &a.inicioManha.minuto);
                    } while (!validar_horario(a.inicioManha, 6, 12));
                    do {
                        printf("Digite o horario de fim da manha (HH MM): ");
                        scanf("%d %d", &a.fimManha.hora, &a.fimManha.minuto);
                    } while (!validar_horario(a.fimManha, 6, 12));

                } while (!validar_interalo_horario(a.inicioManha, a.fimManha));
                getchar();
                break;

            case 3:
                // Somente Tarde
                do {
                    do {
                        printf("Digite o horario de inicio da tarde (HH MM): ");
                        scanf("%d %d", &a.inicioTarde.hora, &a.inicioTarde.minuto);
                    } while (!validar_horario(a.inicioTarde, 14, 18));
                    do {
                        printf("Digite o horario de fim da tarde (HH MM): ");
                        scanf("%d %d", &a.fimTarde.hora, &a.fimTarde.minuto);
                    } while (!validar_horario(a.fimTarde, 14, 18));
                } while (!validar_interalo_horario(a.inicioTarde, a.fimTarde));
                getchar();
                break;
            default:
                printf("Opcao de turno invalida. Tente novamente!\n");
        }

    } while (turno < 1 || turno > 3);
    // Repete até que o turno seja válido (1 a 3).

    a.num_atendimentos = 0;
    if (a.inicioManha.hora!=-1) {
        a.num_atendimentos += ((a.fimManha.hora * 60 + a.fimManha.minuto) - (a.inicioManha.hora * 60 + a.inicioManha.minuto))/30;
    }
    if (a.inicioTarde.hora!=-1) {
        a.num_atendimentos+= ((a.fimTarde.hora*60 + a.fimTarde.minuto)-(a.inicioTarde.hora*60+a.inicioTarde.minuto))/30;
    }   // Calcula o número total de atendimentos do médico considerando intervalos de 30 minutos.

    a.atendimentos= (SlotConsulta*) malloc(a.num_atendimentos * sizeof(SlotConsulta));
    if (a.atendimentos==NULL) {
        printf("Erro ao alocar memoria para os slots.\n");
    } else {
        Horario hora_atual;
        int c=0;
        // Inicializa cada slot de atendimento com horários e marca como não ocupado.
        if (a.inicioManha.hora!=-1) {
            hora_atual=a.inicioManha;
            while (c<a.num_atendimentos && (hora_atual.hora<a.fimManha.hora || (hora_atual.hora==a.fimManha.hora && hora_atual.minuto<a.fimManha.minuto))) {
                a.atendimentos[c].inicio=hora_atual;
                a.atendimentos[c].ocupado=false;
                a.atendimentos[c].data.dia = 0;
                a.atendimentos[c].data.mes = 0;
                a.atendimentos[c].data.ano = 0;
                hora_atual = somar_minutos(hora_atual, 30);
                c++;
            }
        }
        if (a.inicioTarde.hora!=-1) {
            hora_atual=a.inicioTarde;
            while (c<a.num_atendimentos && (hora_atual.hora<a.fimTarde.hora || (hora_atual.hora==a.fimTarde.hora && hora_atual.minuto<a.fimTarde.minuto))) {
                a.atendimentos[c].inicio=hora_atual;
                a.atendimentos[c].ocupado=false;
                a.atendimentos[c].data.dia = 0;
                a.atendimentos[c].data.mes = 0;
                a.atendimentos[c].data.ano = 0;
                hora_atual = somar_minutos(hora_atual, 30);
                c++;
            }
        }
    }

    if (*m >= *capacidade_medicos) {
        *capacidade_medicos += 10;
        *medico = (medicos*)realloc(*medico, *capacidade_medicos * sizeof(medicos));
        
        if (*medico == NULL) {
            printf("Erro ao realocar memoria para medicos.\n");
            return;
        }
    }
    // Se o vetor de médicos estiver cheio, realoca memória para mais 10 posições.



    (*medico)[*m]=a;
    (*m)++;
     // Adiciona o médico ao vetor e incrementa o número total de médicos.
}

void listarmedicos(medicos *m, int j) {
    if (j == 0) {
        printf("Nao existe nenhum medico cadastrado no sistema!\n");
        return;
    }
    // Se não há médicos, imprime mensagem e retorna.

    for(int i = 0; i < j; i++) {
        printf("---LISTA DO MEDICO---\n");
        printf("ID: %d\n", m[i].id);
        printf("Nome: %s\n", m[i].nome);

        switch (m[i].especialidade) {
            case ESPEC_CLINICO: printf("Especialidade: Clinico Geral\n"); break;
            case ESPEC_PEDIATRA: printf("Especialidade: Pediatra\n"); break;
            case ESPEC_DERMATO: printf("Especialidade: Dermatologista\n"); break;
            case ESPEC_CARDIO: printf("Especialidade: Cardiologista\n"); break;
            case ESPEC_PSICO: printf("Especialidade: Psicologo\n"); break;
            default: printf("Especialidade: Outra\n"); break;
        }
        if (m[i].inicioManha.hora != -1) {
            printf("Horario: %02d:%02d - %02d:%02d\n", m[i].inicioManha.hora, m[i].inicioManha.minuto, m[i].fimManha.hora, m[i].fimManha.minuto);
        }
        if (m[i].inicioTarde.hora != -1) {
            printf("Horario: %02d:%02d - %02d:%02d\n", m[i].inicioTarde.hora, m[i].inicioTarde.minuto,m[i].fimTarde.hora, m[i].fimTarde.minuto);
        }
        printf("-------------------------------\n");
    }
     // Percorre o vetor e imprime informações de cada médico, incluindo ID, nome, especialidade e horários.
}

medicos* buscaidm(medicos *x, int tam, int y) {
    bool e = false;
    if (tam == 0) {
        printf("nao existe nenhum medico cadastrado no sitemas!");
        return NULL;
    }
    for (int i = 0; i < tam; i++) {
        if (x[i].id == y) {
            return &x[i];
            e=true;
        }
    }
    if(!e){
        printf("Esse ID nao se encontra no sistema.\n");
    }
    return NULL;
    // Busca um médico pelo ID no vetor. Retorna ponteiro para o médico se encontrado, ou NULL se não encontrado.
}

void atualizarm(medicos *m, int t) {
    int idbusca;
    int escolha;
    int turnoo;

    if (t == 0) {
        printf("Nao existe nenhum medico cadastrado no sistema!\n");
        return;
    }
    printf("Digite o ID do medico que voce deseja atualizar as informacoes: \n");
     idbusca=apenas_numeros();

    medicos *aux = buscaidm(m, t, idbusca);
    if (aux != NULL) {
        printf("--- MEDICO ENCONTRADO ---\n");
        printf("ID: %d\n", aux->id);
        printf("Nome: %s\n", aux->nome);
        // Imprime as informações do médico encontrado

        switch (aux->especialidade) {
            case ESPEC_CLINICO: printf("Especialidade: Clinico Geral\n"); break;
            case ESPEC_PEDIATRA: printf("Especialidade: Pediatra\n"); break;
            case ESPEC_DERMATO: printf("Especialidade: Dermatologista\n"); break;
            case ESPEC_CARDIO: printf("Especialidade: Cardiologista\n"); break;
            case ESPEC_PSICO: printf("Especialidade: Psicologo\n"); break;
            default: printf("Especialidade: Outra\n"); break;
        }
        if (aux->inicioManha.hora != -1) {
            printf("Horario (manha): %02d:%02d - %02d:%02d\n", aux->inicioManha.hora, aux->inicioManha.minuto, aux->fimManha.hora, aux->fimManha.minuto);
        }
        if (aux->inicioTarde.hora != -1) {
            printf("Horario (tarde): %02d:%02d - %02d:%02d\n", aux->inicioTarde.hora, aux->inicioTarde.minuto, aux->fimTarde.hora, aux->fimTarde.minuto);
        }
        printf("\nO que voce deseja atualizar?\n1 - Nome\n2 - Especialidade\n3 - Horario\n");
        printf("Digite sua escolha:\n ");
        escolha = apenas_numeros();
        // Pergunta qual informação deseja atualizar

        switch (escolha) {
            case 1:
                printf("Digite o novo nome.\n");
                scanf(" %63[^\n]", aux->nome);
                getchar();
                printf("Atualizacao feita com sucesso!\n");
                break;
            case 2:
                printf("Digite a nova especialidade\n0-Clinico geral\n1-Pediatra\n2-Dermatologista\n3-Cardiologista\n4-psicologo\n");
                scanf("%d", (int*)&aux->especialidade);
                printf("Atualizacao feita com sucesso!\n");
                getchar();
                break;
            case 3:
                printf("Digite o novo horario\n1-Manha e tarde, 2-Manha, 3-tarde\n");
                turnoo = apenas_numeros();
                switch (turnoo) {
                    case 1:
                        printf("Digite o novo horario inicio manha (HH MM): \n");
                        scanf("%d %d", &aux->inicioManha.hora, &aux->inicioManha.minuto);
                        printf("Digite o novo horario fim manha (HH MM): \n");
                        scanf("%d %d", &aux->fimManha.hora, &aux->fimManha.minuto);
                        printf("Digite o novo horario inicio tarde (HH MM): \n");
                        scanf("%d %d", &aux->inicioTarde.hora, &aux->inicioTarde.minuto);
                        printf("Digite o novo horario fim tarde (HH MM): \n");
                        scanf("%d %d", &aux->fimTarde.hora, &aux->fimTarde.minuto);
                        printf("Atualizacao feita com sucesso!\n");
                        break;
                    case 2:
                        printf("Digite o novo horario de inicio da manha (HH MM): ");
                        scanf("%d %d", &aux->inicioManha.hora, &aux->inicioManha.minuto);
                        printf("Digite o novo horario de fim da manha (HH MM): ");
                        scanf("%d %d", &aux->fimManha.hora, &aux->fimManha.minuto);
                        aux->inicioTarde.hora = -1;
                        printf("Atualizacao feita com sucesso!\n");
                        break;
                    case 3:
                        printf("Digite o novo horario de inicio da tarde (HH MM): ");
                        scanf("%d %d", &aux->inicioTarde.hora, &aux->inicioTarde.minuto);
                        printf("Digite o novo horario de fim da tarde (HH MM): ");
                        scanf("%d %d", &aux->fimTarde.hora, &aux->fimTarde.minuto);
                        aux->inicioManha.hora = -1;
                        printf("Atualizacao feita com sucesso!\n");
                        break;
                }
                getchar();
                break;
            default:
                break;
        }
    } else {
        printf("\nMedico com ID %d nao encontrado.\n", idbusca);
    }
    // Atualiza as informações do médico: nome, especialidade ou horários, caso encontrado pelo ID.
}

void remover_medico(medicos **medico, int *num_medicos) {
    int id_busca;
    int i;
    int encontrado = -1;

    if ((*num_medicos) == 0) {
        printf("Nao existe nenhum medico cadastrado no sistema!\n");
        return;
    }

    printf("Digite o ID do medico que sera removido: ");
    id_busca=apenas_numeros();

    for (int i=0; i < *num_medicos; i++) {
        if ((*medico)[i].id == id_busca) {
            encontrado = i;
            break;
        }
    } // Procura o médico pelo ID e guarda o índice encontrado.
    
    if (encontrado !=-1) {
        free((*medico)[encontrado].atendimentos);
        // Libera a memória alocada para os slots de atendimento do médico.

        for (i=encontrado; i < (*num_medicos) -1; i++) {
            (*medico)[i]= (*medico)[i+1];
        }
        (*num_medicos)--;
        // Remove o médico do vetor e ajusta a quantidade total de médicos.


        printf("Medico removido com sucesso!\n");
    } else {
        printf("Medico com o ID %d nao encontrado.\n", id_busca);
    }
}
// Remove um médico do vetor pelo ID, liberando memória alocada e rearranjando o vetor.

int ordenar_medico_id(const void *x, const void *y) {
    medicos *mx = (medicos*) x;
    medicos *my = (medicos*) y;
    return mx -> id - my -> id;
    // ordena médicos pelo ID em ordem crescente.
}

void ordenar_medico_ID(medicos *a, int b) {
    qsort(a, b, sizeof(medicos), ordenar_medico_id);
    // Chama qsort para ordenar o vetor de médicos pelo ID.
}

int comparar_medicos(const void *a, const void *b) {
    medicos *ma = (medicos *)a;
    medicos *mb = (medicos *)b;
    return strcmp(ma->nome, mb->nome);
    //ordena médicos pelo nome em ordem alfabética.
}

void ordenar_medicos(medicos *x, int n) {
    qsort(x, n, sizeof(medicos), comparar_medicos);
    // Chama qsort para ordenar o vetor de médicos pelo nome.
}

int comparar_medicos_esp(const void *a, const void *b) {
    medicos *m1 = (medicos *)a;
    medicos *m2 = (medicos *)b;
    if (m1->especialidade != m2->especialidade) {
        return m1->especialidade - m2->especialidade;
    }
    return strcmp(m1->nome, m2->nome); 
    // Ordena por especialidade, e em caso de empate, pelo nome.
}

void ordenar_medicos_esp(medicos *x, int n) {
    qsort(x, n, sizeof(medicos), comparar_medicos_esp);
    // Ordena médicos por especialidade e, se houver empate, pelo nome usando qsort.
}

