#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

// Book Ŭ����: ���� ������ ��Ÿ���� Ŭ����
class Book {
private:
    // ���� ������ �Ӽ���
    string bookname;
    string writer;
    string publisher;
    string genre;
    float numbering;
    float star_point;
    string review;
    int page;
    bool rent;
    string rentingMemberId; // �뿩 ���� ȸ���� ���̵�

public:
    // ������: ���� ������ �ʱ�ȭ
    Book(const string& bookName, const string& writer, const string& publisher, const string& genre, float numbering, float starPoint, const string& review, int page, bool rent, string rentId)
        : bookname(bookName), writer(writer), publisher(publisher), genre(genre), numbering(numbering), star_point(starPoint), review(review), page(page), rent(rent), rentingMemberId(rentId) {}

    // Getter �޼����: �Ӽ����� ��ȯ
    string getBookName() const {
        return bookname;
    }
    string getWriter() const {
        return writer;
    }
    string getPublisher() const {
        return publisher;
    }
    string getGenre() const {
        return genre;
    }
    float getNumbering() const {
        return numbering;
    }
    float getStarPoint() const {
        return star_point;
    }
    string getReview() const {
        return review;
    }
    int getPage() const {
        return page;
    }
    bool isRented() const {
        return rent;
    }

    // Setter �޼����: �Ӽ����� ����
    void setBookName(const string& bookName) {
        bookname = bookName;
    }
    void setWriter(const string& writer) {
        this->writer = writer;
    }
    void setPublisher(const string& publisher) {
        this->publisher = publisher;
    }
    void setGenre(const string& genre) {
        this->genre = genre;
    }
    void setNumbering(float numbering) {
        this->numbering = numbering;
    }
    void setStarPoint(float starPoint) {
        star_point = starPoint;
    }
    void setReview(const string& review) {
        this->review = review;
    }
    void setPage(int page) {
        this->page = page;
    }
    void setRentStatus(bool rent) {
        this->rent = rent;
    }

    // ���� ������ ȭ�鿡 ����ϴ� �޼���
    void display() const {
        cout << "------------------------" << endl;
        cout << "���� �̸�: " << bookname << endl;
        cout << "����: " << writer << endl;
        cout << "���ǻ�: " << publisher << endl;
        cout << "�帣: " << genre << endl;
        cout << "������ȣ: " << numbering << endl;
        cout << "������ ��: " << page << endl;
        cout << "�뿩 ����: " << (rent ? "�뿩 ��" : "�뿩 ����") << endl;


        //------- �߰� ------//
        cout << "����: " << star_point << endl;
        cout << "���� ����: " << endl;
        displayReview();
        cout << "------------------------" << endl;
    }

    string getRentingMemberId() const {
        return rentingMemberId;
    }

    // �뿩 ���� ����
    void setRentingStatus(bool rent, const string& memberId) {
        this->rent = rent;
        rentingMemberId = memberId;
    }


    //------- �߰� ------//

    //Ư�� Ű���尡 ���� ���� �Ǵ� ���ڿ� ���ԵǾ� �ִ��� Ȯ��
    bool containsKeyword(const string& keyword) const {
        return (getBookName().find(keyword) != string::npos) || (getWriter().find(keyword) != string::npos);
    }

    //���並 ȭ�鿡 ����ϴ� �Լ� �߰�
    void displayReview() const {
        ifstream reviewFile(getBookName() + "review.txt");

        if (reviewFile.is_open()) {
            string review;
            while (getline(reviewFile, review)) {
                cout << " - " << review << endl;
            }
            reviewFile.close();
        }
        else {
            cout << "* ��ϵ� ���䰡 �����ϴ�." << endl;
        }
    }

    //------- �߰� ------//
};


class Member {
protected:
    string id;
    string pw;
    string name;
    string job;

private:
    vector<string> rentedBooks; // �뿩 ���� å���� �̸��� �����ϴ� ����

public:
    Member(const string& memberId, const string& password, const string& memberName, const string& memberJob)
        : id(memberId), pw(password), name(memberName), job(memberJob) {}

