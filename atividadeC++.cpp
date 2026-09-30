#include <iostream>

using namespace std;

struct No {
    int valor;
    No* proximo;
    No* anterior;

    No(int val) {
        valor = val;
        proximo = nullptr;
        anterior = nullptr;
    }
};

class ListaDupla {
private:
    No* inicio;
    No* fim;
    int tamanhoAtual;

public:
    ListaDupla() {
        inicio = nullptr;
        fim = nullptr;
        tamanhoAtual = 0;
    }

    ~ListaDupla() {
        No* atual = inicio;
        while (atual != nullptr) {
            No* proximoNo = atual->proximo;
            delete atual;
            atual = proximoNo;
        }
    }

    void inserirInicio(int valor) {
        No* novo = new No(valor);

        if (inicio == nullptr) {
            inicio = novo;
            fim = novo;
        } else {
            novo->proximo = inicio;
            inicio->anterior = novo;
            inicio = novo;
        }

        tamanhoAtual++;
    }

    void inserirFim(int valor) {
        No* novo = new No(valor);

        if (inicio == nullptr) {
            inicio = novo;
            fim = novo;
        } else {
            fim->proximo = novo;
            novo->anterior = fim;
            fim = novo;
        }

        tamanhoAtual++;
    }

    void inserirPosicao(int valor, int pos) {
        if (pos < 0 || pos > tamanhoAtual) {
            cout << "Posicao invalida para insercao!\n";
            return;
        }

        if (pos == 0) {
            inserirInicio(valor);
            return;
        }

        if (pos == tamanhoAtual) {
            inserirFim(valor);
            return;
        }

        No* novo = new No(valor);
        No* atual = inicio;

        for (int i = 0; i < pos - 1; i++) {
            atual = atual->proximo;
        }

        novo->proximo = atual->proximo;
        novo->anterior = atual;
        atual->proximo->anterior = novo;
        atual->proximo = novo;

        tamanhoAtual++;
    }

    void removerInicio() {
        if (inicio == nullptr) {
            cout << "A lista esta vazia!\n";
            return;
        }

        No* aux = inicio;

        if (inicio == fim) {
            inicio = nullptr;
            fim = nullptr;
        } else {
            inicio = inicio->proximo;
            inicio->anterior = nullptr;
        }

        delete aux;
        tamanhoAtual--;
    }

    void removerFim() {
        if (inicio == nullptr) {
            cout << "A lista esta vazia!\n";
            return;
        }

        No* aux = fim;

        if (inicio == fim) {
            inicio = nullptr;
            fim = nullptr;
        } else {
            fim = fim->anterior;
            fim->proximo = nullptr;
        }

        delete aux;
        tamanhoAtual--;
    }

    void removerPosicao(int pos) {
        if (pos < 0 || pos >= tamanhoAtual) {
            cout << "Posicao invalida para remocao!\n";
            return;
        }

        if (pos == 0) {
            removerInicio();
            return;
        }

        if (pos == tamanhoAtual - 1) {
            removerFim();
            return;
        }

        No* atual = inicio;

        for (int i = 0; i < pos; i++) {
            atual = atual->proximo;
        }

        atual->anterior->proximo = atual->proximo;
        atual->proximo->anterior = atual->anterior;

        delete atual;
        tamanhoAtual--;
    }

    int tamanho() const {
        return tamanhoAtual;
    }

    bool buscar(int valor) const {
        No* atual = inicio;
        int pos = 0;

        while (atual != nullptr) {
            if (atual->valor == valor) {
                cout << "Valor " << valor << " encontrado na posicao " << pos << ".\n";
                return true;
            }
            atual = atual->proximo;
            pos++;
        }

        cout << "Valor " << valor << " nao foi encontrado na lista.\n";
        return false;
    }

    void imprimir() const {
        if (inicio == nullptr) {
            cout << "Lista vazia.\n";
            return;
        }

        No* atual = inicio;
        cout << "Lista: ";
        while (atual != nullptr) {
            cout << atual->valor;
            if (atual->proximo != nullptr) {
                cout << " <-> ";
            }
            atual = atual->proximo;
        }
        cout << "\n";
    }
};

int main() {
    ListaDupla minhaLista;

    minhaLista.inserirInicio(10);
    minhaLista.inserirInicio(5);
    minhaLista.inserirFim(30);
    minhaLista.inserirPosicao(20, 2);

    minhaLista.imprimir();
    cout << "Tamanho atual: " << minhaLista.tamanho() << "\n\n";

    minhaLista.buscar(20);
    minhaLista.buscar(99);
    cout << "\n";

    minhaLista.removerInicio();
    minhaLista.imprimir();

    minhaLista.removerFim();
    minhaLista.imprimir();

    minhaLista.removerPosicao(1);
    minhaLista.imprimir();

    cout << "Tamanho final: " << minhaLista.tamanho() << "\n";

    return 0;
}