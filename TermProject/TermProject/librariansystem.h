#include "booksystem.h"
#include "membersystem.h"

class LibrarianSystem {

public:
	BookSystem bs;
	MemberSystem ms;

    // ���� �߰� �޼���: ���ο� ������ ���� ��Ͽ� �߰��ϰ� ���Ͽ� ����
    void add_Book(const Book& book) {
        books.push_back(book);
        bs.save_Book_File();
    }

    // ���� ���� �޼���: ���� ��Ͽ��� Ư�� ������ �����ϰ� ���Ͽ� ����
    void remove_Book(const string& book_Name) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getBookName() == book_Name;
            });

        if (it != books.end()) {
            books.erase(it);
            bs.save_Book_File();
            cout << book_Name << "�� ���� �Ǿ����ϴ�." << endl;
        }
        else {
            cout << book_Name << "�̶�� ������ �����ϴ�." << endl;
        }
    }



};