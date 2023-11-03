#include "book.h"

// 생성자 구현
Book::Book(const std::string& bookName, const std::string& writer, const std::string& publisher, const std::string& genre, float numbering, float starPoint, const std::string& review, int page, bool rent)
    : bookname(bookName), writer(writer), publisher(publisher), genre(genre), numbering(numbering), star_point(starPoint), review(review), page(page), rent(rent) {}

// 접근자 메서드 구현
std::string Book::getBookName() const {
    return bookname;
}

std::string Book::getWriter() const {
    return writer;
}

std::string Book::getPublisher() const {
    return publisher;
}

std::string Book::getGenre() const {
    return genre;
}

float Book::getNumbering() const {
    return numbering;
}

float Book::getStarPoint() const {
    return star_point;
}

std::string Book::getReview() const {
    return review;
}

int Book::getPage() const {
    return page;
}

bool Book::isRented() const {
    return rent;
}

// 수정자 메서드 구현
void Book::setBookName(const std::string& bookName) {
    bookname = bookName;
}

void Book::setWriter(const std::string& writer) {
    this->writer = writer;
}

void Book::setPublisher(const std::string& publisher) {
    this->publisher = publisher;
}

void Book::setGenre(const std::string& genre) {
    this->genre = genre;
}

void Book::setNumbering(float numbering) {
    this->numbering = numbering;
}

void Book::setStarPoint(float starPoint) {
    star_point = starPoint;
}

void Book::setReview(const std::string& review) {
    this->review = review;
}

void Book::setPage(int page) {
    this->page = page;
}

void Book::setRentStatus(bool rent) {
    this->rent = rent;
}
