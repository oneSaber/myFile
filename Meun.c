#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>

#define Lenth 70
#define Width 20

int PrintFrame(void);
int WhereX();
int WhereY();
void GotoXY(int x, int y);
void NextLine(int line);
void PrintfWelcome(int x, int y);
void LognAS();
int GetChoose();
void AdmMeun();
void UserMeun();
void SerachSinger(int path);
void SerachSong(int path);
void ShowLyric(FILE* fSong, int path);
void ContralMusic();

//删除文件
void DeleteLyric()
{
	system("cls");
	int X = PrintFrame();
	printf_s("输入歌曲名字");
	NextLine(X);
	char LyricName[81];//歌曲名
	gets(LyricName);
	NextLine(X);
	printf_s("输入歌手名字");
	NextLine(X);
	char SingerName[81];//歌手名
	gets(SingerName);
	NextLine(X);
	printf_s("删除该文件吗？");
	NextLine(X);
	printf_s("1)是\t2)否");
	NextLine(X);
	int choose = GetChoose();
	if (choose==1)
	{
		strcat_s(SingerName, 81, ".txt");
		FILE* fSinger;
		if ((fopen_s(&fSinger,SingerName,"r+"))==0)
		{
			char Song[81];
			fgets(Song,81,fSinger);
			while (strcmp(Song,LyricName)==0)
			{
				fprintf_s(fSinger, "");
			}
			strcat_s(LyricName, 81, ".txt");
			remove(LyricName);
		}
	}
	ContralMusic();
}
//增加文件
void AddLyric()
{
	system("cls");
	int x = PrintFrame();
	printf_s("输入歌手名字");
	NextLine(x);
	char SingerName[81];
	gets(SingerName);
	char Singer[81];
	strcpy_s(Singer, 81, SingerName);
	strcat_s(SingerName, 81, ".txt");
	FILE *fSinger;
	if (fopen_s(&fSinger, SingerName, "w+")== 0)
	{
		printf_s("输入歌曲名字");
		NextLine(x);
		char Song[81];
		gets(Song);
		fseek(fSinger, 0, SEEK_END);
		fprintf_s(fSinger, "\n%s", Song);
	}
	ContralMusic();
}

//管理歌曲
void ContralMusic()
{
	system("cls");
	int x = PrintFrame();
	printf_s("1) 删除歌曲");
	NextLine(x);
	printf_s("2) 增加歌曲");
	NextLine(x);
	printf_s("3) 返回上一级");
	NextLine(x);
	int choose = GetChoose();
	switch (choose)
	{
	case 1:DeleteLyric();
		break;
	case 2:AddLyric();
		break;
	case 3:AdmMeun();
		break;
	}
}

//清楚输入流
void Eatline()
{
	char n;
	while ((n = getchar()) != '\n')
	continue;
}

//输出歌手文件内容
void ShowSingerSong(FILE* fSinger,int path)
{
	if (fSinger==NULL)
	{
		return;
	}
	else
	{
		system("cls");
		PrintFrame();
		int X = WhereX();

		int i = 0;
		while (!feof(fSinger))
		{
			if (i == 5)
			{
				printf_s("N) 下一页");
				char answer = getchar();
				Eatline();
				if (answer == 'N')
				{
					system("Cls");
					PrintFrame();
					i = 0;
				}
			}
			char SongName[81];
			fgets(SongName, 81, fSinger);
			printf_s("%s", SongName);
			NextLine(X);
			i++;
		}

		printf_s("输入要打开的歌曲名");
		NextLine(X);
		char OpenSongName[81];
		gets(OpenSongName);
		strcat_s(OpenSongName, 81,".txt");
		FILE *fSong;
		fopen_s(&fSong, OpenSongName, "r");
		if (fSong!=NULL)
		{
			ShowLyric(fSong,3);
		}
		else
		{
			printf_s("暂时没有歌词");
			NextLine(X);
			NextLine(X);
			printf_s("1） 返回上一级");
			int choose = GetChoose();
			if (choose == 1)
			{
				SerachSinger(path);
				return;
			}
		}
		
	}
}
//输出歌曲歌词
void ShowLyric(FILE* fSong, int path)
{
	if (fSong==NULL)
	{
		return;
	}
	else {
		system("cls");
		int X = PrintFrame();
		char Lyric[50];
		int i = 0;
		while (!feof(fSong))
		{
			if (i==10)
			{
				printf_s("1)Next");
				int choose = GetChoose();
				if (choose ==1)
				{
					system("cls");
					PrintFrame();
				}
				i = 0;
			}
			fgets(Lyric, 50, fSong);
			GotoXY(X, WhereY() - 1);
			printf_s("%s",Lyric);
			NextLine(X);
			i++;
		}
	}
}

