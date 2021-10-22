#include <iostream>
#include <vector>
using namespace std;
bool protocol_error = false;
bool domain_errors = false;
bool port_error = false;
bool path_error = false;
// Hello World!
string protocol_Parse(string URL)
{
    string protocol = URL.substr(0, URL.find("//")-1); // locate the protocol by locating first ":"
    string protocol_2 = URL.substr(0, URL.find("//")-1); // double-checking through attempt to locate by the ":"
    if(! (protocol == protocol_2)) // first make sure a proper protocol exist
    {
        protocol_error = true;
        return "Protocol: incorrect protocol formatting/ can not locate protocol";
    }
    else if(protocol == "https" or protocol == "http" or protocol == "ftp" or protocol == "ftps") //if valid protocol
    {
        return "Protocol: " + protocol + "\n";
    }
    else // if not
    {
        protocol_error = true;
        return "Protocol: " + protocol + "is not a valid protocol\n";
    }
}

string domain_parse(string URL)
{
    int first_index = URL.find('//') +2;
    URL = URL.substr(first_index); // locating the "//" as the domain always follows it
    int last_index = 0;
    if(URL.find(':') != -1) // if a port exists
    {
         last_index= URL.find(':') ;
    }
    else // if not
    {
         last_index = URL.find('/') ;
    }
    string domain = URL.substr(0,last_index); // we had to do last_semi-first_semi because the natural flaw in the substring method, it is poping char as it is counting


    int counter = 0;
    for(int x =0; x < domain.length(); x++) // check if there are 3 "." seperating elements
    {
        if(domain.at(x) == '.')
        {
            counter ++;
        }

    }

    //extracting the true domain
    string ending = domain.substr(domain.rfind('.')+1);

   if (counter != 2 or (ending != "net" and ending != "com" and ending != "edu" and ending != "gov" and ending != "biz") )
    {
        domain_errors = true;
        return "Domain: " + ending + " is not a valid domain\n";
    }
    else
    {
        return "Domain: " + ending + " \n";

    }

}
string port_parse(string URL)
{

    int last_semi = URL.rfind(':');
    // getting rid of the protocol and domain by parsing out the string from 0 to the last semicolon
    string port = URL.substr(last_semi+1); // we had to do last_semi-first_semi because the natural flaw in the substring method, it is poping char as it is counting
    int first_dash = port.find("/"); // now find the next dash
    port = port.substr(0,first_dash); // get the numbers only

    if(last_semi <= 8 or  port == " " or port == "") // if port do not exist - <=8 is incase the only semicolon exist is the one in protocol
    {
        port_error = true;
        return "Port: Port do not exist"; // in case if the URL do not have a port i.e https://google.com/
    }



    bool num_only = true;
    for(int x = 0; x < port.length(); x ++) // check if the port string is only consisting of numbers, avoid stoi error
    {
        if(!isdigit(port[x]))
        {
            num_only = false;
        }
    }

    if(num_only)  // if it is entirly of numint port_num = stoi(port);bers we proceed to check its value
    {
        int port_num = stoi(port);
        if (port_num < 1 or port_num > 65535) {
            port_error = true;
            return "Port: port number must be between 1 and 65535";
        } else {
            return "Port: " + port + " \n";
        }
    }
    else // if not
    {
        return "Port: " + port + " is not a valid port / can not locate port due to incorrect URL formatting \n";
    }


}

string path_parse(string URL)
{

    int first_index = URL.find('//') +2;
    string path = URL.substr(first_index); // locating the "//" as the domain always follows it
    first_index = path.find('/') + first_index-1; // find the first "/" for path
     path = URL.substr(first_index);
    int last_index = 0;
    if(URL.find('?') != -1) // if a parameter exists
    {
        last_index= path.find('?') ;
    }
    else // if not
    {
        last_index = path.length();
    }



    path = path.substr(0,last_index); // get the path
    string ending = path.substr(path.rfind(".")+1); // get the ending
    if(not (path[0] = "/" and (ending == "html" or ending == "html"))) // checking the requirement of starting with / and ending with htm or html
    {
        path_error = true;
        return "path: " + path + " is not a valid path\n";
    }
    else
    {
        return "path: " + path + " \n";
    }
}

string parameters_parse(string URL)
{
    if(URL.rfind('?') != -1)//if there is a parameter
    {
        return "Parameters: " + URL.substr(URL.rfind("?")+1);
    }
    else
    {
        return "Parameters: None given"; // message to return if none given.
    }


}


int main(int argc, char* argv[]) {

    string input = string(argv[1]); // convert it to a string
    string protocol_status = protocol_Parse(input); // parse protocol
    string domain_status = domain_parse(input); // parse domain
    string port_status = port_parse(input); // parse port
    string path_status = path_parse(input);
    if(protocol_error or domain_errors or port_error or path_error)
    {
        //the general error message
        cout<< "Invalid URL with following erroneous components: "<<endl;
        //we display the corresponding message to the error
        if(protocol_error)
        {
            cout<<protocol_status<<endl;
        }
        if(domain_errors)
        {
            cout<<domain_status<<endl;
        }
        if(port_error)
        {
            cout<<port_status<<endl;
        }
        if(path_error)
        {
            cout<<path_status<<endl;
        }

        return 1; // return an error status and exit the program //exiting early to save computation power since we dont expect errors from Parameters



    }
    else
    {
        string parameter_status = parameters_parse(input); // now making sure the URL is correct we compute the parameters
        //displaying the information according to the given format
        cout<<protocol_status<<endl;
        cout<<domain_status<<endl;
        cout<<port_status<<endl;
        cout<<path_status<<endl;
        cout<<parameter_status<<endl;

    }

    return 0;
    }






