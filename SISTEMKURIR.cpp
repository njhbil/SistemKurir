#include <iostream>
using namespace std;

struct paket {
    string noResi;
    string pengirim;
    string penerima;
    string alamatAsal;
    string alamatTujuan;
    string jenisPengiriman;
    float berat;
    int attempCount;
    string status;
};

struct TNode {
    paket* data;
    TNode* next;
    TNode* prev;
};

struct Kurir {
    string id_kurir;
    string nama;
    string password;
    string lokasi;
    int jumlahPaket; 
    float beratTotal; 
    string statusKurir;
    TNode* daftarPaket;
};

struct verifikasiAdmin {
    TNode* verifikasiData;
};

struct verifikasiAdminNode {
    TNode* data;
    verifikasiAdminNode* next;
};

struct paketGagal {
    TNode* dataPaketGagal;
};

struct paketGagalNode {
    TNode* data;
    paketGagalNode* next;
};

struct kurirNode {
    Kurir* data;
    kurirNode* next;
};

struct daftarPaketNode {
    TNode* data;
    daftarPaketNode* next;
};

struct RiwayatNode {
    paket* data;
    RiwayatNode* next;
};

int main ();
void admin(TNode*& head, TNode*& tail) ;

TNode* head = nullptr;
TNode* tail = nullptr;

kurirNode* headKurir = nullptr;
kurirNode* tailKurir = nullptr;

daftarPaketNode* headDaftarPaket = nullptr;
daftarPaketNode* tailDaftarPaket = nullptr;

verifikasiAdminNode* headVerifikasiAdmin = nullptr;
verifikasiAdminNode* tailVerifikasiAdmin = nullptr;

paketGagalNode* headPaketGagal = nullptr;
paketGagalNode* tailPaketGagal = nullptr;

RiwayatNode* headRiwayat = nullptr;

struct ResiNode {
    string noResi;
    ResiNode* next;
};

ResiNode* resiHead = nullptr;

string toUpperString(const string& str) {
    string result = str;
    for (char& c : result) {
        if (c >= 'a' && c <= 'z') {
            c = c - 32;
        }
    }
    return result;
}

string toLowerString(const string& str) {
    string result = str;
    for (char& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c = c + 32;
        }
    }
    return result;
}

bool isNomorResiTerdaftar(const string& nomorResi) {
    ResiNode* current = resiHead;
    while (current != nullptr) {
        if (current->noResi == nomorResi) {
            return true;
        }
        current = current->next;
    } return 
    false;
}

void tambahNomorResi(const string& nomorResi) {
    ResiNode* newNode = new ResiNode();
    newNode->noResi = nomorResi;
    newNode->next = resiHead;
    resiHead = newNode;
}


string noResi(string alamatAsal, string alamatTujuan, float berat, string jenisPengiriman) {
    char hurufPertamaA = toupper(alamatAsal[0]);
    char hurufTerakhirA = toupper(alamatAsal.back());
    int kodePertamaAsal = static_cast<int>(hurufPertamaA);
    int kodeTerakhirAsal = static_cast<int>(hurufTerakhirA);
    int kodeKotaAsal;
    if (kodePertamaAsal-kodeTerakhirAsal < 0) {
        kodeKotaAsal = (kodePertamaAsal - kodeTerakhirAsal);
        kodeKotaAsal *= -1;
        kodeKotaAsal = kodeKotaAsal % 99;
    } else {
        kodeKotaAsal = int(kodePertamaAsal - kodeTerakhirAsal) % 99;
    }
    string kodeKotaAsalString = (kodeKotaAsal < 10) ? "0" + to_string(kodeKotaAsal) : to_string(kodeKotaAsal);

    char hurufPertamaB = toupper(alamatTujuan[0]);
    char hurufTerakhirB = toupper(alamatTujuan.back());
    int kodePertamaTujuan = static_cast<int>(hurufPertamaB);
    int kodeTerakhirTujuan = static_cast<int>(hurufTerakhirB);
    int kodeKotaTujuan;
    if (kodePertamaTujuan-kodeTerakhirTujuan < 0) {
        kodeKotaTujuan = (kodePertamaTujuan - kodeTerakhirTujuan);
        kodeKotaTujuan *= -1;
        kodeKotaTujuan = kodeKotaTujuan % 99;
    } else {
        kodeKotaTujuan = int(kodePertamaTujuan - kodeTerakhirTujuan) % 99;
    }
    string kodeKotaTujuanString = (kodeKotaTujuan < 10) ? "0" + to_string(kodeKotaTujuan) : to_string(kodeKotaTujuan);
    string kodeKota = kodeKotaAsalString + kodeKotaTujuanString;

    string beratS = to_string(berat);
    size_t lokasiTitik = beratS.find('.');
    char kodeBerat = '0';
    if (lokasiTitik != string::npos && lokasiTitik > 0) {
        kodeBerat = beratS[lokasiTitik - 1];
    }

    string kodeJenisPengiriman;
    if (jenisPengiriman == "Ekonomi") {
        kodeJenisPengiriman = "01";
    } else if (jenisPengiriman == "Reguler") {
        kodeJenisPengiriman = "02";
    } else if (jenisPengiriman == "Express") {
        kodeJenisPengiriman = "03";
    } else {
        cout << "Masukan Anda Tidak Sesuai";
        return "";
    }

    string noResiSementara = kodeKota + kodeBerat + kodeJenisPengiriman;

    int digitUnik = 0;
    while (true) {
        string noResiFinal = noResiSementara + to_string(digitUnik);

        if (!isNomorResiTerdaftar(noResiFinal)) {
            tambahNomorResi(noResiFinal);
            return noResiFinal;
        }
        digitUnik++;
    }

    cout << "Tidak dapat menghasilkan nomor resi unik!" << endl;
    return "";
}

void statusPaket(string status, TNode*& head, TNode*& tail, kurirNode*& headKurir, kurirNode*& tailKurir, daftarPaketNode*& headDaftarPaket, daftarPaketNode*& tailDaftarPaket) {
    if (status == "Selesai") {
        TNode* bantu = head;
        kurirNode* bantu1 = headKurir;
        daftarPaketNode* bantu2 = headDaftarPaket;
        int statusSelesai = 0;
        if (head != nullptr) {
            do {
                if (bantu->data->status == "Selesai") {
                    statusSelesai++;
                }
            } while (bantu != head);
        }
    } else if (status == "Gagal Dikirim") {
        cout << "Status Paket : Gagal Dikirim" << endl;
    } 
}

