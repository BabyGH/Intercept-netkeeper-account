// Intercept-netkeeper-account.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#using <System.dll>

using namespace std;
using namespace System;
using namespace System::Diagnostics;
using namespace System::Threading;
using namespace System::IO;

ref class Listener
{
private:

	// �¼������ź�
	static AutoResetEvent^ signal;

public:

	static void main()
	{
		signal = gcnew AutoResetEvent(false);
		EventLog^ NewLog = gcnew EventLog;
		NewLog->Source = "RasClient";
		NewLog->EntryWritten += gcnew EntryWrittenEventHandler(EntryWritten);
		NewLog->EnableRaisingEvents = true;
		NewLog->WriteEntry("Test message", EventLogEntryType::Information);
		signal->WaitOne();
	}

	static void EntryWritten(Object^ source, EntryWrittenEventArgs^ e)
	{

		Console::WriteLine("���ص�һ���¼���ID={0}", e->Entry->InstanceId);
		//�ж��Ƿ�����Ҫ���¼�ID��������������ѡ����Ӧ��ID
		if (e->Entry->InstanceId == 20221)
		{
			//���浽������Ϊ����
			String^ fileName = "log.txt";
			StreamWriter^ sw = gcnew StreamWriter(fileName);
			sw->WriteLine("�ѽػ����Ϣ:Id={0},Message={1}", e->Entry->InstanceId, e->Entry->Message);
			sw->WriteLine(DateTime::Now);
			sw->Close();

			//ֻ��ȡ��Ҫ���˺Ų���
			String^ str = e->Entry->Message;
			int start = str->IndexOf("Dial-in User = ");
			int length = str->IndexOf("VpnStrategy");
			String^ card = str->Substring(start, length - start - 1);

			//�����Ҫ���˺ŵ�����̨
			Console::WriteLine("���¼���Ч���븴�������˺�\n{0}", card);
			Console::WriteLine("**************************\n");
		}
		else
		{
			Console::WriteLine("���¼���Ч�������²���");
			Console::WriteLine("**************************\n");
		}
		signal->Set();
	}
};

int main()
{
	cout << "Made By LinKey0811\nhttps://github.com/LinKey0811 \n***************" << endl;
	//�������ؿ���
	int contral;
	cout << "������ 1 ��ʼ���أ����� 0 �ر�\n";
	do
	{
		cin >> contral;
		if (contral == 1)
		{
			cout << "���ؿ�ʼ���벦��\n=====================\n" << endl;
			Listener::main();
		}
	} while (contral == 1);
	return 0;
}

