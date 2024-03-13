using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;
using System.Windows.Shapes;

namespace LunikEditor.Utils
{
    enum MessageType
    {
        Info    = 0x01,
        Warning = 0x02,
        Error   = 0x04
    }

    class LogMessage
    {
        public DateTime Time { get; }
        public MessageType MessageType { get; }
        public string Message { get; }
        public string File { get; }
        public string Caller { get; }
        public int Line { get; }
        public string MetaData => $"{File}({Line}): {Caller}";

        public LogMessage(MessageType type, string message, string file, string caller, int line)
        {
            Time = DateTime.Now;
            MessageType = type;
            Message = message;
            File = System.IO.Path.GetFileName(file);
            Caller = caller;
            Line = line;
        }
    }

    static class Logger
    {
        private static int _messageFillter = (int)(MessageType.Info | MessageType.Warning | MessageType.Error);
        private readonly static ObservableCollection<LogMessage> _logMessages = new ObservableCollection<LogMessage>();
        public static ReadOnlyObservableCollection<LogMessage> LogMessages { get; } = new ReadOnlyObservableCollection<LogMessage>(_logMessages);
        public static CollectionViewSource FilteredMessage { get; } = new CollectionViewSource() { Source = LogMessages };

        public static async void Log(MessageType type, string message, [CallerFilePath] string file = "", [CallerMemberName]string caller = "", [CallerLineNumber]int line = 0)
        {
            await Application.Current.Dispatcher.BeginInvoke(new Action(() =>
            {
                _logMessages.Add(new LogMessage(type, message, file, caller, line));
            }));
        }

        public static async void Clear()
        {
            await Application.Current.Dispatcher.BeginInvoke(new Action(() =>
            {
                _logMessages.Clear();
            }));
        }

        public static void SetMessageFillter(int mask)
        {
            _messageFillter = mask;
            FilteredMessage.View.Refresh();
        }

        static Logger()
        {
            FilteredMessage.Filter += (s, e) =>
            {
                var type = (int)(e.Item as LogMessage).MessageType;
                e.Accepted = (type & _messageFillter) != 0;
            };
        }
    }
}
