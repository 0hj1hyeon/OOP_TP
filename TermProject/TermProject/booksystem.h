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

            string bookName, writer, publisher, genre, review;
            float numbering, starPoint;
            int page;
            bool rent;

            while (file >> bookName >> writer >> publisher >> genre >> numbering >> starPoint >> review >> page >> rent) {
                Book book(bookName, writer, publisher, genre, numbering, starPoint, review, page, rent);
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
                    << " " << (book.isRented() ? 1 : 0) << endl;
            }
            file.close();
        }
    }
};


class Book_App {
private:
    BookSystem system;
    MemberSystem memberSystem;
    string currentMemberId; // 현재 로그인한 회원의 아이디

public:
    // 생성자
    Book_App() {}


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

            Book newBook(bookName, writer, publisher, genre, numbering, starPoint, review, page, rent);
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
