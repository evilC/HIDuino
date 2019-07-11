using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Management;
using System.Text;
using System.Threading.Tasks;

namespace SerialTest
{
    public class SerialTester
    {
        private readonly SerialPort _serialPort;

        public SerialTester()
        {
            var arduinos = AutodetectArduinoPort();
            if (arduinos.Count == 0)
            {
                Console.WriteLine("Cannot find Arduino, exiting...");
            }
            Console.WriteLine($"Found {arduinos.Count} arduinos.\nConnecting to first found Arduino: {arduinos[0].Name} on port {arduinos[0].Port}");
            Console.WriteLine("Esc to exit, any other key to send char to Arduino");
            _serialPort = new SerialPort(arduinos[0].Port, 115200) {DtrEnable = true};
            _serialPort.DataReceived += sp_DataReceived;
            _serialPort.Open();
            while (true)
            {
                var key = Console.ReadKey().KeyChar.ToString();
                if (key == "\u001b")
                {
                    break;
                }
                _serialPort.Write(key);
            }
        }

        private void sp_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            Console.WriteLine();
            while (_serialPort.BytesToRead != 0)
            {
                var data = _serialPort.ReadLine();
                Console.WriteLine($"Data Received: {data}");
            }
        }

        // https://stackoverflow.com/questions/3293889/how-to-auto-detect-arduino-com-port
        private static List<ArduinoDescriptor> AutodetectArduinoPort()
        {
            var arduinos = new List<ArduinoDescriptor>();
            var connectionScope = new ManagementScope();
            var serialQuery = new SelectQuery("SELECT * FROM Win32_SerialPort");
            var searcher = new ManagementObjectSearcher(connectionScope, serialQuery);

            try
            {
                foreach (var item in searcher.Get())
                {
                    var desc = item["Description"].ToString();
                    var deviceId = item["DeviceID"].ToString();

                    if (desc.Contains("Arduino"))
                    {
                        arduinos.Add(new ArduinoDescriptor{Name = desc, Port = deviceId});
                    }
                }
            }
            catch (ManagementException e)
            {
                /* Do Nothing */
            }

            return arduinos;
        }

        public class ArduinoDescriptor
        {
            public string Name { get; set; }
            public string Port { get; set; }
        }
    }
}