void tambahPaket(TNode*& head, TNode*& tail, string noResi, string pengirim, string penerima, string alamatAsal, string alamatTujuan, string jenisPengiriman, float berat, string status) {
    paket* dataPaketBaru = new paket();
    dataPaketBaru->noResi = noResi;
    dataPaketBaru->pengirim = pengirim;
    dataPaketBaru->penerima = penerima;
    dataPaketBaru->alamatAsal = alamatAsal;
    dataPaketBaru->alamatTujuan = alamatTujuan;
    dataPaketBaru->jenisPengiriman = jenisPengiriman;
    dataPaketBaru->berat = berat;
    dataPaketBaru->status = status;

    TNode* paketBaru = new TNode;
    paketBaru->data = dataPaketBaru;
    paketBaru->next = nullptr;
    paketBaru->prev = nullptr;

    if (head == nullptr) {
        head = paketBaru;
        tail = paketBaru;
        head->next = head;
        head->prev = head;
    } else {
        tail->next = paketBaru;
        paketBaru->prev = tail;
        paketBaru->next = head;
        head->prev = paketBaru;
        tail = paketBaru;
    }
}

void tampilkanData(TNode*& head, TNode*& tail) {
    TNode* bantu = head;
     if (head != nullptr) {
        do {
            cout << "Menampilkan Paket ..." << endl << endl;
            cout << "No Resi          : " << bantu->data->noResi << endl;
            cout << "Pengirim         : " << bantu->data->pengirim << endl;
            cout << "Penerima         : " << bantu->data->penerima << endl;
            cout << "Alamat Tujuan    : " << bantu->data->alamatTujuan << endl;
            cout << "Status           : " << bantu->data->status << endl << endl;
            cout << "1. Next" << endl;
            cout << "2. Previous" << endl;
            cout << "3. Kembali" << endl;
            cout << "Pilih : ";
            int pil;
            cin >> pil;
            if (pil == 1) {
                bantu = bantu->next;
            } else if (pil == 2) {
                bantu = bantu->prev;
            } else if (pil == 3) {
                return;
            } else {
                cout << "Silahkan Masukan yang benar" << endl;
            }
        } while (true); 
    } else {
        cout << "Tidak ada data paket." << endl;
    }
}

void tambahDataPaket(TNode*& head, TNode*& tail) {
    string pengirim;
    string penerima;
    string alamatAsal;
    string alamatTujuan;
    string jenisPengiriman;
    float berat;

    cout << "=================================" << endl;
    cout << "|        Masukan Data Paket      |" << endl;
    cout << "=================================" << endl;
    cout << "Nama Pengirim: ";
    cin.ignore();
    getline(cin, pengirim);
    pengirim = toUpperString(pengirim);
    cout << "Nama Penerima: ";
    getline(cin, penerima);
    penerima = toUpperString(penerima);
    cout << "Alamat Asal: ";
    getline(cin, alamatAsal);
    alamatAsal = toUpperString(alamatAsal);
    cout << "Alamat Tujuan: ";
    getline(cin, alamatTujuan);
    alamatTujuan = toUpperString(alamatTujuan);
    cout << "Berat: ";
    cin >> berat;

    while (true) {
        cout << "Pilih jenis pengiriman: " << endl;
        cout << "1 = Ekonomi" << endl;
        cout << "2 = Reguler" << endl;
        cout << "3 = Express" << endl;
        int pilihan;
        cin >> pilihan;
        if (pilihan == 1) {
            jenisPengiriman = "Ekonomi";
            break;
        } else if (pilihan == 2) {
            jenisPengiriman = "Reguler";
            break;
        } else if (pilihan == 3) {
            jenisPengiriman = "Express";
            break;
        } else {
            cout << "Masukan Anda Tidak Sesuai. Silakan coba lagi." << endl;
        }
    }

    string noResiPaket = noResi(alamatAsal, alamatTujuan, berat, jenisPengiriman);
    string status = "Dalam Proses";
    tambahPaket(head, tail, noResiPaket, pengirim, penerima, alamatAsal, alamatTujuan, jenisPengiriman, berat, status);
    cout << endl << "=================================" << endl;
    cout << "| Data Berhasil dimasukan       |" << endl;
    cout << "=================================" << endl;
}
void ubahData(TNode*& head, TNode*& tail) {
    string nomorResi;
    cout << "Masukan nomor resi: ";
    cin >> nomorResi;
    TNode* bantu = head;
    bool found = false;
    if (head != nullptr) {
        do {
            if (bantu->data->noResi == nomorResi) {
                found = true;
                break;
            }
            bantu = bantu->next;
        } while (bantu != head);
    }

    if (!found) {
        cout << "Nomor resi tidak ditemukan." << endl;
        return;
    }

    int ubah;
    while (true) {
        cout << "Pilih data yang akan diubah:" << endl;
        cout << "1. Nama Pengirim" << endl;
        cout << "2. Nama Penerima" << endl;
        cout << "3. Alamat Asal" << endl;
        cout << "4. Alamat Tujuan" << endl;
        cout << "5. Berat Paket" << endl;
        cout << "6. Jenis Pengiriman" << endl;
        cout << "Pilih : ";
        cin >> ubah;
        cin.ignore(); 

        if (ubah >= 1 && ubah <= 6) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }

    if (ubah == 1) {
        string ubahNama;
        cout << "Masukan Nama Pengirim baru: ";
        getline(cin, ubahNama);
        ubahNama = toUpperString(ubahNama);
        bantu->data->pengirim = ubahNama;
    } else if (ubah == 2) {
        string ubahNama;
        cout << "Masukan Nama Penerima baru: ";
        getline(cin, ubahNama);
        ubahNama = toUpperString(ubahNama);
        bantu->data->penerima = ubahNama;
    } else if (ubah == 3) {
        string ubahAlamat;
        cout << "Masukan Alamat Asal baru: ";
        getline(cin, ubahAlamat);
        ubahAlamat = toUpperString(ubahAlamat);
        bantu->data->alamatAsal = ubahAlamat;
    } else if (ubah == 4) {
        string ubahAlamat;
        cout << "Masukan Alamat Tujuan baru: ";
        getline(cin, ubahAlamat);
        ubahAlamat = toUpperString(ubahAlamat);
        bantu->data->alamatTujuan = ubahAlamat;
    } else if (ubah == 5) {
        float ubahBerat;
        cout << "Masukan Berat Paket baru: ";
        cin >> ubahBerat;
        bantu->data->berat = ubahBerat;
    } else if (ubah == 6) {
        string ubahJenis;
        cout << "Masukan Jenis Pengiriman baru: ";
        getline(cin, ubahJenis);
        bantu->data->jenisPengiriman = ubahJenis;
    }
    string newResi= noResi(bantu->data->alamatAsal, bantu->data->alamatTujuan, bantu->data->berat, bantu->data->jenisPengiriman);
    bantu->data->noResi = newResi;
    cout << "Data berhasil diubah." << endl;
}

