//#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <deque>
#include <fstream>
#include <sstream>
//#include <ostream>
#define CS_CONV_MAX_CHARACTERS 128



using namespace std;


int bit;

bool validity;

bool receipt;

char m_class;
string SMSC;
string receiver;

string message;
string valid_period_str;


string pad(string s,int bits)

{

    while(s.length()<bits)

        s="0"+s;

    return s;

}



static const int GSM_to_UTF8 [CS_CONV_MAX_CHARACTERS] =
{
    0x40 ,0xa3,0x24 ,0xa5 ,0xe8 ,0xe9 ,0xf9 ,0xec ,0xf2 ,0xc7 ,0x0A ,0xd8 ,0xf8 ,0x0D ,0xc5 ,0xe5,
    0x394,0x5F,0x3a6,0x393,0x39b,0x3a9,0x3a0,0x3a8,0x3a3,0x398,0x39e,   -1,0xc6 ,0xe6 ,0xdf ,0xc9,
    0x20 ,0x21,0x22 ,0x23 ,0xa4 ,0x25 ,0x26 ,0x27 ,0x28 ,0x29 ,0x2a ,0x2b ,0x2c ,0x2d ,0x2e ,0x2f,
    0x30 ,0x31,0x32 ,0x33 ,0x34 ,0x35 ,0x36 ,0x37 ,0x38 ,0x39 ,0x3a ,0x3b ,0x3c ,0x3d ,0x3e ,0x3f,
    0xa1 ,0x41,0x42 ,0x43 ,0x44 ,0x45 ,0x46 ,0x47 ,0x48 ,0x49 ,0x4a ,0x4b ,0x4c ,0x4d ,0x4e ,0x4f,
    0x50 ,0x51,0x52 ,0x53 ,0x54 ,0x55 ,0x56 ,0x57 ,0x58 ,0x59 ,0x5a ,0xc4 ,0xd6 ,0xd1 ,0xdc ,0xa7,
    0xbf ,0x61,0x62 ,0x63 ,0x64 ,0x65 ,0x66 ,0x67 ,0x68 ,0x69 ,0x6a ,0x6b ,0x6c ,0x6d ,0x6e ,0x6f,
    0x70 ,0x71,0x72 ,0x73 ,0x74 ,0x75 ,0x76 ,0x77 ,0x78 ,0x79 ,0x7a ,0xe4 ,0xf6 ,0xf1 ,0xfc ,0xe0
};

/* GSM 7 bit default extension table */
static const int GSM_ext_to_UTF8 [CS_CONV_MAX_CHARACTERS] =
{
    -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,
    -1  ,-1  ,-1  ,-1  ,0x5E,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,
    -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,0x7B,0x7D,-1  ,-1  ,-1  ,-1  ,-1  ,0x5C,
    -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,0x5B,0x7E,0x5D,-1  ,
    0x7C,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,
    -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,
    -1  ,-1  ,-1  ,-1  ,-1  ,0x20ac,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,
    -1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1  ,-1
};


int mapper(char c){


    for(int i=0;i<128;i++)

        {

            if(GSM_to_UTF8[i]==c)

                return i;
        }
    for(int i=0;i<128;i++)

        {

            if(GSM_ext_to_UTF8[i]==c)

                return i;
        }

    return -1;


}



bool s_to_b(string a)
{
    if(a=="1")
        return 1;
    else if(a=="0")
        return 0;
}


string bin(int dec)

{

    int rem,i=1,sum=0;

    do

    {

        rem=dec%2;

        sum=sum + (i*rem);

        dec=dec/2;

        i=i*10;

    }while(dec>0);

    string res;

    ostringstream convert;

    convert<<sum;

    res=convert.str();

    return res;

}

string convertBintoHex(string a)

{

    if(a=="0000")

        return "0";

    if(a=="0001")

        return "1";

    if(a=="0010")

        return "2";

    if(a=="0011")

        return "3";

    if(a=="0100")

        return "4";

    if(a=="0101")

        return "5";

    if(a=="0110")

        return "6";

    if(a=="0111")

        return "7";

    if(a=="1000")

        return "8";

    if(a=="1001")

        return "9";

    if(a=="1010")

        return "A";

    if(a=="1011")

        return "B";

    if(a=="1100")

        return "C";

    if(a=="1101")

        return "D";

    if(a=="1110")

        return "E";

    if(a=="1111")

        return "F";



}


void reader()
{
    ifstream myfile;
    myfile.open("test.txt",ios::in);

    string bit_s,receipt_s,validity_s,m_class_s;

    getline(myfile,SMSC,'\n');
    getline(myfile,receiver,'\n');
    getline(myfile,bit_s,'\n');
    getline(myfile,m_class_s,'\n');
    getline(myfile,receipt_s,'\n');
    getline(myfile,validity_s,'\n');

    m_class=m_class_s[0];
    bit=atoi(bit_s.c_str());
    receipt=s_to_b(receipt_s);
    validity=s_to_b(validity_s);


    valid_period_str="";
    if(validity)
    {
     string val_p_s;
     getline(myfile,val_p_s,'\n');
     int val_p=atoi(val_p_s.c_str());
     valid_period_str=pad(bin(val_p),8);
     valid_period_str=convertBintoHex(valid_period_str.substr(0,4))

                                +convertBintoHex(valid_period_str.substr(4,4));
    }

    getline(myfile,message,'\n');
    myfile.close();
}











deque <string> bintohex(deque <string> str,int bits)                 //dividing

