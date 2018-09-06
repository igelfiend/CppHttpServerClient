#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include <algorithm>

#include "httpclient.h"
#include "httpserver.h"

using namespace std;

bool compareFiles(const std::string& p1, const std::string& p2)
{
    cout << "comparing files:\n"
         << "\t f1: " << p1 << "\n"
         << "\t f2: " << p2 << endl;

    ifstream f1(p1, ifstream::binary | ifstream::ate);
    ifstream f2(p2, ifstream::binary | ifstream::ate);

    if( f1.fail() || f2.fail() )
    {
        cerr << "file opening problem" << endl;
        return false; //file problem
    }

    if( f1.tellg() != f2.tellg() )
    {
        cerr << "different size: "
             << f1.tellg()
             << " and "
             << f2.tellg()
             << endl;
        return false; //size mismatch
    }

    cout << "both sizes are " << f1.tellg() << endl;

    //seek back to beginning and use std::equal to compare contents
    f1.seekg( 0, ifstream::beg );
    f2.seekg( 0, ifstream::beg );
    return std::equal( istreambuf_iterator< char >( f1.rdbuf() ),
                       istreambuf_iterator< char >(),
                       istreambuf_iterator< char >( f2.rdbuf() ) );
}

void startServer( string address, string port, string sharePath )
{
    HttpServer server;

    server.setSharefoulderPath( sharePath );
    int result = server.start( address, port );

    switch( result )
    {
    case 0:
        break;
    case -1:
        cout << "Share path error"      << endl;
        cout << "Test failed"           << endl;
        break;
    case -2:
        cout << "Initing address error" << endl;
        cout << "Test failed"           << endl;
        break;
    case -3:
        cout << "Initing socket error"  << endl;
        cout << "Test failed"           << endl;
        break;
    default:
        cout << "Test failed"           << endl;
    }
}

int main(int argc, char *argv[])
{
    /// 1 arg: filename
    /// 2 arg: server.address
    /// 3 arg: server.port
    /// 4 arg: server.sharePath
    /// 5 arg: client.address
    /// 6 arg: client.port
    /// 7 arg: client.filename

    if( argc < 7 )
    {
        cerr << "To few arguments" << endl;
        cout << "Test failed"      << endl;
        return -1;
    }

    string serverAddress  ( argv[ 1 ] );
    string serverPort     ( argv[ 2 ] );
    string serverSharePath( argv[ 3 ] );

    string clientAddress ( argv[ 4 ] );
    string clientPort    ( argv[ 5 ] );
    string clientFilename( argv[ 6 ] );

    thread server( startServer, serverAddress, serverPort, serverSharePath );
    this_thread::sleep_for( chrono::milliseconds( 100 ) );

    HttpClient client;
    if( !client.connect( clientAddress, clientPort ) )
    {
        cout << "Test failed" << endl;
        cout << "Client connection error" << endl;
        return -1;
    }

    if( !client.downloadFile( clientFilename ) )
    {
        cout << "Test failed" << endl;
        cout << "Download file error" << endl;
        return -1;
    }

    string srcPath = serverSharePath + "/" + clientFilename;
    string tgtPath = "./" + clientFilename;

    if( !compareFiles( srcPath, tgtPath ) )
    {
        cout << "Test failed" << endl;
        return -1;
    }
    cout << "Test passed" << endl;
    return 0;
}
