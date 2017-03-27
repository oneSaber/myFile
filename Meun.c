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

//ɾ���ļ�
void DeleteLyric()
{
	system("cls");
	int X = PrintFrame();
	printf_s("�����������");
	NextLine(X);
	char LyricName[81];//������
	gets(LyricName);
	NextLine(X);
	printf_s("�����������");
	NextLine(X);
	char SingerName[81];//������
	gets(SingerName);
	NextLine(X);
	printf_s("ɾ�����ļ���");
	NextLine(X);
	printf_s("1)��\t2)��");
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
//�����ļ�
void AddLyric()
{
	system("cls");
	int x = PrintFrame();
	printf_s("�����������");
	NextLine(x);
	char SingerName[81];
	gets(SingerName);
	char Singer[81];
	strcpy_s(Singer, 81, SingerName);
	strcat_s(SingerName, 81, ".txt");
	FILE *fSinger;
	if (fopen_s(&fSinger, SingerName, "w+")== 0)
	{
		printf_s("�����������");
		NextLine(x);
		char Song[81];
		gets(Song);
		fseek(fSinger, 0, SEEK_END);
		fprintf_s(fSinger, "\n%s", Song);
	}
	ContralMusic();
}

//�������
void ContralMusic()
{
	system("cls");
	int x = PrintFrame();
	printf_s("1) ɾ������");
	NextLine(x);
	printf_s("2) ���Ӹ���");
	NextLine(x);
	printf_s("3) ������һ��");
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

//���������
void Eatline()
{
	char n;
	while ((n = getchar()) != '\n')
	continue;
}

//��������ļ�����
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
				printf_s("N) ��һҳ");
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

		printf_s("����Ҫ�򿪵ĸ�����");
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
			printf_s("��ʱû�и��");
			NextLine(X);
			NextLine(X);
			printf_s("1�� ������һ��");
			int choose = GetChoose();
			if (choose == 1)
			{
				SerachSinger(path);
				return;
			}
		}
		
	}
}
//����������
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

//��������
void SerachSinger(int path)
{
	system("cls");
	int x = PrintFrame();
	printf_s("������Ҫ���ҵĸ�������");
	NextLine(x);
	char SingerName[29];
	gets(SingerName);
	strcat_s(SingerName,29,".txt");
	FILE *fSinger;
	fopen_s(&fSinger, SingerName, "r");
	while (fSinger==NULL)
	{
		NextLine(x);
		printf_s("���ݿ���û����λ���֣�����������");
		NextLine(x);
		printf_s("y)����������");
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
	printf_s("L��������һ��");
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
//��������
void SerachSong(int path)
{
	system("cls");
	int x = PrintFrame();
	printf_s("������Ҫ���ҵĸ�������(����ĸ��д��");
	NextLine(x);
	char SongName[29];
	gets(SongName);
	strcat_s(SongName, 29, ".txt");
	FILE *fSong;
	fopen_s(&fSong,SongName, "r");
	while (fSong == NULL)
	{
		NextLine(x);
		printf_s("���ݿ���û�����׸���������������");
		NextLine(x);
		printf_s("y)����������");
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
	printf_s("1)������һ�˵�");
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
//���ƹ��
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
//��ӭʹ�ý���
void PrintfWelcome(int x,int y)
{
	printf_s("��ӭʹ�ñ�Ktv���ϵͳ");
	GotoXY(x,y+1);
}

//ѡ���¼ģʽ
void LognAS()
{
	PrintFrame();
	GotoXY(10, 3);
	PrintfWelcome(WhereX(),WhereY());
	int X = WhereX();
	printf_s("ѡ����ĵ�½���");
	NextLine(X);
	printf_s("1) ���û���ݵ�½��");
	NextLine(X);
	printf_s("2) �Թ���Ա��ݵ�½");
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
			printf_s("��������ȷѡ��");
			result = GetChoose(); 
		}			
		break;
		}
	}	
}

//�õ��û������ѡ��
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

//����Ա�˵�
void AdmMeun()
{
	system("cls");
	int x = PrintFrame();
	printf_s("��ѡ��Ҫ���еĲ�����");
	NextLine(x);
	printf_s("1) ���Ҹ���");
	NextLine(x);
	printf_s("2) ���Ҹ���");
	NextLine(x);
	printf_s("3) ��������");
	NextLine(x);

	printf_s("4) ������һ��");
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
	default:printf_s("��ѡ����Чѡ��");
	break;
	}
	
}
//��Ϊ�û���½
void UserMeun()
{
	system("cls");
	int x = PrintFrame();
	printf_s("��ѡ��Ҫ���еĲ�����");
	NextLine(x);
	printf_s("1) ���Ҹ���");
	NextLine(x);
	printf_s("2) ���Ҹ���");
	NextLine(x);
	printf_s("3) ������һ��");
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
	default:printf_s("��ѡ����Чѡ��");
	break;
	}
}
//�˵���
int PrintFrame(void)
{
	//��һ��
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
