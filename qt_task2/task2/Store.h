#ifndef STORE_H
#define STORE_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Product {
private:
    string m_name;		// название
    double m_price;		// цена
    int m_count;		// кол-во
public:
    // конструктор с параметрами
    Product(string name, double price, int count) : m_name(name), m_price(price), m_count(count) {
        if (count < 0) m_count = 0; // fix: если задано отрицательное кол-во исправляем.
    }

    // вывод информации о товаре
    void getInfoDisplay() {
        cout << "Товар: " << m_name << " | Цена: " << m_price << " | Количество: " << m_count << endl;
    }

    // получение цены
    double getPrice() {
        return m_price;
    }

    // получение цены
    string getName() {
        return m_name;
    }

    // получение количества
    int getCount() {
        return m_count;
    }

    // изменение кол-ва товара
    void setCount(int newCount) {
        m_count = newCount;
    }

    // перегрузка оператора == сравнения товаров
    bool operator==(const Product& prodOther) {
        return (m_name == prodOther.m_name && m_price == prodOther.m_price);
    }

    // перегрузка оператора += увеличение кол-ва товара на складе
    Product operator+=(const unsigned count) {
        return Product(m_name, m_price, m_count + count);
    }

    // перегрузка оператора -= уменьшение кол-ва товара на складе
    Product operator-=(const unsigned count) {
        if (count > m_count) return Product(m_name, m_price, 0);
        return Product(m_name, m_price, m_count - count);
    }
};

class Customer {
private:
    string m_name;		// имя
    double m_balance;	// баланс
public:
    // конструктор с параметрами
    Customer(string name, double balance): m_name(name), m_balance(balance){}

    // вывод информации о клиенте
    void getInfoDisplay() {
        cout << "Клиент: " << m_name << " | Баланс: " << m_balance << endl;
    }

    // получение имени клиента
    string getName() {
        return m_name;
    }

    // получение баланса клиента
    double getBalance() {
        return m_balance;
    }

    // (пополнение/cнятие с) счета
    void operBalance (double value) {
        if (m_balance + value > 0) {
            m_balance += value;
        }
        else cout << "Ошибка: на счету клиента " << m_name << " недостаточно средств для снятия. Остаток: " << m_balance << endl;
    }

    // покупка товара
    void buyProduct (Product &prod, int count) {
        if (m_balance >= prod.getPrice()*count && prod.getCount() >= count && count > 0) {
            m_balance -= prod.getPrice()*count;
            prod -= count;
            cout << "Покупка совершена:\n[Клиент: " << m_name << " | Остаток баланса: " << m_balance << "]\n[Товар: " << prod.getName() << " | Количество: " << prod.getCount() << " | Цена за ед.: " << prod.getPrice() << "]" << endl;
        }
        else if (count <= 0) cout << "Ошибка: число товаров не может быть меньше или равно нулю." << endl;
        else if (m_balance < prod.getPrice()) cout << "Ошибка: на счету клиента " << m_name << " недостаточно средств для покупки товара " << prod.getName() << endl;
        else if (prod.getCount() < count) cout << "Ошибка покупки: товара в указанном количестве нет." << " | Остаток товара: " << prod.getCount() << " | Требовалось: " << count << endl;
    }

    // дружественный доступ к данным клиента из класса магазин
    friend class Store;
};

template <typename T>
class Employee {
private:
    string m_name;       // имя сотрудника
    double m_salary;     // зарплата
    T m_status;         // статус       (шаблон)
public:
    // конструктор с параметрами
    Employee(string name, double salary, T status) : m_name(name), m_salary(salary), m_status(status) {}

    // установка зарплаты
    void setSalary(double money) {
        m_salary = money;
    }

    // установка статуса
    void setStatus(T newStatus) {
        m_status = newStatus;
    }

    // получение информации о сотруднике
    void getInfoDisplay() {
        cout << "Сотрудник: " << m_name << " | Зарплата: " << m_salary << " | Статус: " << m_status << endl;
    }
};

template <typename T>
class EmployeeManager {
private:
    vector<Employee<T>> employees;      // список сотрудников
public:
    // добавление сотрудника в список сотрудников (новый)
    void addEmployee(string name, double salary, T status) {
        employees.emplace_back(name, salary, status);
    }

    // добавление сотрудника в список сотрудников (уже готовый)
    void addEmployee(Employee<T>& emp) {
        employees.emplace_back(emp);
    }

    Employee<T> getEmployee(size_t index) {
        return employees[index];
    }
};

class Store {
private:
    vector<Product> m_listProduct;			// список товаров
    vector<Customer> m_listCustomer;		// список клиентов
    static long m_countProd;				// счетчик для учета количества товаров в магазине. (реализовал "общее количество единиц товаров", т.к иначе бы попросили "количество видов товара"
public:
    // конструктор без параметров
    Store() {}

    // конструктор с параметрами
    Store(vector<Product> listProduct, vector<Customer> listCustomer): m_listProduct(listProduct), m_listCustomer(listCustomer) {
        for (auto i=0; i<listProduct.size(); i++) {
            m_countProd += listProduct[i].getCount();
        }
    }

    // получение счетчика учета кол-ва товаров в магазине
    static long getCountProd() {
        return m_countProd;
    }

    // получение количества видов товаров
    size_t getCountTypesOfProduct() {
        return m_listProduct.size();
    }

    // добавление товара (новый)
    void addProduct(string name, double price, int count) {
        m_listProduct.emplace_back(name, price, count);
        m_countProd += count;
    }

    // добавление товара (уже готовый)
    void addProduct(Product& prod) {
        m_listProduct.emplace_back(prod);
        m_countProd += prod.getCount();
    }

    // добавление клиента (новый)
    void addCustomer(string name, double balance) {
        m_listCustomer.emplace_back(name, balance);
    }

    // добавление клиента (уже готовый)
    void addCustomer(Customer& cust) {
        m_listCustomer.emplace_back(cust);
    }

    // покупка товаров клиентами
    void customerPurchase(Customer& customer, Product& product, int count) {
        customer.buyProduct(product, count);
        m_countProd -= count;
    }

    // получение инфо о клиенте/товаре - шаблонный метод
    template <typename T>
    void getInfoObject(T& object) {
        if (typeid(object) == typeid(Product) || typeid(object) == typeid(Customer)) {
            object.getInfoDisplay();
        }
        else {
            cout << "Неопознанный объект: это товар или клиент?" << endl;
        }
    }

    // возврата списка товаров или клиентов - шаблонный метод
    template <typename T>
    vector<T> getList() {
        if constexpr (is_same_v<T, Product>) {
            return m_listProduct;
        }
        else if constexpr (is_same_v<T, Customer>) {
            return m_listCustomer;
        }
        else {
            cout << "Неопознанный объект: это товар или клиент?" << endl;
            return vector<string>();
        }
    }
};

long Store::m_countProd = 0;  // инициализация статического члена

#endif // STORE_H
