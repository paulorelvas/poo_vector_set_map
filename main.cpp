#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <map>
#include <string>


using namespace std;

// usando para o sort - usando class e função de comparação, expressão lambda
class Obj {
public:
    // Construtor - membro var do tipo int
    Obj(int v): valor(v) {
    }
    int valor;
};

Obj a{10};
Obj b{9};
vector<Obj> v_aux {a, b};

// função usada no algoritmo sort
bool compara_func(const Obj & a, const Obj & b);

// função usada no for_each
void devolveElementos (int i);

int main(){

    cout << "------ ::SET_MAP_VECTOR:: ------" << endl;

    /** ------------- :: SET :: ---------------
     *      Usado para armazenar apenas KEYs
     *      AS inserções são mais rápidos na inserção e eliminação no meio do container (set)
     *      Acesso aos elementos usando apenas a partir da STL <contentor associativo>
     *      Não insere repetidos
     *
     *      set<int> st;
     *      st.insert(2);
     *      st.insert(5);
     *      cout << "Elementos SET: " << endl;
     *          for (auto it : st)
     *              cout << it << " "; // Os elementos são devolvidos de forma ordenada
     *
     *      Exemplo: se pretender criar um dicionário de palavras,o ideal é usar um set<string>
     */
    set<int> st;
    st.insert(2);
    st.insert(5);
    st.insert(1);
    st.insert(2);//
    cout << "Elementos SET: " << endl;
    for (auto it : st)
        cout << it << " " ; // Os elementos são devolvidos de forma ordenada

    /** ------------- :: MAP :: ---------------
     *      Composto por pares KEY VALUE - usado para armazenar pares key value <string, string>, <int, string>, <string, int>
     *      AS inserções são mais rápidos na inserção e eliminação no meio do container (set)
     *      Acesso aos elementos usando apenas a partir da STL <contentor associativo>
     *      Não insere repetidos
     *
     *      map<int, int> mp;  // map<string, int>...
     *      mp[1] = 5; // Inserção por index (insere no formato(1,5)
     *
     *      // Inserção no formato de pares
     *      mp.insert({ 2, 9 });  // alternativa usando a função make_pair(2,9) ou a função pair();
     *      mp.insert({ 3, 5 });
     *          for (auto it : mp)
     *              cout << it.first << ", " << it.second << endl; // Os elementos são devolvidos de forma ordenada
     *
     *      Exemplo: se pretender criar um dicionário de palavras e contar o número de ocorrências,o ideal é usar um map<string, int>
     */

    cout << endl << "Elementos MAP: " << endl;
    map<int, int> mp;
    mp[2] = 5; // Inserção por index (insere (2,5)

    // Inserção no formato de pares
    mp.insert({ 1, 9 });  // alternativa usando a função make_pair(2,9);
    mp.insert({ 3, 5 });
    mp.insert({ 3, 5 });
    mp.insert({ 4, 5 });
    for (auto it : mp)
        cout << it.first << ", " << it.second << endl; // Os elementos são devolvidos de forma ordenada


    /** ------------- :: VECTOR :: ---------------
     *
     *      Operações de inserção e de eliminção mais rápidas que os SETS e MAPS
     *      Possível aceder usando iterator e no formato [] <contentor sequencial>
     *
     *      Permite iserção de repetidos
     *      usa a função push_back(v) para a inserção
     */

    vector<int> v{1,4,5,6,2,1};

    cout << "Elementos VECT: " << endl;
    for (auto it : v)
        cout << it << " "; // Os elementos são devolvidos de forma ordenada

    /**
     *      Algortimos usados em contentores e expressões lambda
     *      #include <algorithm>
     *
     *      Estes algoritmos (remove() e remove_if() não podem ser usados em contentores associativos (set, map, ...) -
     *          porque o iterador não desreferencia o elemento - as chaves NÃO PODEM SER MODIFICADAS
     *
     *      remove() - remove o elemento com determinado valor e reduz o tamanho do contentor -
     *                  usado associado ao método ERASE
     *
     *                  Recebe um iterador para o primeiro e para o último elemento e uma referência para o objeto
     *                  forwardIt remove(forwardIt first, forwardIt last, const T& val)
     *                  Devolve o iterador para o novo último elemento

     *
     *      remove_if() - similar ao remove - recebe um Predicado Unário - critério/condição
     *                  usado associado ao método ERASE
     *                  forwardIt remove_if(forwardIt first, forwardIt last, UnaryPredicate p)
     *
     *      As funções remove e remove_if apenas eliminam quando usadas com uma função como: erase
     *      Não eliminam porque não permite eliminar diretamente - não têm associado o tipo de contentor - usam apenas iterador
     *      Na realidade apenas mudam os elementos para serem posteriormente eliminados
     *
     *      funções remove e remove_if,... podem ser usadas com expressões lambda [obj] (argumentos, ...) {return ...}
     */

    // vetor usando remove_if e expressões lambda
    vector<int> v1{ 1, 11, 2, 3, 4, 8, 10, 15, 20 };

    cout << endl << "Elementos vector v1 - antes da expressão lambda: " << v1.size() << endl;
    // expressão lambda para remover valores menores que 9 do vector v1
    auto remove_values = [&](int values) -> bool{
        return values < 8;
    };

    // call remove_if usando lambda como predicado unário
    auto iterator = remove_if(v1.begin(), v1.end(), remove_values);
    cout << endl << "Elementos vector v1 - após expressão lambda: " << v1.size() << endl;

    v1.erase(iterator, v1.end());

    cout << endl << "Elementos vector v1 - expressão lambda após erase: " << v1.size() << endl;
    for (auto it : v1)
        cout << it << " ";

    cout << endl << " ---- for_each::lambda ----" << endl;

    /*      for_each() - loop para percorrer um contentor (pode ser usado em todos os contentores) - lambda
    *                  - aceita o uso de funções/objeto função - são executadas no loop para cada elemento existente no container
    *                  - torna o código mais legível
    *      for_each(v.begin(), v.end(), [] () {...} // v.begin() e v.end() iterators - ou v.cbegin() e v.cend() para const iterators
    *
    *      em alternativa usar for(v.begin(); v.end(); inc){...} ou for(auto & el: v1){...}
    */
    // vetor usando for_each - lambda
    vector<int> v2{ 1, 9, 3, 4, 4, 8, 10, 15, 20 };

    // for_each para imprimir vector usando lambda - função unária -
    //      recebe um elemento de cada vez do vetor no intervalo definido entre begin--end
    for_each(v2.begin(), v2.end(), devolveElementos);


     /*
     * sort - para ordenar um intervalo de valores existente num contentor
     *          - contentores sequenciais - definido pelo par de iteradores (begin, end)
     *          sort(vector.begin(), vector.end());
     *
     *      find() - pesquisa uma substring numa string
     *      obj.find("str") devolve npos quando não encontra a sub string na string
     *      size_t - devolve 0 quando não encontra a sub string na string
     *      string :: pos <size_t> - especificar a posição onde inicia a procura
     *      string::npos - handle para a string e que permite detetar o fim da mesma
     *
     */

    // sort - formato simples - par de iteradores (begin, end)
    sort(v2.begin(), v2.end());
    cout << endl << "sort v2 - formato simples " << endl;
    for (auto it : v2)
        cout << it << " ";

    // sort - com ordem específica (asc [less<int>()] or desc [greater<int>()] )
    sort(v2.begin(), v2.end(), greater<int>()); // less<int>()
    cout << endl << "sort v2 - ordem especifica " << endl;
    for (auto it : v2)
        cout << it << " ";

    // sort - usando class e função de comparação, expressão lambda
    // expressão lambda
    auto compara = [](const Obj & a, const Obj & b){ return a.valor < b.valor; };
    sort(v_aux.begin(), v_aux.end(), compara);
    cout << endl << "sort v_aux - ordem expressao lambda - class " << endl;
    for (auto it : v_aux)
        cout << it.valor << " ";

    cout << endl << "sort v_aux - ordem usando função " << endl;
    sort(v_aux.begin(), v_aux.end(), compara_func);
    for (auto it : v_aux)
        cout << it.valor << " ";

    vector<int>::iterator it;
    cout << endl << "after insert() vector: " << v1.size() << endl;
    for (auto it : v1)
        cout << it << " ";
    it = v1.begin();
    // não é muito eficiente - obriga ao realloc dos elementos no container
    // sempre que a inserção não seja no final
    it = v1.insert ( it+2 , 99 );
    cout << endl << "insert() vector: (size) after insert " << v1.size() << endl;
    for (auto it : v1)
        cout << it << " ";


    string poo = "Programação Orientada a Objetos - práticas";
    string str1 = "et";
    string str2 = "Objetos";

    cout << endl << "find() " <<  endl;
    size_t encontrou = poo.find(str1);  // devolve o tamanho da substring na string
    if (encontrou != string::npos) // alternativa --> if(encontrou != 0)
        cout << "substring encontrada em: " << encontrou << endl;
    else
        cout << "substring não encontrada" << endl;

    cout << encontrou;

    return 0;
}


// função usada no algoritmo sort
bool compara_func(const Obj & a, const Obj & b){
    return a.valor > b.valor;
}
// função usada no for_each
void devolveElementos (int i){
    cout << ' ' << i;
}


