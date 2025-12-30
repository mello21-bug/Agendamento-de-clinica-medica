#include "geral.h"

// ----- PROJETO REALIZADO POR -----
// EMERSON MORAIS DE ARAUJO 
// LETICIA DE MELO SOBRAL
// 1° PERIODO INTRODUCAO A PROGRAMACAO 

// contrucao do menu para gerencias as funcoes relacionadas aos medicos
void menu_medicos(medicos **medico, int *num_medicos, int *idmedico, int *capacidade_medicos) {
    int escolhamedico;
    int idbusca;
    int ordem_medica;

		
    do {
        printf("\nBEM-VINDO A AREA MEDICA, O QUE VOCE DESEJA FAZER?\n0-VOLTAR AO MENU PRINCIPAL\n1-ADICIONAR MEDICO\n2-LISTAR MEDICO\n3-ATUALIZAR MEDICO \n4-REMOVER MEDICO\n5-BUSCAR ID\n6-ORDENAR MEDICO\n7-QUANTIDADE DE MEDICO NO SISTEMA\nINSIRA O NUMERO CORRESPONDENTE A SUA ESCOLHA!\n");
        escolhamedico = apenas_numeros();
        printf("---------------------------\n");
        
        switch (escolhamedico) {
            case 0:
            // saida do menu medicos para o pricipal
            printf("\n----------------------\nVOLTANDO AO MENU DE PRINCIPAL...\n----------------------\n");
                break;
            case 1:
            // adicao de medicos
                adicionar_medico(medico, num_medicos, idmedico, capacidade_medicos); 
                printf("\nCadastro de medico concluido. Total de medicos: %d\n", *num_medicos);
                break;
            // lista todos o medicos cadastrados
            case 2:
                listarmedicos(*medico, *num_medicos); 
                break;
            // atualiza informaçoes medicas
            case 3:
                atualizarm(*medico, *num_medicos); 
                break;
            // remove medicos 
            case 4:
                listarmedicos(*medico, *num_medicos);
                remover_medico(medico, num_medicos);
                break;
            // mostra um medico especifico
            case 5:
                if ((*num_medicos) == 0) {
                    printf("Nao existe nenhum medico cadastrado no sistema!\n");
                    break;
                }
                printf("Digite o id que voce deseja buscar: \n");
                idbusca = apenas_numeros();
                medicos *idmedico = buscaidm(*medico, *num_medicos, idbusca);
                if (idmedico !=NULL) {
                    printf("--- MEDICO ENCONTRADO ---\n");
                    printf("ID: %d\n", idmedico->id);
                    printf("Nome: %s\n", idmedico->nome);

                    switch (idmedico->especialidade) {
                        case ESPEC_CLINICO:
                            printf("Especialidade: Clinico Geral\n");
                            break;
                        case ESPEC_PEDIATRA:
                            printf("Especialidade: Pediatra\n");
                            break;
                        case ESPEC_DERMATO:
                            printf("Especialidade: Dermatologista\n");
                            break;
                        case ESPEC_CARDIO:
                            printf("Especialidade: Cardiologista\n");
                            break;
                        case ESPEC_PSICO:
                            printf("Especialidade: Psicologa\n");
                            break;
                    }
                    if (idmedico->inicioManha.hora != -1) {
                        printf("Horario (manha): %02d:%02d - %02d:%02d\n", idmedico->inicioManha.hora, idmedico->inicioManha.minuto, idmedico->fimManha.hora, idmedico->fimManha.minuto);
                    }
                    if (idmedico->inicioTarde.hora != -1) {
                        printf("Horario (tarde): %02d:%02d - %02d:%02d\n", idmedico->inicioTarde.hora, idmedico->inicioTarde.minuto, idmedico->fimTarde.hora, idmedico->fimTarde.minuto);
                    }
                }
                break;
            // menu de opçoes de ordenacao dos medicos
            case 6:
                if ((*num_medicos) == 0) {
                    printf("Nao existe nenhum medico cadastrado no sistema!\n");
                    break;
                }
                printf("\n1-Ordem alfabetica.\n2-Por ordem de especialidade.\n3-Por ID.\n");
                scanf("%d", &ordem_medica);
                getchar();
                switch (ordem_medica) {
                    case 1:
                        ordenar_medicos(*medico, *num_medicos);
                        listarmedicos(*medico, *num_medicos);
                        break;
                    case 2:
                        ordenar_medicos_esp(*medico, *num_medicos);
                        listarmedicos(*medico, *num_medicos);
                        break;
                    case 3:
                        ordenar_medico_ID(*medico, *num_medicos);
                        listarmedicos(*medico, *num_medicos);
                        break;
                    default:
                        printf("Opcao invalida. Tente novamente!\n");
                        break;
                }
            break;
            //quantidades de medicos cadastrados
            case 7:
                if(*num_medicos>0) {
                    printf("Existe %d medicos cadastrados no sistema!\n", *num_medicos);
                } else {
                    printf("Nao existe nenhum medico cadastrado no sistema!\n");
                }
                break;
            default:
                printf("Opcao invalida. Tente novamente!\n");
                break;
        }
    } while (escolhamedico != 0);
}
// menu para gerencias as funcoes dos pacientes
void menu_pacientes(pacientes **paciente, int *num_pacientes, int *idpaciente, int *capacidade_pacientes) {
    int escolhapaciente;
    int idbuscar;
    int ordempac;
    
    do {
        printf("\nBEM-VINDO A AREA DO PACIENTE, O QUE VOCE DESEJA FAZER?\n0-VOLTAR AO MENU PRINCIPAL\n1-ADICIONAR PACIENTE\n2-LISTAR PACIENTE\n3-ATUALIZAR PACIENTE\n4-REMOVER PACIENTE\n5-BUSCAR ID\n6-ORDENAR PACIENTE\n7-QUANTIDADE DE PACIENTE NO SISTEMA\nINSIRA O NUMERO CORRESPONDENTE A SUA ESCOLHA!\n");
        escolhapaciente = apenas_numeros();
        printf("---------------------------\n");
        
        switch (escolhapaciente) {
            // volta para o menu principal
            case 0:
                printf("\n----------------------\nVOLTANDO AO MENU DE PRINCIPAL...\n----------------------\n");
                break;
            // adiciona novo paciente
            case 1:
                adicionar_paciente(paciente, num_pacientes, idpaciente, capacidade_pacientes);
                printf("\nCadastro de paciente concluido. Total de pacientes: %d\n", *num_pacientes);
                break;
            // lista todos os pacientes cadastrados 
            case 2:
                listarpacientes(*paciente, *num_pacientes); 
                break;
            // atualiza informacoes dos pacientes 
            case 3:
                atualizarpacientes(*paciente, *num_pacientes);
                break;
            // remove pacientes 
            case 4:
                listarpacientes(*paciente, *num_pacientes);
                remover_paciente(paciente, num_pacientes);
                break;
            // busca paciente especifico 
            case 5:
                if ((*num_pacientes) == 0) {
                    printf("Nao existe nenhum pacientes cadastrado no sistema!\n");
                    break;
                }
                printf("Digite o id que voce deseja buscar: \n");
                idbuscar=apenas_numeros();

                pacientes *idpaciente_ptr = buscaidp(*paciente, *num_pacientes, idbuscar);
                if (idpaciente_ptr != NULL) {
                    printf("--- PACIENTE ENCONTRADO ---\n");
                    printf("ID: %d\n", idpaciente_ptr->id);
                    printf("Nome: %s\n", idpaciente_ptr->nome);
                    printf("Contato: %s\n", idpaciente_ptr->contato);
                } else {
                    printf("Paciente com ID %d nao encontrado.\n", idbuscar);
                }
                break;
            // menu de ordenaçao de pacientes
            case 6:
                if ((*num_pacientes) == 0) {
                    printf("Nao existe nenhum medico cadastrado no sistema!\n");
                    break;
                }
                printf("\n1-Ordem alfabetica.\n2-Por ID.\n");
                scanf("%d", &ordempac);
                switch (ordempac) {
                    case 1:
                        ordenarpacientes(*paciente, *num_pacientes);
                        listarpacientes(*paciente, *num_pacientes);
                        getchar();
                        break;
                    case 2:
                        ordenar_paciente_ID(*paciente, *num_pacientes);
                        listarpacientes(*paciente, *num_pacientes);
                        getchar();
                        break;
                    default:
                        printf("Opcao invalida. Tente novamente!\n");
                        break;
                }
                break;
                case 7:
                if(*num_pacientes>0) {
                    printf("Existe %d pacientes cadastrados no sistema!\n", *num_pacientes);
                } else {
                    printf("Nao existe nenhum paciente cadastrado no sistema!\n");
                }
                break;
            default:
                printf("Opcao invalida. Tente novamente!\n");
                break;
                }
        } while (escolhapaciente != 0);
    }

