//Programa Doadores de Sangue
//Programador: Marco Aur�lio Macei Duarte
//Data: 05/10/2015 - vers�o 0.1
//Licen�a do Software
/*
Este programa � um software livre; voc� pode redistribu�-lo e/ou modific�-lo dentro dos termos da Licen�a P�blica Geral GNU 
como publicada pela Funda��o do Software Livre (FSF); na vers�o 3 da Licen�a, ou (na sua opini�o) qualquer vers�o.
Este programa � distribu�do na esperan�a de que possa ser �til, mas SEM NENHUMA GARANTIA; 
sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO ou APLICA��O EM PARTICULAR. 
Veja a Licen�a P�blica Geral GNU para maiores detalhes.
Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU junto com este programa. 
Se n�o, veja http://www.gnu.org/licenses/.
*/
//
//Biblioteca
#include "Doador.h"
//
//Entry Point do Programa
//
void main(void)
{
	ACENTUACAO;

	//Declara��o de vari�veis locais
	int i;												//Contador e �ndice gen�rico

	char cOpcaoOper,									//Local para receber a op��o escolhida do menu
		cTempRG[EXTENSAO_RG + 1],						//Recebe temporariamente o RG do doador
		cWork[200],										//Para o sprintf
		szNomeAluno[] = "Marco Aur�lio Macei Duarte";	//Nome do aluno

	bool flagConsList = false;							//True - indica que foi listado um registro
														//False - indica que n�o foi listado nenhum registro

	DOADOR stDoador;									//Struct para conter os dados dos doadores

	QTDE_DOADORES stQuantidade;							//Struct para conter a quantidade de doadores

	FILE *fdDoador,										//File descriptor para o arquivo dos doadores
		*fdQuantidade;									//File descriptor para o arquivo de quantidade

	SYSTEMTIME stTime;									//Para buscar data e hora

														//Comandos para estabelecer o numero de casas decimais
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);						//Duas casas decimais


	//Abrir o arquivo de doadores em modo "r+b" (precisa existir)
	fopen_s(&fdDoador, CAMINHO_DOADOR, "r+b");

	if (fdDoador == NULL)					//Arquivo n�o existe?
	{
		//Arquivo n�o existe
		//Abrir o arquivo de Qtde_doadores em modo wb - grava��o
		fopen_s(&fdQuantidade, CAMINHO_QUANTIDADE, "wb");

		if (fdQuantidade == NULL)				//Erro de abertura?
		{
			//Erro de leitura, abortar programa
			cout << "\tErro. N�o foi poss�vel abrir o arquivo de quantidade!" << endl << endl;
			PAUSA;						//Pausa o programa
			return;						//Retorna ao Sistema Operacional
		}//Fim do if - erro de abertura

		 //Arquivo de QTDE aberto com sucesso
		 //Loop para pedir a qtde de Doadores
		do
		{
			LIMPAR_TELA;
			cout << "Digite a quantidade de doadores entre " << 1
				<< " e " << MAXIMO_DOADORES << " ou 0 para sair: ";				//Pedir quantidade de doadores
			cin >> stQuantidade.nQtdeDoadores;					//Recebendo a qtde de doadores

			if (stQuantidade.nQtdeDoadores == 0)				//Deseja sair?				
				return;						//Retorna ao Sistema Operacional

		} while (stQuantidade.nQtdeDoadores < 1 || stQuantidade.nQtdeDoadores > MAXIMO_DOADORES);

		//Gravando o arquivo de QUANTIDADE
		//Depois de inicializ�-lo, grav�-lo
		if (fwrite(&stQuantidade, SIZE_QUANTIDADE, 1, fdQuantidade) == 0)		//Erro de grava��o?
		{
			//Erro de grava��o
			fclose(fdQuantidade);		//Fechando o arquivo
			cout << "\tErro. N�o foi poss�vel gravar o arquivo de quantidade!" << endl << endl;
			PAUSA;						//Pausa o programa
			return;						//Retorna ao Sistema Operacional
		}//Fim do if de grava��o

		 //Arquivo de QUANTIDADE criado, gravado e agora ser� fechado
		fclose(fdQuantidade);

		//Agora, criar o arquivo de DOADORES
		//Abrir o arquivo de doadores em modo "w+b" grava��o/leitura
		fopen_s(&fdDoador, CAMINHO_DOADOR, "w+b");

		//Erro de abertura
		if (fdDoador == NULL)			//Erro de abertura?
		{
			//Erro de leitura, abortar programa
			cout << "\tErro. N�o foi poss�vel abrir o arquivo de Doadores!" << endl << endl;
			PAUSA;						//Pausa o programa
			return;						//Retorna ao Sistema Operacional

		}//Fim do if erro de abertura

		 //N�o houve erro de abertura
		 //Fazer inicializa��es

		 //Inicializando a situa��o do cadastro e �ndices
		for (i = 0; i < stQuantidade.nQtdeDoadores; i++)
		{
			stDoador.cadAtivoInativo = false;			//Inicializando a vari�vel como cadastro inativo
														//False - inativo, True - ativo
			stDoador.iIndice = 0;						//Iniciando todos os �ndices com zero

														//Depois de inicializ�-los, grav�-los
			if (fwrite(&stDoador, SIZE_DOADORES, 1, fdDoador) == 0)		//Erro de grava��o?
			{
				//Erro de grava��o
				fclose(fdDoador);			//Fechando o arquivo
				cout << "\tErro. N�o foi poss�vel gravar o arquivo de Doadores!" << endl << endl;
				PAUSA;						//Pausa o programa
				return;						//Retorna ao Sistema Operacional
			}//Fim do if de grava��o
		}//Fim do for da inicializa��o
	}//Fim do if de inicializa��o

	 //Arquivo de DOADORES existe
	 //Abrir arquivo de QUANTIDADE em modo leitura
	fopen_s(&fdQuantidade, CAMINHO_QUANTIDADE, "rb");

	//Lendo os dados do arquivo QUANTIDADES
	if (fread(&stQuantidade, SIZE_QUANTIDADE, 1, fdQuantidade) == 0)			//Erro de leitura?
	{
		//Erro de Leitura
		fclose(fdQuantidade);			//Fechando o arquivo
		cout << "\tErro. N�o foi poss�vel ler o arquivo de quantidade!" << endl << endl;
		PAUSA;							//Pausa o programa
		return;							//Retorna ao Sistema Operacional
	}//Fim do if de leitura

	//Arquivo de Doadores existente, arquivo de quantidade lido e fechado
	fclose(fdQuantidade);					//Fechar arquivo de QUANTIDADES

	while (true)						//Loop infinito
	{
		LIMPAR_TELA;

		GetLocalTime(&stTime);				//Recebendo data e hora do sistema

											//Mostrar o menu de op��es para o operador
		sprintf_s(cWork, sizeof(cWork),
			"\n\tFATEC-MC - Sistema de Doadores de Sangue %02d/%02d/%04d %02d:%02d:%02d\n\tOperador: %s \n",
			stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute, stTime.wSecond, szNomeAluno);

		//Exibindo cabe�alho
		cout << cWork << endl << endl;

		//Menu de op��es
		cout << CADASTRAR_DOADOR << " - Cadastrar um doador" << endl
			<< CONSULTAR_DOADOR << " - Consultar o cadastro de um doador" << endl
			<< EXCLUIR_DOADOR << " - Excluir o cadastro de um doador" << endl
			<< LISTAR_DOADORES << " - Listar todos os doadores" << endl
			<< LISTAR_MELHORES_DOADORES << " - Listar os melhores doadores" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do sistema" << endl
			<< "Selecione: ";
		cin >> cOpcaoOper;						//Op��o escolhida pelo operador

		cOpcaoOper = toupper(cOpcaoOper);		//Convertendo para mai�sculo a op��o escolhida

		switch (cOpcaoOper)			//Avaliar a op��o escolhida pelo operador
		{
		case CADASTRAR_DOADOR:

			//Pedir o RG para verificar se j� existe algum cadastro com esse RG
			cin.ignore(1, EOF);
			cout << "\nInforme o RG do doador (Ex. 99999999-9): ";
			cin.getline(cTempRG, EXTENSAO_RG + 1, '\n');			//Recebendo o RG

			//Chamar a fun��o para posicionar no arquivo de doador
			if (!PosicionarDoador(0, fdDoador))
				break;								//Se der erro de posicionamento

			//Posicionado no �nicio do arquivo
			//Loop de verifica��o
			for (i = 0; i < stQuantidade.nQtdeDoadores; i++)			//Percorre todos os registros
			{
				if (!LerDoador(&fdDoador, &stDoador))				//Cadastro existente?
				{
					//Sim. Verificar o RG
					if (strcmp(cTempRG, stDoador.cRG) == 0)			//Mesmo RG?
					{
						//Se j� tem o cadastro com mesmo RG mostrar ao operador
						sprintf_s(cWork, sizeof(cWork),
							"RG: %s \nNome: %s \nIdade: %d \nSexo: %c \nTipo Sangu�neo: %s \nFator RH: %c \nPeso: %.2f",
							stDoador.cRG, stDoador.cNome, stDoador.nIdade, stDoador.cSexo, stDoador.cTipoSanguineo,
							stDoador.cFatorRH, stDoador.dPeso);

						cout << endl << "Doador j� cadastrado!"
							<< endl << endl << cWork << endl << endl;
						PAUSA;
						break;						//Retorna ao menu
					}//Fim do if de verifica��o do RG
				}
				else
				{
					//Ainda n�o cadastrado, receber os dados do doador
					//Atribuir o RG informado para o cadastro do doador
					strcpy_s(stDoador.cRG, cTempRG);					//Copiando o RG informado para o cadastro

					//Recebendo o �ndice do cadastro
					stDoador.iIndice = i;

					//Receber o nome
					cout << "Informe o nome completo do doador: ";
					cin.getline(stDoador.cNome, EXTENSAO_NOME + 1, '\n');

					for (i = 0; i < sizeof(stDoador.cNome); i++)
						stDoador.cNome[i] = toupper(stDoador.cNome[i]);	//Convertendo todos os caracteres em mai�sculo

					//Receber a idade
					do
					{
						cout << "Informe a idade: ";
						cin >> stDoador.nIdade;
						//Pedir idade enquanto for menor que a idade m�nima ou maior que a m�xima
					} while (stDoador.nIdade < IDADE_MINIMA || stDoador.nIdade > IDADE_MAXIMA);

					//Receber o sexo
					do
					{
						cout << "Informe o sexo (M - Masculino ou F - Feminino): ";
						cin >> stDoador.cSexo;

						stDoador.cSexo = toupper(stDoador.cSexo);				//Convertendo o que foi informado para mai�sculo

					//Pedir sexo enquanto for diferente de M e de F
					} while (stDoador.cSexo != MASCULINO && stDoador.cSexo != FEMININO);

					//Receber o tipo sangu�neo
					do
					{
						cin.ignore(1, EOF);
						cout << "Informe o tipo sangu�neo (A, B, AB ou O): ";
						cin.getline(stDoador.cTipoSanguineo, EXTENSAO_TIPO + 1, '\n');

						for (i = 0; i < sizeof(stDoador.cTipoSanguineo); i++)
							stDoador.cTipoSanguineo[i] = toupper(stDoador.cTipoSanguineo[i]);	//Convertendo para mai�sculo

					//Enquanto o tipo for diferente de A, B, AB e O, pedir novamente
					//Strcmp para comparar Strings
					} while (strcmp(stDoador.cTipoSanguineo, TIPO_A) != 0 && strcmp(stDoador.cTipoSanguineo, TIPO_AB) != 0 &&
						strcmp(stDoador.cTipoSanguineo, TIPO_B) != 0 && strcmp(stDoador.cTipoSanguineo, TIPO_O) != 0);

					//Receber o fator RH
					do
					{
						cout << "Informe o fator RH (+ ou -): ";
						cin >> stDoador.cFatorRH;
					//Pedir fator Rh enquanto for diferente de + (positivo) e de - (negativo)
					} while (stDoador.cFatorRH != RH_POSITIVO && stDoador.cFatorRH != RH_NEGATIVO);

					//Receber o peso
					do
					{
						cout << "Informe o peso: ";
						cin >> stDoador.dPeso;
					} while (stDoador.dPeso < PESO_MINMO);

					//Indicando cadastro ativo
					stDoador.cadAtivoInativo = true;

					//Todos os dados recebidos
					//Gravar no arquivo
					if (!GravarDoador(stDoador.iIndice, &fdDoador, &stDoador))
					{
						//Erro de grava��o?
						cout << endl << "\t\tOcorreu um erro durante a grava��o!" << endl << endl;
						PAUSA;								//Pausa o programa
						break;								//Voltar ao menu
					}//Fim do if de grava��o

					//N�o houve erro de grava��o
					//Cadastro do doador realizado
					cout << endl << "\t\tDoador cadastrado com sucesso!" << endl << endl;
					PAUSA;								//Pausa o programa
					break;								//Voltar ao menu

				}//Fim do if
			}//Fim do for

			break;								//Voltar ao menu

		case CONSULTAR_DOADOR:

			//Consultar o cadastro pelo n�mero de RG informado
			//Pedir o RG para verificar se j� existe algum cadastro com esse RG
			cin.ignore(1, EOF);
			cout << "\nInforme o RG do doador (Ex. 99999999-9): ";
			cin.getline(cTempRG, EXTENSAO_RG + 1, '\n');				//Recebendo o RG

			//Chamar a fun��o para posicionar no arquivo de doador
			if (!PosicionarDoador(0, fdDoador))
				break;								//Se der erro de posicionamento

			for (i = 0, flagConsList = false; i < stQuantidade.nQtdeDoadores; i++)		//Percorrendo todo o arquivo
			{
				if (!LerDoador(&fdDoador, &stDoador)					//Cadastro existente?
					&& strcmp(cTempRG, stDoador.cRG) == 0)				//Mesmo RG?	
				{
					flagConsList = true;					//Para indicar que exibiu um cadastro v�lido

					//Se j� tem o cadastro com mesmo RG mostrar ao operador
					sprintf_s(cWork, sizeof(cWork),
						"RG: %s \nNome: %s \nIdade: %d \nSexo: %c \nTipo Sangu�neo: %s \nFator RH: %c \nPeso: %.2f",
						stDoador.cRG, stDoador.cNome, stDoador.nIdade, stDoador.cSexo, stDoador.cTipoSanguineo,
						stDoador.cFatorRH, stDoador.dPeso);

					cout << endl << endl << cWork << endl << endl;			//Exibir cWork
					PAUSA;
					break;						//Retorna ao menu
				}//Fim do if que verifica a existe�ncia do cadastro do RG informado
			}//Fim do for que percorre o arquivo

			if (!flagConsList)					//Se continuou como false � porque n�o houve exibi��o de um registro
			{
				//Aqui � avisado de que n�o existe nenhum registro com o RG informado
				cout << endl << "\t\tN�o h� nenhum registro com o RG informado!" << endl << endl;
				PAUSA;
			}//Fim do if

			break;					//Volta ao menu

		case EXCLUIR_DOADOR:

			//Consultar o cadastro pelo n�mero de RG informado
			//Pedir o RG para verificar se j� existe algum cadastro com esse RG
			cin.ignore(1, EOF);
			cout << "\nInforme o RG do doador (Ex. 99999999-9): ";
			cin.getline(cTempRG, EXTENSAO_RG, '\n');			//Recebendo o RG

			//Chamar a fun��o para posicionar no arquivo de doador
			if (!PosicionarDoador(0, fdDoador))
				break;								//Se der erro de posicionamento

			for (i = 0, flagConsList = false; i < stQuantidade.nQtdeDoadores; i++)		//Percorrendo todo o arquivo
			{
				if (!LerDoador(&fdDoador, &stDoador)					//Cadastro existente?
					&& strcmp(cTempRG, stDoador.cRG) == 0)				//Mesmo RG?	
				{
					flagConsList = true;					//Para indicar que exibiu um cadastro v�lido

					//Se j� tem o cadastro com mesmo RG mostrar ao operador
					sprintf_s(cWork, sizeof(cWork),
						"RG: %s \nNome: %s \nIdade: %d \nSexo: %c \nTipo Sangu�neo: %s \nFator RH: %c \nPeso: %.2f",
						stDoador.cRG, stDoador.cNome, stDoador.nIdade, stDoador.cSexo, stDoador.cTipoSanguineo,
						stDoador.cFatorRH, stDoador.dPeso);

					cout << endl << endl << cWork << endl << endl;			//Exibir cWork
					PAUSA;								//Pausa o programa

					//Perguntar se quer excluir
					cout << endl << endl << "\tDeseja realmente excluir este registro? (S - Sim ou N - N�o): ";
					cin >> cOpcaoOper;				//Recebendo a op��o do operador

					if (cOpcaoOper == 'S' || cOpcaoOper == 's')
					{
						cout << endl << endl << "\t\t\tRegistro exclu�do com sucesso!" << endl << endl;
						stDoador.cadAtivoInativo = false;				//Indica que foi exclu�do
						PAUSA;

						//Gravar no arquivo
						if (!GravarDoador(stDoador.iIndice, &fdDoador, &stDoador))
						{
							//Erro de grava��o?
							cout << endl << "\t\tOcorreu um erro durante a grava��o!" << endl << endl;

							PAUSA;								//Pausa o programa
							break;								//Voltar ao menu
						}//Fim do if de grava��o
					break;					//Volta ao menu
					}//Fim do if de exclus�o

					//Se desistiu de excluir
					cout << endl << endl << "\t\t\tOpera��o Cancelada!" << endl << endl;
					PAUSA;
					break;					//Volta ao menu
				}//Fim do if que verifica a exist�ncia do cadastro do RG informado
			}//Fim do for que percorre o arquivo

			if (!flagConsList)					//Se continuou como false � porque n�o houve exibi��o de um registro
			{
				//Aqui � avisado de que n�o existe nenhum registro com o RG informado
				cout << endl << "\t\tN�o h� nenhum registro com o RG informado!" << endl << endl;
				PAUSA;
			}//Fim do if

			break;					//Volta ao menu

		case LISTAR_DOADORES:

			//Chamar a fun��o para posicionar no arquivo de doador
			if (!PosicionarDoador(0, fdDoador))
				break;								//Se der erro de posicionamento

			//Percorrer o arquivo e exibir todos os que est�o ativos
			for (i = 0, flagConsList = false; i < stQuantidade.nQtdeDoadores; i++)			//Percorrendo todo o arquivo
			{
				if (!LerDoador(&fdDoador, &stDoador))					//Cadastro existente?
				{
					flagConsList = true;					//Para indicar que exibiu um cadastro v�lido

					//Se cadastro ativo exibi-lo
					sprintf_s(cWork, sizeof(cWork),
						"RG: %s \nNome: %s \nIdade: %d \nSexo: %c \nTipo Sangu�neo: %s \nFator RH: %c \nPeso: %.2f",
						stDoador.cRG, stDoador.cNome, stDoador.nIdade, stDoador.cSexo, stDoador.cTipoSanguineo,
						stDoador.cFatorRH, stDoador.dPeso);

					cout << endl << endl << cWork << endl << endl;			//Exibir cWork
				}//Fim do if de exibi��o de cadastro ativo
			}//Fim do for que percorre o arquivo

			if (!flagConsList)					//Se continuou como false � porque n�o houve exibi��o de um registro
				//Aqui � avisado de que n�o existe nenhum registro com o RG informado
				cout << endl << "\t\t\tN�o h� nenhum registro no arquivo!" << endl << endl;

			PAUSA;
			break;					//Volta ao menu

		case LISTAR_MELHORES_DOADORES:

			//Listar os melhores doadores que tenham o tipo sangu�neo O, fator RH - (negativo)
			//Tenham idade compreendida entre 21 e 55 anos e pesem mais de 55 Kgs
			//Chamar a fun��o para posicionar no arquivo de doador
			if (!PosicionarDoador(0, fdDoador))
				break;								//Se der erro de posicionamento

			//Percorrer o arquivo e exibir todos os que est�o ativos
			for (i = 0, flagConsList = false; i < stQuantidade.nQtdeDoadores; i++)
			{
				if (!LerDoador(&fdDoador, &stDoador)					//Cadastro existente?
					&& strcmp(stDoador.cTipoSanguineo, TIPO_O) == 0 && stDoador.cFatorRH == '-'
					&& (stDoador.nIdade > 20 && stDoador.nIdade < 56) && stDoador.dPeso > 55.00)		//Condi��es satisfeitas
				{
					flagConsList = true;					//Para indicar que exibiu um cadastro v�lido

					//Se cadastro ativo exibi-lo
					sprintf_s(cWork, sizeof(cWork),
						"RG: %s \nNome: %s \nIdade: %d \nSexo: %c \nTipo Sangu�neo: %s \nFator RH: %c \nPeso: %.2f",
						stDoador.cRG, stDoador.cNome, stDoador.nIdade, stDoador.cSexo, stDoador.cTipoSanguineo,
						stDoador.cFatorRH, stDoador.dPeso);

					cout << endl << endl << cWork << endl << endl;			//Exibir cWork
				}//Fim do if de exibi��o de cadastro ativo
			}//Fim do for que percorre o arquivo

			if (!flagConsList)					//Se continuou como false � porque n�o houve exibi��o de um registro
				//Aqui � avisado de que n�o existe nenhum registro com o RG informado
				cout << endl << "\tN�o h� nenhum registro no arquivo que satisfa�a as condi��es propostas!" << endl << endl;

			PAUSA;
			break;					//Volta ao menu

		case SAIR_DO_PROGRAMA:
			cout << "\n\t\t\tDeseja realmente sair? (S ou N): ";
			cin >> cOpcaoOper;			//Op��o do operador

			if (cOpcaoOper == 's' || cOpcaoOper == 'S')			//Sair realmente?
			{	//Vai sair
				fclose(fdDoador);								//Fechar o arquivo de Doadores
				return;											//Volta ao Sistema Operacional
			}//Fim do if

			 //Sen�o, retorna ao menu
			break;					//Volta ao menu

		default:
			cout << endl << "\t\t\tOp��o inv�lida!" << endl << endl;
			PAUSA;
		}//Fim do switch...case
	}//Fim do loop while
}//Fim da main