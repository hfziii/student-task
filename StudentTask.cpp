#include <iostream>  
#include <fstream> //TULIS BACA FILE (txt) // DATA USER
#include <queue>   //QUEUE - ANTRIAN //MENU TUGAS
#include <string>
#include <cstdlib>   // untuk menggunakan fungsi rand()-RANDOM, dan exit() // CLS()
#include <algorithm> //SORTING

using namespace std;

struct User // MATERI STRUCT - PAGE LOGIN
{
    string username;
    string password;
    User *next;
};

struct mahasiswa // MATERI STRUCT - DATA USER
{
    string nama;
    string npm;
    string semester;
    string program_studi;
};

struct Tugas // MATERI STRUCT - CATATAN TUGAS
{
    string namaMataKuliah;
    string deskripsiTugas;
    string deadline;
};

void garis1()
{
    cout << "================================================================" << endl;
}

void garis2()
{
    cout << "-----------------------------------------------------------------------------------------" << endl;
}

// Login User - LINKED LIST
class UserList //CLASS OBJEK LINKED LIST
{
    private: //DEKLARASI
        User *head;

    public:
        UserList()
        {
            head = nullptr;
        }

        void addUser(string username, string password) //UNTUK MENGISI NILAI
        {
            User *newUser = new User; //pointer
            newUser->username = username;
            newUser->password = password;
            newUser->next = nullptr;

            if (head == nullptr)
            {
                head = newUser;
            }
            else
            {
                User *temp = head;
                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->next = newUser; //MENAMBAHKAN SIMPUL LINKED LIST
            }

            cout << "Sign Up berhasil!" << endl;
        }

        bool authenticate(string username, string password) //VERIFIKASI USERNAME PASSWORD
        {
            User *temp = head;
            while (temp != nullptr)
            {
                if (temp->username == username && temp->password == password)
                {
                    return true; //VERIFAKASI BERHASIL
                }
                temp = temp->next;
            }
            return false; //VERIFIKASI GAGAL
        }
};

//--------------------------------------------------------------------------
//TAMPILAN WELCOME
// Fungsi untuk mencetak ANSI escape sequence
void printEscapeSequence(const string &sequence)
{
    cout << "\033" << sequence;
}

// Fungsi untuk mencetak teks yang ditengah dengan spasi di sekitarnya
void printCenteredText(const string &text, int width)
{
    int textLength = text.length();
    int padding = (width - textLength) / 2;

    cout << string(padding, ' ') << text << endl;
}

// Fungsi untuk mencetak tampilan "Selamat Datang"
void printWelcomeMessage()
{
    int screenWidth = 80; //DEKLARASI UKURAN LAYAR

    printEscapeSequence("[1;34m"); // Mengubah warna teks menjadi kuning BIRU
    cout << endl;
    printCenteredText("- Selamat Datang di StudentTask -", screenWidth);
    cout << endl;
    printCenteredText(" Catat Tugas dengan cepat dan mudah", screenWidth);
    printCenteredText(" Sortir Tugas berdasarkan deadline", screenWidth);
    printCenteredText(" Kerjakan satu atau semua Tugas dengan mudah", screenWidth);
    cout << endl;
    printEscapeSequence("[0m"); // Mengembalikan warna teks ke default
}

//--------------------------------------------------------------------------

// MENU UTAMA
char pil_menu;
void displayMenuUtama()
{
    garis1();
    cout << "\t \t Menu Utama StudentTask:\n";
    garis1();
    cout << "\t1. Mulai StudentTask\n";
    cout << "\t2. Lihat Profile\n";
    cout << "\t3. Edit Profile\n";
    cout << "\t4. Keluar StudentTask\n";
    cout << "\tPilih Menu (1-4): ";
}

// FUNGSI ISI DATA USER (OFSTREAM) //MATERI FUNGSI DAN FILE
void isi_data_mahasiswa(const mahasiswa &mhs, ofstream &file) //FORMAT DI TXT
{ //& MATERI POINTER
    file << "================================================================" << endl;
    file << "\t\t\tProfile Kamu:" << endl;
    file << "================================================================" << endl;
    file << "Nama Lengkap           : " << mhs.nama << endl;
    file << "Nomor Pokok Mahasiswa  : " << mhs.npm << endl;
    file << "Semester               : " << mhs.semester << endl;
    file << "Program Studi          : " << mhs.program_studi << endl;
}

