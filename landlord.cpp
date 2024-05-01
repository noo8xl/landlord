#include <landlord.h>

void getaLine(string &inStr)
{
  char temp[21];
  cin.get(temp, 20, '/n');
  cin.ignore(20, '\n');
  inStr = temp;
}

char getaChar()
{
  char ch = std::cin.get();
  cin.ignore(80, '\n');
  return ch;
}

// the Tenant class methods <--
Tenant::Tenant(string n, int aNo) : name(n), aptNumber(aNo){};
Tenant::~Tenant(){};
int Tenant::getAptNumber(){};
bool operator<(const Tenant &t1, const Tenant &t2)
{
  return t1.name < t2.name;
};
bool operator==(const Tenant &t1, const Tenant &t2)
{
  return t1.name == t2.name;
};
ostream &operator<<(ostream &s, const Tenant &t)
{
  s << t.aptNumber << '\t' << t.name << endl;
  return s;
};

void TenantInputScreen::getTenant() // get tenant data <-
{
  cout << "input tenant name (John Smith): ";
  getaLine(tName);
  cout << "imput an apartment number (101): ";
  cin >> aptNo;
  cin.ignore(80, '\n');
  Tenant *ptrTenant = new Tenant(tName, aptNo); // create a new tenant
  ptrTenantList->insertTenant(ptrTenant);       // insert to the tenent list
};

bool CompareTenants::operator()(Tenant *ptrT1, Tenant *ptrT2) const
{
  return *ptrT1 < *ptrT2;
};

TenantList::~TenantList()
{
  // delete all tenants
  while (!setPtrsTens.empty())
  {
    iter = setPtrsTens.begin();
    delete *iter; // delete pointers from set
    setPtrsTens.erase(iter);
  }
};

void TenantList::insertTenant(Tenant *ptrT)
{
  setPtrsTens.insert(ptrT); // insert
};

int TenantList::getAptNo(string tName)
{
  int aptNo;
  Tenant dummy(tName, 0);
  iter = setPtrsTens.begin();
  while (iter != setPtrsTens.end())
  {
    aptNo = (*iter)->getAptNumber();
    if (dummy == **iter++)
      return aptNo;
  }
  return -1;
};

void TenantList::display()
{
  std::cout << '\nApt#\tTenant Name \n------------\n';
  if (setPtrsTens.empty())
    std::cout << '*** Empty set ***\n';
  else
  {
    iter = setPtrsTens.begin();
    while (iter != setPtrsTens.end())
    {
      cout << **iter++;
    }
  }
};

RentRow::RentRow(int an) : aptNo(an)
{
  fill(&rent[0], &rent[12], 0);
};

void RentRow::setRent(int m, float am)
{
  rent[m] = am;
};

float RentRow::getSumOfRow()
{
  return reduce(&rent[0], &rent[12, 0]);
};

bool operator<(const RentRow &t1, const RentRow &t2)
{
  return t1.aptNo < t2.aptNo;
};

bool operator==(const RentRow &t1, const RentRow &t2)
{
  return t1.aptNo == t2.aptNo;
};

ostream &operator<<(ostream &s, const RentRow &an)
{
  s << an.aptNo << '\t';
  for (int i = 0; i < 12; i++)
  {
    if (an.rent[i] == 0)
      s << " 0 ";
    else
      s << an.rent[i];
  }
  s << endl;
  return s;
};

bool CompareRows::operator()(RentRow *ptrR1, RentRow *ptrR2) const
{
  return *ptrR1 < *ptrR2;
};

RentRecord::~RentRecord()
{
  while (!setPtrsRR.empty())
  {
    iter = setPtrsRR.begin();
    delete *iter;
    setPtrsRR.erase(iter);
  }
};

