/*
 Este é um esqueleto que deve ser utilzado como base para implementação da Agenda.
	- As funções não tem os parâmetros definidos e os parâmetros caso necessários, devem ser incluídos.
    - Caso seja necessário novas funções podem ser incluídas
 	- Devem ser respeitados os nomes dados mara o métodos e estruturas, porém novas estruturas e funções podem ser criados, caso julgue necessário
	- Faça os includes necessários
	- A organização das funções fica a critério do programador
	- Códigos não identados sofrerão duras penalidades
	- Não serão toleradas variaveis globais
	- Caso seja detectado plágio, os grupos envolvidos receberão nota 0.
*/
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define EXIT 10  // valor fixo para a opção que finaliza a aplicação

//Struct que representa a data.
//Representa o nascimento da pessoa.
typedef struct {
	int day;
	int month;
	int year;
} Date;

// Estrutura que contém os campos dos registros da agenda
struct MREC {
       char name[30];
       Date birth;
       char email[40];
       char phone[15];

	   struct MREC *next;
	   //struct MREC *prev; Fizemos uma lista simplesmente encadeada.
};
// Tipo criado para instanciar variaveis do tipo agenda
typedef struct MREC Contact;

void swap(Contact *x, Contact *y);

// Permite excluir um contato da agenda
void delContact (Contact *raiz, char *nomeProcurado) {
    Contact *nav = raiz->next;

    if (strcmp (nomeProcurado, nav->name)== 0) {
        raiz->next = nav->next;
        free(nav);
        return;
    }

    Contact *anterior = raiz;

    while (nav->next) {
        anterior = nav;
        nav = nav->next;
        if (strcmp (nomeProcurado, nav->name) == 0) {
            break;
        }
    }
    anterior->next = nav->next;
    nav->next = NULL;
    free(nav);
}

// Permite o cadastro de um contato
void insContact (Contact *raiz, char *nome, char *email, char *telefone, int dia, int mes, int ano) {
    
    Contact *novoContato = (Contact* ) malloc(sizeof (Contact));
    snprintf(novoContato->name, sizeof(novoContato->name), "%s", nome);
    novoContato->birth.day = dia;
    novoContato->birth.month = mes;
    novoContato->birth.year = ano;
    snprintf(novoContato->email, sizeof(novoContato->email), "%s", email);
    snprintf(novoContato->phone, sizeof(novoContato->phone), "%s", telefone);

    novoContato->next = raiz->next;
    raiz->next = novoContato;
}

//Permite conultar um contato
int queryContact (Contact *raiz, char *nomeProcurado, int n) {
    int ativacao = 0;
    raiz = raiz->next;

    while (raiz != NULL) {
        if (strncmp (raiz->name, nomeProcurado, n) == 0) {
            printf("\nNome: %s\n", raiz->name);
            printf("Email: %s\n", raiz->email);
            printf("Telefone: %s\n", raiz->phone);
            printf("Data de nascimento: %d/%d/%d\n", raiz->birth.day, raiz->birth.month, raiz->birth.year);
            ativacao = 1;
        }

        if ((ativacao == 1) && (strncmp (raiz->name, nomeProcurado, n) != 0)) {
            break;
        }

        else if ((raiz->next == NULL) && (ativacao == 0)) {
            printf("Nenhum nome encontrado!\n");
        }
        raiz = raiz->next;
    }
        
}