void ubahStatus(TNode*& head, TNode*& tail) {
    string nomorResi;
    cout << "Masukan nomor resi: ";
    cin >> nomorResi;
    TNode* bantu = head;
    bool found = false;
    if (head != nullptr) {
        do {
            if (bantu->data->noResi == nomorResi) {
                found = true;
                break;
            }
            bantu = bantu->next;
        } while (bantu != head);
    }

    if (!found) {
        cout << "Nomor resi tidak ditemukan." << endl;
        return;
    }
    if (bantu->data->status == "Dalam Proses") {
        int pilstatus;
        cout << "Ubah status Paket ke-: " << endl;
        cout << "1. Dikirim" << endl;
        cout << "2. Sedang Diantar" << endl;
        cin >> pilstatus;
        if (pilstatus == 1) {
            bantu->data->status = "Dikirim";
        } else if (pilstatus == 2) {
            bantu->data->status = "Sedang Diantar";
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    } else if(bantu->data->status == "Dikirim") {
        int pilstatus;
        cout << "Ubah status Paket ke-: " << endl;
        cout << "1. Sedang Diantar" << endl;
        cin >> pilstatus;
        if (pilstatus == 1) {
            bantu->data->status = "Sedang Diantar";
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    } else {
        cout << "Status paket tidak dapat diubah." << endl;
    }
}

void hapusPaket(TNode*& head, TNode*& tail) {
    string nomorResi;
    cout << "Masukan nomor resi: ";
    cin >> nomorResi;

    TNode* bantu = head;
    bool found = false;
    if (head != nullptr) {
        do {
            if (bantu->data->noResi == nomorResi) {
                found = true;
                break;
            }
            bantu = bantu->next;
        } while (bantu != head);
    }

    if (!found) {
        cout << "Nomor resi tidak ditemukan." << endl;
        return;
    }

    if (bantu == head) {
        if (head->next == head) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = tail;
            tail->next = head;
        }
    } else if (bantu == tail) {
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
    } else {
        bantu->prev->next = bantu->next;
        bantu->next->prev = bantu->prev;
    }

    delete bantu->data;
    delete bantu;
    cout << "Paket berhasil dihapus." << endl;
}

string idKurir (string nama, string lokasi){
    string kodeLokasi = lokasi.substr(lokasi.length() - 2, 2);
  
    char huruf1  = nama [0] ;
    char huruf2  = nama [1] ;  
    int kodeNamaA = static_cast<int> (huruf1);
    int kodeNamaB = static_cast<int> (huruf2);
    int kodeNama = (kodeNamaA - kodeNamaB);
    if (kodeNama < 0) {
        kodeNama *= -1; 
    }
    string finalKodeNama = (kodeNama < 10) ? "0" + to_string(kodeNama) : to_string(kodeNama);
   
    srand(time(0));
     int random = rand() % 100;

    const string randomStr = (random < 10) ? "0" + to_string(random) : to_string(random);

    const string id_kurir = kodeLokasi + finalKodeNama + randomStr;
    return id_kurir;
}

void tambahkanKurir(kurirNode*& headKurir, kurirNode*& tailKurir) {
    string namaKurir;
    string lokasiKurir;
    string password;

    cout << "=================================" << endl;
    cout << "|        Data Kurir             |" << endl;
    cout << "=================================" << endl << endl;
    cout << "Masukan Nama Kurir : ";
    cin.ignore();
    getline(cin, namaKurir);
    namaKurir = toUpperString(namaKurir);
    cout << "Masukan Lokasi Kurir: ";
    getline(cin, lokasiKurir);
    lokasiKurir = toUpperString(lokasiKurir);
    cout << "Masukan Password: ";
    getline(cin, password);
    string id_kurir = idKurir(namaKurir, lokasiKurir);
    cout << endl << "=================================" << endl;
    cout << "| Kurir Berhasil Ditambahkan    |" << endl;
    cout << "| dengan ID: " << id_kurir << "         |" << endl;
    cout << "=================================" << endl;
    cout << "| Kurir telah berhasil          |" << endl;
    cout << "| ditambahkan dalam antrian     |" << endl;
    cout << "| kurir " << lokasiKurir << "              |" << endl;
    cout << "=================================" << endl << endl;

    Kurir* dataKurir = new Kurir;
    dataKurir->id_kurir = id_kurir;
    dataKurir->nama = namaKurir;
    dataKurir->password = password;
    dataKurir->lokasi = lokasiKurir;
    dataKurir->jumlahPaket = 0; 
    dataKurir->beratTotal = 0;

    kurirNode* newNode = new kurirNode();
    newNode->data = dataKurir;
    newNode->next = nullptr;

    if (headKurir == nullptr) {
        headKurir = newNode;
        tailKurir = newNode;
    } else {
        tailKurir->next = newNode;
        tailKurir = newNode;
    }
}

bool isKurirAvailable(Kurir* kurir, float beratPaket) {
    if (kurir->jumlahPaket < 5 && (kurir->beratTotal + beratPaket) <= 20) {
        return true;
    }
    return false;
}

bool assignPaketToKurir(Kurir* kurir, float beratPaket, TNode*& head, TNode*& tail, kurirNode*& headKurir, kurirNode*& tailKurir) {
    if (beratPaket > 20 || kurir->jumlahPaket > 5 ) {
        return false; 
    }
    return true;
}

void daftarPaket(TNode* paket) {
    daftarPaketNode* newDaftarPaket = new daftarPaketNode();
    newDaftarPaket->data = paket;
    newDaftarPaket->next = headDaftarPaket;

    if (headDaftarPaket == nullptr) {
        headDaftarPaket = newDaftarPaket;
        tailDaftarPaket = newDaftarPaket;
    } else {
        tailDaftarPaket->next = newDaftarPaket;
        tailDaftarPaket = newDaftarPaket;
    }
}

void hapusDaftarPaket(daftarPaketNode*& headDaftarPaket, daftarPaketNode*& tailDaftarPaket, TNode* paket) {
    if (headDaftarPaket == nullptr || paket == nullptr) {
        cout << "Daftar paket kosong atau paket tidak valid." << endl;
        return;
    }

    daftarPaketNode* bantu = headDaftarPaket;
    daftarPaketNode* prev = nullptr;

    while (bantu != nullptr) {
        if (bantu->data == paket) {
            if (prev == nullptr) {
                headDaftarPaket = bantu->next;
                if (headDaftarPaket == nullptr) {
                    tailDaftarPaket = nullptr;
                }
            } else {
                prev->next = bantu->next;
            }
            if (bantu == tailDaftarPaket) {
                tailDaftarPaket = prev;
            }
            
            delete bantu;
            return;
        }
        prev = bantu;
        bantu = bantu->next;
    }

    cout << "Paket tidak ditemukan dalam daftar kurir." << endl;
}

void hapusVerifikasiAdmin(verifikasiAdminNode*& headVerifikasiAdmin, verifikasiAdminNode*& tailVerifikasiAdmin, TNode* paket) {
    if (headVerifikasiAdmin == nullptr || paket == nullptr) {
        cout << "Daftar paket kosong atau paket tidak valid." << endl;
        return;
    }

    verifikasiAdminNode* bantu = headVerifikasiAdmin;
    verifikasiAdminNode* prev = nullptr;

    while (bantu != nullptr) {
        if (bantu->data == paket) {
            if (prev == nullptr) {
                headVerifikasiAdmin = bantu->next;
                if (headVerifikasiAdmin == nullptr) {
                    tailVerifikasiAdmin = nullptr;
                }
            } else {
                prev->next = bantu->next;
            }
            if (bantu == tailVerifikasiAdmin) {
                tailVerifikasiAdmin = prev;
            }
            
            delete bantu;
            return;
        }
        prev = bantu;
        bantu = bantu->next;
    }

    cout << "Paket tidak ditemukan dalam daftar kurir." << endl;
}

void hapusPaketGagal(paketGagalNode*& headPaketGagal, paketGagalNode*& tailPaketGagal, TNode* paket) {
    if (headPaketGagal == nullptr || paket == nullptr) {
        cout << "Daftar paket kosong atau paket tidak valid." << endl;
        return;
    }

    paketGagalNode* bantu = headPaketGagal;
    paketGagalNode* prev = nullptr;

    while (bantu != nullptr) {
        if (bantu->data == paket) {
            if (prev == nullptr) {
                headPaketGagal = bantu->next;
                if (headPaketGagal == nullptr) {
                    tailPaketGagal = nullptr;
                }
            } else {
                prev->next = bantu->next;
            }
            if (bantu == tailPaketGagal) {
                tailPaketGagal = prev;
            }
            
            delete bantu;
            return;
        }
        prev = bantu;
        bantu = bantu->next;
    }

    cout << "Paket tidak ditemukan dalam daftar kurir." << endl;
}

void kurir ();

void temukanKurir(TNode*& head, TNode*& tail, kurirNode*& headKurir, kurirNode*& tailKurir) {
    TNode* bantu = head;
    cout << "Daftar Paket :" << endl;
    int i = 1;
    bool tidakAdaPaket = true ;


    do {
        if (bantu->data->jenisPengiriman == "Express" && bantu->data->status != "Sedang Diantar" && bantu->data->status != "Selesai" && bantu->data->status != "Gagal Dikirim" && bantu->data->status != "Menunggu Verifikasi") {
            cout << i << ". " << bantu->data->noResi ;
            cout << " - Tujuan : " << bantu->data->alamatTujuan;
            cout << " - Berat  : " << bantu->data->berat << endl;
            i++;
            tidakAdaPaket = false ;
        }
        bantu = bantu->next;
        
    } while (bantu != head);
    do {
        if (bantu->data->jenisPengiriman == "Reguler" && bantu->data->status != "Sedang Diantar"&& bantu->data->status != "Selesai" && bantu->data->status != "Gagal Dikirim" && bantu->data->status != "Menunggu Verifikasi") {
            cout << i << ". " << bantu->data->noResi ;
            cout << " - Tujuan : " << bantu->data->alamatTujuan;
            cout << " - Berat  : " << bantu->data->berat << endl;
            i++;
            tidakAdaPaket = false ;
        }
        bantu = bantu->next;
    } while (bantu != head);

    do {
        if (bantu->data->jenisPengiriman == "Ekonomi" && bantu->data->status != "Sedang Diantar"&& bantu->data->status != "Selesai" && bantu->data->status != "Gagal Dikirim" && bantu->data->status != "Menunggu Verifikasi") {
            cout << i << ". " << bantu->data->noResi ;
            cout << " - Tujuan : " << bantu->data->alamatTujuan;
            cout << " - Berat  : " << bantu->data->berat << endl;
            i++;
            tidakAdaPaket = false ;
        }
        bantu = bantu->next;
    } while (bantu != head);

    
 
    if (tidakAdaPaket){
        cout << "Tidak ada paket yang perlu dikirim";
        return;
    }

    string jawaban;
    cout << "Berikan Kepada Kurir (y/n) : ";
    cin >> jawaban;

    if (jawaban == "y") {
        bantu = head;
        kurirNode* bantu1 = headKurir;
        bool kurirFound = false;

        do {
            if (bantu->data->attempCount<=3 && bantu->data->jenisPengiriman == "Express" && bantu->data->status != "Sedang Diantar"&& bantu->data->status != "Selesai" && bantu->data->status != "Gagal Dikirim" &&bantu->data->status != "Menunggu Verifikasi") {    
                while (bantu1 != nullptr) {
                    if (bantu1->data->lokasi == bantu->data->alamatTujuan && isKurirAvailable(bantu1->data, bantu->data->berat)) {
                        kurirFound = true; 
                        break;

                    }
                    bantu1 = bantu1->next;
                    
                }
                    
                if (kurirFound) {
                    if (assignPaketToKurir(bantu1->data, bantu->data->berat, head, tail, headKurir, tailKurir)) {
                        cout << "Kurir ditemukan : " << bantu1->data->nama << " (" << bantu1->data->id_kurir << ")" << endl;
                        bantu->data->status = "Sedang Diantar";
                        bantu->data->attempCount++;
                        cout << "Paket dengan resi " << bantu->data->noResi << " telah ditugaskan ke Kurir " << bantu1->data->nama << endl;
                        TNode* paketBaru = new TNode;   
                        paketBaru->data = bantu->data;
                        paketBaru->next = bantu1->data->daftarPaket;
                        bantu1->data->daftarPaket = paketBaru;
                        bantu1->data->jumlahPaket++;
                        bantu1->data->beratTotal += bantu->data->berat;
                        cout << "Kurir sekarang membawa " << bantu1->data->jumlahPaket << "/5 paket" << endl;
                        return; 
                    } else {
                        cout << "Kurir tidak dapat menangani paket ini." << endl;
                        return ;
                    }
                } else {
                    cout << "Tidak ada kurir yang tersedia untuk menerima paket ini." << endl;
                    return ;
                }
            }
            bantu = bantu->next;
        } while (bantu != head);
   
 
        do {
            if (bantu->data->attempCount<=3 && bantu->data->jenisPengiriman == "Reguler" && bantu->data->status != "Sedang Diantar"&& bantu->data->status != "Selesai" && bantu->data->status != "Gagal Dikirim" &&bantu->data->status != "Menunggu Verifikasi") {
                while (bantu1 != nullptr) {
                    if (bantu1->data->lokasi == bantu->data->alamatTujuan && isKurirAvailable(bantu1->data, bantu->data->berat)) {
                        kurirFound = true;
                        break;
                    }
                    bantu1 = bantu1->next;
                }

                if (kurirFound) {
                    if (assignPaketToKurir(bantu1->data, bantu->data->berat, head, tail, headKurir, tailKurir)) {
                        cout << "Kurir ditemukan : " << bantu1->data->nama << " (" << bantu1->data->id_kurir << ")" << endl;
                        bantu->data->status = "Sedang Diantar";
                        bantu->data->attempCount++;
                        cout << "Paket dengan resi " << bantu->data->noResi << " telah ditugaskan ke Kurir " << bantu1->data->nama << endl;
                        TNode* paketBaru = new TNode;
                        paketBaru->data = bantu->data;
                        paketBaru->next = bantu1->data->daftarPaket;
                        bantu1->data->daftarPaket = paketBaru;
                        bantu1->data->jumlahPaket++;
                        bantu1->data->beratTotal += bantu->data->berat;
                        cout << "Kurir sekarang membawa " << bantu1->data->jumlahPaket << "/5 paket" << endl;
                        return; 
                    } else {
                        cout << "Kurir tidak dapat menangani paket ini." << endl;
                        return ;
                    }
                } else {
                    cout << "Tidak ada kurir yang tersedia untuk menerima paket ini." << endl;
                    return ;
                }
            }
            bantu = bantu->next;
        } while (bantu != head);
    


        do {
            if (bantu->data->attempCount<=3 && bantu->data->jenisPengiriman == "Ekonomi" && bantu->data->status != "Sedang Diantar"&& bantu->data->status != "Selesai" && bantu->data->status != "Gagal Dikirim" &&bantu->data->status != "Menunggu Verifikasi") {
                while (bantu1 != nullptr) {
                    if (bantu1->data->lokasi == bantu->data->alamatTujuan && isKurirAvailable(bantu1->data, bantu->data->berat)) {
                        kurirFound = true;
                        break;
                    }
                    bantu1 = bantu1->next;
                }

                if (kurirFound) {
                    if (assignPaketToKurir(bantu1->data, bantu->data->berat, head, tail, headKurir, tailKurir)) {
                        cout << "Kurir ditemukan : " << bantu1->data->nama << " (" << bantu1->data->id_kurir << ")" << endl;
                        bantu->data->status = "Sedang Diantar";
                        bantu->data->attempCount++;
                        cout << "Paket dengan resi " << bantu->data->noResi << " telah ditugaskan ke Kurir " << bantu1->data->nama << endl;
                        TNode* paketBaru = new TNode;
                        paketBaru->data = bantu->data;
                        paketBaru->next = bantu1->data->daftarPaket;
                        bantu1->data->daftarPaket = paketBaru;
                        bantu1->data->jumlahPaket++;
                        bantu1->data->beratTotal += bantu->data->berat;
                        cout << "Kurir sekarang membawa " << bantu1->data->jumlahPaket << "/5 paket" << endl;
                        return; 
                    } else {
                        cout << "Kurir tidak dapat menangani paket ini." << endl;
                        return ;
                    }
                } else {
                    cout << "Tidak ada kurir yang tersedia untuk menerima paket ini." << endl;
                    return ;
                }
            }
            bantu = bantu->next;
        } while (bantu != head);
    } else {
        cout << "Kembali ke menu";
        admin(head,tail);
    
}
}

void tambahRiwayat(paket* dataPaket) {
    RiwayatNode* newNode = new RiwayatNode();
    newNode->data = dataPaket;
    newNode->next = headRiwayat;
    headRiwayat = newNode;
}

void riwayatPengiriman() {
    if (headRiwayat == nullptr) {
        cout << "Tidak ada riwayat pengiriman." << endl;
        return;
    }

    RiwayatNode* bantu = headRiwayat;
    int i = 1;
    cout << "========================================" << endl;
    cout << "| Menampilkan semua riwayat pengiriman |" << endl;
    cout << "========================================" << endl;
    while (bantu != nullptr) {
        cout << i << ". Resi: " << bantu->data->noResi << " | ";
        cout << " Pengirim: " << bantu->data->pengirim << " | ";
        cout << " Penerima: " << bantu->data->penerima << " | ";
        cout << " Alamat Tujuan: " << bantu->data->alamatTujuan << " | " << endl;
        bantu = bantu->next;
        i++;
    }
}

void verifikasiAdmin(TNode*& head, TNode*& tail, kurirNode*& headKurir, kurirNode*& tailKurir, 
    verifikasiAdminNode*& headVerifikasiAdmin, verifikasiAdminNode*& tailVerifikasiAdmin) {
    
    verifikasiAdminNode* bantu = headVerifikasiAdmin;
    TNode* bantu1 = head;
    int i=1;

    if (headVerifikasiAdmin == nullptr) {
        cout << "Tidak ada paket yang perlu diverifikasi." << endl;
        return;
    }
    cout << "Daftar Paket Menunggu Verifikasi:" << endl;
    while (bantu != nullptr) {
        cout << i << ". " << bantu->data->data->noResi;
        cout << " - Tujuan: " << bantu->data->data->alamatTujuan;
        cout << " - Status: " << bantu->data->data->status << endl;
        bantu = bantu->next;
        i++;
    }

    int pilihan;
    cout << "Pilih paket yang akan diverifikasi (nomor): ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan >= i) {
        cout << "Pilihan tidak valid." << endl;
        return;
    }

    bantu= headVerifikasiAdmin;
    if (bantu != nullptr && i != pilihan) {
        for (int j = 1; j < pilihan; j++) {
        bantu = bantu->next;
        i++;
        }
    cout << "Memproses verifikasi paket " << bantu->data->data->noResi << endl;
    cout << "Paket dikirim oleh: " << bantu->data->data->pengirim << endl;
    cout << "Paket diterima oleh: " << bantu->data->data->penerima << endl;
    cout << "Alamat tujuan: " << bantu->data->data->alamatTujuan << endl;
    cout << "Status: " << bantu->data->data->status << endl;
    }
    int pil;
    cout << "Apakah paket ini benar-benar sudah diterima?" << endl;
    cout << "1. Konfirmasi" << endl;
    cout << "2. Tidak" << endl;
    cout << "Pilih: ";
    cin >> pil;

    if (pil == 1) {
        while (bantu1 != nullptr) {
            if (bantu1->data->noResi == bantu->data->data->noResi) {
                bantu1->data->status = "Selesai";
                tambahRiwayat(bantu1->data); 
                break;
            }
            bantu1 = bantu1->next;
        }
        bantu->data->data->status = "Selesai";
        hapusVerifikasiAdmin(headVerifikasiAdmin, tailVerifikasiAdmin, bantu->data);
        cout << "Paket berhasil diverifikasi dan status diubah menjadi 'Selesai'." << endl;
    } else if (pil == 2) {
        bantu->data->data->status = "Gagal Dikirim";
        
        paketGagalNode* newPaketGagal = new paketGagalNode();
        newPaketGagal->data = bantu->data;
        newPaketGagal->next = headPaketGagal;

        if (headPaketGagal == nullptr) {
            headPaketGagal = newPaketGagal;
            tailPaketGagal = newPaketGagal;
        } else {
            newPaketGagal->next = headPaketGagal;
            headPaketGagal = newPaketGagal;
        }
        hapusVerifikasiAdmin(headVerifikasiAdmin, tailVerifikasiAdmin, bantu->data);
        cout << "Paket dipindahkan ke paket gagal dikirim." << endl;
        cout << "Verifikasi dibatalkan." << endl;
    }
}