void RentRecord::insertRent(int aptNo, int month, float amount)
{
  RentRow searchRow(aptNo);
  iter = setPtrsRR.begin();
  while (iter != setPtrsRR.end())
  {
    if (searchRow == **iter)
    {
      (*iter)->setRent(month, amount);
      return;
    }
    else
      iter++;
  }
  RentRow *ptrRow = new RentRow(aptNo);
  ptrRow->setRent(month, amount);
  setPtrsRR.insert(ptrRow);
};

void RentRecord::display()
{
  cout << '\nAptNo\tJan Feb Mar Apr Mai Jun '
       << ' Jul Aug Sep Okt Nov Dec\n'
       << '------------------------------'
       << '------------------------------\n';

  if (setPtrsRR.empty())
    cout << '*** empty record***\n';
  else
  {
    iter = setPtrsRR.begin();
    while (iter != setPtrsRR.end())
    {
      cout << **iter++;
    }
  }
};

float RentRecord::getSumOfRents()
{
  float sumRents = 0.0;
  iter = setPtrsRR.begin();
  while (iter != setPtrsRR.end())
  {
    sumRents += (*iter)->getSumOfRow();
    iter++;
  }
  return sumRents;
};

void RentInputScreen::getRent()
{
  cout << 'enter a tenant name (John Smith): ';
  getaLine(renterName);
  aptNo = ptrTenantList->getAptNo(renterName);
  if (aptNo > 0)
  {
    cout << 'enter payment sum (123,44): ';
    cin >> rentPaid;
    cin.ignore(80, '\n');
    cout << ' enter month num (12): ';
    cin >> month;
    cin.ignore(80, '\n');
    month--;
    ptrRentRecord->insertRent(aptNo, month, rentPaid);
  }
  else
    cout << ' tenant not found. ';
};

bool operator<(const Expense &e1, const Expense &e2)
{
  if (e1.month == e2.month)
    return e1.day < e2.day;
  else
    return e1.month < e2.month;
};

bool operator==(const Expense &e1, const Expense &e2)
{
  return e1.month == e2.month && e1.day == e2.day;
};

ostream &operator<<(ostream &s, const Expense &exp)
{
  s << exp.month << '/' << exp.day << '\t' << exp.payee << '\t';
  s << exp.amount << '\t' << exp.category << endl;
  return s;
};

bool CompareDates::operator()(Expense *ptrE1, Expense *ptrE2) const
{
  return ptrE1->month < ptrE2->month && ptrE1->day < ptrE2->month;
};

bool CompareCategories::operator()(Expense *ptrE1, Expense *ptrE2) const
{
  return ptrE1->category < ptrE2->category;
};

ExpenseRecord::~ExpenseRecord()
{
  while (!vectPtrsExpenses.empty())
  {
    iter = vectPtrsExpenses.begin();
    delete *iter;
    vectPtrsExpenses.erase(iter);
  }
};

void ExpenseRecord::insertExp(Expense *ptrExp)
{
  vectPtrsExpenses.push_back(ptrExp);
};

void ExpenseRecord::display()
{
  cout << '\ndate\tbeneficiar\t\tsum\tcategorie\n'
       << '-------------------------------------\n';

  if (vectPtrsExpenses.size() == 0)
    cout << '*** empty set ***' << endl;
  else
  {
    sort(vectPtrsExpenses.begin(), vectPtrsExpenses.end(), CompareDates());
    iter = vectPtrsExpenses.begin();
    while (iter != vectPtrsExpenses.end())
      cout << **iter++;
  }
};

float ExpenseRecord::displaySummary()
{
  float totalExpenses = 0;

  if (vectPtrsExpenses.size() == 0)
  {
    cout << '\tall categories\t0\n';
    return 0;
  }
  sort(vectPtrsExpenses.begin(), vectPtrsExpenses.end(), CompareCategories());

  iter = vectPtrsExpenses.begin();
  string tempCat = (*iter)->category;
  float sumCat = 0.0;
  while (iter != vectPtrsExpenses.end())
  {
    if (tempCat == (*iter)->category)
      sumCat += (*iter)->amount;
    else
    {
      cout << '\t' << tempCat << '\t' << sumCat << endl;
      totalExpenses += sumCat;
      tempCat = (*iter)->category;
      sumCat = (*iter)->amount;
    }
    iter++;
  }
  totalExpenses += sumCat;
  cout << '\t' << tempCat << '\t' << sumCat << endl;
  return totalExpenses;
};

