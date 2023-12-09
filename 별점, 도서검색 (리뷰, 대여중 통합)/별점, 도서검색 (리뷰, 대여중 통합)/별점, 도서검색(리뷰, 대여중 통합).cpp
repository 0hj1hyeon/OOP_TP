#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

// Book 클래스: 도서 정보를 나타내는 클래스
class Book {
private:
    // 도서 정보의 속성들
    string bookname;
    string writer;
    string publisher;
    string genre;
    float numbering;
    float star_point;
    string review;
    int page;
    bool rent;
    string rentingMemberId; // 대여 중인 회원의 아이디

public:
    // 생성자: 도서 정보를 초기화
    Book(const string& bookName, const string& writer, const string& publisher, const string& genre, float numbering, float starPoint, const string& review, int page, bool rent, string rentId)
        : bookname(bookName), writer(writer), publisher(publisher), genre(genre), numbering(numbering), star_point(starPoint), review(review), page(page), rent(rent), rentingMemberId(rentId) {}

    // Getter 메서드들: 속성값을 반환
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

    // Setter 메서드들: 속성값을 설정
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

    // 도서 정보를 화면에 출력하는 메서드
    void display() const {
        cout << "------------------------" << endl;
        cout << "도서 이름: " << bookname << endl;
        cout << "저자: " << writer << endl;
        cout << "출판사: " << publisher << endl;
        cout << "장르: " << genre << endl;
        cout << "고유번호: " << numbering << endl;
        cout << "페이지 수: " << page << endl;
        cout << "대여 여부: " << (rent ? "대여 중" : "대여 가능") << endl;


        //------- 추가 ------//
        cout << "별점: " << star_point << endl;
        cout << "도서 리뷰: " << endl;
        displayReview();
        cout << "------------------------" << endl;
    }

    string getRentingMemberId() const {
        return rentingMemberId;
    }

    // 대여 상태 설정
    void setRentingStatus(bool rent, const string& memberId) {
        this->rent = rent;
        rentingMemberId = memberId;
    }


    //------- 추가 ------//

    //특정 키워드가 도서 제목 또는 저자에 포함되어 있는지 확인
    bool containsKeyword(const string& keyword) const {
        return (getBookName().find(keyword) != string::npos) || (getWriter().find(keyword) != string::npos);
    }

    //리뷰를 화면에 출력하는 함수 추가
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
            cout << "* 등록된 리뷰가 없습니다." << endl;
        }
    }

    //------- 추가 ------//
};


class Member {
protected:
    string id;
    string pw;
    string name;
    string job;

private:
    vector<string> rentedBooks; // 대여 중인 책들의 이름을 저장하는 벡터

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

    // 대여한 책 추가
    void addRentedBook(const string& bookName) {
        rentedBooks.push_back(bookName);
    }

    // 대여한 책 제거
    void removeRentedBook(const string& bookName) {
        auto it = find(rentedBooks.begin(), rentedBooks.end(), bookName);
        if (it != rentedBooks.end()) {
            rentedBooks.erase(it);
        }
    }


    void check_rentedBooks(string& id) { // 오지현 추가함(회원의 텍스트 파일 열어서 안의 책제목들 출력)
        ifstream file(id + "_rentedbook.txt");
        string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                cout << line << std::endl; // 한 줄씩 출력
            }
            file.close();
        }
        else {
            cout << "파일을 열 수 없습니다." << std::endl;
        }

    }


    virtual void display() const {
        cout << "아이디: " << id << endl;
        cout << "비밀번호: " << pw << endl;
        cout << "이름: " << name << endl;
        cout << "직업: " << job << endl;

    }
};


class User : public Member {
private:
    vector<User> users;
    int booklimit; // 대여 가능한 권 수
    int daylimit;  // 대여 가능 기간 

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
        cout << "대여 가능 권 수: " << booklimit << endl;
        cout << "대여 가능 기간: " << daylimit << "일" << endl;
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




// BookSystem 클래스: 도서 관리 시스템을 나타내는 클래스
class BookSystem {
private:
    // 도서 목록을 저장하는 벡터
    vector<Book> books;
    string currentMemberId; // 현재 로그인한 회원의 아이디

public:
    // 생성자: 파일에서 도서 정보를 읽어옴
    BookSystem() {
        Load_Book_File();
    }

