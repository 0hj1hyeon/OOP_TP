<<<<<<< HEAD
#include "book.h"
#include<iostream>
#include<string>
#include <vector>
=======
#include<iostream>
#include<string>
#include <vector>
#include "book.h" // Book 클래스 정의가 있는 헤더 파일을 포함합니다
>>>>>>> 8adb0e24c409e98410d362b8b8f537ed63f162a9
using namespace std;

class Member {

    std::string id;
    std::string pw;
    std::string name;
    std::string job;
    std::vector<Book> bookCollection; // Book 객체를 저장하는 벡터

	int booklimit; // 대여가능한 권 수
	int daylimit; // 대여 가능 기간
    vector<Book> borrowedBooks; // 책 저장

public:
    // 생성자
    Member(const std::string& memberId, const std::string& password, const std::string& memberName, const std::string& memberJob, int bookLimit, int daysLimit);

    // 접근자 (Getter)
    std::string getId() const;
    std::string getPassword() const;
    std::string getName() const;
    std::string getJob() const;
    int getBookLimit() const;
    int getDaysLimit() const;

    // 설정자 (Setter)
    void setId(const std::string& memberId);
    void setPassword(const std::string& password);
    void setName(const std::string& memberName);
    void setJob(const std::string& memberJob);
    void setBookLimit(int bookLimit);
    void setDaysLimit(int daysLimit);

    // Book 객체 벡터에 관련된 메서드
    void addBook(const Book& newBook);
    void removeBook(const std::string& bookName);
    void displayBooks() const;
};





