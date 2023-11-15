class BookSystem {
private:
    // ���� ����� �����ϴ� ����
    vector<Book> books;

public:
    // ������: ���Ͽ��� ���� ������ �о��
    BookSystem() {
        Load_Book_File();
    }

    // ���� �߰� �޼���: ���ο� ������ ���� ��Ͽ� �߰��ϰ� ���Ͽ� ����
    void add_Book(const Book& book) {
        books.push_back(book);
        save_Book_File();
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

    // ���� ��� ��ȯ �޼���
    const vector<Book>& getBooks() const {
        return books;
    }




    // ���� �뿩 �޼���: Ư�� ������ �뿩�ϰ� ���Ͽ� ����
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
            it->setRentingStatus(false, "");
            save_Book_File();
            cout << bookName << "��(��) �ݳ��Ǿ����ϴ�." << endl;
            return true; // ���������� �ݳ��� ��� true ��ȯ
        }
        else {
            cout << "�ش� ������ �뿩 ���� ȸ���� �ƴϰų� ������ �������� �ʽ��ϴ�." << endl;
            return false; // �ݳ� ������ ��� false ��ȯ
        }
    }



private:
    // ���Ͽ��� å ���� �о����
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

    // å ������ ���Ͽ� �����ϱ�
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
    string currentMemberId; // ���� �α����� ȸ���� ���̵�

public:
    // ������
    Book_App() {}


    // ���ø����̼� ���� �޼���
    void run() {
        while (true) {
            try {
                showMenu();
                int choice = getChoice();

                switch (choice) {
                case 0:
                    cout << "���α׷��� �����մϴ�." << endl;
                    return;
                case 1:
                    display_Books();
                    break;
                case 2: {
                    if (!display_Books()) {
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
                    Add_Book();
                    break;
                case 4:
                    rentBook();
                    break;
                case 5:
                    returnBook();
                    break;
                default:
                    cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
                }
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl; // ���� �޽��� ���
            }
        }
    }

    // �޴� ��� �޼���
    void showMenu() const {
        cout << "���� ���� ���α׷�" << endl;
        cout << "1. ���� ��ȸ" << endl;
        cout << "2. ���� ����" << endl;
        cout << "3. ���� �߰�" << endl;
        cout << "4. ���� �뿩" << endl;
        cout << "5. ���� �ݳ�" << endl;
        cout << "0. ����0" << endl;
        cout << "�޴� ����: " << endl;
    }

    // ����� �Է� �޴� �޼���
    int getChoice() const {
        int choice;
        cin >> choice;
        return choice;
    }

    // ���� ��� ��� �޼���
    bool display_Books() const {
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



    // ���ο� ���� �߰� �޼���
    void Add_Book() {
        try {
            string bookName, writer, publisher, genre, review;
            float numbering, starPoint;
            int page;
            bool rent = 0;

            cout << "���� �̸�: ";
            cin.ignore();
            getline(cin, bookName);
            cout << "����: ";
            getline(cin, writer);
            cout << "���ǻ�: ";
            getline(cin, publisher);
            cout << "�帣: ";
            getline(cin, genre);
            cout << "������ȣ: ";
            cin >> numbering;
            cout << "����: ";
            cin >> starPoint;
            cout << "����: ";
            cin.ignore();
            getline(cin, review);
            cout << "������ ��: ";
            cin >> page;

            Book newBook(bookName, writer, publisher, genre, numbering, starPoint, review, page, rent);
            system.add_Book(newBook);
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl; // ���� �޽��� ���
        }
    }

    void setcurrentMemberId(string id) {
        currentMemberId = id;
    }

    string getcurrentMemberId() {
        return currentMemberId;
    }
};
