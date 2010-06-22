/*
 ============================================================================
 Arquivo     : Programação - Prova 01 - Questao 04
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */
#include<stdio.h>
#include<stdlib.h> 

long int data_ant=0;
int num_compra=0;
// declaracoes de estruturas de controle dos dados dos caixa (diario)

struct arrecada_dia{
       int unidades;
       float arrecadacao;
       int qtd_clientes;
       int qtd_cli_dif;
};
typedef struct arrecada_dia Caixa;
Caixa caixas[5];

//%%%%%%%%%%%%%%%%%%%%%%% LISTA DE PRODUTOS %%%%%%%%%%%%%%%%%%%%%%%%%%
// declaracao de tipos usados na implementacao

struct produtos{
       int codigo, qtd_atual, qtd_min,vendas_dia,total,total_pesquisa;
       float preco;
       char nome[20];
       char categoria[10];
};
typedef struct produtos Produtos;

struct lista_ordenada_produtos{
       Produtos produto;
       struct lista_ordenada_produtos* prox;
       };
       
typedef struct lista_ordenada_produtos No; 

struct no_cabeca_produtos{
       struct lista_ordenada_produtos* prox;
       };  
          
typedef struct no_cabeca_produtos No_cabeca_prod; 

//cria lista
No_cabeca_prod* criarLista(void){
    No_cabeca_prod* inicio=(No_cabeca_prod*)malloc(sizeof(No_cabeca_prod));
    inicio->prox=NULL;
    return inicio;
} 

// busca no cujo campo info tem o valor procurado
No* busca_prod(No_cabeca_prod* inicio, int valor){
    No* percorre=inicio->prox;
    while(percorre!=NULL){
                           if(percorre->produto.codigo==valor) return percorre; // caso encontre, ja retorna o no
                           percorre=percorre->prox;
                           }
    return NULL; // caso nao encontre
}

// algoritmo de busca que facilita a remocao de um dado no (pois retorna o no anterior ao que sera removido)
No* busca_anterior_prod(No_cabeca_prod* inicio, int valor){
    No* ant_buscada;
    No* buscada;
    if(inicio->prox!=NULL){
                  ant_buscada=inicio->prox;         
                  buscada=inicio->prox; 
                  // se o buscado for o primeiro no, ele eh retornado        
                  if(inicio->prox->produto.codigo==valor) return inicio->prox;         
                  while((buscada->prox!=NULL)&&(buscada->produto.codigo!=valor)){  
                         ant_buscada=buscada;
                         buscada=buscada->prox;                       
                  }
                  if(buscada->produto.codigo==valor) return ant_buscada;
                  return NULL;
    }
    printf(" ** Lista Vazia!!\n");
    return NULL;
}

// insere preservando a ordenacao (Vendas do dia)
void insereProduto(No_cabeca_prod* inicio,No* novo){
     No* percorre=inicio->prox;
     No* ant_percorre=inicio->prox;
     if(novo!=NULL){          
                                              if((inicio->prox==NULL)||(novo->produto.vendas_dia > inicio->prox->produto.vendas_dia)){
                                                                               novo->prox=inicio->prox;
                                                                               inicio->prox=novo;
                                               }else{
                                                     while((percorre->prox!=NULL)&&(percorre->prox->produto.vendas_dia > novo->produto.vendas_dia)){
                                                                                    percorre=percorre->prox;
                                                     }
                                               novo->prox=percorre->prox;
                                               percorre->prox=novo;
                                               } 
     }else printf(" ** Erro na insercao\n");
}

// insere preservando a ordenacao (Total vendido em reais)
void insereProdutoPesquisa(No_cabeca_prod* inicio,No* novo){
     No* percorre=inicio->prox;
     No* ant_percorre=inicio->prox;
     if(novo!=NULL){          
                                              if((inicio->prox==NULL)||(novo->produto.total_pesquisa > inicio->prox->produto.total_pesquisa)){
                                                                               novo->prox=inicio->prox;
                                                                               inicio->prox=novo;
                                               }else{
                                                     while((percorre->prox!=NULL)&&(percorre->prox->produto.total_pesquisa > novo->produto.total_pesquisa)){
                                                                                    percorre=percorre->prox;
                                                     }
                                               novo->prox=percorre->prox;
                                               percorre->prox=novo;
                                               } 
     }else printf(" ** Erro na insercao\n");
}
// remove elemento (caso exista) da lista

void removeProduto(No_cabeca_prod* inicio,int valor){
    No* ant_buscada;
    No* buscada;
    if(inicio->prox!=NULL){
        ant_buscada=busca_anterior_prod(inicio, valor);                   
        if(ant_buscada!=NULL){
                              if(ant_buscada->produto.codigo==valor){ // teste para ver se o buscado ja eh o primeiro no
                                                           buscada=ant_buscada;
                                                           inicio->prox=buscada->prox;
                              }else{
                                    buscada=ant_buscada->prox;                                    
                                    ant_buscada->prox=buscada->prox; 
                              }
                              free(buscada);
        }else printf(" ** Valor nao encontrado na lista\n");
    }else printf(" ** Lista vazia\n");
}

// imprime produtos com seus respectivos codigo e preco

void imprimeProdutos(No_cabeca_prod* inicio){
     if(inicio!=NULL){
                      printf("\n====== Lista de Produtos =======\n");
                      No *percorre=inicio->prox;
                      while(percorre!=NULL){
                                     if(percorre->produto.codigo!=12345){
                                            printf("Nome: %s - Codigo: %d - Preco: RS %.2f - Categoria: %s\n",percorre->produto.nome,percorre->produto.codigo,percorre->produto.preco,percorre->produto.categoria);
                                     }
                                            percorre=percorre->prox;
                      }
     }
}

// atualiza dados de um produto

