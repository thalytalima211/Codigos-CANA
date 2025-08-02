package questao03;

public class ListaSimplesmenteEncadeada {
    Node inicio; 

	   public ListaSimplesmenteEncadeada() {
	       this.inicio = null;
	   }


	   public void inserir(int elemento){
	       Node novo= new Node(elemento);
	       
	        if (inicio == null) {
	            inicio = novo;
	        } else {
	            Node atual = inicio;
	            while (atual.proximo != null) {
	                atual = atual.proximo;
	            }
	            atual.proximo = novo;
	        }
	   }
	   
	   
	   public Node meio(Node inicio,Node ultimo) {
		   if(inicio==null) {
			   return null;
		   }
		 
		    Node slow = inicio;
		    Node fast = inicio;
            
		    while (fast.proximo != ultimo && fast.proximo.proximo != ultimo) {
		        fast = fast.proximo.proximo;
		        slow = slow.proximo;
		    }
		 
		    return slow;
	   }

	   
	   public boolean busca_Sequencial(int valor) {
		   int passos = 0;
	       Node pAtual = inicio;

	       while (pAtual != null) {
	    	   passos++;
	           if (pAtual.elemento == valor) {
                   System.out.println("Quantidade de comparações Busca sequencial:"+passos);
	               return true;
	           }
	           pAtual = pAtual.proximo;
	        
	       }
	       return false;  
	   }
	   
	   
	   public boolean busca_Binaria(int elemento) {
		    return busca_Binaria(inicio,null, elemento);
		}
	   

	   private boolean busca_Binaria(Node inicio,Node ultimo,int element) {
		   int passos = 0;
		   while(inicio != ultimo) {
			   Node m= meio(inicio,ultimo);
			   
			   if(m==null) {
				   return false;
			   }
			   passos++;
			   if(m.elemento== element) {
				   System.out.println("Quantidade de comparações Busca Binária:"+passos);
				   return true;
			   }
			   
			   else if(m.elemento< element) {
				   inicio=m.proximo;
			   }
			   
			   else {
				   ultimo= m;
			   }
			   
		   }
		   return false;  
	   }

	
	   public void imprimirLista() {

	       Node pAtual = inicio;
	       System.out.println("inicio->");
	       while (pAtual != null) {
	           System.out.print(pAtual.elemento + " -> ");
	           pAtual = pAtual.proximo;
	       }
	       System.out.println("null");
	   }
    
}
