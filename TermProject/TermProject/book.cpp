#include "book.h"

// ������ ����
Book::Book(const std::string& bookName, const std::string& writer, const std::string& publisher, const std::string& genre, float numbering, float starPoint, const std::string& review, int page, bool rent)
    : bookname(bookName), writer(writer), publisher(publisher), genre(genre), numbering(numbering), star_point(starPoint), review(review), page(page), rent(rent) {}

// ������ �޼��� ����
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

// ������ �޼��� ����
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
    ofstream file(getBookName() + "_review.txt");  //å����_review.txt ������ ���� ���� 
    if (file.is_open()) {  //������ �����ٸ�
        file << review;  //���並 ��
        file.close();  //������ ����
    }
    else  //������ ������ ����
        cout << "���� ���� �߻�" << endl;
}

//���並 ���Ͽ��� �ҷ���(����ó�� ���)
void Book::readReviewFile() {
    try {  //���� ó��
        ifstream file(getBookName() + "_review.txt");  //å ����_reveiw.txt ������ �б� ����

        if (file.is_open()) {  //������ �����ٸ�
            getline(file, review);  //review�� ������ ���Ͽ� ����
            file.close();  //������ ����
        }
        else {  //������ ������ ������ ���� �߻�, ���� �޼��� ���
            throw runtime_error("������ �� �� �����ϴ�.");
        }
    }
    catch (const exception& e) {  //���� �߻� ��
        cerr << "���� �б� ���� �߻�: " << e.what() << endl;  //�����޼��� ���
    }
}

//��ü ���� Ȯ��
bool Book:: checkOverdue() const {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);


    //�뿩�� ��¥���� �뿩 ���� �Ⱓ�� ���� ��¥
    tm dueDate = ltm;
    dueDate.tm_mday += (getDaysLimit() - 1);

    //���� ��¥�� ��ü ��¥�� �������� Ȯ��
    return difftime(mktime(&dueDate), now) < 0;
}
};