    string getId() const {
        return id;
    }

    string getPassword() const {
        return pw;
    }

    string getName() const {
        return name;
    }

    string getJob() const {
        return job;
    }

    const vector<string>& getRentedBooks() const {
        return rentedBooks;
    }

    // �뿩�� å �߰�
    void addRentedBook(const string& bookName) {
        rentedBooks.push_back(bookName);
    }

    // �뿩�� å ����
    void removeRentedBook(const string& bookName) {
        auto it = find(rentedBooks.begin(), rentedBooks.end(), bookName);
        if (it != rentedBooks.end()) {
            rentedBooks.erase(it);
        }
    }


    void check_rentedBooks(string& id) { // ������ �߰���(ȸ���� �ؽ�Ʈ ���� ��� ���� å����� ���)
        ifstream file(id + "_rentedbook.txt");
        string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                cout << line << std::endl; // �� �پ� ���
            }
            file.close();
        }
        else {
            cout << "������ �� �� �����ϴ�." << std::endl;
        }

    }


    virtual void display() const {
        cout << "���̵�: " << id << endl;
        cout << "��й�ȣ: " << pw << endl;
        cout << "�̸�: " << name << endl;
        cout << "����: " << job << endl;

    }
};


class User : public Member {
private:
    vector<User> users;
    int booklimit; // �뿩 ������ �� ��
    int daylimit;  // �뿩 ���� �Ⱓ 

public:
    User(const string& memberId, const string& password, const string& memberName, const string& memberJob,
        int bookLimit, int daysLimit)
        : Member(memberId, password, memberName, memberJob), booklimit(bookLimit), daylimit(daysLimit) {
    }


    User(const string& memberId, const string& password, const string& memberName, const string& memberJob) :Member(memberId, password, memberName, memberJob) {
        Load_Member_File();
    }

    int getBookLimit() const {
        return booklimit;
    }

    int getDaysLimit() const {
        return daylimit;
    }

    void setBookLimit(int bookLimit) {
        booklimit = bookLimit;
    }

    void setDaysLimit(int daysLimit) {
        daylimit = daysLimit;
    }


    void display() const {
        Member::display();
        cout << "�뿩 ���� �� ��: " << booklimit << endl;
        cout << "�뿩 ���� �Ⱓ: " << daylimit << "��" << endl;
    }


    void save_Member_File() {
        ofstream file("members.txt");
        if (file.is_open()) {
            for (const User& user : users) {
                file << user.getId() << " " << user.getPassword() << " " << user.getName() << " " << user.getJob() << " " << user.getBookLimit() << " " << user.getDaysLimit() << endl;
            }
            file.close();
        }
    }

    void Load_Member_File() {
        ifstream file("members.txt");
        if (file.is_open()) {
            users.clear();
            string id, password, name, job;
            int booklimit, dayslimit;
            while (file >> id >> password >> name >> job >> booklimit >> dayslimit) {
                User user(id, password, name, job, booklimit, dayslimit);
                users.push_back(user);

            }
            file.close();
        }
    }
};


class Student : public User {
public:
    Student(const string& memberId, const string& password, const string& memberName, const string& memberJob)
        : User(memberId, password, memberName, memberJob, 5, 14) {}
};

class Professor : public User {
public:
    Professor(const string& memberId, const string& password, const string& memberName, const string& memberJob)
        : User(memberId, password, memberName, memberJob, 10, 28) {}
};

class PostgraduateStudent : public User {
public:
    PostgraduateStudent(const string& memberId, const string& password, const string& memberName, const string& memberJob)
        : User(memberId, password, memberName, memberJob, 5, 14) {}
};




// BookSystem Ŭ����: ���� ���� �ý����� ��Ÿ���� Ŭ����
class BookSystem {
private:
    // ���� ����� �����ϴ� ����
    vector<Book> books;
    string currentMemberId; // ���� �α����� ȸ���� ���̵�

public:
    // ������: ���Ͽ��� ���� ������ �о��
    BookSystem() {
        Load_Book_File();
    }

