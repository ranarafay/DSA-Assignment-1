/*  
    P200636
    Rao Muhammad Rafay
*/

#include <iostream>
using namespace std;

// class Polynomial (Enclosing Class)
class Polynomial
{
    // class Term (Nested Class) as private member
    class Term
    {
        // data members of class Term
        // private:
        int Coefficient;
        int Exponent;
        Term *NextTerm;

    public:
        // member functions of class Term
        // default constructor
        Term();
        // setter
        void setCoefficient(int);
        void setExponent(int);
        void setNextTerm(Term *);
        // getter
        int getCoefficient();
        int getExponent();
        Term *getNextTerm() { return NextTerm; }
    };

    // data members of class Polynomial
    // private:
    int Size;
    Term *StartingAddrOfPolynomial;

public:
    // member functions of class Polynomial
    // default constructor
    Polynomial();
    // functions
    void Input();
    void ConvertSimplest();
    void Output();
    Polynomial Add(Polynomial);
    Polynomial operator+(Polynomial);
    Polynomial Multiply(Polynomial);
    Polynomial operator*(Polynomial);
    int Evalute(int);
    int operator*(int); // overloading * operator because Dot/Member Selection (.) operator can't be overloaded, doing so will cause an error
    // destructor
    // ~Polynomial();
};
// fuction implementation for class Term
Polynomial ::Term ::Term()
{
    Coefficient = 0;
    Exponent = 0;
    NextTerm = NULL;
}
void Polynomial ::Term ::setCoefficient(int coeff)
{
    Coefficient = coeff;
}
void Polynomial ::Term ::setExponent(int expo)
{
    Exponent = expo;
}
void Polynomial ::Term ::setNextTerm(Term *next)
{
    NextTerm = next;
}
int Polynomial ::Term ::getCoefficient()
{
    return Coefficient;
}
int Polynomial ::Term ::getExponent()
{
    return Exponent;
}

