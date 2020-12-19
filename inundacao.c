#include <stdio.h>
#include <stdlib.h>

// Quantidade de vértices
#define v 6


// Função que limpa as relações após a iteração em um vértice ter sido concluída
int limpaArestas(int *matriz, int vertice)
{
    for (int i = 0; i < v; i++)
    {
        *((matriz + i * v) + vertice) = 0;
    }
    return 1;
}

// Função que verifica se o vértice que tem uma aresta com o atual da iteração, já está no array de adjacentes
// Retorna 1 se já estiver, 0 se não estiver
int jaEhAdjacente(int *verticesAdjacentes, int contAdjacentes ,int vertice)
{
    for (int i = 0; i < contAdjacentes; i++)
    {
        if (*(verticesAdjacentes + i) == vertice)
        {
            return 1;
        }
    }
    return 0;
}

// Função para preencher a matriz a partir do arquivo matriz.txt.
int preencheMatriz(int *matriz) {
    int contadorArquivo = 0;
    FILE *pa;

    // Verificação se o arquivo pôde ser aberto
    if ((pa = fopen("matriz.txt", "r")) == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
        exit(1);
    }

    // Enquanto tiver conteúdo no arquivo e os dados não ultrapassarem o limite da matriz
    while (!feof(pa) && (contadorArquivo < (v*v)))
    {
        // Adiciona o inteiro achado na matriz
        fscanf(pa, "%d", (matriz + contadorArquivo));
        contadorArquivo++;
    }
    fclose(pa);
    return 0;
}

// Verifica se a matriz está correta
int verificaMatriz(int matriz[v][v]) {
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            // Se a matriz não tiver simétrica (considerando que não é um dígrafo)
            // Erro de inconsistência da adjacência do vértice 
            if (matriz[i][j] != matriz[j][i]) {
                printf("Adjacencia inconsistente\n");
                printf("Adjacencia [%d][%d] deve ser igual a [%d][%d]\n",i,j,j,i);
                exit(1);
            }
        }
    }
}

int main()
{
    //Inicializa a matriz
    int matriz[v][v] = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };
    
    int verticeAtual = 0;
    int verticesAdjacentes[v];
    int ehAdjacente;
    int contAdjacentes = 1;
    int indexVerticeAtual = 0;
    
    // Chama função pra preencher a matriz
    preencheMatriz(*matriz);
    // Chama a função para verificar a matriz preenchida
    verificaMatriz(matriz);

    // Escolha do vértice de partida
    // Caso não seja uma entrada válida, o programa continuará pedindo um vértice válido
    do {
        printf("Escolha um vertice:\n");
        scanf("%d", &verticeAtual);

        if (verticeAtual >= v) {
            printf("Os vertices disponiveis sao do intervalo de 0 a %d\n", v-1);
        }
    } while (verticeAtual >= v);

    // O primeiro vértice a ser colocado no array, é o escolhido pelo usuário
    verticesAdjacentes[0] = verticeAtual;

    // Equanto o array de adjacentes não atingir o número máximo de vértices do grafo
    // Ou não houver um vértice atual, continua procurando vértices adjacentes
    while ( contAdjacentes != v && (contAdjacentes > indexVerticeAtual) )
    {
        for (int i = 0; i < v; i++)
        {
            ehAdjacente = matriz[verticeAtual][i];
            if (ehAdjacente != 0) {
                // Verifica se o vértice que ele percebeu que possui aresta, já está no array de adjacentes
                // Caso não esteja, ele adiciona
                if (!jaEhAdjacente(verticesAdjacentes, contAdjacentes, i)) {
                    verticesAdjacentes[contAdjacentes] = i;
                    contAdjacentes++;
                }
                //Limpa aquela relação que já foi verificada
                matriz[verticeAtual][i] = 0;
            }
        }
        //Limpa as arestas do vértice que a iteração acabou para evitar o loop.
        limpaArestas(*matriz, verticeAtual);
        indexVerticeAtual++;
        // O vértice atual será o próximo da lista de adjacentes
        verticeAtual = verticesAdjacentes[indexVerticeAtual];
    }

    contAdjacentes == v ?
        printf("O grafo eh conexo\n") :
        printf("O grafo nao eh conexo\n");    
    
    printf("Os vertices adjacentes ao escolhido sao:\n");
    //Resultado printando as componentes conexas achadas
    for (int i = 0; i < contAdjacentes; i++)
    {
        printf("[%d]", verticesAdjacentes[i]);
    }
    printf("\n");

    return 0;
}