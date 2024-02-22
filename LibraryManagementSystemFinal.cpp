#include <iostream>
#include <string>
using namespace std;

const int initialSize = 2;
int currentSize = initialSize;
int noOfBooks;

class Book {
public:
    Book() {
        name = "";
        author = "";
        genre = "";
        assigned = false;
    }
    Book(string n, string a, string g) {
        name = n;
        author = a;
        genre = g;
        assigned = false;
        noOfBooks++;
    }
    string getName() {
        return name;
    }
    string getAuthor() {
        return author;
    }
    string getGenre() { 
        return genre;
    }
    void setAssigned(bool a) {
        assigned = a;
    }
    bool getAssigned() {
        return assigned;
    }

private:
    string name, author, genre;
    bool assigned;
};

Book* library = new Book[initialSize]{
    {"If You Could See The Sun", "Ann Liang", "Fantasy"},
    {"The Priory Of The Orange Tree", "Samantha Shanon", "Fiction"}
};

class User {
private:
    string username, password;

public:
    User(string u, string p) {
        username = u;
        password = p;
    }
    string getUsername() {
        return username;
    }
    string getPassword() {
        return password;
    }
    
};

class Member : public User {
    private:
        string lastBorrowedGenre;
public:
    Member(string u, string p) : User(u, p) {
        lastBorrowedGenre = "";
    }
    void borrowBook(Book& b) {
        for (int i = 0; i < currentSize; i++) {
            if (library[i].getName() == b.getName() && library[i].getAssigned() == false) {
                cout << getUsername() << " has borrowed the book " << library[i].getName() << " by " << library[i].getAuthor() << endl;
                library[i].setAssigned(true);
                return;
            }
        }
    }
    void returnBook(Book& b) {
        for (int i = 0; i < currentSize; i++) {
            if (library[i].getName() == b.getName() && library[i].getAssigned() == true) {
                cout << b.getName() << " has been returned by " << getUsername() << endl;
                b.setAssigned(false);
                return;
            }
        }
    }
    void setLastBorrowedGenre(string& genre) {
        lastBorrowedGenre = genre;
    }

    string getLastBorrowedGenre() {
        return lastBorrowedGenre;
    }
};

class Librarian : public User {
public:
    Librarian(string u, string p) : User(u, p) {}
    void add(Book& b) {
        Book* newLibrary = new Book[currentSize + 1];
        for (int i = 0; i < currentSize; i++) {
            newLibrary[i] = library[i];
        }
        newLibrary[currentSize] = b;
        delete[] library;
        library = newLibrary;
        currentSize++;
    }
    void remove(string name) {
        Book* newLibrary = new Book[currentSize - 1];
        for (int i = 0, j = 0; i < currentSize; i++) {
            if (!(library[i].getName() == name)) {
                newLibrary[j++] = library[i];
            }
        }
        delete[] library;
        library = newLibrary;
        --currentSize;
        --noOfBooks;
    }
};

void authentication(User& user) {
    string userTry, passTry;
    cout << "Enter Username: ";
    cin >> userTry;
    cout << "Enter Password: ";
    cin >> passTry;

    if (userTry == user.getUsername() && passTry == user.getPassword()) {
        cout << "Login Success!" << endl;
    } else {
        cout << "Username or Password incorrect." << endl;
        authentication(user);
    }
}

void addBookToLibrary(Librarian& l) {
    string n, a, g;
    cout << "Enter the Name of the Book you want to add to the library: ";
    cin.ignore(); // Ignore any previous newline character in the input buffer
    getline(cin, n); // Allowing spaces in book name
    cout << "Enter the Author Name: ";
    getline(cin, a); // Allowing spaces in author name
    cout << "Enter the Genre: ";
    getline(cin, g); // Allowing spaces in genre name
    Book newBook(n, a, g);
    l.add(newBook);
}

