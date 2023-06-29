// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

///1
class InvestmentPlan{
    char name[81];
    double plan;
    double shares;
    bool time;
public:
    InvestmentPlan(char *name="", double plan=0, double shares=0, bool time=false) :  plan(plan), shares(shares),time(time) {
        strcpy(this->name,name);
    }
    bool iscurrentday() const {
        return time;
    }

    friend class InvestmentFund;
    friend class ActionFund;
};

///2
class InvestmentFund{
protected:
    char name[51];
    InvestmentPlan* investplans;
    int n;
    double priceOfShares;
    void copy(const InvestmentFund &other){
        strcpy(this->name,other.name);
        this->priceOfShares=other.priceOfShares;
        this->n=other.n;
        this->investplans=new InvestmentPlan[other.n];
        for (int i = 0; i < n; ++i) {
            this->investplans[i]=other.investplans[i];
        }
    }
public:

    InvestmentFund(char *name="", InvestmentPlan *investplans= nullptr, int n=0, double priceOfShares=0) {
        strcpy(this->name,name);
        this->priceOfShares=priceOfShares;
        this->n=n;
        this->investplans=new InvestmentPlan[n];
        for (int i = 0; i < n; ++i) {
            this->investplans[i]=investplans[i];
        }
    }

    InvestmentFund(const InvestmentFund &other){
        copy(other);
    }

    InvestmentFund &operator=(const InvestmentFund &other){
        if (this!=&other){
            delete[]investplans;
            copy(other);
        }
        return *this;
    }
    virtual ~InvestmentFund(){
        delete[]investplans;
    }

    virtual double profit()=0;

    InvestmentPlan& getPlan(int index) {
        return investplans[index];
    }

    double totalinvest(){
        double sum=0;
        for (int i = 0; i < n; ++i) {
            sum += investplans[i].shares*priceOfShares;
        }
        return sum;
    }
    double newPlansSum() {
        double newPlansSum = 0.0;
        for (int i = 0; i < n; i++) {
            if (getPlan(i).iscurrentday())
                newPlansSum += getPlan(i).plan;
        }
        return newPlansSum;
    }
};


/// 3 Money
class MoneyFund: public InvestmentFund{
    static const double yearlyProvision;
public:
    MoneyFund(char *name, InvestmentPlan *investplans, int n, double priceOfShares) : InvestmentFund(name,investplans,n,priceOfShares) {}

    double profit() override{
        return (totalinvest() * yearlyProvision / 100) / 365;
    }
};


/// 4 Action
class ActionFund: public InvestmentFund{
    static const double yearlyProvision;
    static const double entryProvision;
public:
    ActionFund(char *name, InvestmentPlan *investplans, int n, double priceOfShares) : InvestmentFund(name,investplans,n,priceOfShares) {}

    double profit() override{

        return (totalinvest() * yearlyProvision / 100) / 365 +  newPlansSum() * entryProvision / 100;
    }
};



///Money
const double MoneyFund::yearlyProvision=1;
///Actions
const double ActionFund::yearlyProvision=1.5;
const double ActionFund::entryProvision=3;


double totalProfit(InvestmentFund** funds, int n){
    double totalsum=0;
    for (int i = 0; i < n; ++i) {

            totalsum += funds[i]->profit();

    }
    return totalsum;
}

int main(){

    char investitor[80], ime[50];
    double plan, brUdeli, udel;
    bool flag = false;
    int n, m;
    cin >> n;
    InvestmentFund **fondovi = new InvestmentFund*[n];
    for(int i = 0; i < n; i++){
        cin >> ime;
        cin >> m;
        InvestmentPlan *ip = new InvestmentPlan[m];
        for(int j = 0; j < m; j++){
            cin >> investitor >> plan >> brUdeli;
            if(j % 2) flag = true;
            else flag = false;
            InvestmentPlan IP(investitor, plan, brUdeli, flag);
            ip[j] = IP;
        }
        cin >> udel;
        if(i % 2){
            fondovi[i] = new ActionFund(ime, ip, m, udel);

        }
        else{
            fondovi[i] = new MoneyFund(ime, ip, m, udel);
        }
    }
    cout << totalProfit(fondovi, n);
    return 0;
}
