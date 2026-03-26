#include<iostream>
#include<fstream>
#include<filesystem>
#include<map>
#include<vector>
using namespace std;

map<string, string> n_f;
string lastopen;
//& findExt
string findExt(string ext){
  for(auto& entry : filesystem::directory_iterator(".")){
    if(entry.path().extension()==ext)
      return entry.path().string().substr(2);
  }
  return "";
}
//!
//& makeFile
void makeFile(string name){
  std::ofstream(name, ios::trunc);
  if(auto s=findExt(name);!s.empty()){
    cout<<"File template created successfully. Edit it and rerun the tool.\n";
  }else{
    cout<<"Error creating file, go deal with it. \n";
  }
}
//!
//& parseFile
void parseFile(string filename){
  fstream in(filename);
  string line;
  while(getline(in, line)){
    if(!line.empty()){
      string name, eq, filepath;
      istringstream ss(line);
      string ext;
      ss>>name>>eq>>filepath;
      if(name=="o.nsnapDONOTTOUCH"){
        lastopen=filepath;
      }
      else if(filepath.starts_with("~/")){
        string btrpath = "/home/nullora/" + filepath.substr(2);
        n_f[name]=btrpath;
      }else{
        n_f[name]=filepath;
      }
    }
  }
}
//!
//& saveFile
void saveFile(string filename){
  ofstream out(filename, ios::trunc);
  for(auto& [name, path] : n_f){
    out<<name<<" = "<<path<<endl;
  }
  out<<"o.nsnapDONOTTOUCH = "<<lastopen<<endl;
}
//!
//& parseTargetFile
string parseTargetFile(string name, string funcname){
  fstream in(n_f[name]);
  string line;
  string func = "//& " + funcname;
  string result="";
  bool infunc=false;
  while(getline(in, line)){
    if(!line.empty()){
      //start function
      if(line==func && !infunc){
        infunc = true;
      }
      //getting snippet
      if(infunc){
        result += line + '\n';
      }
      //end function
      if(line=="//!" && infunc){
        infunc=false;
        return result;
      }
    }
  }
  return result;
}
//!
//& getAllFunctions
string getAllFunctions(string name){
  fstream in(n_f[name]);
  string line;
  string func="//&";
  string result;
  while(getline(in,line)){
    if(!line.empty()){
      if(line.starts_with(func)){
        result += line.substr(3) + '\n';
      }
    }
  }
  return result;
}
//!
//& handlecommand
void handlecommand(string cmd, string var1, string var2){
  if(cmd=="list"){
    cout<<getAllFunctions(var1);
    lastopen=var1;
  }
  if(cmd=="get"){
    cout<<parseTargetFile(lastopen, var1);
  }
}
//!

//&main
int main(int argc, char* argv[]){
  //init
  string var1="";
  string cmd="";
  string var2="";
  if(argc>=2){
    cmd = argv[1];
  }
  if(argc>=3){
    var1=argv[2];
  }
  if(argc>=4){
    var2=argv[3];
  }


  //finding config file
  if(string s=findExt(".nsnap");!s.empty()){
    parseFile(s);
  }else{
    makeFile("o.nsnap");
  }


  //actual parsing
  handlecommand(cmd, var1, var2);
  saveFile(findExt(".nsnap"));
  return 0;
}
//!
