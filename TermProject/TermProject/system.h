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
        cout << "도서 이름: " << bookname << endl;
        cout << "저자: " << writer << endl;
        cout << "출판사: " << publisher << endl;
        cout << "장르: " << genre << endl;
        cout << "고유번호: " << numbering << endl;
        cout << "별점: " << star_point << endl;
        cout << "리뷰: " << review << endl;
        cout << "페이지 수: " << page << endl;
        cout << "대여 여부: " << (rent ? "대여 중" : "대여 가능") << endl;
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

    void display() const {
        cout << "아이디: " << id << endl;
        cout << "비밀번호: " << pw << endl;
        cout << "이름: " << name << endl;
        cout << "직업: " << job << endl;
    }
};



class User : public Member {
private:
    int booklimit; // 대여 가능한 권 수
    int daylimit;  // 대여 가능 기간 

public:
    User(const string& memberId, const string& password, const string& memberName, const string& memberJob,
        int bookLimit, int daysLimit)
        : Member(memberId, password, memberName, memberJob), booklimit(bookLimit), daylimit(daysLimit) {}

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
};

// BookSystem 클래스: 도서 관리 시스템을 나타내는 클래스
class BookSystem {
private:
    // 도서 목록을 저장하는 벡터
    vector<Book> books;

public:
    // 생성자: 파일에서 도서 정보를 읽어옴
    BookSystem() {
        Load_Book_File();
    }

    // 도서 추가 메서드: 새로운 도서를 도서 목록에 추가하고 파일에 저장
    void add_Book(const Book& book) {
        books.push_back(book);
        save_Book_File();
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

    // 도서 목록 반환 메서드
    const vector<Book>& getBooks() const {
        return books;
    }


    void book_and_app() {
        save_Book_File();
    }


    // 도서 대여 메서드: 특정 도서를 대여하고 파일에 저장
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
            it->setRentingStatus(false, "");
            save_Book_File();
            cout << bookName << "이(가) 반납되었습니다." << endl;
            return true; // 성공적으로 반납된 경우 true 반환
        }
        else {
            cout << "해당 도서를 대여 중인 회원이 아니거나 도서가 존재하지 않습니다." << endl;
            return false; // 반납 실패한 경우 false 반환
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
                    << " " << (book.isRented() ? 1 : 0) << book.getRentingMemberId() << endl;
            }
            file.close();
        }
    }
};

class MemberSystem {
private:
    vector<Member> members;

public:

    MemberSystem() {
        Load_Member_File();
    }

    void signUp(const Member& member) {

        members.push_back(member);
        save_Member_File();
        cout << "회원가입이 완료되었습니다." << endl;
    }