void atualizaDados_prod(No_cabeca_prod* inicio,No_cabeca_prod* inicio_database){
     int cod_atualiza,opcao=0,roda=0,qtd=0;
     No* buscado;
     No* buscado_pesquisa;
     printf("Digite o codigo do produto: ");
     scanf("%d",&cod_atualiza);
     buscado=busca_prod(inicio,cod_atualiza);
     buscado_pesquisa=busca_prod(inicio_database,cod_atualiza);
     if((buscado!=NULL)&&(cod_atualiza!=12345)&&((buscado_pesquisa!=NULL))){
                       printf("\n=> Dados atuais do produto:\n");
                       printf("(1)Nome: %s\n",buscado->produto.nome);
                       printf("(2)Codigo: %d\n",buscado->produto.codigo);
                       printf("(3)Quantidade Atual: %d\n",buscado->produto.qtd_atual);
                       printf("(4)Quantidade Minima: %d\n",buscado->produto.qtd_min);
                       printf("(5)Categoria: %s\n",buscado->produto.categoria);
                       printf("(6)Preco: RS %.2f\n",buscado->produto.preco);
                       printf("(7)Unidades Vendidas: %d\n",buscado->produto.total);
                       printf("Quantas unidades serao acrescidas? ");
                       scanf("%d",&qtd);
                       if(qtd>0){
                                 buscado->produto.qtd_atual+=qtd;
                                 buscado_pesquisa->produto.qtd_atual+=qtd;     
                                 printf("*** Estoque Atualizado!\n");                  
                       }else printf("Erro na atualizacao!\n");
                       /*do{
                          printf("Qual dado deseja atualizar? Exceto (7) e (2)[ou (8)- para sair: ");
                          scanf("%d",&opcao);
                          getchar();
                          switch(opcao){
                                        case 1:{
                                             printf("\nNovo nome: ");
                                             gets(buscado->produto.nome);
                                             while(buscado->produto.nome[roda]!='\0'){
                                                                                      buscado_pesquisa->produto.nome[roda]=buscado->produto.nome[roda];
                                                                                      roda++;
                                             }
                                             buscado_pesquisa->produto.nome[roda]='\0';
                                             break;
                                        }
                                        case 3:{
                                             printf("\nNova Quantidade Atual: ");
                                             scanf("%d",&(buscado->produto.qtd_atual));
                                             buscado_pesquisa->produto.qtd_atual=buscado->produto.qtd_atual;
                                             break;
                                        }
                                        case 4:{
                                             printf("\nNova Quantidade Minima: ");
                                             scanf("%d",&(buscado->produto.qtd_min));
                                             buscado_pesquisa->produto.qtd_min=buscado->produto.qtd_min;
                                             break;
                                        }
                                        case 5:{
                                             roda=0;
                                             printf("\nNova Categoria: ");
                                             gets(buscado->produto.categoria);
                                             while(buscado->produto.categoria[roda]!='\0'){
                                                                                      buscado_pesquisa->produto.categoria[roda]=buscado->produto.categoria[roda];
                                                                                      roda++;
                                             }
                                             buscado_pesquisa->produto.categoria[roda]='\0';
                                             break;
                                        }
                                        case 6:{
                                             printf("\nNovo Preco: RS ");
                                             scanf("%f",&(buscado->produto.preco));
                                             buscado_pesquisa->produto.preco=buscado->produto.preco;
                                             break;
                                        }
                                        case 7: {
                                             printf("\nVoce nao pode alterar a quantidade de unidades vendidas.\n");
                                             break;
                                        }
                                        case 8: break;
                                        default: printf("Opcao invalida!\n");                 
                          }*
                       }while(opcao!=8);*/
     }else printf("Erro na atualizacao!\n");
}

//%%%%%%%%%%%%%%%%%%%%%%% LISTA DE CLIENTES %%%%%%%%%%%%%%%%%%%%%%%%%%
// declaracao dos tipos usados na implementacao

struct clientes{
       char nome[30];
       int codigo;
       float gastos_pesquisa;
};
typedef struct clientes Clientes;

struct lista_ordenada{
       Clientes cliente;
       struct lista_ordenada* prox;
       };
       
typedef struct lista_ordenada Noh; 

struct no_cabeca{
       struct lista_ordenada* prox;
       };  
          
typedef struct no_cabeca No_cabeca;   

//cria lista
No_cabeca* criaLista(void){
    No_cabeca* inicio=(No_cabeca*)malloc(sizeof(No_cabeca));
    inicio->prox=NULL;
    return inicio;
} 

// busca no cujo campo info tem o valor procurado
Noh* busca(No_cabeca* inicio, int valor){
    Noh* percorre=inicio->prox;
    while(percorre!=NULL){
                           if(percorre->cliente.codigo==valor) return percorre; // caso encontre, ja retorna o no
                           percorre=percorre->prox;
                           }
    return NULL; // caso nao encontre
}

// algoritmo de busca que facilita a remocao de um dado no (pois retorna o no anterior ao que sera removido)
Noh* busca_anterior(No_cabeca* inicio, int valor){
    Noh* ant_buscada;
    Noh* buscada;
    if(inicio->prox!=NULL){
                  ant_buscada=inicio->prox;         
                  buscada=inicio->prox; 
                  // se o buscado for o primeiro no, ele eh retornado        
                  if(inicio->prox->cliente.codigo==valor) return inicio->prox;         
                  while((buscada->prox!=NULL)&&(buscada->cliente.codigo!=valor)){  
                         ant_buscada=buscada;
                         buscada=buscada->prox;                       
                  }
                  if(buscada->cliente.codigo==valor) return ant_buscada;
                  return NULL;
    }
    printf(" ** Lista Vazia!!\n");
    return NULL;
}

// insere preservando a ordenacao 
void insereLista(No_cabeca* inicio,Noh* novo){
     Noh* percorre=inicio->prox;
     Noh* ant_percorre=inicio->prox;
     if(novo!=NULL){          
                                              if((inicio->prox==NULL)||(novo->cliente.gastos_pesquisa > inicio->prox->cliente.gastos_pesquisa)){
                                                                               novo->prox=inicio->prox;
                                                                               inicio->prox=novo;
                                               }else{
                                                     while((percorre->prox!=NULL)&&(percorre->prox->cliente.gastos_pesquisa > novo->cliente.gastos_pesquisa)){
                                                                                    percorre=percorre->prox;
                                                     }
                                               novo->prox=percorre->prox;
                                               percorre->prox=novo;
                                               }  
     }else printf(" ** Erro na insercao\n");
}

// remove elemento (caso exista) da lista
void removeLista(No_cabeca* inicio,int valor){
    Noh* ant_buscada;
    Noh* buscada;
    if(inicio->prox!=NULL){
        ant_buscada=busca_anterior(inicio, valor);                   
        if(ant_buscada!=NULL){
                              if(ant_buscada->cliente.codigo==valor){ // teste para ver se o buscado ja eh o primeiro no
                                                           buscada=ant_buscada;
                                                           inicio->prox=buscada->prox;
                              }else{
                                    buscada=ant_buscada->prox;                                    
                                    ant_buscada->prox=buscada->prox; 
                              }
                              free(buscada);
        }else printf(" ** Cliente nao cadastrado\n");
    }else printf(" ** Lista vazia\n");
}

// atualiza dados de um cliente
void atualizaDados(No_cabeca* inicio){
     int cod_atualiza,opcao=0;
     Noh* buscado;
     printf("Digite o codigo do cliente: ");
     scanf("%d",&cod_atualiza);
     buscado=busca(inicio,cod_atualiza);
     if((buscado!=NULL)&&(cod_atualiza!=12345)){
                       printf("=> Dados atuais do cliente:\n");
                       printf("(1)Nome: %s\n",buscado->cliente.nome);
                       printf("OBS: Atualizar nome apenas em caso de digitacao errada.\n");
                       printf("(2)Codigo: %d",buscado->cliente.codigo);
                       do{
                          printf("\nQual dado deseja atualizar? Exceto (2) - (3)- para sair: ");
                          scanf("%d",&opcao);
                          getchar();
                          switch(opcao){
                                        case 1:{
                                             printf("\nNovo Nome: ");
                                             gets(buscado->cliente.nome);
                                             break;
                                        }
                                        case 3:break;
                                        default: printf("Opcao invalida!\n");                 
                          }
                       }while(opcao!=3);
     }else printf("Erro na atualizacao!\n");
}
//imprime nome e codigo de todos os clientes

