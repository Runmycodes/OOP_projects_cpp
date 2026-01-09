#include <iostream>//I prefer using these over <bits/stdc++.h>, starting to lose my sanity, turned off coderunner
#include <limits>
#include <vector>
#include <string>

using namespace std;

class Vehicle{
    private:
        string brand;
        string model;
        double price; //price of car or bike
        static int n_vehicles;
    public:
        Vehicle(): brand("unkwown"), model("unknown"), price(0.00) { ++n_vehicles;} //will count no. of vehicles formed
        Vehicle(const string& brand, const string& model, const double& price): brand(brand), model(model), price(price) {}

        ~Vehicle(){--n_vehicles;}

        static int& n_vehicles_return(){return n_vehicles;}

        const string& get_brand() const {return brand;}
        const string& get_model() const {return model;}
        const double& get_price() const {return price;}

        void set_brand(const string& brand){this->brand=brand;}
        void set_model(const string& model){this->model=model;}
        void set_price(const double& price){this->price=price;}

        virtual void displayInfo(){
            cout << get_brand() << ", " << get_model() << ", " << get_price() << endl;
        }; 
        virtual void calcrent(const int& days) = 0;
        virtual int& get_days() = 0;
};

int Vehicle::n_vehicles = 0;

class Car : public Vehicle{
private:
    int doors;
    int days;
public:
    Car(): doors(0), days(0){
        set_brand("unknown");
        set_model("unknown");
        set_price(0.00);
    }
    Car(const int& doors, const string& brand, const string& model, const double& price, const int& days): doors(doors), days(days){
        set_brand(brand);
        set_model(model);
        set_price(price);
    }
    virtual void displayInfo(){
        cout << "Car: " << get_brand() << ", " << get_model() << ", " << get_price()<< ", for " << doors << " no. of doors!" << endl; 
    }
    virtual void calcrent(const int& days){cout << (get_price()/(doors*doors))*days << endl;} //random rent pricing lol
    
    int& get_days() override {return days;}
};

class Bike : public Vehicle{
    private:
        int weight;
        int days;
    public:
        Bike():weight(0), days(0){
            set_brand("unknown");
            set_model("unknown");
            set_price(0.00);
        }
        Bike(const int& weight, const string& brand, const string& model, const double& price, const int& days): weight(weight), days(days){
            set_brand(brand);
            set_model(model);
            set_price(price);
        }
        virtual void displayInfo(){
            cout << "Bike: " << get_brand() << ", " << get_model() << ", " << get_price()<< ", for " << weight << " kg weight of bike!" << endl; 
        }
        virtual void calcrent(const int& days){cout << (get_price()/(weight*weight))*days << endl;}

        int& get_days() override {return days;}
};

int main(){
    vector<Vehicle*> v; 
    string model, brand; double price; int days, weight, doors, i = 0;
    while(1){
        cout << "What do you want to do?" << endl << "1. Rent a Car" << endl << "2. Rent a Bike" << endl;
        cout << "3. Display Information" << endl <<  "4. Check no. of Vehicles" << endl;
        cout << "5. Leave" << endl;

        int n;  cin>> n;
        switch(n){
            case 1:{ //fun fact without the curly brace here, car cannot be instantiated
                cout << "Enter the brand, model, price, no. of doors, and the days of rent:" << endl;
                cin >> brand >> model;
                cin >> price >> doors >> days;
                v.push_back(new Car(doors, brand, model, price, days)); //passing in heap memory
                cout << "Order registered!" << endl;
                break;
            }
            case 2:{
                cout << "Enter the brand, model, price, weight of bike, and the days of rent:" << endl;
                cin >> brand >> model;
                cin >> price >> weight >> days;
                v.push_back(new Bike(weight, brand, model, price, days));
                cout << "Order registered!" << endl;
                break;
            }
            case 3:{
                for(auto &it: v){
                    it->displayInfo();
                    cout << "The rent for " << it->get_days() << " days is: ";
                    it->calcrent(it->get_days());
                    cout << endl;
                }
                break;
            }
            case 4:
                cout << "Your have " << Vehicle::n_vehicles_return() << " vehicles rented!" << endl << endl;
                break;
            case 5:
                cout << "Hey you didn't pay for rent!" << endl;
                i = 1;
                break;
            default:
                cout << "What kinda number is that???" << endl << endl;
        }
        if(i != 0)  break;
    }

    for(auto &it: v){ //ok so i learned this
        delete it;
    }
    v.clear();
    
    return 0;
}