    bool login(const string& id, const string& password) {
        for (const Member& member : members) {
            if (member.getId() == id && member.getPassword() == password) {
                cout << "로그인 성공!" << endl;
                return true;
            }
        }
        cout << "로그인 실패. 아이디나 비밀번호가 일치하지 않습니다." << endl;
        return false;
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

private:

    void Load_Member_File() {
        ifstream file("members.txt");
        if (file.is_open()) {
            members.clear();
            string id, password, name, job;
            while (file >> id >> password >> name >> job) {
                Member member(id, password, name, job);
                members.push_back(member);
            }
            file.close();
        }
    }


    void save_Member_File() {
        ofstream file("members.txt");
        if (file.is_open()) {
            for (const Member& member : members) {
                file << member.getId() << " " << member.getPassword() << " " << member.getName() << " " << member.getJob() << endl;
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
};



// Book_App 클래스: 도서 관리 애플리케이션을 나타내는 클래스
class Book_App {
private:
    BookSystem system;
    MemberSystem memberSystem;
    string currentMemberId; // 현재 로그인한 회원의 아이디

public:
    // 생성자
    Book_App(string id) : currentMemberId(id) {}


    // 애플리케이션 실행 메서드
    void run() {
        while (true) {
            try {
                showMenu();
                int choice = getChoice();

                switch (choice) {
                case 0:
                    cout << "프로그램을 종료합니다." << endl;
                    return;
                case 1:
                    display_Books();
                    break;
                case 2: {
                    if (!display_Books()) {
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
                    Add_Book();
                    break;
                case 4:
                    rentBook();
                    break;
                case 5:
                    returnBook();
                    break;
                default:
                    cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
                }
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl; // 예외 메시지 출력
            }
        }
    }



    // 메뉴 출력 메서드
    void showMenu() const {
        cout << "도서 관리 프로그램" << endl;
        cout << "1. 도서 조회" << endl;
        cout << "2. 도서 삭제" << endl;
        cout << "3. 도서 추가" << endl;
        cout << "4. 도서 대여" << endl;
        cout << "5. 도서 반납" << endl;
        cout << "0. 종료0" << endl;
        cout << "메뉴 선택: " << endl;
    }

    // 사용자 입력 받는 메서드
    int getChoice() const {
        int choice;
        cin >> choice;
        return choice;
    }

    // 도서 목록 출력 메서드
    bool display_Books() const {
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



    // 새로운 도서 추가 메서드
    void Add_Book() {
        try {
            string bookName, writer, publisher, genre, review;
            float numbering, starPoint;
            int page;
            bool rent = 0;
            string rentId = " ";

            cout << "도서 이름: ";
            cin.ignore();
            getline(cin, bookName);
            cout << "저자: ";
            getline(cin, writer);
            cout << "출판사: ";
            getline(cin, publisher);
            cout << "장르: ";
            getline(cin, genre);
            cout << "고유번호: ";
            cin >> numbering;
            cout << "별젘: ";
            cin >> starPoint;
            cout << "리뷰: ";
            cin.ignore();
            getline(cin, review);
            cout << "페이지 수: ";
            cin >> page;

            Book newBook(bookName, writer, publisher, genre, numbering, starPoint, review, page, rent, rentId);
            system.add_Book(newBook);
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl; // 예외 메시지 출력
        }
    }

    void setcurrentMemberId(string id) {
        currentMemberId = id;
    }

    string getcurrentMemberId() {
        return currentMemberId;
    }
};

class Member_App {
private:
    MemberSystem system;
    string cuid;

public:
    Member_App() {}

    void run() {
        while (true) {
            try {
                showMenu();
                int choice = getChoice();

                switch (choice)
                {
                case 0:
                    cout << "프로그램을 종료합니다." << endl;
                    break;
                case 1:
                    Login();
                    break;
                case 2:
                    signup();
                    break;
                case 3: {
                    string deleteId;
                    cout << "회원 삭제" << endl;
                    cout << "삭제할 회원의 아이디: ";
                    cin >> deleteId;
                    system.deleteMember(deleteId); // 회원 삭제 함수 호출
                    break;
                }
                case 4:
                    system.displayMembers();
                    break;
                default:
                    cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
                    break;
                }
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl; // 예외 메시지 출력
            }
        }
    }

    void showMenu() const {
        cout << "로그인 프로그램" << endl;
        cout << "1. 로그인" << endl;
        cout << "2. 회원 가입" << endl;
        cout << "3. 회원 삭제" << endl;
        cout << "4. 회원 조회및 삭제" << endl;
        cout << "0. 종료" << endl;
        cout << "명령어 선택: " << endl;
    }

    int getChoice() const {
        int choice;
        cin >> choice;
        return choice;
    }

    void Login() {
        string id = "", password = "";
        cout << "로그인" << endl;
        cout << "아이디: ";
        cin >> id;
        cin.ignore(); // 이전 입력 버퍼를 비웁니다.
        cout << "비밀번호: ";
        password = system.getPasswordFromUser(); // 비밀번호 입력 함수 호출.
        if (system.login(id, password)) { // 로그인 함수 호출
            Book_App App(id);
            App.run();
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
        newUser = User(id, password, name, job, 5, 15); // 예시로 bookLimit과 daysLimit을 초기값으로 설정
        system.signUp(newUser);                   // 회원가입 함수 호출

    }

};








int main() {
    Member_App App;
    App.run();
    return 0;
}




/*

member 파일에 빌린 정보가 안들어간다 지상아 정신차리고 얼른하고 때려치자 런치자 강민서 사랑해 ♧
*/