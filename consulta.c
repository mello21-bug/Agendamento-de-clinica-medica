#include "geral.h"

bool anobissexto(int ano) {
    if ((ano%400==0) || (ano%4==0 && ano%100!=0)) {
        return true;
    }
    return false;
}

// verificaçoes gerais de datas (intevalo entre dias e meses)

bool validar_data(Data d) {
    if (d.dia<1 || d.dia >31) {
        printf("Erro: o dia esta fora do intervalo, prencha o campo dd com numeros entre 1 a 31.\n");
        return false;
    }

    if (d.mes<1 || d.mes>12) {
        printf("Erro: o mes esta fora do intervalo, prencha o campo mm com numeros entre 1 a 12.\n");
        return false;
    }

    if (d.ano<2025) {
        printf("O agendamento das consultas so sao marcadas a partir de 2025.\n");
        return false;
    }

    if (d.mes==2) {
        if (anobissexto(d.ano)) {
            if (d.dia>29) {
                printf("Erro: o dia esta fora do intervalo, prencha o campo dd com numeros entre 1 a 29.\n");
                return false;
            }
        } else {
            if (d.dia>28) {
                printf("Erro: o dia esta fora do intervalo, prencha o campo dd com numeros entre 1 a 28.\n");
                return false;
            }
        }
    } else if (d.mes==4 || d.mes==6 || d.mes==9 || d.mes==11) {
        if (d.dia>30) {
            printf("Erro: o dia esta fora do intervalo, prencha o campo dd com numeros entre 1 a 30.\n");
            return false;
        }
    }
    return true;
}

// funcao para montar os horarios do turno do medico (conta de 30 em 30 minutos cada atendimento)
void processar_turno(medicos *medico, Horario inicio_turno, Horario fim_turno) {
    Horario hora_atual = inicio_turno;
    int atendiemnto_count = 0;
    while (hora_atual.hora < fim_turno.hora || (hora_atual.hora == fim_turno.hora && hora_atual.minuto < fim_turno.minuto)) {
        if (atendiemnto_count >= medico->num_atendimentos) {
            break; // para antes de passar do horario final
        }
        if (!medico->atendimentos[atendiemnto_count].ocupado) {
            printf("%d: %02d:%02d\n", atendiemnto_count, hora_atual.hora, hora_atual.minuto);
            medico->atendimentos[atendiemnto_count].inicio = hora_atual;
        }
        hora_atual = somar_minutos(hora_atual, 30); // soma 30 min
        atendiemnto_count++;
    }
}

bool data_igual(Data a, Data b) {
    return a.dia==b.dia && a.mes==b.mes && a.ano==b.ano;
}

