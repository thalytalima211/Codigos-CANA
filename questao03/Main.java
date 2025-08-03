package questao03;
/** 
 Descrição da questão: 
  Implemente em Java os algoritmos de busca sequencial e binária para listas simplesmente encadeadas.

 Responsável: Cláudia Ferreira de Souza.

 Comandos para rodar a Class main(vscode):
 1- cd Codigos-CANA 
 2- javac questao03/*.java
 3- java questao03.Main 

**/

public class Main {
    public static void main(String[] args) {
		ListaSimplesmenteEncadeada list = new ListaSimplesmenteEncadeada ();

		   //inserindo ordenado manualmente
		   list.inserir(8); 
	       list.inserir(12); 
	       list.inserir(19); 
	       list.inserir(43); 
	       list.inserir(45); 
	       list.inserir(56); 
	       list.inserir(61);  
	       list.inserir(95); 



	       list.imprimirLista();
	      
	  
	       int elemento =8; //busca elemento
	       
	       System.out.println("Buscar Binária "+elemento+":" + list.busca_Sequencial(elemento));
	       System.out.println("Buscar Linear "+elemento+":" + list.busca_Binaria(elemento));
           
	       
	       

	   }
    
}
