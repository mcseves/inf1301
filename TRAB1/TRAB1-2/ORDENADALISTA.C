/***************************************************************************
*  $MCI Módulo de implementação: OLIS Lista duplamente
*  encadeada ordenada criada com base em lista.h
*
*  Arquivo gerado:              ORDENADALISTA.c
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
*	  5	   gbha	13/set/2016 Implemetacao de mudancas do T1 (Ordenacao e estrutura pessoas)
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "ORDENADALISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: OLIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         struct OLIS_pessoa*  pPessoa ;
               /* Ponteiro para o valor contido no elemento do tipo Pessoa */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: OLIS Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct OLIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( OLIS_tppPessoa pValor ) ;
               /* Ponteiro para a função de destruição do tipo pessoa contido em um elemento */

   } OLIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( OLIS_tppLista   pLista ,
                                tpElemLista  * pElem) ;

   static tpElemLista * CriarElemento( OLIS_tppLista pLista ,
                                      OLIS_tppPessoa    pValor) ;

   static void LimparCabeca( OLIS_tppLista pLista) ;
   
   static OLIS_tpCondRet OLIS_InserirElementoAntes(OLIS_tppLista pLista ,
                                          OLIS_tppPessoa pValor);
										  
	static OLIS_tpCondRet OLIS_InserirElementoApos(OLIS_tppLista pLista ,
                                          OLIS_tppPessoa pValor);
										  
	static OLIS_tpCondRet OLIS_ComparaPessoa( OLIS_tppPessoa referencia,
                                          OLIS_tppPessoa alvo);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: OLIS  &Criar lista
*  ****/

   OLIS_tppLista OLIS_CriarLista( void   ( * ExcluirValor ) ( OLIS_tppPessoa pDado ) ){

      OLIS_tpLista * pLista = NULL ;

      pLista = ( OLIS_tpLista * ) malloc( sizeof( OLIS_tpLista )) ;
      if ( pLista == NULL )
      {
         return NULL ;
      } /* if */

      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor ;

      return pLista ;

    } /* Fim função: OLIS  &Criar lista */