// adicao de consultas
void adicionar_consulta(medicos **medico, int *num_medicos, int *c, consultas **consulta, int *idconsulta, int *capacidade_consultas, int *num_pacientes, pacientes *paciente) {
    consultas a;
    int idMedico, idPaciente, id_duplicado;
    int atendimento_escolhido = -1;
    medicos *medico_selecionado = NULL;
    pacientes *paciente_selecionado = NULL;
    int prioridade;
    bool consulta_encontrado = false;

    // verificaçao para entrar no sistema somente se houver medicos e pacientes cadastrados
    if (*num_medicos == 0) {
        printf("Nao ha medicos cadastrados. Agendamento cancelado.\n");
        return;
    }
    if (*num_pacientes == 0) {
        printf("Nao ha pacientes cadastrados. Agendamento cancelado.\n");
        return;
    }

    printf("\n--- AGENDAMENTO DE CONSULTA ---\n");

    // lista medicos e paceintes para facilitar a escolha por ID

    listarmedicos(*medico, *num_medicos);
    printf("Qual o ID do medico para a consulta? ");
    idMedico = apenas_numeros();
    
    medico_selecionado = buscaidm(*medico, *num_medicos, idMedico);
    if (medico_selecionado == NULL) {
        printf("Medico nao encontrado. Agendamento cancelado.\n");
        return;
    }

    listarpacientes(paciente, *num_pacientes);
    printf("Qual o ID do paciente para a consulta? ");
    idPaciente = apenas_numeros();

    paciente_selecionado = buscaidp(paciente, *num_pacientes, idPaciente);
    if (paciente_selecionado == NULL) {
        printf("Paciente nao encontrado. Agendamento cancelado.\n");
        return;
    }

    // escolha da data para a consulta
    Data data_temp;
    do {
        printf("Qual a data da consulta? (dd mm aaaa) ");
        scanf("%d %d %d", &data_temp.dia, &data_temp.mes, &data_temp.ano);
    } while (!validar_data(data_temp));
    limpar_buffer();
    
    // escolha de prioridade, caso escolha 0 mandara o usuario para escolha de horarios, caso nao, procura o menor horario possivel 
    printf("qual a prioridade do caso?\n0-NORMAL\n1-URGENTE\n");
    prioridade = apenas_numeros();

    if (prioridade != 1){
        printf("\n--- Horarios disponiveis para %s ---\n", medico_selecionado->nome);

        // verifica se o slot da consulta esta vago, caso esteja ele escreve como opcao para o usuario

        bool h_disposnivel=false;
        for (int i=0; i<medico_selecionado->num_atendimentos; i++) {
            if (!medico_selecionado->atendimentos[i].ocupado || (medico_selecionado->atendimentos[i].ocupado && !data_igual(medico_selecionado->atendimentos[i].data, data_temp))) {
                printf("%d: %02d:%02d\n", i, medico_selecionado->atendimentos[i].inicio.hora, medico_selecionado->atendimentos[i].inicio.minuto);
                h_disposnivel=true;
            }
        }
        if (h_disposnivel) {
            printf("Escolha o horario da consulta: ");
            scanf("%d", &atendimento_escolhido);
            consulta_encontrado = true;
            getchar();

        } else {
            printf("Nenhum horario disponivel para a data e medico selecionados.\n");
            return; // Retorna para cancelar o agendamento
        }
    } else {
        printf("Caso urgente detectado. Buscando o horario mais cedo possivel...\n");
        for (int i = 0; i < medico_selecionado->num_atendimentos; i++) {
            if (!medico_selecionado->atendimentos[i].ocupado || (medico_selecionado->atendimentos[i].ocupado && !data_igual(medico_selecionado->atendimentos[i].data, data_temp))) {
                atendimento_escolhido = i;
                consulta_encontrado = true;
                break;
            }
        }

    }


    // definiçao de todas as variaveis presentes na struct de consulta 
    if (consulta_encontrado && atendimento_escolhido >= 0 && atendimento_escolhido < medico_selecionado->num_atendimentos && (!medico_selecionado->atendimentos[atendimento_escolhido].ocupado || (medico_selecionado->atendimentos[atendimento_escolhido].ocupado && !data_igual(medico_selecionado->atendimentos[atendimento_escolhido].data, data_temp)))) {

    int maior_id = 0;
        for (int i = 0; i < *c; i++) {
            if ((*consulta)[i].id > maior_id) {
                maior_id = (*consulta)[i].id;
            }
        }
        a.id = maior_id + 1;
        (*idconsulta) = a.id + 1;

        a.idMedico = idMedico;
        a.idPaciente = idPaciente;
        a.data = data_temp;
        a.inicio = medico_selecionado->atendimentos[atendimento_escolhido].inicio;
        a.fim = somar_minutos(a.inicio, 30);
        a.status = CONS_AGENDADA;
        a.prioridade = prioridade; 
        a.indice_atendimento = atendimento_escolhido;
        medico_selecionado->atendimentos[atendimento_escolhido].data = data_temp;
        medico_selecionado->atendimentos[atendimento_escolhido].ocupado = true;
        
        // alocaçao dinamica da memoria para consltas 
        if (*c >= *capacidade_consultas) {
            *capacidade_consultas += 10;
            *consulta = (consultas*)realloc(*consulta, *capacidade_consultas * sizeof(consultas));

            if (*consulta == NULL) {
                printf("Erro ao realocar memoria para consultas.\n");
                return;
            }
        }

        (*consulta)[*c] = a;
        (*c)++;
        (*idconsulta)++;

        printf("\nConsulta agendada com sucesso!\n");
    } else {
        printf("Slot de consulta invalido ou ja ocupado. Agendamento cancelado.\n");
        getchar();
    }
}

// lista todas as consultas ja agendadas