void ubahStatusKurir(TNode*& head, TNode*& tail, kurirNode*& headKurir, kurirNode*& tailKurir) {
    string nomorResi;
    cout << "Masukan nomor resi: ";
    cin >> nomorResi;

    kurirNode* bantuKurir = headKurir;
    TNode* paketDitemukan = nullptr;

    while (bantuKurir != nullptr) {
        TNode* daftarPaket = bantuKurir->data->daftarPaket;
        while (daftarPaket != nullptr) {
            if (daftarPaket->data->noResi == nomorResi) {
                paketDitemukan = daftarPaket;
                break;
            }
            daftarPaket = daftarPaket->next;
        }
        if (paketDitemukan != nullptr) {
            break;
        }
        bantuKurir = bantuKurir->next;
    }

    if (paketDitemukan == nullptr) {
        cout << "Nomor resi tidak ditemukan dalam daftar kurir." << endl;
        return;
    }

    TNode* bantu = head;
    while (bantu != nullptr && bantu->data->noResi != nomorResi) {
        bantu = bantu->next;
    }

    if (bantu == nullptr) {
        cout << "Nomor resi tidak ditemukan di data utama." << endl;
        return;
    }

    if (paketDitemukan->data->status == "Sedang Diantar" || paketDitemukan->data->status == "Dikirim" || paketDitemukan->data->status == "Dalam Proses") {
        int pilstatus;
        while (true) {
            cout << "Ubah status Paket ke-: " << endl;
            cout << "1. Selesai" << endl;
            cout << "2. Gagal Dikirim" << endl;
            cout << "Pilih : ";
            cin >> pilstatus;

            if (pilstatus == 1) {
                bantu->data->status = "Menunggu Verifikasi";
                verifikasiAdminNode* newVerifikasiAdmin = new verifikasiAdminNode();
                newVerifikasiAdmin->data = bantu;
                newVerifikasiAdmin->next = nullptr;

                if (headVerifikasiAdmin == nullptr) {
                    headVerifikasiAdmin = newVerifikasiAdmin;
                    tailVerifikasiAdmin = newVerifikasiAdmin;
                } else {
                    tailVerifikasiAdmin->next = newVerifikasiAdmin;
                    tailVerifikasiAdmin = newVerifikasiAdmin;
                }

                bantuKurir->data->jumlahPaket--;
                bantuKurir->data->beratTotal -= bantu->data->berat;

                if (bantuKurir->data->daftarPaket == paketDitemukan) {
                    bantuKurir->data->daftarPaket = paketDitemukan->next;
                } else {
                    TNode* prev = bantuKurir->data->daftarPaket;
                    while (prev->next != paketDitemukan) {
                        prev = prev->next;
                    }
                    prev->next = paketDitemukan->next;
                }
                delete paketDitemukan;
                break;

            } else if (pilstatus == 2) {
                paketDitemukan->data->status = "Gagal Dikirim";
                bantu->data->status = "Gagal Dikirim";
                cout << "Paket " << paketDitemukan->data->noResi << " Gagal Dikirim." << endl;

                paketGagalNode* newNode = new paketGagalNode();
                newNode->data = bantu;
                newNode->next = headPaketGagal;
                headPaketGagal = newNode;

                if (tailPaketGagal == nullptr) {
                    tailPaketGagal = headPaketGagal;
                }

                bantuKurir->data->jumlahPaket--;
                bantuKurir->data->beratTotal -= paketDitemukan->data->berat;

                if (bantuKurir->data->daftarPaket == paketDitemukan) {
                    bantuKurir->data->daftarPaket = paketDitemukan->next;
                } else {
                    TNode* prev = bantuKurir->data->daftarPaket;
                    while (prev->next != paketDitemukan) {
                        prev = prev->next;
                    }
                    prev->next = paketDitemukan->next;
                }
                delete paketDitemukan;
                break;

            } else {
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
        }
    } else {
        cout << "Status paket tidak dapat diubah." << endl;
    }
    kurir();
}

void daftarPaketGagal(TNode*& head, TNode*& tail, kurirNode*& headKurir, kurirNode*& tailKurir, paketGagalNode*& headPaketGagal, paketGagalNode*& tailPaketGagal) {
    paketGagalNode* bantu = headPaketGagal;
    int i = 1;
    bool adaPaketGagal = false;

    cout << "=====================================" << endl;
    cout << "|        Daftar Paket Gagal         |" << endl;
    cout << "=====================================" << endl;
    cout << "Menampilkan Daftar Paket yang gagal dikirim:" << endl;

    while (bantu != nullptr) {
        adaPaketGagal = true;
        cout << i << ". " << bantu->data->data->noResi 
             << " - Percobaan Pengiriman: " << bantu->data->data->attempCount << endl;
        i++;
        bantu = bantu->next;
    }

    if (!adaPaketGagal) {
        cout << "Tidak ada paket dengan status Gagal Dikirim." << endl;
        return;
    }

    cout << endl << "Pilih paket untuk diproses (nomor): ";
    int pil;
    cin >> pil;

    if (pil < 1 || pil >= i) {
        cout << "Pilihan tidak valid." << endl;
        return;
    }

    bantu = headPaketGagal;
    for (int j = 1; j < pil; j++) {
        bantu = bantu->next;
    }

    cout << "Pilih tindakan yang akan dilakukan untuk paket " << bantu->data->data->noResi << endl;
    cout << "1. Tugaskan Kembali ke Kurir Lain" << endl;
    cout << "2. Tandai paket sebagai gagal    " << endl;
    cout << "Pilih : ";
    cin >> pil;

    if (pil == 1) {
        cout << "Kirim Ulang" << endl;
        kurirNode* bantuKurir = headKurir;
        bool kurirFound = false;
         
        while (bantuKurir != nullptr) {
            if (isKurirAvailable(bantuKurir->data, bantu->data->data->berat)) {
                kurirFound = true;
                break;
            }
            bantuKurir = bantuKurir->next;
        }

        if (kurirFound && bantu->data->data->attempCount < 3) {
            if (assignPaketToKurir(bantuKurir->data, bantu->data->data->berat, head, tail, headKurir, tailKurir)) {
                cout << "Kurir ditemukan : " << bantuKurir->data->nama << " (" << bantuKurir->data->id_kurir << ")" << endl;
                bantu->data->data->status = "Sedang Diantar";
                bantu->data->data->attempCount++;
                cout << "Paket dengan resi " << bantu->data->data->noResi << " telah ditugaskan ke Kurir " << bantuKurir->data->nama << endl;
                TNode* paketBaru = new TNode;
                paketBaru->data = bantu->data->data;
                paketBaru->next = bantuKurir->data->daftarPaket;
                bantuKurir->data->daftarPaket = paketBaru;
                bantuKurir->data->jumlahPaket++;
                bantuKurir->data->beratTotal += bantu->data->data->berat;
                cout << "Percoobaan pengiriman ke-" << bantu->data->data->attempCount << endl;
                cout << "Kurir sekarang membawa " << bantuKurir->data->jumlahPaket << "/5 paket" << endl;

                hapusPaketGagal(headPaketGagal, tailPaketGagal, bantu->data);
            } else {
                cout << "Kurir tidak dapat menangani paket ini." << endl;
            }
        } else {
            cout << "Tidak ada kurir yang tersedia untuk menerima paket ini." << endl;
        }
    } else if (pil == 2) {
        cout << "Paket " << bantu->data->data->noResi << " dikirim setelah " << bantu->data->data->attempCount << "x Percobaan" << endl;
        bantu->data->data->attempCount++;
        if (bantu->data->data->attempCount >= 3) {
            cout << "Paket tidak dapat dikirim lagi." << endl;
            cout << "Admin akan menghubungi pengirim untuk tindakan selanjutnya." << endl;
            hapusPaketGagal(headPaketGagal, tailPaketGagal, bantu->data);
        } else {
            cout << "Paket ditandai sebagai gagal kembali." << endl;
        }
    } else {
        cout << "Pilihan tidak valid." << endl;
    }
}

void kurir() {
    int pil;
    cout << endl << "============================" << endl;
    cout << "         Menu Kurir         " << endl;
    cout << "============================" << endl;
    cout << "1. Ubah Status Paket" << endl;
    cout << "2. Kembali ke menu utama" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilih : ";
    cin >> pil;

    if (pil == 1) {
        ubahStatusKurir(head,tail, headKurir, tailKurir);
    } else if (pil == 2) {
        main();
    } else if (pil == 0) {
        cout << "Keluar, terimakasih" << endl;
        return;
    } else {
        cout << "Masukan anda tidak sesuai. Silakan coba lagi." << endl;
        kurir();
    }
}

void loginKurir(kurirNode*& headKurir, kurirNode*& tailKurir) {
    string idKurir;
    string passwordKurir;
    cout << "Masukan ID Kurir: ";
    cin.ignore();
    getline(cin, idKurir);
    idKurir = toUpperString(idKurir);
    cout << "Masukan Password: ";
    getline(cin, passwordKurir);

    kurirNode* bantu = headKurir;
    bool found = false;
    while (bantu != nullptr) {
        if (bantu->data->id_kurir == idKurir && bantu->data->password == passwordKurir) {
            found = true;
            break;
        }
        bantu = bantu->next;
    }

    if (found) {
        cout << endl << "=================================" << endl;
        cout << "| Selamat Datang " << bantu->data->nama << " |" << endl;
        cout << "=================================" << endl;
        cout << "| Daftar Paket untuk diantar:   |" << endl;
        cout << "=================================" << endl;
        if (bantu->data->jumlahPaket == 0) {
            cout << "| Tidak ada paket untuk diantar.|" << endl;
        } else {
            TNode* paketBantu = bantu->data->daftarPaket;
            for (int i = 1; i <= bantu->data->jumlahPaket; i++) {
                cout << "| " << i << ". " << paketBantu->data->noResi 
                     << " - Tujuan: " << paketBantu->data->alamatTujuan 
                     << " - Berat: " << paketBantu->data->berat << " Kg |" << endl;
                paketBantu = paketBantu->next;
            }
        }
        cout << "=================================" << endl;
        kurir();
    } else {
        cout << "ID Kurir atau password salah" << endl;
        main();
    }
}

void statistikPengiriman(TNode*& head, TNode*& tail, kurirNode*& headKurir, kurirNode*& tailKurir) {
    int totalPaketSelesai = 0;
    int totalPaketGagal = 0;
    int kurirTersedia = 0;
    TNode* bantu = head;
    kurirNode* bantu1 = headKurir;

    if (head != nullptr) {
        do {
            if (bantu->data->status == "Selesai") {
                totalPaketSelesai++;
            } else if (bantu->data->status == "Gagal Dikirim") {
                totalPaketGagal++;
            }
            bantu = bantu->next;
        } while (bantu != head);
    }

    while (bantu1 != nullptr) {
        if (bantu1->data->jumlahPaket < 5 && bantu1->data->beratTotal < 20) {
            kurirTersedia++;
        }
        bantu1 = bantu1->next;
    }

    cout << endl << "=================================" << endl;
    cout << "      Statistik Pengiriman        " << endl;
    cout << "=================================" << endl;
    cout << "Total Paket yang Terkirim: " << totalPaketSelesai << endl;
    cout << "Total Paket yang Gagal Dikirim: " << totalPaketGagal << endl;
    cout << "Kurir yang tersedia: " << kurirTersedia << endl;
}

void admin(TNode*& head, TNode*& tail) {
    int opsiAdmin;
    do {
        cout << endl << "=================================" << endl;
        cout << "|           Menu Admin          |" << endl;
        cout << "=================================" << endl;
        cout << "| 1. Menambahkan Paket          |" << endl;
        cout << "| 2. Menampilkan Data Paket     |" << endl;
        cout << "| 3. Mengubah Data Paket        |" << endl;
        cout << "| 4. Mengubah Status Paket      |" << endl;
        cout << "| 5. Menghapus Paket            |" << endl;
        cout << "| 6. Tambahkan Kurir            |" << endl;
        cout << "| 7. Temukan Kurir              |" << endl;
        cout << "| 8. Statistik Kurir            |" << endl;
        cout << "| 9. Daftar Paket Gagal         |" << endl;
        cout << "| 10. Verifikasi Paket          |" << endl;
        cout << "| 11. Riwayat Pengiriman        |" << endl;
        cout << "| 12. Kembali ke Menu Utama     |" << endl;
        cout << "| 0. Keluar                     |" << endl;
        cout << "=================================" << endl;
        cout << "Pilih : ";
        cin >> opsiAdmin;

        if (opsiAdmin == 1) {
            tambahDataPaket(head, tail);
        } else if (opsiAdmin == 2) {
            tampilkanData(head, tail);
        } else if (opsiAdmin == 3) {
            ubahData(head, tail);
        }  else if (opsiAdmin == 4) {
            ubahStatus(head, tail);
        } else if (opsiAdmin == 5) {
            hapusPaket(head, tail);
        } else if (opsiAdmin == 6) {
            tambahkanKurir(headKurir,tailKurir);
        } else if (opsiAdmin == 7) {
            temukanKurir(head,tail,headKurir,tailKurir);
        } else if (opsiAdmin == 8) {
            statistikPengiriman(head, tail, headKurir, tailKurir);
        } else if (opsiAdmin == 9) {
            daftarPaketGagal(head, tail, headKurir, tailKurir,headPaketGagal, tailPaketGagal);
        } else if (opsiAdmin == 10) {
            verifikasiAdmin(head, tail, headKurir, tailKurir, headVerifikasiAdmin, tailVerifikasiAdmin);
        } else if (opsiAdmin == 11) {
            riwayatPengiriman();
        } else if (opsiAdmin == 12) {
            main();
        } else if (opsiAdmin == 0) {
            cout << "Keluar, terimakasih" << endl;
            return;
        } else {
            cout << "Masukan anda tidak sesuai. Silakan coba lagi." << endl;
        }
    } while (true);
}

int main() {
    int kodeLogin;

    cout << endl;
    cout << "=====================================" << endl;
    cout << "|       SISTEM PENGELOLAAN PAKET    |" << endl;
    cout << "=====================================" << endl;
    cout << "| 1. Login sebagai Admin            |" << endl;
    cout << "| 2. Login sebagai Kurir            |" << endl;
    cout << "| 0. Keluar                         |" << endl;
    cout << "=====================================" << endl;
    cout << "Pilih : ";
    cin >> kodeLogin;

    if (kodeLogin == 1) {
        admin(head, tail);
    } else if (kodeLogin == 2) {
        loginKurir(headKurir, tailKurir);
    } else if (kodeLogin == 0) {
        cout << "Keluar, terimakasih" << endl;
        return 0;
    } else {
        cout << "Masukan anda tidak sesuai" << endl;
    }

    return 0;
}