void imprimeClientes(No_cabeca* inicio){
     if(inicio!=NULL){
                      printf("\n====== Lista de Clientes =======\n");
                      Noh *percorre=inicio->prox;
                      while(percorre!=NULL){
                                            if(percorre->cliente.codigo!=12345){
                                                                                printf("Nome: %s - Codigo: %d\n",percorre->cliente.nome,percorre->cliente.codigo);
                                            }
                                                                                percorre=percorre->prox;
                      }
     }
}

// Imprime top 10 produtos do dia

void top10Produtos(No_cabeca_prod *inicio2){
     int i=1;
     if(inicio2!=NULL){
         system("cls");              
         printf("====== 10 Produtos mais vendidos do dia ======\n");
         No* percorre=inicio2->prox;
                        while(percorre!=NULL) {
                                           if((i<=10)&&(percorre->produto.codigo!=12345)){// imprime os 10 mais vendidos no dia
                                                     printf("%d o: %s - Quantidade: %d\n",i,percorre->produto.nome,percorre->produto.vendas_dia);
                                                     i++;
                                           }// Zera o campo vendas_dia de toda a lista de produtos
                                           percorre->produto.vendas_dia=0;
                                           percorre=percorre->prox;
                        }         
     }
}

// imprime produtos com estoque abaixo do minimo
void produtosFalta(No_cabeca_prod *inicio2){
     if(inicio2!=NULL){
         system("cls");               
         int contador=0;              
         printf("====== Produtos com estoque escasso ======\n");
         No* percorre=inicio2->prox;
         while(percorre!=NULL) {
                               if(percorre->produto.qtd_min>percorre->produto.qtd_atual){
                                                                                        contador=1; 
                                                                                        printf("-> %s - Quantidade: %d / Minimo permitido: %d\n",percorre->produto.nome,percorre->produto.qtd_atual,percorre->produto.qtd_min);
                               }    
                               percorre=percorre->prox;     
         }
         if(contador==0) printf(" ** Todos os produtos estao com estoque suficiente!\n");
     }
}

// imprime balanco diario de caixas
void balancoCaixas(No_cabeca_prod *inicio2){
     if(inicio2!=NULL){
                       system("cls"); 
                       int o=0,num;
                       printf("====== Balanco do dia ======\n");
                       for(o=0;o<5;o++){
                                        num=o+1;
                                        printf("\n->Caixa %d: \n",num);
                                        printf("Unidades Vendidas: %d",caixas[o].unidades);
                                        printf(" | Arrecadacao: RS %.2f",caixas[o].arrecadacao);
                                        printf("\n* %d cliente(s) atendido(s). \n",caixas[o].qtd_clientes);
                       }                
     }
}

void percorreNotasProdutos(No_cabeca_prod* inicio_database,long int data,long int data2,int num){
     int i=0;
     int percorre,percorre2=1,cod_cliente,qtd_prod_dif,numero_compra;
     long int dataCompra;
     int codigo,qtd;
     int total=0;
     No* produtoProcurado,*percorreProduto,*auxiliar,*deletar;
     No_cabeca_prod * cabeca=criarLista();
     FILE *arquivo2=fopen("compras.dat","rb");
     percorre=1;
     while(percorre<=num){
                           fread(&numero_compra,sizeof(int),1,arquivo2);
                           fread(&dataCompra,sizeof(dataCompra),1,arquivo2);
                           fread(&cod_cliente,sizeof(int),1,arquivo2);
                           fread(&qtd_prod_dif,sizeof(int),1,arquivo2);
                           for(percorre2=1;percorre2<=qtd_prod_dif;percorre2++){
                                          fread(&codigo,sizeof(int),1,arquivo2);
                                          fread(&qtd,sizeof(int),1,arquivo2);   
                                          produtoProcurado=busca_prod(inicio_database,codigo);
                                          total=qtd;
                                          if((dataCompra<=data2)&&(dataCompra>=data)&&(produtoProcurado!=NULL)){
                                                         produtoProcurado->produto.total_pesquisa=produtoProcurado->produto.total_pesquisa+total;
                                          }           
                           } 
                           percorre++;                             
     }
     fclose(arquivo2);
     percorreProduto=inicio_database->prox;
     //ordena a lista de produtos(database2) pelo campo total_pesquisa
     while(percorreProduto!=NULL){
                   if(percorreProduto->produto.codigo!=12345){               
                           auxiliar=(No*)malloc(sizeof(No));
                           auxiliar->produto.codigo=percorreProduto->produto.codigo;
                           auxiliar->produto.preco=percorreProduto->produto.preco;
                           auxiliar->produto.qtd_atual=percorreProduto->produto.qtd_atual;
                           auxiliar->produto.qtd_min=percorreProduto->produto.qtd_min;
                           auxiliar->produto.total=percorreProduto->produto.total;
                           auxiliar->produto.total_pesquisa=percorreProduto->produto.total_pesquisa;
                           auxiliar->produto.vendas_dia=percorreProduto->produto.vendas_dia;
                           i=0;
                           while(percorreProduto->produto.nome[i]!='\0'){
                                                                  auxiliar->produto.nome[i]=percorreProduto->produto.nome[i];
                                                                  i++;
                           }
                           auxiliar->produto.nome[i]='\0';
                           i=0;
                           while(percorreProduto->produto.categoria[i]!='\0'){
                                                                  auxiliar->produto.categoria[i]=percorreProduto->produto.categoria[i];
                                                                  i++;
                           }
                           auxiliar->produto.categoria[i]='\0';
                           insereProdutoPesquisa(cabeca,auxiliar);
                   }
                   percorreProduto=percorreProduto->prox;
     }
     percorreProduto=cabeca->prox;
     printf("\n Lista de Produtos (Do 'melhor' para o 'pior'):\n");
     //imprime melhores produtos
     i=1;
     while(percorreProduto!=NULL){
                                  if(percorreProduto->produto.codigo!=12345){
                                           printf("%d) %s - Total de vendas: %d unidades \n",i,percorreProduto->produto.nome,percorreProduto->produto.total_pesquisa);

                                           //zera o campo total_pesquisa
                                           percorreProduto->produto.total_pesquisa=0;
                                           //imprime de 10 em 10
                                           if(i%10==0){
                                                       printf("\n Tecle ENTER para continuar ...\n");
                                                       getchar();
                                                       getchar();
                                           }
                                           i++;
                                  }
                                  deletar=percorreProduto;
                                  percorreProduto=percorreProduto->prox;
                                  removeProduto(cabeca,deletar->produto.codigo);
     }
     free(cabeca);// acaba com a lista auxiliar
}