    BookSystem(string memberId) : currentMemberId(memberId) {
        Load_Book_File();
    }
    // ���� �߰� �޼���: ���ο� ������ ���� ��Ͽ� �߰��ϰ� ���Ͽ� ����
    void add_Book(Book& book) { // �������� ������ �޼���


        float number = book.getNumbering();
        for (const Book& book1 : books) {
            if (book1.getGenre() == book.getGenre()) {
                if (number < book1.getNumbering()) number = book1.getNumbering();
            }
        }
        number += 1;
        book.setNumbering(number);
        books.push_back(book);
        save_Book_File();
    }

    bool rent_Book(const string& bookName, const string& memberId) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getBookName() == bookName;
            });

        if (it != books.end()) {
            if (!it->isRented()) {
                it->setRentingStatus(true, memberId);
                save_Book_File();
                cout << bookName << "��(��) �뿩�Ǿ����ϴ�." << endl;
                return true; // �뿩 ���� �� true ��ȯ
            }

            else {
                cout << bookName << "��(��) �̹� �뿩 ���Դϴ�." << endl;
            }
        }
        else {
            cout << bookName << "��(��)��� ������ �����ϴ�." << endl;
        }

        return false; // �뿩 ���� �� false ��ȯ
    }




    // ���� �ݳ� �޼���: Ư�� ������ �ݳ��ϰ� ���Ͽ� ����
    bool return_Book(const string& bookName, const string& memberId) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getBookName() == bookName && book.isRented() && book.getRentingMemberId() == memberId;
            });

        if (it != books.end()) {
            // ����ڿ��� ���� �Է� �ޱ�
            float userRating;
            cout << "������ ���� ������ �Է��ϼ��� (0.0���� 5.0����): ";
            cin >> userRating;

            // ���� ������ ������ ������Ʈ�ϰ� �ݳ� ó��
            float currentRating = it->getStarPoint();
            float newRating = (currentRating + userRating) / 2.0;  // ���÷� ������ ��� ���

            // ���� �ڵ� //
            it->setStarPoint(newRating);
            it->setRentingStatus(false, "����");
            save_Book_File();
            // ���� �ڵ� //
            // 
            // 
            // ���� �Է� �ޱ�
            string review;
            cout << bookName << "�� ���並 �ۼ����ּ���: ";
            cin.ignore();
            getline(cin, review);
            saveReview(bookName, review);


            cout << bookName << " ��(��) �ݳ��Ǿ����ϴ�." << endl;
            return true; // ���������� �ݳ��� ��� true ��ȯ
        }
        else {
            cout << "�ش� ������ �뿩 ���� ȸ���� �ƴϰų� ������ �������� �ʽ��ϴ�." << endl;
            return false; // �ݳ� ������ ��� false ��ȯ
        }
    }

    void saveReview(const string& bookName, const string& review) { //(����)�������� �ۼ�
        ofstream reviewFile(bookName + "review.txt", ios::app);
        if (reviewFile.is_open()) {
            reviewFile << review << endl;
            reviewFile.close();
        }
    }

    // ���� ��� ��ȯ �޼���
    const vector<Book>& getBooks() const {

        return books;
    }

    // ���� ���� �޼���: ���� ��Ͽ��� Ư�� ������ �����ϰ� ���Ͽ� ����
    void remove_Book(const string& book_Name) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getBookName() == book_Name;
            });

        if (it != books.end()) {
            books.erase(it);
            save_Book_File();
            cout << book_Name << "�� ���� �Ǿ����ϴ�." << endl;
        }
        else {
            cout << book_Name << "�̶�� ������ �����ϴ�." << endl;
        }
    }

    void book_and_app() {
        save_Book_File();
    }

    //���� �˻� �޼���: Ư�� ������ �˻��Ͽ� ������ ���
    void searchBooks(const string& keyword) const {
        const vector<Book>& books = getBooks();
        bool found = false;

        for (const Book& book : books) {
            if (book.containsKeyword(keyword)) {
                book.display();
                found = true;
            }
        }

        if (!found) {
            cout << "�˻� ����� �����ϴ�." << endl;
        }
    }

