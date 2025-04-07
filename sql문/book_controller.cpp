#include <iostream>
#include <windows.h>
#include <string>
#include <mysql/jdbc.h>
using namespace std;

std::unique_ptr<sql::Connection> con;

// INSERT
void createbook() {
	// 고객 등록
	int price;
	string title, author,publoshed_at;

	cin.ignore();

	cout << "도서 제목 :";
	getline(cin, title);
	cout << "저자이름 :";
	getline(cin, author);
	cout << "출판일 :";
	getline(cin, publoshed_at);
	cout << "가격 :";
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
		cout << result << "도서 등록 완료" << endl;
	}
	catch (sql::SQLException& e) {
		cerr << "insert failed" << e.what() << endl;
	}
}

// 조회
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
				<< res->getInt("price") << "원 / "
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

	cout << "수정할 도서의 ID를 입력하세요: ";
	cin >> bookId;
	cin.ignore(); // 버퍼 비우기

	cout << "새 제목: ";
	getline(cin, title);

	cout << "새 저자: ";
	getline(cin, author);

	cout << "새 가격: ";
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
			cout << result << "권의 도서 정보가 수정되었습니다." << endl;
		}
		else {
			cout << "해당 ID의 도서를 찾을 수 없습니다." << endl;
		}
	}
	catch (sql::SQLException& e) {
		cerr << "도서 수정 실패: " << e.what() << endl;
	}
}

void deleteBook() {
	int bookId;

	cout << "삭제할 도서의 ID를 입력하세요: ";
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