void percorreNotasClientes(No_cabeca* inicio,No_cabeca_prod* inicio_database,long int data2,int num){
     int i=0;
     int percorre=1,percorre2=1,cod_cliente,qtd_prod_dif,numero_compra;
     long int dataCompra;
     int codigo,qtd;
     float total=0;
     Noh* clienteProcurado,*percorreCliente,*auxiliar,*deletar;
     No* produtoProcurado;
     No_cabeca *ordenado=criaLista();
     FILE *arquivo2=fopen("compras.dat","rb");
     while(percorre<=num){
                           fread(&numero_compra,sizeof(int),1,arquivo2);
                           fread(&dataCompra,sizeof(int),1,arquivo2);
                           fread(&cod_cliente,sizeof(int),1,arquivo2);
                           fread(&qtd_prod_dif,sizeof(int),1,arquivo2);
                           clienteProcurado=busca(inicio,cod_cliente);
                           for(percorre2=1;percorre2<=qtd_prod_dif;percorre2++){
                                          fread(&codigo,sizeof(int),1,arquivo2);
                                          fread(&qtd,sizeof(int),1,arquivo2);   
                                          produtoProcurado=busca_prod(inicio_database,codigo);
                                          if(produtoProcurado!=NULL)total=qtd*(produtoProcurado->produto.preco);  
                                          if(dataCompra<=data2){
                                                         if(clienteProcurado!=NULL) clienteProcurado->cliente.gastos_pesquisa=clienteProcurado->cliente.gastos_pesquisa+total;
                                          }           
                         } 
                         percorre++;                             
     }
     fclose(arquivo2);
     percorreCliente=inicio->prox;
     //carrega uma lista nova ordenada por Gastos dos clientes no periodo
     while(percorreCliente!=NULL){
                  if(percorreCliente->cliente.codigo!=12345){                
                           auxiliar=(Noh*)malloc(sizeof(Noh));
                           auxiliar->cliente.codigo=percorreCliente->cliente.codigo;
                           auxiliar->cliente.gastos_pesquisa=percorreCliente->cliente.gastos_pesquisa;
                           i=0;
                           while(percorreCliente->cliente.nome[i]!='\0'){
                                                                  auxiliar->cliente.nome[i]=percorreCliente->cliente.nome[i];
                                                                  i++;
                           }
                           auxiliar->cliente.nome[i]='\0';
                           insereLista(ordenado,auxiliar);
                           percorreCliente->cliente.gastos_pesquisa=0; //volta a ser zero
                  }
                  percorreCliente=percorreCliente->prox;
     }
     percorreCliente=ordenado->prox;
     printf("\n Lista de Clientes (Do 'melhor' para o 'pior'):\n");
     //imprime melhores clientes
     i=1;
     while(percorreCliente!=NULL){
                                  printf("%d) %s - RS %.2f\n",i,percorreCliente->cliente.nome,percorreCliente->cliente.gastos_pesquisa);
                                  deletar=percorreCliente;
                                  percorreCliente=percorreCliente->prox;
                                  removeLista(ordenado,deletar->cliente.codigo);
                                  //imprime de 10 em 10
                                           if(i%10==0){
                                                       printf("\n Tecle ENTER para continuar ...\n");
                                                       getchar();
                                                       getchar();
                                           }
                                           i++;
     }
     free(ordenado); //acaba com a lista criada para a pesquisa
     
}

// imprime Nota fiscal (a partir de um codigo que a identifica)
void imprimeNotaFiscal(No_cabeca_prod* inicio2,int num){
     int percorre=1,percorre2=1,cod_cliente,qtd_prod_dif,numero_compra;
     long int data;
     int codigo,qtd;
     float total=0,total_prod=0;
     No* buscado;
     FILE *arquivo=fopen("compras.dat","rb");
     printf("\n==== Nota Fiscal ====\n");
     while(percorre<num){
                                             fread(&numero_compra,sizeof(int),1,arquivo);
                                             fread(&data,sizeof(data),1,arquivo);
                                             fread(&cod_cliente,sizeof(int),1,arquivo);
                                             fread(&qtd_prod_dif,sizeof(int),1,arquivo);
                                             for(percorre2=1;percorre2<=qtd_prod_dif;percorre2++){
                                                                                                  fread(&codigo,sizeof(int),1,arquivo);
                                                                                                  fread(&qtd,sizeof(int),1,arquivo);                    
                                             } 
                                             percorre++;                                  
     }
     if(percorre==num){
                                          total=0;
                                          total_prod=0;   
                                          fread(&numero_compra,sizeof(int),1,arquivo);
                                          printf("\nNumero da compra: %d\n",numero_compra);
                                          fread(&data,sizeof(int),1,arquivo);
                                          printf("Data da compra(AAAAMMDD): %li\n",data);
                                          fread(&cod_cliente,sizeof(int),1,arquivo);
                                          printf("Codigo do Cliente: %d\n\n",cod_cliente);
                                          fread(&qtd_prod_dif,sizeof(int),1,arquivo);
                                          for(percorre2=1;percorre2<=qtd_prod_dif;percorre2++){
                                                                                               total_prod=0;
                                                                                               fread(&codigo,sizeof(int),1,arquivo);
                                                                                               fread(&qtd,sizeof(int),1,arquivo);
                                                                                               buscado=busca_prod(inicio2,codigo);
                                                                                               if(buscado!=NULL){
                                                                                                                 total_prod=qtd*(buscado->produto.preco);
                                                                                                                 total=total+total_prod;
                                                                                                                 printf("%s - %d x %.2f = RS %.2f\n",buscado->produto.nome,qtd,buscado->produto.preco,total_prod);
                                                                                               }else printf("Produto nao mais cadastrado\n");// nao acontece!
                                          }
                                          printf("Total: RS %.2f\n",total);
     }else printf("\n ** Nota Fiscal Inexistente!\n");
     fclose(arquivo);
}

long int recebeValidaData(void){
    int ano, mes, dia;
    long int data;
    printf("Digite o ano: ");
    scanf("%d",&ano);
    printf("Digite o mes: ");
    scanf("%d",&mes);
    printf("Digite o dia: ");
    scanf("%d",&dia);
    if((ano>0)&&(dia>0)&&(dia<=30)&&(mes>0)&&(mes<=12)){
                   data=dia+(mes*100)+(ano*10000);
                   return data;
    }//else
    return 0;
}

long int atualizaData(long int data){
    int ano, mes, dia;
    ano=data/10000;
    mes=(data-(ano*10000))/100;
    dia=(data-(ano*10000))-(mes*100);
    dia++;
    if(dia==31){
                dia=1;
                mes++;
                if(mes==13){
                            mes=1;
                            ano++;
                     }
    }
    data=dia+(mes*100)+(ano*10000);
    return data;
}
     
// &&&&&&&&&  MENU &&&&&&&&&

