import jssc.SerialPort;
import jssc.SerialPortException;

import java.io.IOException;
import jssc.SerialPort;

public class SerialReader implements Runnable {

    SerialPort serialPort;
    DataHandler dataHandler;
    public SerialReader( SerialPort serialPort,DataHandler dataHandler ) {
        this.serialPort = serialPort;
        this.dataHandler = dataHandler;
    }
    public void run() {
        System.out.println("Start thread: SerialReader");
        byte[] buffer;
        String byteToString;
        try{
            while(true) {
                try {
                    buffer = serialPort.readBytes(1);//Read 10 bytes from serial port
                    byteToString = new String(buffer);
                    this.dataHandler.appendData(byteToString);
                } catch (SerialPortException ex) {
                    System.out.println(ex);
             }
            }
        }finally{
            try {
                this.serialPort.closePort();
            }catch(SerialPortException ex){
                System.out.println(ex);
            }
        }
    }
}
