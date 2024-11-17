#include<iostream>
#include<string>
#include<iomanip>
#include<list>
#include<algorithm>
#include<fstream>
#include<climits>

using namespace std;

class Sinhvien {
private:
    string ten;
    string msv;
    int tuoi;
    float diem;
    
public:
    Sinhvien() {
        ten = "";
        msv = "";
        tuoi = 0;
        diem = 0.0;
    }

    Sinhvien(string ten, string msv, int tuoi, float diem) {
        this->ten = ten;
        this->msv = msv;
        this->tuoi = tuoi;
        this->diem = diem;
    }

    friend istream& operator>>(istream& in, Sinhvien& sv) {
        cout << "Nhap ma sinh vien: ";
        in >> sv.msv;
        in.ignore(); 
        cout << "Nhap ten sinh vien: ";
        getline(in, sv.ten);
        cout << "Nhap tuoi sinh vien: ";
        in >> sv.tuoi;
        cout << "Nhap diem sinh vien: ";
        in >> sv.diem;
        return in;
    }

    friend ostream &operator << (ostream &out, const Sinhvien &sv) {
        out << "| " << setw(9) << left << sv.msv
            << " | " << setw(18) << left << sv.ten
            << " | " << setw(5) << left << sv.tuoi 
            << " | " << setw(15) << right << fixed << setprecision(2) << sv.diem << " | " << endl;
        out << "+-----------+--------------------+-------+-----------------+" << endl;
        return out;
    }

    friend ifstream &operator >> (ifstream &in, Sinhvien &sv){
        getline(in, sv.msv, ',');
        getline(in, sv.ten, ',');
        in >> sv.tuoi;
        in.ignore();
        in >> sv.diem;
        in.ignore();
        return in;
    }

    friend ofstream &operator << (ofstream &out, const Sinhvien &sv){
        out << sv.ten << "," << sv.msv << "," << sv.tuoi << "," << sv.diem << endl;
        return out;
    }

    string getten()const{return ten;}

    string getmsv()const{return msv;}

    float getdiem()const{return diem;}

    int gettuoi()const{return tuoi;}

    bool operator < (const Sinhvien &other)const{
        return ten < other.ten;
    }
};

class Danhsachsinhvien{
private:
    list<Sinhvien> dslist;
public:
    void docfile(const string &filename){
        ifstream file(filename);
        if(!file.is_open()){
            cout << "Khong mo duoc file: " << filename << endl;
            return;
        }
        Sinhvien sv;
        while(file >> sv){
            dslist.push_back(sv);
           
        }
        file.close();
    }
    
    void indssinhvien() const{
        cout << "\nDanh sach sinh vien " << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;
        cout << "| Ma SV     | Ten sinh vien      | Tuoi  | Diem trung binh |" << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;
        for (const auto& sv : dslist) {
            cout << sv;
        }
    }

    void themsinhvien(int n){
        for(int i = 0; i < n; i++){
            Sinhvien sv;
            cout << "\nNhap thong tin sinh vien thu " << (i + 1) << endl;
            cin >> sv;
            dslist.push_back(sv);
        }
        sapxeptheoten();
    }

    void suathongtinsinhvien(const string &msv){
        bool thongtin = false;
        for(auto &sv : dslist){
                if(sv.getmsv() == msv){
                    cout << "Nhap thong tin moi cho sinh vien: " << endl;
                    cin >> sv;
                    thongtin = true;
                    break;
                }
            }
        if(!thongtin){
            cout << "Khong thay thong tin sinh vien voi ma " << msv << endl;
        }
    }

    void xoasinhvien(const string &msv){
        for(auto xoa = dslist.begin(); xoa != dslist.end(); ){
                if(xoa->getmsv() == msv){
                    xoa = dslist.erase(xoa);
                }
                else{
                    ++xoa;
                }
        }
    }

    void timkiemtheokitu(const string &ten){
    	cout << endl;
    	cout << "+-----------+--------------------+-------+-----------------+" << endl;
        cout << "| Ma SV     | Ten sinh vien      | Tuoi  | Diem trung binh |" << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;
        
        for(const auto &sv : dslist){
            if(sv.getten().find(ten) != string::npos){
                cout << sv;
            }
        }

    }
    void timkiemtheomsv(const string &msv){
        cout << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;
        cout << "| Ma SV     | Ten sinh vien      | Tuoi  | Diem trung binh |" << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;
        
        for(const auto &sv : dslist){
            if(sv.getmsv().find(msv) != string::npos){
                cout << sv;
            }
        }
    }
    void timkiemdiem(const float &diem){
        cout << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;
        cout << "| Ma SV     | Ten sinh vien      | Tuoi  | Diem trung binh |" << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;
       
        for(const auto &sv : dslist){
            if(sv.getdiem() == diem){
                cout << sv;
            }
        }
    }
    
