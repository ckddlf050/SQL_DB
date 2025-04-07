#include <iostream>
#include <windows.h>
#include <string>
#include <mysql/jdbc.h>
using namespace std;

std::unique_ptr<sql::Connection> con;

// INSERT
void createbook() {
	// �� ���
	int price;
	string title, author,publoshed_at;

	cin.ignore();

	cout << "���� ���� :";
	getline(cin, title);
	cout << "�����̸� :";
	getline(cin, author);
	cout << "������ :";
	getline(cin, publoshed_at);
	cout << "���� :";
	cin >> price;

	try {
		unique_ptr<sql::PreparedStatement> insertQuery(
			con->prepareStatement("INSERT INTO books (title, author, published_at, price) VALUES (?, ?, ?, ?)")
		);
		insertQuery->setString(1, title);
		insertQuery->setString(2, author);
		insertQuery->setString(3, publoshed_at);
		insertQuery->setInt(4, price);

		int result = insertQuery->executeUpdate();
		cout << result << "���� ��� �Ϸ�" << endl;
	}
	catch (sql::SQLException& e) {
		cerr << "insert failed" << e.what() << endl;
	}
}

// ��ȸ
void listBooks() {
	try {
		unique_ptr<sql::PreparedStatement> selectQuery(
			con->prepareStatement("SELECT book_id, title, author, published_at, price, status FROM books")
		);

		unique_ptr<sql::ResultSet> res(selectQuery->executeQuery());


		while (res->next()) {
			cout << "[" << res->getInt("book_id") << "] "
				<< res->getString("title") << " / "
				<< res->getString("author") << " / "
				<< res->getString("published_at") << " / "
				<< res->getInt("price") << "�� / "
				<< res->getString("status") << endl;
		}
	}
	catch (sql::SQLException& e) {
		cerr << "select failed : " << e.what() << endl;
	}
}

// update
void updateBook() {
	int bookId, price;
	string title, author;

	cout << "������ ������ ID�� �Է��ϼ���: ";
	cin >> bookId;
	cin.ignore(); // ���� ����

	cout << "�� ����: ";
	getline(cin, title);

	cout << "�� ����: ";
	getline(cin, author);

	cout << "�� ����: ";
	cin >> price;

	try {
		unique_ptr<sql::PreparedStatement> updateQuery(
			con->prepareStatement("UPDATE books SET title = ?, author = ?, price = ? WHERE book_id = ?")
		);

		updateQuery->setString(1, title);
		updateQuery->setString(2, author);
		updateQuery->setInt(3, price);
		updateQuery->setInt(4, bookId);

		int result = updateQuery->executeUpdate();

		if (result > 0) {
			cout << result << "���� ���� ������ �����Ǿ����ϴ�." << endl;
		}
		else {
			cout << "�ش� ID�� ������ ã�� �� �����ϴ�." << endl;
		}
	}
	catch (sql::SQLException& e) {
		cerr << "���� ���� ����: " << e.what() << endl;
	}
}

void deleteBook() {
	int bookId;

	cout << "������ ������ ID�� �Է��ϼ���: ";
	cin >> bookId;

	try {
		unique_ptr<sql::PreparedStatement> deleteQuery(
			con->prepareStatement("DELETE FROM books WHERE book_id = ?")
		);

		deleteQuery->setInt(1, bookId);

		int result = deleteQuery->executeUpdate();

		if (result > 0) {
			cout << result << "books delete." << endl;
		}
		else {
			cout << "not found book." << endl;
		}
	}
	catch (sql::SQLException& e) {
		cerr << "delete failed: " << e.what() << endl;
	}
}