    BookSystem(string memberId) : currentMemberId(memberId) {
        Load_Book_File();
    }
    // 도서 추가 메서드: 새로운 도서를 도서 목록에 추가하고 파일에 저장
    void add_Book(Book& book) { // 오지현이 수정한 메서드


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
                cout << bookName << "이(가) 대여되었습니다." << endl;
                return true; // 대여 성공 시 true 반환
            }

            else {
                cout << bookName << "은(는) 이미 대여 중입니다." << endl;
            }
        }
        else {
            cout << bookName << "이(가)라는 도서가 없습니다." << endl;
        }

        return false; // 대여 실패 시 false 반환
    }




    // 도서 반납 메서드: 특정 도서를 반납하고 파일에 저장
    bool return_Book(const string& bookName, const string& memberId) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getBookName() == bookName && book.isRented() && book.getRentingMemberId() == memberId;
            });

        if (it != books.end()) {
            // 사용자에게 별점 입력 받기
            float userRating;
            cout << "도서에 대한 별점을 입력하세요 (0.0부터 5.0까지): ";
            cin >> userRating;

            // 현재 도서의 별점을 업데이트하고 반납 처리
            float currentRating = it->getStarPoint();
            float newRating = (currentRating + userRating) / 2.0;  // 예시로 간단한 평균 계산

            // 기존 코드 //
            it->setStarPoint(newRating);
            it->setRentingStatus(false, "없음");
            save_Book_File();
            // 기존 코드 //
            // 
            // 
            // 리뷰 입력 받기
            string review;
            cout << bookName << "의 리뷰를 작성해주세요: ";
            cin.ignore();
            getline(cin, review);
            saveReview(bookName, review);


            cout << bookName << " 이(가) 반납되었습니다." << endl;
            return true; // 성공적으로 반납된 경우 true 반환
        }
        else {
            cout << "해당 도서를 대여 중인 회원이 아니거나 도서가 존재하지 않습니다." << endl;
            return false; // 반납 실패한 경우 false 반환
        }
    }

    void saveReview(const string& bookName, const string& review) { //(수정)리뷰파일 작성
        ofstream reviewFile(bookName + "review.txt", ios::app);
        if (reviewFile.is_open()) {
            reviewFile << review << endl;
            reviewFile.close();
        }
    }

    // 도서 목록 반환 메서드
    const vector<Book>& getBooks() const {

        return books;
    }

    // 도서 삭제 메서드: 도서 목록에서 특정 도서를 삭제하고 파일에 저장
    void remove_Book(const string& book_Name) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getBookName() == book_Name;
            });

        if (it != books.end()) {
            books.erase(it);
            save_Book_File();
            cout << book_Name << "이 삭제 되었습니다." << endl;
        }
        else {
            cout << book_Name << "이라는 도서가 없습니다." << endl;
        }
    }

    void book_and_app() {
        save_Book_File();
    }

    //도서 검색 메서드: 특정 도서를 검색하여 정보를 출력
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
            cout << "검색 결과가 없습니다." << endl;
        }
    }

private:
    // 파일에서 책 정보 읽어오기
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

    // 책 정보를 파일에 저장하기
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

// Admin 클래스: 관리자 정보를 나타내는 클래스
class Admin : public Member {
public:
    Admin(const string& adminId, const string& password, const string& adminName, const string& adminJob)
        : Member(adminId, password, adminName, adminJob) {}
};


class MemberSystem {
private:
    vector<Member> members;
    vector<Admin> admins;  // 관리자 정보를 저장하는 벡터
    vector<User> users;
public:

    MemberSystem() {
        Load_Member_File();
        Load_Admin_File();  // 관리자 정보 파일 로드
    }

    void signUp(const User& user) {
        if (isDuplicateId(user.getId())) {
            cout << "이미 존재하는 아이디입니다. 다른 아이디를 사용해 주세요." << endl;
            return;
        }

        //users.push_back(user);


        if (user.getJob() == "대학생") {
            Student student(user.getId(), user.getPassword(), user.getName(), user.getJob());

            cout << "student" << user.getId() << endl;
            users.push_back(student);
        }
        else if (user.getJob() == "교수") {
            Professor professor(user.getId(), user.getPassword(), user.getName(), user.getJob());

            cout << "professor" << user.getId() << endl;
            users.push_back(professor);
        }
        else if (user.getJob() == "대학원생") {
            PostgraduateStudent postgraduateStudent(user.getId(), user.getPassword(), user.getName(), user.getJob());

            cout << "poststudent" << user.getId() << endl;
            users.push_back(postgraduateStudent);
        }



        save_Member_File();
        cout << "회원가입이 완료되었습니다." << endl;
    }



