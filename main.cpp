#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void home();
void menu();
void transaksi();

/*
	PEMROGRAMAN BERORIENTASI OBJEK
	Nama			= Rico Putra Anugerah
	NPM				= 20081010024
	Dosen Pengampu	= Wahyu S.J. Saputra, S.Kom, M.Kom
	Materi			= UTS PEMROGRAMAN BERORIENTASI OBJEK C081
*/

class MenuRestoran{
    public:
    int kodeMenu, hargaMenu;
    string namaMenu;

    MenuRestoran(int kode, int harga, string nama){
        
        MenuRestoran::kodeMenu = kode;
        MenuRestoran::hargaMenu = harga;
        MenuRestoran::namaMenu = nama;

    }
};

class Regis{
    public:
    string username, password;

    Regis(string username, string password){

        Regis::username = username;
        Regis::password = password;

    }
};

class DBase{
    public:
        ifstream in;
        ofstream out;
        string fileName;

        DBase(const char* fileName){
            DBase::fileName = fileName;
        }

        void save(Regis data){

            DBase::out.open(this->fileName,ios::app);
            DBase::out << data.username << endl;
            DBase::out << data.password << endl;
            DBase::out.close();

        }

        void login(){

            DBase::in.open(DBase::fileName, ios::in);
            string user, pass;
            string username, password;
            int count = 0;
            login:
            cout << "\n";
            cout << "Halaman Login" << endl;
            cout << "Username : ";
            cin >> user;
            cout << "Password : ";
            cin >> pass;

            while (!DBase::in.eof()){
                
                DBase::in >> username;
                DBase::in >> password;

                if (username==user && password==pass){
                    transaksi();
                }
            }
        }

        void savemenu(MenuRestoran data){

            DBase::out.open(this->fileName,ios::app);
            DBase::out << "\n" << data.kodeMenu << endl;
            DBase::out << data.namaMenu << endl;
            DBase::out << data.hargaMenu;
            DBase::out.close();

        }

        void showAll(){
            DBase::in.open(DBase::fileName, ios::in);
            int kodeMenu, hargaMenu;
            string namaMenu;
            int i = 0;

            while (!DBase::in.eof()){
                DBase::in >> kodeMenu;
                DBase::in >> namaMenu;
                DBase::in >> hargaMenu;
                
                cout << "\n";
                cout << "Menu ke-" << i+1 << endl;
                cout << "Kode Menu  : " << kodeMenu << endl;
                cout << "Nama Menu  : " << namaMenu << endl;
                cout << "Harga Menu : Rp" << hargaMenu << endl;
                i++; 
            }
            DBase::in.close();
        }

        void transaksiUser(){
            cout << "\n";
            cout << "Halo, Selamat Datang di Resto Suka-Suka^^!" << endl;
            cout << "Silahkan mau pesan apa^^!" << endl;
            showAll();
            DBase::in.open(DBase::fileName, ios::in);
            int kodeMenu, hargaMenu;
            string namaMenu;
            int pilih,uang;
            int j = 0;
            
            cout << "\n";
            cout << "Masukkan pilihan Menu yang ingin dipesan : ";
            cin >> pilih;

            while (!DBase::in.eof()){
                DBase::in >> kodeMenu;
                DBase::in >> namaMenu;
                DBase::in >> hargaMenu;

                if ((pilih-1)==j){
                    cout << "\n";
                    cout << "Menu yang anda pilih!!" << endl;
                    cout << "Kode Menu  : " << kodeMenu << endl;
                    cout << "Nama Menu  : " << namaMenu << endl;
                    cout << "Harga Menu : Rp" << hargaMenu << endl;

                    cout << endl;
                    cout << "Halo, Anda harus membayar sebanyak Rp" << hargaMenu << endl;
                    input:
                    cout << "Masukkan uang anda : ";
                    cin >> uang;
                    if (uang >= hargaMenu){
                        cout << "\n";
                        cout << "TERIMA KASIH TELAH BERBELANJA DI RESTO SUKA-SUKA" << endl;
                        cout << "STRUK BELANJA" << endl;
                        cout << "Kode Menu      : " << kodeMenu << endl;
                        cout << "Nama Menu      : " << namaMenu << endl;
                        cout << "Harga Menu     : Rp" << hargaMenu << endl;
                        cout << "Total Harga    : Rp" << hargaMenu << endl;
                        cout << "Bayar          : Rp" << uang << endl;
                        cout << "Kembali        : Rp" << uang-hargaMenu << endl;

                        cout << endl;
                        cout << "Ingin Belanja Lagi?" << endl;
                        cout << "[1]. Ya" << endl;
                        cout << "[2]. Tidak" <<endl;
                        cin >> pilih;
                        if (pilih==1){
                            transaksi();
                        }else{
                            cout << "\n";
                            cout << "Selamat datang kembali wahai pelangganku!!" << endl;
                            exit(0);
                        }
                        
                    }else{
                        cout << "\n";
                        cout << "Mohon maaf, uang anda kurang! silakan input uang anda lagi!" << endl;
                        goto input;
                    }
                }
                j++;
            }
        }
};