int menu(No_cabeca* inicio,No_cabeca_prod* inicio2,No_cabeca_prod* inicio_database){
     No* auxiliar;
     FILE *arquivo;
     int opcao,sub_opcao,senha,cod_remove,i,j;
     long int data,data2;
     system("cls");
     printf("=> Qual operacao deseja efetuar?\n\n");
     printf("(1) - Atualizar/Cadastrar Clientes (Restrito ao Gerente - Senha necessaria)\n");
     printf("(2) - Atualizar Dados de estoque(Restrito ao Gerente - Senha necessaria)\n");
     printf("(3) - Realizar transacao\n");
     printf("(4) - Imprimir lista de clientes\n");
     printf("(5) - Imprimir lista de produtos\n");
     printf("(6) - Imprimir nota fiscal de compra anteriormente realizada\n");
     printf("(7) - Encerrar Caixas no dia e Exibir Relatorios(Senha necessaria)\n");
     printf("(8) - Melhores Clientes (ate data determinado) \n");
     printf("(9) - Produtos mais vendidos (intervalo de tempo determinado)\n");
     printf("(10) - Imprimir Lista de todos os produtos ja existentes no supermercado\n");
     printf("(11) - Encerrar Sistema \n");
     scanf("%d",&opcao);
     switch(opcao){  
                     case 1:{
                          printf("\n *** Digite a senha de acesso: ");
                          scanf("%d",&senha);
                          if(senha==12345){
                                           printf("\n (1) - Adicionar cliente\n");
                                           printf(" (2) - Atualizar cliente\n");
                                           printf("=> ");
                                           scanf("%d",&sub_opcao);
                                           switch(sub_opcao){
                                                             case 1:{
                                                                  Noh* novo=(Noh*)malloc(sizeof(Noh));
                                                                  if(novo!=NULL){
                                                                                printf("\nCodigo do novo cliente: ");
                                                                                scanf("%d",&(novo->cliente.codigo));
                                                                                getchar();
                                                                                novo->cliente.gastos_pesquisa=0;
                                                                                if(busca(inicio,novo->cliente.codigo)==NULL){
                                                                                               printf("Nome do novo cliente: ");
                                                                                               gets(novo->cliente.nome);                                   
                                                                                               insereLista(inicio,novo);
                                                                                }else printf("\nCodigo ja cadastrado!!\n");
                                                                  }else printf("\nErro na insercao!\n");
                                                                  break;
                                                             }
                                                             case 2: atualizaDados(inicio); break;
                                                             default: printf("Opcao invalida!\n"); break;
                                           }
                          }else printf("\nSenha Errada! Acesso restrito ao gerente!\n");
                          break;
                     }
                     case 2:{                         
                          printf("\n *** Digite a senha de acesso: ");
                          scanf("%d",&senha);
                          if(senha==12345){
                                           printf("\n (1) - Adicionar produto\n");
                                           printf(" (2) - Atualizar estoque de produto\n");
                                           printf(" (3) - Remover produto\n");
                                           printf("=> ");
                                           scanf("%d",&sub_opcao);
                                           switch(sub_opcao){
                                                             case 1:{
                                                                  No* novo=(No*)malloc(sizeof(No));
                                                                  No* novo_database=(No*)malloc(sizeof(No));         
                                                                  if(novo!=NULL){
                                                                                printf("\nCodigo do novo produto: ");
                                                                                scanf("%d",&novo->produto.codigo);
                                                                                novo_database->produto.codigo=novo->produto.codigo;
                                                                                getchar();
                                                                                // teste se codigo ja foi de algum produto que agora esta apenas no database
                                                                                // e, portanto, tambem testa se pertence a um produto que esta atualmente no supermercado
                                                                                if(busca_prod(inicio_database,novo->produto.codigo)==NULL){
                                                                                               printf("Nome do novo produto: ");
                                                                                               gets(novo->produto.nome);
                                                                                               j=0;
                                                                                               while(novo->produto.nome[j]!='\0'){
                                                                                                       novo_database->produto.nome[j]=novo->produto.nome[j];  
                                                                                                       j++;                         
                                                                                               }
                                                                                               novo_database->produto.nome[j]=novo->produto.nome[j];
                                                                                               printf("Quantidade do novo produto: ");
                                                                                               scanf("%d",&novo->produto.qtd_atual);
                                                                                               novo_database->produto.qtd_atual=novo->produto.qtd_atual;
                                                                                               getchar();
                                                                                               printf("Quantidade minima do produto: ");
                                                                                               scanf("%d",&novo->produto.qtd_min); 
                                                                                               novo_database->produto.qtd_min=novo->produto.qtd_min;
                                                                                               getchar(); 
                                                                                               printf("Preco unitario do novo produto: ");
                                                                                               scanf("%f",&novo->produto.preco); 
                                                                                               novo_database->produto.preco=novo->produto.preco; 
                                                                                               getchar();
                                                                                               printf("Categoria do novo produto: ");
                                                                                               gets(novo->produto.categoria);
                                                                                               j=0;
                                                                                               while(novo->produto.categoria[j]!='\0'){
                                                                                                       novo_database->produto.categoria[j]=novo->produto.categoria[j];  
                                                                                                       j++;                         
                                                                                               }
                                                                                               novo_database->produto.categoria[j]=novo->produto.categoria[j];
                                                                                               novo->produto.total=0;   
                                                                                               novo->produto.vendas_dia=0;      
                                                                                               novo->produto.total_pesquisa=0; 
                                                                                               novo_database->produto.total=0;   
                                                                                               novo_database->produto.vendas_dia=0;      
                                                                                               novo_database->produto.total_pesquisa=0;                     
                                                                                               insereProduto(inicio2,novo);
                                                                                               insereProdutoPesquisa(inicio_database,novo_database);
                                                                                }else{ 
                                                                                       printf("\nCodigo indisponivel!!\n");
                                                                                       free(novo);
                                                                                       }
                                                                  }else printf("\nErro na insercao!\n");
                                                                  break;
                                                             }
                                                             case 2: atualizaDados_prod(inicio2,inicio_database); break;
                                                             case 3: {
                                                                      printf("\nCodigo do produto: ");
                                                                      scanf("%d",&cod_remove);
                                                                      if(cod_remove!=12345) removeProduto(inicio2,cod_remove);
                                                                      break;          
                                                             }
                                                             default: printf("Opcao invalida!\n"); break;
                                           }
                          }else printf("\nSenha Errada! Acesso restrito ao gerente!\n");
                          break;
                          }
                          case 3:{
                                int caixa,cod_cliente,cod_prod,qtd;
                                Noh* buscado_cliente;
                                No* buscado_prod;
                                No_cabeca_prod *inicio3=criarLista(); 
                                No* percorre;
                                int qtd_prod_dif=0; // quantidade de produtos diferentes (para manipular arquivo de dados)
                                                  printf("Digite o codigo do cliente: ");
                                                  scanf("%d",&cod_cliente);
                                                  buscado_cliente=busca(inicio,cod_cliente);
                                                  if((buscado_cliente!=NULL)&&((cod_cliente!=12345))){
                                                              printf("Nome do Cliente: %s\n",buscado_cliente->cliente.nome);
                                                                    // lê qual caixa
                                                                    printf("\nQual o caixa? ");
                                                                    scanf("%d",&caixa);
                                                                    if((caixa>=1)&&(caixa<=5)){
                                                                            // lê os produtos de determinada compra
                                                                            qtd_prod_dif=0;
                                                                            do{
                                                                               printf("Digite o codigo do produto(0 para encerrar):");
                                                                               scanf("%d",&cod_prod);
                                                                               if(cod_prod!=0){
                                                                                      buscado_prod=busca_prod(inicio2,cod_prod);
                                                                                      if((buscado_prod!=NULL)&&(cod_prod!=12345)){
                                                                                          printf("Produto: %s\n",buscado_prod->produto.nome);                  
                                                                                          printf("Quantidade: ");
                                                                                          scanf("%d",&qtd);
                                                                                          // testa se o estoque dispoe da quantidade desejada
                                                                                          if((qtd<=buscado_prod->produto.qtd_atual)&&(qtd>0)){
                                                                                                 // atualiza estoque e mais vendidos do dia  
                                                                                                 int i=0; 
                                                                                                 auxiliar=(No*)malloc(sizeof(No));                                       
                                                                                                 auxiliar->produto.qtd_atual=buscado_prod->produto.qtd_atual-qtd;
                                                                                                 auxiliar->produto.total=buscado_prod->produto.total+qtd;
                                                                                                 auxiliar->produto.vendas_dia=buscado_prod->produto.vendas_dia+qtd;
                                                                                                 auxiliar->produto.codigo=buscado_prod->produto.codigo;
                                                                                                 while(buscado_prod->produto.nome[i]!='\0'){
                                                                                                 auxiliar->produto.nome[i]=buscado_prod->produto.nome[i];
                                                                                                 i++;
                                                                                                 }
                                                                                                 auxiliar->produto.nome[i]='\0';
                                                                                                 i=0;
                                                                                                 auxiliar->produto.preco=buscado_prod->produto.preco;
                                                                                                 auxiliar->produto.qtd_min=buscado_prod->produto.qtd_min;
                                                                                                 while(buscado_prod->produto.categoria[i]!='\0'){
                                                                                                 auxiliar->produto.categoria[i]=buscado_prod->produto.categoria[i];
                                                                                                 i++;
                                                                                                 }
                                                                                                 auxiliar->produto.categoria[i]='\0';
                                                                                                 removeProduto(inicio2,buscado_prod->produto.codigo);
                                                                                                 insereProduto(inicio2,auxiliar);   
                                                                                                 
                                                                                                 // Atualiza balanco de caixas (diário)
                                                                                                 caixas[caixa-1].unidades=caixas[caixa-1].unidades+qtd;//(caixa-1) porque vetor comeca de indice 0
                                                                                                 caixas[caixa-1].arrecadacao=caixas[caixa-1].arrecadacao+(qtd*buscado_prod->produto.preco);
                                                                                                 
                                                                                                 //cria lista para auxiliar no armazenamento de produtos
                                                                                                 No* novo=(No*)malloc(sizeof(No));
                                                                                                 novo->produto.codigo=cod_prod;
                                                                                                 novo->produto.qtd_atual=qtd;
                                                                                                 novo->produto.vendas_dia=0; //porque o insere ordena por esse campo
                                                                                                 insereProduto(inicio3,novo);
                                                                                                 qtd_prod_dif++;
                                                                                          }else{
                                                                                                 if (qtd<=0) printf(" *** Quantidade invalida!\n");  
                                                                                                 else printf(" *** Estoque insuficiente!\n");
                                                                                                }   
                                                                               
                                                                                      }else printf("Codigo invalido!\n");
                                                                               }      
                                                                               }while(cod_prod!=0);
                                                                               if(qtd_prod_dif!=0) {
                                                                                                   caixas[caixa-1].qtd_clientes++; // incrementa a qtd de clientes do caixa!
                                                                                                   int c=1;
                                                                                                   num_compra++;// incrementa o codigo que identifica a compra
                                                                                                   
                                                                                                   // atualiza todos os dados!
                                                                                                   
                                                                                                   arquivo=fopen("compras.dat","ab"); // abre o arquivo para anexacao de dados
                                                                                                   
                                                                                                   //escreve dados da compra no arquivo (sem apagar o que ja ha nele)
                                                                                                   fwrite(&num_compra,sizeof(int),1,arquivo);
                                                                                                   fwrite(&data_ant,sizeof(data_ant),1,arquivo);
                                                                                                   fwrite(&cod_cliente,sizeof(int),1,arquivo);
                                                                                                   fwrite(&qtd_prod_dif,sizeof(int),1,arquivo);
                                                                                                   fclose(arquivo); 
                                                                                                   percorre=inicio3->prox;
                                                                                                   while(percorre!=NULL){
                                                                                                                         arquivo=fopen("compras.dat","ab");
                                                                                                                         fwrite(&(percorre->produto.codigo),sizeof(int),1,arquivo);
                                                                                                                         fwrite(&(percorre->produto.qtd_atual),sizeof(int),1,arquivo);
                                                                                                                         removeProduto(inicio3,percorre->produto.codigo);
                                                                                                                         percorre=percorre->prox;
                                                                                                                         fclose(arquivo); 
                                                                                                   } 
                                                                                              
                                                                                                   do{
                                                                                                      printf("Imprimir nota fiscal? 1-Sim / 2-Nao : ");
                                                                                                      scanf("%d",&c); 
                                                                                                      switch(c){
                                                                                                                case 1: imprimeNotaFiscal(inicio2,num_compra);break;
                                                                                                                case 2: break;
                                                                                                                default: printf("\n ** Operacao invalida!\n");break;
                                                                                                      }
                                                                                                   }while((c!=2)&&(c!=1));
                                                                               }
                                                                       }else printf("Caixa invalido!\n");
                                                  }else printf("Cliente nao cadastrado!\n");
                                 break;
                          }
                          case 4:{
                               imprimeClientes(inicio);break;
                          }
                          case 5:{
                               imprimeProdutos(inicio2);break;
                          }     
                          case 6:{
                               int num;
                               printf("Digite o numero da nota fiscal: ");
                               scanf("%d",&num);
                               getchar();
                               if(num<=num_compra){
                                                   imprimeNotaFiscal(inicio_database,num);
                               }else printf(" ** Nota Fiscal inexistene!\n");
                               break;
                               }
                          case 7:{
                               int z;
                               printf("\n *** Digite a senha de acesso: ");
                               scanf("%d",&senha);
                               getchar(); // limpa buffer
                               if(senha==12345){
                                                data_ant=atualizaData(data_ant); // atualiza data final(finaliza dia)
                                                top10Produtos(inicio2); 
                                                printf("\nTecle ENTER para continuar ");
                                                getchar();
                                                produtosFalta(inicio2); // imprime produtos abaixo do estoque minimo 
                                                printf("\nTecle ENTER para continuar ");
                                                getchar();  
                                                balancoCaixas(inicio2); // imprime balanco do dia dos caixas  
                                                printf("\nTecle ENTER para continuar ");
                                                getchar();   
                                                for(z=0;z<5;z++){ // Zera dados diarios de caixa
                                                caixas[z].unidades=0;
                                                caixas[z].arrecadacao=0;
                                                caixas[z].qtd_clientes=0;
                                                }
                               }else printf("Senha invalida!!\n");
                               break;
                          }
                          case 8:{
                               printf("\n*Fim do Periodo Considerado:\n");
                               data=recebeValidaData();
                               //checa se o perido eh valido
                               if(data!=0){
                                                    percorreNotasClientes(inicio,inicio_database,data,num_compra);                    
                               }else printf("\nPeriodo invalido!");     
                               break;
                          }
                          case 9:{
                               printf("\n*Inicio do Perido:\n");
                               data=recebeValidaData();
                               printf("\n*Fim do Perido:\n");
                               data2=recebeValidaData();
                               //checa se o perido eh valido
                               if((data!=0)&&(data2!=0)&&(data<=data2)){
                                                    percorreNotasProdutos(inicio_database,data,data2,num_compra);                   
                               }else printf("\nPeriodo invalido!");     
                               break;
                          }
                          case 10: {
                               imprimeProdutos(inicio_database);break;
                               break;
                          }
                          case 11: break;
                          default:{
                                   printf("Operacao invalida!\n");break;
                          }
     }
     return opcao;
}
     
