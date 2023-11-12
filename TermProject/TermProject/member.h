
#include<iostream>
#include<string>
#include <vector>
#include "book.h" // Book Ŭ���� ���ǰ� �ִ� ��� ������ �����մϴ�
using namespace std;

class Member {

    std::string id;
    std::string pw;
    std::string name;
    std::string job;
    std::vector<Book> bookCollection; // Book ��ü�� �����ϴ� ����

	int booklimit; // �뿩������ �� ��
	int daylimit; // �뿩 ���� �Ⱓ

public:
    // ������
    Member(const std::string& memberId, const std::string& password, const std::string& memberName, const std::string& memberJob, int bookLimit, int daysLimit);

    // ������ (Getter)
    std::string getId() const;
    std::string getPassword() const;
    std::string getName() const;
    std::string getJob() const;
    int getBookLimit() const;
    int getDaysLimit() const;

    // ������ (Setter)
    void setId(const std::string& memberId);
    void setPassword(const std::string& password);
    void setName(const std::string& memberName);
    void setJob(const std::string& memberJob);
    void setBookLimit(int bookLimit);
    void setDaysLimit(int daysLimit);

    // Book ��ü ���Ϳ� ���õ� �޼���
    void addBook(const Book& newBook);
    void removeBook(const std::string& bookName);
    void displayBooks() const;
};