int main(int argc, char const *argv[]){

    home();
	return 0;

}

void regis(){

    DBase databaseUser = DBase("DatabaseUser.txt");
    string regUser, regPass;
    cout << "\n";
    cout << "Halaman Regis" << endl;
    cout << "Username : ";
    cin >> regUser;
    cout << "Password : ";
    cin >> regPass;

    Regis regisUser = Regis(regUser,regPass);
    
    databaseUser.save(regisUser);
}

void menu(){

    int menuCode, menuPrice;
    string menuName;
    int pilih;
    DBase databaseUser = DBase("DatabaseMenu.txt");

    cout << "\n";
    cout << "Halo Admin! Hari ini mau ngelola apa nih?" << endl;
    cout << "[1]. Insert Menu Baru" << endl;
    cout << "[2]. Lihat Menu Terkini" << endl;
    cin >> pilih;

    switch (pilih){
        case 1:{
            cout << "HALAMAN INSERT MENU" << endl;
            cout << "Masukkan Kode Menu : ";
            cin >> menuCode;
            cout << "Masukkan Nama Menu : ";
            cin >> menuName;
            cout << "Masukkan Harga Menu : ";
            cin >> menuPrice;

            MenuRestoran Menu = MenuRestoran(menuCode,menuPrice,menuName);
            databaseUser.savemenu(Menu);
            cout << "Data Tersimpan!!" << endl;
            break;
        }
        case 2:{
            cout << "LIST MENU TERKINI" << endl;
            databaseUser.showAll();
            break;
        }
    
    }
}

void home(){

    DBase databaseLogin = DBase("DatabaseUser.txt");

    int pilih;
    string user, pass;
    string userAdmin, passAdmin;
    int count = 0;

    userAdmin = "username";
    passAdmin = "password";

    cout << "\n";
    cout << "Halo selamat datang di Resto Suka-Suka^^!" << endl;
    cout << "Silahkan Login dulu yaaa!!" << endl;
    cout << "Login as" << endl;
    cout << "[1]. User" << endl;
    cout << "[2]. Admin" << endl;
    cout << "Masukkan pilihan anda : ";
    cin >> pilih;
    switch (pilih){
        
        case 1:{
            cout << "\n";
            cout << "Sudah punya akun atau belum?" << endl;
            cout << "[1]. Belum, Gas Daftar!" << endl;
            cout << "[2]. Sudah, Yok Login!" << endl;
            cout << "Masukkan pilihan anda : ";
            cin >> pilih;
            if (pilih==1){
                regis();
                cout << "\n";
                cout << "Yuk Login!" << endl;
                databaseLogin.login();

            }else{
                databaseLogin.login();
            }
        break;
        }

        case 2:{
            loginAdmin:
            cout << "\n";
            cout << "HALAMAN LOGIN" << endl;
            cout << "Username   : ";
            cin >> user;
            cout << "Password   : ";
            cin >> pass;
            if (user==userAdmin && pass==passAdmin){
                menu();
            }else{
                count++;
                if (count==3){
                    cout << "\n";
                    cout << "Sudah salah 3x nih, harap mulai dari awal ya!^^";
                    exit(0);
                }
                goto loginAdmin;
            }
        break;
        }

        default:{
        break;
        }
    }

}

void transaksi(){
    
    DBase databaseUser = DBase("DatabaseMenu.txt");
    databaseUser.transaksiUser();

}