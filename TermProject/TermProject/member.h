
#include<iostream>
#include<string>
using namespace std;

class Member {

    std::string id;
    std::string pw;
    std::string name;

	int booklimit; // �뿩������ �� ��
	int daylimit; // �뿩 ���� �Ⱓ

public:
    // ������
    Member(const std::string& memberId, const std::string& password, const std::string& memberName, int bookLimit, int daysLimit);

    // ������ (Getter)
    std::string getId() const;
    std::string getPassword() const;
    std::string getName() const;
    int getBookLimit() const;
    int getDaysLimit() const;

    // ������ (Setter)
    void setId(const std::string& memberId);
    void setPassword(const std::string& password);
    void setName(const std::string& memberName);
    void setBookLimit(int bookLimit);
    void setDaysLimit(int daysLimit);
};





