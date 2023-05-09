#include "huff_head.h"
#include "queue_head.h"
#include "tree_head.h"

void proces_input(char kalimat[1000], ListQueue *L){
    int freq[128] = {0}; //  agar dapat menampung semua karakter ASCII
    int i;
    for (i = 0; kalimat[i] != '\0'; i++) {
        freq[(int)kalimat[i]]++; // Tambahkan karakter ke array frekuensi
    }
    
    for (i = 0; i < 128; i++) { // Melakukan iterasi dari nilai ASCII 0 hingga 127
        if (freq[i] > 0) {
            char info = i; // Simpan nilai ASCII ke dalam variabel info
            Insrt_Node(&(*L),freq[i],info);
        } 
    }
}


char* input_teks(){
    char* input = (char*) malloc(1001 * sizeof(char)); // tambahkan 1 byte untuk null terminator
    if (input == NULL) {
        printf("Gagal mengalokasikan memori.\n");
        exit(1);
    }
    printf("\t  Masukkan Text : ");
    fgets(input, 1001, stdin); // baca string input dengan fungsi fgets
    input[strcspn(input, "\n")] = '\0'; // hapus karakter newline pada akhir string
    return input;
}


char* read_file(char* input_file) {
    char* text = (char*) malloc(1000 * sizeof(char));
    FILE *file;
    file = fopen(input_file, "r");

    if (file == NULL) {
        printf("File tidak ditemukan\n");
        return;
    }
	fscanf(file, "%[^\n]s", text);
    fclose(file);
	return text;
}

Taddres Build_Huffman(ListQueue *L){
    Taddres root;
    Taddres n1;
    Taddres n2;

    while (L->size > 1)
    {
        // Get first smallest node  
        n1 = peek(*L);
        // Remove a front element
        Deque(&(*L));
        // Get second smallest node
        n2 = peek(*L);
        // Remove a front element
        Deque(&(*L));
        // Make new node using two smallest node
        root = Create_TNode(n1->freq + n2->freq, ' ');
        // Set left and right child
        root->LSon = n1;
        root->RSon = n2;
        // Add new node into priority queue 
        enque(&(*L),root); 
		//Insrt_Node(&(*L), root->freq, root->info);
    }
    return root;
}



// Display Huffman code

void PrintHuffman(Taddres node, char result[], int n, encoding tamp[],int x)
{
    if (node == NULL)
    {
        return;
    }
    if (node->LSon == NULL && node->RSon == NULL)
    {
        result[n] = '\0';
        tamp[x].info = node->info;
        strcpy(tamp[x].value,result);
        printf("\n\t %c = %s", node->info, result);
        x += 1;
        return;
    }
    result[n] = '0';
    PrintHuffman(node->LSon, result, n + 1, tamp, x);
    result[n] = '1';
    PrintHuffman(node->RSon, result, n + 1, tamp, x);
}


void PrintHuffmanHelper(Taddres root,int max_tree){
	
	
    char result[max_tree]; // inisialisasi array result
    encoding tamp[max_tree]; // inisialisasi array tamp
    int n = 0, x = 0; // inisialisasi variabel n dan x

    PrintHuffman(root, result, n, tamp, x); // panggil fungsi rekursif helper

}

void PrintTree(Taddres root, int level) {
    if (root == NULL) {
        return;
    }
    PrintTree(root->RSon, level + 1);
    int i;
    for (i = 0; i < level; i++) {
        printf("    ");
    }
    
    if (root->LSon != NULL && root->RSon != NULL) {
        printf("%d\n", root->freq);
    } else {
        printf("%c:%d\n", root->info, root->freq);
    }
    PrintTree(root->LSon, level + 1);
}