/***************************************************************************
*
*  Função: OLIS  &Destruir lista
*  ****/

   void OLIS_DestruirLista( OLIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      OLIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim função: OLIS  &Destruir lista */

/***************************************************************************
*
*  Função: OLIS  &Esvaziar lista
*  ****/

   void OLIS_EsvaziarLista( OLIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim função: OLIS  &Esvaziar lista */


/***************************************************************************
*
*  $FC Função: OLIS  &Inserir elemento ordenado
*  ****/

   OLIS_tpCondRet OLIS_InserirElemento( OLIS_tppLista pLista ,
                                         OLIS_tppPessoa pValor)
      
   {
	  OLIS_tppPessoa  pessoa;
	  OLIS_tpCondRet  ret;
	  int res;
	  int dirAnterior = 0;
	  int meio = pLista->numElem/2;
	  

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
	  
	  if(pLista->numElem<2){
			return OLIS_InserirElementoApos(pLista , pValor);
	    }
	  
	  OLIS_IrInicioLista(pLista);
	  ret  = OLIS_AvancarElementoCorrente(pLista, meio);
	  if(ret!=OLIS_CondRetOK) return OLIS_CondRetErro;
	  
	  while(1){
		   pessoa = OLIS_ObterValor(pLista);
		   res = strcmp(pValor->iniciais, pessoa->iniciais);
		   
		   if(res<0 && dirAnterior>0){
				//Achou ponto de inserção no meio:  indo para o fim;
				return OLIS_InserirElementoAntes(pLista , pValor);						
			}
			
			if(res>0 && dirAnterior<0){
				//Achou ponto de inserção no meio:  indo para o inicio;
				return OLIS_InserirElementoApos(pLista , pValor);
			}
		   
		  if(res<0){
				// deve inserir antes do corrente;
				if(pLista->pElemCorr->pAnt == NULL){
					return OLIS_InserirElementoAntes(pLista , pValor);						
				}else{
					pLista->pElemCorr =  pLista->pElemCorr->pAnt ;
				}
				dirAnterior = -1;
		    }else if(res == 0){
				// deve por cima do corrente;
				pLista->pElemCorr->pPessoa = pValor;
				return OLIS_CondRetOK;		  
		    }else{
				// deve inserir depois do corrente;
				if(pLista->pElemCorr->pProx == NULL){
					return OLIS_InserirElementoApos(pLista , pValor);
				}else{
					pLista->pElemCorr =  pLista->pElemCorr->pProx ;
				}
				dirAnterior = 1;
			}
		}
    } /* Fim função: OLIS  &Inserir elemento ordenado */

/***************************************************************************
*
*  Função: OLIS  &Excluir elemento
*  ****/

   OLIS_tpCondRet OLIS_ExcluirElemento( OLIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return OLIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return OLIS_CondRetOK ;

   } /* Fim função: OLIS  &Excluir elemento */

/***************************************************************************
*
*  Função: OLIS  &Obter referência para o valor contido no elemento
*  ****/

   OLIS_tppPessoa OLIS_ObterValor( OLIS_tppLista pLista ) 
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
        return NULL ;
      } /* if */

      return pLista->pElemCorr->pPessoa ;

   } /* Fim função: OLIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: OLIS  &Ir para o elemento inicial
*  ****/

   void OLIS_IrInicioLista( OLIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim função: OLIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: OLIS  &Ir para o elemento final
*  ****/

   void OLIS_IrFinalLista( OLIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim função: OLIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: OLIS  &Avançar elemento
*  ****/

   OLIS_tpCondRet OLIS_AvancarElementoCorrente( OLIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {

            return OLIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */

         if ( numElem > 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return OLIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return OLIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return OLIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return OLIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         return OLIS_CondRetOK ;

   } /* Fim função: OLIS  &Avançar elemento */

/***************************************************************************
*
*  Função: OLIS  &Procurar elemento contendo valor
*  ****/

   OLIS_tpCondRet OLIS_ProcurarValor( OLIS_tppLista pLista ,
                                    OLIS_tppPessoa pValor){

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pOrigemLista == NULL )
      {
         return OLIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pOrigemLista; pElem != NULL ; pElem  = pElem->pProx ){
         if (OLIS_ComparaPessoa(pElem->pPessoa , pValor)==OLIS_CondRetOK){
				pLista->pElemCorr = pElem;
				return OLIS_CondRetOK ;
			} /* if */
		} /* for */

      return OLIS_CondRetNaoAchou ;

    } /* Fim função: OLIS  &Procurar elemento contendo valor */

/***********************************************************************
*
*  $FC Função: OLIS  -Criar pessoa.
*
***********************************************************************/
   
   OLIS_tppPessoa OLIS_CriarPessoa(char* iniciais, char* nomeCompleto){
	  OLIS_tppPessoa pessoa ;

      pessoa = ( OLIS_tppPessoa ) malloc( sizeof( OLIS_tpPessoa)) ;
      if ( pessoa == NULL )
      {
         return NULL ;
      } /* if */

      pessoa->iniciais   = iniciais  ;
      pessoa->nomeCompleto = nomeCompleto;
	  
      return pessoa ; 
	}/* Fim função: OLIS  -Criar pessoa. */
   
   /***********************************************************************
*
*  $FC Função: OLIS  -Print.
*
***********************************************************************/
	void OLIS_Print(OLIS_tppLista pLista , char* returnPrint, int strMaxSize){
		 tpElemLista * pElem ;
		 int proxTamanho;
		 #ifdef _DEBUG
			assert( pLista  != NULL ) ;
		 #endif
			
			returnPrint[0] = '\0';
		 if ( pLista->pOrigemLista == NULL ){
				return;
			} /* if */
			
		 pElem  = pLista->pOrigemLista;
		
		 
		 while(pElem!=NULL) {
				int iniLen, nomeLen;
				iniLen = strlen(pElem->pPessoa->iniciais);
				nomeLen = strlen(pElem->pPessoa->nomeCompleto);
				
				proxTamanho =  strlen(returnPrint)+iniLen+nomeLen+1;
				if(proxTamanho>strMaxSize){
						break;
				}
				
				strcat(returnPrint, pElem->pPessoa->iniciais);
				strcat(returnPrint, pElem->pPessoa->nomeCompleto);
				
				pElem  = pElem->pProx ;
			}	
			
			printf("%s",  returnPrint);
	}/* Fim função: OLIS  -Print. */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/
   tpElemLista* CriarElemento( OLIS_tppLista pLista ,
                               OLIS_tppPessoa      pValor  )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pPessoa = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */

/***********************************************************************
*
*  $FC Função: OLIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( OLIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pPessoa != NULL        ))
      {
         pLista->ExcluirValor( pElem->pPessoa ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim função: OLIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: OLIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( OLIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim função: OLIS  -Limpar a cabeça da lista */
   
   /***************************************************************************
*
*  Função: OLIS  &Inserir elemento antes
*  ****/

   OLIS_tpCondRet OLIS_InserirElementoAntes(OLIS_tppLista pLista ,
                                          OLIS_tppPessoa pValor){

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return OLIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return OLIS_CondRetOK ;

    } /* Fim função: OLIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/
   OLIS_tpCondRet OLIS_InserirElementoApos(OLIS_tppLista pLista ,
                                          OLIS_tppPessoa pValor        ){

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir após */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return OLIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return OLIS_CondRetOK ;

    } /* Fim função: LIS  &Inserir elemento após */
   
   
   /***************************************************************************
*
*  Função: OLIS  &Compara pessoa.
*  ****/
   OLIS_tpCondRet OLIS_ComparaPessoa( OLIS_tppPessoa referencia,
                                          OLIS_tppPessoa alvo){
		if((strcmp(referencia->iniciais, alvo->iniciais)==0)
		&&(strcmp(referencia->nomeCompleto, alvo->nomeCompleto)==0)){
			return OLIS_CondRetOK;
		}
		return OLIS_CondRetErro;   
    }/* Fim função: OLIS  &Compara pessoa */
	
	
/********** Fim do módulo de implementação: OLIS  Lista duplamente encadeada **********/