int main(){
    Noh* novo;
    No_cabeca_prod* inicio2=criarLista();
    No_cabeca_prod* inicio_database=criarLista();
    No_cabeca* inicio=criaLista();
    char nome[30];
    int codigo;
    int i,j=0,controle=1,eof=0;
    float gastos_pesquisa=0;
    
    // armazena em lista encadeada dados dos clientes salvos no arquivo
    FILE *clientes=fopen("clientes.dat","rb");
    while(eof==0){//testa fim de arquivo
          novo=(Noh*)malloc(sizeof(Noh));
          fread(nome,sizeof(nome),1,clientes);
          fread(&codigo,sizeof(int),1,clientes);
          fread(&gastos_pesquisa,sizeof(float),1,clientes);
          fread(&eof,sizeof(int),1,clientes);
          j=0;
          while(nome[j]!='\0'){
                               novo->cliente.nome[j]=nome[j];
                               j++;
          }
          novo->cliente.nome[j]='\0';
          novo->cliente.codigo=codigo;
          novo->cliente.gastos_pesquisa=gastos_pesquisa;
          insereLista(inicio,novo);
          
    }
    fclose(clientes);
    // Recupera ultima data de compra realizada (evitar fraude)
    FILE *datas=fopen("datas.dat","rb");
    fread(&data_ant,sizeof(data_ant),1,datas);
    fclose(datas);
    
    // Recupera o numero da ultima compra realizada
    FILE *compras=fopen("qtd_compras.dat","rb");
    fread(&num_compra,sizeof(int),1,compras);
    fclose(compras);
    
    // Recupera dados diarios dos caixas(caso o sistema encerre antes de o dia acabar)
    FILE *dados_caixas=fopen("caixas.dat","rb");
    int w=0;
    for(w=0;w<5;w++){
                     fread(&(caixas[w].unidades),sizeof(int),1,dados_caixas);
                     fread(&(caixas[w].arrecadacao),sizeof(float),1,dados_caixas);
                     fread(&(caixas[w].qtd_clientes),sizeof(int),1,dados_caixas);
                     fread(&(caixas[w].qtd_cli_dif),sizeof(int),1,dados_caixas);
    }
    fclose(dados_caixas);
    
    // armazena em lista encadeada dados dos produtos salvos no arquivo
    FILE *produtos=fopen("produtos.dat","rb");
    int codigoProd, qtd_atual, qtd_min,vendas_dia,total,total_pesquisa;
    float preco;
    char nomeProd[20];
    char categoria[10];
    eof=0;
    while(eof==0){
          No *novo2=(No*)malloc(sizeof(No));
          fread(nomeProd,sizeof(nomeProd),1,produtos);
          fread(categoria,sizeof(categoria),1,produtos);
          fread(&codigoProd,sizeof(int),1,produtos);
          fread(&qtd_min,sizeof(int),1,produtos);
          fread(&qtd_atual,sizeof(int),1,produtos);
          fread(&vendas_dia,sizeof(int),1,produtos);
          fread(&total,sizeof(int),1,produtos);
          fread(&preco,sizeof(float),1,produtos);
          fread(&total_pesquisa,sizeof(int),1,produtos);
          fread(&eof,sizeof(int),1,produtos);
          j=0;
          while(nomeProd[j]!='\0'){
                               novo2->produto.nome[j]=nomeProd[j];
                               j++;
          }
          novo2->produto.nome[j]='\0';
          j=0;
          while(categoria[j]!='\0'){
                               novo2->produto.categoria[j]=categoria[j];
                               j++;
          }
          novo2->produto.categoria[j]='\0';
          novo2->produto.preco=preco;
          novo2->produto.codigo=codigoProd;
          novo2->produto.qtd_atual=qtd_atual;
          novo2->produto.qtd_min=qtd_min;
          novo2->produto.vendas_dia=vendas_dia;
          novo2->produto.total=total;
          novo2->produto.total_pesquisa=total_pesquisa;
          insereProduto(inicio2,novo2);
          
    }
    fclose(produtos);
    
    // armazena em lista encadeada dados dos produtos(DATABASE) salvos no arquivo
    eof=0;
    produtos=fopen("produtos_database.dat","rb");
    while(eof==0){
          No* novo3=(No*)malloc(sizeof(No));
          fread(nomeProd,sizeof(nomeProd),1,produtos);
          fread(categoria,sizeof(categoria),1,produtos);
          fread(&codigoProd,sizeof(int),1,produtos);
          fread(&qtd_min,sizeof(int),1,produtos);
          fread(&qtd_atual,sizeof(int),1,produtos);
          fread(&vendas_dia,sizeof(int),1,produtos);
          fread(&total,sizeof(int),1,produtos);
          fread(&preco,sizeof(float),1,produtos);
          fread(&total_pesquisa,sizeof(int),1,produtos);
          fread(&eof,sizeof(int),1,produtos);
          j=0;
          while(nomeProd[j]!='\0'){
                               novo3->produto.nome[j]=nomeProd[j];
                               j++;
          }
          novo3->produto.nome[j]='\0';
          j=0;
          while(categoria[j]!='\0'){
                               novo3->produto.categoria[j]=categoria[j];
                               j++;
          }
          novo3->produto.categoria[j]='\0';
          novo3->produto.preco=preco;
          novo3->produto.codigo=codigoProd;
          novo3->produto.qtd_atual=qtd_atual;
          novo3->produto.qtd_min=qtd_min;
          novo3->produto.vendas_dia=vendas_dia;
          novo3->produto.total=total;
          novo3->produto.total_pesquisa=total_pesquisa;
          insereProdutoPesquisa(inicio_database,novo3);   
    }
    fclose(produtos);
    
    int operacao;
    printf(".........................................................\n");
    printf("                 BEM-VINDO AO SISTEMA\n");
    printf(".........................................................\n");
    printf("-> Informacos recuperadas do banco de dados com sucesso!\n");
    printf("Data(AAAAMMDD): %li\n",data_ant);
    printf("---------------------------------------------------------\n");
    printf("Tecle ENTER para comecar a interagir com o sistema\n");
    getchar();
    do{
           switch(controle){
                            case 1: operacao=menu(inicio,inicio2,inicio_database); break;
                            default: printf("\n** Operacao Invalida!! **\n"); break;
           }
           if(operacao!=11){ // nao houver encerrado o sistema
                           printf("\n=> 1 - Continuar no Sistema\n");
                           printf("=> 0 - Encerrar o Sistema\n");
                           printf("-> ");
                           scanf("%d",&controle);
           }
    }while((controle!=0)&&(operacao!=11));

    // ATUALIZACAO DE DADOS AO ENCERRAR O PROGRAMA
    
    // atualiza no arquivo data de ultima transacao
    FILE *datas2=fopen("datas.dat","wb"); // sobrepoe nova data
    fwrite(&data_ant,sizeof(data_ant),1,datas2);
    fclose(datas2);
    
    // atualiza no arquivo numero de ultima transacao
    compras=fopen("qtd_compras.dat","wb");
    fwrite(&num_compra,sizeof(int),1,compras);
    fclose(compras);
    
    //Atualiza dados dos caixas (evita que se perda dados quando o sistema encerra antes do fim do dia)
    dados_caixas=fopen("caixas.dat","wb");
    w=0;
    for(w=0;w<5;w++){
                     fwrite(&(caixas[w].unidades),sizeof(int),1,dados_caixas);
                     fwrite(&(caixas[w].arrecadacao),sizeof(float),1,dados_caixas);
                     fwrite(&(caixas[w].qtd_clientes),sizeof(int),1,dados_caixas);
                     fwrite(&(caixas[w].qtd_cli_dif),sizeof(int),1,dados_caixas);
    }
    fclose(dados_caixas);
    
    // atualiza lista de clientes
    clientes=fopen("clientes.dat","wb");
    i=1;
    Noh* percorre=inicio->prox;
    while(percorre!=NULL){
                          j=0;
                           while(percorre->cliente.nome[j]!='\0'){
                               nome[j]=percorre->cliente.nome[j];
                               j++;
                           }
                           nome[j]='\0';
                           codigo=percorre->cliente.codigo;
                           gastos_pesquisa=percorre->cliente.gastos_pesquisa;
                           fwrite(nome,sizeof(nome),1,clientes);
                           fwrite(&codigo,sizeof(int),1,clientes);
                           fwrite(&gastos_pesquisa,sizeof(float),1,clientes);
                           percorre=percorre->prox;
                           if(percorre==NULL) eof=1;
                           else eof=0;
                           fwrite(&eof,sizeof(controle),1,clientes);
    }
    fclose(clientes);
    
    // atualiza lista de produtos
    produtos=fopen("produtos.dat","wb");
    No* percorre2=inicio2->prox;
    while(percorre2!=NULL){
          j=0;
          while(percorre2->produto.nome[j]!='\0'){
                               nomeProd[j]=percorre2->produto.nome[j];
                               j++;
          }
          nomeProd[j]='\0';
          j=0;
          while(percorre2->produto.categoria[j]!='\0'){
                               categoria[j]=percorre2->produto.categoria[j];
                               j++;
          }
          categoria[j]='\0';
          preco=percorre2->produto.preco;
          codigoProd=percorre2->produto.codigo;
          qtd_atual=percorre2->produto.qtd_atual;
          qtd_min=percorre2->produto.qtd_min;
          vendas_dia=percorre2->produto.vendas_dia;
          total=percorre2->produto.total;
          total_pesquisa=percorre2->produto.total_pesquisa;
          
          fwrite(nomeProd,sizeof(nomeProd),1,produtos);
          fwrite(categoria,sizeof(categoria),1,produtos);
          fwrite(&codigoProd,sizeof(int),1,produtos);
          fwrite(&qtd_min,sizeof(int),1,produtos);
          fwrite(&qtd_atual,sizeof(int),1,produtos);
          fwrite(&vendas_dia,sizeof(int),1,produtos);
          fwrite(&total,sizeof(int),1,produtos);
          fwrite(&preco,sizeof(float),1,produtos);  
          fwrite(&total_pesquisa,sizeof(int),1,produtos);
          percorre2=percorre2->prox;  
          if(percorre2==NULL) eof=1; // testa fim de arquivo
                           else eof=0;
          fwrite(&eof,sizeof(int),1,produtos); 
    }
    fclose(produtos);
    
    // atualiza lista de produtos(DATABASE)
    produtos=fopen("produtos_database.dat","wb");
    No* percorre3=inicio_database->prox;
    while(percorre3!=NULL){
          j=0;
          while(percorre3->produto.nome[j]!='\0'){
                               nomeProd[j]=percorre3->produto.nome[j];
                               j++;
          }
          nomeProd[j]='\0';
          j=0;
          while(percorre3->produto.categoria[j]!='\0'){
                               categoria[j]=percorre3->produto.categoria[j];
                               j++;
          }
          categoria[j]='\0';
          preco=percorre3->produto.preco;
          codigoProd=percorre3->produto.codigo;
          qtd_atual=percorre3->produto.qtd_atual;
          qtd_min=percorre3->produto.qtd_min;
          vendas_dia=percorre3->produto.vendas_dia;
          total=percorre3->produto.total;
          total_pesquisa=percorre3->produto.total_pesquisa;
          
          fwrite(nomeProd,sizeof(nomeProd),1,produtos);
          fwrite(categoria,sizeof(categoria),1,produtos);
          fwrite(&codigoProd,sizeof(int),1,produtos);
          fwrite(&qtd_min,sizeof(int),1,produtos);
          fwrite(&qtd_atual,sizeof(int),1,produtos);
          fwrite(&vendas_dia,sizeof(int),1,produtos);
          fwrite(&total,sizeof(int),1,produtos);
          fwrite(&preco,sizeof(float),1,produtos);  
          fwrite(&total_pesquisa,sizeof(int),1,produtos);
          percorre3=percorre3->prox;  
          if(percorre3==NULL) eof=1; // testa fim de arquivo
                           else eof=0;
          fwrite(&eof,sizeof(int),1,produtos); 
    }
    fclose(produtos);
    return 0;
}
