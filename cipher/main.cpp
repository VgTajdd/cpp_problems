#include <iostream>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <process.h>

using namespace std;

string msg = "Bgc-bfufb tegaedppqna ql aggv zge xof tegaedppfe\'l lgjb.\n\
Xof adpf vflqanfe logjbvn\'x hf pdwqna d cgebv qn coqro xof tbdkfe ql mjlx d lpdbb tdex. Xof tbdkfe QL XOF HGLL; qx\'l kgje vjxk xg fnxfexdqn oqp ge ofe.\n\
Zgrjl ql d pdxxfe gz vfrqvqna codx xoqnal kgj def ngx agqna xg vg.\n\
Xof rglx gz dvvqna d zfdxjef qln\'x mjlx xof xqpf qx xdwfl xg rgvf qx. Xof rglx dblg qnrbjvfl xof dvvqxqgn gz dn ghlxdrbf xg zjxjef fstdnlqgn. Xof xeqrw ql xg tqrw xof zfdxjefl xodx vgn\'x zqaox fdro gxofe. - Mgon Rdepdrw.\n\
(ccc.adpdljxed.rgp/uqfc/nfcl/234346?utkjpvbjr)\n\
(ccc.hedqnkijgxf.rgp/ijgxfl/djxogel/m/mgon_rdepdrw.oxpb)\n";

string freqLang     = "TEOAISRHNUCMDLGWFPYKJBVQX";
string alphabet     = "abcdefghijklmnopqrstuvwxyz";

void decryptMessage( const string& message, const string& freqLang )
{
    string decryptedMsg;
    vector<int> freq; // Frequency by letter position.
    freq.resize( alphabet.size(), 0 );

    for ( int i = 0; i < message.size(); i++ )
    {
        auto it = find( alphabet.begin(), alphabet.end(), tolower( message[i] ) );
        if ( it != alphabet.end() )
        {
            freq[distance( alphabet.begin(), it )]++;
        }
    }

    string freqLang2; // New frequency table.
    {
        vector<pair<int, char>> map_freq;
        for ( int i = 0; i < freq.size(); i++ )
        {
            map_freq.emplace_back( freq[i], alphabet[i] );
        }
        sort( map_freq.rbegin(), map_freq.rend() ); // Reverse iterators (descendent).
        for ( auto it : map_freq )
        {
            freqLang2.append( 1, it.second );
        }
        /*cout << freqLang2.c_str() << endl;*/
    }
    for ( int i = 0; i < message.size(); i++ )
    {
        char c = message[i];
        bool upper = isupper( c );
        auto it = find( freqLang2.begin(), freqLang2.end(), tolower( c ) );
        if ( it == freqLang2.end() )
        {
            decryptedMsg.append( 1, c );
        }
        else
        {
            int d = distance( freqLang2.begin(), it );
            char toPut = tolower( freqLang[d] );
            if ( upper )
            {
                toPut = toupper( toPut );
            }
            decryptedMsg.append( 1, toPut );
        }
    }
    cout << decryptedMsg.c_str();
}

void main()
{
    decryptMessage( msg, freqLang );
    system("pause");
}