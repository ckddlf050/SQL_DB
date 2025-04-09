#include <iostream>
#include <windows.h>
#include <string>
#include <mysql/jdbc.h>
#include "db.hpp"  

using namespace std;


void createMember() {
    string name, email, phone;

    cin.ignore(); // 버퍼 비우기
    cout << "name: ";
    getline(cin, name);
    cout << "email: ";
    getline(cin, email);
    cout << "phone: ";
    getline(cin, phone);

    try {
        unique_ptr<sql::PreparedStatement> insertQuery(
            con->prepareStatement("INSERT INTO members (name, email, phone) VALUES (?, ?, ?)")
        );

        insertQuery->setString(1, name);
        insertQuery->setString(2, email);
        insertQuery->setString(3, phone);

        int result = insertQuery->executeUpdate();
        cout << result << "Member information updated." << endl;
    }
    catch (sql::SQLException& e) {
        cerr << "insert failed: " << e.what() << endl;
    }
}

void listMembers() {
    try {
        unique_ptr<sql::PreparedStatement> selectQuery(
            con->prepareStatement("SELECT member_id, name, email, phone, registered_at FROM members")
        );
        unique_ptr<sql::ResultSet> res(selectQuery->executeQuery());

        while (res->next()) {
            cout << "[" << res->getInt("member_id") << "] "
                << res->getString("name") << " / "
                << res->getString("email") << " / "
                << res->getString("phone") << " / "
                << res->getString("registered_at") << endl;
        }
    }
    catch (sql::SQLException& e) {
        cerr << "Member not found: " << e.what() << endl;
    }
}


void updateMember() {
    int memberId;
    string name, email, phone;
    cout << "Enter the member ID to update: ";
    cin >> memberId;
    cin.ignore();

    cout << "new name: ";
    getline(cin, name);
    cout << "new email: ";
    getline(cin, email);
    cout << "new phone: ";
    getline(cin, phone);

    try {
        unique_ptr<sql::PreparedStatement> updateQuery(
            con->prepareStatement("UPDATE members SET name = ?, email = ?, phone = ? WHERE member_id = ?")
        );

        updateQuery->setString(1, name);
        updateQuery->setString(2, email);
        updateQuery->setString(3, phone);
        updateQuery->setInt(4, memberId);

        int result = updateQuery->executeUpdate();
        if (result > 0)
            cout << "Member information updated." << endl;
        else
            cout << "not found id." << endl;
    }
    catch (sql::SQLException& e) {
        cerr << "update fial: " << e.what() << endl;
    }
}

void deleteMember() {
    int memberId;

    
    cout << "Enter the member ID to delete ";
    cin >> memberId;

    try {
        unique_ptr<sql::PreparedStatement> deleteQuery(
            con->prepareStatement("DELETE FROM members WHERE member_id = ?")
        );
        deleteQuery->setInt(1, memberId);

        int result = deleteQuery->executeUpdate();
        if (result > 0)
            cout << "member deleted." << endl;
        else
            cout << "not found." << endl;
    }
    catch (sql::SQLException& e) {
        cerr << "delete fail: " << e.what() << endl;
    }
}
