#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Compute the present value
double PV(double future_value, double coupon_rate, double r, int N,double d)
{
    double temp_PV=0;
    double coupon=coupon_rate*future_value;
    for(int i=0;i<=N;i++)
    {
        temp_PV += coupon*pow(1+r,-i-d);
    }
    temp_PV += future_value*pow(1+r,-N-d);
    return temp_PV;
}

// Compute the Yield-to-Maturity(YTM) by iteration : Secant method
double iterationYTM(double future_value,double coupon_rate,double price_value,int N,double d,double i0=0.00001, double i1= 10, const int MaxIter=50000, double epsilon = 1e-7)
{
    //temporary iterative values
    double final_yield=0.0,temp_yield;
    
    //Algorithm interval
    double low_bound=price_value- PV(future_value, coupon_rate, i0, N,d);
    double high_bound=price_value- PV(future_value, coupon_rate, i1, N,d);

    //Algorithm process
        //bond at par
        if(price_value == future_value)
        {
            return coupon_rate;
        }
        //zero coupon bond
        else if(coupon_rate == 0)
        {
            return  pow((future_value/price_value),1/N+d);
        }
        //iteration process error
        else if (low_bound*high_bound>0) {
            return -1;
        }
        //secant algorithm
        else
            for(int i=0;i<=MaxIter;i++){
                final_yield=(i0+i1)/2.0;
                temp_yield= price_value- PV(future_value, coupon_rate, final_yield, N,d);
                if(abs(temp_yield)< epsilon) return final_yield;
                else
                {
                    if (temp_yield>0) i1=final_yield;
                    else i0=final_yield;
                }
            }
    return final_yield;
}


int main()
{
    //Yield-to-Maturity procedure
    double coupon_rate, d, future_value, price_value,coupon;
    int N;
    cout << endl;
    cout << "Yield-to-Maturity Calculator" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << endl;
    cout << "Please, can you enter your Bond characteristics:" << endl;
    cout << "The coupon rate" << ", next the coupon payment" << ", the future value" << ", the present value" << " and the number of year before maturity:" << endl;

    //Input characteristics
    cin >> coupon_rate >> d >> future_value >> price_value >> N;

    //restrictions

        //d conditioning
        while(d > 1 || d < 0)
        {
            cout << "Please enter a value between 0 and 1 : " << endl;
            cin >> d;
        }

        //future value conditioning
        while(future_value<0)
        {
            cout << "Please enter a positive value for the future value : " << endl;
            cin >> future_value;
        }

        //present value conditioning
        while(future_value<0)
        {
            cout << "Please enter a positive value for the present value : " << endl;
            cin >> price_value;
        }

        //number of year conditioning
        while(N < 0)
        {
            cout << "Please enter a positive for the number of year : " << endl;
            cin >> N;
        }

    //With these information, we compute the coupon value that the user receive each year
    coupon=coupon_rate*future_value;

    //Pass the coupon rate to percent
    coupon_rate /= future_value;

    //Summary
    cout <<"Finally, we have a coupon rate = "<< setprecision(3) << coupon_rate*100 <<", a coupon value = "<< coupon <<", the next coupon payment in "<< d <<" years"<<", a future value = "<< future_value <<", a price value = "<< price_value  << endl <<"And your bond comes to maturity in "<< N << " years." << endl;

    //Results
    cout << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "Result : YTM = " << setprecision(3) << iterationYTM(future_value,coupon_rate,price_value,N,d) * 100 << "%" <<endl;

    return 0;
}