void searchAndFilterBooks(const string& title) {
    bool found = false;
    cout << "\nSearch Results for '" << title << "':\n";
    for (int i = 0; i < currentSize; ++i) {
        if (library[i].getName() == title) {
            found = true;
            cout << "Book " << i + 1 << " - "
                 << "Title: " << library[i].getName() << ", "
                 << "Author: " << library[i].getAuthor() << ", "
                 << "Assigned: " << (library[i].getAssigned() ? "Yes" : "No") << endl;
        }
    }
    if (!found) {
        cout << "No book found.\n";
    }
}

void displayBooks(){
    cout<<"Total number of books in Library are: "<<noOfBooks<<endl;
    for (int i = 0; i < currentSize; i++) {
            cout << "Book " << i + 1 << " - "
                 << "Title: " << library[i].getName() << ", "
                 << "Author: " << library[i].getAuthor() << ", "
                 << "Assigned: " << (library[i].getAssigned() ? "Yes" : "No")<< endl;
        }
}

void recommendBooks(Member& member) {
    cout << "\nRecommended Books (Based on Last Borrowed Genre - " << member.getLastBorrowedGenre() << "):\n";

    for (int i = 0; i < currentSize; ++i) {
        if (library[i].getGenre() == member.getLastBorrowedGenre() && !library[i].getAssigned()) {
            cout << "Book " << i + 1 << " - "
                 << "Title: " << library[i].getName() << ", "
                 << "Author: " << library[i].getAuthor() << ", "
                 << "Genre: " << library[i].getGenre() << endl;
        }
    }
}

int main() {
    cout << "Enter login details for librarian \n";

    Librarian librarian("librarian1", "password123");
    authentication(librarian);

    Book book1("When No One Is Watching", "Alyssa Cole", "Thriller");
    Book book2("The Man Who Could Move Clouds", "Ingrid Contreras", "Nonfiction");
    Book book3("Enter Ghost", "Isabella Hammad", "Horror");
    librarian.add(book1);
    librarian.add(book2);
    librarian.add(book3);
    
    cout << "Enter login details for member \n";
    
    Member member("member1", "password123");
    authentication(member);

    
    Book book4("The Priory Of The Orange Tree", "Samantha Shanon", "Fiction");
    librarian.add(book4);
    int choice;
    while (choice != -1){
        cout<<"Enter 1 to add book to library\nEnter 2 to remove book from library\nEnter 3 to search for a book\nEnter 4 to get book recommendations\nEnter 5 to display all books in library\nEnter 6 to borrow book from library\nEnter 7 to return book to library\nEnter 8 to exit\n";
        cin>>choice;
        switch(choice){
        case 1:
        {
            addBookToLibrary(librarian);
            break;
        }
            
        case 2:
            {
                string bookRemove;
                cout<<"Enter the name of the book you want to remove: "<<endl;
                cin>>bookRemove;
                librarian.remove(bookRemove);
                break;  
            }
            
        case 3:
            {
                string titleSearch;
                cout << "Enter a title to search: ";
                cin.ignore(); 
                getline(cin, titleSearch);
                searchAndFilterBooks(titleSearch);
                break;  
            }
            
        case 4:
        {
            string history;
            cout << "Enter the genre of the last book you borrowed: "; 
            cin>>history;
            member.setLastBorrowedGenre(history);
            recommendBooks(member);
            break;
        }
            
        case 5:
            {
                displayBooks();
                break;  
            }
            
        case 6:
        {
            string titleBorrow;
            cout<<"Enter the name of the book you want to borrow: "<<endl;
            cin>>titleBorrow;
            bool found = false;
            for (int i = 0; i < currentSize; i++) {
                if (library[i].getName() == titleBorrow) {
                    member.borrowBook(library[i]);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "No book with this name in the library.\n";
            }
            break;  
        }
            
        case 7:
        {
            string titleReturn;
            cout<<"Enter the name of the book you want to return: \n";
            cin>>titleReturn;
            bool found = false;
            for (int i = 0; i < currentSize; i++) {
                if (library[i].getName() == titleReturn) {
                    member.returnBook(library[i]);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "No book with this name in the library.\n";
            }
            break;  
        }
            
        case 8:
        {
            exit(1);
            break;
        }   
        default:
            {
                cout<<"invalid number entered...\n";
                break;  
            }                            
    }   
    }   
}