private:
    // ���Ͽ��� å ���� �о����
    void Load_Book_File() {
        ifstream file("books.txt");

        if (file.is_open()) {
            books.clear();

            string bookName, writer, publisher, genre, review, getRentingMemberId;
            float numbering, starPoint;
            int page;
            bool rent;

            while (file >> bookName >> writer >> publisher >> genre >> numbering >> starPoint >> review >> page >> rent >> getRentingMemberId) {
                Book book(bookName, writer, publisher, genre, numbering, starPoint, review, page, rent, getRentingMemberId);
                books.push_back(book);
            }

            file.close();
        }
    }

    // å ������ ���Ͽ� �����ϱ�
    void save_Book_File() {
        ofstream file("books.txt");

        if (file.is_open()) {
            for (const Book& book : books) {
                file << book.getBookName() << " " << book.getWriter() << " " << book.getPublisher() << " " << book.getGenre()
                    << " " << book.getNumbering() << " " << book.getStarPoint() << " " << book.getReview() << " " << book.getPage()
                    << " " << (book.isRented() ? 1 : 0) << " " << book.getRentingMemberId() << endl;
            }
            file.close();
        }
    }
};

// Admin Ŭ����: ������ ������ ��Ÿ���� Ŭ����
class Admin : public Member {
public:
    Admin(const string& adminId, const string& password, const string& adminName, const string& adminJob)
        : Member(adminId, password, adminName, adminJob) {}
};


class MemberSystem {
private:
    vector<Member> members;
    vector<Admin> admins;  // ������ ������ �����ϴ� ����
    vector<User> users;
public:

    MemberSystem() {
        Load_Member_File();
        Load_Admin_File();  // ������ ���� ���� �ε�
    }

    void signUp(const User& user) {
        if (isDuplicateId(user.getId())) {
            cout << "�̹� �����ϴ� ���̵��Դϴ�. �ٸ� ���̵� ����� �ּ���." << endl;
            return;
        }

        //users.push_back(user);


        if (user.getJob() == "���л�") {
            Student student(user.getId(), user.getPassword(), user.getName(), user.getJob());

            cout << "student" << user.getId() << endl;
            users.push_back(student);
        }
        else if (user.getJob() == "����") {
            Professor professor(user.getId(), user.getPassword(), user.getName(), user.getJob());

            cout << "professor" << user.getId() << endl;
            users.push_back(professor);
        }
        else if (user.getJob() == "���п���") {
            PostgraduateStudent postgraduateStudent(user.getId(), user.getPassword(), user.getName(), user.getJob());

            cout << "poststudent" << user.getId() << endl;
            users.push_back(postgraduateStudent);
        }



        save_Member_File();
        cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << endl;
    }



    bool isDuplicateId(const string& id) const {
        // ��� ���Ϳ��� ���̵� �̹� �����ϴ��� Ȯ���մϴ�.
        for (const Member& member : members) {
            if (member.getId() == id) {
                return true; // �ߺ��� ���̵� �߰�
            }
        }

        for (const Admin& admin : admins) {
            if (admin.getId() == id) {
                return true;
            }
        }

        return false;
    }


    bool login(const string& id, const string& password) {
        for (const User& user : users) {
            if (user.getId() == id && user.getPassword() == password) {
                cout << "�α��� ����!" << endl;
                return true;
            }
        }
        cout << "�α��� ����. ���̵� ��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
        return false;
    }

    bool isAdmin(const string& id) const {
        // id�� ���������� ���θ� �Ǻ��ϴ� ����
        for (const Admin& admin : admins) {
            if (admin.getId() == id) {
                return true;
            }
        }
        return false;
    }

    void add_Admin(const Admin& admin) {
        admins.push_back(admin);
        save_Admin_File();
        cout << "������ �߰��� �Ϸ�Ǿ����ϴ�." << endl;
    }

