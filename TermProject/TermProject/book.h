#include<iostream>
#include<string>
using namespace std;

class Book {
private:
    std::string bookname; // å�̸�
    std::string writer;   // ����
    std::string publisher; // ���ǻ�
    std::string genre;    // å �帣(�о�)
    float numbering;      // å ������ȣ
    float star_point;     // ����
    std::string review;   // ����
    int page;             // ������ ��
    bool rent;            // �뿩 ����


public:
    // ������
    Book(const std::string& bookName, const std::string& writer, const std::string& publisher, const std::string& genre, float numbering, float starPoint, const std::string& review, int page, bool rent);

    // ������ (Getter)
    std::string getBookName() const;
    std::string getWriter() const;
    std::string getPublisher() const;
    std::string getGenre() const;
    float getNumbering() const;
    float getStarPoint() const;
    std::string getReview() const;
    int getPage() const;
    bool isRented() const;

    // ������ (Setter)
    void setBookName(const std::string& bookName);
    void setWriter(const std::string& writer);
    void setPublisher(const std::string& publisher);
    void setGenre(const std::string& genre);
    void setNumbering(float numbering);
    void setStarPoint(float starPoint);
    void setReview(const std::string& review);
    void setPage(int page);
    void setRentStatus(bool rent);


};