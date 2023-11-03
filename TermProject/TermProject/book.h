#include<iostream>
#include<string>
using namespace std;

class Book {
private:
    std::string bookname; // 책이름
    std::string writer;   // 저자
    std::string publisher; // 출판사
    std::string genre;    // 책 장르(분야)
    float numbering;      // 책 고유번호
    float star_point;     // 별점
    std::string review;   // 리뷰
    int page;             // 페이지 수
    bool rent;            // 대여 여부


public:
    // 생성자
    Book(const std::string& bookName, const std::string& writer, const std::string& publisher, const std::string& genre, float numbering, float starPoint, const std::string& review, int page, bool rent);

    // 접근자 (Getter)
    std::string getBookName() const;
    std::string getWriter() const;
    std::string getPublisher() const;
    std::string getGenre() const;
    float getNumbering() const;
    float getStarPoint() const;
    std::string getReview() const;
    int getPage() const;
    bool isRented() const;

    // 수정자 (Setter)
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