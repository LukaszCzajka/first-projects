//this validator is better then others bcs for example PESEL "48954584584" is false, other validators return a result true
//uwzglednnic lata przestepne np 29.02.2020 90023019286 ------------ <-fix this example pesel
/*
if bday > 28 && bmonth == 2 &&  year == lata przestepne{wrong pesel}

 if else miesiace majace 30dni maja 31 {wrong pesel}

 else wszystkie dni powyzej 31 dni 


*/

#include <iostream>
#include <time.h>
#include <iomanip>
#include <windows.h>
#include <ctime>  
#include <conio.h>

using namespace std;


string entering_pesel(string &);
void coversion_str2int_tab(string, int[]);
void wyswietlanie_tab(int[]);
void verification(int[], string &);
void gender_check(int[]);
void date_of_birth(int[], int &, int &, int &);
void findAge(int current_date, int current_month, int current_year, int birth_day, int birth_month, int birth_year);
void horoscop (int, int);

int main() {

   // current date/time based on current system
    time_t now = time(0);

   // Number of sec since January 1,1970 is: " << now << endl;

   tm *ltm = localtime(&now);


int birth_year, birth_month, birth_day;
int current_date = ltm->tm_mday, 
    current_month =  1 + ltm->tm_mon,
    current_year = 1900 + ltm->tm_year;
int pesel_tab[11] = {0};
string pesel_str;

    cout << "Prosze podac nr PESEL: ";

    entering_pesel(pesel_str);
    verification(pesel_tab, pesel_str); 
    gender_check(pesel_tab);
    date_of_birth(pesel_tab, birth_year, birth_month, birth_day);
    findAge(current_date, current_month, current_year, birth_day, birth_month, birth_year);
    horoscop(birth_day, birth_month);

return 0;

}

string entering_pesel(string & pesel_str)
{
    cin >> pesel_str;
for (;;)
{
  if (pesel_str.length() == 11)
    {
        break;
    }else if(pesel_str.length() < 11)
    {
        cout << "PESEL jest za krotki, podaj PESEL ponownie: " << endl;
        entering_pesel(pesel_str);
    }else {
        cout << "PESEL jest zbyt dlugi, podaj PESEL ponownie: " << endl;
        entering_pesel(pesel_str);
    }
}
return pesel_str;
}

void coversion_str2int_tab(string pesel_str, int pesel_tab[])
{
    for (int i = 0; i < 11; i++)
    {   
        char znak = pesel_str[i];
        int cyfra = znak - '0';
        pesel_tab[i] = cyfra;
    }
}

void wyswietlanie_tab(int pesel_tab[])
{
    cout << "Wprowadzony PESEL to: ";
    for(int i = 0; i < 11; i++)
        {
            cout << pesel_tab[i];
        }
    cout << endl;
}

void verification(int pesel_tab[], string & pesel_str) 
{
  for (;;) 
  {  
    coversion_str2int_tab(pesel_str, pesel_tab);
    wyswietlanie_tab(pesel_tab);

    int check, last_check;
    check = 1*pesel_tab[0] + 3*pesel_tab[1] + 7*pesel_tab[2] + 9*pesel_tab[3] + pesel_tab[4] + 3*pesel_tab[5] + 7*pesel_tab[6] + 9*pesel_tab[7] + pesel_tab[8] + 3*pesel_tab[9];

    last_check = check % 10;

    //https://www.infor.pl/prawo/gmina/dowod-osobisty/262184,Jak-sprawdzic-czy-masz-poprawny-PESEL.html

    int birth_day = (pesel_tab[4] * 10) + pesel_tab[5];  // for verification 2 lines down... if b_day > 31 PESEL is wrong bcs birth day cannot be greater than 31

    if (((last_check - 10) * (-1)) == pesel_tab[10] && birth_day < 32)
    {
        cout << "PESEL is corect!     " << endl;
        break;
    }else {
        cout << "PESEL is wrong, try again: ";
        entering_pesel(pesel_str);
    }
  }
}

void gender_check(int pesel_tab[])
{
            cout << "Gender: \t\t";
        if ((pesel_tab[9] % 2) == 0)
        {
            cout << "Male" <<endl;
        } else {
            cout << "Female" << endl;
        }
}