    bool isDuplicateId(const string& id) const {
        // 멤버 벡터에서 아이디가 이미 존재하는지 확인합니다.
        for (const Member& member : members) {
            if (member.getId() == id) {
                return true; // 중복된 아이디 발견
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
                cout << "로그인 성공!" << endl;
                return true;
            }
        }
        cout << "로그인 실패. 아이디나 비밀번호가 일치하지 않습니다." << endl;
        return false;
    }

    bool isAdmin(const string& id) const {
        // id가 관리자인지 여부를 판별하는 로직
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
        cout << "관리자 추가가 완료되었습니다." << endl;
    }

    bool deleteMember(const string& id) {
        auto it = find_if(members.begin(), members.end(), [&](const Member& member) {
            return member.getId() == id;
            });

        if (it != members.end()) {
            members.erase(it);
            Load_Member_File();
            cout << id << " 회원이 삭제되었습니다." << endl;
            return true;
        }
        else {
            cout << "해당 아이디의 회원을 찾을 수 없습니다." << endl;
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
            cout << bookName << "이(가) 대여되었습니다." << endl;
            return true;
        }
        else {
            cout << "해당 아이디의 회원을 찾을 수 없습니다." << endl;
            return false;
        }
    }

    // 책 반납 기능 추가
    bool returnBook(const string& memberId, const string& bookName) {
        auto it = find_if(members.begin(), members.end(), [&](const Member& member) {
            return member.getId() == memberId;
            });

        if (it != members.end()) {
            it->removeRentedBook(bookName);
            save_Member_File();
            cout << bookName << "이(가) 반납되었습니다." << endl;
            return true;
        }
        else {
            cout << "해당 아이디의 회원을 찾을 수 없습니다." << endl;
            return false;
        }
    }

    void saveRentedBook(const string& bookName, const string& memberId) { //"멤버"파일에 대여했던 정보 저장
        ofstream rentedFile(memberId + "_rentedbook.txt", ios::app);
        if (rentedFile.is_open()) {
            rentedFile << bookName << endl;
            rentedFile.close();
        }
    }


    void check_rentedBooks(string& memberId) { // 오지현 추가(회원 정보 존재하면 파일에 저장하는 멤버 클래스 메서드 실행)
        auto it = find_if(users.begin(), users.end(), [&](const Member& member) {
            return member.getId() == memberId;
            });
        if (it != users.end()) {
            it->check_rentedBooks(memberId);
        }

    }



    void displayMembers() {
        if (members.empty()) {
            cout << "회원 목록이 비어 있습니다." << endl;
        }
        else {
            cout << "회원 목록: " << endl;
            for (size_t i = 0; i < members.size(); ++i) {
                cout << "회원 번호: " << i + 1 << endl;
                members[i].display();
                cout << "-------------------" << endl;
            }

            int deleteMemberNumber;
            cout << "삭제할 회원의 번호를 입력하세요 (0: 취소): ";
            cin >> deleteMemberNumber;

            if (deleteMemberNumber > 0 && deleteMemberNumber <= members.size()) {
                // 회원 삭제
                removeMemberByIndex(deleteMemberNumber - 1);
            }
            else if (deleteMemberNumber != 0) {
                cout << "잘못된 회원 번호입니다." << endl;
            }
        }
    }