// FUNGSI MENU CATAT TUGAS (QUEUE) //MATERI QUEUE
void displayMenu()
{
    garis1();
    cout << "\t\t\tMenu StudentTask:\n";
    garis1();
    cout << "1. Catat Tugas\n";
    cout << "2. Lihat Catatan Tugas\n";
    cout << "3. Kerjakan Satu Tugas\n";
    cout << "4. Kerjakan Semua Tugas\n";
    cout << "5. Kembali ke Menu Utama\n";
    cout << "6. Urutkan Tugas berdasarkan Deadline (Ascending)\n";
    cout << "7. Kembalikan Urutan Ke Awal (Queue)\n";
    cout << "8. Keluar StudentTask\n";
    cout << "Pilih menu (1-8): ";
}

void inputTugas(queue<Tugas> &tugasQueue)
{ //& MATERI POINTER
    if (tugasQueue.size() >= 10)
    {
        cout << "\nCatatan tugas udah penuh! Ayo mulai kerjain Tugasnya satu-satu!\n";
        return;
    }

    Tugas tugas;
    garis1();
    cout << "\t\t\tCatat Tugas Kamu..." << endl;
    garis1();
    cout << "\nMata Kuliah\t\t: ";
    getline(cin, tugas.namaMataKuliah);
    cout << "\nCatat Deskripsi Tugas\t: ";
    getline(cin, tugas.deskripsiTugas);
    cout << "\nDeadline Tugas (Hari)\t: ";
    getline(cin, tugas.deadline);
    system("CLS");

    tugasQueue.push(tugas);
    cout << "Tugas berhasil dicatat!\n";
    cout << endl;
    cout << endl;
}

void lihatDataTugas(queue<Tugas> tugasQueue)
{
    if (tugasQueue.empty())
    {
        cout << "\nTidak ada tugas yang dicatat!\n";
        return;
    }

    cout << "Catatan Tugas:\n";
    int index = 1;
    while (!tugasQueue.empty())
    {
        Tugas tugas = tugasQueue.front();
        cout << "Tugas Ke-" << index << endl;
        cout << "Nama Mata Kuliah: " << tugas.namaMataKuliah << endl;
        cout << "Deskripsi Tugas: " << tugas.deskripsiTugas << endl;
        cout << "Deadline Tugas: " << tugas.deadline << " Hari" << endl;
        tugasQueue.pop();
        index++;
        cout << endl;
        cout << endl;
    }
}

void hapusSatuDataTugas(queue<Tugas> &tugasQueue)
{ //& MATERI POINTER
    if (tugasQueue.empty())
    {
        cout << "\nTidak ada tugas yang dicatat!\n";
        return;
    }

    cout << "\nTugas yang dikerjakan:\n";
    Tugas tugas = tugasQueue.front();
    cout << "Nama Mata Kuliah: " << tugas.namaMataKuliah << endl;
    cout << "Deskripsi Tugas: " << tugas.deskripsiTugas << endl;
    cout << "Deadline Tugas: " << tugas.deadline << endl
         << endl;
    string quotes[] = {
        // MATERI ARRAY 1 DIMENSI
        // KETIK QUOTES DIBAWAH YAA
        "Ingatlah kehidupan kampus dengan terus mengasah. Jangan habiskan waktumu untuk berkeluh kesah!. -Najwa Sihab-",
        "Pendidikan adalah satu-satunya kunci untuk membuka dunia ini, serta paspor untuk menuju kebebasan. -Oprah Winfrey-",
        "Apabila kamu sudah memutuskan untuk menekuni suatu bidang. Jadilah orang yang konsisten. Itu adalah kunci keberhasilan yang sebenarnya. -BJ Habibie-",
        "Jangan biarkan siapapun mengatakan kau tidak bisa melakukan sesuatu. Kau bermimpi, kau harus menjaganya. Kalau menginginkan sesuatu, raihlah. -Chris Gardner-",
        "Wisuda adalah impian setiap mahasiswa. Namun kita perlu berjuang semester demi semester untuk mewujudkannya. Jangan pernah mengeluh.",
        "Berpikir itu sulit, itulah mengapa kebanyakan orang lebih suka menilai. -Carl Gustav Jung-",
        "Di dunia ini masih banyak yang lebih sulit keadaan nya. Tetapi mengeluhnya tidak seberisik kamu. -RT ZAINUDDIN-",
        "Yang kau sangka bodoh belum tentu dia tidak cerdas, siapa tau dia cermin, menyesuaikan diri dengan yang di hadapinya. -Candra Malik",
        "Setiap kamu ketemu orang baru, jangan lupa selalu kosongkan gelasmu. -Bob Sadino-",
        "Aku rela di penjara asalkan bersama buku, karna dengan buku aku bebas. -Mohammad Hatta-",
    };

    int randomIndex = rand() % 10;
    cout << "\n"
         << quotes[randomIndex] << endl;
    tugasQueue.pop();
}