    void timkiemsinhvien(){
        int luachon;
        cout << "\nTim kiem danh sach theo?" << endl;
        cout << "\t5.1Tim kiem theo ki tu " << endl;
        cout << "\t5.2Tim kiem theo ma sinh vien " << endl;
        cout << "\t5.3Tim kiem theo diem " << endl;
        cout << "Nhap lua chon: ";
        cin >> luachon;

        switch (luachon){
            case 1:{
                string ten;
                cout << "Nhap ki tu can tim: ";
                cin.ignore();
                getline(cin,ten);
                timkiemtheokitu(ten);
                break;
            }
            case 2:{
                string msv;
                cout << "Nhap ma sinh vien can tim: ";
                cin >> msv;
                timkiemtheomsv(msv);
                break;
            }
            case 3:{
                float diem;
                cout << "Nhap diem can tim: ";
                cin >> diem;
                timkiemdiem(diem);
                break;
            }
            default:{
                cout << "Lua chon khong hop le!" << endl;
                return; 
            }   
        }
    }

   void sapxeptheoten(){
        dslist.sort([](const Sinhvien &a, const Sinhvien &b){
            return a.getten() < b.getten(); 
        });
        indssinhvien();
    }
    void sapxeptheodiem(){
        dslist.sort([](const Sinhvien &a, const Sinhvien &b){
            return a.getdiem() < b.getdiem(); 
        });
        indssinhvien();
    }
    void sapxeptheotuoi(){
        dslist.sort([](const Sinhvien &a, const Sinhvien &b){
            return a.gettuoi() < b.gettuoi(); 
        });
        indssinhvien();
    }
    void sapxeptheomsv(){
        dslist.sort([](const Sinhvien &a, const Sinhvien &b){
            return a.getmsv() < b.getmsv();
        });
        indssinhvien();
    }

    void sapxep(){
        int luachon;
        cout << "Sap xep theo?" << endl;
        cout << "\t6.1 Sap xep theo ten " << endl;
        cout << "\t6.2 Sap xep theo diem " << endl;
        cout << "\t6.3 Sap  xep theo tuoi " << endl;
        cout << "\t6.4 Sap xep theo ma sinh vien" << endl;
        cout << "Nhap lua chon: ";
        cin >> luachon;
        cin.ignore();

        switch (luachon){
            case 1:{
                sapxeptheoten();
                break;
            }
            case 2:{
                sapxeptheodiem();
                break;
            }
            case 3:{
                sapxeptheotuoi();
                break;
            }
            case 4:{
                sapxeptheomsv();
                break;
            }
            default:{
                cout << "Lua chon khong hop le!" << endl;
                return;
            }
        }
    }

    void thongkediemcaonhat() const{
        float maxdiem = INT_MIN;
        for (const auto& sv : dslist){
            if (sv.getdiem() > maxdiem){
                maxdiem = sv.getdiem();
            }
        }
        if (maxdiem == INT_MIN){
            cout << "Khong co sinh vien nao trong danh sach" << endl;
            return;
        }
        cout << "\nSinh vien co diem cao nhat" << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;
        cout << "| Ma SV     | Ten sinh vien      | Tuoi  | Diem trung binh |" << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;

        for (const auto& sv : dslist){
            if (sv.getdiem() == maxdiem){
                cout << sv;
            }
        }
        
    }
    void thongkediemthapnhat() const{
        float mindiem = INT_MAX;
        for (const auto& sv : dslist){
            if (sv.getdiem() < mindiem){
                mindiem = sv.getdiem();
            }
        }
        if (mindiem == INT_MAX){
            cout << "Khong co sinh vien nao trong danh sach" << endl;
            return;
        }
        cout << "\nSinh vien co diem cao nhat" << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;
        cout << "| Ma SV     | Ten sinh vien      | Tuoi  | Diem trung binh |" << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;

        for (const auto& sv : dslist){
            if (sv.getdiem() == mindiem){
                cout << sv;
            }
        }    
    }
    void thongketuoicaonhat() const{
        int maxtuoi = INT_MIN;  
        for (const auto& sv : dslist){
            if (sv.gettuoi() > maxtuoi){
                maxtuoi = sv.gettuoi();
            }
        }
        if (maxtuoi == INT_MIN) {
            cout << "Khong co sinh vien nao trong danh sach" << endl;
            return;
        }
        cout << "\nSinh vien co tuoi lon nhat" << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;
        cout << "| Ma SV     | Ten sinh vien      | Tuoi  | Diem trung binh |" << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;

        for (const auto& sv : dslist){
            if (sv.gettuoi() == maxtuoi){
                cout << sv;
            }
        }
    }
    void thongketuoithapnhat() const{
        int mintuoi = INT_MAX;  
        for (const auto& sv : dslist){
            if (sv.gettuoi() < mintuoi){
                mintuoi = sv.gettuoi();
            }
        }
        if (mintuoi == INT_MAX) {
            cout << "Khong co sinh vien nao trong danh sach" << endl;
            return;
        }
        cout << "\nSinh vien co tuoi thap nhat" << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;
        cout << "| Ma SV     | Ten sinh vien      | Tuoi  | Diem trung binh |" << endl;
        cout << "+-----------+--------------------+-------+-----------------+" << endl;

        for (const auto& sv : dslist){
            if (sv.gettuoi() == mintuoi){
                cout << sv;
            }
        }
    }
    void thongkediemtrungbinh() const{
        if (dslist.empty()){
            cout << "Khong co sinh vien nao trong danh sach de tinh diem trung binh." << endl;
            return;
        }
        float tongdiem = 0.0;
        for (const auto& sv : dslist){
            tongdiem += sv.getdiem();
        }
        
        float diemtrungbinh = tongdiem / dslist.size();
        cout << "Diem trung binh cua danh sach sinh vien la: " << fixed << setprecision(2) << diemtrungbinh << endl;
    }

