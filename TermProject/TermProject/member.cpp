#include "member.h" // Member 클래스 정의가 있는 헤더 파일을 포함합니다.

// 생성자 구현
Member::Member(const std::string& memberId, const std::string& password, const std::string& memberName,const std::string& memberJob, int bookLimit, int daysLimit) {
    id = memberId;
    pw = password;
    name = memberName;
    job = memberJob;
    booklimit = bookLimit;
    daylimit = daysLimit;
}

// 접근자 메서드 구현
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

// 수정자 메서드 구현
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