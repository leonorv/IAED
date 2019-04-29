/*PROJETO DE IAED 1*/ 
/*FICHEIRO - proj.c*/
/*AUTORA - Leonor Veloso 92509*/
/*BIBLIOTECAS*/
#include <stdio.h>
#include <string.h>

/*CONSTANTES*/
#define MAX_STRING 64
#define MAX_PARTICIPANTES 194
#define MAX_SALAS 10
#define MAX_EVENTOS 100
#define MAX_DURACAO 1440 
#define MAX_N_PARTICIPANTES 3
#define FALSE 0
#define TRUE 1

/*ESTRUTURAS DE DADOS*/
/*ESTRUTURA EVENTO*/
typedef struct {
    char descricao[MAX_STRING];
    int data; /*ddmmaaaa*/
    int amd; /*aaaammdd*/
    int inicio; /*hhmm*/
    int sala; /* de 1 a 10*/
    int duracao; /*em minutos*/
    char participantes[MAX_PARTICIPANTES]; /*participantes separados por ':'*/
    char responsavel[MAX_STRING];
    char splitParticipantes[MAX_N_PARTICIPANTES][MAX_STRING]; /*3 participantes com 63 caracteres cada*/
} evento;

/*VARIAVEIS GLOBAIS*/
evento vec_eventos[MAX_SALAS*MAX_EVENTOS]; /*vetor onde sao inseridos os eventos*/ 
int lstlen; /*contador de eventos*/
int x = FALSE; /*verifica se a funcao main chega a um termino, inicializada a FALSE, passa a TRUE com o comando x*/

/*INICIALIZA A MATRIZ*/
void nullify() {
    int i,m;
    for (i = 0; i < MAX_EVENTOS*MAX_SALAS; i++) {
        vec_eventos[i].descricao[0] = '\0';
        vec_eventos[i].responsavel[0] = '\0';
        vec_eventos[i].participantes[0] = '\0';
        vec_eventos[i].data = 0;
        vec_eventos[i].inicio = 0;
        vec_eventos[i].duracao = 0;
        vec_eventos[i].sala = 0;
        vec_eventos[i].amd = 0;
        for (m = 0; m < MAX_N_PARTICIPANTES; m++) {
            vec_eventos[i].splitParticipantes[m][0] = '\0';
        }
    }
}

/*TRANSFORMA O INICIO DE UM EVENTO (HHMM) EM MINUTOS*/
int inicio_p_minutos(int i) { 
    int horas, minutos, res;
    horas = i/100;
    minutos = i%100;
    res = 60*horas + minutos;
    return res;
}

/*SORT - TROCA 2 EVENTOS NO VETOR SE NAO ESTIVEREM POR ORDEM CRONOLOGICA*/
void o_povo_e_quem_mais_ordena(evento vec_eventos[MAX_SALAS*MAX_EVENTOS]) { 
    int counter = lstlen - 1;
    evento temp;
    for (; counter > 0; counter--) {
        if (vec_eventos[counter - 1].amd > vec_eventos[counter].amd) {
            temp = vec_eventos[counter - 1];
            vec_eventos[counter - 1] = vec_eventos[counter];
            vec_eventos[counter] = temp;
        }
        else if (vec_eventos[counter - 1].amd == vec_eventos[counter].amd) {
            if (inicio_p_minutos(vec_eventos[counter - 1].inicio) > inicio_p_minutos(vec_eventos[counter].inicio)) {
                temp = vec_eventos[counter - 1];
                vec_eventos[counter - 1] = vec_eventos[counter];
                vec_eventos[counter] = temp;
            }
            else if (inicio_p_minutos(vec_eventos[counter - 1].inicio) == inicio_p_minutos(vec_eventos[counter].inicio)) {
                if (vec_eventos[counter - 1].sala > vec_eventos[counter].sala) {
                    temp = vec_eventos[counter - 1];
                    vec_eventos[counter - 1] = vec_eventos[counter];
                    vec_eventos[counter] = temp;
                }
            }
        }
    }
}

