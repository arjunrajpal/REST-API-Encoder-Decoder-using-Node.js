//#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <deque>
#include <fstream>
#include <sstream>

#define CS_CONV_MAX_CHARACTERS 128
using namespace std;



bool validity=0,receipt=0;
string enc_message,SMSC_dec,RXR_dec,TP_ID,TP_DCS;
string m_class,alpha_size,val_string,user_data,TP_DCS_popis;
int base,length;

/* GSM 7 bit default mapping table */
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

char demapper(int c){
    return GSM_to_UTF8[c];
}

string pad(string m,int bit)
{
    while(m.length()<bit)
        m="0"+m;
    return m;
}

int bin_to_int(string a)
{
    int x=0,pow=1;
    for(int i=a.length()-1;i>=0;i--)
    {
        x=x+(a[i]-48)*pow;
        pow=pow*2;
    }
    return x;
}

int hex_to_int(string a)
{
    stringstream ss;
    ss<<hex<<a;
    int b;
    ss>>b;
    return b;
}

string int_to_bin(int dec)
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

string convert_to_string(int a)
{
    stringstream ss;
    ss<<a;
    return ss.str();
}



void message_unmap7(string m)
{
    deque <string> unmap;
    for(int i=0;i<m.length();i=i+2){
        string p=m.substr(i,2);
        int x=hex_to_int(p);
        p=int_to_bin(x);
        p=pad(p,8);
        unmap.push_back(p);
    }
    int rem=1;
    string a,temp="",atemp;
    while(!unmap.empty())
    {
        if(rem==8)
        {
            int k=bin_to_int(temp);
            user_data+=(demapper(k)=='\n'?' ':demapper(k));
            temp="";
            rem=1;
        }
        a=unmap.front();
        atemp=a;
        unmap.pop_front();
        a=atemp.substr(rem,atemp.length()-rem)+temp;
        temp=atemp.substr(0,rem);
        rem++;
        int k=bin_to_int(a);
        user_data+=demapper(k);

    }

    if(rem==8)                          //check for leftover temp
        {
            int k=bin_to_int(temp);
            user_data+=(demapper(k)=='\n'?' ':demapper(k));
            temp="";
            rem=1;
        }


}

void message_unmap8_16(string m)
{
    for(int i=0;i<m.length();i=i+base/4)
    {
        int k=hex_to_int(m.substr(i,base/4));
        user_data+=(char)k;
    }
}

void message_decode(string m)
{
    if(base==7)
        message_unmap7(m);
    else if(base==8||base==16)
        message_unmap8_16(m);
}


void deticketer(string enc_message,int i)
{
    if(enc_message[i]=='0')
            validity=receipt=0;
    else if(enc_message[i]=='1'){
        receipt=0;
        validity=1;
    }
    else if(enc_message[i]=='2')
    {
        receipt=1;
        validity=0;
    }
    else if(enc_message[i]=='3')
        receipt=validity=1;

}

string TP_DCS_decoder()
{
        string tp_DCS_desc="";
        stringstream ss;
        ss<<hex<<TP_DCS;
        int pomDCS;
        ss>>pomDCS;
        switch(pomDCS & 192)
        {
            case 0: if(pomDCS & 32)
                    {
                        tp_DCS_desc="Compressed Text\n";
                    }
                    else
                    {
                        tp_DCS_desc="Uncompressed Text\n";
                    }
                    if(!(pomDCS & 16))
                    {
                        tp_DCS_desc+="No class\n";
                    }
                    else
                    {
                        tp_DCS_desc+="Class : ";
                        switch(pomDCS & 3)
                        {
                            case 0:
                                tp_DCS_desc+="0\n";
                                break;
                            case 1:
                                tp_DCS_desc+="1\n";
                                break;
                            case 2:
                                tp_DCS_desc+="2\n";
                                break;
                            case 3:
                                tp_DCS_desc+="3\n";
                                break;
                        }
                    }
                            tp_DCS_desc+="Alphabet : ";
                    switch(pomDCS & 12)
                    {
                        case 0:
                            tp_DCS_desc+="Default\n";
                            base=7;
                            break;
                        case 4:
                            tp_DCS_desc+="8bit\n";
                            base=8;
                            break;
                        case 8:
                            tp_DCS_desc+="UCS2(16)bit\n";
                            base=16;
                            break;
                        case 12:
                            tp_DCS_desc+="Reserved\n";
                            break;
                    }
                    break;
                        case 64:
                        case 128:
                    tp_DCS_desc ="Reserved Coding Group\n";
                    break;
                case 192:
                    switch(pomDCS & 0x30)
                    {
                        case 0:
                            tp_DCS_desc ="Message Waiting Group\n";
                            tp_DCS_desc+="Discard\n";
                            break;
                        case 0x10:
                            tp_DCS_desc ="Message Waiting Group\n";
                            tp_DCS_desc+="Store Message. Default Alphabet\n";
                            break;
                        case 0x20:
                            tp_DCS_desc ="Message Waiting Group\n";
                            tp_DCS_desc+="Store Message. UCS2 Alphabet\n";
                            break;
                        case 0x30:
                            tp_DCS_desc ="Data Coding Message Class\n";
                            if (pomDCS & 0x4)
                            {
                                tp_DCS_desc+="Default Alphabet\n";
                            }
                            else
                            {
                                tp_DCS_desc+="8 bit Alphabet\n";
                            }
                            break;
                    }
                    break;
        }
	return tp_DCS_desc;
}


