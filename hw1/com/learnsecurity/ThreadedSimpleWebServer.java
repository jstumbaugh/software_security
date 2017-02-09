package com.learnsecurity;

public class ThreadedSimpleWebServer {
    public static void main(String args[]) throws Exception {
        SimpleWebServer S1 = new SimpleWebServer("Thread 1", 8080);
        S1.start();

        SimpleWebServer S2 = new SimpleWebServer("Thread 2", 8081);
        S2.start();
    }
}