//搜索歌手
void SerachSinger(int path)
{
	system("cls");
	int x = PrintFrame();
	printf_s("输入你要查找的歌手名字");
	NextLine(x);
	char SingerName[29];
	gets(SingerName);
	strcat_s(SingerName,29,".txt");
	FILE *fSinger;
	fopen_s(&fSinger, SingerName, "r");
	while (fSinger==NULL)
	{
		NextLine(x);
		printf_s("数据库中没有这位歌手，请重新输入");
		NextLine(x);
		printf_s("y)放弃搜索？");
		char choose = getchar();
		if (choose=='y')
		{
			break;
			fSinger = NULL;
		}
		gets(SingerName);
		strcat_s(SingerName,29, ".txt");
		fopen_s(&fSinger, SingerName, "r");
	}
	ShowSingerSong(fSinger,path);
	Eatline();
	system("cls");
	PrintFrame();
	printf_s("L）返回上一级");
	NextLine(x);
	char choose = getchar();
	if (choose == 'L')
	{
		switch (path)
		{
		case 1: UserMeun();
			break;
		case 2:AdmMeun();
			break;
		}
	}
}
//搜索歌曲
void SerachSong(int path)
{
	system("cls");
	int x = PrintFrame();
	printf_s("输入你要查找的歌曲名字(首字母大写）");
	NextLine(x);
	char SongName[29];
	gets(SongName);
	strcat_s(SongName, 29, ".txt");
	FILE *fSong;
	fopen_s(&fSong,SongName, "r");
	while (fSong == NULL)
	{
		NextLine(x);
		printf_s("数据库中没有这首歌曲，请重新输入");
		NextLine(x);
		printf_s("y)放弃搜索？");
		char choose = getchar();
		if (choose == 'y')
		{
			fSong = NULL;
			break;		
		}
		gets(SongName);
		strcat_s(SongName, 29, ".txt");
		fopen_s(&fSong, SongName, "r");
	}
	ShowLyric(fSong, path);
	printf_s("1)返回上一菜单");
	int choose = GetChoose();
	if (choose==1)
	{
		switch (path)
		{
		case 1: UserMeun(); break;
		case 2: AdmMeun(); break;
		}
	}
}
//控制光标
int WhereX()
{
	CONSOLE_SCREEN_BUFFER_INFO pBuffer;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
	return (pBuffer.dwCursorPosition.X + 1); 
}
int WhereY()
{
	CONSOLE_SCREEN_BUFFER_INFO pBuffer;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
	return (pBuffer.dwCursorPosition.Y + 1);
}
void GotoXY(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void NextLine(int x)
{
	GotoXY(x, WhereY()+1);
}
//欢迎使用界面
void PrintfWelcome(int x,int y)
{
	printf_s("欢迎使用本Ktv点歌系统");
	GotoXY(x,y+1);
}

//选择登录模式
void LognAS()
{
	PrintFrame();
	GotoXY(10, 3);
	PrintfWelcome(WhereX(),WhereY());
	int X = WhereX();
	printf_s("选择你的登陆身份");
	NextLine(X);
	printf_s("1) 以用户身份登陆；");
	NextLine(X);
	printf_s("2) 以管理员身份登陆");
	NextLine(X);
	int result = GetChoose();
	while (result!=-1)
	{
		switch (result)
		{
		case 1:UserMeun();
			break;
		case 2:AdmMeun();
			break;
		default: {
			printf_s("请输入正确选项");
			result = GetChoose(); 
		}			
		break;
		}
	}	
}

//得到用户输入的选择
int GetChoose()
{
	char answers[50];
	gets(answers);
	int i = 0;
	while (answers[i]!='\0')
	{
		if (answers[i]<'9'&&answers[i]>'0')
		{
			return answers[i] - '0';
		}
		else i++;
	}
	return -1;
}

//管理员菜单
void AdmMeun()
{
	system("cls");
	int x = PrintFrame();
	printf_s("请选择要进行的操作：");
	NextLine(x);
	printf_s("1) 查找歌手");
	NextLine(x);
	printf_s("2) 查找歌曲");
	NextLine(x);
	printf_s("3) 管理曲库");
	NextLine(x);

	printf_s("4) 返回上一级");
	NextLine(x);
	int result = GetChoose();
	switch (result)
	{
	case 1: SerachSinger(2);
	break;
	case 2: SerachSong(2);
	break;
	case 3:ContralMusic();
	break;
	case 4: {
		system("cls");
		LognAS();
	}
	default:printf_s("请选择有效选项");
	break;
	}
	
}
//作为用户登陆
void UserMeun()
{
	system("cls");
	int x = PrintFrame();
	printf_s("请选择要进行的操作：");
	NextLine(x);
	printf_s("1) 查找歌手");
	NextLine(x);
	printf_s("2) 查找歌曲");
	NextLine(x);
	printf_s("3) 返回上一级");
	NextLine(x);
	int result = GetChoose();
	switch (result)
	{
	case 1:SerachSinger(1);
	break;
	case 2: SerachSong(1);
	break;
	case 3: {
		system("cls");
		LognAS();
	}
	break;
	default:printf_s("请选择有效选项");
	break;
	}
}
//菜单框
int PrintFrame(void)
{
	//第一行
	for (int cout = 0; cout < Lenth; cout++)
	{
		printf_s("=");
	}
	printf_s("\n");
	for (int cout = 0; cout < Width; cout++)
	{
		printf_s("=");
		for (int i = 0; i < Lenth-1; i++)
		{
			printf_s(" ");
		}
		printf_s("=");
		printf_s("\n");
	}
	for (int cout = 0; cout < Lenth; cout++)
	{
		printf_s("=");
	}
	GotoXY(10, 3);
	return WhereX();
}

int main()
{
    LognAS();
	system("pause");
}
