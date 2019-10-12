#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#define NL "\r\n"
#else
#define NL "\n"
#endif
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include<bits/stdc++.h>
#include <queue>
#include<fstream>
#include<sstream>
#include <unordered_map>
using namespace std;

struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};

void encode(Node* root, string str,
			unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;
   
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int &index, string str)
{
	if (root == nullptr) {
		return;
	}

	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] =='0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

void buildHuffmanTree(string text)
{
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	priority_queue<Node*, vector<Node*>, comp> pq;

	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	Node* root = pq.top();

	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair: huffmanCode) {
		cout << pair.first << ":" << pair.second << '\n';
	}

	cout << "\nOriginal string was :\n" << text << '\n';

	string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n" << str << '\n';
     ofstream fout;
    fout.open("output.txt"); 
    fout<<str;
    fout.close();
    cout<<""<<"Encoded message length:"<<str.length()<<endl;

	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
} 

int tsize; 

struct pnode
{
  char ch;
  float p;
};
  pnode *ptable;
  map<char, string> codes;
static int pnode_compare( const void *elem1, const void *elem2 )
{
  const pnode a = *(pnode*)elem1;
  const pnode b = *(pnode*)elem2;
  if( a.p < b.p ) return 1;
  else if( a.p > b.p ) return -1;
  return 0;
}
void EncShannon( int li, int ri );

void Encode1( const char *inputFilename, const char *outputFilename )
  {
    map<char, int> freqs;
    int i;

    FILE *inputFile;
    inputFile = fopen( inputFilename, "r" );
    assert( inputFile );

    char ch;
    unsigned total = 0;
    while( fscanf( inputFile, "%c", &ch ) != EOF )
    {
      freqs[ch]++;
      total++;
    }
    tsize = (int)freqs.size();

    ptable = new pnode[tsize];
    assert( ptable );
    float ftot = float(total);
    map<char, int>::iterator fi;
    for( fi=freqs.begin(),i=0; fi!=freqs.end(); ++fi,++i )
    {
      ptable[i].ch = (*fi).first;
      ptable[i].p = float((*fi).second) / ftot;
    }
    qsort( ptable, tsize, sizeof(pnode), pnode_compare );

    EncShannon( 0, tsize-1 );

    FILE *outputFile;
    outputFile = fopen( outputFilename, "wb" );
    assert( outputFile );

    printf( "%i"NL, tsize );
    for( i=0; i<tsize; i++ )
    {
      printf("%c\t%f\t%s"NL, ptable[i].ch, ptable[i].p, codes[ptable[i].ch].c_str() );
    }

    fseek( inputFile, SEEK_SET, 0 );
    printf(NL);
    fprintf(outputFile, NL);
 
    while( fscanf( inputFile, "%c", &ch ) != EOF )
    {
      printf("%s", codes[ch].c_str());
      fprintf(outputFile, "%s", codes[ch].c_str());
    }
    printf(NL);

    codes.clear();
    delete[] ptable;

    fclose( outputFile );
    fclose( inputFile );
  }
  
  void Decode1( const char *inputFilename, const char *outputFilename )
  {

    FILE *inputFile;
    inputFile = fopen( inputFilename, "r" );
    assert( inputFile );

    fscanf( inputFile, "%i", &tsize );
    char ch, code[128];
    float p;
    int i;
    fgetc( inputFile ); 
    for( i=0; i<tsize; i++ )
    {
      ch = fgetc(inputFile);
      fscanf( inputFile, "%f %s", &p, code );
      codes[ch] = code;
      fgetc(inputFile); 
    }
    fgetc(inputFile); 

    FILE *outputFile;
    outputFile = fopen( outputFilename, "w" );
    assert( outputFile );

    string accum = "";
    map<char, string>::iterator ci;
    while((ch = fgetc(inputFile)) != EOF)
    {
      accum += ch;
      for( ci=codes.begin(); ci!=codes.end(); ++ci )
        if( !strcmp( (*ci).second.c_str(), accum.c_str() ) )
        {
          accum = "";
          printf( "%c", (*ci).first );
          fprintf( outputFile, "%c", (*ci).first );
        }
    }
    printf(NL);

    fclose( outputFile );
    fclose( inputFile );
  }
void EncShannon( int li, int ri )
  {
    int i, isp;
    float p;
    float pfull;
    float phalf;

    if( li == ri )
    {
      return;
    }
    else if( ri - li == 1 )
    {
      codes[ptable[li].ch] += '0';
      codes[ptable[ri].ch] += '1';
    }
    else
    {
      pfull = 0;
      for( i=li; i<=ri; ++i )
      {
        pfull += ptable[i].p;
      }

      p = 0;
      isp = -1;
      phalf = pfull * 0.5f;
      for( i=li; i<=ri; ++i )
      {
        p += ptable[i].p;
        if(p <= phalf) {
          codes[ptable[i].ch] += '0';
        }
        else
        {
          codes[ptable[i].ch] += '1';
          if( isp < 0 ) isp = i;
        }
      }
      
      if( isp < 0 ) isp = li+1;

      EncShannon( li, isp-1 );
      EncShannon( isp, ri );
    }
  }
  int show_usage() {
  printf("Shannon-Fano coding algorithm"NL);
  printf("by Sergey Tikhonov (st@haqu.net)"NL);
  printf(NL);
  printf("Usage: shannon [OPTIONS] input [output]"NL);
  printf("  The default action is to encode input file."NL);
  printf("  -d\tDecode file."NL);
  printf(NL);
  printf("Examples:"NL);
  printf("  shannon input.txt"NL);
  printf("  shannon input.txt encoded.txt"NL);
  printf("  shannon -d encoded.txt"NL);
  printf(NL);
  exit(0);
}

int main(int argc, char **argv)
{    
	cout<<"Select Encoding"<<endl;
	cout<<"1. Huffman"<<endl;
	cout<<"2. Shannon-Fano"<<endl;
	int x;
	cin>>x;
	if(x==1){
	ifstream f(argv[1]);
   string str;
   if(f) {
      ostringstream ss;
      ss << f.rdbuf();
      str = ss.str();
   }
	buildHuffmanTree(str);
}else{
int i = 1;
  int dFlag = 0;
  char inputFilename[128];
  char outputFilename[128];

  printf(NL);

  if(i == argc) show_usage();

  if(strcmp(argv[i],"-d") == 0) {
    dFlag = 1;
    i++;
    if(i == argc) show_usage();
  }

  strcpy(inputFilename, argv[i]);
  i++;

  if(i < argc) {
    strcpy(outputFilename, argv[i]);
  } else {
    if(dFlag) {
      strcpy(outputFilename, "decoded.txt");
    } else {
      strcpy(outputFilename, "encoded.txt");
    }
  }

  
  if(!dFlag) {
    Encode1( inputFilename, outputFilename );
    ifstream is;
    string FileName="encoded.txt";
is.open (FileName.c_str(), ios::binary );
is.seekg (0, ios::end);
int length = is.tellg();
cout<<"\n"<<"Length of encoded message : "<<length<<endl;
  } else {
    Decode1( inputFilename, outputFilename );
  }
  

  printf(NL);
}
	return 0;
}