// fuction implementation for class Polynomial
Polynomial ::Polynomial()
{
    StartingAddrOfPolynomial = NULL;
    Size = 0;
}
void Polynomial ::Input()
{
    // taking size (number of terms) as input
    cout << "\nEnter the Number of Terms: ";
    int size;
    cin >> size;
    Size = size;

    // taking Coefficient and Exponent of each term as input
    cout << "Enter Coefficients and Exponents for Polynomial:" << endl;
    for (int i = 0; i < Size; i++)
    {
        // making new terms one by one in every iteration
        Term *newterm = new Term;

        cout << "\nFor " << i + 1 << " term: " << endl;
        cout << "Coefficient: ";
        int coeff;
        cin >> coeff;
        newterm->setCoefficient(coeff);
        cout << "Exponent: ";
        int Expo;
        cin >> Expo;
        newterm->setExponent(Expo);

        // temporary pointer for iteration process
        Term *temp = StartingAddrOfPolynomial;
        if (temp == NULL)
        {
            StartingAddrOfPolynomial = newterm;
        }
        else
        {
            while (temp->getNextTerm() != NULL)
            {
                temp = temp->getNextTerm();
            }
            temp->setNextTerm(newterm);
        }
    }

    // sorting the polynomial using SelectionSort
    Term *i;
    Term *j;
    i = StartingAddrOfPolynomial;
    int temp1;
    int temp2;

    while (i->getNextTerm() != NULL)
    {
        j = i;
        while (j != NULL)
        {
            // swapping Coefficeints and Exponents
            if (i->getExponent() < j->getExponent())
            {
                // for Coffeint
                temp1 = i->getCoefficient();
                i->setCoefficient(j->getCoefficient()); // Coefficient(i) = Coefficient(j)
                j->setCoefficient(temp1);               // Coefficient(j) = temp1

                // for Exponent
                temp2 = i->getExponent();
                i->setExponent(j->getExponent()); // Exponent(i) = Exponent(j)
                j->setExponent(temp2);            // Exponent(j) = temp2
            }
            // traversing forward
            j = j->getNextTerm();
        }
        // traversing forward
        i = i->getNextTerm();
    }
}
void Polynomial ::ConvertSimplest()
{
    this->Output();
    Term *i = StartingAddrOfPolynomial;
    Term *j;

    if (i == NULL)
    {
        return;
    }
    else
    {
        while (i != NULL)
        {
            Term *j = i->getNextTerm();
            while (j != NULL)
            {
                if (i->getExponent() == j->getExponent())
                {
                    cout << "found" << endl;
                    i->setCoefficient(i->getCoefficient() + j->getCoefficient());

                    Term *del = j;
                    i->setNextTerm(j->getNextTerm());
                    j = j->getNextTerm();
                    delete del;
                    continue;
                }
                else
                {
                    j->getNextTerm();
                }
            }
            i = i->getNextTerm();
        }
    }
}
void Polynomial ::Output()
{
    // temporary pointer for iteration process
    Term *temp = StartingAddrOfPolynomial;

    // this will probably not execute in given conditions, but we are using for exeption purpose
    if (temp == NULL)
    {
        cout << "\nNo Polynomial Exist";
    }

    else
    {
        int cnt = 0;
        cout << "\nThe Polynomial is: ";
        while (temp != NULL)
        {
            // for first iteration (first term)
            // sign (+) will not be displayed, whereas sign (-) will be
            if (cnt == 0)
            {
                // n^1 = n
                if (temp->getExponent() == 1)
                {
                    // for +
                    if (temp->getCoefficient() >= 0)
                    {
                        cout << temp->getCoefficient() << "n"
                             << " ";
                    }
                    // for -
                    else
                    {
                        cout << temp->getCoefficient() << "n"
                             << " ";
                    }
                }
                // n^0 = 1
                else if (temp->getExponent() == 0)
                {
                    // for +
                    if (temp->getCoefficient() >= 0)
                    {
                        cout << temp->getCoefficient() << " ";
                    }
                    // for -
                    else
                    {
                        cout << temp->getCoefficient() << " ";
                    }
                }

                else
                {
                    // for +
                    if (temp->getCoefficient() >= 0)
                    {
                        cout << temp->getCoefficient() << "n^" << temp->getExponent() << " ";
                    }
                    // for -
                    else
                    {
                        cout << temp->getCoefficient() << "n^" << temp->getExponent() << " ";
                    }
                }
            }

            // n^1 = n
            else if (temp->getExponent() == 1 && cnt != 0)
            {
                // for +
                if (temp->getCoefficient() >= 0)
                {
                    cout << "+" << temp->getCoefficient() << "n"
                         << " ";
                }
                // for -
                else
                {
                    cout << temp->getCoefficient() << "n"
                         << " ";
                }
            }
            // n^0 = 1
            else if (temp->getExponent() == 0 && cnt != 0)
            {
                // for +
                if (temp->getCoefficient() >= 0)
                {
                    cout << "+" << temp->getCoefficient() << " ";
                }
                // for -
                else
                {
                    cout << temp->getCoefficient() << " ";
                }
            }

            else
            {
                // for +
                if (temp->getCoefficient() >= 0)
                {
                    cout << "+" << temp->getCoefficient() << "n^" << temp->getExponent() << " ";
                }
                // for -
                else
                {
                    cout << temp->getCoefficient() << "n^" << temp->getExponent() << " ";
                }
            }
            // traversing forward
            temp = temp->getNextTerm();
            // will show that first iteration passed
            cnt++;
        }
        cout << "\n";
    }
    cout << "\n";
}
Polynomial Polynomial ::Add(Polynomial obj)
{
    Polynomial Sum;

    Term *i = this->StartingAddrOfPolynomial;
    Term *j;
    // Addition
    while (i != NULL)
    {
        j = obj.StartingAddrOfPolynomial;
        Term *term = new Term;

        term->setCoefficient(i->getCoefficient());
        term->setExponent(i->getExponent());

        while (j != NULL)
        {
            if (term->getExponent() == j->getExponent())
            {
                term->setCoefficient(term->getCoefficient() + j->getCoefficient());
            }
            // iterating forward
            j = j->getNextTerm();
        }
        // linking terms
        if (Sum.StartingAddrOfPolynomial == NULL)
        {
            Sum.StartingAddrOfPolynomial = term;
        }
        else if (Sum.StartingAddrOfPolynomial != NULL)
        {
            Term *temp1 = Sum.StartingAddrOfPolynomial;
            while (temp1->getNextTerm() != NULL)
            {
                temp1 = temp1->getNextTerm();
            }
            temp1->setNextTerm(term);
        }
        // iterating forward
        i = i->getNextTerm();
    }

    Term *k = Sum.StartingAddrOfPolynomial;
    Term *l = obj.StartingAddrOfPolynomial;

    int minexpo = k->getExponent();
    while (k != NULL)
    {
        if (k->getExponent() < minexpo)
        {
            minexpo = k->getExponent();
        }
        k = k->getNextTerm();
    }
    while (l != NULL)
    {
        if (l->getExponent() < minexpo)
        {
            Term *newterm = new Term;
            newterm->setCoefficient(l->getCoefficient());
            newterm->setExponent(l->getExponent());

            Term *temp = Sum.StartingAddrOfPolynomial;
            while (temp->getNextTerm() != NULL)
            {
                temp = temp->getNextTerm();
            }
            temp->setNextTerm(newterm);
        }
        l = l->getNextTerm();
    }

    return Sum;
}
Polynomial Polynomial ::operator+(Polynomial obj)
{
    Polynomial Sum;

    Term *i = this->StartingAddrOfPolynomial;
    Term *j;
    // Addition
    while (i != NULL)
    {
        j = obj.StartingAddrOfPolynomial;
        Term *term = new Term;

        term->setCoefficient(i->getCoefficient());
        term->setExponent(i->getExponent());

        while (j != NULL)
        {
            if (term->getExponent() == j->getExponent())
            {
                term->setCoefficient(term->getCoefficient() + j->getCoefficient());
            }
            // iterating forward
            j = j->getNextTerm();
        }
        // linking terms
        if (Sum.StartingAddrOfPolynomial == NULL)
        {
            Sum.StartingAddrOfPolynomial = term;
        }
        else if (Sum.StartingAddrOfPolynomial != NULL)
        {
            Term *temp1 = Sum.StartingAddrOfPolynomial;
            while (temp1->getNextTerm() != NULL)
            {
                temp1 = temp1->getNextTerm();
            }
            temp1->setNextTerm(term);
        }
        // iterating forward
        i = i->getNextTerm();
    }

    Term *k = Sum.StartingAddrOfPolynomial;
    Term *l = obj.StartingAddrOfPolynomial;

    int minexpo = k->getExponent();
    while (k != NULL)
    {
        if (k->getExponent() < minexpo)
        {
            minexpo = k->getExponent();
        }
        k = k->getNextTerm();
    }
    while (l != NULL)
    {
        if (l->getExponent() < minexpo)
        {
            Term *newterm = new Term;
            newterm->setCoefficient(l->getCoefficient());
            newterm->setExponent(l->getExponent());

            Term *temp = Sum.StartingAddrOfPolynomial;
            while (temp->getNextTerm() != NULL)
            {
                temp = temp->getNextTerm();
            }
            temp->setNextTerm(newterm);
        }
        l = l->getNextTerm();
    }

    return Sum;
}
Polynomial Polynomial ::Multiply(Polynomial obj)
{
    Polynomial Mul;

    Term *temp1 = this->StartingAddrOfPolynomial; // calling object
    bool chk = false;
    while (temp1 != NULL)
    {
        Polynomial tempobj;

        Term *temp2 = obj.StartingAddrOfPolynomial; // parameterized object
        while (temp2 != NULL)
        {
            Term *multerm = new Term;
            multerm->setCoefficient(temp1->getCoefficient() * temp2->getCoefficient()); // Coefficient(multerm) = Coefficient(temp1 * temp2)
            multerm->setExponent(temp1->getExponent() + temp2->getExponent());          // Exponent(multerm) = Exponent(temp1 + temp2)

            if (tempobj.StartingAddrOfPolynomial == NULL)
            {
                tempobj.StartingAddrOfPolynomial = multerm;
            }
            else
            {
                Term *temp3 = tempobj.StartingAddrOfPolynomial;
                while (temp3->getNextTerm() != NULL)
                {
                    temp3 = temp3->getNextTerm();
                }
                temp3->setNextTerm(multerm);
            }
            // iterating forward
            temp2 = temp2->getNextTerm();
        }
        // iterating forward
        temp1 = temp1->getNextTerm();

        // exeptions for handling errors
        if (chk == false)
        {
            Mul = tempobj;
            chk = true;
        }
        else
        {
            Mul = Mul + tempobj;
        }
    }
    return Mul;
}
Polynomial Polynomial ::operator*(Polynomial obj)
{
    Polynomial Mul;

    Term *temp1 = this->StartingAddrOfPolynomial; // calling object
    bool chk = false;
    while (temp1 != NULL)
    {
        Polynomial tempobj;

        Term *temp2 = obj.StartingAddrOfPolynomial; // parameterized object
        while (temp2 != NULL)
        {
            Term *multerm = new Term;
            multerm->setCoefficient(temp1->getCoefficient() * temp2->getCoefficient()); // Coefficient(multerm) = Coefficient(temp1 * temp2)
            multerm->setExponent(temp1->getExponent() + temp2->getExponent());          // Exponent(multerm) = Exponent(temp1 + temp2)

            if (tempobj.StartingAddrOfPolynomial == NULL)
            {
                tempobj.StartingAddrOfPolynomial = multerm;
            }
            else
            {
                Term *temp3 = tempobj.StartingAddrOfPolynomial;
                while (temp3->getNextTerm() != NULL)
                {
                    temp3 = temp3->getNextTerm();
                }
                temp3->setNextTerm(multerm);
            }
            // iterating forward
            temp2 = temp2->getNextTerm();
        }
        // iterating forward
        temp1 = temp1->getNextTerm();

        // exeptions for handling errors
        if (chk == false)
        {
            Mul = tempobj;
            chk = true;
        }
        else
        {
            Mul = Mul + tempobj;
        }
    }
    return Mul;
}
// helper function for evaluting polynomial
int pow(int val, int p)
{
    int ans = 1;
    for (int i = 0; i < p; i++)
    {
        ans = ans * val;
    }
    return ans;
}
int Polynomial ::Evalute(int x)
{
    int val = 0;

    Term *temp = this->StartingAddrOfPolynomial;
    while (temp != NULL)
    {
        // using above defined "pow(x, y)" function
        val += (temp->getCoefficient() * pow(x, temp->getExponent()));
        temp = temp->getNextTerm();
    }

    return val;
}
// overloading * operator because Dot/Member Selection (.) operator can't be overloaded, doing so will cause an error
int Polynomial ::operator*(int x)
{
    int val = 0;

    Term *temp = this->StartingAddrOfPolynomial;
    while (temp != NULL)
    {
        // using above defined "pow(x, y)" function
        val += (temp->getCoefficient() * pow(x, temp->getExponent()));
        temp = temp->getNextTerm();
    }

    return val;
}
// // destructor
// Polynomial ::~Polynomial()
// {
//     cout << "Destructor" << endl;
//     Term *temp;
//     temp = StartingAddrOfPolynomial;

//     while (temp)
//     {
//         Term *l;
//         l = temp;

//         temp = temp->getNextTerm();
//         delete l;
//     }
//     StartingAddrOfPolynomial = NULL;
// }
int main()
{
    Polynomial P1, P2, P3;
    P1.Input();
    P2.Input();
    // P3.Input();

    P1.Output();
    P2.Output();
    // (3n^2 + 2n - 4) (5n^2 - 3n + 3)
    cout << "Multiplication: ";
    P3 = P1 * P2;
    P3.Output();

    return 0;
}