long long val_relative_convert(int val)
{
    if(val<=143)
        val=val*5+5;
    else if(val>143&&val<=167)
        val=(12*60+(val-143)*30);
    else if(val>167&&val<=196)
        val=(val-166)*24*60;
    else if(val>196&&val<=255)
        val=(4+val-196)*24*60*7;
    return val;
}

void val_convert(int val)
{
    long long vali=(long long)val;
    vali=val_relative_convert(val);         //vali is the relative time in minutes
    long long weeks=vali/(24*60*7);
    vali=vali-weeks*24*60*7;
    long long days=vali/(24*60);
    vali=vali-days*24*60;
    long long hrs=vali/60;
    vali=vali-hrs*60;

    val_string=convert_to_string(weeks)+" weeks "+convert_to_string(days)+
                " days "+convert_to_string(hrs)+" hours "+convert_to_string(vali)+" mins ";
}



void display()
{
    if(receipt)
        cout<<"\nReceipt Requested";
    cout<<"\nSMSC : +"<<SMSC_dec;
    cout<<"\n"<<"Receiver : +"<<RXR_dec;
    cout<<"\n";
    if(validity)
        cout<<"Validity : Rel "<<val_string;
    else
        cout<<"Validity : Not Present ";

    cout<<"\n"<<"TP_ID : "<<TP_ID;
    cout<<"\n"<<"TP_DCS : "<<TP_DCS;
    cout<<"\n"<<"TP_DCS_popis : "<<TP_DCS_popis;
    cout<<"\n\n";
    cout<<user_data;
    cout<<"\n"<<"Length : "<<length;
    cout<<"\n\n\n";
}


int main(int argc, char *argv[])
{
    //while(1){
    int i;
    base=7;
    length=0;
    validity=receipt=0;
    enc_message=SMSC_dec=RXR_dec=TP_DCS=TP_ID="";
    m_class=alpha_size=val_string=user_data=TP_DCS_popis="";
    //cin>>enc_message;
    fstream myfile;
    myfile.open("test2.txt",ios::in);
    getline(myfile,enc_message,' ');
    myfile.close();

   // enc_message=argv[1];





    string SMSC_len=enc_message.substr(0,2);
    if(SMSC_len!="00")
    {
        int SMSC_int_len=atoi(SMSC_len.c_str());
        SMSC_dec=enc_message.substr(4,(SMSC_int_len-1)*2);
        for(i=0;i<SMSC_dec.length();i+=2)
        {
            swap(SMSC_dec[i],SMSC_dec[i+1]);
        }
        i=4+SMSC_dec.length();
        if(SMSC_dec[SMSC_dec.length()-1]=='F')
            SMSC_dec=SMSC_dec.substr(0,SMSC_dec.length()-1);
    }
    else if(SMSC_len=="00")
        i=2;

    deticketer(enc_message,i);

    i=i+4;                              //skipping 100 delimiter
    string RXR_len=enc_message.substr(i,2);
    i=i+4;
    if(RXR_len=="00")
    {

    }
    else if(RXR_len!="00")
    {
        int offset=0;
        int backupi=i;
        int RXR_int_len=hex_to_int(RXR_len);
        if(RXR_int_len%2!=0)
            offset=1;
        RXR_dec=enc_message.substr(i,(RXR_int_len+offset));
        for(i=0;i<RXR_dec.length()+offset;i+=2)
        {
            swap(RXR_dec[i],RXR_dec[i+1]);
        }
        i=backupi+RXR_dec.length();
        if(RXR_dec[RXR_dec.length()+-1]=='F')
            RXR_dec=RXR_dec.substr(0,RXR_dec.length()-1);
    }
    TP_ID=enc_message.substr(i,2);
    i=i+2;
    TP_DCS=enc_message.substr(i,2);
    i=i+2;
    TP_DCS_popis=TP_DCS_decoder();
    if(validity)
    {
        string val_period=enc_message.substr(i,2);
        int val_int=hex_to_int(val_period);
        val_convert(val_int);
        i=i+2;
    }
    string m_length=enc_message.substr(i,2);
    length=hex_to_int(m_length);
    if(base==16)
        length=length/2;
    if(length!=0)
    {
        i=i+2;
        string message=enc_message.substr(i,enc_message.length()-i);
        message_decode(message);
    }
    display();
//    }
}
