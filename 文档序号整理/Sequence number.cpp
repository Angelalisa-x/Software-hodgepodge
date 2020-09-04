#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h> 

using namespace std;

#define MAXBUFSIZE 1024
 
class Sequence
{
public:
    Sequence();
    ~Sequence();

    void doProcess();
    

private:
    void GetFileNames(string path, vector<string>& filenames);
    void process(string fileName);
    void createShScript(string copyName);
    void finalFiling(string filePath);
    
    ifstream m_fin;
    ofstream m_fout;
    vector<string> m_file_name;

};

Sequence::Sequence()//:m_fin("data.txt",ios::in), m_fout("out.txt",ios::ate|ios::out)
{
    char buf[ MAXBUFSIZE ];
    getcwd(buf, MAXBUFSIZE);
    GetFileNames(buf, m_file_name);

}

Sequence::~Sequence()
{
    m_fout << "\r\n";
    //m_fin.close();
    //m_fout.close();
}

void Sequence::GetFileNames(string path, vector<string>& filenames)
{
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path.c_str())))
        return;
    while((ptr = readdir(pDir))!=0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
            filenames.push_back(path + "/" + ptr->d_name);
    }
    closedir(pDir);

}

void Sequence::process(string fileName)
{
    m_fin.open(fileName.c_str(), ios::in);
    m_fout.open("out.txt", ios::out);
    if(!m_fin){
        cout << "Error" << fileName.c_str() << "doesn't exist" << endl;
    }


    string sGetLine = "yudong";
    int iCount = 1;
    string strCount ="";

    while(getline(m_fin, sGetLine)){
        stringstream ss;
        ss << iCount;
        ss >> strCount;

        if(sGetLine.empty() || sGetLine.size() <= 1){
            m_fout << sGetLine << endl;
            continue;
        }

        if(sGetLine[0] == '\t' || sGetLine[0] == ' '){
            m_fout << sGetLine << endl;
            continue;
        }

        int iPos = sGetLine.find(".", 0);
        if(iPos != -1){
            string strRight = sGetLine.substr(iPos, sGetLine.size());
            sGetLine = strCount + strRight;
            m_fout << sGetLine << endl;
            //cout <<sGetLine << endl;
            iCount++;
        }
        
    }
    m_fout.close();
    m_fin.close();
}

void Sequence::createShScript(string copyName)
{
    string mkdirTest = "Transit";
    mkdir(mkdirTest.c_str(),S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);

    string strCommand = "cp -R ";
    strCommand += "out.txt ";
    strCommand += "Transit/";
    strCommand += ";cd Transit";
    strCommand += ";mv out.txt " + copyName + ";cd ..";
    strCommand += ";rm -rf out.txt";

    char buff[1024];
    strCommand.copy(buff,strCommand.length(), 0);
    //cout << "strCommand:" << strCommand << endl;
    system(buff);

}

void Sequence::finalFiling(string filePath)
{
    string strScript = "cd Transit ;";
    strScript += "cp -R * ../ ;";
    strScript += "cd .. ;";
    strScript += "rm -rf Transit ;";
    strScript += "rm -rf out.txt";

    char buff[256];
    strScript.copy(buff,strScript.length(), 0);
    //cout << "strScript:" << strScript << endl;
    system(buff);
}


void Sequence::doProcess()
{
    for(int i =0; i< m_file_name.size(); i++)
    {
        //cout << m_file_name[i] << endl;
        if(m_file_name[i].find(".txt~") != -1 || (m_file_name[i].find("out.txt") != -1)){
            continue;
        }

        if(m_file_name[i].find(".txt") != -1){
            int iPosTxt = m_file_name[i].find_last_of("/");
            if(iPosTxt != -1){
                string strFileName = m_file_name[i].substr(iPosTxt + 1, m_file_name[i].size());

                this->process(strFileName);
                //cout << strFileName << endl;
                this->createShScript(strFileName);
                
            }
            
        }

    }
    this->finalFiling("123\123");

}


int main(void)
{

    Sequence seq;
    seq.doProcess();

    return 0;

}