void hapusSemuaDataTugas(queue<Tugas> &tugasQueue)
{ //& MATERI POINTER
    if (tugasQueue.empty())
    {
        cout << "\nTidak ada data tugas yang tersimpan!\n";
        return;
    }

    while (!tugasQueue.empty())
    {
        tugasQueue.pop();
    }
    cout << "\nSemua data tugas berhasil dikerjakan!\n";
    string quotes[] = {
        // MATERI ARRAY 1 DIMENSI
        // KETIK QUOTES DIBAWAH YAA
        "Ingatlah kehidupan kampus dengan terus mengasah. Jangan habiskan waktumu untuk berkeluh kesah!. -Najwa Sihab-",
        "Pendidikan adalah satu-satunya kunci untuk membuka dunia ini, serta paspor untuk menuju kebebasan. -Oprah Winfrey-",
        "Apabila kamu sudah memutuskan untuk menekuni suatu bidang. Jadilah orang yang konsisten. Itu adalah kunci keberhasilan yang sebenarnya. -BJ Habibie-",
        "Jangan biarkan siapapun mengatakan kau tidak bisa melakukan sesuatu. Kau bermimpi, kau harus menjaganya. Kalau menginginkan sesuatu, raihlah. -Chris Gardner-",
        "Wisuda adalah impian setiap mahasiswa. Namun kita perlu berjuang semester demi semester untuk mewujudkannya. Jangan pernah mengeluh.",
        "Berpikir itu sulit, itulah mengapa kebanyakan orang lebih suka menilai. -Carl Gustav Jung-",
        "Di dunia ini masih banyak yang lebih sulit keadaan nya. Tetapi mengeluhnya tidak seberisik kamu. -RT ZAINUDDIN-",
        "Yang kau sangka bodoh belum tentu dia tidak cerdas, siapa tau dia cermin, menyesuaikan diri dengan yang di hadapinya. -Candra Malik",
        "Setiap kamu ketemu orang baru, jangan lupa selalu kosongkan gelasmu. -Bob Sadino-",
        "Aku rela di penjara asalkan bersama buku, karna dengan buku aku bebas. -Mohammad Hatta-",
    };

    int randomIndex = rand() % 10;
    cout << "\n"
         << quotes[randomIndex] << endl;
}
//--------------------------------------------------------------------------

// SORTING
void sortQueue(queue<Tugas> &tugasQueue)
{
    vector<Tugas> tugasVector;
    while (!tugasQueue.empty())
    {
        tugasVector.push_back(tugasQueue.front());
        tugasQueue.pop();
    }

    // Mengurutkan data dalam vector secara ascending
    sort(tugasVector.begin(), tugasVector.end(), [](const Tugas &a, const Tugas &b)
         { return a.deadline < b.deadline; });

    // Memasukkan data yang sudah diurutkan ke dalam queue
    for (const auto &tugas : tugasVector)
    {
        tugasQueue.push(tugas);
    }
}

void kembalikanUrutanAsli(queue<Tugas> &tugasQueue, const queue<Tugas> &tugasAsli)
{
    tugasQueue = tugasAsli;
}

//--------------------------------------------------------------------------