    string getPasswordFromUser() {
        string password = "";
        char ch;
        while (true) {
            ch = _getch(); // 키 입력을 읽습니다.
            if (ch == 13) // Enter 키가 입력되면 입력 종료.
                break;
            else if (ch == 8) { // 백스페이스 키가 입력되면 마지막 문자 삭제.
                if (password.length() > 0) {
                    password.pop_back();
                    cout << "\b \b"; // 백스페이스를 통해 지운 문자를 화면에서 지웁니다.
                }
            }
            else {
                password.push_back(ch); // 비밀번호에 문자 추가.
                cout << '*'; // 별표로 표시.
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
        cout << "회원 삭제가 완료되었습니다." << endl;
    }

    bool deleteMemberByNumber(int memberNumber) {
        if (memberNumber > 0 && memberNumber <= members.size()) {
            removeMemberByIndex(memberNumber - 1);
            return true;
        }
        else {
            cout << "잘못된 회원 번호입니다." << endl;
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
                cout << "프로그램을 종료합니다." << endl;
                return;
            case 1:
                displayBooks();
                break;
            case 2: {
                if (!displayBooks()) {
                    break;
                }
                string bookName;

                cout << "삭제할 도서 이름을 입력하세요: ";
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
                cout << "회원 삭제" << endl;
                cout << "삭제할 회원의 아이디: ";
                cin >> deleteId;
                memberSystem.deleteMember(deleteId);
                break;
            }
            case 6:
                addAdmin();  // 새로운 관리자 추가
                break;
            default:
                cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
            }
        }
    }
private:
    void showMenu() const {
        cout << "1. 도서 조회" << endl;
        cout << "2. 도서 삭제" << endl;
        cout << "3. 도서 추가" << endl;
        cout << "4. 회원 조회" << endl;
        cout << "5. 회원 삭제" << endl;
        cout << "6. 관리자 추가" << endl;
        cout << "0. 종료" << endl;
        cout << "메뉴 선택: ";
    }

    int getChoice() const {
        int choice;
        cin >> choice;
        return choice;
    }

    bool displayBooks() const {
        const vector<Book>& books = system.getBooks();

        if (books.empty()) {
            cout << "도서 목록이 비어 있습니다." << endl;
            return 0;
        }
        else {
            cout << "도서 목록: " << endl;
            for (const Book& book : books) {
                book.display();
            }
        }
    }

    void addAdmin() {
        string id = "", password = "", name = "", job = "";
        Admin newAdmin("", "", "", "");

        // 관리자 정보 입력
        cout << "관리자 추가" << endl;
        cout << "아이디: ";
        cin >> id;
        cout << "비밀번호: ";
        cin >> password;
        cout << "이름: ";
        cin >> name;
        cout << "직업: ";
        cin >> job;
        newAdmin = Admin(id, password, name, job);
        memberSystem.add_Admin(newAdmin);  // 관리자 추가 함수 호출
    }

    void addBook() {
        try {
            string bookName, writer, publisher, genre, review;
            float starPoint, numbering;
            int gn;

            int page;
            bool rent = 0;
            string rentId = "없음";
            cout << "도서 이름: ";
            cin.ignore();
            getline(cin, bookName);
            cout << "저자: ";
            getline(cin, writer);
            cout << "출판사: ";
            getline(cin, publisher);
            cout << "장르: 1. 컴퓨터, 2 수학, 3.과학 4. 소설";
            cin >> gn;
            if (gn == 1) { genre = "컴퓨터"; numbering = 100; }
            else if (gn == 2) { genre = "수학"; numbering = 200; }
            else if (gn == 3) { genre = "과학"; numbering = 300; }
            else if (gn == 4) { genre = "소설"; numbering = 400; }
            cout << "별점: ";
            cin >> starPoint;
            cout << "리뷰: ";
            cin.ignore();
            getline(cin, review);
            cout << "페이지 수: ";
            cin >> page;
            Book newBook(bookName, writer, publisher, genre, numbering, starPoint, review, page,
                rent, rentId);
            system.add_Book(newBook);
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl; // 예외 메시지 출력
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
                cout << "프로그램을 종료합니다." << endl;
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
            case 6: {//오지현이 추가한거
                check_rentedBooks();
                break;
            }
            default:
                cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
            }
        }
    }

private:
    void showMenu() const {
        cout << "1. 도서 조회" << endl;
        cout << "2. 도서 대여" << endl;
        cout << "3. 도서 반납" << endl;
        cout << "4. 대여중인 도서 조회" << endl;
        cout << "5. 도서 검색" << endl;
        cout << "6. 대여했던 도서 조회" << endl; // 오지현이 추가한거
        cout << "0. 종료" << endl;
        cout << "메뉴 선택: ";
    }

    int getChoice() const {
        int choice;
        cin >> choice;
        return choice;
    }

