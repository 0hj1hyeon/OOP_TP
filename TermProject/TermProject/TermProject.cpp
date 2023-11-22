#include "book.h"
#include "member.h"
#include "booksystem.h"
#include "membersystem.h"
//도서를 벡터로 저장(코드 합치면 없어질듯)
void AddBookToLibrary(vector<Book>& library, const Book& book) {
    library.push_back(book);  //벡터에 객체 저장
}

//도서 검색
void searchBooks(const vector<Book>& library, const string& searchKeyword) {  //333,4444 도서검색 
    bool found = false;  //부울 변수를 거짓으로 지정. found는 검색어가 유효한지를 나타냄
    cout << "\"" << searchKeyword << "\"에 대한 검색결과" << endl;
    for (const Book& book : library) {  //library안의 객체를 반복
        // 검색어가 도서 이름 또는 저자에 포함되는지 확인
        if (book.getBookName().find(searchKeyword) != string::npos || book.getWriter().find(searchKeyword) != string::npos) {
            //책 제목이나 저자 중에 검색어를 찾지 못한것이 아니라면; 검색어를 찾았다면
            cout << "제목: " << book.getBookName() << endl;
            cout << "저자: " << book.getWriter() << endl;
            cout << "출판사: " << book.getPublisher() << endl;
            cout << "장르: " << book.getGenre() << std::endl;
            cout << "고유번호: " << book.getNumbering() << endl;
            cout << "페이지 수: " << book.getPage() << endl;
            cout << "대여 여부: " << (book.isRented() ? "Yes" : "No") << endl;  //대여 여부에 따라 다른 출력
            cout << "평점: " << book.getStarPoint() << endl;
            cout << "리뷰: " << book.getReview() << endl;
            found = true; //found를 true로
        }
    }

    if (!found) {  //found가 fasle라면; 찾지 못한다면
        cout << "해당 검색어의 결과를 찾을 수 없습니다." << endl;
    }
}

class NotReturned : public exception {
public:
    virtual const char* what() const throw() {  //가상함수로 
        return "Error: 책이 반납되지 않았습니다. 반납 후 리뷰를 작성할 수 있습니다.";
    }
};

void addReview(Member& member, Book& book, float starPoint, const string& review) { // 666 리뷰등록 
    try {
        //책의 대여 상태 확인
        if (book.isRented()) {
            //책 정보 출력
            cout << "Book Information:\n";
            book.BookInfo();

            //별점 및 리뷰 등록
            book.setStarPoint(starPoint);
            book.setReview(review);

            cout << "리뷰가 성공적으로 등록되었습니다. " << book.getBookName() << "'.\n";
        }
        else {
            //대여되지 않은 책에 대한 오류 출력
            throw NotReturned();
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
}


int main()
{
    std::cout << "Hello World!\n";
}

