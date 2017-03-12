$EventListenerDef=@"
namespace PStips.Net
{
    using System;
    using System.Diagnostics;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.IO;
    public class EventListener
    {
        public string EventName { private set; get; }
        public string EventSource { private set; get; }
        private EventLog log;
        public EventListener(string eventName, string eventSource)
        {
            log = new EventLog(eventName);
            log.Source = eventSource;
            log.EnableRaisingEvents = true;
            log.EntryWritten += log_EntryWritten;
        }
        int cishu = 0;
        void log_EntryWritten(object sender, EntryWrittenEventArgs e)
        {
            cishu = 1 + cishu;
            Console.WriteLine("=============================��{0}�νػ�=============================",cishu);
            if (e.Entry.InstanceId==20221)
            {
		StreamWriter f = new StreamWriter(@"log.txt", false);  
            	f.WriteLine("�ѽػ����Ϣ:Id={0},Message={1},Time={2}",e.Entry.InstanceId,e.Entry.Message,e.Entry.TimeGenerated);
            	f.Close();
		Console.WriteLine("======================�ػ�ɹ�,�븴����ʵ�˺�======================\n");
            	string str = e.Entry.Message;
		int start = str.IndexOf("Dial-in User = ");
		int length = str.IndexOf("VpnStrategy");
		string card = str.Substring(start, length-start-1);
		Console.WriteLine(card);
	    }
	    else
	    {
	        Console.WriteLine("==========================�ػ���Ч��Ϣ===========================\r");
	    }
	    Console.WriteLine("\n**************************�뿪ʼ��ı���!**************************\n");
		}
    }
}
"@
Add-Type -TypeDefinition $EventListenerDef
New-Object PStips.Net.EventListener -ArgumentList 'Application','EventCreate'
Write-Host '**************************�뿪ʼ��ı���!**************************

===========================����رմ���!===========================
============���ڵ�1�뵽��3���ڵ����¼��ʼ����,�ȴ��ػ�============
===================��¼��ʱ��δ��Ӧ�볢������!===================

**************************�뿪ʼ��ı���!**************************

' -NoNewline
$null = [Console]::ReadKey('?')