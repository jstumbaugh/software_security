/***********************************************************************

   SimpleWebServer.java


   This toy web server is used to illustrate security vulnerabilities.
   This web server only supports extremely simple HTTP GET requests.

   This file is also available at http://www.learnsecurity.com/ntk

***********************************************************************/

package com.learnsecurity;

import java.io.*;
import java.net.*;
import java.util.*;
import java.util.Base64;


public class SimpleWebServer implements Runnable {

    /* Maximum allowed file size in bytes to be sent */
    private static final int MAXIMUM_FILE_SIZE = 1000;

    /* default user name and password */
    private static final String USERNAME = "default_username";
    private static final String PASSWORD = "default_password";


    private Thread t;
    private String server_name;
    private int port;

    /* The socket used to process incoming connections
       from web clients */
    private static ServerSocket dServerSocket;

    /* Constructor for accepting a name or not */
    public SimpleWebServer() throws Exception { this("default_server_name", 8080); }

    public SimpleWebServer(String name, int p) throws Exception {
        server_name = name;
        port = p;
        dServerSocket = new ServerSocket(port);
    }

    public void start() {
        System.out.println("Starting " + server_name + " on port " + port);
        t = new Thread(this, server_name);
        t.start();
    }

    public void run() {
        System.out.println("RUNNING " + server_name);
        while (true) {
            try {
                /* wait for a connection from a client */
                Socket s = dServerSocket.accept();

                /* then process the client's request */
                processRequest(s);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    /* Reads the HTTP request from the client, and
       responds with the file the user requested or
       a HTTP error code. */
    public void processRequest(Socket s) throws Exception {
        /* used to read data from the client */
        BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));

        /* used to write data to the client */
        OutputStreamWriter osw = new OutputStreamWriter(s.getOutputStream());

        osw.write("Processing Request on " + server_name + "\n");

        /* read the HTTP request from the client */
        String request = br.readLine();
        String command = null;
        String pathname = null;

        /* parse the HTTP request */
        StringTokenizer st = new StringTokenizer(request, " ");
        command = st.nextToken();
        pathname = st.nextToken();

        /* Authenticate User */
        // if (!userAuthenticated(br)) {
        //     logEntry("log.txt", "Unauthorized");
        //     osw.write("WWW-Authenticate: Basic realm=SimpleWebServer");
        //     osw.write("\nHTTP/1.1 401 Unauthorized");
        // } else {
            logEntry("log.txt", "Authorized");
            if (command.equals("GET")) {
                /* if the request is a GET, try to respond with the file the user
                   is requesting */

                serveFile(osw,pathname);
                logEntry("log.txt", command + " " + pathname);
            } else if (command.equals("PUT")) {
                /* if the request is a PUT, store the file */

                String file_to_write_to = pathname.replaceAll(".*\\/", "");

                FileReader input_fr = new FileReader(pathname);
                BufferedReader input_br = new BufferedReader(input_fr);

                storeFile(input_br, osw, file_to_write_to);
                logEntry("log.txt", command + " " + file_to_write_to);
            } else {
                /* if the request is a NOT a GET, return an error saying this server
                  does not implement the requested command */
                String error = "HTTP/1.0 501 Not Implemented";
                osw.write(error);
                logEntry("log.txt", command + " " + pathname + " ERROR: " + error);
            }
        // }

        /* close the connection to the client */
        osw.close();
    }

    public boolean userAuthenticated(BufferedReader br) throws Exception {
        String host = br.readLine();
        String auth = br.readLine();

        /* remove the HTTP header portion */
        auth = auth.replaceAll("Authorization: Basic ", "");

        /* Decode the authorization string */
        byte[] decodedBytes = Base64.getDecoder().decode(auth);
        auth = new String(decodedBytes, "UTF-8");

        StringTokenizer st = new StringTokenizer(auth, ":");
        String username = st.nextToken();
        String password = st.nextToken();

        /* Authenticate user */
        logEntry("log.txt", "Attempting to authenticate " + username + " with password " + password);
        return (username.equals(USERNAME) && password.equals(PASSWORD));
    }

    public void storeFile(BufferedReader br, OutputStreamWriter osw, String pathname) throws Exception {
        FileWriter fw = null;
        try {
            fw = new FileWriter(pathname);
            String s = br.readLine();
            while (s != null) {
              fw.write(s);
              s = br.readLine();
            }
            fw.close();
            osw.write("HTTP/1.1 100 Continue\n\n");
        }
        catch (Exception e) {
            String msg = "HTTP/1.1 500 Internal Server Error";
            logEntry("error_log.txt", msg + " - Attempting to open " + pathname);
            osw.write(msg + "\n\n");
            return;
        }
    }

    public void logEntry(String filename, String record) throws Exception {
        FileWriter fw = new FileWriter(filename, true);
        fw.write(getTimestamp() + " " + record + "\n");
        fw.close();
    }

    public String getTimestamp() {
        return (new Date()).toString();
    }

    public void serveFile(OutputStreamWriter osw, String pathname) throws Exception {
        FileReader fr=null;
        int c=-1;
        StringBuffer sb = new StringBuffer();

        /* remove the initial slash at the beginning
           of the pathname in the request */
        if (pathname.charAt(0)=='/')
            pathname = pathname.substring(1);

        /* if there was no filename specified by the
           client, serve the "index.html" file */
        if (pathname.equals(""))
            pathname = "index.html";

        /* Check to see if the file requested was smaller than the maximum allowed */
        if (checkFileSize(pathname) == 403) {
            String msg = "HTTP/1.0 403 Forbidden";
            osw.write(msg + "\n");
            logEntry("error_log.txt", msg + " - " + pathname + " too large");
            return;
        }

        /* try to open file specified by pathname */
        try {
            fr = new FileReader(pathname);
            c = fr.read();
        }
        catch (Exception e) {
            /* if the file is not found,return the
               appropriate HTTP response code  */
            e.printStackTrace();
            osw.write("HTTP/1.0 404 Not Found\n\n");
            return;
        }

        /* if the requested file can be successfully opened
           and read, then return an OK response code and
           send the contents of the file */
        osw.write("HTTP/1.0 200 OK\n\n");
        while (c != -1) {
            sb.append((char)c);
            c = fr.read();
        }
        osw.write(sb.toString());
    }

    /* This method checks to see if the file requested is under the maximum
       allowed file size */
    public int checkFileSize(String path) {
        File file = new File(path);
        if (file.length() > MAXIMUM_FILE_SIZE) {
            return 403;
        } else {
            return 0;
        }
    }

    /* This method is called when the program is run from
       the command line. */
    public static void main(String argv[]) throws Exception {
        /* Create a SimpleWebServer object, and run it */
        SimpleWebServer sws = new SimpleWebServer();
        sws.run();
    }
}
