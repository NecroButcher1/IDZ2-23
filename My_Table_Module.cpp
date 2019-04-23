#include "My_Table.h"
template<typename T>
table<T>::table(){
	row=0;
	col=0;
	body=NULL;
}
template<typename T>
int table<T>::get_row(){
	return row;
}
template<typename T>
int table<T>::get_col(){
	return col;
}
template<typename T>
int table<T>::Set(int i,int j,T _data){
	errcode=0;
	if((i>row)||(i<0)||(j<0)||(j>col))errcode=INNCORECT_DATA;
	else{
		this->body[i][j]=_data;
	}
	return errcode;
}
template<typename T>
int table<T>::Get(int i,int j,T &_data){
	errcode=0;
	if((i>row)||(i<0)||(j>col)||(j<0))errcode=INNCORECT_DATA;
	else{
		if(body==NULL)errcode=EMPTY_TABLE;
		else{
			_data=body[i][j];
		}
	}
	return errcode;
}
template<typename T>
int table<T>::create(int _row,int _col){
	errcode=0;
	if((_row<0)||(_col<0))errcode=INNCORECT_DATA;
	else{
		this->row=_row;
		this->col=_col;
		body=new T*[row];
		for(unsigned i=0;i<row;i++){
			body[i]=new T[col];
		}
	}
	return errcode;
}
template<typename T1>
int getfile(std::ifstream &in,table<T1> &t){
    int num=0,_row=0,_col=0;
    t.del();
    int errcode=0;
    if(!in.is_open())errcode=ERR_FILE;
    else{
		in.seekg(0,ios::end);
		if(in.tellg()==0)errcode=EMPTY_FILE;
		else{
			in.seekg(0,ios::beg);
			in>>_row;
			if(in.fail())errcode=INNCORECT_DATA;
			in>>_col;
			if(in.fail())errcode=INNCORECT_DATA;
			if(errcode==0)t.create(_row,_col);
			for(int i=0;((i<t.row)&&(errcode==0));i++){
				for(int j=0;((j<t.col)&&(errcode==0));j++){
					in>>t.body[i][j];
					if(in.fail()){
						errcode=INNCORECT_DATA;
						num=0;
					}
					num++;
				}
			}
			if(errcode!=0||(num!=_row*_col))t.del();
		}
    }
    return errcode;
}
template<typename T1>
int Keys(table<T1>&b){
	int out=0;
	if(b.body==NULL)out=EMPTY_TABLE;
	else{
		int local=0;
		int *key=new int[b.row];
		for(unsigned i=0;i<b.row;i++){
			local=0;
			for(unsigned j=0;j<b.col;j++){
				local=local+b.body[i][j];
			}
			key[i]=abs(local);
		}
		out=Quick_Sort(b,key,0,b.row);
		delete[]key;
	}
	return out;
}
template<typename T1>
int Quick_Sort(table<T1>&b,int *key, int from, int to){
    int x, i, j, temp,out=0;
    if(b.body==NULL)out=EMPTY_TABLE;
    else{
        if(from >= to){
            out=0;
        }
        else{
            TElem *tmp;
            i = from;
            j = to-1;
            x = key[(from+to)/2];
            while(i <= j){
                    while(key[i] > x) i++;
                    while(key[j] < x) j--;
                    if(i <= j){
                        temp = key[i];
                        key[i] = key[j];
                        key[j] = temp;
                        tmp=b.body[i];
                        b.body[i]=b.body[j];
                        b.body[j]=tmp;
                        i++;
                        j--;
                    }
                }
                Quick_Sort(b,key, from, j);
                Quick_Sort(b,key, i, to);
        }
    }
    return out;
}
template<typename T>
int table<T>::Save(std::ostream& out){
	int errcode=0;
	if(body==NULL)errcode=EMPTY_TABLE;
	else{
		out<<row<<endl;
		out<<col<<endl;
		for(unsigned i=0;i<row;i++){
			for(unsigned j=0;j<col;j++){
				out<<body[i][j]<<" ";
			}
			out<<endl;
		}
	}
	return errcode;
	//cout<<"lol";
}
template<typename T>
void table<T>::del(){
	if(body!=NULL){
		for(unsigned i=0;i<row;i++)delete[]body[i];
		delete[]body;
		body=NULL;
		row=0;
		col=0;
	}
}
template<typename T>
table<T>::~table(){
	if(body!=NULL){
		for(unsigned i=0;i<row;i++)delete[]body[i];
		delete[]body;
		body=NULL;
		row=0;
		col=0;
	}
}
template<typename T1>
int redact_printf(table<T1>&b,int lx,int ly,int size_y,int size_x){
	int out=0,i,j;
	if(b.body!=NULL){
		system("cls");
		cout<<"==========================================================="<<endl;
		cout<<"1.[Esc]    =Exit             [TAB] = GoTo elem[i][j]"<<endl;
		cout<<"2.[PgDown] =Fill from file   [PgUp]=Save in File"<<endl;
		cout<<"3.[ENTER]  =Redact elem"<<endl;
		cout<<"==========================================================="<<endl;
		if(b.row>=size_y){
            if(b.col>=size_x){
                for(i=ly;i<size_y;i++){
                    for(j=lx;j<size_x;j++){
                        cout.width(6);
                        cout<<b.body[i][j];
                    }
                    cout<<endl;
                }
            }
            else{
                for(i=ly;i<size_y;i++){
                    for(j=0;j<b.col;j++){
                        cout.width(6);
                        cout<<b.body[i][j];
                    }
                    cout<<endl;
                }
            }
        }
        else{
            if(b.col>=size_x){
                for(i=0;i<b.row;i++){
                    for(j=lx;j<size_x;j++){
                        cout.width(6);
                        cout<<b.body[i][j];
                    }
                cout<<endl;
                }
            }
            else{
                for(i=0;i<b.row;i++){
                    for(j=0;j<b.col;j++){
                        cout.width(6);
                        cout<<b.body[i][j];
                    }
                    cout<<endl;
                }
            }
        }
    }
    else{
        out=EMPTY_TABLE;
    }
    return out;
}
template<typename T1>
int Redact(table<T1>&b){
	int out=0,i,j,size_x=10,size_y=10,lx=0,ly=0,check,cord_y=-1,cord_x=-1,check_file,ichecker,x,y;
	char filename[50],s[5]=".txt";
	T1 c,k;
	if(b.body==NULL)out=EMPTY_TABLE;
	else{
		redact_printf(b,lx,ly,size_y,size_x);
		bool exit=false;
		int ch;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD position ={1,5};
		SetConsoleCursorPosition(hConsole,position);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		while(!exit){
			ch=_getch();
			switch(ch){
			case 224:
				{
				switch(_getch()){
				case 73:
					{
						system("cls");
						cout<<"PRESS FILE NAME >>";
						cin>>filename;
						strcat(filename,s);
						ofstream fout;
						fout.open(filename);
						ichecker=b.Save(fout);
						fout.close();
						if(ichecker==EMPTY_TABLE){
							cout<<"TABLE DONT EXIST"<<endl;
							out=1;
							exit=true;
						}
						if(ichecker==0){
							cout<<"EXCELENT FILL"<<endl;
							getchar();
							cout<<"PRESS ENTER"<<endl;
							getchar();
							redact_printf(b,lx,ly,size_y,size_x);
						}
						position={1,5};
                        SetConsoleCursorPosition(hConsole, position);
                        SetConsoleCursorPosition(hConsole, position);
                        break;
					}
					case 81:
					{
						system("cls");
						cout<<"PRESS FILE NAME >>: ";
						cin>>filename;
						strcat(filename,s);
						ifstream fin;
						fin.open(filename);
						b.del();
						ichecker=getfile(fin,b);
						fin.close();
						if(ichecker==0){
							cout<<"EXCELLENT FILL"<<endl;
							cout<<"PRESS ENTER"<<endl;
							_getch();
							system("cls");
							redact_printf(b,lx,ly,size_y,size_x);
							position={1,5};
							SetConsoleCursorPosition(hConsole, position);
							SetConsoleCursorPosition(hConsole, position);
						}
						else{
							if(ichecker==ERR_FILE)cout<<"ERROR OPEN FILE"<<endl;
							if(ichecker==EMPTY_FILE)cout<<"EMPTY FILE"<<endl;
							if(ichecker==INNCORECT_DATA)cout<<"INNCORECT DATA"<<endl;
							b.del();
							out=1;
							exit=true;
						}
						break;
					}
					case 72:
					{
						if(position.Y>5){
							position.Y--;
                            SetConsoleCursorPosition(hConsole, position);
                            SetConsoleCursorPosition(hConsole, position);
						}
						if(position.Y==5){
							if(size_y>10){
								ly--;
								size_y--;
								redact_printf(b,lx,ly,size_y,size_x);
								position.Y=5;
								SetConsoleCursorPosition(hConsole, position);
								SetConsoleCursorPosition(hConsole, position);
							}
						}
						break;
					}
					case 80:
					{
						 if(b.row>size_y){
                            if(position.Y<14){
                                position.Y++;
                                SetConsoleCursorPosition(hConsole, position);
                                SetConsoleCursorPosition(hConsole, position);
                            }
                            if(position.Y==14){ //position.Y==size_y+3
                                ly++;
                                size_y++;
                                redact_printf(b,lx,ly,size_y,size_x);
                                position.Y=14;
                                SetConsoleCursorPosition(hConsole, position);
                                SetConsoleCursorPosition(hConsole, position);
                            }
                        }
                        else{
                            if(position.Y<b.row-ly+4)
                            {
                                position.Y++;
                                SetConsoleCursorPosition(hConsole, position);
                                SetConsoleCursorPosition(hConsole, position);
                            }
                        }
                        break;
					}
					case 77:
					{
						if(b.col>size_x){
                            if(position.X<60){
                                position.X++;
                                SetConsoleCursorPosition(hConsole, position);
                                SetConsoleCursorPosition(hConsole, position);
                            }
                            if(position.X==60){
                                lx++;
                                size_x++;
                                redact_printf(b,lx,ly,size_y,size_x);
                                position.X=59;
                                SetConsoleCursorPosition(hConsole, position);
                                SetConsoleCursorPosition(hConsole, position);
                            }
                        }
                        else {
                            if(position.X<(b.col*6-lx*6-1)){
                                position.X++;
                                SetConsoleCursorPosition(hConsole, position);
                                SetConsoleCursorPosition(hConsole, position);
                            }
                        }
                        break;
					}
					case 75:
					{
						 if(position.X>1){
                            position.X--;
                            SetConsoleCursorPosition(hConsole, position);
                            SetConsoleCursorPosition(hConsole, position);
                        }
                        if(position.X==1){
                            if(size_x>10){
                                lx--;
                                size_x--;
                                system("cls");
                                redact_printf(b,lx,ly,size_y,size_x);
                                position.X=1;
                                SetConsoleCursorPosition(hConsole, position);
                                SetConsoleCursorPosition(hConsole, position);
                            }
                        }
                        break;
					}
					default:
                    break;
				}
				break;
			}
			case 13:
			{
				check=0;
				system("cls");
				while((!cin)||(check<1)||(check>2)){
					system("cls");
					cout<<"Change elem ?"<<endl;
					cout<<"1.Yes"<<endl;
                    cout<<"2.NO"<<endl;
                    cin>>check;
				}
				if(check==1){
					x=(position.X)/6+lx;
					y=position.Y-5+ly;
					c=b.body[y][x];
					 system("cls");
					cout<<x<<" "<<y<<endl;
					cout<<c<<" "<<"PRESS ELEM >>";
					cin>>k;
					while(!cin){
						system("cls");
						cin.clear();
						std::cin.ignore(32767, '\n');
						cout<<c<<" "<<"PRESS ELEM >>";
						cin>>k;
					}
					b.body[y][x]=k;
					redact_printf(b,lx,ly,size_y,size_x);
				}
				else{
					redact_printf(b,lx,ly,size_y,size_x);
				}
					position = {1, 5};
					SetConsoleCursorPosition(hConsole, position);
					SetConsoleCursorPosition(hConsole, position);
					break;
				}
				 case 9:
                {
                    system("cls");
                    cord_y=-1;
                     while((cord_y<0)||(cord_y>b.row)||(std::cin.fail())){
                        system("cls");
                        cout<<"press CORD [i] >>";
                        cin>>cord_y;
                            if(std::cin.fail()){
                                system("cls");
                                cord_y=-1;
                                std::cin.clear();
                                std::cin.ignore(32767, '\n');
                                cout<<"press CORD [i] >>";
                                cin>>cord_y;
                            }
                    }
                    cord_x=-1;
                    while((cord_x<0)||(cord_x>b.col)||(std::cin.fail())){
                        system("cls");
                        cout<<"press CORD [j] >>";
                        cin>>cord_x;
                            if(std::cin.fail()){
                                system("cls");
                                cord_x=-1;
                                std::cin.clear();
                                std::cin.ignore(32767, '\n');
                                cout<<"press CORD [j] >>";
                                cin>>cord_x;
                            }
                        }
                        if(cord_y<=ly){
                            while(ly>=cord_y){
                                ly--;
                                size_y--;
                            }
                        }
                        if(cord_x<=lx){
                            while(lx>=cord_x){
                                lx--;
                                size_x--;
                            }
                        }
                        if(cord_y>size_y){
                            while(size_y<cord_y){
                                size_y++;
                                ly++;
                            }
                        }
                        if(cord_x>size_x){
                            while(size_x<cord_x){
                                size_x++;
                                lx++;
                            }
                        }
                        cord_x=cord_x*6-1-6*lx;
                        cord_y=cord_y+4-ly;
                        redact_printf(b,lx,ly,size_y,size_x);
                        position.Y=cord_y;
                        position.X=cord_x;
                        SetConsoleCursorPosition(hConsole, position);
                        SetConsoleCursorPosition(hConsole, position);
                        break;
                    }
				   case 27:
                {
                    exit = true;
                    break;
                }
                default:
                break;
			}
		}
	}
	system("cls");
	return out;
}
