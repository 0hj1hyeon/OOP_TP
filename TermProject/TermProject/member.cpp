#include "member.h" // Member Ŭ���� ���ǰ� �ִ� ��� ������ �����մϴ�.

// ������ ����
Member::Member(const std::string& memberId, const std::string& password, const std::string& memberName,const std::string& memberJob, int bookLimit, int daysLimit) {
    id = memberId;
    pw = password;
    name = memberName;
    job = memberJob;
    booklimit = bookLimit;
    daylimit = daysLimit;

}

// ������ �޼��� ����
std::string Member::getId() const {
    return id;
}

std::string Member::getPassword() const {
    return pw;
}

std::string Member::getName() const {
    return name;
}
std::string Member::getJob() const {
    return job;
}

int Member::getBookLimit() const {
    return booklimit;
}

int Member::getDaysLimit() const {
    return daylimit;
}

// ������ �޼��� ����
void Member::setId(const std::string& memberId) {
    id = memberId;
}

void Member::setPassword(const std::string& password) {
    pw = password;
}

void Member::setName(const std::string& memberName) {
    name = memberName;
}

void Member::setJob(const std::string& memberJob) {
    job = memberJob;  
}

void Member::setBookLimit(int bookLimit) {
    booklimit = bookLimit;
}

void Member::setDaysLimit(int daysLimit) {
    daylimit = daysLimit;
}

// Book ��ü ���Ϳ� ���õ� �޼��� ����
void Member::addBook(const Book& newBook) {
    bookCollection.push_back(newBook);
}

void Member::removeBook(const std::string& bookName) {
    // ������ ���ǿ� ���� Book ��ü�� ���Ϳ��� �����ϴ� �ڵ带 �߰��ؾ� �մϴ�.
}

void Member::displayBooks() const {
    // ���Ϳ� �ִ� ��� Book ��ü�� ȭ�鿡 ǥ���ϴ� �ڵ带 �߰��ؾ� �մϴ�.
    for (const Book& book : bookCollection) {
        // �� Book ��ü�� ���� ������ ����ϴ� �ڵ�
    }
}