    bool deleteMember(const string& id) {
        auto it = find_if(members.begin(), members.end(), [&](const Member& member) {
            return member.getId() == id;
            });

        if (it != members.end()) {
            members.erase(it);
            Load_Member_File();
            cout << id << " ȸ���� �����Ǿ����ϴ�." << endl;
            return true;
        }
        else {
            cout << "�ش� ���̵��� ȸ���� ã�� �� �����ϴ�." << endl;
            return false;
        }
    }

    bool rentBook(const string& memberId, const string& bookName) {
        auto it = find_if(members.begin(), members.end(), [&](const Member& member) {
            return member.getId() == memberId;
            });

        if (it != members.end()) {
            it->addRentedBook(bookName);
            save_Member_File();
            cout << bookName << "��(��) �뿩�Ǿ����ϴ�." << endl;
            return true;
        }
        else {
            cout << "�ش� ���̵��� ȸ���� ã�� �� �����ϴ�." << endl;
            return false;
        }
    }

    // å �ݳ� ��� �߰�
    bool returnBook(const string& memberId, const string& bookName) {
        auto it = find_if(members.begin(), members.end(), [&](const Member& member) {
            return member.getId() == memberId;
            });

        if (it != members.end()) {
            it->removeRentedBook(bookName);
            save_Member_File();
            cout << bookName << "��(��) �ݳ��Ǿ����ϴ�." << endl;
            return true;
        }
        else {
            cout << "�ش� ���̵��� ȸ���� ã�� �� �����ϴ�." << endl;
            return false;
        }
    }

    void saveRentedBook(const string& bookName, const string& memberId) { //"���"���Ͽ� �뿩�ߴ� ���� ����
        ofstream rentedFile(memberId + "_rentedbook.txt", ios::app);
        if (rentedFile.is_open()) {
            rentedFile << bookName << endl;
            rentedFile.close();
        }
    }


    void check_rentedBooks(string& memberId) { // ������ �߰�(ȸ�� ���� �����ϸ� ���Ͽ� �����ϴ� ��� Ŭ���� �޼��� ����)
        auto it = find_if(users.begin(), users.end(), [&](const Member& member) {
            return member.getId() == memberId;
            });
        if (it != users.end()) {
            it->check_rentedBooks(memberId);
        }

    }



    void displayMembers() {
        if (members.empty()) {
            cout << "ȸ�� ����� ��� �ֽ��ϴ�." << endl;
        }
        else {
            cout << "ȸ�� ���: " << endl;
            for (size_t i = 0; i < members.size(); ++i) {
                cout << "ȸ�� ��ȣ: " << i + 1 << endl;
                members[i].display();
                cout << "-------------------" << endl;
            }

            int deleteMemberNumber;
            cout << "������ ȸ���� ��ȣ�� �Է��ϼ��� (0: ���): ";
            cin >> deleteMemberNumber;

            if (deleteMemberNumber > 0 && deleteMemberNumber <= members.size()) {
                // ȸ�� ����
                removeMemberByIndex(deleteMemberNumber - 1);
            }
            else if (deleteMemberNumber != 0) {
                cout << "�߸��� ȸ�� ��ȣ�Դϴ�." << endl;
            }
        }
    }

    string getPasswordFromUser() {
        string password = "";
        char ch;
        while (true) {
            ch = _getch(); // Ű �Է��� �н��ϴ�.
            if (ch == 13) // Enter Ű�� �ԷµǸ� �Է� ����.
                break;
            else if (ch == 8) { // �齺���̽� Ű�� �ԷµǸ� ������ ���� ����.
                if (password.length() > 0) {
                    password.pop_back();
                    cout << "\b \b"; // �齺���̽��� ���� ���� ���ڸ� ȭ�鿡�� ����ϴ�.
                }
            }
            else {
                password.push_back(ch); // ��й�ȣ�� ���� �߰�.
                cout << '*'; // ��ǥ�� ǥ��.
            }
        }
        cout << endl;
        return password;
    }

    const vector<string>& getRentedBooks(const string& memberId) const {
        auto it = find_if(members.begin(), members.end(), [&](const Member& member) {
            return member.getId() == memberId;
            });

        if (it != members.end()) {
            return it->getRentedBooks();
        }
        else {
            static const vector<string> empty;
            return empty;
        }
    }

private:

