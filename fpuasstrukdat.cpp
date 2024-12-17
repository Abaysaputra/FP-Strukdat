#include <iostream>
#include <string>
using namespace std;

struct EquipmentItem {
    int id;
    string name;
    float pricePerDay;
    int stock;
    EquipmentItem* next;
};

struct RentalItem {
    int id;
    string name;
    float pricePerDay;
    RentalItem* next;
};

EquipmentItem* equipmentList = nullptr;
RentalItem* rentalHistory = nullptr;
int equipmentID = 1;
const string ADMIN_KEY = "admin123";

// Function to authenticate admin
bool autentikasiAdmin() {
    string inputKey;
    cout << "\nMasukkan admin key: ";
    cin >> inputKey;
    if (inputKey == ADMIN_KEY) {
        cout << "Akses diterima.\n";
        return true;
    } else {
        cout << "Akses ditolak. Key salah!\n";
        return false;
    }
}

// Function to display equipment list
void viewEquipmentList() {
    if (!equipmentList) {
        cout << "Maaf, daftar alat masih kosong :(\n";
        return;
    }

    EquipmentItem* current = equipmentList;
    cout << "\nDaftar Alat Outdoor:\n";
    while (current) {
        cout << current->id << ". " << current->name << " - Rp " << current->pricePerDay 
             << " per hari | Stok: " << current->stock << endl;
        current = current->next;
    }
    cout << endl;
}

// Function to add a new equipment
void addEquipment() {
    string name;
    float pricePerDay;
    int stock;

    cout << "\nMasukkan nama alat: ";
    cin.ignore();
    getline(cin, name);
    cout << "Masukkan harga sewa per hari: ";
    cin >> pricePerDay;
    cout << "Masukkan jumlah stok: ";
    cin >> stock;

    EquipmentItem* newItem = new EquipmentItem{equipmentID++, name, pricePerDay, stock, equipmentList};
    equipmentList = newItem;

    cout << "Alat berhasil ditambahkan!\n";
}

// Function to delete an equipment
void deleteEquipment() {
    int id;
    cout << "\nMasukkan ID alat yang ingin dihapus: ";
    cin >> id;

    EquipmentItem* current = equipmentList;
    EquipmentItem* prev = nullptr;

    while (current && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        cout << "Alat tidak ditemukan!\n";
        return;
    }

    if (prev) {
        prev->next = current->next;
    } else {
        equipmentList = current->next;
    }

    delete current;
    cout << "Alat berhasil dihapus!\n";
}

// Function to update an equipment
void updateEquipment() {
    int id;
    cout << "\nMasukkan ID alat yang ingin diubah: ";
    cin >> id;

    EquipmentItem* current = equipmentList;
    while (current && current->id != id) {
        current = current->next;
    }

    if (!current) {
        cout << "Alat tidak ditemukan!\n";
        return;
    }

    string newName;
    float newPrice;
    int newStock;
    cout << "Masukkan nama baru: ";
    cin.ignore();
    getline(cin, newName);
    cout << "Masukkan harga sewa baru per hari: ";
    cin >> newPrice;
    cout << "Masukkan stok baru: ";
    cin >> newStock;

    current->name = newName;
    current->pricePerDay = newPrice;
    current->stock = newStock;

    cout << "Data alat berhasil diubah!\n";
}

// Function to rent equipment
void rentEquipment() {
    if (!equipmentList) {
        cout << "Daftar alat masih kosong. Silakan kembali dan tambahkan alat terlebih dahulu.\n";
        return;
    }

    int id;
    cout << "\nMasukkan ID alat yang ingin disewa: ";
    cin >> id;

    EquipmentItem* current = equipmentList;
    while (current && current->id != id) {
        current = current->next;
    }

    if (!current) {
        cout << "Alat tidak ditemukan!\n";
        return;
    }

    if (current->stock <= 0) {
        cout << "Maaf, stok alat habis!\n";
        return;
    }

    // Kurangi stok
    current->stock--;

    // Tambahkan ke riwayat penyewaan
    RentalItem* newRental = new RentalItem{current->id, current->name, current->pricePerDay, rentalHistory};
    rentalHistory = newRental;

    cout << "Alat '" << current->name << "' berhasil disewa!\n";
}

// Function to view rental history
void viewRentalHistory() {
    if (!rentalHistory) {
        cout << "Tidak ada riwayat penyewaan.\n";
        return;
    }

    RentalItem* current = rentalHistory;
    cout << "\nRiwayat Penyewaan Alat:\n";
    while (current) {
        cout << current->id << ". " << current->name << " - Rp " << current->pricePerDay << " per hari\n";
        current = current->next;
    }
    cout << endl;
}

int main() {
    int choice;
    do {
        cout << "\n===== Penyewaan Alat Outdoor =====\n";
        cout << "1. Lihat Daftar Alat\n";
        cout << "2. Sewa Alat\n";
        cout << "3. Riwayat Penyewaan\n";
        cout << "4. Admin\n";
        cout << "5. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewEquipmentList();
                break;
            case 2:
                viewEquipmentList();
                rentEquipment();
                break;
            case 3:
                viewRentalHistory();
                break;
            case 4:
                if (autentikasiAdmin()) {
                    int adminChoice;
                    do {
                        cout << "\n===== Admin Menu =====\n";
                        cout << "1. Lihat Daftar Alat\n";
                        cout << "2. Tambah Alat\n";
                        cout << "3. Hapus Alat\n";
                        cout << "4. Ubah Alat\n";
                        cout << "5. Kembali\n";
                        cout << "Pilihan Anda: ";
                        cin >> adminChoice;

                        switch (adminChoice) {
                            case 1:
                                viewEquipmentList();
                                break;
                            case 2:
                                addEquipment();
                                break;
                            case 3:
                                deleteEquipment();
                                break;
                            case 4:
                                updateEquipment();
                                break;
                            case 5:
                                cout << "Kembali ke menu utama.\n";
                                break;
                            default:
                                cout << "Pilihan tidak valid!\n";
                        }
                    } while (adminChoice != 5);
                }
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (choice != 5);

    return 0;
}
