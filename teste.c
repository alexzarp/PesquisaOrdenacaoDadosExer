#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	   struct MREC *prev;
};
// Tipo criado para instanciar variaveis do tipo agenda
typedef struct MREC Contact;

// Permite o cadastro de um contato
void insContact (Contact *raiz, char *nome, char *email, char *telefone, int dia, int mes, int ano) {
    
    Contact *novoContato = (Contact* ) malloc(sizeof (Contact));
    snprintf(novoContato->name, sizeof(novoContato->name), "%s", nome);
    novoContato->birth.day = dia;
    novoContato->birth.month = mes;
    novoContato->birth.year = ano;
    snprintf(novoContato->email, sizeof(novoContato->email), "%s", email);
    snprintf(novoContato->phone, sizeof(novoContato->phone), "%s", telefone);

    Contact *contato = raiz;
    Contact *aux;
   
// Isso se chama insetion sort
    // Isso se chama insetion sort
    do{

        //printf("%s %s", novoContato->name, nav->name);
        if (strcmp(contato->name, novoContato->name) < 0) {
            novoContato->next = contato->next;
            contato->next = novoContato;
            printf("\nEntrou no primeiro if\n");
            //printf("%s %s", novoContato->name, nav->name);

            break;
        }
        else if (strcmp(contato->name, novoContato->name) > 0){
            aux = novoContato;
            novoContato->next = contato->next;
            contato->next = aux;
        }

        else if (strcmp(contato->name, novoContato->name) == 0){
            printf("\nEntrou no segundo if\n");
            //printf("%s %s", novoContato->name, nav->name);
            break;
        }
        printf("\nFoi ao proximo\n");
        contato = contato->next;

    }while (contato->next != NULL);
    
    printf("\nInseriu contato\n");
    //novoContato->next = nav->next;
    //nav->next = novoContato;
}

// Permite excluir um contato da agenda
void delContact (Contact *raiz) {
    int digito, contador = 0;
    
    Contact *aux = raiz->next;
    Contact *nav = raiz->next;
    Contact *anterior = raiz;

    while (aux->next) {
        contador++;
        printf("%d - %s\n", contador, aux->name);
        aux = aux->next;
    }
    free(aux);
    printf("Por favor digite o número correspondente a pessoa\nque você deseja excluir: ");
    scanf("%d", &digito);
    contador = 0;

    while (nav->next) {   
        contador++;
        anterior = nav;
        nav = nav->next;

        if (contador == digito) {
            break;
        }
    }

    anterior->next = nav->next;
    nav->next = NULL;
    free(nav);
}

void displayLL(Contact *p)
{
    p = p->next;
    printf("Mostrando a lista:\n");
    if(p)
    {
        do
        {            
            printf(" %s \n ", p->name);
            printf(" %s \n ", p->email);
            printf(" %s \n ", p->phone);
            printf(" %d/%d/%d \n ", p->birth.day,p->birth.month,p->birth.year);
            printf("\n\n");
            p = p->next;
        }
        while(p);
        printf("\n\n");

    }
    else
        printf("Lista vazia.\n\n");
}

int main(int argc, char const *argv[])
{
    char nome[30];
    char email[40];
    char telefone[15];
    int dia, mes, ano;


    Contact *raiz = (Contact* ) malloc(sizeof (Contact));
    /*snprintf(raiz->name, sizeof(raiz->name), "%s", nome);
    raiz->birth.day = 0;
    raiz->birth.month = 0;
    raiz->birth.year = 0;
    snprintf(raiz->email, sizeof(raiz->email), "%s", email);
    snprintf(raiz->phone, sizeof(raiz->phone), "%s", telefone);*/
    raiz->next = NULL;

    for (int i=0; i<3; i++){
        printf("Digite um nome ");
        scanf("%s",nome);
        printf("Digite um email ");
        scanf("%s",email);
        printf("Digite um telefone ");
        scanf("%s",telefone);
        printf("Digite o dia ");
        scanf("%d",&dia);
        printf("Digite o mes ");
        scanf("%d",&mes);
        printf("Digite o ano ");
        scanf("%d",&ano);
        insContact(raiz,nome,email,telefone,dia,mes,ano);


    }
    displayLL(raiz);

    delContact(raiz);

    displayLL(raiz);
    free(raiz);

    return 0;
}
