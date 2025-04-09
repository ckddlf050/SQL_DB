#include <iostream>
#include <windows.h>
#include <string>
#include <mysql/jdbc.h>
#include "db.hpp"  

using namespace std;

// INSERT - Register Book
void createBook() {
	int price;
	string title, author, published_at;

	cin.ignore(); // Clear input buffer

	cout << "Title: ";
	getline(cin, title);
	cout << "Author: ";
	getline(cin, author);
	cout << "Published Date (YYYY-MM-DD): ";
	getline(cin, published_at);
	cout << "Price: ";
	cin >> price;

	try {
		unique_ptr<sql::PreparedStatement> insertQuery(
			con->prepareStatement("INSERT INTO books (title, author, published_at, price) VALUES (?, ?, ?, ?)")
		);
		insertQuery->setString(1, title);
		insertQuery->setString(2, author);
		insertQuery->setString(3, published_at);
		insertQuery->setInt(4, price);

		int result = insertQuery->executeUpdate();
		cout << result << " book(s) have been registered." << endl;
	}
	catch (sql::SQLException& e) {
		cerr << "Book registration failed: " << e.what() << endl;
	}
}

// SELECT - List Books
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
				<< res->getInt("price") << " KRW / "
				<< res->getString("status") << endl;
		}
	}
	catch (sql::SQLException& e) {
		cerr << "Failed to fetch book list: " << e.what() << endl;
	}
}

// UPDATE - Modify Book Info
void updateBook() {
	int bookId, price;
	string title, author;

	cout << "Book ID to update: ";
	cin >> bookId;
	cin.ignore(); // Clear buffer

	cout << "New Title: ";
	getline(cin, title);

	cout << "New Author: ";
	getline(cin, author);

	cout << "New Price: ";
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
			cout << result << " book(s) updated successfully." << endl;
		}
		else {
			cout << "Book not found." << endl;
		}
	}
	catch (sql::SQLException& e) {
		cerr << "Book update failed: " << e.what() << endl;
	}
}

// DELETE - Remove Book
void deleteBook() {
	int bookId;

	cout << "Enter the ID of the book to delete: ";
	cin >> bookId;

	try {
		unique_ptr<sql::PreparedStatement> deleteQuery(
			con->prepareStatement("DELETE FROM books WHERE book_id = ?")
		);

		deleteQuery->setInt(1, bookId);

		int result = deleteQuery->executeUpdate();

		if (result > 0) {
			cout << result << " book(s) deleted." << endl;
		}
		else {
			cout << "Book not found." << endl;
		}
	}
	catch (sql::SQLException& e) {
		cerr << "Book deletion failed: " << e.what() << endl;
	}
}