void date_of_birth(int pesel_tab[], int & birth_year, int & birth_month, int & birth_day)
{
    int century;
        if (pesel_tab[2] == 8 || pesel_tab[2] == 9) 
        {
            century = 18;
            pesel_tab[2] -= 8;
        } 
        else if (pesel_tab[2] == 0 || pesel_tab[2] == 1)
        {
            century = 19;
        } else 
        {
            century = 20;
            pesel_tab[2] -= 2;
        }

    birth_day = (pesel_tab[4] * 10) + pesel_tab[5];
    birth_month = (pesel_tab[2] * 10) + pesel_tab[3];
    birth_year = (century * 100) + (pesel_tab[0] * 10) + pesel_tab[1];

    string months_str[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    string month_str;

        for (int i = 1; i <= 12; i++)
        {
            if (birth_month == i)
            {
                month_str = months_str[i - 1];
            }
        }
        cout << "Date of birth: \t\t";
        cout << birth_day << "." << month_str << "." << birth_year;
}

void findAge(int current_date, int current_month,int current_year, int birth_day, int birth_month, int birth_year)
             {
                
                int days_of_month[] = { 31, 28, 31, 30, 31, 30, 31,
                                    31, 30, 31, 30, 31 };
            
                // if birth date is greater then current birth
                // month then do not count this month and add 30
                // to the date so as to subtract the date and
                // get the remaining days
                if (birth_day > current_date) {
                    current_date = current_date + days_of_month[birth_month - 1];
                    current_month = current_month - 1;
                }
            
                // if birth month exceeds current month, then do
                // not count this year and add 12 to the month so
                // that we can subtract and find out the difference
                if (birth_month > current_month) {
                    current_year = current_year - 1;
                    current_month = current_month + 12;
                }
            
                // calculate date, month, year
                int calculated_date = current_date - birth_day;
                int calculated_month = current_month - birth_month;
                int calculated_year = current_year - birth_year;


                cout << endl << "Present age : \t\t" << calculated_year << " Years, " << calculated_month << " Months, " << calculated_date << " Days." << endl;

             }

void horoscop (int birth_day, int birth_month)
{
    string zodiacs[12] = {"Aquarius", "Pisces", "Aries", "Taurus", "Gemini", "Cancer", "Leo", "Virgo", "Libra", "Scorpio", "Sagittarius", "Capricorn"};
    string zodiac;

    if ((birth_day >= 20 && birth_month == 1) || (birth_day <= 18 && birth_month == 2)) zodiac = zodiacs[0];
    else if ((birth_day >= 19 && birth_month == 2) || (birth_day <= 20 && birth_month == 3)) zodiac = zodiacs[1];
    else if ((birth_day >= 21 && birth_month == 3) || (birth_day <= 19 && birth_month == 4)) zodiac = zodiacs[2];
    else if ((birth_day >= 20 && birth_month == 4) || (birth_day <= 20 && birth_month == 5)) zodiac = zodiacs[3];
    else if ((birth_day >= 21 && birth_month == 5) || (birth_day <= 20 && birth_month == 6)) zodiac = zodiacs[4];
    else if ((birth_day >= 21 && birth_month == 6) || (birth_day <= 22 && birth_month == 7)) zodiac = zodiacs[5];
    else if ((birth_day >= 23 && birth_month == 7) || (birth_day <= 22 && birth_month == 8)) zodiac = zodiacs[6];
    else if ((birth_day >= 23 && birth_month == 8) || (birth_day <= 22 && birth_month == 9)) zodiac = zodiacs[7];
    else if ((birth_day >= 23 && birth_month == 9) || (birth_day <= 22 && birth_month == 10)) zodiac = zodiacs[8];
    else if ((birth_day >= 23 && birth_month == 10) || (birth_day <= 21 && birth_month == 11)) zodiac = zodiacs[9];
    else if ((birth_day >= 22 && birth_month == 11) || (birth_day <= 21 && birth_month == 12)) zodiac = zodiacs[10];
    else if ((birth_day >= 22 && birth_month == 12) || (birth_day <= 19 && birth_month == 01)) zodiac = zodiacs[11];

    cout << "Zodiac sign: \t\t" << zodiac;
}



