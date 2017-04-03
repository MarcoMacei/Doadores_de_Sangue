#include "Doador.h"

//---[GravarDoador]--------------------------------------------------------------------
// Função que grava um doador dentro do arquivo de doadores
//
//	Parâmetros:
//		Entrada:
//			int nIndice - índice do cadastro do doador
//			FILE *fdDoador - file descriptor do doador
//			DOADOR *ptrStDoador - ponteiro da struct que contém os dados dos doadores a serem gravados
//		Retorno:
//			bool - true - indica que a gravação foi realizada
//				   false - indica que houve erro, ou no posicionamento ou na gravação
bool GravarDoador(int nIndice, FILE **fdDoador, DOADOR *ptrStDoador)
{
	//Fazer o posicionamento no arquivo
	if (fseek(*fdDoador, nIndice * SIZE_DOADORES, SEEK_SET) != 0)	//Fseek com erro?
		return false;								//Indica que houve erro

													//Vai vai gravar o registro do doador
	if (fwrite(ptrStDoador, SIZE_DOADORES, 1, *fdDoador) == 0)		//Erro de gravação?
		return false;								//Indica que houve erro

	//Arquivo posicionado e gravado
	return true;						//True - arquivo gravado com sucesso
}//Fim da função de gravação
 //
 //---[PosicionaDoador]--------------------------------------------------------------------
 // Função que posicionado no arquivo pelo índice informado
 //
 //	Parâmetros:
 //		Entrada:
 //			int nIndice - índice do cadastro do doador
 //			FILE *fdDoador - file descriptor do doador
 //		Retorno:
 //			bool - true - indica que foi corretamente posicionado
 //				   false - indica que houve erro no posicionamento
bool PosicionarDoador(int nIndice, FILE *fdDoador)
{
	//Fazer o posicionamento no arquivo
	if (fseek(fdDoador, nIndice * SIZE_DOADORES, SEEK_SET) != 0)	//Fseek com erro?
	{
		cout << endl << "\t\t\tErro de posicionamento!" << endl << endl;
		PAUSA;						//Pausa o programa
		return false;				//Indica que houve erro
	}//Fim if FSEEK - posicionamento

	return true;							//Se foi posicionado
}//Fim da função de posicionamento
//
//---[LerDoador]--------------------------------------------------------------------
// Função que lê um doador dentro do arquivo de doadores
//
//	Parâmetros:
//		Entrada:
//			int nIndice - índice do cadastro do doador
//			FILE *fdDoador - file descriptor do doador
//			DOADOR *ptrStDoador - ponteiro da struct que contém os dados dos doadores a serem lidos
//		Retorno:
//			bool - true - indica que a leitura foi realizada e o conteúdo do doador
//							foi armazenado em ptrStDoador
//				   false - indica que houve erro, ou no posicionamento ou na leitura
bool LerDoador(FILE **fdDoador, DOADOR *ptrStDoador)
{
	 //Vai ler o registro do doador
	if (fread(ptrStDoador, SIZE_DOADORES, 1, *fdDoador) == 0)		//Erro de leitura?
	{
		cout << endl << "\t\t\tErro de leitura!" << endl << endl;
		PAUSA;						//Pausa o programa
		return false;				//Indica que o registro não pode ser lido
	}//Fim do if FREAD - leitura

	 //Verificando se está livre
	if (ptrStDoador->cadAtivoInativo == true)				//Se true, cadastro existente
		return false;										//Retorna false se o cadastro já existe

	//lido e cadastro livre
	return true;							//Se o cadastro não existe retorna true
}//Fim da função de leitura