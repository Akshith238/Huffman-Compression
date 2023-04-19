#include<cstring>
#include<vector>
#include<iostream>
#include<iomanip>
#include<queue>
#include<fstream>
using namespace std;
string str;
int count3 = 0;
int count1 = 0;
int num = 254;
char chh = char(num);
vector<pair<char,string> > charactermap;
vector<int> Huffcode;

class BitwiseWrite
{
private:
    char buf;
    int Tbits;
    ostream& out;
public:
    BitwiseWrite(ostream & os) : out(os),buf(0),Tbits(0)
    {
    //clear buffer and bit counter
    }
    void flush(); // write buffer into output file and clear it
    void writeBit(int i);
};

void BitwiseWrite::flush()
{
    out.put(buf);
    out.flush();
    buf = Tbits = 0;
}

void BitwiseWrite::writeBit(int i)
{
    if( i == -1)
    {
        flush();
    }
    if(Tbits == 8)
    {
        flush();
    }
    if(i == 1)
    {
        buf = 1;
    }
    if(i == 0)

    {
        buf = 0;
    }
    Tbits++;
}


class MinHeapNode
 {
 public:
    int data;
    int freq;
    MinHeapNode *lchild, *rchild;

    MinHeapNode(int data, int freq)
    {
        this->lchild = this->rchild = NULL;
        this->data = data;
        this->freq = freq;
    }
};

struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

// Prints huffman codes from
// the root of Huffman Tree.
int p;
string str1= "";
int n=0;

void printCodes(struct MinHeapNode* root, string str)
{

    if (!root)
    {
        return;
    }

if (root->data != chh)
{
    char ch;
    ch = char(root->data);
    cout <<"\t "<< ch << "\t\t\t " << str << "\n";
    for(int i = 0;i < count3;i++)
    {
        if(charactermap[i].first == ch)
        {
            charactermap[i].second = str;
        }
    }
}
    printCodes(root->lchild, str + "0");
    printCodes(root->rchild, str + "1");
}
// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
void HuffmanCodes(int data[], int freq[], int size)
{
    struct MinHeapNode *lchild, *rchild, *top;

    // Create a min heap & inserts all characters of data[]


    for (int i = 0; i < size; ++i) //Build Heap
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1)
    {

    // Extract the two minimum
    // freq items from min heap
    lchild = minHeap.top();
    minHeap.pop();

    rchild = minHeap.top();
    minHeap.pop();

    // Create a new internal node with
    // frequency equal to the sum of the
    // two nodes frequencies. Make the
    // two extracted node as lchild and rchild children
    // of this new node. Add this node
    // to the min heap 'â– ' is a special value
    // for internal nodes, not used
    top = new MinHeapNode(chh, lchild->freq + rchild->freq);

    top->lchild = lchild;
    top->rchild = rchild;
    minHeap.push(top);
    }

    // Print Huffman codes using
    // the Huffman tree built above
    printCodes(minHeap.top(),"");
}


void calculate_frequency(int frequency[],char filename[])
{
    char ch,ch1;
    int y;
    int f;
    int x;
    ifstream fin;
    fin.open(filename);
    if(!fin.is_open())
    {
        cout <<"Error !!! Cannot open Source file.\n";
        cin>>y;
        exit(1);
    }
    while(fin.get(ch))
    {
        if( ch >=32 && ch < 255)
        {
            charactermap.push_back(make_pair(ch,""));
            count3++;
        }
        y = int(ch);
        frequency[y]=frequency[y]+1;
    }
    ch1 = char(129);
    charactermap.push_back(make_pair(ch1,""));
    count3++;
    fin.close();
}

void SeperateCharacter(int frequency[],int actual_frequency[],int ASCII_values[])
{
    int k =0;
    int y=0;
    for(int j=32;j < 254;j++) //For seperating occurring and non-occurring characters & to create actual
    {                                        // frequency array & ASCII_values array
        if(frequency[j] != 0)
        {
            actual_frequency[k] = frequency[j];
            ASCII_values[y] = j;
            y++;
            k++;
            count1++;
        }
    }
    actual_frequency[y] = 1; // For adding pseudo-EOF in actual_frequency & ASCII_values arrays
    ASCII_values[k] = 129;
    count1++;
}

void Convert_StringBits_to_IntegerBits()
{
    string temp;
    for (int i = 0; i < charactermap.size();i++)
    {
        temp = charactermap[i].second;
        for(int j=0;j < temp.size();j++) //For storing strings bits into integer vector,for writing bit by bit in file
        {
            if(temp[j] == '1')
            {
                Huffcode.push_back(1);
            }
            else
            {
                Huffcode.push_back(0);
            }
        }
}
    Huffcode.push_back(-1);
}
void printFrequencyTable(int actual_frequency[],int ASCII_values[])
{
    char ch;
    cout<<"\n\tFrequency Table of Characters present in file\n\n";
    cout<<"\t===================================================\n";
    cout<<"\tCharacters\t\tFrequency\n";
    cout<<"\t===================================================\n";
    for(int i=0; i < count1; i++)
    {
        ch = char(ASCII_values[i]);
        cout<<"\t "<<ch<<"\t\t\t "<<actual_frequency[i]<<"\n";
    }
}

// Driver program to test above functions
int main()
{
    int frequency[256]={0};
    int ASCII_values[256]={0};
    int actual_frequency[256]={0};
    char ch;
    char filename[50];
    char cfilename[50];
    string decode;
    cout<<"\n\t====================================";
    cout<<"\n\t\t Text File Compressor\n";
    cout<<"\t====================================";
    cout<<"\n\nEnter Name of File to Compress : ";
    cin>>filename;


    calculate_frequency(frequency,filename); //To calculate frequency of each character in file

    SeperateCharacter(frequency,actual_frequency,ASCII_values); //Make actual frequency array and ASCII values

    printFrequencyTable(actual_frequency,ASCII_values); // Print frequency table
    cout<<"\nCharacter Table with Huffman codes \n";
    cout<<"\n\tCharacter\t\tHuffman Code\n";

    HuffmanCodes(ASCII_values,actual_frequency,count1); //Function to build Huffman tree

    Convert_StringBits_to_IntegerBits(); //Converts character from charactermap to int vector

    int len = strlen(filename);
    filename[len-1] = 'p';
    filename[len-2] = 'm';
    filename[len-3] = 'c';
    cout<<"\n";
    ofstream fout;
    fout.open(filename,ios::binary);
    int temp1;
    BitwiseWrite s(fout);
    cout<<"\nProcessing.... Plz wait !!!";
    for(int d = 0;d < Huffcode.size();d++)
    {
        temp1 = Huffcode[d];
        s.writeBit(temp1); //To write Bit by bit by bit in compressed file
    }
    cout<<"\nCompression Successful !!!";
    int v;
    cout<<"\nEnter any key to exit : ";
    cin>>v;
    return 0;

}