void listarconsultas(medicos *medico, int *num_medicos, int *c, consultas *consulta, int *num_pacientes, pacientes *paciente){
    int idMedicoaux, idPacienteaux;
    if (*c== 0) {
        printf("Nao existe nenhuma consulta cadastrado no sistema!\n");
        return;
    }

    // procura todas as infomacoes necessarias para montar a consulta (nome de paciente, medico) e aprensanta junto com os elementos da struct de consulta
    for(int i = 0; i < *c; i++) {
        printf("---LISTA DE CONSULTAS---\n");
        printf("ID da consulta: %d\n", consulta[i].id);

        printf("\n");
        idMedicoaux = consulta[i].idMedico;
        medicos *medico_aux = buscaidm(medico, *num_medicos, idMedicoaux);
        if (medico_aux != NULL) {
            printf("Medico: %s\n", medico_aux->nome);
            printf("ID do medico: %d\n", consulta[i].idMedico);
            switch (medico_aux->especialidade) {
                case ESPEC_CLINICO: printf("Especialidade: Clinico Geral\n"); break;
                case ESPEC_PEDIATRA: printf("Especialidade: Pediatra\n"); break;
                case ESPEC_DERMATO: printf("Especialidade: Dermatologista\n"); break;
                case ESPEC_CARDIO: printf("Especialidade: Cardiologista\n"); break;
                case ESPEC_PSICO: printf("Especialidade: Psicologo\n"); break;
                default: printf("Especialidade: Outra\n"); break;
            }
        }

        printf("\n");
        idPacienteaux = consulta[i].idPaciente;
        pacientes *paciente_aux = buscaidp(paciente, *num_pacientes, idPacienteaux);
        if (paciente_aux != NULL) {
            printf("Paciente: %s\n", paciente_aux->nome);
            printf("ID do paciente: %d\n", paciente_aux->id);
            printf("Contato: %s\n", paciente_aux->contato);
        } else {
            printf("Paciente com ID %d nao encontrado.\n\n", idPacienteaux);
        }

        printf("Data: %02d/%02d/%4d\n", consulta[i].data.dia, consulta[i].data.mes, consulta[i].data.ano);
        printf("Horario de inicio %02d:%02d\n", consulta[i].inicio.hora, consulta[i].inicio.minuto);
        printf("Horario de fim %02d:%02d\n", consulta[i].fim.hora, consulta[i].fim.minuto);
        switch (consulta[i].status){
            case CONS_AGENDADA:
            printf("Status da consulta: Agendada\n");
            break;
            case CONS_CANCELADA:
            printf("Status da consulta: Cancelada\n");
            break;
            case CONS_CONCLUIDA:
            printf("Status da consulta: Concluida\n");
            break;
            case CONS_FALTA:
            printf("Status da consulta: Falta\n");
            break;
            default: break;
        }
        printf("-------------------------------\n");
    }
}

// busca uma consulta por determinado ID
consultas* buscaidc(consultas *consulta, int *c, int idcerto) {
    for (int i = 0; i < *c; i++) {
        if (consulta[i].id == idcerto) {
            return &consulta[i];
        }
    }
    return NULL;
}

// exibe uma consulta (mesmo funcionamento da listar_consultas, porem eh unitario)
void exibir_consulta(medicos *medico, int num_medicos, consultas *consulta, int num_pacientes, pacientes *paciente){
 
    printf("--- CONSULTA ENCONTRADA ---\n");
    printf("ID: %d\n\n", consulta->id);

    medicos *medico_encontrado = buscaidm(medico, num_medicos, consulta->idMedico);
    if (medico_encontrado != NULL){
        printf("Medico: %s\n", medico_encontrado->nome);
        printf("ID do medico: %d\n", medico_encontrado->id);
        switch (medico_encontrado->especialidade) {
            case ESPEC_CLINICO: printf("Especialidade: Clinico Geral\n"); break;
            case ESPEC_PEDIATRA: printf("Especialidade: Pediatra\n"); break;
            case ESPEC_DERMATO: printf("Especialidade: Dermatologista\n"); break;
            case ESPEC_CARDIO: printf("Especialidade: Cardiologista\n"); break;
            case ESPEC_PSICO: printf("Especialidade: Psicologo\n"); break;
            default: printf("Especialidade: Outra\n"); break;
        }
    } else {
        printf("Medico (ID: %d) nao encontrado.\n", consulta->idMedico);
    }
    
    printf("\n");
    pacientes *paciente_escolhido = buscaidp(paciente, num_pacientes, consulta->idPaciente);
    if (paciente_escolhido != NULL){
        printf("Paciente: %s\n", paciente_escolhido->nome);
        printf("ID do paciente: %d\n", paciente_escolhido->id);
        printf("Contato: %s\n", paciente_escolhido->contato);
    } else {
        printf("Paciente (ID: %d) nao encontrado.\n\n", consulta->idPaciente);
    }

    printf("Data: %02d/%02d/%04d\n", consulta->data.dia, consulta->data.mes, consulta->data.ano);
    printf("Horario de inicio %02d:%02d\n", consulta->inicio.hora, consulta->inicio.minuto);
    printf("Horario de fim %02d:%02d\n", consulta->fim.hora, consulta->fim.minuto);
    switch (consulta->status){
        case CONS_AGENDADA: printf("Status da consulta: Agendada\n"); break;
        case CONS_CANCELADA: printf("Status da consulta: Cancelada\n"); break;
        case CONS_CONCLUIDA: printf("Status da consulta: Concluida\n"); break;
        case CONS_FALTA: printf("Status da consulta: Faltada\n"); break;
        default: break;
    }
    printf("-------------------------------\n");
}