// menu para gerencias funcoes das consultas 
void menu_consultas(medicos **medico, int *num_medicos, int *num_consultas, consultas **consulta, int *idconsulta, int *capacidade_consultas, int *num_pacientes, pacientes **paciente) {
    int escolha_consulta;
    int escolha_id;
    do {
        printf("\nBEM-VINDO A AREA DAS CONSULTAS, O QUE VOCE DESEJA FAZER?\n0-VOLTAR AO MENU PRINCIPAL\n1-ADICIONAR CONSULTA\n2-LISTAR CONSULTAS\n3-ATUALIZAR CONSULTA\n4-REMOVER CONSULTA\n5-BUSCAR ID\n6-MENU DE RELATORIOS\n7-QUANTIDADE DE CONSULTA CADASTRADA NO SISTEMA\nINSIRA O NUMERO CORRESPONDENTE A SUA ESCOLHA!\n");
        escolha_consulta = apenas_numeros();
                
        switch (escolha_consulta){
        // volta para o menu geral
        case 0:
            printf("\n----------------------\nVOLTANDO AO MENU DE PRINCIPAL...\n----------------------\n");
            break;
        // adiciona consulta
        case 1:
                adicionar_consulta(medico, num_medicos, num_consultas, consulta, idconsulta, capacidade_consultas, num_pacientes, *paciente);
            break;
        // lista todas as consultas cadastradas
        case 2:
                listarconsultas(*medico, num_medicos, num_consultas, *consulta, num_pacientes, *paciente);
            break;
        // atualiza consulta expecifica
        case 3:
                atualizarconsulta(num_consultas, consulta, *medico, *num_medicos, *paciente, *num_pacientes);
            break;
        // remove consulta
        case 4:
                listarconsultas(*medico, num_medicos, num_consultas, *consulta, num_pacientes, *paciente);
                remover_consulta(consulta, num_consultas);
            break;
        // exibe consulta especifica 
        case 5:
                if ((*num_consultas) == 0) {
                    printf("Nao existe nenhuma consulta cadastrado no sistema!\n");
                    break;
                }
                printf("Digite o id que voce deseja buscar: \n");
                escolha_id=apenas_numeros();
                consultas *consulta_encontrada = buscaidc(*consulta, num_consultas, escolha_id);
            
                if (consulta_encontrada != NULL) {
                    exibir_consulta(*medico, *num_medicos, consulta_encontrada, *num_pacientes, *paciente);
                } else {
                    printf("Consulta com ID %d nao encontrada.\n", escolha_id);
                }
                break;
        // abre o menu de relatorios
        case 6:
                relatorio(*consulta,*num_consultas,*medico, *num_medicos, *paciente, *num_pacientes);
                break;
        case 7:
             if(*num_consultas>0) {
                    printf("Existe %d consultas cadastrados no sistema!\n", *num_consultas);
                } else {
                    printf("Nao existe nenhuma consulta cadastrada no sistema!\n");
                }
                break;
        default:
                printf("Opcao invalida. Tente novamente!\n");
                break;
        }
    } while (escolha_consulta != 0);
}

