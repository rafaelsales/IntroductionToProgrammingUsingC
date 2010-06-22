#include <stdio.h>
#include <stdlib.h>

int main()
  {
    int codigoProd=12345, qtd_atual=0, qtd_min=0,vendas_dia=0,total=0,controle=1,controle2=0;
    float preco=0,controle3=0,gastos_pesquisa=0;
    long int data=20081027;
    float total_pesquisa=0;
    char nome[30]="lucas assuncao(gerente)";
    int codigo=12345;
    char nomeProd[20]="Produto padrao";
    char categoria[10]="nulo";
    FILE *produtos=fopen("produtos.dat","wb");
          fwrite(nomeProd,sizeof(nomeProd),1,produtos);
          fwrite(categoria,sizeof(categoria),1,produtos);
          fwrite(&codigoProd,sizeof(int),1,produtos);
          fwrite(&qtd_min,sizeof(int),1,produtos);
          fwrite(&qtd_atual,sizeof(int),1,produtos);
          fwrite(&vendas_dia,sizeof(int),1,produtos);
          fwrite(&total,sizeof(int),1,produtos);
          fwrite(&preco,sizeof(float),1,produtos);
          fwrite(&total_pesquisa,sizeof(float),1,produtos);
          fwrite(&controle,sizeof(int),1,produtos);
    fclose(produtos);
    
    produtos=fopen("produtos_database.dat","wb");
          fwrite(nomeProd,sizeof(nomeProd),1,produtos);
          fwrite(categoria,sizeof(categoria),1,produtos);
          fwrite(&codigoProd,sizeof(int),1,produtos);
          fwrite(&qtd_min,sizeof(int),1,produtos);
          fwrite(&qtd_atual,sizeof(int),1,produtos);
          fwrite(&vendas_dia,sizeof(int),1,produtos);
          fwrite(&total,sizeof(int),1,produtos);
          fwrite(&preco,sizeof(float),1,produtos);
          fwrite(&total_pesquisa,sizeof(float),1,produtos);
          fwrite(&controle,sizeof(int),1,produtos);
    fclose(produtos);
    
    FILE *clientes=fopen("clientes.dat","wb");
                           fwrite(nome,sizeof(nome),1,clientes);
                           fwrite(&codigo,sizeof(int),1,clientes);
                           fwrite(&gastos_pesquisa,sizeof(float),1,clientes);
                           fwrite(&controle,sizeof(int),1,clientes);
    fclose(clientes);
    
    FILE *datas=fopen("datas.dat","wb");
    fwrite(&data,sizeof(data),1,datas);
    fclose(datas);
    
    FILE *compras=fopen("qtd_compras.dat","wb");
    fwrite(&controle2,sizeof(int),1,compras);
    fclose(compras);
    
    FILE *dados_caixas=fopen("caixas.dat","wb");
    int w=1;
    for(w=1;w<=5;w++){
                     fwrite(&controle2,sizeof(int),1,dados_caixas);
                     fwrite(&controle3,sizeof(float),1,dados_caixas);
                     fwrite(&controle2,sizeof(int),1,dados_caixas);
                     fwrite(&controle2,sizeof(int),1,dados_caixas);
    }
    fclose(dados_caixas);
    return(0);
}