    void Load_Member_File() {
        ifstream file("members.txt");
        if (file.is_open()) {
            users.clear();
            string id, password, name, job;
            int booklimit, dayslimit;
            while (file >> id >> password >> name >> job >> booklimit >> dayslimit) {
                //Member member(id, password, name, job);
                User user(id, password, name, job, booklimit, dayslimit);
                users.push_back(user);

            }
            file.close();
        }
    }


    void save_Member_File() {
        ofstream file("members.txt");
        if (file.is_open()) {
            for (const User& user : users) {
                file << user.getId() << " " << user.getPassword() << " " << user.getName() << " " << user.getJob() << " " << user.getBookLimit() << " " << user.getDaysLimit() << endl;
            }
            file.close();
        }
    }

    void removeMemberByIndex(int index) {
        members.erase(members.begin() + index);
        save_Member_File();
        cout << "ȸ�� ������ �Ϸ�Ǿ����ϴ�." << endl;
    }

    bool deleteMemberByNumber(int memberNumber) {
        if (memberNumber > 0 && memberNumber <= members.size()) {
            removeMemberByIndex(memberNumber - 1);
            return true;
        }
        else {
            cout << "�߸��� ȸ�� ��ȣ�Դϴ�." << endl;
            return false;
        }
    }

    void Load_Admin_File() {
        ifstream file("admins.txt");
        if (file.is_open()) {
            admins.clear();
            string id, password, name, job;
            while (file >> id >> password >> name >> job) {
                Admin admin(id, password, name, job);
                admins.push_back(admin);
            }
            file.close();
        }
    }


    void save_Admin_File() {
        ofstream file("admins.txt");
        if (file.is_open()) {
            for (const Admin& admin : admins) {
                file << admin.getId() << " " << admin.getPassword() << " " << admin.getName() << " " << admin.getJob() << endl;
            }
            file.close();
        }
    }
};

class App {
public:
    virtual void run() = 0;
};

class AdminApp : public App {
private:
    BookSystem system;
    MemberSystem& memberSystem;

public:
    AdminApp(BookSystem& bookSystem, MemberSystem& mSystem)
        : system(bookSystem), memberSystem(mSystem) {}

    void run() override {
        while (true) {
            showMenu();
            int choice = getChoice();

            switch (choice) {
            case 0:
                cout << "���α׷��� �����մϴ�." << endl;
                return;
            case 1:
                displayBooks();
                break;
            case 2: {
                if (!displayBooks()) {
                    break;
                }
                string bookName;

                cout << "������ ���� �̸��� �Է��ϼ���: ";
                cin.ignore();
                getline(cin, bookName);
                system.remove_Book(bookName);
                break;
            }
            case 3:
                addBook();
                break;
            case 4:
                displayMembers();
                break;
            case 5: {
                string deleteId;
                cout << "ȸ�� ����" << endl;
                cout << "������ ȸ���� ���̵�: ";
                cin >> deleteId;
                memberSystem.deleteMember(deleteId);
                break;
            }
            case 6:
                addAdmin();  // ���ο� ������ �߰�
                break;
            default:
                cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
            }
        }
    }
private:
    void showMenu() const {
        cout << "1. ���� ��ȸ" << endl;
        cout << "2. ���� ����" << endl;
        cout << "3. ���� �߰�" << endl;
        cout << "4. ȸ�� ��ȸ" << endl;
        cout << "5. ȸ�� ����" << endl;
        cout << "6. ������ �߰�" << endl;
        cout << "0. ����" << endl;
        cout << "�޴� ����: ";
    }

    int getChoice() const {
        int choice;
        cin >> choice;
        return choice;
    }

    bool displayBooks() const {
        const vector<Book>& books = system.getBooks();

        if (books.empty()) {
            cout << "���� ����� ��� �ֽ��ϴ�." << endl;
            return 0;
        }
        else {
            cout << "���� ���: " << endl;
            for (const Book& book : books) {
                book.display();
            }
        }
    }