// MAIN PROGRAM
int main()
{
    char next;
    printWelcomeMessage();
    garis2();

    do
    {
        cout << "\t \t \t Lanjutkan? (y/t): ";
        cin >> next;
        cout << endl;
    } while (next != 'y');

    system("CLS");

    // Mengisi Data Mahasiswa
    UserList userList;
    
    int choice;
    do
    {
        garis1(); //MENU WELCOME (SIGNUP & LOGIN)
        cout << "\t\t\tWelcome!" << endl;
        garis1();
        cout << "1. Sign Up" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Pilih : ";
        cin >> choice;
        system("CLS");

        if (choice == 1)
        {
            string username, password;
            garis1();
            cout << "\t\t\tSign Up" << endl; //PAGE SIGNUP
            garis1();
            cout << "Username \t \t \t: ";
            cin >> username;
            cout << "Password \t \t \t: ";
            cin >> password;
            system("CLS");

            userList.addUser(username, password);
        }
        else if (choice == 2)
        {
            string username, password;
            garis1();
            cout << "\t\t\tLogin" << endl; //PAGE LOGIN
            garis1();
            cout << "Username \t \t \t: ";
            cin >> username;
            cout << "Password \t \t \t: ";
            cin >> password;
            system("CLS");
            bool isAuthenticated = userList.authenticate(username, password);
            if (isAuthenticated)
            {
                cout << "Login berhasil." << endl;
                goto Editprofile1;
            }
            else
            {
                cout << "Username atau password salah." << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "\nTerima kasih telah menggunakan StudentTask. Sampai jumpa!\n";
            exit(0);
        }

    } while (choice != 3);

    cin.ignore(); // Mengabaikan karakter newline (\n) setelah memasukkan pilihan
    
    Editprofile2:
    Editprofile1:
    mahasiswa mhs; // ISI DATA USER
    garis1();
    cin.ignore(); // Mengabaikan karakter newline (\n) setelah memasukkan pilihan
    cout << "\t \t \t Data User" << endl;
    garis1();

    cout << "\nNama Kamu Siapa ? \t \t: ";
    getline(cin, mhs.nama);

    cout << "\nNPM Kamu? \t \t \t: ";
    getline(cin, mhs.npm);

    cout << "\nMahasiswa Semester berapa nih? \t: ";
    getline(cin, mhs.semester);

    cout << "\nAnak Prodi mana nih? \t \t: ";
    getline(cin, mhs.program_studi);
    system("CLS");

    // Memasukan data yg sudah di input ke file //MATERI FUNGSI DAN FILE
    ofstream file_mahasiswa;
    file_mahasiswa.open("data_user_mahasiswa.txt");
    isi_data_mahasiswa(mhs, file_mahasiswa);
    cout << "Data berhasil Disimpan" << endl;
    file_mahasiswa.close();
    //--------------------------------------------------------------------------

    // PILIH MENU UTAMA
    int choice_1;
    MenuUtama:
    do
    {
        displayMenuUtama();
        cin >> choice_1;
        cin.ignore(); // Mengabaikan karakter newline (\n) setelah memasukkan pilihan
        system("CLS");

        switch (choice_1)
        {
        case 1:
        {

            // MENU CATAT TUGAS
            queue<Tugas> tugasQueue;
            queue<Tugas> tugasAsli;
            int choice_2;

            do
            {
                displayMenu();
                cin >> choice_2;
                cin.ignore(); // Mengabaikan karakter newline (\n) setelah memasukkan pilihan
                system("CLS");

                switch (choice_2)
                {
                case 1:
                {
                    inputTugas(tugasQueue);
                    break;
                }

                case 2:
                {
                    lihatDataTugas(tugasQueue);
                    break;
                }
                case 3:
                {
                    hapusSatuDataTugas(tugasQueue);
                    break;
                }
                case 4:
                {
                    hapusSemuaDataTugas(tugasQueue);
                    break;
                }
                case 5:
                {
                    goto MenuUtama;
                    break;
                }
                case 6:
                {
                    tugasAsli = tugasQueue;
                    sortQueue(tugasQueue);
                    cout << "\nTugas berhasil diurutkan berdasarkan deadline! (Ascending)\n";
                    lihatDataTugas(tugasQueue);
                    break;
                }
                case 7:
                {
                    kembalikanUrutanAsli(tugasQueue, tugasAsli);
                    cout << "\nTugas berhasil diurutkan ke antrian awal! (Queue)!\n";
                    lihatDataTugas(tugasQueue);
                    break;
                }
                case 8:
                {
                    cout << "\nTerima kasih telah menggunakan StudentTask. Sampai jumpa!\n";
                    exit(0);
                    break;
                }
                default:
                {
                    cout << "\nPilihan tidak valid. Silakan pilih menu yang sesuai.\n";
                    break;
                }
                }
            } while (choice_2 != 5);
            break;
        }

        case 2:
        {
            /* IFSTREAM */ // MATERI FUNGSI DAN FILE
            ifstream file_mahasiswa;
            file_mahasiswa.open("data_user_mahasiswa.txt");
            system("CLS");
            string line;
            while (getline(file_mahasiswa, line))
            {
                cout << line << endl;
            }
            file_mahasiswa.close();
            break;
        }

        case 3:
        {
            goto Editprofile2;
            break;
        }

        case 4:
        {
            cout << "\nTerima kasih telah menggunakan StudentTask. Sampai jumpa!\n";
            exit(0);
            break;
        }

        default:
        {
            cout << "\nPilihan tidak valid. Silakan pilih menu yang sesuai.\n";
            break;
        }
        }
    } while (choice_1 != 5);

    return 0;
}