#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

class ToDoList
{
	public:
		string x,y;
};

class Hobby : public ToDoList
{
	public:
		vector< string > todo_h;
		void loaddata()
		{
			ifstream ifs( "input_h.txt" );
			if (ifs.fail())
			{
				cout << "ifs failed." << endl;
				ifs.close( );
			}
			for( int i = 0 ; ifs >> x >> y; i++ )
			{
				todo_h.push_back(x + " " + y);
			}
			ifs.close( );
		};
		void addlist(string l)
		{
			todo_h.push_back(l);
		};
		void listdelete(int s)
		{
			vector< string >::iterator it = todo_h.begin( );
			if(s == 0)
			{
				todo_h.erase(it);
			}
			else
			{
				for(size_t i; i < s; i++)
				{
					++it;
				}
				todo_h.erase(it);
			}
		};
};

class Schedule : public ToDoList
{
	public:
		vector< string > todo_s;
		void addlist(string l)
		{
			todo_s.push_back(l);
		};
		void loaddata()
		{
			ifstream ifs1( "input_s.txt" );
			if (ifs1.fail())
			{
				cout << "ifs failed." << endl;
				ifs1.close( );
			}
			for( int i = 0 ; ifs1 >> x >> y; i++ )
			{
				todo_s.push_back(x + " " + y);
			}
			ifs1.close( );
		};
		void listdelete(int s)
		{
			vector< string >::iterator it = todo_s.begin( );
			if(s == 0)
			{
				todo_s.erase(it);
			}
			else
			{
				for(size_t i; i < s; i++)
				{
					++it;
				}
				todo_s.erase(it);
			}
		};
};

template < class T >
void sort_list(T &hob)
{
	sort( hob.todo_h.begin( ), hob.todo_h.end( ) );
	return;
}

template < class T >
void sort_list(T *sche)
{
	sort( sche->todo_s.begin( ), sche->todo_s.end( ) );
	return;
}

void datashow(class Hobby &x,class Schedule &y)
{
	int x1,y1;
	cout << "趣味：" << endl;
	for( int i=0 ; i< x.todo_h.size(); i++)
	{
		cout << i+1 << " : " << x.todo_h[i] << endl;
	}
	cout << "\n" << "課題：" << endl;
	for( int j=0 ; j< y.todo_s.size(); j++)
	{
		cout << j+1 << " : " << y.todo_s[j] << endl;
	}
	cout << "\n" << endl;
	return;
}

int main(void)
{
	cin.exceptions( ios::failbit );

	Hobby hobby;
	Schedule schedule;

	hobby.loaddata();
	schedule.loaddata();
	
	int select;
	bool flag = true;

	while(flag)
	{
		try
		{
			cout << "1:趣味に追加 , 2:課題に追加 , 3:削除 , 4:リストの表示 , その他:終了" << endl;
			cout << "動作を選択：";
			cin >> select;
			cout << "\n" << endl;
		}
		catch(ios::failure e)
		{
			cout << "Exception" << endl;
			break;
		}
		switch(select)
		{
			case 1:
			{
				string x,y;
				cout << "day doing (ex: 3/11 aaa):";
				cin >> x >> y;
				hobby.addlist(x + " " + y);
			}
				sort_list(hobby);
				break;
			case 2:
			{
				string x,y;
				cout << "day doing (ex: 3/11 aaa):";
				cin >> x >> y;
				schedule.addlist(x + " " + y);
			}
				sort_list(&schedule);
				break;

			case 3:
			{
				string sel;
				cout << "1.趣味 , 2.課題 :";
				cin >> sel;
				if(sel == "1")
				{
					int delnum;
					cout << "何番目を削除 :";
					cin >> delnum;
					hobby.listdelete(delnum);
					sort_list(hobby);
				}
				else if(sel == "2")
				{
					int delnum;
					cout << "何番目を削除 :";
					cin >> delnum;
					schedule.listdelete(delnum-1);
					sort_list(&schedule);
				}
				else
				{
					cout << "　不明な値　" << endl;
				}
			}
				cout << "\n" << endl;
				break;
			
			case 4:
				datashow(hobby,schedule);
				break;
			
			default:
				flag = false;
				break;
		}
	}

	ofstream ofs1( "input_h.txt" );
	ofstream ofs2( "input_s.txt" );

	for( int i=0 ; i< hobby.todo_h.size(); i++)
	{
		ofs1 << hobby.todo_h[i] << endl;
	}
	for( int j=0 ; j< schedule.todo_s.size(); j++)
	{
		ofs2 << schedule.todo_s[j] << endl;
	}

	ofs1.close( );
	ofs2.close( );

	system("pause");
	return 0;
}