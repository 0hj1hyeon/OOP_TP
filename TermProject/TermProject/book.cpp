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
int Book::getDayslimits() const {
    return daylimit;
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

void Book::saveReviewToFile() const {
    ofstream file(getBookName() + "_review.txt");  //책제목_review.txt 파일을 쓰기 모드로 
    if (file.is_open()) {  //파일이 열린다면
        file << review;  //리뷰를 씀
        file.close();  //파일을 닫음
    }
    else  //파일이 없으면 오류
        cout << "파일 오류 발생" << endl;
}

//리뷰를 파일에서 불러옴(예외처리 사용)
void Book::readReviewFile() {
    try {  //예외 처리
        ifstream file(getBookName() + "_review.txt");  //책 제목_reveiw.txt 파일을 읽기 모드로

        if (file.is_open()) {  //파일이 열린다면
            getline(file, review);  //review의 문장을 파일에 저장
            file.close();  //파일을 닫음
        }
        else {  //파일이 열리지 않으면 예외 발생, 예외 메세지 출력
            throw runtime_error("파일을 열 수 없습니다.");
        }
    }
    catch (const exception& e) {  //예외 발생 시
        cerr << "파일 읽기 예외 발생: " << e.what() << endl;  //오류메세지 출력
    }
}

//연체 상태 확인
bool Book:: checkOverdue() const {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);


    //대여한 날짜에서 대여 가능 기간을 더한 날짜
    tm dueDate = ltm;
    dueDate.tm_mday += (getDaysLimit() - 1);

    //현재 날짜가 연체 날짜를 지났는지 확인
    return difftime(mktime(&dueDate), now) < 0;
}
};
