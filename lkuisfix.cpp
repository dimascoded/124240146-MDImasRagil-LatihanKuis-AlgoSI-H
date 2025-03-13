#include <iostream>
#include <iomanip>
#include <cstring> // Untuk strcmp()
using namespace std;

struct buku
{
    char id[20], judul[30], penulis[30];
    int stok;
};

void baca_data(buku bk[], int &jml_dt)
{
    FILE *hiu = fopen("data.dat", "r"); // mode read untuk membaca data dalam file
    if (hiu == NULL)
    {
        cout << "Tidak bisa membuka data.txt" << endl;
        return;
    }

    jml_dt = 0;
    while (fscanf(hiu, "%s", bk[jml_dt].id) != EOF) // mengambil data dari dalam file
    {
        fscanf(hiu, " %[^\n]", bk[jml_dt].judul);
        fscanf(hiu, " %[^\n]", bk[jml_dt].penulis);
        fscanf(hiu, "%d", &bk[jml_dt].stok);
        jml_dt++;
    }
    fclose(hiu);
}
void tambah_data(buku bk[], int &jml_dt)
{
    cout << "===== Tambah Data Buku =====" << endl;
    cout << "ID buku = ";
    cin.getline(bk[jml_dt].id, 100);
    cout << "Judul buku = ";
    cin.getline(bk[jml_dt].judul, 100);
    cout << "Penulis = ";
    cin.getline(bk[jml_dt].penulis, 100);
    cout << "Stok = ";
    cin >> bk[jml_dt].stok;

    FILE *hiu = fopen("data.dat", "a"); // mode append untuk menambah data ke dalam file tanpa menimpa yang lama
    if (hiu == NULL)
    {
        cout << "Tidak bisa membuka data.txt" << endl;
        exit(1);
    }
    // menyimpan data ke dalam file
    fprintf(hiu, "%s\n%s\n%s\n%d\n", bk[jml_dt].id, bk[jml_dt].judul, bk[jml_dt].penulis, bk[jml_dt].stok);
    fclose(hiu);

    jml_dt++;
}

void tampil_data(buku bk[], int &jml_dt)
{
    baca_data(bk, jml_dt);
    for (int i = 0; i < jml_dt - 1; i++)
    {
        for (int j = i + 1; j < jml_dt; j++)
        {
            if (strcmp(bk[i].id, bk[j].id) > 0)
            {
                swap(bk[i], bk[j]);
            }
        }
    }

    cout << "\n===== Daftar Buku =====\n";
    cout << "+----------------------+-----------------------------+-----------------------------+------+" << endl;
    cout << "| ID Buku              | Judul Buku                  | Penulis                     | Stok |" << endl;
    cout << "+----------------------+-----------------------------+-----------------------------+------+" << endl;
    for (int a = 0; a < jml_dt; a++)
    {
        cout << "| " << setw(21) << left << bk[a].id
             << "| " << setw(28) << left << bk[a].judul
             << "| " << setw(28) << left << bk[a].penulis
             << "| " << setw(4) << right << bk[a].stok << " |" << endl;
    }
    cout << "+----------------------+-----------------------------+-----------------------------+------+" << endl;
}

void cari_data(buku bk[], int &jml_dt)
{
    baca_data(bk, jml_dt);
    string cari;
    bool found = false;

    cout << "Masukkan kata kunci atau awal judul buku yang ingin dicari = ";
    getline(cin, cari);

    cout << "\n===== Hasil Pencarian =====\n";
    cout << "+----------------------+-----------------------------+-----------------------------+------+" << endl;
    cout << "| ID Buku              | Judul Buku                  | Penulis                     | Stok |" << endl;
    cout << "+----------------------+-----------------------------+-----------------------------+------+" << endl;

    for (int i = 0; i < jml_dt; i++)
    {
        if (strstr(bk[i].judul, cari.c_str()) != NULL) // Mencari kata dalam judul buku
        {
            found = true;
            cout << "| " << setw(21) << left << bk[i].id
                 << "| " << setw(28) << left << bk[i].judul
                 << "| " << setw(28) << left << bk[i].penulis
                 << "| " << setw(4) << right << bk[i].stok << " |" << endl;
        }
    }

    cout << "+----------------------+-----------------------------+-----------------------------+------+" << endl;

    if (!found)
    {
        cout << "Tidak ada buku yang mengandung kata \"" << cari << "\" dalam judulnya.\n";
    }
}

void hapus_data(buku bk[], int &jml_dt)
{
    bool found = false;
    string hapus;
    cout << "Masukkan id buku yang ingin dihapus = ";
    cin >> hapus;
    for (int a = 0; a < jml_dt; a++)
    {
        if (hapus == bk[a].id)
        {
            found = true;
            for (int i = a; i < jml_dt - 1; i++)
            {
                bk[i] = bk[i + 1];
            }

            jml_dt--;
            cout << "Data buku dengan nomer id " << hapus << " berhasil dihapus" << endl;
        }
    }
    if (!found)
    {
        cout << "Data buku dengan ID " << hapus << " tidak ditemukan" << endl;
    }
    FILE *hiu = fopen("data.dat", "w"); // Mode "w" untuk menulis ulang file
    if (hiu == NULL)
    {
        cout << "Tidak bisa membuka data.txt" << endl;
        exit(1);
    }

    for (int i = 0; i < jml_dt; i++)
    {
        fprintf(hiu, "%s\n%s\n%s\n%d\n", bk[i].id, bk[i].judul, bk[i].penulis, bk[i].stok);
    }

    fclose(hiu);
}

int main()
{
    buku bk[100];
    int jml_dt = 0;
    int pil;
    string lanjut;
    string nama, pass;

    do
    {
        cout << "Login ke Database Perpustakaan Informatika" << endl;
        cout << "Masukkan username = ";
        cin >> nama;
        cout << "Masukkan password = ";
        cin >> pass;
        if (nama != "ragil" || pass != "146")
            cout << "Username atau Password salah" << endl;
    } while (nama != "ragil" || pass != "146");

    do
    {
        system("cls");
        cout << "Halo, " << nama << "! Selamat Datang di Database Perpustakaan Informatika" << endl;
        cout << "1. Tambah data buku \n2. Tampilkan daftar buku \n3. Cari buku \n4. Hapus buku \n5. Keluar" << endl;
        cout << "Pilihan >> ";
        cin >> pil;
        cin.ignore();

        switch (pil)
        {
        case 1:
            tambah_data(bk, jml_dt);
            break;
        case 2:
            tampil_data(bk, jml_dt);
            break;
        case 3:
            cari_data(bk, jml_dt);
            break;
        case 4:
            hapus_data(bk, jml_dt);
            break;
        case 5:
            cout << "Keluar dari program..." << endl;
            return 0;
        default:
            cout << "Pilihan tidak valid" << endl;
        }

        cout << "Kembali ke menu? (ya/tidak) ";
        cin >> lanjut;
    } while (lanjut == "ya");

    return 0;
}