ExpenseInputScreen::ExpenseInputScreen(ExpenseRecord *per){};

void ExpenseInputScreen::getExpense()
{
  int month;
  int day;
  string category;
  string payye;
  float amount;

  cout << 'input month (1-12): ';
  cin >> month;
  cin.ignore(80, '\n');
  cout << 'input day (1-31): ';
  cin >> day;
  cin.ignore(80, '\n');
  cout << 'input category (rebuild, taxes, etc.): ';
  getaLine(category);
  cout << 'input a benefeciar (bosh gmbh): ';
  getaLine(payye);
  cout << 'input sum (29.90): ';
  cin >> amount;
  cin.ignore(80, '\n');
  Expense *ptrExpense = new Expense(month, day, category, payye, amount);
  ptrExpenseRecord->insertExp(ptrExpense);
};

AnnualReport::AnnualReport(RentRecord *pRR, ExpenseRecord *pER) : ptrRR(pRR), ptrER(pER){};

void AnnualReport::display()
{
  cout << 'yearly report\n----------------\n';
  cout << 'incomes\n';
  cout << 'rent payment\n';
  rents = ptrRR->getSumOfRents();
  cout << rents << endl;

  cout << 'expenses\n:';
  expenses = ptrER->displaySummary();
  cout << '\nbalance is \t\t\t' << rents - expenses << endl;
};

UserInterface::UserInterface()
{
  ptrTenantList = new TenantList();
  ptrRentRecord = new RentRecord();
  ptrExpenseRecord = new ExpenseRecord();
};

UserInterface::~UserInterface()
{
  delete ptrTenantList;
  delete ptrRentRecord;
  delete ptrExpenseRecord;
};

void UserInterface::interact()
{
  while (true)
  {
    cout << 'for the data input press "i", \n'
         << ' for print report press "d", \n'
         << ' exit - press "q": ';
    ch = getaChar();
    if (ch == 'i')
    {
      cout << ' to add a user press "t",\n'
           << ' to set a rent payment press "r", \n'
           << ' to set an expenses press "e": ';
      ch = getaChar();
      switch (ch)
      {
      case 't':
        ptrTenantInputScreen = new TenantInputScreen(ptrTenantList);
        ptrTenantInputScreen->getTenant();
        delete ptrTenantInputScreen;
        break;
      case 'r':
        ptrRentInputScreen = new RentInputScreen(ptrTenantList, ptrRentRecord);
        ptrRentInputScreen->getRent();
        delete ptrRentInputScreen;
        break;
      case 'e':
        ptrExpenseInputScreen = new ExpenseInputScreen(ptrExpenseRecord);
        ptrExpenseInputScreen->getExpense();
        delete ptrExpenseInputScreen;
        break;
      default:
        cout << 'unknown func' << endl;
        break;
      }
    } // end of if
    else if (ch == 'd')
    {
      cout << ' to print a tenant list press "t",\n'
           << ' to print a rent value press "r", \n'
           << ' to print an expenses press "e", \n'
           << ' to print a yearly report press "a": ';
      ch = getaChar();
      switch (ch)
      {
      case 't':
        ptrTenantList->display();
        break;
      case 'r':
        ptrRentRecord->display();
        break;
      case 'e':
        ptrExpenseRecord->display();
        break;
      case 'a':
        ptrAnnualReport = new AnnualReport(ptrRentRecord, ptrExpenseRecord);
        ptrAnnualReport->display();
        delete ptrAnnualReport;
        break;
      default:
        cout << 'unknown func' << endl;
        break;
      }
    } // end of else if
    else if (ch == 'q')
      return;
    else
      cout << 'unknown func. use only recommended chars!' << endl;
  } // end of while
};
