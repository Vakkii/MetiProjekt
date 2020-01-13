import java.io.IOException;
import java.io.InputStream;

public class SerialReader implements Runnable {

    InputStream in;
    DataHandler dataHandler;
    public SerialReader( InputStream in,DataHandler dataHandler ) {
        this.in = in;
        this.dataHandler = dataHandler;
    }

    public void run() {

        byte[] buffer = new byte[1024];
        int len = -1;
        try {
            while( ( len = this.in.read( buffer ) ) > -1 ) {
                String buf =  new String( buffer, 0, len );
                this.dataHandler.appendData(buf);


            }
        } catch( IOException e) {
            e.printStackTrace();
        }
    }
}
