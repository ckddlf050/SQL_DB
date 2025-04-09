#include <iostream>
#include <windows.h>
#include <mysql/jdbc.h>
#include "book_controller.hpp" 
#include "member_controller.hpp"
#include "rental_controller.hpp"
#include "db.hpp"
using namespace std;

std::unique_ptr<sql::Connection> con; // ���� Ŀ�ؼ� ����

// ��Ʈ�ѷ� �Լ��� ����
void createBook();
void listBooks();
void updateBook();
void deleteBook();

void createMember();
void listMembers();
void updateMember();
void deleteMember();

void rentBook();
void returnBook();
void listRentals();

// DB ���� ��ü
//unique_ptr<sql::Connection> con;

int main() {
    SetConsoleOutputCP(CP_UTF8);  // �ѱ� �ܼ� ��� ����

    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        con.reset(driver->connect("tcp://127.0.0.1:3306", "root", "1234")); // DB ���� ����
        con->setSchema("book_management_db"); // ����Ϸ��� DB �̸����� ����

        int choice;

        do {
            cout << "\n==== Book Management System ====\n";
            cout << "1. Register Book\n";
            cout << "2. View Book List\n";
            cout << "3. Edit Book Info\n";
            cout << "4. Delete Book\n";
            cout << "5. Register Member\n";
            cout << "6. View Member List\n";
            cout << "7. Edit Member Info\n";
            cout << "8. Delete Member\n";
            cout << "9. Rent Book\n";
            cout << "10. Return Book\n";
            cout << "11. View Rental Status\n";
            cout << "0. Exit\n";
            cout << "===============================\n";
            cout << "Select a menu option: ";
            cin >> choice;

            switch (choice) {
            case 1: createBook(); break;
            case 2: listBooks(); break;
            case 3: updateBook(); break;
            case 4: deleteBook(); break;
            case 5: createMember(); break;
            case 6: listMembers(); break;
            case 7: updateMember(); break;
            case 8: deleteMember(); break;
            case 9: rentBook(); break;
            case 10: returnBook(); break;
            case 11: listRentals(); break;
            case 0: cout << "Exiting program.\n"; break;
            default: cout << "Please try again.\n"; break;
            }
        } while (choice != 0);
    }
    catch (sql::SQLException& e) {
        cerr << "DB ���� ����: " << e.what() << endl;
    }

    return 0;
}

