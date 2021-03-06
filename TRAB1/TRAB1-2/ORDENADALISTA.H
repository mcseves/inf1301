#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: OLIS Lista duplamente encadeada 
*	ordenada criada com base em lista.h
*
*  Arquivo gerado:              ORDENADALISTA.h
*  Letras identificadoras:      OLIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*      5	   gbha	13/set/2016 Implemetacao de mudancas do T1 (Ordenacao e estrutura pessoas)
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa listas da Pessoas (Nome e Inicial) duplamente
*	  encadeadas e internamente ordenada.
*     Podem existir n listas em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*	  Essa caracter�stica � enfor�ada pelo fata da lista n�o ser mais gen�rica.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: OLIS valor do elemento.
*	Pessoa representada por nome e inicial.
*
*
***********************************************************************/
	typedef struct OLIS_pessoa {
		char* iniciais;
			/* Caracteres mai�sculos que representem a primeira
			*  letra do nome e de cada sobrenome em ordem
			*/
		char* nomeCompleto;
			/* String com o nome da pessoa*/
	} OLIS_tpPessoa;

/* Tipo refer�ncia para estrutura de um elemento da lista. */
typedef struct OLIS_pessoa* OLIS_tppPessoa;

/* Tipo refer�ncia para uma lista */
typedef struct OLIS_tagLista* OLIS_tppLista;


/***********************************************************************
*
*  $TC Tipo de dados: OLIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         OLIS_CondRetOK ,
               /* Concluiu corretamente */

         OLIS_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         OLIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         OLIS_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

         OLIS_CondRetFaltouMemoria,
               /* Faltou mem�ria ao tentar criar um elemento de lista */
		
		 OLIS_CondRetErro
				/*N�o consegui realizar a opera��o desejada*/

   } OLIS_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: OLIS  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista de OLIS_tppPessoa duplamente encadeada e ordenada.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

   OLIS_tppLista OLIS_CriarLista(
             void   ( * ExcluirValor ) ( OLIS_tppPessoa pDado ) ) ;


/***********************************************************************
*
*  $FC Fun��o: OLIS  &Destruir lista
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $FV Valor retornado
*     OLIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   void OLIS_DestruirLista( OLIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: OLIS  &Esvaziar lista
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void OLIS_EsvaziarLista( OLIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: OLIS  &Inserir elemento ordenado
*
*  $ED Descri��o da fun��o
*     Insere novo elemento mantendo a ordem dos elementos na lista com base
*     nos caracteres das siglas de cada Pessoa.
*
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*	  Caso a pessoa sendo inserida tenha a mesma inicial de algu�m j�
*      na lista, o registro � alterado e a �ltima inser��o � que vale.
*
*  $EP Par�metros
*     Par�metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        OLIS_CondRetOK
*        OLIS_CondRetFaltouMemoria
*
***********************************************************************/

   OLIS_tpCondRet OLIS_InserirElemento( OLIS_tppLista pLista ,
                                         OLIS_tppPessoa pValor);


/***********************************************************************
*
*  $FC Fun��o: OLIS  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     OLIS_CondRetOK
*     OLIS_CondRetListaVazia
*
***********************************************************************/

   OLIS_tpCondRet OLIS_ExcluirElemento( OLIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: OLIS  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     n�o NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

   OLIS_tppPessoa OLIS_ObterValor( OLIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: OLIS  &Ir para o elemento inicial
*
*  $ED Descri��o da fun��o
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void OLIS_IrInicioLista( OLIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: OLIS  &Ir para o elemento final
*
*  $ED Descri��o da fun��o
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void OLIS_IrFinalLista( OLIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: OLIS  &Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a em dire��o ao final
*     Se numElem for negativo avan�a em dire��o ao in�cio
*     numElem pode ser maior do que o n�mro de elementos existentes na
*               dire��o desejada
*     Se numElem for zero somente verifica se a lista est� vazia
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o n�mero de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista est� vazia
*
***********************************************************************/

   OLIS_tpCondRet OLIS_AvancarElementoCorrente( OLIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Fun��o: OLIS  &Procurar elemento contendo valor
*
*  $ED Descri��o da fun��o
*     Procura o elemento que referencia o valor dado.
*     A fun��o compara ponteiro e n�o conte�do apontado.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     OLIS_CondRetOK  - se encontrou.
*                      O elemento corrente � o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que cont�m o ponteiro procurado
*
*     OLIS_CondRetNaoEncontrou - se o ponteiro n�o foi encontrado
*                      O elemento corrente continua o mesmo
*     OLIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   OLIS_tpCondRet OLIS_ProcurarValor( OLIS_tppLista pLista ,
                                    OLIS_tppPessoa pValor        ) ;

/***********************************************************************
*
*  $FC Fun��o: OLIS  &Criar pessoa.
*
*  $ED Descri��o da fun��o
*     Cria uma nova pessoa a partir de valores de nome iniciais.
*
*  $EP Par�metros
*     iniciais  - String com as iniciais da pessoa. Primeira letra do nome
*     seguido da primeira letra de cada sobrenome.
*     nomeCompleto  - Nome e sobrenome da pessoa.
*
*  $FV Valor retornado
*     OLIS_tppPessoa - Ponteiro para a pessoa.
*
***********************************************************************/
	OLIS_tppPessoa OLIS_CriarPessoa(char* iniciais, char* nomeCompleto);
	
/***********************************************************************
*
*  $FC Fun��o: OLIS  &Print.
*
*  $ED Descri��o da fun��o
*     Imprime todos os valores da lista. Como a lista � ordenada estes 
*	  valores estar�o ordenados tamb�m.
*	  
*    Para casos de debug ou testes automatizados � poss�vel passar
*    para a fun��o um espa�o de mem�ria que ser� preenchido com a 
*    string que foi impressa.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista que ser� impressa.
*     returnPrint  - Ponteiro para recebimento da string que ser� impressa.
*     Pode ser NULL
*     strMaxSize  - N�mero de carateres para o retorno.
*     Pode ser zero.
*   
*
***********************************************************************/
	void OLIS_Print(OLIS_tppLista pLista , char* returnPrint, int strMaxSize);
	
#undef LISTA_EXT
/********** Fim do m�dulo de defini��o: OLIS  Lista duplamente encadeada **********/

#else
#endif