/*VERIFICA SE DOIS EVENTOS SE SOBREPOEM, APENAS EM TERMOS DE HORARIO/DATA*/
int sobreposicao(evento e1, evento e2) {
    int inmin_e1, inmin_e2;
    inmin_e1 = inicio_p_minutos(e1.inicio);
    inmin_e2 = inicio_p_minutos(e2.inicio);
    if (e1.data != e2.data) return FALSE;
    if (inmin_e1 < inmin_e2 + e2.duracao) {
        if (inmin_e2 < inmin_e1 + e1.duracao) return TRUE;
    }
    else {
        if (inmin_e1 < inmin_e2 + e2.duracao) return TRUE;
    }
    return FALSE;
}

/*VERIFICA SE UM EVENTO SE PASSA NUMA SALA OCUPADA*/
int sala_ocupada(evento e, evento vec_eventos[MAX_SALAS*MAX_EVENTOS]) {
    int i;
    for (i = 0; i < lstlen; i++) {
        if (sobreposicao(e, vec_eventos[i]) && e.sala == vec_eventos[i].sala) {
            printf("Impossivel agendar evento %s. Sala%d ocupada.\n", e.descricao, e.sala);
            return TRUE;
        }
    }
    return FALSE;
}

/*DEVOLVE O MESMO EVENTO COM A MATRIZ DOS PARTICIPANTES ATUALIZADA*/
evento saveParticipantes(evento e) {
    int i, j = 0, counter = 0, len;
    len = strlen(e.participantes);
    for (i = 0; i < len; i++, j++) {
        if (e.participantes[i] == ':' || e.participantes[i] == '\0') {
            e.splitParticipantes[counter][j] = '\0';
            counter++;
            j = -1;
        }
        else e.splitParticipantes[counter][j] = e.participantes[i];
    }
    e.splitParticipantes[counter][j] = '\0';
    for (i = counter + 1; i < MAX_N_PARTICIPANTES; i++) {
        e.splitParticipantes[i][0] = '\0';
    }
    return e;
}

/*VERIFICA SE UM EVENTO CONTEM UM PARTICIPANTE OCUPADO (QUE PARTICIPE NOUTRO EVENTO)*/
/*esta funcao contem uma condicao:
    - se for TRUE, esta a ser chamada para adicionar um evento novo
    - se for FALSE, esta a ser chamada quando se tenta adicionar um participante*/
int participante_ocupado(evento e, evento vec_eventos[MAX_SALAS*MAX_EVENTOS], int condicao) {
    int i, m, n, valor = FALSE;
    for (i = 0; i < lstlen; i++) {
        for (m = 0; m < MAX_N_PARTICIPANTES; m++) {
            if(strcmp(e.splitParticipantes[m], vec_eventos[i].responsavel) == 0 && e.splitParticipantes[m][0] != '\0' && sobreposicao(e, vec_eventos[i])) {
                if (condicao == 0) printf("Impossivel adicionar participante. Participante %s tem um evento sobreposto.\n", e.splitParticipantes[m]);
                else printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", e.descricao, e.splitParticipantes[m]);
                valor = TRUE;
            }
            for (n = 0; n < MAX_N_PARTICIPANTES; n++) {
                if (strcmp(e.splitParticipantes[m], vec_eventos[i].splitParticipantes[n]) == 0 && e.splitParticipantes[m][0] != '\0' && sobreposicao(e, vec_eventos[i])) {
                    if (condicao == 0) printf("Impossivel adicionar participante. Participante %s tem um evento sobreposto.\n", e.splitParticipantes[m]);
                    else printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", e.descricao, e.splitParticipantes[m]);
                    valor = TRUE;
                }
            }
        }
    }
    return valor;
}

/*VERIFICA SE O RESPONSAVEL DE UM EVENTO ESTA OCUPADO (QUE PARTICIPE NOUTRO EVENTO)*/
int responsavel_ocupado(evento e, evento vec_eventos[MAX_SALAS*MAX_EVENTOS]) {
    int i, m, valor = FALSE;
    for (i = 0; i < lstlen; i++) {
        if (strcmp(e.responsavel, vec_eventos[i].responsavel) == 0 && sobreposicao(e, vec_eventos[i])) {
            printf ("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", e.descricao, e.responsavel);
            valor = TRUE;;
        }
    }
    for (i = 0; i < lstlen; i++) {
        for (m = 0; m < MAX_N_PARTICIPANTES; m++) {
            if (strcmp(e.responsavel, vec_eventos[i].splitParticipantes[m]) == 0 && sobreposicao(e, vec_eventos[i])) {
                printf ("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", e.descricao, e.responsavel);
                valor = TRUE;
            }
        }
    }
    return valor;
}