    void addAdmin() {
        string id = "", password = "", name = "", job = "";
        Admin newAdmin("", "", "", "");

        // ������ ���� �Է�
        cout << "������ �߰�" << endl;
        cout << "���̵�: ";
        cin >> id;
        cout << "��й�ȣ: ";
        cin >> password;
        cout << "�̸�: ";
        cin >> name;
        cout << "����: ";
        cin >> job;
        newAdmin = Admin(id, password, name, job);
        memberSystem.add_Admin(newAdmin);  // ������ �߰� �Լ� ȣ��
    }

    void addBook() {
        try {
            string bookName, writer, publisher, genre, review;
            float starPoint, numbering;
            int gn;

            int page;
            bool rent = 0;
            string rentId = "����";
            cout << "���� �̸�: ";
            cin.ignore();
            getline(cin, bookName);
            cout << "����: ";
            getline(cin, writer);
            cout << "���ǻ�: ";
            getline(cin, publisher);
            cout << "�帣: 1. ��ǻ��, 2 ����, 3.���� 4. �Ҽ�";
            cin >> gn;
            if (gn == 1) { genre = "��ǻ��"; numbering = 100; }
            else if (gn == 2) { genre = "����"; numbering = 200; }
            else if (gn == 3) { genre = "����"; numbering = 300; }
            else if (gn == 4) { genre = "�Ҽ�"; numbering = 400; }
            cout << "����: ";
            cin >> starPoint;
            cout << "����: ";
            cin.ignore();
            getline(cin, review);
            cout << "������ ��: ";
            cin >> page;
            Book newBook(bookName, writer, publisher, genre, numbering, starPoint, review, page,
                rent, rentId);
            system.add_Book(newBook);
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl; // ���� �޽��� ���
        }
    }

    void displayMembers() const {
        memberSystem.displayMembers();
    }

};

class StudentApp : public App {
private:
    BookSystem& system;
    string currentMemberId;
    MemberSystem memberSystem;

public:
    StudentApp(BookSystem& bookSystem, string Id) : system(bookSystem), currentMemberId(Id) {}

    void run() override {
        while (true) {
            showMenu();
            int choice = getChoice();

            switch (choice) {
            case 0:
                cout << "���α׷��� �����մϴ�." << endl;
                return;
            case 1:
                displayBooks();
                break;
            case 2: {
                rentBook();
                break;
            }
            case 3: {
                returnBook();
                break;
            }
            case 4: {
                rentedBooks();
                break;
            }
            case 5: {
                enter_searchBooks();
                break;
            }
            case 6: {//�������� �߰��Ѱ�
                check_rentedBooks();
                break;
            }
            default:
                cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
            }
        }
    }

private:
    void showMenu() const {
        cout << "1. ���� ��ȸ" << endl;
        cout << "2. ���� �뿩" << endl;
        cout << "3. ���� �ݳ�" << endl;
        cout << "4. �뿩���� ���� ��ȸ" << endl;
        cout << "5. ���� �˻�" << endl;
        cout << "6. �뿩�ߴ� ���� ��ȸ" << endl; // �������� �߰��Ѱ�
        cout << "0. ����" << endl;
        cout << "�޴� ����: ";
    }

    int getChoice() const {
        int choice;
        cin >> choice;
        return choice;
    }

    bool displayBooks() const {

        const vector<Book>& books = system.getBooks();

        if (books.empty()) {
            cout << "���� ����� ��� �ֽ��ϴ�." << endl;
            return 0;
        }
        else {
            cout << "���� ���: " << endl;
            for (const Book& book : books) {
                book.display();
            }
        }
    }

    // �뿩 ��� �߰�
    void rentBook() {
        if (currentMemberId.empty()) {
            cout << "�α����� �ʿ��մϴ�." << endl;
            return;
        }

        string bookName;
        cout << "�뿩�� ���� �̸��� �Է��ϼ���: ";
        cin.ignore();
        getline(cin, bookName);

        if (system.rent_Book(bookName, currentMemberId)) {
            memberSystem.rentBook(currentMemberId, bookName);
            memberSystem.saveRentedBook(bookName, currentMemberId); // ������ �߰� (�뿩�Ҷ� �� ȸ�� �ؽ�Ʈ ���Ͽ� å ���� ����)
        }
    }


