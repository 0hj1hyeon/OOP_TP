class MemberSystem {
private:
    vector<Member> members;

public:

    MemberSystem() {
        Load_Member_File();
    }

    void signUp(const Member& member) {

        members.push_back(member);
        save_Member_File();// �Լ��� save_member_file�� �ٲٱ�
        cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << endl;
    }

    bool login(const string& id, const string& password) {
        for (const Member& member : members) {
            if (member.getId() == id && member.getPassword() == password) {
                cout << "�α��� ����!" << endl;
                return true;
            }
        }
        cout << "�α��� ����. ���̵� ��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
        return false;
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
    // ���⼭���ʹ� ������ �� �ý��ۿ� �����ϳ�?
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
};
//��������� ��� �ý���

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
                    cout << "���α׷��� �����մϴ�." << endl;
                case 1:
                    Login();
                    break;
                case 2:
                    signup();
                    break;
                case 3: {
                    string deleteId;
                    cout << "ȸ�� ����" << endl;
                    cout << "������ ȸ���� ���̵�: ";
                    cin >> deleteId;
                    system.deleteMember(deleteId); // ȸ�� ���� �Լ� ȣ��
                    break;
                }
                case 4:
                    system.displayMembers();
                    break;
                default:
                    cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
                    break;
                }
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl; // ���� �޽��� ���
            }
        }
    }

    void showMenu() const {
        cout << "�α��� ���α׷�" << endl;
        cout << "1. �α���" << endl;
        cout << "2. ȸ�� ����" << endl;
        cout << "3. ȸ�� ����" << endl;
        cout << "4. ȸ�� ��ȸ�� ����" << endl;
        cout << "0. ����" << endl;
        cout << "��ɾ� ����: " << endl;
    }

    int getChoice() const {
        int choice;
        cin >> choice;
        return choice;
    }

    void Login() {
        string id = "", password = "";
        cout << "�α���" << endl;
        cout << "���̵�: ";
        cin >> id;
        cin.ignore(); // ���� �Է� ���۸� ���ϴ�.
        cout << "��й�ȣ: ";
        password = system.getPasswordFromUser(); // ��й�ȣ �Է� �Լ� ȣ��.
        system.login(id, password); // �α��� �Լ� ȣ��.

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
        newUser = User(id, password, name, job, 5, 15); // ���÷� bookLimit�� daysLimit�� �ʱⰪ���� ����
        system.signUp(newUser);                   // ȸ������ �Լ� ȣ��

    }
};

