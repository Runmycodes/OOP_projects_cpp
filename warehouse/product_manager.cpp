#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Product{
private:
    string name;
    double price_each;
    int count;
    static double total_value; //the total value(net worth) of all the products that I have
public:
    Product():name("unknown"), price_each(0.00), count(0){}
    Product(const string& name, const double& price_each, const int& count):name(name), price_each(price_each), count(count){
        total_value += (price_each*count);//when a product is added to warehouse, total value is calculated
    } 
    Product(const Product& p){ //this is a copy constructor
        name = p.name;
        price_each = p.price_each;
        count = p.count;

        total_value += (price_each*count);
    }
    ~Product(){total_value -= (price_each*count);} //when a product is removed, the net value decreases
    const string& get_string() const {return name;} //returns name of a specific product
    const double& get_price() const {return price_each;}
    const int& get_count() const {return count;}
    static double& get_total(){return total_value;} //returns net worth of all the warehouses

};
double Product::total_value = 0;

class Warehouse{
private:
    string location;
    vector<Product> inventory; //ooo vector data
public:
    Warehouse():location("unknown"){}
    void add_prod(const Product& p){
        inventory.push_back(p);}
    void set_location(const string& location){this->location=location;} //sets the location of warehouses
    const string& get_location() const {return location;} //returns location of a warehouse
     
    bool delete_product(const string& name){//this is to delete any product from the warehouse, by checking name of product
        for(int i = 0; i < inventory.size(); i++){
            if(inventory.at(i).get_string() == name){
                //inventory.at(i).~Product(); //so this crashes my program, already erasing it so destructor is called automatically
                inventory.erase(inventory.begin() + i);
                return true;
            }
        }
        return false;
    }

    void DisplayProducts(){
        cout << "The products at " << location << " warehouse is: " << endl;
        for(auto &it: inventory){
            cout << endl << it.get_string() << ", " << it.get_price() << ", " << it.get_count() << endl;
        }
    }

};

int main(){
    Warehouse* North = new Warehouse;
    Warehouse* South = new Warehouse; //a warehouse at north hub and south hub ig, stored in heap 

    cout << "Location of your North Warehouse: ";
    string loc1; getline(cin, loc1);
    North->set_location(loc1);
    cout << "Location of your South Warehouse: ";
    getline(cin, loc1);
    South->set_location(loc1);

    string name; double price; int count; int x; 
    while(1){
        cout << "What do you want to do?" << endl;
        cout << "1. Add a product" << endl << "2. Remove a product" << endl;
        cout << "3. View Net Worth" << endl << "4. Display all Product Information" << endl << "5. Leave" << endl;

        int n; cin >> n;
        if(n == 1){
            cout << "Choose Warehouse! (1=north, 2=south)Input number: ";
            cin >> x;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(x == 1){
                cout << "Kindly register the name: ";
                getline(cin, name);
                cout << "Kindly register price of each item: ";
                cin >> price;
                cout << "Kindly register quantity of items: ";
                cin >> count;

                Product p(name, price, count);

                North->add_prod(p);
                cout << "Product has been registered!" << endl << endl;
            }else if(x == 2){
                cout << "Kindly register the name: ";
                getline(cin, name);
                cout << "Kindly register price of each item: ";
                cin >> price;
                cout << "Kindly register quantity of items: ";
                cin >> count;

                Product p(name, price, count);

                South->add_prod(p);
                cout << "Product has been registered!" << endl << endl;
            }
            continue;
        }
        else if(n == 2){
            cout << "Choose Warehouse! (1=north, 2=south)Input number: ";
            cin >> x;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Kindly enter the name of the Product(has to be exact): ";
            getline(cin, name);
            if(x == 1){
                if(North->delete_product(name)){
                    cout << name << " product has been deleted." << endl << endl;
                }else   cout << "No such product exists! Please review product informations." << endl << endl;
            }else if(x == 2){
                if(South->delete_product(name)){
                    cout << name << " product has been deleted." << endl << endl;
                }else   cout << "No such product exists! Please review product informations." << endl << endl;
            }
        }
        else if(n == 3){
            cout << "Your net worth across both warehouses is: " <<Product::get_total() << endl << endl;
        }
        else if(n == 4){
            cout << "Choose Warehouse! (1=north, 2=south)Input number: ";
            cin >> x;
            if(x == 1){
                North->DisplayProducts();
                cout << endl;
            }else if(x == 2){
                South->DisplayProducts();
                cout << endl;
            }
        }
        else if(n == 5){cout << "Farewell!"; break;}
        else{cout << "What kinda number is that?!?!" << endl;}
    }

    delete North; //never forget never forgive
    delete South;
    return 0;
}