    // �ݳ� ��� �߰�
    void returnBook() {
        if (currentMemberId.empty()) {
            cout << "�α����� �ʿ��մϴ�." << endl;
            return;
        }

        string bookName;
        cout << "�ݳ��� ���� �̸��� �Է��ϼ���: ";
        cin.ignore();
        getline(cin, bookName);

        if (system.return_Book(bookName, currentMemberId)) {
            memberSystem.returnBook(currentMemberId, bookName);
        }
    }

    void rentedBooks() const { //(����)���� å ��ȸ�ϱ�
        const vector<Book>& books = system.getBooks();
        const vector<string>& rentedBooks = memberSystem.getRentedBooks(currentMemberId);

        if (rentedBooks.empty()) {
            cout << "�뿩 ���� ������ �����ϴ�." << endl;
            return;
        }

        cout << "�뿩 ���� ���� ��� : " << endl;
        for (const string& bookName : rentedBooks) {
            auto it = find_if(books.begin(), books.end(), [&](const Book& book) {
                return book.getBookName() == bookName; });
            if (it != books.end()) {
                it->display();
            }
        }
    }

    void enter_searchBooks() const {  //���� �˻���� �߰�
        string keyword;
        cout << "Ű���� �Է�(���� �Ǵ� ����): ";
        cin.ignore();
        getline(cin, keyword);
        system.searchBooks(keyword);
    }

    void check_rentedBooks() { // �������� �߰��Ѱ�
        cout << "���ݱ��� �뿩�ߴ� å�� ������ �����帮�ڽ��ϴ�" << endl;
        memberSystem.check_rentedBooks(currentMemberId);
    }

};

class LoginApp : public App {
private:
    MemberSystem& memberSystem;

public:

    LoginApp(MemberSystem& memSys)
        : memberSystem(memSys) {}

    void run() override {
        while (true) {
            showMenu();
            int choice = getChoice();

            switch (choice) {
            case 0:
                cout << "���α׷��� �����մϴ�." << endl;
                return;
            case 1:
                login();
                break;
            case 2:
                signup();
                break;
            default:
                cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
            }
        }
    }

private:
    void showMenu() const {
        cout << "1. �α���" << endl;
        cout << "2. ȸ�� ����" << endl;
        cout << "0. ����" << endl;
        cout << "��ɾ� ����: ";
    }
    int getChoice() const {
        int choice;
        cin >> choice;
        return choice;
    }

    void login() {
        BookSystem bookSystem;
        string id = "", password = "";
        cout << "�α���" << endl;
        cout << "���̵�: ";
        cin >> id;
        cin.ignore();
        cout << "��й�ȣ: ";
        password = memberSystem.getPasswordFromUser();

        if (memberSystem.isAdmin(id)) {
            // ������ �α���
            AdminApp adminApp(bookSystem, memberSystem);
            adminApp.run();
        }
        else if (memberSystem.login(id, password)) {
            // �л� �α���
            cout << "�α��� ����!" << endl;
            StudentApp studentApp(bookSystem, id);
            studentApp.run();
        }
        else {
            cout << "�α��� ����. ���̵� ��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
        }
    }

    void signup() {
        string id = "", password = "", name = "", job = "";
        User newUser("", "", "", "", 0, 0);

        // ȸ�� ���� �Է�
        cout << "ȸ������" << endl;
        cout << "���̵�: ";
        cin >> id;
        cout << "��й�ȣ: ";
        cin >> password;
        cout << "�̸�: ";
        cin >> name;
        cout << "����: ";
        cin >> job;
        newUser = User(id, password, name, job); // ���÷� bookLimit�� daysLimit�� �ʱⰪ���� ����
        memberSystem.signUp(newUser);                   // ȸ������ �Լ� ȣ��

    }
};

int main() {

    MemberSystem memberSystem;

    LoginApp loginApp(memberSystem);
    loginApp.run();

    return 0;
}