class MemberSystem {
private:
    vector<Member> members;

public:

    MemberSystem() {
        Load_Member_File();
    }

    void signUp(const Member& member) {

        members.push_back(member);
        save_Member_File();// 함수명 save_member_file로 바꾸기
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
    // 여기서부터는 관리자 쪽 시스템에 들어가야하나?
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
        save_Book_File();
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
//여기까지가 멤버 시스템

class Member_App {
private:
    MemberSystem system;

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
        system.login(id, password); // 로그인 함수 호출.

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

