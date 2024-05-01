#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <numeric>
// #include <ostream>
using namespace std;

// --> global methods
void getaLine(string &inStr); // get a string
char getaChar();              // get a symbol

// --> a Tenant class

class Tenant
{
private:
  string name;   // tenant name
  int aptNumber; // apartment name
  int age;       // tenant age
  // ... etc

public:
  Tenant(string n, int aNo);
  ~Tenant();
  int getAptNumber();
  // used with set
  friend bool operator<(const Tenant &, const Tenant &);
  friend bool operator==(const Tenant &, const Tenant &);

  friend ostream &operator<<(ostream &, const Tenant &);
};

class CompareTenants
{
public:
  bool operator()(Tenant *, Tenant *) const;
};

class TenantList
{
private:
  // set pointers o tenants
  set<Tenant *, CompareTenants> setPtrsTens;
  set<Tenant *, CompareTenants>::iterator iter;

public:
  ~TenantList(); // destructor

  void insertTenant(Tenant *);
  int getAptNo(string);
  void display();
};

class TenantInputScreen
{
private:
  TenantList *ptrTenantList;
  string tName;
  int aptNo;

public:
  TenantInputScreen(TenantList *ptrTL) : ptrTenantList(ptrTL){};
  void getTenant();
};

class RentRow
{
private:
  int aptNo;
  float rent[12];

public:
  RentRow(int);             // line len
  void setRent(int, float); // mothly sum
  float getSumOfRow();      // one line sum

  friend bool operator<(const RentRow &, const RentRow &);
  friend bool operator==(const RentRow &, const RentRow &);
  // for the call
  friend ostream &operator<<(ostream &, const RentRow &);
};

class CompareRows // functional obj for the comparing
{
public:
  bool operator()(RentRow *, RentRow *) const;
};

class RentRecord
{
private:
  set<RentRow *, CompareRows> setPtrsRR;
  set<RentRow *, CompareRows>::iterator iter;

public:
  ~RentRecord();
  void insertRent(int, int, float);
  void display();
  float getSumOfRents(); // total sum
};

class RentInputScreen
{
private:
  TenantList *ptrTenantList;
  RentRecord *ptrRentRecord;

  string renterName;
  float rentPaid;
  int month;
  int aptNo;

public:
  RentInputScreen(TenantList *ptrTL, RentRecord *ptrRR) : ptrTenantList(ptrTL), ptrRentRecord(ptrRR){};
  void getRent(); // monthly rent val
};

class Expense
{
public:
  int month;
  int day;
  string category;
  string payee;
  float amount;
  Expense(){};
  Expense(int m, int d, string c, string p, float a) : month(m), day(d), category(c), payee(p), amount(a){};

  friend bool operator<(const Expense &, const Expense);
  friend bool operator==(const Expense &, const Expense &);

  friend ostream &operator<<(std::ostream &, const Expense &);
};

class CompareCategories // functional obj for the comparing
{
public:
  bool operator()(Expense *, Expense *) const;
};

class CompareDates
{
public:
  bool operator()(Expense *, Expense *) const;
};

class ExpenseRecord
{
private:
  // vec expenses pointer
  vector<Expense *> vectPtrsExpenses;
  vector<Expense *>::iterator iter;

public:
  ~ExpenseRecord();
  void insertExp(Expense *);
  void display();
  float displaySummary(); // yearly report <-
};

class ExpenseInputScreen
{
private:
  ExpenseRecord *ptrExpenseRecord;

public:
  ExpenseInputScreen(ExpenseRecord *);
  void getExpense();
};

class AnnualReport
{
private:
  RentRecord *ptrRR;
  ExpenseRecord *ptrER;
  float expenses;
  float rents;

public:
  AnnualReport(RentRecord *, ExpenseRecord *){};
  void display();
};

class UserInterface
{
private:
  TenantList *ptrTenantList;
  TenantInputScreen *ptrTenantInputScreen;
  RentRecord *ptrRentRecord;
  RentInputScreen *ptrRentInputScreen;
  ExpenseRecord *ptrExpenseRecord;
  ExpenseInputScreen *ptrExpenseInputScreen;
  AnnualReport *ptrAnnualReport;
  char ch;

public:
  UserInterface();
  ~UserInterface();
  void interact();
};