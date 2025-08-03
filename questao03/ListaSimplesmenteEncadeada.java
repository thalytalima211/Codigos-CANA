package questao03;

public class ListaSimplesmenteEncadeada {
    Node inicio; // nó inicial

       // inicialização da list
	   public ListaSimplesmenteEncadeada() {
	       this.inicio = null;
	   }

       //inserindo elementos
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
	   
	   //Ponteiros (slow e fast) para encontra nó do meio
	   public Node meio(Node inicio,Node ultimo) {
		   if(inicio==null) {
			   return null;
		   }
		 
		    Node slow = inicio;
		    Node fast = inicio;
            
		    while (fast.proximo != ultimo && fast.proximo.proximo != ultimo) {
				//fast avança dois nós
		        fast = fast.proximo.proximo;

				//slow avança um nó
		        slow = slow.proximo;
		    }
		 
		    return slow;
	   }

	   //busca sequencial
	   public boolean busca_Sequencial(int valor) {
		   int count = 0;
	       Node pAtual = inicio;

	       while (pAtual != null) {
	    	count++;
	           if (pAtual.elemento == valor) { // Se o valor do nó atual for igual ao buscado
                   System.out.println("Quantidade de comparações Busca sequencial:"+count);
	               return true; // Valor encontrado
	           }
	           pAtual = pAtual.proximo; // Vai para o próximo nó
	        
	       }
	       return false;  
	   }
	   
	   
	   public boolean busca_Binaria(int elemento) {
		    return busca_Binaria(inicio,null, elemento);
		}
	   
       // busca binaria
	   private boolean busca_Binaria(Node inicio,Node ultimo,int element) {
		   int count = 0;
		   while(inicio != ultimo) {
			   // Encontra o nó do meio entre inicio e ultimo
			   Node m= meio(inicio,ultimo);
			   
			   // Se não houver meio (encerra a busca)
			   if(m==null) {
				   return false;
			   }
			   count++;

			   // Caso o elemento do meio seja o valor procurado
			   if(m.elemento== element) {
				   System.out.println("Quantidade de comparações Busca binária:"+count);
				   return true; // Elemento encontrado
			   }
			   
			   // Se o elemento do meio for menor que o valor procurado
			   else if(m.elemento< element) {
				//busca continua na metade direita da lista.
				   inicio=m.proximo;
			   }
			   
			    // Se o elemento do meio for maior que o valor procurado
			   else {
				//busca continua na metade esquerda da lista.
				   ultimo= m;
			   }
			   
		   }
		   return false;  
	   }

	  //imprimir lista 
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