{

    int k=str.size();

    for(int i=0;i<k;i++)

    {

        string l=str.front();

        string k="";

        str.pop_front();

        for(int i=0;i<bits;i+=4)

        {

            k=k+convertBintoHex(l.substr(i,4));

        }

        str.push_back(k);



    }

    return str;

}





deque <string> messagemap7(string message)

{

    int msglen=message.length();

    deque <string> a,converted;

    int num=1;

    string f;

    for(int i=0;i<msglen;i++)                   //binary to deque of string

    {

        int c=message[i];

        f=pad(bin(mapper(c)),7);

        a.push_back(f);

    }



    while(a.size()>1)               //deque converted to binary octet

    {

        string f=a.front();

        a.pop_front();

        string l=a.front();

        a.pop_front();

        f=l.substr(l.length()-num,num)+f;

        converted.push_back(f);

        l.erase(l.length()-num,num);

        if(l.length()==0)

            ;

        else

            a.push_front(l);

        num++;

        if(num==8)

            num=1;

    }


    if(!a.empty())                          //False for length in multiples of 8
    {
        string k;                           //Else push over the last unconverted character

        k=pad(a.front(),8);

        a.pop_back();

        converted.push_back(k);
    }



    converted=bintohex(converted,8);

    return converted;

}



char alpha_size(int bits)

{

    if(bits==7)

        return '0';

    else if(bits==8)

        return '4';

    else if(bits==16)

        return '8';

}



string valid_length(string message,int bits)

{

    if(bits==7){

        if(message.length()>160)

        return message.substr(0,160);

        else

        return message;

    }

    else if(bits==8){

        if(message.length()>140)

        return message.substr(0,140);

        else

        return message;

    }

    else if(bits==16){

        if(message.length()>70)

        return message.substr(0,70);

        else

        return message;

    }

}



deque <string> messagemap8_16(string message,int bits)      //for 8 and 16 bit encoding

{

    deque <string> vals;

    int msglen=message.length();

    for(int i=0;i<msglen;i++)

    {

        int k=message[i];

        string f=pad(bin(k),bits);

        vals.push_back(f);



    }

    vals=bintohex(vals,bits);

    return vals;



}



string SMSC_enc(string SMSC)

{

    int len=SMSC.length();

    if(len%2!=0)

        SMSC+="F";

    len=SMSC.length();

    for(int i=0;i<len;i+=2)

    {

        swap(SMSC[i],SMSC[i+1]);

    }

    len=len/2+1;

    ostringstream convert;

    convert<<len;



    return "0"+convert.str()+"91"+SMSC;

}





string class_enc(char m_class,int bit)

{

    string ret_string="";

    if(m_class=='N'){

            ret_string="0";

            ret_string+=alpha_size(bit);

    }

    else

    {

            ret_string="1";

            if(m_class=='0')

                ret_string+=alpha_size(bit);



            else if(m_class=='1')

                ret_string+=(alpha_size(bit)+1);



            else if(m_class=='2')

            {

                if(bit==7||bit==8)

                    ret_string+=(alpha_size(bit)+2);

                else if(bit==16)

                    ret_string+="A";

            }



            else if(m_class=='3')

            {

                if(bit==7||bit==8)

                    ret_string+=(alpha_size(bit)+3);

                else if(bit==16)

                    ret_string+="B";

            }





    }

    return ret_string;

}



string RXR_enc(string rxr)

{

    int len=rxr.length();

    if(len%2!=0)

        rxr+="F";

    len=rxr.length();

    for(int i=0;i<len;i+=2)

    {

        swap(rxr[i],rxr[i+1]);

    }

    string rxr_len=pad(bin(len),8);

    rxr_len=convertBintoHex(rxr_len.substr(0,4))+convertBintoHex(rxr_len.substr(4,4));

    return rxr_len+"91"+rxr;

}







char ticketer(bool receipt,bool validity)

{

    int x='0';

    if(receipt)

        x+=2;

    if(validity)

        x++;

    return x;

}



int main()

{

        deque <string> result;

        message="";
        result.clear();

        string enc_message;              //  Final encoded message


        reader();

//*********************************************************************************************************
//FOR CONSOLE


//      for(int i=1;i<argc;i++){

//	        string j=argv[i];

//		    message+=j+" ";

//	    }
//      message=message.substr(0,message.length()-1);







//***********************************************************************************************************



        message=valid_length(message,bit);      //      Limiting length

        int k=message.length();

        if(bit==16)

            k+=k;

        string m_length=pad(bin(k),8);

        m_length=convertBintoHex(m_length.substr(0,4))+convertBintoHex(m_length.substr(4,4));







        if(bit==7)

            result=messagemap7(message);

        else if(bit==8)

             result = messagemap8_16(message,8);

        else if(bit==16)

             result = messagemap8_16(message,16);

        else{

            cout<<"Invalid. Try again...\n";


        }



        enc_message+=SMSC_enc(SMSC);

        enc_message+=ticketer(receipt,validity);

        enc_message+="100";                         //Delimiter

        enc_message+=RXR_enc(receiver);

        enc_message+="00";                         //TP_ID

        enc_message+=class_enc(m_class,bit);        // Encoding alpha size and class (TP_DCS)

        enc_message+=valid_period_str;

        enc_message+=m_length;


        for(int i=0;i<result.size();i++)            //concat encoded user data

            enc_message+=result[i];



        cout<<enc_message<<"\n\n";



}


