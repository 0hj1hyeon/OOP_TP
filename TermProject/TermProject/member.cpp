#include "member.h" // Member Ŭ���� ���ǰ� �ִ� ��� ������ �����մϴ�.

// ������ ����
Member::Member(const std::string& memberId, const std::string& password, const std::string& memberName, int bookLimit, int daysLimit) {
    id = memberId;
    pw = password;
    name = memberName;
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

void Member::setBookLimit(int bookLimit) {
    booklimit = bookLimit;
}

void Member::setDaysLimit(int daysLimit) {
    daylimit = daysLimit;
}