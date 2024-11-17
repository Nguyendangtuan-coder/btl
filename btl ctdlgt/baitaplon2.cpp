#include <iostream>

using namespace std;

const int MAXCHAR = 128;

struct Node {
    char kytu;
    int tansuat;
    Node* trai;
    Node* phai;

    Node(char kyTu = '\0', int tanSuat = 0) {
        kytu = kyTu;
        tansuat = tanSuat;
        trai = nullptr;
        phai = nullptr;
    }
};

class HangDoiUuTien {
private:
    Node *nodes[MAXCHAR];
    int size;

public:
    HangDoiUuTien() : size(0) {}

    bool isempty() {
        return size == 0;
    }

    int getsize(){
        return size;
    }

    void push(Node* node) {
        nodes[size++] = node;
        int i = size - 1;
        while (i > 0 && nodes[(i - 1) / 2]->tansuat > nodes[i]->tansuat) {
            swap(nodes[i], nodes[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    Node* pop() {
        if (isempty()) return nullptr;
        Node* a = nodes[0];
        nodes[0] = nodes[--size];
        int i = 0;
        while (2 * i + 1 < size) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < size && nodes[left]->tansuat < nodes[smallest]->tansuat) smallest = left;
            if (right < size && nodes[right]->tansuat < nodes[smallest]->tansuat) smallest = right;

            if (smallest == i) break;

            swap(nodes[i], nodes[smallest]);
            i = smallest;
        }
        return a;
    }
};

class HuffmanTree {
private:
    Node *goc;
    char makytu[MAXCHAR][MAXCHAR];
    int chieudaima[MAXCHAR];

    void ganmakytu(Node *root, char *ma, int chieudai) {
        if (!root) return;

        if (!root->trai && !root->phai) {
            ma[chieudai] = '\0';
            chieudaima[(int)root->kytu] = chieudai;
            for (int i = 0; i < chieudai; i++) {
                makytu[(int)root->kytu][i] = ma[i];
            }
            return;
        }

        ma[chieudai] = '0';
        ganmakytu(root->trai, ma, chieudai + 1);

        ma[chieudai] = '1';
        ganmakytu(root->phai, ma, chieudai + 1);
    }

public:
    HuffmanTree(int tansuatkytu[MAXCHAR]) {
        HangDoiUuTien hangdoi;

        for (int i = 0; i < MAXCHAR; i++) {
            if (tansuatkytu[i] > 0) {
                hangdoi.push(new Node((char)i, tansuatkytu[i]));
            }
        }

        while (hangdoi.getsize() > 1) {
            Node* trai = hangdoi.pop();
            Node* phai = hangdoi.pop();

            Node* tonghop = new Node('\0', trai->tansuat + phai->tansuat);
            tonghop->trai = trai;
            tonghop->phai = phai;

            hangdoi.push(tonghop);
        }

        goc = hangdoi.pop();

        char maTam[MAXCHAR];
        ganmakytu(goc, maTam, 0);
    }

    void mahoa(const char* chuoi, char* ketqua) {
        int index = 0;
        for (int i = 0; chuoi[i] != '\0'; i++) {
            int kyTu = (int)chuoi[i];
            for (int j = 0; j < chieudaima[kyTu]; j++) {
                ketqua[index++] = makytu[kyTu][j];
            }
        }
        ketqua[index] = '\0';
    }

    void giaima(const char* chuoimahoa, char* ketqua) {
        int index = 0;
        Node *hienTai = goc;
        for (int i = 0; chuoimahoa[i] != '\0'; i++) {
            hienTai = (chuoimahoa[i] == '0') ? hienTai->trai : hienTai->phai;

            if (!hienTai->trai && !hienTai->phai) {
                ketqua[index++] = hienTai->kytu;
                hienTai = goc;
            }
        }
        ketqua[index] = '\0';
    }

    ~HuffmanTree() {
        xoaCay(goc);
    }

private:
    void xoaCay(Node *node) {
        if (node) {
            xoaCay(node->trai);
            xoaCay(node->phai);
            delete node;
        }
    }
};

void tinhtansuat(const char* chuoi, int tansuat[MAXCHAR]) {
    for (int i = 0; i < MAXCHAR; i++) tansuat[i] = 0;
    for (int i = 0; chuoi[i] != '\0'; i++) tansuat[(int)chuoi[i]]++;
}

int main() {
    const char* chuoi = "Toi co ma huffman";

    char chuoimahoa[1024];
    char chuoigiaima[1024];

    int tanSuatKyTu[MAXCHAR];
    tinhtansuat(chuoi, tanSuatKyTu);

    HuffmanTree huffman(tanSuatKyTu);

    huffman.mahoa(chuoi, chuoimahoa);
    cout << "Chuoi sau khi ma hoa: " << chuoimahoa << endl;

    huffman.giaima(chuoimahoa, chuoigiaima);
    cout << "Chuoi sau khi giai ma: " << chuoigiaima << endl;

    return 0;
}
