//Programa Doadores de Sangue
//Programador: Marco Aurélio Macei Duarte
//Data: 05/10/2015 - versão 0.1
//Licença do Software
/*
Este programa é um software livre; você pode redistribuí-lo e/ou modificá-lo dentro dos termos da Licença Pública Geral GNU 
como publicada pela Fundação do Software Livre (FSF); na versão 3 da Licença, ou (na sua opinião) qualquer versão.
Este programa é distribuído na esperança de que possa ser útil, mas SEM NENHUMA GARANTIA; 
sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO EM PARTICULAR. 
Veja a Licença Pública Geral GNU para maiores detalhes.
Você deve ter recebido uma cópia da Licença Pública Geral GNU junto com este programa. 
Se não, veja http://www.gnu.org/licenses/.
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

	//Declaração de variáveis locais
	int i;												//Contador e índice genérico

	char cOpcaoOper,									//Local para receber a opção escolhida do menu
		cTempRG[EXTENSAO_RG + 1],						//Recebe temporariamente o RG do doador
		cWork[200],										//Para o sprintf
		szNomeAluno[] = "Marco Aurélio Macei Duarte";	//Nome do aluno

	bool flagConsList = false;							//True - indica que foi listado um registro
														//False - indica que não foi listado nenhum registro

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

	if (fdDoador == NULL)					//Arquivo não existe?
	{
		//Arquivo não existe
		//Abrir o arquivo de Qtde_doadores em modo wb - gravação
		fopen_s(&fdQuantidade, CAMINHO_QUANTIDADE, "wb");

		if (fdQuantidade == NULL)				//Erro de abertura?
		{
			//Erro de leitura, abortar programa
			cout << "\tErro. Não foi possível abrir o arquivo de quantidade!" << endl << endl;
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
		//Depois de inicializá-lo, gravá-lo
		if (fwrite(&stQuantidade, SIZE_QUANTIDADE, 1, fdQuantidade) == 0)		//Erro de gravação?
		{
			//Erro de gravação
			fclose(fdQuantidade);		//Fechando o arquivo
			cout << "\tErro. Não foi possível gravar o arquivo de quantidade!" << endl << endl;
			PAUSA;						//Pausa o programa
			return;						//Retorna ao Sistema Operacional
		}//Fim do if de gravação

		 //Arquivo de QUANTIDADE criado, gravado e agora será fechado
		fclose(fdQuantidade);

		//Agora, criar o arquivo de DOADORES
		//Abrir o arquivo de doadores em modo "w+b" gravação/leitura
		fopen_s(&fdDoador, CAMINHO_DOADOR, "w+b");

		//Erro de abertura
		if (fdDoador == NULL)			//Erro de abertura?
		{
			//Erro de leitura, abortar programa
			cout << "\tErro. Não foi possível abrir o arquivo de Doadores!" << endl << endl;
			PAUSA;						//Pausa o programa
			return;						//Retorna ao Sistema Operacional

		}//Fim do if erro de abertura

		 //Não houve erro de abertura
		 //Fazer inicializações

		 //Inicializando a situação do cadastro e índices
		for (i = 0; i < stQuantidade.nQtdeDoadores; i++)
		{
			stDoador.cadAtivoInativo = false;			//Inicializando a variável como cadastro inativo
														//False - inativo, True - ativo
			stDoador.iIndice = 0;						//Iniciando todos os índices com zero

														//Depois de inicializá-los, gravá-los
			if (fwrite(&stDoador, SIZE_DOADORES, 1, fdDoador) == 0)		//Erro de gravação?
			{
				//Erro de gravação
				fclose(fdDoador);			//Fechando o arquivo
				cout << "\tErro. Não foi possível gravar o arquivo de Doadores!" << endl << endl;
				PAUSA;						//Pausa o programa
				return;						//Retorna ao Sistema Operacional
			}//Fim do if de gravação
		}//Fim do for da inicialização
	}//Fim do if de inicialização

	 //Arquivo de DOADORES existe
	 //Abrir arquivo de QUANTIDADE em modo leitura
	fopen_s(&fdQuantidade, CAMINHO_QUANTIDADE, "rb");

	//Lendo os dados do arquivo QUANTIDADES
	if (fread(&stQuantidade, SIZE_QUANTIDADE, 1, fdQuantidade) == 0)			//Erro de leitura?
	{
		//Erro de Leitura
		fclose(fdQuantidade);			//Fechando o arquivo
		cout << "\tErro. Não foi possível ler o arquivo de quantidade!" << endl << endl;
		PAUSA;							//Pausa o programa
		return;							//Retorna ao Sistema Operacional
	}//Fim do if de leitura

	//Arquivo de Doadores existente, arquivo de quantidade lido e fechado
	fclose(fdQuantidade);					//Fechar arquivo de QUANTIDADES

	while (true)						//Loop infinito
	{
		LIMPAR_TELA;

		GetLocalTime(&stTime);				//Recebendo data e hora do sistema

											//Mostrar o menu de opções para o operador
		sprintf_s(cWork, sizeof(cWork),
			"\n\tFATEC-MC - Sistema de Doadores de Sangue %02d/%02d/%04d %02d:%02d:%02d\n\tOperador: %s \n",
			stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute, stTime.wSecond, szNomeAluno);

		//Exibindo cabeçalho
		cout << cWork << endl << endl;

		//Menu de opções
		cout << CADASTRAR_DOADOR << " - Cadastrar um doador" << endl
			<< CONSULTAR_DOADOR << " - Consultar o cadastro de um doador" << endl
			<< EXCLUIR_DOADOR << " - Excluir o cadastro de um doador" << endl
			<< LISTAR_DOADORES << " - Listar todos os doadores" << endl
			<< LISTAR_MELHORES_DOADORES << " - Listar os melhores doadores" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do sistema" << endl
			<< "Selecione: ";
		cin >> cOpcaoOper;						//Opção escolhida pelo operador

		cOpcaoOper = toupper(cOpcaoOper);		//Convertendo para maiúsculo a opção escolhida

		switch (cOpcaoOper)			//Avaliar a opção escolhida pelo operador
		{
		case CADASTRAR_DOADOR:

			//Pedir o RG para verificar se já existe algum cadastro com esse RG
			cin.ignore(1, EOF);
			cout << "\nInforme o RG do doador (Ex. 99999999-9): ";
			cin.getline(cTempRG, EXTENSAO_RG + 1, '\n');			//Recebendo o RG

			//Chamar a função para posicionar no arquivo de doador
			if (!PosicionarDoador(0, fdDoador))
				break;								//Se der erro de posicionamento

			//Posicionado no ínicio do arquivo
			//Loop de verificação
			for (i = 0; i < stQuantidade.nQtdeDoadores; i++)			//Percorre todos os registros
			{
				if (!LerDoador(&fdDoador, &stDoador))				//Cadastro existente?
				{
					//Sim. Verificar o RG
					if (strcmp(cTempRG, stDoador.cRG) == 0)			//Mesmo RG?
					{
						//Se já tem o cadastro com mesmo RG mostrar ao operador
						sprintf_s(cWork, sizeof(cWork),
							"RG: %s \nNome: %s \nIdade: %d \nSexo: %c \nTipo Sanguíneo: %s \nFator RH: %c \nPeso: %.2f",
							stDoador.cRG, stDoador.cNome, stDoador.nIdade, stDoador.cSexo, stDoador.cTipoSanguineo,
							stDoador.cFatorRH, stDoador.dPeso);

						cout << endl << "Doador já cadastrado!"
							<< endl << endl << cWork << endl << endl;
						PAUSA;
						break;						//Retorna ao menu
					}//Fim do if de verificação do RG
				}
				else
				{
					//Ainda não cadastrado, receber os dados do doador
					//Atribuir o RG informado para o cadastro do doador
					strcpy_s(stDoador.cRG, cTempRG);					//Copiando o RG informado para o cadastro

					//Recebendo o índice do cadastro
					stDoador.iIndice = i;

					//Receber o nome
					cout << "Informe o nome completo do doador: ";
					cin.getline(stDoador.cNome, EXTENSAO_NOME + 1, '\n');

					for (i = 0; i < sizeof(stDoador.cNome); i++)
						stDoador.cNome[i] = toupper(stDoador.cNome[i]);	//Convertendo todos os caracteres em maiúsculo

					//Receber a idade
					do
					{
						cout << "Informe a idade: ";
						cin >> stDoador.nIdade;
						//Pedir idade enquanto for menor que a idade mínima ou maior que a máxima
					} while (stDoador.nIdade < IDADE_MINIMA || stDoador.nIdade > IDADE_MAXIMA);

					//Receber o sexo
					do
					{
						cout << "Informe o sexo (M - Masculino ou F - Feminino): ";
						cin >> stDoador.cSexo;

						stDoador.cSexo = toupper(stDoador.cSexo);				//Convertendo o que foi informado para maiúsculo

					//Pedir sexo enquanto for diferente de M e de F
					} while (stDoador.cSexo != MASCULINO && stDoador.cSexo != FEMININO);

					//Receber o tipo sanguíneo
					do
					{
						cin.ignore(1, EOF);
						cout << "Informe o tipo sanguíneo (A, B, AB ou O): ";
						cin.getline(stDoador.cTipoSanguineo, EXTENSAO_TIPO + 1, '\n');

						for (i = 0; i < sizeof(stDoador.cTipoSanguineo); i++)
							stDoador.cTipoSanguineo[i] = toupper(stDoador.cTipoSanguineo[i]);	//Convertendo para maiúsculo

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
						//Erro de gravação?
						cout << endl << "\t\tOcorreu um erro durante a gravação!" << endl << endl;
						PAUSA;								//Pausa o programa
						break;								//Voltar ao menu
					}//Fim do if de gravação

					//Não houve erro de gravação
					//Cadastro do doador realizado
					cout << endl << "\t\tDoador cadastrado com sucesso!" << endl << endl;
					PAUSA;								//Pausa o programa
					break;								//Voltar ao menu

				}//Fim do if
			}//Fim do for

			break;								//Voltar ao menu

		case CONSULTAR_DOADOR:

			//Consultar o cadastro pelo número de RG informado
			//Pedir o RG para verificar se já existe algum cadastro com esse RG
			cin.ignore(1, EOF);
			cout << "\nInforme o RG do doador (Ex. 99999999-9): ";
			cin.getline(cTempRG, EXTENSAO_RG + 1, '\n');				//Recebendo o RG

			//Chamar a função para posicionar no arquivo de doador
			if (!PosicionarDoador(0, fdDoador))
				break;								//Se der erro de posicionamento

			for (i = 0, flagConsList = false; i < stQuantidade.nQtdeDoadores; i++)		//Percorrendo todo o arquivo
			{
				if (!LerDoador(&fdDoador, &stDoador)					//Cadastro existente?
					&& strcmp(cTempRG, stDoador.cRG) == 0)				//Mesmo RG?	
				{
					flagConsList = true;					//Para indicar que exibiu um cadastro válido

					//Se já tem o cadastro com mesmo RG mostrar ao operador
					sprintf_s(cWork, sizeof(cWork),
						"RG: %s \nNome: %s \nIdade: %d \nSexo: %c \nTipo Sanguíneo: %s \nFator RH: %c \nPeso: %.2f",
						stDoador.cRG, stDoador.cNome, stDoador.nIdade, stDoador.cSexo, stDoador.cTipoSanguineo,
						stDoador.cFatorRH, stDoador.dPeso);

					cout << endl << endl << cWork << endl << endl;			//Exibir cWork
					PAUSA;
					break;						//Retorna ao menu
				}//Fim do if que verifica a existeância do cadastro do RG informado
			}//Fim do for que percorre o arquivo

			if (!flagConsList)					//Se continuou como false é porque não houve exibição de um registro
			{
				//Aqui é avisado de que não existe nenhum registro com o RG informado
				cout << endl << "\t\tNão há nenhum registro com o RG informado!" << endl << endl;
				PAUSA;
			}//Fim do if

			break;					//Volta ao menu

		case EXCLUIR_DOADOR:

			//Consultar o cadastro pelo número de RG informado
			//Pedir o RG para verificar se já existe algum cadastro com esse RG
			cin.ignore(1, EOF);
			cout << "\nInforme o RG do doador (Ex. 99999999-9): ";
			cin.getline(cTempRG, EXTENSAO_RG, '\n');			//Recebendo o RG

			//Chamar a função para posicionar no arquivo de doador
			if (!PosicionarDoador(0, fdDoador))
				break;								//Se der erro de posicionamento

			for (i = 0, flagConsList = false; i < stQuantidade.nQtdeDoadores; i++)		//Percorrendo todo o arquivo
			{
				if (!LerDoador(&fdDoador, &stDoador)					//Cadastro existente?
					&& strcmp(cTempRG, stDoador.cRG) == 0)				//Mesmo RG?	
				{
					flagConsList = true;					//Para indicar que exibiu um cadastro válido

					//Se já tem o cadastro com mesmo RG mostrar ao operador
					sprintf_s(cWork, sizeof(cWork),
						"RG: %s \nNome: %s \nIdade: %d \nSexo: %c \nTipo Sanguíneo: %s \nFator RH: %c \nPeso: %.2f",
						stDoador.cRG, stDoador.cNome, stDoador.nIdade, stDoador.cSexo, stDoador.cTipoSanguineo,
						stDoador.cFatorRH, stDoador.dPeso);

					cout << endl << endl << cWork << endl << endl;			//Exibir cWork
					PAUSA;								//Pausa o programa

					//Perguntar se quer excluir
					cout << endl << endl << "\tDeseja realmente excluir este registro? (S - Sim ou N - Não): ";
					cin >> cOpcaoOper;				//Recebendo a opção do operador

					if (cOpcaoOper == 'S' || cOpcaoOper == 's')
					{
						cout << endl << endl << "\t\t\tRegistro excluído com sucesso!" << endl << endl;
						stDoador.cadAtivoInativo = false;				//Indica que foi excluído
						PAUSA;

						//Gravar no arquivo
						if (!GravarDoador(stDoador.iIndice, &fdDoador, &stDoador))
						{
							//Erro de gravação?
							cout << endl << "\t\tOcorreu um erro durante a gravação!" << endl << endl;

							PAUSA;								//Pausa o programa
							break;								//Voltar ao menu
						}//Fim do if de gravação
					break;					//Volta ao menu
					}//Fim do if de exclusão

					//Se desistiu de excluir
					cout << endl << endl << "\t\t\tOperação Cancelada!" << endl << endl;
					PAUSA;
					break;					//Volta ao menu
				}//Fim do if que verifica a existência do cadastro do RG informado
			}//Fim do for que percorre o arquivo

			if (!flagConsList)					//Se continuou como false é porque não houve exibição de um registro
			{
				//Aqui é avisado de que não existe nenhum registro com o RG informado
				cout << endl << "\t\tNão há nenhum registro com o RG informado!" << endl << endl;
				PAUSA;
			}//Fim do if

			break;					//Volta ao menu

		case LISTAR_DOADORES:

			//Chamar a função para posicionar no arquivo de doador
			if (!PosicionarDoador(0, fdDoador))
				break;								//Se der erro de posicionamento

			//Percorrer o arquivo e exibir todos os que estão ativos
			for (i = 0, flagConsList = false; i < stQuantidade.nQtdeDoadores; i++)			//Percorrendo todo o arquivo
			{
				if (!LerDoador(&fdDoador, &stDoador))					//Cadastro existente?
				{
					flagConsList = true;					//Para indicar que exibiu um cadastro válido

					//Se cadastro ativo exibi-lo
					sprintf_s(cWork, sizeof(cWork),
						"RG: %s \nNome: %s \nIdade: %d \nSexo: %c \nTipo Sanguíneo: %s \nFator RH: %c \nPeso: %.2f",
						stDoador.cRG, stDoador.cNome, stDoador.nIdade, stDoador.cSexo, stDoador.cTipoSanguineo,
						stDoador.cFatorRH, stDoador.dPeso);

					cout << endl << endl << cWork << endl << endl;			//Exibir cWork
				}//Fim do if de exibição de cadastro ativo
			}//Fim do for que percorre o arquivo

			if (!flagConsList)					//Se continuou como false é porque não houve exibição de um registro
				//Aqui é avisado de que não existe nenhum registro com o RG informado
				cout << endl << "\t\t\tNão há nenhum registro no arquivo!" << endl << endl;

			PAUSA;
			break;					//Volta ao menu

		case LISTAR_MELHORES_DOADORES:

			//Listar os melhores doadores que tenham o tipo sanguíneo O, fator RH - (negativo)
			//Tenham idade compreendida entre 21 e 55 anos e pesem mais de 55 Kgs
			//Chamar a função para posicionar no arquivo de doador
			if (!PosicionarDoador(0, fdDoador))
				break;								//Se der erro de posicionamento

			//Percorrer o arquivo e exibir todos os que estão ativos
			for (i = 0, flagConsList = false; i < stQuantidade.nQtdeDoadores; i++)
			{
				if (!LerDoador(&fdDoador, &stDoador)					//Cadastro existente?
					&& strcmp(stDoador.cTipoSanguineo, TIPO_O) == 0 && stDoador.cFatorRH == '-'
					&& (stDoador.nIdade > 20 && stDoador.nIdade < 56) && stDoador.dPeso > 55.00)		//Condições satisfeitas
				{
					flagConsList = true;					//Para indicar que exibiu um cadastro válido

					//Se cadastro ativo exibi-lo
					sprintf_s(cWork, sizeof(cWork),
						"RG: %s \nNome: %s \nIdade: %d \nSexo: %c \nTipo Sanguíneo: %s \nFator RH: %c \nPeso: %.2f",
						stDoador.cRG, stDoador.cNome, stDoador.nIdade, stDoador.cSexo, stDoador.cTipoSanguineo,
						stDoador.cFatorRH, stDoador.dPeso);

					cout << endl << endl << cWork << endl << endl;			//Exibir cWork
				}//Fim do if de exibição de cadastro ativo
			}//Fim do for que percorre o arquivo

			if (!flagConsList)					//Se continuou como false é porque não houve exibição de um registro
				//Aqui é avisado de que não existe nenhum registro com o RG informado
				cout << endl << "\tNão há nenhum registro no arquivo que satisfaça as condições propostas!" << endl << endl;

			PAUSA;
			break;					//Volta ao menu

		case SAIR_DO_PROGRAMA:
			cout << "\n\t\t\tDeseja realmente sair? (S ou N): ";
			cin >> cOpcaoOper;			//Opção do operador

			if (cOpcaoOper == 's' || cOpcaoOper == 'S')			//Sair realmente?
			{	//Vai sair
				fclose(fdDoador);								//Fechar o arquivo de Doadores
				return;											//Volta ao Sistema Operacional
			}//Fim do if

			 //Senão, retorna ao menu
			break;					//Volta ao menu

		default:
			cout << endl << "\t\t\tOpção inválida!" << endl << endl;
			PAUSA;
		}//Fim do switch...case
	}//Fim do loop while
}//Fim da main