void upContact (Contact *raiz, char *nomeProcurado) {
    raiz = raiz->next;//vai para o primeiro elemento
    char chave[30];
    char info[100];
    int info_int, info_int1, info_int2;

    while (raiz != NULL) {
        if (strcmp (nomeProcurado, raiz->name) == 0) {
            //listContacts(raiz);
            printf("\nDeseja atualizar o nome? [y or n]: ");
            scanf("%s", chave);
            if (strcmp(chave, "y") == 0)  {
                printf("Digite o novo nome: ");
                setbuf(stdin,NULL);
                scanf("%[^\n]",info);
                for (int i = 0; i < strlen(info); i++) {
                    info[i] = toupper(info[i]);
                }
                //setbuf(stdin,NULL);
                snprintf(raiz->name, sizeof(raiz->name), "%s", info);
            }

            printf("\nDeseja atualizar o email? [y or n]: ");
            scanf("%s", chave);
            if (strcmp(chave, "y") == 0) {
                printf("Digite o novo email: ");
                scanf("%s",info);
                snprintf(raiz->email, sizeof(raiz->email), "%s", info);
            }
            
            printf("\nDeseja atualizar o telefone? [y or n]: ");
            scanf("%s", chave);
            if (strcmp(chave, "y") == 0)  {
                printf("Digite o novo telefone: ");
                scanf("%s",info);
                snprintf(raiz->phone, sizeof(raiz->phone), "%s", info);
            }

            printf("\nDeseja atualizar a data de aniversário? [y or n]: ");
            scanf("%s", chave);
            if (strcmp(chave, "y") == 0)  {
                printf("Digite a data dia/mes/ano, separado apenas por espaço: ");
                scanf("%d %d %d",&info_int, &info_int1, &info_int2);
                raiz->birth.day = info_int;
                raiz->birth.month = info_int1;
                raiz->birth.year = info_int2;
            }

            printf("\nDados atualizados\n");
            printf("Nome: %s\n", raiz->name);
            printf("Email: %s\n", raiz->email);
            printf("Telefone %s\n", raiz->phone);
            printf("Data de nascimento %d/%d/%d\n", raiz->birth.day, raiz->birth.month, raiz->birth.year);
            return;
        }

        raiz = raiz->next;
    }
}

void ordena(Contact *raiz){
    Contact *aux;

    while (raiz != NULL){
        aux = raiz->next;
        while (aux != NULL){
            if (strcmp(raiz->name,aux->name) > 0){
                swap(raiz,aux);
            }
            aux = aux->next;
        }
        raiz = raiz->next;
    }
    //Aqui deveria haver um free no aux?
}

// Lista o conteudo da agenda (todos os campos)
void listContacts(Contact *p) {
    p = p->next;
    printf("\nOs contatos armazenados são:\n");
    if(p)
    {
        do
        {            
            printf("Nome: %s\n", p->name);
            printf("Email: %s\n", p->email);
            printf("Telefone: %s\n", p->phone);
            printf("Data de nascimento: %d/%d/%d\n", p->birth.day,p->birth.month,p->birth.year);
            printf("\n");
            p = p->next;
        }
        while(p);
        

    }
    else
        printf("Agenda vazia.\n");
}

void swap(Contact *x, Contact *y){ 
    Contact *temp = (Contact* ) malloc(sizeof (Contact));
    snprintf(temp->name, sizeof(temp->name), "%s", x->name);
    temp->birth.day = x->birth.day;
    temp->birth.month = x->birth.month;
    temp->birth.year = x->birth.year;
    snprintf(temp->email, sizeof(temp->email), "%s", x->email);
    snprintf(temp->phone, sizeof(temp->phone), "%s", x->phone);

    snprintf(x->name, sizeof(x->name), "%s", y->name);
    x->birth.day = y->birth.day;
    x->birth.month = y->birth.month;
    x->birth.year = y->birth.year;
    snprintf(x->email, sizeof(x->email), "%s", y->email);
    snprintf(x->phone, sizeof(x->phone), "%s", y->phone);

    snprintf(y->name, sizeof(y->name), "%s", temp->name);
    y->birth.day = temp->birth.day;
    y->birth.month = temp->birth.month;
    y->birth.year = temp->birth.year;
    snprintf(y->email, sizeof(y->email), "%s", temp->email);
    snprintf(y->phone, sizeof(y->phone), "%s", temp->phone);

    free(temp);
}

// Apresenta o menu da aplicação e retorna a opção selecionada
int menu() {
    int op=0;
    while (op != EXIT) {
        printf("\nPara finalizar o programa e salvar automaticamente, digite %d e tecle enter. E da mesma forma tecle:\n",EXIT);
        printf("1 - Para inserir um novo contato;\n");
        printf("2 - Para deletar um contato existente;\n");
        printf("3 - Para atualizar um contato existente;\n");
        printf("4 - Para pesquisar contatos;\n");
        printf("5 - Para listar todos os contatos contidos na memória.\n");
        scanf("%d",&op);
        return op;
    }
}

