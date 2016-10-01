#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: OLIS Lista duplamente encadeada 
*	ordenada criada com base em lista.h
*
*  Arquivo gerado:              ORDENADALISTA.h
*  Letras identificadoras:      OLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*      5	   gbha	13/set/2016 Implemetacao de mudancas do T1 (Ordenacao e estrutura pessoas)
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas da Pessoas (Nome e Inicial) duplamente
*	  encadeadas e internamente ordenada.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*	  Essa característica é enforçada pelo fata da lista não ser mais genérica.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: OLIS valor do elemento.
*	Pessoa representada por nome e inicial.
*
*
***********************************************************************/
	typedef struct OLIS_pessoa {
		char* iniciais;
			/* Caracteres maiúsculos que representem a primeira
			*  letra do nome e de cada sobrenome em ordem
			*/
		char* nomeCompleto;
			/* String com o nome da pessoa*/
	} OLIS_tpPessoa;

/* Tipo referência para estrutura de um elemento da lista. */
typedef struct OLIS_pessoa* OLIS_tppPessoa;

/* Tipo referência para uma lista */
typedef struct OLIS_tagLista* OLIS_tppLista;


/***********************************************************************
*
*  $TC Tipo de dados: OLIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         OLIS_CondRetOK ,
               /* Concluiu corretamente */

         OLIS_CondRetListaVazia ,
               /* A lista não contém elementos */

         OLIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         OLIS_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         OLIS_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento de lista */
		
		 OLIS_CondRetErro
				/*Não consegui realizar a operação desejada*/

   } OLIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: OLIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista de OLIS_tppPessoa duplamente encadeada e ordenada.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   OLIS_tppLista OLIS_CriarLista(
             void   ( * ExcluirValor ) ( OLIS_tppPessoa pDado ) ) ;


/***********************************************************************
*
*  $FC Função: OLIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     OLIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   void OLIS_DestruirLista( OLIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: OLIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void OLIS_EsvaziarLista( OLIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: OLIS  &Inserir elemento ordenado
*
*  $ED Descrição da função
*     Insere novo elemento mantendo a ordem dos elementos na lista com base
*     nos caracteres das siglas de cada Pessoa.
*
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*	  Caso a pessoa sendo inserida tenha a mesma inicial de alguém já
*      na lista, o registro é alterado e a última inserção é que vale.
*
*  $EP Parâmetros
*     Parâmetros
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
*  $FC Função: OLIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
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
*  $FC Função: OLIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

   OLIS_tppPessoa OLIS_ObterValor( OLIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: OLIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void OLIS_IrInicioLista( OLIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: OLIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void OLIS_IrFinalLista( OLIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: OLIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

   OLIS_tpCondRet OLIS_AvancarElementoCorrente( OLIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Função: OLIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     OLIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     OLIS_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     OLIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   OLIS_tpCondRet OLIS_ProcurarValor( OLIS_tppLista pLista ,
                                    OLIS_tppPessoa pValor        ) ;

/***********************************************************************
*
*  $FC Função: OLIS  &Criar pessoa.
*
*  $ED Descrição da função
*     Cria uma nova pessoa a partir de valores de nome iniciais.
*
*  $EP Parâmetros
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
*  $FC Função: OLIS  &Print.
*
*  $ED Descrição da função
*     Imprime todos os valores da lista. Como a lista é ordenada estes 
*	  valores estarão ordenados também.
*	  
*    Para casos de debug ou testes automatizados é possível passar
*    para a função um espaço de memória que será preenchido com a 
*    string que foi impressa.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista que será impressa.
*     returnPrint  - Ponteiro para recebimento da string que será impressa.
*     Pode ser NULL
*     strMaxSize  - Número de carateres para o retorno.
*     Pode ser zero.
*   
*
***********************************************************************/
	void OLIS_Print(OLIS_tppLista pLista , char* returnPrint, int strMaxSize);
	
#undef LISTA_EXT
/********** Fim do módulo de definição: OLIS  Lista duplamente encadeada **********/

#else
#endif
