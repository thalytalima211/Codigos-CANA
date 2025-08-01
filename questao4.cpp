#include <vector>
#include <cstdio>

template <typename T>
class Arvore {
public:
    T valor;
    Arvore* esquerda;
    Arvore* direita;

    Arvore<T>(T valor){
        this->valor = valor;
        this->esquerda = nullptr;
        this->direita = nullptr;
    }

    Arvore* push(T valor){
        if(this->valor == valor) return nullptr;
        if(valor < this->valor){
            if(this->esquerda == nullptr){
                return this->esquerda = new Arvore(valor);
            }else{
                return this->esquerda->push(valor);
            }
        }else{
            if(this->direita == nullptr){
                return this->direita = new Arvore(valor);
            }else{
                return this->direita->push(valor);
            }
        }
        return nullptr;
    }

    std::vector<T> getNosFolha() {
        static auto out = std::vector<T>();
        out.clear();
        getNosFolhaHelper(&out,this);
        return out;
    }

    void getNosFolhaHelper(std::vector<T>* out,Arvore<T>* node){
        if(node->esquerda != nullptr){
            getNosFolhaHelper(out,node->esquerda);
        }
        out->push_back(node->valor);
        if(node->direita != nullptr){
            getNosFolhaHelper(out,node->direita);
        }
    
    };

    struct FindResult {
        Arvore* node;
        int nivel;
    };

    FindResult find(T valor,int nivel=0){
        if(valor == this->valor) return FindResult { this, nivel };
        if(valor < this->valor) return this->esquerda->find(valor,nivel+1);        
        if(valor > this->valor) return this->direita->find(valor,nivel+1);        
        return FindResult { nullptr, 0 };
    }

    int getGrau(T valor){
        auto find = this->find(valor).node;
        return (find->esquerda != nullptr) + (find->direita != nullptr);
    }

    int getProfundidade(T valor){
        return this->find(valor).nivel;
    }

    int getAltura(){
        return getAlturaHelper(this);
    }

    int getAlturaHelper(Arvore* node) {
        if (node == nullptr) return -1; // altura de árvore vazia é -1
        int alturaEsquerda = getAlturaHelper(node->esquerda);
        int alturaDireita = getAlturaHelper(node->direita);
        return 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita);
    }
};

int main() {
    auto root = Arvore(10);

    root.push(100);
    root.push(1);
    root.push(2);
    root.push(120);

}