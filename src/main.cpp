#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>

using namespace std;


class Product
{
public:
    int price;
    bool sold;
    Product(int price, bool sold)
    {
        this->price = price;
        this->sold = sold;
    };
};

class Human;
class Company
{
private:

public:
    /* data */
    string name;
    int employee_capacity;
    int product_price;
    int current_money;
    int product_per_employee;
    int employee_wage;
    int product_count;
    int count_sold;
    vector<Human*> employees;
    Company()
    {

    }
    Company(string name, int employee_capacity, int product_price, int current_money, int product_per_employee, int employee_wage, int product_count)
    {
        this->name = name;
        this->employee_capacity = employee_capacity;
        this->product_price = product_price;
        this->current_money = current_money;
        this->product_per_employee = product_per_employee;
        this->employee_wage = employee_wage;
        this->product_count = product_count;
        this->count_sold = 0;
    };
    
    //void Act(int t)
    int Act(int t)
    {
        int retVal = 0;
        int num_employees = employees.size();
        int new_prod_count = num_employees * product_per_employee;
        product_count += new_prod_count;

        cout << "\t: " << (double)count_sold / product_count << "\n";
        cout << "\t: " << new_prod_count << "\n";

        if (count_sold == product_count)//if we sold less then 80%, decrease the price
        {
            product_price *= 1.05;
            retVal  = 1;
        }
        else if ((double)count_sold / product_count < 0.8)
        {
            if (product_price > 100)
                product_price *= 0.9;
            if(num_employees)
                retVal  = -1;
        } else {            
            product_price *= 1.02;
            retVal  = 1;
        }

        if (!(t % 7))
        {
            cout << "\n - " << t / 7 <<". tyden:\n";
            cout << "\tCount sold: " << count_sold << "\n";
            cout << "\tProduct prize: " << product_price << "\n";
            cout << "\tProduct count: " << product_count << "\n";
        }

        
        
        count_sold = 0;
        return retVal;
    }
};


class Human
{
private:

public:
    Company* employer;
    int current_money;
    vector<Company*> shopping_companies;
    Human(Company* employer, int current_money)
    {
        this->employer = employer;
        this->current_money = current_money;
    };
};



//int main(int argc, char const* argv[])
int main()
{
    //INIT
    int end_time = 365;
    //name, employee_capacity, product_price, current_money, product_per_employee, employee_wage, product_count
    Company supermarket("kaufland", 50, 250, 10e6, 7, 40000, 200);
    vector<Human*>people;
    for (int i = 0; i < 50; i++)
    {
        Human* person = new Human(&supermarket, 100000);
        people.push_back(person);
        supermarket.employees.push_back(person);
    }

    //Main loop
    for (int t = 0; t < end_time; t++)
    {
        for(auto p : people)
        {
            int amount = rand() % 9 + 5;
            for (int i = 0; i < amount; i++)
            {
                if (p->current_money >= supermarket.product_price and supermarket.product_count > 0)
                {
                    p->current_money -= supermarket.product_price;
                    supermarket.current_money += supermarket.product_price;
                    supermarket.count_sold++;
                    supermarket.product_count--;
                }
            }
        }

        for (auto emp : supermarket.employees)
        {
            if (!((t + 1) % 30))
            {
                //cout << emp->current_money << "emp money-------------\n";
                emp->current_money += supermarket.employee_wage;
                supermarket.current_money -= supermarket.employee_wage;
            }
            
        }

        int ret = supermarket.Act(t);

        if(ret == -1)
        {
            supermarket.employees[supermarket.employees.size()-1]->employer = nullptr;
            supermarket.employees.pop_back();
        }else if(ret == 1)
        {
            for (auto p : people)
            {
                if(p->employer == nullptr and ret )
                {
                    supermarket.employees.push_back(p);
                    p->employer = &supermarket;
                    ret = 0;
                }
            }
        }
 
        if (!(t % 7))
        {
            cout << "\tkapital firmy: " << supermarket.current_money << "\n";
            cout << "\tVyplaty: " << supermarket.employee_wage * supermarket.employees.size() << "\n\n";
        }
    }

    cout << "\n\nPrehled lidi na konci\n";
    for (auto p : people)
        {   
            if (p->employer)
                cout << "Zamestnany\n";
            else
                cout << "Nezamestnany\n";
            cout << "Penize: " << p->current_money << "\n";
        }


    /* code */
    return 0;
}
