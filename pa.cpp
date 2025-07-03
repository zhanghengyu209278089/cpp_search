#include <bits/stdc++.h>
using namespace std;
int maxdep;
map<string,string> website;
int cnt=0;
void pa(string page,int dep){
	if(website.size()>50) return;
	if(dep>maxdep) return;
	website[page]=" ";
	cout<<page<<endl;
	{
		system(("curl -# \""+page+"\" | find \"<a\" > code"+to_string(dep)+".txt").c_str());
		ifstream fin(("code"+to_string(dep)+".txt").c_str());
		string code;
		while(getline(fin,code)){
			code.erase(0,code.find("href"));
			code.erase(0,5);
			char tmp=code[0];
			code.erase(0,1);
			string link;
			for (int i=0;i<code.size();i++){
				if(code[i]==tmp) break;
				link+=code[i];
			}
			bool flag=1;
			if(flag){
				if(link.find("/")==0&&(link.size()>2&&link[1]!='/')){
					if(page.find(link)==string::npos){
						string tmps=page;
						if(page.find("/",8)!=string::npos)page.erase(page.find("/",8));
						pa(page+link,dep+1);
						page=tmps;
					}
				}
				else if(link.find("http")==0){
					pa(link,dep+1);
				}
				else if(link.size()>2&&link[0]=='/'&&link[1]=='/'){
					pa("https:"+link,dep+1);
				}
				else{
					if(page.find(link)==string::npos){
						string tmps=page;
						if(page.rfind("/")!=string::npos&&page.rfind("/")>8)page.erase(page.rfind("/"));
						pa(page+"/"+link,dep+1);
						page=tmps;
					}
				}
			}
			
		}
	}
	{
		system(("curl -# \""+page+"\" | find \"<link\" > code"+to_string(dep)+".txt").c_str());
		ifstream fin(("code"+to_string(dep)+".txt").c_str());
		string code;
		while(getline(fin,code)){
			code.erase(0,code.find("href"));
			code.erase(0,5);
			char tmp=code[0];
			code.erase(0,1);
			string link;
			for (int i=0;i<code.size();i++){
				if(code[i]==tmp) break;
				link+=code[i];
			}
			bool flag=1;
			if(flag){
				if(link.find("/")==0&&(link.size()>2&&link[1]!='/')){
					if(page.find(link)==string::npos){
						string tmps=page;
						if(page.find("/",8)!=string::npos)page.erase(page.find("/",8));
						pa(page+link,dep+1);
						page=tmps;
					}
				}
				else if(link.find("http")==0){
					pa(link,dep+1);
				}
				else if(link.size()>2&&link[0]=='/'&&link[1]=='/'){
					pa("https:"+link,dep+1);
				}
				else{
					if(page.find(link)==string::npos){
						string tmps=page;
						if(page.rfind("/")!=string::npos&&page.rfind("/")>8)page.erase(page.rfind("/"));
						pa(page+"/"+link,dep+1);
						page=tmps;
					}
				}
			}
			
		}
	}
	system(("del code"+to_string(dep)+".txt").c_str());
}

int main(){
	system("chcp 65001");
	string url,urlm;
	getline(cin,url);
	maxdep=1;
	pa(url,0);
	//system("cls");
	for (auto it=website.begin();it!=website.end();it++){
		system(("curl -# \""+it->first+"\" | find \"<title>\" > title.txt").c_str());
		string tmp;
		ifstream fin("title.txt");
		string title;
		getline(fin,tmp);
		tmp.erase(0,tmp.find("<title>"));
		//tmp.erase(0,tmp.find( "src"));
		tmp.erase(0,string("<title>").size());
		for (int i=0;i<tmp.size();i++){
			if(tmp[i]=='<') break;
			title+=tmp[i];
		}
		website[it->first]=title;
	}
	//system("cls");
	string fname;
	cin>>fname;
	ofstream fout(fname.c_str());
	if(!fout.good()){
		cout<<"CANNOT OPEN OUTPUT FILE ";
		cout<<fname;
		return 0;
	}
	int cnt=0;
	for (auto it=website.begin();it!=website.end();it++){
		fout<<"	    { \"url\": \""<<it->first<<"\", \"title\": \""<<it->second<<"\""<<"}";
		if(cnt!=website.size()-1) fout<<",";
		fout<<endl;
		cnt++;
	}
	system("del title.txt");
	return 0;
}

