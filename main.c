#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <direct.h>


int opcao;

FILE *arq_pacientes;
FILE *arq_pacientesc;

void main(){

   setlocale(LC_ALL, "Portuguese");
   system("color 3F");

    char usuario[20], scanUsuario[20];
    char senha[20], scanSenha[20];

    strcpy(usuario,"admin");
    strcpy(senha,"covid19");

    bool usuariosIguais = false;
    bool senhasIguais = false;

    do{
        printInfoBase();

        printf("\nBEM VINDO, DIGITE O USUARIO:");
        scanf("%s",scanUsuario);

        printInfoBase();
        printf("\nDIGITE A SENHA:");
        scanf ("%s",scanSenha);

        usuariosIguais = strcmp(usuario,scanUsuario) == 0;
        senhasIguais = strcmp(senha, scanSenha) == 0;

        if (!usuariosIguais || !senhasIguais){
            printInfoBase();
            printf("\n\n\n\tÚsuario e/ou senha incorretos\n");
            getch();
        }

    } while(!usuariosIguais || !senhasIguais);

    printInfoBase();
    printf("\n**LOGIN APROVADO**\n");
    getch();

    char nome[50], cpf[50], endereco_rua[50], endereco_numero[50], endereco_bairro[50], endereco_cep[50],telefone[50], strIdade[4],dataDiagnostico[50],comorbidades[50];
    int idade, nitems,opcaoComorbidade;





    do
	{
	    printInfoBase();
        printf("\n** SISTEMA PARA CADASTRO DE PACIENTES POSITIVOS PARA COVID-19 **\n");
        printf("\n** 1-Cadastrar novo paciente **\n");
        printf("\n** 2-Listar pacientes fora do grupo de risco **\n");
        printf("\n** 3-Listar pacientes considerados de risco **\n");
        printf("\n** 0-Sair **\n");
        scanf("%d", &opcao);
        fflush(stdin);

        switch(opcao){
            case 0:;
                printInfoBase();
                printf("Muito obrigado pela preferência.");
                getch();
                break;
            case 1:;
                bool continuaValido = true;

                struct tm *data_hora_atual;
                time_t segundos;
                time(&segundos);
                data_hora_atual = localtime(&segundos);
                data_hora_atual = localtime(&segundos);
                int diaA = data_hora_atual->tm_mday;
                int mesA = data_hora_atual->tm_mon+1; //mês
                int anoA = data_hora_atual->tm_year+1900; //ano Atual

                printInfoBase();
                arq_pacientes=fopen("pacientes.txt","a");
                printf("\nDigite o nome completo do paciente: ");
                fgets(nome,50,stdin);
                fputs(nome,arq_pacientes);


                if(strlen(nome) == 0){
                    continuaValido = false;
                }

                if (continuaValido){
                    printf("\nDigite o CPF do paciente (xxx.xxx.xxx-xx): ");
                    fgets(cpf,50,stdin);
                    fputs(cpf,arq_pacientes);

                }

                printf("\nDigite o endereco do paciente (Rua): ");
                fgets(endereco_rua,50,stdin);
                printf("\nDigite o endereco do paciente (Numero): ");
                fgets(endereco_numero,50,stdin);
                printf("\nDigite o endereco do paciente (Bairro): ");
                fgets(endereco_bairro,50,stdin);
                printf("\nDigite o endereco do paciente (CEP): ");
                fgets(endereco_cep,50,stdin);
                printf("\nDigite o telefone do paciente (xx-xxxxxxxx): ");
                fgets(telefone,50,stdin);
                printf("\nDigite data de diagnostico na seguinte configuracao: dd/mm/aaaa\n");
                fgets(dataDiagnostico,50,stdin);


                int diaN, mesN, anoN, idade;

                printf("\nInforme a sua data de nascimento na seguinte configuracao: dd/mm/aaaa\n");
                scanf("%d/%d/%d", &diaN, &mesN, &anoN);

                if ((mesN > mesA) || ((mesN = mesA) && (diaN > diaA))){
                   idade = anoA - anoN ;
                   printf("Paciente tem %d", idade);
                }
                else {
                    idade = anoA - anoN;
                    printf("Paciente tem %d", idade);
                }


                printf("\nVocê tem algum comorbidade(Sim 1/Nao 2): ");
                scanf("%d",&opcaoComorbidade);

                if(opcaoComorbidade == 1) {
                    printf("\nInforme a Comorbidade: ");
                    scanf(" %[^\n]s",&comorbidades);
                }

                if((opcaoComorbidade == 1)||(idade >= 65)){
                   arq_pacientesc=fopen("pacientescomorb.txt","a");
                   fprintf(arq_pacientesc,"Nome: %s",nome);
                   fprintf(arq_pacientesc,"CPF: %s",cpf);
                   fprintf(arq_pacientesc,"CEP: %s",endereco_cep);
                   fprintf(arq_pacientesc,"Telefone: %s",telefone);
                   fprintf(arq_pacientesc,"Idade: %d\n",idade);
                   fprintf(arq_pacientesc,"Comorbidade: %s \n\n",comorbidades);


                    fclose(arq_pacientesc);

                    printInfoBase();
                    printf("\nPaciente Cadastrado com Sucesso");
                    getch();
                }
                else if ((opcaoComorbidade == 2)||(idade < 65)){
                   arq_pacientes=fopen("pacientes.txt","a");
                   fprintf(arq_pacientes,"Nome: %s",nome);
                   fprintf(arq_pacientes,"CPF: %s",cpf);
                   fprintf(arq_pacientes,"CEP: %s",endereco_cep);
                   fprintf(arq_pacientes,"Telefone: %s",telefone);
                   fprintf(arq_pacientes,"Idade: %d\n",idade);
                   fclose(arq_pacientes);

                    printInfoBase();
                    printf("\nPaciente Cadastrado com Sucesso");
                    getch();
                } else {
                     printInfoBase();
                    printf("\nHouve uma falha durante o cadastro.");
                    getch();
                }

                break;

            case 2:;
                printInfoBase();

                char ch;
                arq_pacientes = fopen("pacientes.txt", "r");
                if(arq_pacientes == NULL)
                {   printInfoBase();
                    /* Unable to open file hence exit */
                    printf("Não foi possível abrir o arquivo.\n");
                    printf("Por favor verifique as permissões de acesso ou se os arquivos existem.\n");
                    exit(EXIT_FAILURE);
                } else do {
                   ch = fgetc(arq_pacientes);
                    putchar(ch);


                } while(ch != EOF); /* Repeat this if last read character is not EOF */

                fclose(arq_pacientes);


                printf("\n\n\n************************************************************************************************");
                printf("\nFim da lista de pacientes.");
                getch();
                break;


              case 3:;
                printInfoBase();

                char ch1;
                arq_pacientesc = fopen("pacientescomorb.txt", "r");
                if(arq_pacientesc == NULL)
                {   printInfoBase();
                    /* Unable to open file hence exit */
                    printf("Não foi possível abrir o arquivo.\n");
                    printf("Por favor verifique as permissões de acesso ou se os arquivos existem.\n");
                    exit(EXIT_FAILURE);
                } else do {
                   ch1 = fgetc(arq_pacientesc);
                    putchar(ch1);


                } while(ch1 != EOF); /* Repeat this if last read character is not EOF */

                fclose(arq_pacientesc);


                printf("\n\n\n************************************************************************************************");
                printf("\nFim da lista de pacientes de risco.");
                getch();
                break;

            default:;
                printInfoBase();
                printf("Opção inválida\n");
                getch();
                break;
            }
    } while(opcao !=0);

    system('cls');
}

void printInfoBase(){
    system("cls");
    struct tm *data_hora_atual;
    time_t segundos;
    time(&segundos);
    data_hora_atual = localtime(&segundos);
    printf("\nHora ........: %d:",data_hora_atual->tm_hour);//hora
    printf("%d:",data_hora_atual->tm_min);//minuto
    printf("%d\n",data_hora_atual->tm_sec);//segundo
    printf("\nData ........: %d/", data_hora_atual->tm_mday);
    printf("%d/",data_hora_atual->tm_mon+1); //mês
    printf("%d\n\n",data_hora_atual->tm_year+1900); //ano

    printf("\n************************************************************");
    printf("\n****************GERENCIAMENTO PACIENTE COVID****************");
    printf("\n************************************************************\n\n");

    return segundos;
}
