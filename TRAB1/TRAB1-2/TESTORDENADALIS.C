/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
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
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "ORDENADALISTA.h"


static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"     ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"  ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"  ;
static const char INSERIR_VALOR_CMD      [ ] = "=insertval"  ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"    ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"       ;
static const char IR_FIM_CMD              [ ] = "=irfinal"        ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"    ;
static const char PROCURAR_VALOR_CMD        [ ] = "=procv"    ;
static const char PRINT_LISTA_CMD        [ ] = "=printlista"    ;



#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

OLIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

	/* Essa função é requerida pela função cria lista e trata
	*  de liberar o valor armazenado pelos elementos.
	*/
   static void DestruirValor( OLIS_tppPessoa pValor ) ;

   /* Função valida o estado da lista antes e/ou depois de realizar
   *  um teste.
   */
   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   inxLista
*     =esvaziarlista              inxLista
*	  =destruirlista               inxLista
*     =insertval                    inxLista  stirng string TST_tpCondRet
*     =excluirelem               inxLista  TST_tpCondRet
*     =obtervalorelem           inxLista  string string TST_tpCondRet
*     =irinicio                      inxLista
*     =irfinal                        inxLista
*     =avancarelem             inxLista  numElem TST_tpCondRet
*	  =procv					    inxLista string string TST_tpCondRet
*     =printlista					inxLista string TST_tpCondRet
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char   StringDado[  DIM_VALOR ] ;
      char * pDado ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtListas[ inxLista ] =
                 OLIS_CriarLista( DestruirValor ) ;

            return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista."  ) ;

         } /* fim ativa: Testar CriarLista */

      /* Testar Esvaziar lista lista */

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            OLIS_EsvaziarLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar lista lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            OLIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista */
		 
		/* Testar Inserir Valor Ordenado */
         else if ( strcmp( ComandoTeste , INSERIR_VALOR_CMD ) == 0 )
         {
			char iniciaisIn[  DIM_VALOR/2 ];
			char nomeIn[  DIM_VALOR ];
			char* iniciaisRef;
			char* nomeRef;
			OLIS_tppPessoa pessoa;
			
			numLidos = LER_LerParametros( "issi" ,
                       &inxLista , iniciaisIn, nomeIn, &CondRetEsp ) ;
			
			if ( ( numLidos != 4 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
				    return TST_CondRetParm ;
            } /* if */
		 
		  iniciaisRef = ( char * ) malloc( strlen( iniciaisIn ) + 1 ) ;
            if ( iniciaisRef == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */
			
			strcpy( iniciaisRef , iniciaisIn );
			
			 nomeRef = ( char * ) malloc( strlen( nomeIn ) + 1 ) ;
            if ( nomeRef == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */
			
			strcpy( nomeRef , nomeIn );
			
			 pessoa = OLIS_CriarPessoa( iniciaisRef , nomeRef ) ;
			 
			if(pessoa == NULL){
					return TST_CondRetErro;
			}
			
			 CondRet = OLIS_InserirElemento( vtListas[ inxLista ] , pessoa ) ;
			
		 
			if ( CondRet != OLIS_CondRetOK )
            {
               DestruirValor(pessoa);
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir.") ;
					 
		 }/* fim ativa: Inserir Valor Ordenado  */

      /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      OLIS_ExcluirElemento( vtListas[ inxLista ] ) ,
                     "Condição de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            char iniciaisIn[  DIM_VALOR/2 ];
			char nomeIn[  DIM_VALOR ];
			OLIS_tppPessoa pessoa;
			
			numLidos = LER_LerParametros( "issi" ,
                       &inxLista , iniciaisIn, nomeIn, &ValEsp ) ;
			
			if ( ( numLidos != 4 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
				    return TST_CondRetParm ;
            } /* if */

           pessoa = OLIS_ObterValor(vtListas[ inxLista ]) ;

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , pessoa ,
                         "Valor não deveria existir." ) ;
            } /* if */

            if ( pessoa == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pessoa ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

            if (TST_CompararString( iniciaisIn , pessoa->iniciais ,
                         "Valor das iniciais errado." ) == TST_CondRetOK){
						 return TST_CompararString( nomeIn , pessoa->nomeCompleto ,
                         "Valor do nome errado." );
			} else{
				return TST_CondRetErro;
			}

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            OLIS_IrInicioLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ir para o elemento inicial */

      /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            OLIS_IrFinalLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: LIS  &Ir para o elemento final */

      /* LIS  &Avançar elemento */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      OLIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: LIS  &Avançar elemento */
		 
		/* Testar Procurar valor na lista (usa iniciais) */
         else if ( strcmp( ComandoTeste , PROCURAR_VALOR_CMD ) == 0 )
         {
			char iniciaisIn[  DIM_VALOR/2 ];
			char nomeIn[  DIM_VALOR ];
			char* iniciaisRef;
			char* nomeRef;
			OLIS_tppPessoa pessoa;
			
			numLidos = LER_LerParametros( "issi" , &inxLista, iniciaisIn, nomeIn, &CondRetEsp );

			if ( ( numLidos != 4 ) || ( ! ValidarInxLista(inxLista, NAO_VAZIO)) )
		    {
				return TST_CondRetParm;
			} /* if */

          iniciaisRef = ( char * ) malloc( strlen( iniciaisIn ) + 1 ) ;
          if ( iniciaisRef == NULL ){
				return TST_CondRetMemoria ;
		    } /* if */
    
          strcpy( iniciaisRef , iniciaisIn );

          nomeRef = ( char * ) malloc( strlen( nomeIn ) + 1 ) ;
          if ( nomeRef == NULL ){
				return TST_CondRetMemoria ;
			} /* if */
    
          strcpy( nomeRef , nomeIn );

          pessoa = OLIS_CriarPessoa(iniciaisRef , nomeRef ) ;
     
          if(pessoa == NULL){
              return TST_CondRetErro;
          }

          CondRet = OLIS_ProcurarValor( vtListas[ inxLista ], pessoa ) ;

          if ( CondRet != OLIS_CondRetOK ){	
				DestruirValor(pessoa);
            } /* if */
			
			return TST_CompararInt( CondRetEsp , CondRet, "Condição de retorno errada ao procurar valor"); 
		 
		 }/* fim ativa: Procurar valor na lista */ 
		 
		/* Testar Imprimir valores ordenados por iniciais */
         else if ( strcmp( ComandoTeste , PRINT_LISTA_CMD ) == 0 )
         {
				char* saidaPrint;
				int tamanhoEsperado;
				numLidos = LER_LerParametros("isi", &inxLista, StringDado, &CondRetEsp);
				

				if ( numLidos != 3 || (! ValidarInxLista(inxLista, NAO_VAZIO)) ) {
					return TST_CondRetParm;
				} /* if */
				
				pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
				if ( pDado == NULL ){
				
				   return TST_CondRetMemoria ;
				} /* if */

				strcpy( pDado , StringDado ) ;
				
				tamanhoEsperado = strlen( pDado ) + 1;
				saidaPrint = ( char * ) malloc( tamanhoEsperado) ;
				
				OLIS_Print (vtListas[ inxLista ] , saidaPrint , tamanhoEsperado );
				
				CondRet = TST_CompararString( pDado, saidaPrint,  "Condição de retorno errada imprimir ao lista ordenadamente");		
				
				free(saidaPrint);
				free(pDado);
				return  CondRet;
		 
		 }/* fim ativa: Imprimir valores ordenados  */	

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( OLIS_tppPessoa pValor )
   {
		free(pValor->iniciais);
		free(pValor->nomeCompleto);
		free(pValor) ;

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de lista */

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