    void thongkesinhvien(){
        int luachon;
        cout << "Thong ke" << endl;
        cout << "\t7.1 Thong ke diem cao nhat" << endl;
        cout << "\t7.2 Thong ke diem thap nhat" << endl;
        cout << "\t7.3 Thong ke tuoi cao nhat" << endl;
        cout << "\t7.4 Thong ke tuoi thap nhat" << endl;
        cout << "\t7.5 Thong ke diem trung binh" << endl;
        cout << "nhap lua chon: ";
        cin >> luachon;
        cin.ignore();

        switch(luachon){
            case 1:{
                thongkediemcaonhat();
                break;
            }
            case 2:{
                thongkediemthapnhat();
                break;
            }
            case 3:{
                thongketuoicaonhat();
                break;
            }
            case 4:{
                thongketuoithapnhat();
                break;
            }
            case 5:{
                thongkediemtrungbinh();
                break;
            }
            default:{
                cout << "Lua chon khong hop le!" << endl;
                return;
            }
        }
    }

    void luufile(const string &filename)const{
        ofstream file(filename);
        if(!file.is_open()){
            cout << "Khong mo duoc file: " << filename << endl;
            return;
        }

        for(const auto &sv : dslist){
            file << sv;
        }

        file.close();
        cout << "Da luu vao file " << endl;
    }
};

class App{
private:
    Danhsachsinhvien danhsach;
public:
    void menu(){
        int luachon;
        string filename = "sinhvien.txt";
        danhsach.docfile(filename);
        do{
            cout << "\n====== MENU QUAN LY SINH VIEN ======" << endl;
            cout << "1. In danh sach sinh vien" << endl;
            cout << "2. Them sinh vien" << endl;
            cout << "3. Sua thong tin sinh vien" << endl;
            cout << "4. Xoa thong tin sinh vien" << endl;
            cout << "5. Tim kiem sinh vien" << endl;
            cout << "6. Sap xep sinh vien" << endl;
            cout << "7. Thong ke sinh vien" << endl;
            cout << "8. Sao luu danh sach sinh vien" << endl;
            cout << "0. Thoat" << endl;
            cout << "Nhap lua chon: ";
            cin >> luachon;

            switch(luachon){
                case 1:{
                    danhsach.indssinhvien();
                    break;
                }
                case 2:{
                    int n;
                    cout << "Nhap so luong sinh vien: ";
                    cin >> n;
                    danhsach.themsinhvien(n);
                    break;
                }
                case 3:{
                    string msv;
                    cout << "Nhap msv can sua: ";
                    cin >> msv;
                    danhsach.suathongtinsinhvien(msv);
                    break;
                }
                case 4:{
                    string msv;
                    cout << "Nhap ma sinh vien can xoa: ";
                    cin >> msv;
                    danhsach.xoasinhvien(msv);
                    break;
                }
                case 5:{
                    danhsach.timkiemsinhvien();
                    break;
                }   
                case 6:{
                    danhsach.sapxep();
                    break;
                }
                case 7:{
                    danhsach.thongkesinhvien();
                    break;
                }
                case 8:{
                    danhsach.luufile(filename);
                    break;
                }
                case 0:
                    cout << "Thoat chuong trinh!" << endl;
                    break;
                default:
                    cout << "Lua chon khong hop le!" << endl;
            }
        }
        while(luachon != 0);
    }
};
int main() {
    App app;
    app.menu();
    return 0;
}