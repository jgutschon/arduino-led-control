$port= new-Object System.IO.Ports.SerialPort COM4,9600,None,8,one
$port.open()
$port.WriteLine('f')
$port.close()