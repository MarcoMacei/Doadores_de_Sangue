//Header File do Programa Doadores de Sangue
//
//Bibliotecas
#include <Windows.h>
#include <iostream>
using namespace std;
//
//Defini��es do Programa
#define	ACENTUACAO						setlocale(LC_ALL, "portuguese_brazil")		//Acentua��o e caracteres especiais PT - BR
#define	LIMPAR_TELA						system("cls")								//Limpa a tela (clear screen)
#define	PAUSA							system("pause")								//Pausa o programa
#define SIZE_DOADORES					sizeof(DOADOR)								//Sizeof da struct DOADOR
#define	SIZE_QUANTIDADE					sizeof(QTDE_DOADORES)						//Sizeof da struct QTDE_DOADORES
//
//Caminho dos arquivos
#define CAMINHO_DOADOR					"..\\Doador.dat"							//Caminho do arquivo doadores
#define CAMINHO_QUANTIDADE				"..\\Quantidades.dat"						//Caminho do arquivo de quantidades
//
//Menu do operador
#define	CADASTRAR_DOADOR				'D'						//Op��o de cadastro de doadores
#define	CONSULTAR_DOADOR				'C'						//Op��o de consulta de doadores
#define	EXCLUIR_DOADOR					'E'						//Op��o de exclus�o de doador
#define	LISTAR_DOADORES					'L'						//Op��o para listar todos os doadores
#define	LISTAR_MELHORES_DOADORES		'M'						//Op��o para listar somente os melhores doadores
#define SAIR_DO_PROGRAMA				'S'						//Op��o para sair do sistema
//
//Outras defini��es do Programa
#define	MASCULINO						'M'						//Masculino
#define	FEMININO						'F'						//Feminino
#define	EXTENSAO_NOME					40						//Tamanho do nome
#define	EXTENSAO_RG						12						//Tamanho RG
#define	EXTENSAO_TIPO					2						//Tamanho do tipo sangu�neo
#define	MAXIMO_DOADORES					2000					//M�ximo de doadores do sistema
#define	TIPO_O							"O"						//Tipo O
#define	TIPO_A							"A"						//Tipo A
#define	TIPO_B							"B"						//Tipo B
#define	TIPO_AB							"AB"					//Tipo AB
#define	RH_POSITIVO						'+'						//Fator RH positivo
#define	RH_NEGATIVO						'-'						//Fator RH negativo
#define	IDADE_MINIMA					16						//Idade m�nima permitida
#define	IDADE_MAXIMA					69						//Idade m�xima permitida
#define	PESO_MINMO						50.00					//Peso m�nimo do doador
//
//Struct doador
typedef struct tagDOADOR
{
	char cNome[EXTENSAO_NOME + 1],								//Para receber o nome do doador
		cSexo,													//Para receber o sexo do doador
		cTipoSanguineo[EXTENSAO_TIPO + 1],						//Para receber o tipo sangu�neo do doador
		cFatorRH,												//Para receber o fator RH do sangue do doador
		cRG[EXTENSAO_RG + 1];									//Para receber o RG do doador
	int nIdade,													//Para receber a idade do doador
		iIndice;												//Para receber o �ndice do cadastro
	double dPeso;												//Para receber o peso do doador
	bool cadAtivoInativo;										//True - para cadastro ativo
																//False - para cadastro inativo
}DOADOR;
//
//Struct qtde de doadores
typedef struct tagQTDE
{
	int nQtdeDoadores;											//Para a quantidade de registros de doadores informada
}QTDE_DOADORES;
//
//Prot�tipo de Fun��es
bool GravarDoador(int nIndice, FILE **fdDoador, DOADOR *ptrStDoador);
bool PosicionarDoador(int nIndice, FILE *fdDoador);
bool LerDoador(FILE **fdDoador, DOADOR *ptrStDoador);