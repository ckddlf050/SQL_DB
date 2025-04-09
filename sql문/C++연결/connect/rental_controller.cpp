#include <iostream>
#include <string>
#include <mysql/jdbc.h>
#include "db.hpp"

using namespace std;

// Rent a book
void rentBook() {
    int bookId, memberId;

    cout << "Book ID: ";
    cin >> bookId;
    cout << "Member ID: ";
    cin >> memberId;

    try {
        // 1. Check if book is available
        unique_ptr<sql::PreparedStatement> checkBook(
            con->prepareStatement("SELECT status FROM books WHERE book_id = ?")
        );
        checkBook->setInt(1, bookId);
        unique_ptr<sql::ResultSet> res(checkBook->executeQuery());

        if (res->next()) {
            string status = res->getString("status");
            if (status != "Available") {
                cout << "This book is currently rented.\n";
                return;
            }
        }
        else {
            cout << "Book not found.\n";
            return;
        }

        // 2. Insert into rentals table
        unique_ptr<sql::PreparedStatement> insertRental(
            con->prepareStatement("INSERT INTO rentals (book_id, member_id) VALUES (?, ?)")
        );
        insertRental->setInt(1, bookId);
        insertRental->setInt(2, memberId);
        insertRental->executeUpdate();

        // 3. Update book status
        unique_ptr<sql::PreparedStatement> updateBook(
            con->prepareStatement("UPDATE books SET status = 'Rented' WHERE book_id = ?")
        );
        updateBook->setInt(1, bookId);
        updateBook->executeUpdate();

        cout << "Book successfully rented.\n";
    }
    catch (sql::SQLException& e) {
        cerr << "Failed to rent book: " << e.what() << endl;
    }
}

// Return a book
void returnBook() {
    int bookId;

    cout << "Book ID: ";
    cin >> bookId;

    try {
        // 1. Find most recent unreturned rental
        unique_ptr<sql::PreparedStatement> checkRental(
            con->prepareStatement("SELECT rental_id FROM rentals WHERE book_id = ? AND returned_at IS NULL ORDER BY rented_at DESC LIMIT 1")
        );
        checkRental->setInt(1, bookId);
        unique_ptr<sql::ResultSet> res(checkRental->executeQuery());

        if (res->next()) {
            int rentalId = res->getInt("rental_id");

            // 2. Set return date
            unique_ptr<sql::PreparedStatement> updateRental(
                con->prepareStatement("UPDATE rentals SET returned_at = NOW() WHERE rental_id = ?")
            );
            updateRental->setInt(1, rentalId);
            updateRental->executeUpdate();

            // 3. Update book status
            unique_ptr<sql::PreparedStatement> updateBook(
                con->prepareStatement("UPDATE books SET status = 'Available' WHERE book_id = ?")
            );
            updateBook->setInt(1, bookId);
            updateBook->executeUpdate();

            cout << "Book successfully returned.\n";
        }
        else {
            cout << "This book is not currently rented.\n";
        }
    }
    catch (sql::SQLException& e) {
        cerr << "Failed to return book: " << e.what() << endl;
    }
}

// View rental list
void listRentals() {
    try {
        unique_ptr<sql::PreparedStatement> selectQuery(
            con->prepareStatement(R"(
                SELECT r.rental_id, b.title, m.name, r.rented_at, r.returned_at
                FROM rentals r
                JOIN books b ON r.book_id = b.book_id
                JOIN members m ON r.member_id = m.member_id
                ORDER BY r.rented_at DESC
                where r.returned_at is null
            )")
        );
        unique_ptr<sql::ResultSet> res(selectQuery->executeQuery());

        while (res->next()) {
            cout << "[Rental ID: " << res->getInt("rental_id") << "] "
                << res->getString("title") << " / "
                << res->getString("name") << " / "
                << res->getString("rented_at") << " / Returned: ";

            if (res->isNull("returned_at"))
                cout << "Not returned yet" << endl;
            else
                cout << res->getString("returned_at") << endl;
        }
    }
    catch (sql::SQLException& e) {
        cerr << "Failed to fetch rental list: " << e.what() << endl;
    }
}