// atualiza uma consulta em especifico 
void atualizarconsulta(int *c, consultas **consulta, medicos *medico, int num_medicos, pacientes *paciente, int num_pacientes){
    consultas *cauxi;
    int idaux, escolha, novo_status;
    Data data_aux;
    int escolha_horario;


    if ((*c) == 0) {
        printf("Nao existe nenhuma consulta cadastrado no sistema!\n");
        return;
    }

    printf("qual o ID da consulta que sera atualizada?\n");
    idaux=apenas_numeros();
    cauxi = buscaidc(*consulta, c, idaux);
    if (cauxi == NULL){
        printf("\nID NAO ENCONTRADO!\n");
        return;
    }
    medicos *medico_c = buscaidm(medico, num_medicos, cauxi->idMedico);
    
    if (cauxi != NULL) {

        exibir_consulta(medico, num_medicos, cauxi, num_pacientes, paciente);
        printf("o que voce quer modificar?\n1-DATA\n2-HORARIO\n3-STAUTS DA CONSULTA\nINSIRA O NUMERO CORRESPONDENTE A SUA ESCOLHA: ");
        escolha = apenas_numeros();

        switch (escolha){
            // atualiza por data
        case 1:
                do {
                    printf("qual a data nova?");
                    scanf("%d %d %d", &data_aux.dia, &data_aux.mes, &data_aux.ano);
                } while (!validar_data(data_aux));
                cauxi->data = data_aux;
                printf("Data da consulta atualizada com sucesso!\n");
            break;
            // atualiza por horario
        case 2:
                if (medico_c != NULL) {
                    printf("\n--- Horarios disponiveis para %s ---\n", medico_c->nome);

                    if (medico_c->inicioManha.hora != -1) {
                        processar_turno(medico_c, medico_c->inicioManha, medico_c->fimManha);
                    }
                    if (medico_c->inicioTarde.hora != -1) {
                        processar_turno(medico_c, medico_c->inicioTarde, medico_c->fimTarde);
                    }

                    printf("\nEscolha o horario da consulta: ");
                    escolha_horario = apenas_numeros();

                    int indice_atendimento_novo = escolha_horario;

                    if (indice_atendimento_novo >= 0 && indice_atendimento_novo < medico_c->num_atendimentos && !medico_c->atendimentos[indice_atendimento_novo].ocupado) {
            
                        if (cauxi->indice_atendimento >= 0 && cauxi->indice_atendimento < medico_c->num_atendimentos) {
                            medico_c->atendimentos[cauxi->indice_atendimento].ocupado = false;
                        }

                        cauxi->inicio = medico_c->atendimentos[indice_atendimento_novo].inicio;
                        cauxi->fim = somar_minutos(cauxi->inicio, 30);
                        cauxi->indice_atendimento = indice_atendimento_novo;
                        
                
                        medico_c->atendimentos[indice_atendimento_novo].ocupado = true;
                        medico_c->atendimentos[indice_atendimento_novo].data = cauxi->data;

                        printf("Horario da consulta atualizado com sucesso para %02d:%02d!\n", cauxi->inicio.hora, cauxi->inicio.minuto);
                    } else {
                        printf("Opcao de horario invalida ou ja ocupada. Nenhum dado foi alterado.\n");
                    }
                } else {
                    printf("Erro: Medico da consulta nao encontrado.\n");
            }
                break;
            // atualiza por status
        case 3:
            printf("Qual o novo status da consulta?\n1-AGENDADA\n2-CONCLUIDA\n3-CANCELADA\n4-FALTA\nescolha uma opcao: ");
            novo_status = apenas_numeros();
            switch (novo_status){
                case 1: cauxi->status=CONS_AGENDADA; break;
                case 2: cauxi->status=CONS_CONCLUIDA; break;
                case 3: cauxi->status=CONS_CANCELADA; break;
                case 4: cauxi->status=CONS_FALTA; break;
                default: break;
            }
            printf("status atualizado com sucesso!\n");
            break;
        default:
            printf("opcao invalida!\n");
            break;
        }
    } else {
        printf("Consulta com ID %d nao encontrada.\n", idaux);
    }
}

