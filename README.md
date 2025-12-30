# Sistema de Agendamento Clínico

Este projeto é uma aplicação de linha de comando (CLI) desenvolvida em linguagem C para o gerenciamento de médicos, pacientes e consultas de uma clínica médica. O sistema permite o cadastro completo de profissionais e pacientes, controle de horários de atendimento e geração de relatórios.

---

># Funcionalidades Principal
O sistema está dividido em três grandes áreas:

> Gestão de Médicos
Cadastro Completo: Registro de nome, especialidade (Clínico, Pediatra, Dermatologista, Cardiologista ou Psicólogo) e horários de atendimento.

Configuração de Turnos: Definição de horários para os turnos da manhã e tarde, com geração automática de slots de atendimento a cada 30 minutos.

Ordenação: Visualização de médicos por ID, ordem alfabética ou especialidade.

> Gestão de Pacientes
Cadastro de Contatos: Registro de nome e informações de contato (validando se é e-mail ou telefone).

Organização: Listagem e busca de pacientes por ID ou nome.

Manutenção: Atualização de dados cadastrais e remoção de registros.

> Agendamento de Consultas
Marcação Inteligente: Vinculação entre médico, paciente e data.

Controle de Ocupação: O sistema verifica automaticamente se o médico possui o slot de horário livre na data escolhida.

Prioridade: Opção de agendamento "Urgente", que busca o primeiro horário disponível.

Status da Consulta: Controle de estado (Agendada, Concluída, Cancelada ou Falta).

Relatórios Filtrados: Geração de listas de consultas por médico, por dia, por semana, por paciente ou por especialidade.

---

># Detalhes Técnicos
Estrutura de Dados
O projeto utiliza estruturas (structs) aninhadas para organizar as informações:

Horario e Data: Para manipulação de tempo.

SlotConsulta: Representa cada intervalo de 30 minutos de um médico.

medicos, pacientes e consultas: Estruturas principais de armazenamento.

Persistência de Dados
O sistema utiliza arquivos de texto para salvar e carregar as informações:

arq_medico.txt

arq_paciente.txt

arq_consulta.txt

Ao iniciar, o programa lê esses arquivos e carrega os dados na memória (usando malloc e realloc). Ao sair, ele atualiza os arquivos com as novas informações inseridas durante a execução.

---

># Estrutura do Projeto
geral.h: Protótipos das funções, definições de constantes e structs.

agendamento.c: Contém a função main e a lógica dos menus principais.

medicos.c: Implementação das funções de gestão de médicos.

paciente.c: Implementação das funções de gestão de pacientes.

consulta.c: Lógica de agendamento, validação de datas e relatórios.

---

># Como Executar
Compilação: Certifique-se de ter um compilador C (como o GCC) instalado. No terminal, execute:

```c

gcc -o sistema agendamento.c medicos.c paciente.c consulta.c -I.
Execução:

```
```c
./sistema
```
Nota: Certifique-se de que os arquivos .txt mencionados acima existam no diretório ou o programa os criará ao fechar.

--- 

Desenvolvedores
Emerson Morais de Araujo

Leticia de Melo Sobral

Projeto realizado para a disciplina de Introdução à Programação (1° Período).
