#include <QCoreApplication>
#include <iostream>
#include <string>
#include <clocale>
#include <Windows.h>
#include "Store.h"

int main(int argc, char *argv[]) {

    setlocale(LC_ALL, "PL_pl.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    QCoreApplication a(argc, argv);
    cout << "Задание 2:\n__________\n" << endl;

    EmployeeManager<string> empManage;
    Store storeMagnit;

    empManage.addEmployee("Мартин Некролог", 100000, "Начальник");
    Employee<string> employee1("Алекс Рашпили", 27000, "Продавец");
    empManage.addEmployee(employee1);
    cout << "Первый сотрудник: ";
    empManage.getEmployee(0).getInfoDisplay();
    empManage.getEmployee(1).setStatus("Начальник отдела");
    cout << "Второй сотрудник: ";
    empManage.getEmployee(1).getInfoDisplay();

    storeMagnit.addProduct("Tomato ANGUS", 150, 10);
    Product XJLEB("Хлеб", 42.5, 6);
    storeMagnit.addProduct(XJLEB);

    storeMagnit.addCustomer("Джон Шепард", 2000.5);
    Customer customer1("Павел Морозов", 1547);
    storeMagnit.addCustomer(customer1);

    auto listProd = storeMagnit.getList<Product>();
    cout << "Первый товар из списка: ";
    listProd[0].getInfoDisplay();

    auto listCust = storeMagnit.getList<Customer>();
    cout << "Первый клиент из списка: ";
    listCust[0].getInfoDisplay();

    cout << "Инфо об объекте XJLEB: ";
    storeMagnit.getInfoObject(XJLEB);
    cout << "Инфо об объекте customer1: ";
    storeMagnit.getInfoObject(customer1);
    cout << "Счетчик товаров: " << storeMagnit.getCountProd() << endl;

    storeMagnit.customerPurchase(customer1, XJLEB, 999); // выйдет ошибка
    storeMagnit.customerPurchase(customer1, XJLEB, 2);

    return 0;
}

//return a.exec();
// Set up code that uses the Qt event loop here.
// Call a.quit() or a.exit() to quit the application.
// A not very useful example would be including
// #include <QTimer>
// near the top of the file and calling
// QTimer::singleShot(5000, &a, &QCoreApplication::quit);
// which quits the application after 5 seconds.

// If you do not need a running Qt event loop, remove the call
// to a.exec() or use the Non-Qt Plain C++ Application template.