/*TRANSFORMA UMA DATA NO FORMATO DDMMAAAA PARA UMA DATA NO FORMATO AAAAMMDD*/
int transdata(int data) { 
    int dia, mes, ano;
    dia = data/1000000;
    ano = data%10000;
    data = data/10000;
    mes = data%100;
    data = ano*10000 + mes*100 + dia;
    return data;
}

/*VERIFICA SE UM EVENTO JA EXISTE NO VETOR DE EVENTOS*/
int eventoExiste(char descricao[MAX_STRING],evento vec_eventos[MAX_SALAS*MAX_EVENTOS]) {
    int i;
    for (i = 0; i < lstlen; i++) {
        if (strcmp(descricao, vec_eventos[i].descricao) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

/*DEVOLVE UM EVENTO CUJAS COMPONENTES SAO DADAS NOS ARGUMENTOS*/
evento criaEvento(char descricao[MAX_STRING],int data,int inicio, int sala,int duracao,char participantes[MAX_PARTICIPANTES],char responsavel[MAX_STRING]) {
    evento e;
    strcpy(e.descricao, descricao);
    strcpy(e.participantes, participantes);
    strcpy(e.responsavel, responsavel);
    e.sala = sala;
    e.duracao = duracao;
    e.data = data;
    e.amd = transdata(data);
    e.inicio = inicio;
    e = saveParticipantes(e);
    return e;
}

/*ADICIONA UM EVENTO AO VETOR DE EVENTOS*/
void addEvento(evento vec_eventos[MAX_SALAS*MAX_EVENTOS], evento e) {
    int flag = 0;
    flag += sala_ocupada(e, vec_eventos);
    if (flag != 0) return;
    flag += responsavel_ocupado(e, vec_eventos);
    flag += participante_ocupado(e, vec_eventos, TRUE);
    if (flag == 0) {
        vec_eventos[lstlen] = e;
        lstlen++;
        o_povo_e_quem_mais_ordena(vec_eventos);
    }
}

/*IMPRIME OS PARTICIPANTES DE UM EVENTO*/
void printParticipantes(evento e) {
    int m;
    for (m = 0; m < MAX_N_PARTICIPANTES; m++) {
        if (e.splitParticipantes[m][0] != '\0') printf(" %s", e.splitParticipantes[m]);
    }
    printf("\n");
}

/*IMPRIME UM EVENTO*/
void listEvento(evento vec_eventos[MAX_SALAS*MAX_EVENTOS]) {
    int i;
    for (i = 0; i < lstlen; i++) {
        printf("%s %08d %04d %d Sala%d %s\n*", vec_eventos[i].descricao, vec_eventos[i].data, vec_eventos[i].inicio, vec_eventos[i].duracao, vec_eventos[i].sala, vec_eventos[i].responsavel);
        printParticipantes(vec_eventos[i]);
    }
}

/*IMPRIME OS EVENTOS POR SALA*/
void listSalaEvento(evento vec_eventos[MAX_SALAS*MAX_EVENTOS], int sala) {
    int i;
    for (i = 0; i < lstlen; i++) {
        if (vec_eventos[i].sala == sala) {
            printf("%s %08d %04d %d Sala%d %s\n*", vec_eventos[i].descricao, vec_eventos[i].data, vec_eventos[i].inicio, vec_eventos[i].duracao, vec_eventos[i].sala, vec_eventos[i].responsavel);
            printParticipantes(vec_eventos[i]);
        }
    }
}

/*APAGA UM EVENTO DO VETOR DE EVENTOS*/
void apagaEvento(evento vec_eventos[MAX_SALAS*MAX_EVENTOS], char descricao[MAX_STRING]) {
    int i = 0, j;
    if (eventoExiste(descricao, vec_eventos) == FALSE) {
        printf("Evento %s inexistente.\n", descricao);
        return;
    }
    while (strcmp(vec_eventos[i].descricao, descricao) != 0) {
        i++; /*guarda indice do evento a apagar*/
    }
    for (j = i; j < lstlen - 1; j++) {
        vec_eventos[j] = vec_eventos[j+1];
    }
    lstlen--;
}

/*ALTERA O INICIO DE UM EVENTO, SE POSSIVEL*/
void mudaInicio(evento vec_eventos[MAX_SALAS*MAX_EVENTOS], char descricao[MAX_STRING], int inicio) {
    evento temp, copia;
    int i, flag = 0;
    if (eventoExiste(descricao, vec_eventos) == FALSE) {
        printf("Evento %s inexistente.\n", descricao);
        return;
    }
    strcpy(temp.descricao, descricao);
    for (i = 0; i < lstlen; i++) {
        if (strcmp(vec_eventos[i].descricao, temp.descricao) == 0) {
            copia = vec_eventos[i];
            temp = vec_eventos[i];
            temp.inicio = inicio;
            apagaEvento(vec_eventos, vec_eventos[i].descricao);
            break;
        }
    }
    flag += sala_ocupada(temp, vec_eventos); 
    if (flag != 0) {
        addEvento(vec_eventos, copia);
        return;
    }
    flag += responsavel_ocupado(temp, vec_eventos);
    flag += participante_ocupado(temp, vec_eventos, TRUE); 
    if (flag == 0) addEvento(vec_eventos, temp);
    else addEvento(vec_eventos, copia);
}

/*ALTERA A DURACAO DE UM EVENTO, SE POSSIVEL*/
void mudaDuracao(evento vec_eventos[MAX_SALAS*MAX_EVENTOS], char descricao[MAX_STRING], int duracao) {
    evento temp, copia;
    int i, flag = 0;
    if (eventoExiste(descricao, vec_eventos) == FALSE) {
        printf("Evento %s inexistente.\n", descricao);
        return;
    }
    strcpy(temp.descricao, descricao);
    for (i = 0; i < lstlen; i++) {
        if (strcmp(vec_eventos[i].descricao, temp.descricao) == 0) {
            copia = vec_eventos[i];
            temp = vec_eventos[i];
            temp.duracao = duracao;
            apagaEvento(vec_eventos, vec_eventos[i].descricao);
            break;
        }
    }
    flag += sala_ocupada(temp, vec_eventos); 
    if (flag != 0) {
        vec_eventos[lstlen] = copia;
        lstlen++;
        o_povo_e_quem_mais_ordena(vec_eventos);
        return;
    }
    flag += responsavel_ocupado(temp, vec_eventos);
    flag += participante_ocupado(temp, vec_eventos, TRUE); 
    if (flag == 0) addEvento(vec_eventos, temp);
    else addEvento(vec_eventos, copia);
}

/*ALTERA A SALA DE UM EVENTO, SE POSSIVEL*/
void mudaSala(evento vec_eventos[MAX_SALAS*MAX_EVENTOS], char descricao[MAX_STRING], int sala) {
    evento temp, copia;
    int i, flag = 0;
    if (eventoExiste(descricao, vec_eventos) == FALSE) {
        printf("Evento %s inexistente.\n", descricao);
        return;
    }
    strcpy(temp.descricao, descricao);
    for (i = 0; i < lstlen; i++) {
        if (strcmp(vec_eventos[i].descricao, temp.descricao) == 0) {
            copia = vec_eventos[i];
            temp = vec_eventos[i];
            temp.sala = sala;
            apagaEvento(vec_eventos, vec_eventos[i].descricao);
            break;
        }
    }
    flag += sala_ocupada(temp, vec_eventos); 
    if (flag != 0) {
        addEvento(vec_eventos, copia);
        return;
    }
    addEvento(vec_eventos, temp);
}

/*DEVOLVE O NUMERO DE PARTICIPANTES DE UM EVENTO*/
int nParticipantes(evento e) {
    int i, n = 0;
    for (i = 0; i < MAX_N_PARTICIPANTES; i++) {
        if (e.splitParticipantes[i][0] != '\0') n++;
    }
    return n;
}

/*ADICIONA UM PARTICIPANTE A UM EVENTO, SE POSSIVEL*/
void adicionaParticipante(evento vec_eventos[MAX_SALAS*MAX_EVENTOS], char participante[MAX_STRING], char descricao[MAX_STRING]) {
    int i, j, m, flag = 0;
    evento temp, copia;
    if (eventoExiste(descricao, vec_eventos) == FALSE) {
        printf("Evento %s inexistente.\n", descricao);
        return;
    }
    for (i = 0; i < lstlen; i++) {
        if (strcmp(vec_eventos[i].descricao, descricao) == 0) break;
    }
    if (nParticipantes(vec_eventos[i]) == MAX_N_PARTICIPANTES) {
        printf("Impossivel adicionar participante. Evento %s ja tem 3 participantes.\n", vec_eventos[i].descricao);
        return;
    }
    for (j = 0; j < MAX_N_PARTICIPANTES; j++) {
        if (strcmp(vec_eventos[i].splitParticipantes[j], participante) == 0) return;
    }
    copia = vec_eventos[i];
    temp = vec_eventos[i];
    for (m = 0; m < MAX_N_PARTICIPANTES; m++) {
        if (temp.splitParticipantes[m][0] == '\0') {
            strcpy(temp.splitParticipantes[m], participante);
            break;
        }
    }
    apagaEvento(vec_eventos, vec_eventos[i].descricao);
    flag += participante_ocupado(temp, vec_eventos, FALSE);
    if (flag == 0) addEvento(vec_eventos, temp);
    else addEvento(vec_eventos, copia);
}

/*REMOVE UM PARTICIPANTE DE UM EVENTO, SE POSSIVEL*/
void removeParticipante(evento vec_eventos[MAX_SALAS*MAX_EVENTOS], char descricao[MAX_STRING], char participante[MAX_STRING]) {
    int i, m;
    if (eventoExiste(descricao, vec_eventos) == FALSE) {
        printf("Evento %s inexistente.\n", descricao);
        return;
    }
    for (i = 0; i < lstlen; i++) {
        if (strcmp(vec_eventos[i].descricao, descricao) == 0) break;
    }
    if (nParticipantes(vec_eventos[i]) == 1) {
        for (m = 0; m < MAX_N_PARTICIPANTES; m++) {
            if (strcmp(vec_eventos[i].splitParticipantes[m], participante) == 0) {
                printf("Impossivel remover participante. Participante %s e o unico participante no evento %s.\n", participante, descricao);
                return;
            }
        }
        return;
    }
    for (m = 0; m < MAX_N_PARTICIPANTES; m++) {
        if (strcmp(vec_eventos[i].splitParticipantes[m], participante) == 0) vec_eventos[i].splitParticipantes[m][0] = '\0';
    } 
    for (m = 0; m < MAX_N_PARTICIPANTES - 1; m++) { /*SHIFTAR PARTICIPANTES*/
        char temp[MAX_STRING];
        if (vec_eventos[i].splitParticipantes[m][0] == '\0') {
            strcpy(temp, vec_eventos[i].splitParticipantes[m]);
            strcpy(vec_eventos[i].splitParticipantes[m], vec_eventos[i].splitParticipantes[m + 1]);
            strcpy(vec_eventos[i].splitParticipantes[m + 1], temp);
        }
    }
}

int main() {
    int c;
    char descricao[MAX_STRING], participantes[MAX_PARTICIPANTES], responsavel[MAX_STRING];
    int data, inicio, sala, duracao;
    nullify();
    c = getchar();
    while (x == FALSE) {
        switch(c) {
            case 'a':
                scanf(" %[^:]: %d: %d: %d: %d: %[^:]: %[^\n]", descricao, &data, &inicio, &duracao, &sala, responsavel, participantes);
                addEvento(vec_eventos, criaEvento(descricao, data, inicio, sala, duracao, participantes, responsavel));
                break;
            case 'l':
                listEvento(vec_eventos);
                break;
            case 's':
                scanf("%d", &sala);
                listSalaEvento(vec_eventos, sala);
                break;
            case 'r': 
                scanf(" %[^\n]", descricao);
                apagaEvento(vec_eventos, descricao);
                break;
            case 'i':
                scanf(" %[^:]:%d", descricao, &inicio);
                mudaInicio(vec_eventos, descricao, inicio);
                break;
            case 't':
                scanf(" %[^:]:%d", descricao, &duracao);
                mudaDuracao(vec_eventos, descricao, duracao);
                break;
            case 'm':
                scanf(" %[^:]:%d", descricao, &sala);
                mudaSala(vec_eventos, descricao, sala);
                break;
            case 'A':
                scanf(" %[^:]: %[^\n]", descricao, participantes); 
                adicionaParticipante(vec_eventos, participantes, descricao);
                break;
            case 'R':
                scanf(" %[^:]:%[^\n]", descricao, participantes); 
                removeParticipante(vec_eventos, descricao, participantes);
                break;
            case 'x':
                x = TRUE;
                break;
        }
        c = getchar();
    }
    return 0;
}