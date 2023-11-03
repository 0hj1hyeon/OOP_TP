
#include<iostream>
#include<string>
using namespace std;

class Member {

    std::string id;
    std::string pw;
    std::string name;
    std::string job;

	int booklimit; // 대여가능한 권 수
	int daylimit; // 대여 가능 기간

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
};