char verificaPalvra (char nome[]) {
    int i = 0;
    while (i < strlen (nome)) {
        if ((nome[i] > 'A' || nome[i] < 'Z') || (nome[i] > 'a' || nome[i] < 'z')) {
            printf("Nome não aceito, não insira caracteres especiais! Digite o nome novamente da forma aceita: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]",nome);
            break;
        }
        i++;
    }

    return nome[30];
}

// Programa principal
int main() {
    int op=0;

    char nome[30];
    char email[40];
    char telefone[15];
    int dia, mes, ano;

    char nomeProcurado[30];
    int n = 0;

    printf("===================================!!!!!!Atenção!!!!!!===================================\n");
    printf("   Os nomes para pessoas registradas nesta agenda estão restritos a caracteres comuns,\n");
    printf("sem qualquer caracter do tipo epecial, sejam eles acentuação ou letras especiais como 'ç'\n");
    printf("=========================================================================================\n\n");

    Contact *raiz = (Contact*) malloc(sizeof (Contact));
    raiz->next = NULL;
    Contact *inicio = (Contact*) malloc(sizeof (Contact));
    Contact *ultimo = NULL;
    inicio = NULL;
    
    FILE *arquivo;
    arquivo = fopen("agenda.ab","rb");
   

    if (arquivo == NULL){ //se for igual a null arquivo vazio
        arquivo = fopen("agenda.ab","wb");
    } else {
        arquivo = fopen("agenda.ab", "rb");
        
        while (fread(raiz, sizeof(raiz), 1, arquivo) > 0){
            raiz->next = NULL;
    
            if (inicio == NULL) //verifica se vai ser o primeiro
                inicio = raiz;

            if (ultimo == NULL)  //controla o ultimo para encadear
                ultimo = raiz;
            else{
                ultimo->next = raiz;
                ultimo = raiz;
            }
            raiz = malloc(sizeof(Contact));
        }
    }
    fclose(arquivo);
    
    while (op != EXIT) {       
        op = menu();
        switch(op) {
            case 1:
                printf("Digite um nome: ");
                setbuf(stdin,NULL);
                scanf("%[^\n]",nome);
                nome[30] = verificaPalvra(nome);
                for (int i = 0; i < strlen(nome); i++) {
                    nome[i] = toupper(nome[i]);
                }
                printf("Digite um email: ");
                scanf("%s",email);
                printf("Digite um telefone: ");
                scanf("%s",telefone);
                printf("Digite o dia/mes/ano separado por espaço: ");
                scanf("%d %d %d",&dia, &mes, &ano);
                insContact(raiz, nome, email, telefone, dia, mes, ano);
                ordena(raiz);
                break;

            case 2:
                printf("Digite o nome completo da pessoa que deseja excluir,\npor exemplo, Gabriel Lima da Silva: ");
                setbuf(stdin,NULL);
                scanf("%[^\n]",nomeProcurado);
                for (int i = 0; i < strlen(nomeProcurado); i++) {
                    nomeProcurado[i] = toupper(nomeProcurado[i]);
                }
                delContact(raiz, nomeProcurado);
                break;

            case 3:
                printf("Digite o nome completo da pessoa que deseja atualizar,\npor exemplo, Gabriel Lima da Silva: ");
                setbuf(stdin,NULL);
                scanf("%[^\n]",nomeProcurado);
                nomeProcurado[30] = verificaPalvra(nomeProcurado);
                for (int i = 0; i < strlen(nomeProcurado); i++) {
                    nomeProcurado[i] = toupper(nomeProcurado[i]);
                }
                upContact(raiz, nomeProcurado);
                ordena(raiz);
                break;

            case 4:
                printf("Digite o nome que seja buscar na agenda,\npor exemlo Gabriel, joao Lima ou PEDRO SANTOS: ");
                setbuf(stdin,NULL);
                scanf("%[^\n]",nomeProcurado);
                for (int i = 0; i < strlen(nomeProcurado); i++) {
                    nomeProcurado[i] = toupper(nomeProcurado[i]);
                }
                n = strlen(nomeProcurado);
                queryContact(raiz, nomeProcurado, n);
                break;

            case 5:
                listContacts(raiz);
                break;
        }
    }

    arquivo = fopen("agenda.ab", "wb");
    for (raiz = inicio; raiz != NULL; raiz = raiz->next){
        fwrite(raiz, sizeof(Contact),1,arquivo);
    }
    fclose(arquivo);
    
    free(raiz);
    return 0;
}