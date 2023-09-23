#include <iostream>
#include <string>
#include <bitset>
#include<random>
using namespace std;

class CRC
{
    string input, divisor, divident, result, binaryChar, main;
    string asciiString="";
    int len_divident, len_gen, len_inp, sum = 0;

public:
    string fun_xor(string a, string b) // xor operation perfom
    {
        string result = "";
        if (a[0] == '0')
        {
            return a.substr(1);
        }
        else
        {
            for (int i = 0; i < len_gen; i++)
            {
                result = result + (a[i] == b[i] ? '0' : '1');
            }
            return result.substr(1);
        }
    }
    void randomlyFlipBit(string &data)
    {                                                  
        int index = rand() % data.length();            
        data[index] = (data[index] == '0') ? '1' : '0';
    }
    void getdata()
    { // it will take all input and then calcualte ascii value of indiviual characters
        cout << "Enter input (string):" << endl;
        getline(cin, input);

        //cout << "Enter  generator :" << endl;
        divisor="1101";

        len_gen = divisor.length();
        len_inp = input.length();

        divident = input;
        int r = len_gen - 1;
        for (int i = 0; i < r; i++)
        {
            divident = divident + '0';
        }
        len_divident = divident.length();

        cout << "\nCharacter .... ASCII ... Binary:" << endl;
        for (auto c : input)
        {
            string binaryChar = bitset<8>(c).to_string();
            cout << c << " ---" << int(c) << " --- " << binaryChar << endl;
            string New = binaryChar;
            string latest=binaryChar;
            string da=binaryChar;

            int r = len_gen - 1;
            cout<<"Redundant bit "<< r<<endl;
            for (int i = 0; i < r; i++)
            {
                binaryChar = binaryChar + '0';
            }
            cout << "dataword(Data + redundant bit) :" << binaryChar << endl;

            string temp_div = divisor;
            string temp_divident = binaryChar.substr(0, len_gen);
            int j = len_gen;
            while (j < len_divident)
            {
                temp_divident = fun_xor(temp_divident, temp_div);
                temp_divident = temp_divident + binaryChar[j];
                j++;
            }
            result = binaryChar + fun_xor(temp_divident, temp_div);
            string rem = fun_xor(temp_divident, temp_div);
            cout << "Remainder:  "  << rem << endl;

            New = New + rem;
            cout << "Codeword: " << New << endl;

    char ch;
    // cout << "\nsyndrome is  0,CRC pass,Error not detected" << endl;
    cout<<"\nYou want error or not (y/n): ";
    cin>>ch;
    if(ch=='y'|| ch=='Y'){
        string receivedDataCopy = New;  
        randomlyFlipBit(receivedDataCopy);  
           
            // latest=latest+errors;

        cout << "Original data: " << New << endl;
        cout<<endl;  

        cout << "After inducing error: " << receivedDataCopy << endl;
        cout<<endl;
         string New_div=divisor;
            string New_divident=receivedDataCopy.substr(0,len_gen);
            int k=len_gen;
            while(k<New.length())
            {
                 New_divident=fun_xor(New_divident,New_div);
                 New_divident= New_divident+ receivedDataCopy[k];
                 k++;
            }
            string errors=fun_xor(New_divident,New_div);
            cout<<endl;
            // cout<<"-********** After CRC *********** "<<endl;
            cout<<"Remainder: "<<errors<<endl;
         cout << "\nSyndrome is not  0,CRC fail,Error detected" << endl;

       
    cout<<"--------------------------------------------"<<endl<<endl;
         }
        else if(ch=='n'||ch=='N'){
             int dec_value = 0;
       int base = 1;
       int len = latest.length();
        string dividnt=divisor;
       for (int i = len - 1; i >= 0; i--) {
        if (latest[i] == '1')
            dec_value += base;
        base = base * 2;
        }
        string errors=fun_xor(dividnt,divisor);
        cout<<"Remainder :"<<errors<<endl;
        cout << "\nSyndrome 0,CRC Pass" << endl;
         cout<<"\nOriginal data: "<<da<<endl;
        cout<<"AScii value:  "<<dec_value<<endl;
       char ch=char(dec_value);
      cout<<"Decoded data: "<<ch<<endl;
     
         cout<<"--------------------------------------------"<<endl<<endl;
        }
      }
    }
};
int main()
{
    CRC crc;
    crc.getdata();
    return 0;
}