int main(){
    //variaveis para parametro dos IDs, contadores de quantidade e outros
    medicos *medico = NULL;
    pacientes *paciente = NULL;
    consultas *consulta = NULL;
    int idmedico = 1, num_medicos = 0;
    int idpaciente = 1, num_pacientes = 0, idtemp;
    int idconsulta = 1, num_consultas = 0;
    int escolha;
    int capacidade_medicos = 10;
    int capacidade_pacientes = 10;
    int capacidade_consultas = 10;
    FILE *arq_medico, *arq_paciente, *arq_consulta;
    char temp[100];

    // alocaçao de memoria inicial dos medicos, pacientes e consultas
    medico = (medicos*) malloc(capacidade_medicos * sizeof(medicos));
    paciente = (pacientes*) malloc(capacidade_pacientes * sizeof(pacientes));
    consulta = (consultas*) malloc(capacidade_consultas * sizeof(consultas));


    if (medico == NULL || paciente == NULL || consulta == NULL) {
        printf("Erro ao alocar memoria inicial. O programa sera encerrado.\n");
        return 1;
    }

    //leitura de medicos no arquivo

    arq_medico = fopen("arq_medico.txt", "r");
    if (arq_medico == NULL) {
        printf("ERRO! Nao foi possivel abrir o arquivo medico para leitura!\n");
        return 1;
    }

    fgets(temp, sizeof(temp), arq_medico);
    fgets(temp, sizeof(temp), arq_medico); 

    while (fscanf(arq_medico, "ID: %d\n", &idtemp) == 1) {
        if (num_medicos>= capacidade_medicos) {
            capacidade_medicos += 10;
            medico = (medicos*)realloc(medico, capacidade_medicos * sizeof(medicos));
            if (medico == NULL) {
                printf("Erro ao realocar memoria para medicos.\n");
                fclose(arq_medico);
                return 1;
            }
        }

        medico[num_medicos].id = idtemp;
        fscanf(arq_medico, "Nome: %[^\n]\n\n", medico[num_medicos].nome);

        fgets(temp, sizeof(temp), arq_medico);

        if (strstr(temp, "Clinico") != NULL) medico[num_medicos].especialidade = 0;
        else if (strstr(temp, "Pediatra") != NULL) medico[num_medicos].especialidade = 1;
        else if (strstr(temp, "Dermatologista") != NULL) medico[num_medicos].especialidade = 2;
        else if (strstr(temp, "Cardiologista") != NULL) medico[num_medicos].especialidade = 3;
        else if (strstr(temp, "Psicologo") != NULL) medico[num_medicos].especialidade = 4;

        fscanf(arq_medico, "Horario: %d:%d - %d:%d\n", &medico[num_medicos].inicioManha.hora, &medico[num_medicos].inicioManha.minuto, &medico[num_medicos].fimManha.hora, &medico[num_medicos].fimManha.minuto);
        fscanf(arq_medico, "Horario: %d:%d - %d:%d\n", &medico[num_medicos].inicioTarde.hora, &medico[num_medicos].inicioTarde.minuto, &medico[num_medicos].fimTarde.hora, &medico[num_medicos].fimTarde.minuto);

        fgets(temp, sizeof(temp), arq_medico);

        medico[num_medicos].num_atendimentos = 0;
        if (medico[num_medicos].inicioManha.hora != -1) {
            medico[num_medicos].num_atendimentos += ((medico[num_medicos].fimManha.hora * 60 + medico[num_medicos].fimManha.minuto) -
            (medico[num_medicos].inicioManha.hora * 60 + medico[num_medicos].inicioManha.minuto)) / 30;
        }
        if (medico[num_medicos].inicioTarde.hora != -1) {
            medico[num_medicos].num_atendimentos += ((medico[num_medicos].fimTarde.hora * 60 + medico[num_medicos].fimTarde.minuto) -
            (medico[num_medicos].inicioTarde.hora * 60 + medico[num_medicos].inicioTarde.minuto)) / 30;
        }

    medico[num_medicos].atendimentos = malloc(medico[num_medicos].num_atendimentos * sizeof(SlotConsulta));

    Horario hora_atual;
    int c = 0;
    if (medico[num_medicos].inicioManha.hora != -1) {
        hora_atual = medico[num_medicos].inicioManha;
        while (c < medico[num_medicos].num_atendimentos &&
            (hora_atual.hora < medico[num_medicos].fimManha.hora ||
            (hora_atual.hora == medico[num_medicos].fimManha.hora && hora_atual.minuto < medico[num_medicos].fimManha.minuto))) {
            medico[num_medicos].atendimentos[c].inicio = hora_atual;
            medico[num_medicos].atendimentos[c].ocupado = false;
            hora_atual = somar_minutos(hora_atual, 30);
            c++;
        }
    }
    if (medico[num_medicos].inicioTarde.hora != -1) {
        hora_atual = medico[num_medicos].inicioTarde;
        while (c < medico[num_medicos].num_atendimentos &&
            (hora_atual.hora < medico[num_medicos].fimTarde.hora ||
            (hora_atual.hora == medico[num_medicos].fimTarde.hora && hora_atual.minuto < medico[num_medicos].fimTarde.minuto))) {
            medico[num_medicos].atendimentos[c].inicio = hora_atual;
            medico[num_medicos].atendimentos[c].ocupado = false;
            hora_atual = somar_minutos(hora_atual, 30);
            c++;
        }
    }

        num_medicos++;
        if (num_medicos > 0) {
        idmedico = medico[num_medicos - 1].id + 1;
        }
        if (medico[num_medicos-1].id >= idmedico) {
            idmedico = medico[num_medicos-1].id + 1;
        }
    }

    fclose(arq_medico);

    printf("\nMedicos lidos do arquivo\n");

    //leitura de pacientes no arquivo

    arq_paciente = fopen("arq_paciente.txt", "r");
    if (arq_paciente == NULL) {
        printf("ERRO! Nao foi possivel abrir o arquivo paciente para leitura!\n");
        return 1;
    }

    fgets(temp, sizeof(temp), arq_paciente);
    fgets(temp, sizeof(temp), arq_paciente); 

    while (fscanf(arq_paciente, "ID: %d\n", &idtemp) == 1) {

        if (num_pacientes>=capacidade_pacientes) {
            capacidade_pacientes += 10;
            pacientes *ptemp = (pacientes*)realloc(paciente, capacidade_pacientes * sizeof(pacientes));
            if (ptemp==NULL) {
                printf("Erro ao realocar memoria para pacientes.\n");
                fclose(arq_paciente);
                return 1;
            }
            paciente = ptemp;
        }
        paciente[num_pacientes].id = idtemp;
        fscanf(arq_paciente, "Nome: %[^\n]\n", paciente[num_pacientes].nome);
        fscanf(arq_paciente, "contato: %[^\n]\n", paciente[num_pacientes].contato);

        fgets(temp, sizeof(temp), arq_paciente);
        idpaciente++;
        num_pacientes++;
    }

    fclose(arq_paciente);

    printf("\nPacientes lidos do arquivo\n");

    // leitura da consulta no arquivo

    arq_consulta = fopen("arq_consulta.txt", "r");

if (arq_consulta == NULL) {
    printf("ERRO! Nao foi possivel abrir o arquivo consulta para leitura!\n");
    return 1;
}

fgets(temp, sizeof(temp), arq_consulta);
fgets(temp, sizeof(temp), arq_consulta);

char status_str[50];

while (fscanf(arq_consulta, "ID: %d\n", &idtemp) == 1) {
    if (num_consultas >= capacidade_consultas) {
        capacidade_consultas += 10;
        consultas *temp = realloc(consulta, capacidade_consultas * sizeof(consultas));
        if (temp == NULL) {
            printf("Erro ao realocar memoria para consultas.\n");
            fclose(arq_consulta);
            return 1;
        }
        consulta = temp;
    }

    consulta[num_consultas].id = idtemp;
    fscanf(arq_consulta, "ID do medico: %d\n", &consulta[num_consultas].idMedico);
    fscanf(arq_consulta, "ID do paciente: %d\n", &consulta[num_consultas].idPaciente);
    fscanf(arq_consulta, "Data: %d/%d/%d\n", &consulta[num_consultas].data.dia, &consulta[num_consultas].data.mes, &consulta[num_consultas].data.ano);
    fscanf(arq_consulta, "Prioridade: %d\n", &consulta[num_consultas].prioridade);
    fscanf(arq_consulta, "Horario de inicio %d:%d\n", &consulta[num_consultas].inicio.hora, &consulta[num_consultas].inicio.minuto);
    fscanf(arq_consulta, "Horario de fim %d:%d\n", &consulta[num_consultas].fim.hora, &consulta[num_consultas].fim.minuto);
    fscanf(arq_consulta, "Status da consulta: %[^\n]\n", status_str);

    if (strstr(status_str, "Agendada") != NULL) consulta[num_consultas].status = CONS_AGENDADA;
    else if (strstr(status_str, "Cancelada") != NULL) consulta[num_consultas].status = CONS_CANCELADA;
    else if (strstr(status_str, "Concluida") != NULL) consulta[num_consultas].status = CONS_CONCLUIDA;
    else if (strstr(status_str, "Falta") != NULL) consulta[num_consultas].status = CONS_FALTA;

    medicos *medico_consulta = buscaidm(medico, num_medicos, consulta[num_consultas].idMedico);
    if (medico_consulta != NULL) {
        for (int i = 0; i < medico_consulta->num_atendimentos; i++) {
            if (medico_consulta->atendimentos[i].inicio.hora == consulta[num_consultas].inicio.hora &&
                medico_consulta->atendimentos[i].inicio.minuto == consulta[num_consultas].inicio.minuto) {
                medico_consulta->atendimentos[i].ocupado = true;
                medico_consulta->atendimentos[i].data = consulta[num_consultas].data;
                consulta[num_consultas].indice_atendimento = i;
                break;
            }
        }
    }

    fgets(temp, sizeof(temp), arq_consulta);

    num_consultas++;
    idconsulta++;
}

fclose(arq_consulta);

printf("\nConsultas lidas do arquivo\n");

// chamada do menu principal, o qual chama todos os outros menus 
    do {
        printf("\nBEM-VINDO, O QUE VOCE DESEJA FAZER?\n0-SAIR DO SISTEMA\n1-AREA MEDICA\n2-AREA DO PACIENTE\n3-AREA DAS CONSULTAS\nINSIRA O NUMERO CORRESPONDENTE A SUA ESCOLHA!\n");
        escolha = apenas_numeros();
        printf("---------------------------\n");

        switch (escolha) {
            case 0:
                printf("Saindo do sistema. Ate mais!\n");
                break;
            case 1:
                menu_medicos(&medico, &num_medicos, &idmedico, &capacidade_medicos);
                break;
            case 2:
                menu_pacientes(&paciente, &num_pacientes, &idpaciente, &capacidade_pacientes);
                break;
            case 3:
                menu_consultas(&medico, &num_medicos, &num_consultas, &consulta, &idconsulta, &capacidade_consultas, &num_pacientes, &paciente);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (escolha != 0);

    // grava as informacoes novas antigas e alteradas no arquivo medico
    arq_medico = fopen("arq_medico.txt", "w");
    if(arq_medico == NULL){
		printf("ERRO! arquivo medico nao foi aberto!");
	}
	else{
        fprintf(arq_medico, "medicos cadastrados:\n");
        fprintf(arq_medico, "---------------------------\n");

        for (int i = 0; i < num_medicos; i++) {
            fprintf(arq_medico, "ID: %d\n", medico[i].id);
            fprintf(arq_medico, "Nome: %s\n", medico[i].nome);
            switch (medico[i].especialidade) {
                case ESPEC_CLINICO: fprintf(arq_medico,"Especialidade: Clinico Geral\n"); break;
                case ESPEC_PEDIATRA: fprintf(arq_medico,"Especialidade: Pediatra\n"); break;
                case ESPEC_DERMATO: fprintf(arq_medico,"Especialidade: Dermatologista\n"); break;
                case ESPEC_CARDIO: fprintf(arq_medico,"Especialidade: Cardiologista\n"); break;
                case ESPEC_PSICO: fprintf(arq_medico,"Especialidade: Psicologo\n"); break;
                default: break;
            }

        if (medico[i].inicioManha.hora != -1) {
            fprintf(arq_medico,"Horario: %02d:%02d - %02d:%02d\n", medico[i].inicioManha.hora, medico[i].inicioManha.minuto, medico[i].fimManha.hora, medico[i].fimManha.minuto);
        } else {
            fprintf(arq_medico,"Horario: -1:-1 - -1:-1\n");
        }
        if (medico[i].inicioTarde.hora != -1) {
            fprintf(arq_medico,"Horario: %02d:%02d - %02d:%02d\n", medico[i].inicioTarde.hora, medico[i].inicioTarde.minuto,medico[i].fimTarde.hora, medico[i].fimTarde.minuto);
        } else {
            fprintf(arq_medico,"Horario: -1:-1 - -1:-1\n");
        }
            fprintf(arq_medico, "---------------------------\n");	
	    }
        fclose(arq_medico);
        printf("\n-----DADOS DOS MEDICOS SALVOS COM SUCESSO!!-----\n");
    }

    // grava as informacoes novas antigas e alteradas no arquivo paciente
    arq_paciente = fopen("arq_paciente.txt", "w");
    if(arq_paciente == NULL){
        printf("ERRO! o arquivo paciente nao foi aberto");
    } else {
        fprintf(arq_paciente, "pacientes cadastrados: %d\n", num_medicos);
        fprintf(arq_paciente, "---------------------------\n");

        for (int i = 0; i < num_pacientes; i++){
            fprintf(arq_paciente, "ID: %d\n", paciente[i].id);
            fprintf(arq_paciente, "Nome: %s\n", paciente[i].nome);
            fprintf(arq_paciente, "contato: %s\n", paciente[i].contato);
            fprintf(arq_paciente, "---------------------------\n");
        }
        fclose(arq_paciente);
        printf("\n-----DADOS DOS PACIENTES SALVOS COM SUCESSO!!-----\n");

    }

    // grava as informacoes novas antigas e alteradas no arquivo consulta
    arq_consulta = fopen("arq_consulta.txt", "w");
    if(arq_consulta == NULL){
        printf("ERRO! o arquivo consulta nao foi aberto");
    } else {
        fprintf(arq_consulta, "consultas cadastradas\n");
        fprintf(arq_consulta, "---------------------------\n");

        for (int i = 0; i < num_consultas; i++){
            fprintf(arq_consulta, "ID: %d\n", consulta[i].id);
            fprintf(arq_consulta, "ID do medico: %d\n", consulta[i].idMedico);
            fprintf(arq_consulta, "ID do paciente: %d\n", consulta[i].idPaciente);
            fprintf(arq_consulta, "Data: %02d/%02d/%04d\n", consulta[i].data.dia, consulta[i].data.mes, consulta[i].data.ano);
            fprintf(arq_consulta, "Prioridade: %d\n", consulta[i].prioridade);
            fprintf(arq_consulta, "Horario de inicio %02d:%02d\n", consulta[i].inicio.hora, consulta[i].inicio.minuto);
            fprintf(arq_consulta, "Horario de fim %02d:%02d\n", consulta[i].fim.hora, consulta[i].fim.minuto);
            switch (consulta[i].status){
                case CONS_AGENDADA: fprintf(arq_consulta, "Status da consulta: Agendada\n"); break;
                case CONS_CANCELADA: fprintf(arq_consulta, "Status da consulta: Cancelada\n"); break;
                case CONS_CONCLUIDA: fprintf(arq_consulta, "Status da consulta: Concluida\n"); break;
                case CONS_FALTA: fprintf(arq_consulta, "Status da consulta: Falta\n"); break;
                default: break;
            }
            fprintf(arq_consulta, "---------------------------\n");
        }
        fclose(arq_consulta);
        printf("\n-----DADOS DAS CONSULTAS SALVOS COM SUCESSO!!-----\n\n");
    }

    for (int i = 0; i < num_medicos; i++) {
        free(medico[i].atendimentos);
    }

    // libera a memoria alocada extra
    free(medico);
    free(paciente);
    free(consulta);
    
    return 0;
}