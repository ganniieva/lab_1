#include <iostream> 
#include <fstream>  
#include <cstring>  
#include <iomanip>  

using namespace std; 

const int MAX_BOOKS = 1000; 

struct Book
{
    char title[101] = "";    
    char author[51] = "";     
    int year = 0;           
    float rating = 0.0f;    
};

Book books[MAX_BOOKS];
int bookCount = 0; 

void loadBooks(const char *filename)
{
    ifstream fin(filename); 

    if (!fin){
        cout << "Файл не найден, будет создан новый." << endl;
        return;
    }

    bookCount = 0; 

    cout << endl;
    fin.close();
    
    ofstream fout(filename, ios::trunc);
    if (fout) {
        fout.close();
    }
}

void saveBookToFile(const char *filename, Book b)
{
    if (strlen(b.title) == 0 || strlen(b.author) == 0 || b.year < 0 || b.rating < 0) {
        cout << "Ошибка: некорректные данные книги!" << endl;
        return;
    }
    ofstream fout(filename, ios::app); 

    if (!fout)
    {
        cout << "Ошибка при сохранении файла!" << endl;
        return;
    }

    fout << b.title << " " << b.author << " " << b.year << " " << b.rating << endl;

    fout.close(); 
}

void addBook()
{
    if (bookCount >= MAX_BOOKS)
    {
        cout << "Превышен лимит книг!" << endl;
        return;
    }

    Book b; 

    cin.ignore(1000, '\n');

    cout << "Введите название книги: ";
    cin >> b.title;

    cout << "Введите автора: ";
    cin >> b.author;

    cout << "Год прочтения: ";
    cin >> b.year;

    cout << "Ваша оценка (0-10): ";
    cin >> b.rating;

    books[bookCount] = b;
    bookCount++; 
    saveBookToFile("book.txt", b);

    cout << "Книга добавлена!\n";
}

void showAllBooks()
{
    if (bookCount == 0)
    {
        cout << "Нет данных о книгах.\n";
        return;
    }

    cout << "\n--- Все книги ---\n";
    cout << left << setw(30) << "Название" 
         << setw(20) << "Автор"
         << setw(10) << "Год"
         << "Оценка\n";
    cout << "----------------------------------------------------\n";

    for (int i = 0; i < bookCount; i++)
    {
        cout << left << setw(30) << books[i].title
             << setw(20) << books[i].author
             << setw(10) << books[i].year
             << fixed << setprecision(1) << books[i].rating << "/10\n";
    }
}

void showStats()
{
    if (bookCount == 0)
    {
        cout << "Нет данных для анализа.\n";
        return;
    }

    float totalRating = 0;           
    float maxRating = books[0].rating; 
    int bestBookIndex = 0;           

    for (int i = 0; i < bookCount; i++)
    {
        totalRating += books[i].rating;

        if (books[i].rating > maxRating)
        {
            maxRating = books[i].rating;
            bestBookIndex = i;
        }
    }

    float averageRating = totalRating / bookCount; 

    cout << "\n--- Статистика ---\n";
    cout << "Количество прочитанных книг: " << bookCount << "\n";
    cout << "Средняя оценка: " << fixed << setprecision(2) << averageRating << "/10\n";
    cout << "Самая высоко оценённая книга: \"" << books[bestBookIndex].title 
         << "\" (" << books[bestBookIndex].author << ") - " 
         << fixed << setprecision(1) << books[bestBookIndex].rating << "/10\n";
}

void showMenu()
{
    cout << "\n=== Трекер книг ===\n";
    cout << "1. Добавить книгу\n";
    cout << "2. Показать все книги\n";
    cout << "3. Показать статистику\n";
    cout << "4. Выход\n";
    cout << "Выберите пункт: ";
}

int main()
{
    bookCount = 0;
    
    loadBooks("book.txt"); 

    int choice; 

    do
    {
        showMenu();    
        cin >> choice; 

        switch (choice)
        {
        case 1:
            addBook(); 
            break;
        case 2:
            showAllBooks(); 
            break;
        case 3:
            showStats(); 
            break;
        case 4:
            cout << "Выход из программы.\n"; 
            break;
        default:
            cout << "Неверный выбор.\n";
            cin.clear(); 
            cin.ignore(1000, '\n'); 
        }

    } while (choice != 4); 

    return 0; 
}