// remove uma consulta especifica
void remover_consulta(consultas **c, int *tc) {
    int buscaidd;
    int encont = 0;

    if (*tc==0) {
        printf("Nenhuma consultada foi marcada!\n");
        return;
    }
    // busca a consulta escolhida, caso for econtrada eh sobreposta por outra
    printf("Digite o id da consulta que voce deseja remover: \n");
    buscaidd=apenas_numeros();

    for (int i=0; i<*tc; i++) {
        if ((*c)[i].id==buscaidd) {
            for (int j=i; j<*tc-1; j++) {
                (*c)[j]=(*c)[j+1];
            }
            (*tc)--;
            encont=1;
            printf("Consulta com ID %d removida com sucesso!\n", buscaidd);
            break;
        }
    }
    if (!encont) {
        printf("Nao foi encontrado a onsulta com ID %d.\n", buscaidd);
    }

}

//modalidades de exibicao de consultas
void relatorio(consultas *consulta, int nc, medicos *medico, int nm, pacientes *paciente, int np) {
    int idm, j;
    bool encontrei=false;
    int prioridade_filtro, esp_filtro;    
    StatusConsulta filtrocons;
    Data filtro_data;
    if (nc==0) {
        printf("Nao ha consultas agendadas para gerar relatorio.\n");
        return;
    }
    int filtro;
    
    do {
        printf("\n--- GERAR RELATORIO DE CONSULTAS ---\n");
        printf("Escolha o criterio de filtragem:\n");
        printf("0 - voltar ao menu de consultas\n");
        printf("1 - Por Medico\n");
        printf("2 - Por Medico e dia\n");
        printf("3 - Por Medico e semana\n");
        printf("4 - Por Paciente\n");
        printf("5 - Por Status\n");
        printf("6 - Por Especialidade\n");
        printf("7 - Por data\n");
        printf("Opcao: ");
        filtro = apenas_numeros();

        switch (filtro) {
            case 0:
                printf("\n----------------------\nVOLTANDO AO MENU DE CONSULTAS...\n----------------------\n");
                break;
            // por medico
            case 1:
                    if (nm == 0){
                        printf("nao ha medico cadastrados");
                        break;
                    } else {
                        printf("Digite o id do medico: \n");
                        idm = apenas_numeros();
                        for (int i=0; i<nc; i++) {
                            if (consulta[i].idMedico== idm) {
                                exibir_consulta(medico,nm, &consulta[i], np, paciente);
                                encontrei = true;
                            }
                        }
                        break;
                    }
            // por dia e medico
            case 2:
                if (nm == 0 || nc == 0){
                        printf("nao ha medicos ou consultas cadastrados");
                        break;
                    } else {
                        printf("Digite o id do medico: \n");
                        idm = apenas_numeros();
                        printf("Digite a data (dd mm aaaa): ");
                        scanf("%d %d %d", &filtro_data.dia, &filtro_data.mes, &filtro_data.ano);
                        for (int i=0; i<nc; i++) {
                            if (consulta[i].idMedico == idm && consulta[i].data.dia == filtro_data.dia && consulta[i].data.mes == filtro_data.mes && consulta[i].data.ano == filtro_data.ano) {
                                exibir_consulta(medico,nm, &consulta[i], np, paciente);
                                encontrei = true;
                            }
                        }
                        if (!encontrei){
                            printf("\nnenhuma consulta marcada para o dia %d\n\n", filtro_data.dia);
                        }
                    }
                getchar();
                break;
            // por semana e medico
            case 3:
                if (nm == 0 || nc == 0){
                        printf("nao ha medicos ou consultas cadastrados");
                        break;
                    } else {
                        printf("Digite o id do medico: \n");
                        idm = apenas_numeros();
                        printf("Digite a data do inicio da semana (dd mm aaaa): ");
                        scanf("%d %d %d", &filtro_data.dia, &filtro_data.mes, &filtro_data.ano);
                        for (j=0; j<5; j++){
                            for (int i=0; i<nc; i++) {
                                if (consulta[i].idMedico == idm && consulta[i].data.dia == filtro_data.dia && consulta[i].data.mes == filtro_data.mes && consulta[i].data.ano == filtro_data.ano) {
                                    printf("----- consultas marcadas para o dia %02d -----\n", filtro_data.dia);
                                    exibir_consulta(medico,nm, &consulta[i], np, paciente);
                                    encontrei = true;
                                }
                            }
                            if (!encontrei){
                                printf("\nnenhuma consultas marcadas\n\n");
                            }

                            filtro_data.dia++;
                        }
                    }
                getchar();
            break;
            // por paciente
            case 4:
                if (np == 0){
                    printf("nao ha pacientes cadastrados");
                    break;
                } else {
                    printf("Digite o id do paciente: \n");
                    idm = apenas_numeros();
                    for (int i=0; i<nc; i++) {
                        if (consulta[i].idPaciente==idm) {
                            exibir_consulta(medico,nm, &consulta[i], np, paciente);
                            encontrei = true;
                        }
                    }
                    break;
                }
             
            // por status    
            case 5:
                do{
                    printf("Escolha o status:\n");
                    printf("0 - Agendada\n1 - Concluida\n2 - Cancelada\n3 - Falta\n");
                    printf("Opcao: ");
                    scanf ("%d", (int *)&filtrocons);
                    if (filtrocons < 0 || filtrocons > 3){
                        printf("\nESCOLHA INVALIDA! Tente novamente (entre 0 e 3)\n");
                    }
                } while (filtrocons < 0 || filtrocons > 3);

                for (int i=0; i<nc; i++) {
                    if (consulta[i].status==filtrocons) {
                        exibir_consulta(medico,nm, &consulta[i], np, paciente);
                        encontrei = true;
                    }
                }
                if (!encontrei){
                    printf("nenhuma consulta encontrada!\n"); 
                }
                getchar();
                break;
            
            // por especialidade 
            case 6:
                if (nm == 0){
                    printf("nao ha medico cadastrados");
                    break;
                } else {
                    do{
                        printf("Escolha a especialidade:\n");
                        printf("0 - Clinico geral\n1 - Pediatra\n2 - Dermatologista\n3 - Cardiologista\n4 - Psicologo\n");
                        printf("Opcao: ");
                        scanf("%d", &esp_filtro);
                        if (esp_filtro < 0 || esp_filtro > 4){
                            printf("\nESCOLHA INVALIDA! Tente novamente (entre 0 e 4)\n");
                        }
                    } while (esp_filtro < 0 || esp_filtro > 4);

                    for (int i=0; i<nc; i++) {
                        medicos *medico_esp = buscaidm(medico, nm, consulta[i].idMedico);
                        if (medico_esp != NULL && medico_esp->especialidade==esp_filtro) {
                            exibir_consulta(medico,nm, &consulta[i], np, paciente);
                            encontrei = true;
                        } 
                    }
                    if (!encontrei){
                        printf("nenhuma consulta encontrada!\n"); 
                    }
                    getchar();
                    break;
                }
            // por data
            case 7:
                do {
                    printf("Digite a data: dd mm aaaa \n");
                    scanf("%d %d %d", &filtro_data.dia, &filtro_data.mes, &filtro_data.ano);
                    if (!validar_data(filtro_data)) {
                        printf("A data inserida e invalida. Por favor, tente novamente.\n");
                        return;
                    }
                } while (!validar_data(filtro_data));

                printf("\n--- Consultas na data %02d/%02d/%04d---\n", filtro_data.dia, filtro_data.mes, filtro_data.ano);
                for (int i=0; i<nc; i++) {
                    if (consulta[i].data.dia==filtro_data.dia && consulta[i].data.mes==filtro_data.mes && consulta[i].data.ano==filtro_data.ano) {
                        exibir_consulta(medico,nm, &consulta[i], np, paciente);
                        encontrei = true;
                    }
                }
                if (!encontrei) {
                    printf("Nenhuma consulta foi encontrada nessa data.\n");
                }
                getchar();
                break;
        default:
            break;
        }
    } while (filtro != 0);

}

