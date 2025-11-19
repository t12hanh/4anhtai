#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <iomanip>

using namespace std;

// Ki?m tra chu?i toàn s?
int isAllDigits(const char* s) {
    if (s[0] == '\0') return 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] < '0' || s[i] > '9') return 0;
    }
    return 1;
}

// Ki?m tra chu?i toàn kho?ng tr?ng
int isAllSpaces(const char* s) {
    if (s[0] == '\0') return 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ') return 0;
    }
    return 1;
}

// Chuy?n chu?i s? sang long long
long long toLongLong(const char* s) {
    long long num = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        num = num * 10 + (s[i] - '0');
    }
    return num;
}

// Xóa ph?n c?n l?i trong buffer
void clearLine() {
    cin.ignore(1000000, '\n');
}

bool isValidText(const char* s) {
    if (strlen(s) == 0 || isAllSpaces(s)) return false;

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (!((c >= 'A' && c <= 'Z') ||
              (c >= 'a' && c <= 'z') ||
              c == ' ')) {
            return false; 
        }
    }
    return true;
}


// ??nh ngh?a NhanVien
struct NhanVien {
    long long SoCCCD;
    char HoVaTenNV[50];
    char ChucVu[50];
    char SDT[15];
    float LuongCoBan;
    int SoNgayNghi;
};

// Node cho danh sách liên k?t
struct Node {
    NhanVien data;
    Node* next;
};

// Class qu?n l? danh sách
class List {
private:
    Node* head;
    Node* tail;
    int size;

public:
    List();
    Node* createNode(NhanVien x);
    bool Empty();
    void ThemNVdauDS(NhanVien x);
    void ThemNVcuoiDS(NhanVien x);
    void ThemNVbatki(NhanVien x, int pos);
    void deleteFirst();
    void deleteLast();
    void xoabatki(int pos);
    void print();
    bool check(long long SoCCCD);
    void SapxepSoCCCD();
    void SAPXEPTHEOTEN();
    void SAPXEPLUONG(int tg);
    void timkiemSoCCCD(long long key);
    void timkiemTheoTen(const char* namePart);
    void xetthuong();
    void saveToFile(const char* filename);
    void loadFromFile(const char* filename);
    void suaNhanVien(long long SoCCCD);
    int getSize() { return size; }
    void thongke();
    void exportCSV(const char* filename);
};

List::List() {
    head = tail = NULL;
    size = 0;
}

bool List::Empty() {
    return head == NULL;
}

Node* List::createNode(NhanVien x) {
    Node* p = new Node();
    p->data = x;
    p->next = NULL;
    return p;
}

void List::ThemNVcuoiDS(NhanVien x) {
    Node* p = createNode(x);
    if (head == NULL) {
        head = tail = p;
    } else {
        tail->next = p;
        tail = p;
    }
    size++;
}

void List::ThemNVdauDS(NhanVien x) {
    Node* p = createNode(x);
    if (head == NULL) {
        head = tail = p;
    } else {
        p->next = head;
        head = p;
    }
    size++;
}

void List::ThemNVbatki(NhanVien x, int pos) {
    if (pos < 1 || pos > size + 1) {
        cout << "Vi tri khong hop le\n";
        return;
    }
    if (Empty() || pos == 1) {
        ThemNVdauDS(x);
    } else if (pos == size + 1) {
        ThemNVcuoiDS(x);
    } else {
        Node* p = createNode(x);
        Node* a = head;
        for (int i = 1; i < pos - 1; i++) {
            a = a->next;
        }
        p->next = a->next;
        a->next = p;
        size++;
    }
}

bool List::check(long long SoCCCD) {
    if (SoCCCD <= 0) return 0;
    for (Node* p = head; p != NULL; p = p->next) {
        if (p->data.SoCCCD == SoCCCD) return 1;
    }
    return 0;
}

