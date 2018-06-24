package RoboArm.UI.Client;

import java.io.*;
import java.net.*;


public class SocketClient
{
    private final String ip;
    private final int port;
    private Socket echoSocket;
    private InputStream serverResponseReader;
    private PrintWriter clientRequestWriter;
    private String lastResponse;

    private static final int MAX_DATA_SIZE = 1024;

    SocketClient(String _ip, int _port)
    { 
        port = _port; 
        ip = _ip;
    }

    public void openSocket() throws IOException
    {
        try
        {
            echoSocket = new Socket(ip, port);
            serverResponseReader = echoSocket.getInputStream();
            clientRequestWriter = new PrintWriter(echoSocket.getOutputStream(), true);
        }
        catch(UnknownHostException uhe)
        {
            System.err.println("Unknown host!");
            System.exit(1);
        }
        catch(IOException ioe)
        {
            System.err.println("Could not get I/O for the connection!");
            System.exit(1);
        }
    }

    public String sendRequestToServerAndGetResponse(String request) throws IOException
    {
        //Send requet to server
        if(request != null)
            clientRequestWriter.println(request);
        else
            clientRequestWriter.println("none");

        //Read response from server
        byte[] data = new byte[MAX_DATA_SIZE];
        int count = 0;
        try
        {
            count = serverResponseReader.read(data);
        }
        catch (IOException ioe)
        {
            System.err.println("Data read exception!");
            data = null;
            System.exit(1);
        }

        String response;
        if(data != null)
            response = new String(data, 0, count);
        else
            response = "Invalid response";

        lastResponse = response;

        return response;
    }

    public String getLastResponse()
    {
        if(lastResponse != null)
            return lastResponse;
        else
            return "none";
    }

    public void closeSocket() throws IOException
    {
        try
        {
            echoSocket.close();
            serverResponseReader.close();
            clientRequestWriter.close();
        }
        catch(IOException ioe)
        {
            System.err.println("Could not get I/O for the connection!");
            System.exit(1);
        }
    }

    public static void main(String[] args) throws IOException 
    {
        try
        {
            SocketClient client = new SocketClient("localhost", 8080);
            client.openSocket();
            String response = client.sendRequestToServerAndGetResponse("Hello from new Java socket client class!!!");
            client.closeSocket();
            System.out.println("Response from server: " + response);
        } 
        catch (Exception e)
        {
            System.err.println("Something went wrong!");
            System.exit(1);
        }
    }
}