    bool displayBooks() const {

        const vector<Book>& books = system.getBooks();

        if (books.empty()) {
            cout << "도서 목록이 비어 있습니다." << endl;
            return 0;
        }
        else {
            cout << "도서 목록: " << endl;
            for (const Book& book : books) {
                book.display();
            }
        }
    }

    // 대여 기능 추가
    void rentBook() {
        if (currentMemberId.empty()) {
            cout << "로그인이 필요합니다." << endl;
            return;
        }

        string bookName;
        cout << "대여할 도서 이름을 입력하세요: ";
        cin.ignore();
        getline(cin, bookName);

        if (system.rent_Book(bookName, currentMemberId)) {
            memberSystem.rentBook(currentMemberId, bookName);
            memberSystem.saveRentedBook(bookName, currentMemberId); // 오지현 추가 (대여할때 각 회원 텍스트 파일에 책 제목 저장)
        }
    }


    // 반납 기능 추가
    void returnBook() {
        if (currentMemberId.empty()) {
            cout << "로그인이 필요합니다." << endl;
            return;
        }

        string bookName;
        cout << "반납할 도서 이름을 입력하세요: ";
        cin.ignore();
        getline(cin, bookName);

        if (system.return_Book(bookName, currentMemberId)) {
            memberSystem.returnBook(currentMemberId, bookName);
        }
    }

    void rentedBooks() const { //(수정)빌린 책 조회하기
        const vector<Book>& books = system.getBooks();
        const vector<string>& rentedBooks = memberSystem.getRentedBooks(currentMemberId);

        if (rentedBooks.empty()) {
            cout << "대여 중인 도서가 없습니다." << endl;
            return;
        }

        cout << "대여 중인 도서 목록 : " << endl;
        for (const string& bookName : rentedBooks) {
            auto it = find_if(books.begin(), books.end(), [&](const Book& book) {
                return book.getBookName() == bookName; });
            if (it != books.end()) {
                it->display();
            }
        }
    }

    void enter_searchBooks() const {  //도서 검색기능 추가
        string keyword;
        cout << "키워드 입력(제목 또는 저자): ";
        cin.ignore();
        getline(cin, keyword);
        system.searchBooks(keyword);
    }

    void check_rentedBooks() { // 오지현이 추가한것
        cout << "지금까지 대여했던 책의 제목을 보여드리겠습니다" << endl;
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
                cout << "프로그램을 종료합니다." << endl;
                return;
            case 1:
                login();
                break;
            case 2:
                signup();
                break;
            default:
                cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
            }
        }
    }

private:
    void showMenu() const {
        cout << "1. 로그인" << endl;
        cout << "2. 회원 가입" << endl;
        cout << "0. 종료" << endl;
        cout << "명령어 선택: ";
    }
    int getChoice() const {
        int choice;
        cin >> choice;
        return choice;
    }

    void login() {
        BookSystem bookSystem;
        string id = "", password = "";
        cout << "로그인" << endl;
        cout << "아이디: ";
        cin >> id;
        cin.ignore();
        cout << "비밀번호: ";
        password = memberSystem.getPasswordFromUser();

        if (memberSystem.isAdmin(id)) {
            // 관리자 로그인
            AdminApp adminApp(bookSystem, memberSystem);
            adminApp.run();
        }
        else if (memberSystem.login(id, password)) {
            // 학생 로그인
            cout << "로그인 성공!" << endl;
            StudentApp studentApp(bookSystem, id);
            studentApp.run();
        }
        else {
            cout << "로그인 실패. 아이디나 비밀번호가 일치하지 않습니다." << endl;
        }
    }

    void signup() {
        string id = "", password = "", name = "", job = "";
        User newUser("", "", "", "", 0, 0);

        // 회원 정보 입력
        cout << "회원가입" << endl;
        cout << "아이디: ";
        cin >> id;
        cout << "비밀번호: ";
        cin >> password;
        cout << "이름: ";
        cin >> name;
        cout << "직업: ";
        cin >> job;
        newUser = User(id, password, name, job); // 예시로 bookLimit과 daysLimit을 초기값으로 설정
        memberSystem.signUp(newUser);                   // 회원가입 함수 호출

    }
};

int main() {

    MemberSystem memberSystem;

    LoginApp loginApp(memberSystem);
    loginApp.run();

    return 0;
}