void List::deleteFirst() {
    if (head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    Node* tmp = head;
    head = head->next;
    delete tmp;
    size--;
    if (head == NULL) tail = NULL;
}

void List::deleteLast() {
    if (head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    if (head == tail) {
        deleteFirst();
        return;
    }
    Node* a = head;
    while (a->next != tail) {
        a = a->next;
    }
    delete tail;
    tail = a;
    tail->next = NULL;
    size--;
}

void List::xoabatki(int pos) {
    if (head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    if (pos < 1 || pos > size) {
        cout << "Vi tri khong hop le!\n";
        return;
    }
    if (pos == 1) {
        deleteFirst();
        return;
    }
    if (pos == size) {
        deleteLast();
        return;
    }
    Node* a = head;
    for (int i = 1; i < pos - 1; i++) {
        a = a->next;
    }
    Node* temp = a->next;
    a->next = temp->next;
    delete temp;
    size--;
}

char* Ten(char* HoVaTenNV) {
    char* p = strrchr(HoVaTenNV, ' ');
    if (p == NULL) return HoVaTenNV;
    return p + 1;
}

void List::SapxepSoCCCD() {
    if (head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    for (Node* i = head; i != NULL; i = i->next) {
        for (Node* j = i->next; j != NULL; j = j->next) {
            if (i->data.SoCCCD > j->data.SoCCCD) {
                NhanVien temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    cout << "\n => Danh sach da duoc sap xep theo So CCCD tang dan.\n";
}

void List::SAPXEPTHEOTEN() {
    if (head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    for (Node* p = head; p->next != NULL; p = p->next) {
        for (Node* q = p->next; q != NULL; q = q->next) {
            if (strcmp(Ten(p->data.HoVaTenNV), Ten(q->data.HoVaTenNV)) > 0) {
                NhanVien temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
    cout << "\n => Danh sach da duoc sap xep theo ten.\n";
}

void List::SAPXEPLUONG(int tg) {
    if (head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    for (Node* p = head; p->next != NULL; p = p->next) {
        for (Node* q = p->next; q != NULL; q = q->next) {
            if ((tg == 1 && p->data.LuongCoBan > q->data.LuongCoBan) ||
                (tg == 2 && p->data.LuongCoBan < q->data.LuongCoBan)) {
                NhanVien temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
    cout << "\n => Danh sach da duoc sap xep theo Luong co ban.\n";
}

void List::timkiemSoCCCD(long long key) {
    Node* p = head;
    int found = 0;

    cout << "\n-----------------------------------------------------------------------------------------------";
    cout << "\n| SO CCCD      | HO VA TEN                 | CHUC VU         | SDT        | LUONG CB   | NGAY NGHI |";
    cout << "\n-----------------------------------------------------------------------------------------------";

    while (p != NULL) {
        if (p->data.SoCCCD == key) {
            cout << "\n| " << setw(12) << p->data.SoCCCD
                 << " | " << setw(25) << p->data.HoVaTenNV
                 << " | " << setw(15) << p->data.ChucVu
                 << " | " << setw(10) << p->data.SDT
                 << " | " << setw(10) << fixed << setprecision(0) << p->data.LuongCoBan
                 << " | " << setw(8) << p->data.SoNgayNghi << " |";
            found = 1;
            break;
        }
        p = p->next;
    }

    cout << "\n-----------------------------------------------------------------------------------------------\n";
    if (!found) {
        cout << "\n => Khong tim thay nhan vien voi so CCCD: " << key << "\n";
    }
}

void List::timkiemTheoTen(const char* namePart) {
    Node* p = head;
    int found = 0;
        cout << "\n-----------------------------------------------------------------------------------------------";
    cout << "\n| SO CCCD      | HO VA TEN                 | CHUC VU         | SDT        | LUONG CB   | NGAY NGHI |";
    cout << "\n-----------------------------------------------------------------------------------------------";

    while (p != NULL) {
        // so sánh không phân bi?t hoa th??ng
        char tenLower[60];
        char keyLower[60];
        strcpy(tenLower, p->data.HoVaTenNV);
        strcpy(keyLower, namePart);
        // chuy?n v? lower-case
        for (int i = 0; tenLower[i]; i++) if (tenLower[i] >= 'A' && tenLower[i] <= 'Z') tenLower[i] += 32;
        for (int i = 0; keyLower[i]; i++) if (keyLower[i] >= 'A' && keyLower[i] <= 'Z') keyLower[i] += 32;

        if (strstr(tenLower, keyLower) != NULL) {
            cout << "\n| " << setw(12) << p->data.SoCCCD
                 << " | " << setw(25) << p->data.HoVaTenNV
                 << " | " << setw(15) << p->data.ChucVu
                 << " | " << setw(10) << p->data.SDT
                 << " | " << setw(10) << fixed << setprecision(0) << p->data.LuongCoBan
                 << " | " << setw(8) << p->data.SoNgayNghi << " |";
            found = 1;
        }
        p = p->next;
    }
    cout << "\n-----------------------------------------------------------------------------------------------\n";
    if (!found) {
        cout << "\n => Khong tim thay nhan vien voi tu: \"" << namePart << "\"\n";
    }
}

void List::xetthuong() {
    if (head == NULL) {
        cout << "Danh sach rong! Khong co nhan vien de xet thuong.\n";
        return;
    }

    // Sap xep giam dan theo luong
    SAPXEPLUONG(2);

    cout << "\n => Danh sach 5 nhan vien co luong co ban cao nhat va xem xet thuong:\n";
    cout << "\n------------------------------------------------------------------------------------------------------";
    cout << "\n| SO CCCD      | HO VA TEN                 | CHUC VU         | SDT         | LUONG CB   | NGAY NGHI | THUONG        |";
    cout << "\n------------------------------------------------------------------------------------------------------";

    int dem = 0;
    int found_eligible = 0;

    for (Node* i = head; i != NULL; i = i->next) {
        if (dem >= 5) break;

        if (i->data.SoNgayNghi < 3) {
            const char* loaiThuong;

            if ((i->data.LuongCoBan > 15000000) && (i->data.SoNgayNghi == 0)) {
                loaiThuong = "Thuong";
            } else if ((i->data.LuongCoBan >= 10000000 && i->data.LuongCoBan <= 15000000) &&
                       (i->data.SoNgayNghi < 2)) {
                loaiThuong = "Thuong";
            } else if ((i->data.LuongCoBan >= 7000000 && i->data.LuongCoBan < 10000000) &&
                       (i->data.SoNgayNghi < 3)) {
                loaiThuong = "Khong";
            } else {
                loaiThuong = "Khong";
            }

            cout << "\n| " << setw(12) << i->data.SoCCCD
                 << " | " << setw(25) << i->data.HoVaTenNV
                 << " | " << setw(15) << i->data.ChucVu
                 << " | " << setw(12) << i->data.SDT
                 << " | " << setw(10) << fixed << setprecision(0) << i->data.LuongCoBan
                 << " | " << setw(8) << i->data.SoNgayNghi
                 << " | " << setw(13) << loaiThuong << " |";

            dem++;
            found_eligible = 1;
        }
    }

    cout << "\n------------------------------------------------------------------------------------------------------\n";

    if (!found_eligible) {
        cout << "\n => Khong tim thay nhan vien nao thoa man dieu kien xet thuong (Luong cao nhat va so ngay nghi < 3).\n";
    }
}

void List::saveToFile(const char* filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Khong the mo file de ghi!\n";
        return;
    }
    Node* p = head;
    while (p != NULL) {
        // Ghi theo 6 dong cho moi nhan vien de de doc
        file << p->data.SoCCCD << "\n";
        file << p->data.HoVaTenNV << "\n";
        file << p->data.ChucVu << "\n";
        file << p->data.SDT << "\n";
        file << p->data.LuongCoBan << "\n";
        file << p->data.SoNgayNghi << "\n";
        p = p->next;
    }
    file.close();
    cout << "Du lieu da duoc luu vao file: " << filename << endl;
}

void List::loadFromFile(const char* filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Khong the mo file de doc!\n";
        return;
    }

    NhanVien nv;

    // Xoa danh sach cu
    while (head != NULL) {
        deleteFirst();
    }

    // ??c theo format 6 d?ng / nhân viên
    while (file >> nv.SoCCCD) {
        file.ignore(1000000, '\n');
        file.getline(nv.HoVaTenNV, sizeof(nv.HoVaTenNV));
        file.getline(nv.ChucVu, sizeof(nv.ChucVu));
        file.getline(nv.SDT, sizeof(nv.SDT));
        file >> nv.LuongCoBan;
        file >> nv.SoNgayNghi;
        file.ignore(1000000, '\n');

        ThemNVcuoiDS(nv);
        if (file.eof()) break;
    }

    file.close();
    cout << "Du lieu da duoc tai ve tu file: " << filename << endl;
}

void List::print() {
    if (head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }

    cout << left;

    cout << "\n-------------------------------------------------------------------------------------------------------------";
    cout << "\n| "
         << setw(12) << "SO CCCD"
         << " | " << setw(25) << "HO VA TEN"
         << " | " << setw(15) << "CHUC VU"
         << " | " << setw(12) << "SDT"
         << " | " << setw(12) << "LUONG CB"
         << " | " << setw(10) << "NGAY NGHI" << " |";
    cout << "\n-------------------------------------------------------------------------------------------------------------";

    for (Node* p = head; p != NULL; p = p->next) {
        cout << "\n| "
             << setw(12) << p->data.SoCCCD
             << " | " << setw(25) << p->data.HoVaTenNV
             << " | " << setw(15) << p->data.ChucVu
             << " | " << setw(12) << p->data.SDT
             << " | " << setw(12) << fixed << setprecision(0) << p->data.LuongCoBan
             << " | " << setw(10) << p->data.SoNgayNghi << " |";
    }

    cout << "\n-------------------------------------------------------------------------------------------------------------\n";
}
// S?a nhân viên theo S? CCCD
void List::suaNhanVien(long long SoCCCD) {
    if (head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    Node* p = head;
    while (p != NULL && p->data.SoCCCD != SoCCCD) p = p->next;
    if (p == NULL) {
        cout << "Khong tim thay nhan vien co CCCD: " << SoCCCD << "\n";
        return;
    }

    cout << "Tim thay nhan vien: \n";
    cout << "1) Ho va ten: " << p->data.HoVaTenNV << "\n";
    cout << "2) Chuc vu: " << p->data.ChucVu << "\n";
    cout << "3) SDT: " << p->data.SDT << "\n";
    cout << "4) Luong co ban: " << p->data.LuongCoBan << "\n";
    cout << "5) So ngay nghi: " << p->data.SoNgayNghi << "\n";

    cout << "\nBan muon sua thong tin gi?\n";
    cout << "Nhap 0 de thoat.\n";

    int opt;
    do {
        cout << "Chon (1-5, 0 de thoat): ";
        if (!(cin >> opt)) {
            cin.clear();
            clearLine();
            cout << "Nhap khong hop le.\n";
            continue;
        }
        clearLine();
        if (opt == 0) break;

        if (opt == 1) {
            char tmp[50];
            cout << "Nhap ho va ten moi: ";
            cin.getline(tmp, sizeof(tmp));
            if (strlen(tmp) == 0 || isAllSpaces(tmp)) {
                cout << "Ho ten khong hop le. Bo qua.\n";
            } else {
                strcpy(p->data.HoVaTenNV, tmp);
                cout << "Cap nhat thanh cong.\n";
            }
        } else if (opt == 2) {
            char tmp[50];
            cout << "Nhap chuc vu moi: ";
            cin.getline(tmp, sizeof(tmp));
            if (strlen(tmp) == 0 || isAllSpaces(tmp)) {
                cout << "Chuc vu khong hop le. Bo qua.\n";
            } else {
                strcpy(p->data.ChucVu, tmp);
                cout << "Cap nhat thanh cong.\n";
            }
        } else if (opt == 3) {
            char tmp[20];
            cout << "Nhap SDT moi (10 so): ";
            cin.getline(tmp, sizeof(tmp));
            if (strlen(tmp) != 10 || !isAllDigits(tmp)) {
                cout << "SDT khong hop le. Bo qua.\n";
            } else {
                strcpy(p->data.SDT, tmp);
                cout << "Cap nhat thanh cong.\n";
            }
        } else if (opt == 4) {
            float lu;
            cout << "Nhap luong moi: ";
            if (!(cin >> lu)) {
                cin.clear();
                clearLine();
                cout << "Nhap khong hop le.\n";
            } else {
                if (lu <= 0) cout << "Luong phai > 0. Bo qua.\n";
                else {
                    p->data.LuongCoBan = lu;
                    cout << "Cap nhat thanh cong.\n";
                }
                clearLine();
            }
        } else if (opt == 5) {
            int sn;
            cout << "Nhap so ngay nghi moi (0-28): ";
            if (!(cin >> sn)) {
                cin.clear();
                clearLine();
                cout << "Nhap khong hop le.\n";
            } else {
                if (sn < 0 || sn > 28) cout << "So ngay nghi khong hop le. Bo qua.\n";
                else {
                    p->data.SoNgayNghi = sn;
                    cout << "Cap nhat thanh cong.\n";
                }
                clearLine();
            }
        } else {
            cout << "Lua chon khong hop le.\n";
        }
    } while (opt != 0);

}

// Th?ng kê (t?ng s? NV, l??ng TB, l??ng max + NV có l??ng max)
void List::thongke() {
    if (head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    int count = 0;
    double sum = 0;
    float maxLuong = -1;
    Node* p = head;
    while (p) {
        count++;
        sum += p->data.LuongCoBan;
        if (p->data.LuongCoBan > maxLuong) maxLuong = p->data.LuongCoBan;
        p = p->next;
    }

    cout << "\n=> Thong ke danh sach:\n";
    cout << "Tong so nhan vien: " << count << "\n";
    cout << "Luong trung binh: " << fixed << setprecision(0) << (sum / count) << "\n";
    cout << "Luong cao nhat: " << fixed << setprecision(0) << maxLuong << "\n";

    // In danh sach nhan vien co luong cao nhat
    cout << "\nNhan vien co luong cao nhat:\n";
    cout << "-----------------------------------------------------------------------------------------------";
    cout << "\n| SO CCCD      | HO VA TEN                 | CHUC VU         | SDT        | LUONG CB   | NGAY NGHI |";
    cout << "\n-----------------------------------------------------------------------------------------------";
    p = head;
    while (p) {
        if (p->data.LuongCoBan == maxLuong) {
            cout << "\n| " << setw(12) << p->data.SoCCCD
                 << " | " << setw(25) << p->data.HoVaTenNV
                 << " | " << setw(15) << p->data.ChucVu
                 << " | " << setw(10) << p->data.SDT
                 << " | " << setw(10) << fixed << setprecision(0) << p->data.LuongCoBan
                 << " | " << setw(8) << p->data.SoNgayNghi << " |";
        }
        p = p->next;
    }
    cout << "\n-----------------------------------------------------------------------------------------------\n";
}
int main() {
    List l;
    int choice;

    do {
        cout << "\n*------------ ||QUAN LY NHAN VIEN|| ----------------*";
        cout << "\n=====================================================";
        cout << "\n||             1. Them nhan vien                   ||";
        cout << "\n||             2. Xoa nhan vien                    ||";
        cout << "\n||             3. Tim / Sua nhan vien              ||";
        cout << "\n||             4. Sap xep nhan vien                ||";
        cout << "\n||             5. Danh sach nhan vien              ||";
        cout << "\n||             6. Luu danh sach vao file           ||";
        cout << "\n||             7. Tai danh sach tu file            ||";
        cout << "\n||             8. Xet thuong                       ||";
        cout << "\n||             9. Thong ke                         ||";
        cout << "\n||             0. Thoat                            ||";
        cout << "\n*---------------------------------------------------*";
        cout << "\n =>  Chon chuc nang: ";

        if (!(cin >> choice)) {
            cin.clear();
            clearLine();
            cout << "Nhap sai! Vui long nhap so.\n";
            choice = -1;
            continue;
        }
        clearLine();

        switch (choice) {
        case 1: {
            int lc;
            cout << "\n1. Them nhan vien dau danh sach.";
            cout << "\n2. Them nhan vien cuoi danh sach.";
            cout << "\n3. Them nhan vien tai vi tri bat ki.";
            cout << "\nChon: ";

            if (!(cin >> lc)) {
                cin.clear();
                clearLine();
                cout << "Lua chon khong hop le. Quay lai menu chinh.\n";
                break;
            }
            clearLine();

            NhanVien nv;
            int pos;
            char tempCCCD[30];

            // Nhap CCCD
            while (1) {
                cout << "\n- Nhap vao So CCCD (phai du 12 so): ";
                cin.getline(tempCCCD, sizeof(tempCCCD));

                int length = strlen(tempCCCD);
                if (length != 12) {
                    cout << "So CCCD khong hop le. Phai du 12 so. Vui long nhap lai.\n";
                    continue;
                }
                if (!isAllDigits(tempCCCD)) {
                    cout << "So CCCD khong hop le. Chi duoc nhap chu so. Vui long nhap lai.\n";
                    continue;
                }

                long long tmp = toLongLong(tempCCCD);
                if (l.check(tmp)) {
                    cout << "So CCCD da ton tai. Vui long nhap lai.\n";
                    continue;
                }

                nv.SoCCCD = tmp;
                break;
            }

            // Nhap ho ten
           while (1) {
                cout << "- Nhap vao ho va ten nhan vien: ";
                 cin.getline(nv.HoVaTenNV, sizeof(nv.HoVaTenNV));

                if (!isValidText(nv.HoVaTenNV)) {
                    cout << "Ho ten chi duoc chua chu cai va khoang trang! "
                  "Khong duoc chua so hoac ky tu dac biet.\n";
                    continue;
                }
                 break;
            }


            // Nhap chuc vu
            while (1) {
                cout << "- Nhap vao chuc vu: ";
                cin.getline(nv.ChucVu, sizeof(nv.ChucVu));
 
                if (!isValidText(nv.ChucVu)) {
                cout << "Chuc vu chi duoc chua chu cai va khoang trang! "
                "Khong duoc chua so hoac ky tu dac biet.\n";
                 continue;
                }
              break;
            }


            // Nhap SDT
            while (1) {
                cout << "- Nhap vao So dien thoai (10 so): ";
                cin.getline(nv.SDT, sizeof(nv.SDT));

                if (strlen(nv.SDT) != 10) {
                    cout << "So dien thoai phai co 10 so!\n";
                    continue;
                }
                if (!isAllDigits(nv.SDT)) {
                    cout << "So dien thoai chi duoc chua chu so!\n";
                    continue;
                }
                break;
            }

            // Nhap Luong co ban
            while (1) {
                cout << "\n- Nhap Luong co ban (VD: 10000000): ";
                if (!(cin >> nv.LuongCoBan)) {
                    cin.clear();
                    clearLine();
                    cout << "Luong co ban khong hop le, vui long nhap so!\n";
                    continue;
                }
                if (nv.LuongCoBan <= 0) {
                    cout << "Luong co ban phai > 0!\n";
                    continue;
                }
                clearLine();
                break;
            }

            // Nhap so ngay nghi (0-28)
            while (1) {
                cout << "\n- Nhap vao so ngay nghi trong thang (0 - 28): ";
                if (!(cin >> nv.SoNgayNghi)) {
                    cin.clear();
                    clearLine();
                    cout << "So ngay nghi khong hop le, vui long nhap so!\n";
                    continue;
                }
                if (nv.SoNgayNghi < 0 || nv.SoNgayNghi > 28) {
                    cout << "So ngay nghi phai trong khoang 0 - 28!\n";
                    continue;
                }
                clearLine();
                break;
            }

            // Chen vao danh sach
            if (lc == 1) {
                l.ThemNVdauDS(nv);
                cout << "\n => Nhan vien da duoc them vao dau danh sach.\n";
            } else if (lc == 2) {
                l.ThemNVcuoiDS(nv);
                cout << "\n => Nhan vien da duoc them vao cuoi danh sach.\n";
            } else if (lc == 3) {
                cout << "\n- Nhap vi tri can them: ";
                if (!(cin >> pos)) {
                    cin.clear();
                    clearLine();
                    cout << "Vi tri khong hop le.\n";
                    break;
                }
                clearLine();
                l.ThemNVbatki(nv, pos);
            } else {
                cout << "Lua chon khong hop le.\n";
            }

            break;
        }

        case 2: {
            int lc;
            cout << "\n1. Xoa dau danh sach";
            cout << "\n2. Xoa cuoi danh sach";
            cout << "\n3. Xoa tai vi tri bat ky";
            cout << "\nChon: ";
            if (!(cin >> lc)) {
                cin.clear();
                clearLine();
                cout << "Lua chon khong hop le.\n";
                break;
            }
            clearLine();

            if (lc == 1) {
                l.deleteFirst();
            } else if (lc == 2) {
                l.deleteLast();
            } else if (lc == 3) {
                int pos;
                cout << "- Nhap vi tri nhan vien can xoa: ";
                if (!(cin >> pos)) {
                    cin.clear();
                    clearLine();
                    cout << "Vi tri khong hop le.\n";
                    break;
                }
                clearLine();
                l.xoabatki(pos);
            } else {
                cout << "Lua chon khong hop le.\n";
            }

            break;
        }

        case 3: {
            cout << "\n1. Tim nhan vien theo So CCCD";
            cout << "\n2. Tim nhan vien theo ten (tu khoa)";
            cout << "\n3. Sua nhan vien theo So CCCD";
            cout << "\nChon: ";
            int opt;
            if (!(cin >> opt)) {
                cin.clear();
                clearLine();
                cout << "Lua chon khong hop le.\n";
                break;
            }
            clearLine();

            if (opt == 1) {
                char input[30];
                cout << "- Nhap so CCCD can tim: ";
                cin.getline(input, sizeof(input));
                if (!isAllDigits(input) || strlen(input) != 12) {
                    cout << "So CCCD khong hop le.\n";
                } else {
                    long long key = toLongLong(input);
                    l.timkiemSoCCCD(key);
                }
            } else if (opt == 2) {
                char kw[50];
                cout << "- Nhap tu khoa (ten hoac mot phan cua ten): ";
                cin.getline(kw, sizeof(kw));
                if (strlen(kw) == 0) {
                    cout << "Tu khoa rong.\n";
                } else {
                    l.timkiemTheoTen(kw);
                }
            } else if (opt == 3) {
                char input[30];
                cout << "- Nhap so CCCD cua nhan vien can sua: ";
                cin.getline(input, sizeof(input));
                if (!isAllDigits(input) || strlen(input) != 12) {
                    cout << "So CCCD khong hop le.\n";
                } else {
                    long long key = toLongLong(input);
                    l.suaNhanVien(key);
                }
            } else {
                cout << "Lua chon khong hop le.\n";
            }
            break;
        }

        case 4: {
            cout << "\n1. Sap xep theo So CCCD (tang dan)";
            cout << "\n2. Sap xep theo Ten (A-Z)";
            cout << "\n3. Sap xep theo Luong (tang dan)";
            cout << "\n4. Sap xep theo Luong (giam dan)";
            cout << "\nChon: ";
            int opt;
            if (!(cin >> opt)) {
                cin.clear();
                clearLine();
                cout << "Lua chon khong hop le.\n";
                break;
            }
            clearLine();
            if (opt == 1) l.SapxepSoCCCD();
            else if (opt == 2) l.SAPXEPTHEOTEN();
            else if (opt == 3) l.SAPXEPLUONG(1);
            else if (opt == 4) l.SAPXEPLUONG(2);
            else cout << "Lua chon khong hop le.\n";
            break;
        }

        case 5:
            l.print();
            break;

        case 6: {
            char fname[200];
            cout << "Nhap ten file de luu (vi du: ds.txt): ";
            cin.getline(fname, sizeof(fname));
            if (strlen(fname) == 0) {
                cout << "Ten file rong. Bo qua.\n";
            } else {
                l.saveToFile(fname);
            }
            break;
        }

        case 7: {
            char fname[200];
            cout << "Nhap ten file de tai (vi du: ds.txt): ";
            cin.getline(fname, sizeof(fname));
            if (strlen(fname) == 0) {
                cout << "Ten file rong. Bo qua.\n";
            } else {
                l.loadFromFile(fname);
            }
            break;
        }

        case 8:
            l.xetthuong();
            break;

        case 9:
            l.thongke();
            break;
			 
        case 0:
            cout << "Thoat chuong trinh. Tam biet!\n";
            break;

        default:
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
            break; 
        }

    } while (choice != 0);

    return 0;
}

