#include "booksystem.h"
#include "membersystem.h"

class LibrarianSystem {

public:
	BookSystem bs;
	MemberSystem ms;

    // 도서 추가 메서드: 새로운 도서를 도서 목록에 추가하고 파일에 저장
    void add_Book(const Book& book) {
        books.push_back(book);
        bs.save_Book_File();
    }

    // 도서 삭제 메서드: 도서 목록에서 특정 도서를 삭제하고 파일에 저장
    void remove_Book(const string& book_Name) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getBookName() == book_Name;
            });

        if (it != books.end()) {
            books.erase(it);
            bs.save_Book_File();
            cout << book_Name << "이 삭제 되었습니다." << endl;
        }
        else {
            cout << book_Name << "이라는 도서가 없습니다." << endl;
        }
    }



};