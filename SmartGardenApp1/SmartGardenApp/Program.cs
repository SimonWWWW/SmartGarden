using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SmartGardenApp
{
    class Program
    {
        static SerialPort SP;
        static void Main(string[] args)
        {
            SP = new SerialPort();
            SP.PortName = "COM3";
            SP.BaudRate = 9600;
            //SP.ReadTimeout = 500;
            SP.Open();
            while (true)
            {
                Console.WriteLine(SP.ReadLine());
            }
        }
    }
}
